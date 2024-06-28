#include "server.h"
#include <QDebug>
Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
    //connect(tcpServer, &QTcpServer::disconnect, this, &Server::disConnection);
    if (!tcpServer->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Error: Unable to start the server.";
    } else {
        qDebug() << "Server started. Listening on port 12345...";
    }
    db=new UserDatabase();
    db->openDatabase();
}

void Server::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    clients.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readyRead);
    connect(clientSocket, &QTcpSocket::disconnected, [&]() {
            qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();
            // Clean up resources related to this client
            int id=connectedClients[clientSocket];
            connectedClients.remove(clientSocket);
            connectedUser.remove(id);
            clientSocket->deleteLater();//断开连接
        });
    qDebug()<<"有用户端申请连接服务器";
}

// void Server::disConnection()
// {

// }

void Server::readyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    QString message = data;
    QString msgType=jsonObj.value("msgType").toString();
     qDebug()<<msgType<<jsonObj.value("username").toString();

    if(msgType=="REGISTER"||msgType=="LOGIN")//注册或登录
    {
        QString username=jsonObj.value("username").toString(),password=jsonObj.value("password").toString();
        QJsonObject jsonObj2;
        if(msgType=="REGISTER"){
            jsonObj2["msgType"]="REGISTER";
            if(db->registerUser(username,password)){
                qDebug()<<username<<"注册成功";
                jsonObj2["msg"]="success";
            }
            else{
                jsonObj2["msg"]="fail";
            }
        }
        else{
            jsonObj2["msgType"]="LOGIN";
            if(db->loginUser(username,password)){//在数据库中查看是否匹配
                jsonObj2["msg"]="success";
                jsonObj2["username"]=username;
                QString userIdentifier = username;
                int userId=db->queryUserId(username);
                jsonObj2["userId"]=userId;
                connectedClients[clientSocket] = userId;//用户端与用户ID进行直接关联
                qDebug()<<username<<":"<<userId;
                connectedUser[userId]=clientSocket;
                qDebug()<<username<<"登录成功！";
            }
            else{
                jsonObj2["msg"]="fail";
            }
        }
        QJsonDocument jsonDoc(jsonObj2);
        QByteArray data_ = jsonDoc.toJson();
        clientSocket->write(data_);
    }
    else if(msgType=="UPDATE_PROFILE"||msgType=="UPDATE_BGPHOTO"||msgType=="UPDATE_AGE"||msgType=="UPDATE_SEX")//用户基本信息变更消息
    {
        int userId= connectedClients[clientSocket];
        QString field;
        int serial=jsonObj.value("serial").toInt();
        if(msgType=="UPDATE_PROFILE")
            field="profile";
        else if(msgType=="UPDATE_BGPHOTO")
            field="bg_photo";
        else if(msgType=="UPDATE_AGE")
                field="age";
        else if(msgType=="UPDATE_SEX")
                field="sex";
        db->modifyBasicInfo(userId,field,serial);
    }
    else if(msgType=="FRIEND_MESSAGE"||msgType=="GROUP_MESSAGE")
    {
        int senderId=connectedClients[clientSocket];
        QString msg=jsonObj.value("msg").toString();
        QString timestamp=jsonObj.value("timestamp").toString();
        if(msgType=="FRIEND_MESSAGE"){
            int  receiverId=jsonObj.value("receiverId").toInt();
            QJsonObject jsonObj2;
            jsonObj2["msgType"]="FRIEND_MESSAGE";
            jsonObj2["senderId"]=senderId;
            jsonObj2["msg"]=msg;
            jsonObj2["timestamp"]=timestamp;
            qDebug()<<msg;
            if(connectedUser.find(receiverId)!=connectedUser.end()){//好友是否在线
                QJsonDocument jsonDoc2(jsonObj2);
                QByteArray data_ = jsonDoc2.toJson();
                qDebug()<<receiverId<<":好友在线";
                connectedUser[receiverId]->write(data_);
            }
            else{//不在线
                qDebug()<<receiverId<<":好友不在线";
               // db->addOffLineMsg(receiverId,jsonObj2);//存入离线消息库
            }
            //聊天记录保存
            QJsonObject jsonObj3;
            jsonObj3["senderId"]=jsonObj2["senderId"];
            jsonObj3["msg"]=jsonObj2["msg"];
            jsonObj3["timestamp"]=jsonObj2["timestamp"];
            db->addFriendChatRecord(senderId,receiverId,jsonObj3);
            db->addFriendChatRecord(receiverId,senderId,jsonObj3);
        }
        else{
            int groupId=jsonObj.value("groupId").toInt();
            qDebug()<<"向群发送消息"<<groupId;
            QJsonObject jsonObj2;
            jsonObj2["msgType"]="GROUP_MESSAGE";
            jsonObj2["senderId"]=senderId;
            jsonObj2["groupId"]=groupId;
            jsonObj2["msg"]=msg;
            jsonObj2["timestamp"]=timestamp;
            QJsonObject jsonObj_=db->getUserBasicInfo(senderId);
            jsonObj2["username"]=jsonObj_.value("username").toString();
            jsonObj2["profile"]=jsonObj_.value("profile").toInt();
            QVector<int> groupMembers=db->queryGroupMembers(groupId);//找寻群聊成员
            for(int member:groupMembers){
                qDebug()<<"群成员"<<member;
                if(member!=senderId){
                    if(connectedUser.find(member)!=connectedUser.end()){
                        qDebug()<<"在线";
                        QJsonDocument jsonDoc2(jsonObj2);
                        QByteArray data_ = jsonDoc2.toJson();
                        connectedUser[member]->write(data_);
                    }
                    else{
                        //db->addOffLineMsg(member,jsonObj2);//存入离线消息库
                    }
                }
            }
            //聊天记录保存
            QJsonObject jsonObj3;
            jsonObj3["senderId"]=jsonObj2["senderId"];
            jsonObj3["msg"]=jsonObj2["msg"];
            jsonObj3["timestamp"]=jsonObj2["timestamp"];
            db->addGroupChatRecord(groupId,jsonObj3);
        }
    }
    else if(msgType=="ADD_FRIEND"||msgType=="ACCEPT_FRIEND")
    {
        int receiverId=jsonObj.value("receiverId").toInt(),senderId=connectedClients[clientSocket];
        if(msgType=="ADD_FRIEND"){
            QString userName=jsonObj.value("userName").toString();
            receiverId=db->queryUserId(userName);
            qDebug()<<userName<<receiverId;
            //db->addFriend(senderId,receiverId);//自动建立好友关系
        }
        QString timestamp=jsonObj.value("timestamp").toString();
        QJsonObject jsonObj2;
        jsonObj2["msgType"]=msgType;
        jsonObj2["senderId"]=senderId;
        jsonObj2["timestamp"]=timestamp;
        QJsonObject jsonObj3=db->getUserBasicInfo(senderId);
        jsonObj2["senderName"]=jsonObj3.value("username").toString();
        jsonObj2["profile"]=jsonObj3.value("profile").toInt();
        if(msgType=="ADD_FRIEND"){
            //jsonObj2["status"]=0;//未办状态
            qDebug()<<"好友申请时间"<<timestamp;
            db->addToDoMsg(receiverId,jsonObj2);
        }
        else{
            int msgId=jsonObj.value("msgId").toInt();
            db->addFriend(senderId,receiverId);//好友建立
            qDebug()<<senderId<<receiverId<<"好友建立";
            db->deleteToDoMsg(msgId);
        }
        if(connectedUser.find(receiverId)!=connectedUser.end()){
            QJsonDocument jsonDoc2(jsonObj2);
            QByteArray data_ = jsonDoc2.toJson();
            connectedUser[receiverId]->write(data_);
        }//同意好友客户端不做反应,被添加者及时显示代办
    }
    else if(msgType=="APPLY_PAL"||msgType=="ACCEPT_PAL")
    {
        int receiverId=jsonObj.value("receiverId").toInt(),  senderId=connectedClients[clientSocket];
        int postId=jsonObj.value("postId").toInt();
        QString timestamp=jsonObj.value("timestamp").toString();
        QJsonObject jsonObj2;
        jsonObj2["msgType"]=msgType;
        jsonObj2["senderId"]=senderId;
        jsonObj2["postId"]=postId;
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString formattedDateTime = currentDateTime.toString("M/d/yy  hh:mm");
        jsonObj2["timestamp"]=formattedDateTime;
        QJsonObject jsonObj3=db->getUserBasicInfo(senderId);
        jsonObj2["senderName"]=jsonObj3.value("username").toString();
        jsonObj2["profile"]=jsonObj3.value("profile").toInt();
        jsonObj2["postName"]=db->queryGroupName(db->queryGroupId( postId));
        if(msgType=="APPLY_PAL"){
            //jsonObj2["status"]=0;
            db->addToDoMsg(receiverId,jsonObj2);
        }
        else{
            int groupId=db->queryGroupId(postId);
            db->addGroupMember(receiverId,groupId);//加入群,此处没有将pal关联post，待定
            int msgId=jsonObj.value("msgId").toInt();
            db->deleteToDoMsg(msgId);
        }
        if(connectedUser.find(receiverId)!=connectedUser.end()){
            QJsonDocument jsonDoc2(jsonObj2);
            QByteArray data_ = jsonDoc2.toJson();
            connectedUser[receiverId]->write(data_);
        }

    }
    else if(msgType=="PUBLISH_POST")
    {
        int senderId=connectedClients[clientSocket];
        QString kind=jsonObj.value("kind").toString(),content=jsonObj.value("content").toString(),
            totalNumOfPpl=jsonObj.value("totalNumOfPpl").toString(),
            timestamp=jsonObj.value("timestamp").toString();//imageUrl=jsonObj.value("imageUrl").toString(),
        db->addPostRecord(senderId,kind,content,totalNumOfPpl.toInt(),timestamp);//包含对group的处理
    }
    else if(msgType=="END_POST")//搭子组建完成
    {
        int postId=jsonObj.value("postId").toInt();
        db->endPost(postId);
    }
    else if(msgType=="OVER_POST")//活动结束
    {
        int postId=jsonObj.value("postId").toInt();
        db->overPost(postId);//包含对group的处理

    }
    else if(msgType=="DELETE_POST")//删除征求
    {
        int postId=jsonObj.value("postId").toInt();
        db->deletePost(postId);//包含对group的处理
    }
    else if(msgType=="FRIEND_LIST")//获取好友列表
    {
        int senderId=connectedClients[clientSocket];
        QJsonArray friendsInfo=db->getAllFriends(senderId);
        QJsonObject jsonObj2;
        jsonObj2["msgType"]=msgType;
        jsonObj2["jsonArray"]=friendsInfo;
        QJsonDocument jsonDoc2(jsonObj2);
        QByteArray data_ = jsonDoc2.toJson();
        connectedUser[senderId]->write(data_);
    }
    else if(msgType=="GROUP_LIST")//获取群聊列表
    {
        int senderId=connectedClients[clientSocket];
        QJsonArray groupsInfo=db->getAllGroups(senderId);
        QJsonObject jsonObj2;
        jsonObj2["msgType"]=msgType;
        jsonObj2["jsonArray"]=groupsInfo;
        QJsonDocument jsonDoc2(jsonObj2);
        QByteArray data_ = jsonDoc2.toJson();
        connectedUser[senderId]->write(data_);
    }
    else if(msgType=="TODO_LIST")//获取待办事项：好友申请、搭子申请
    {
        int senderId=connectedClients[clientSocket];
        QJsonArray todoList=db->getToDoList(senderId);
        QJsonObject jsonObj2;
        jsonObj2["msgType"]=msgType;
        jsonObj2["jsonArray"]=todoList;
        QJsonDocument jsonDoc2(jsonObj2);
        QByteArray data_ = jsonDoc2.toJson();
        connectedUser[senderId]->write(data_);
    }
    else if(msgType=="USERPOSTS"){
        int senderId=connectedClients[clientSocket];
        int userId=jsonObj.value("userId").toInt();
        QJsonArray myPosts=db->getUserPosts(userId);
        QJsonObject jsonObj2;
        jsonObj2["msgType"]=msgType;
        jsonObj2["jsonArray"]=myPosts;
        QJsonDocument jsonDoc2(jsonObj2);
        QByteArray data_ = jsonDoc2.toJson();
        connectedUser[senderId]->write(data_);
    }
    else if(msgType=="ONLINE_POSTS"){
        int senderId=connectedClients[clientSocket];
        QJsonArray onlinePosts=db->getOnlinePosts(senderId);
        QJsonObject jsonObj2;
        jsonObj2["msgType"]=msgType;
        jsonObj2["jsonArray"]=onlinePosts;
        QJsonDocument jsonDoc2(jsonObj2);
        QByteArray data_ = jsonDoc2.toJson();
        connectedUser[senderId]->write(data_);
    }
    else if(msgType=="USERINFO"){//获取好友基本背景信息
        int senderId=connectedClients[clientSocket];
        int userId=jsonObj.value("id").toInt();
        QJsonObject jsonObj2=db->getUserBasicInfo(userId);
        jsonObj2["msgType"]=msgType;//
        QJsonDocument jsonDoc2(jsonObj2);
        QByteArray data_ = jsonDoc2.toJson();
        connectedUser[senderId]->write(data_);
    }
    else if(msgType=="MYINFO"){//获得用户自己的基本信息
         int senderId=connectedClients[clientSocket];
        QJsonObject jsonObj2=db->getUserBasicInfo(senderId);
        jsonObj2["msgType"]=msgType;//
        QJsonDocument jsonDoc2(jsonObj2);
        QByteArray data_ = jsonDoc2.toJson();
        connectedUser[senderId]->write(data_);
    }
    else if(msgType=="DISAGREE"){
        int msgId=jsonObj.value("msgId").toInt();
        db->deleteToDoMsg(msgId);
    }
}
