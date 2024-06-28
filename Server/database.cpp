# include "Database.h"
  #include <QCoreApplication>
UserDatabase:: UserDatabase()
{

    QString dbpath = QCoreApplication::applicationDirPath() +"//database.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbpath);
    if(db.open()){
        QSqlQuery query(db);
        //创建用户表
        query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(255) NOT NULL UNIQUE, password VARCHAR(255) NOT NULL, "
                   "sex INT, age INT , profile INT, bg_photo INT)");
        qDebug()<< "Error create table1: " <<query.lastError().text();
        //创建好友表
        query.exec("CREATE TABLE IF NOT EXISTS friends (user_id INT, friend_id INT, PRIMARY KEY (user_id, friend_id))");
         qDebug()<< "Error create table2: " <<query.lastError().text();
        //创建群聊表
        query.exec("CREATE TABLE IF NOT EXISTS group_chats (id INTEGER PRIMARY KEY AUTOINCREMENT , name VARCHAR(255))");
          qDebug()<< "Error create table3: " <<query.lastError().text();
        //创建群成员表
        query.exec("CREATE TABLE IF NOT EXISTS post_and_group (post_id INT, group_id INT, PRIMARY KEY (post_id , group_id))");
           qDebug()<< "Error create table4: " <<query.lastError().text();
        query.exec("CREATE TABLE IF NOT EXISTS group_members (group_id INT, user_id INT, PRIMARY KEY (group_id, user_id))");
            qDebug()<< "Error create table5: " <<query.lastError().text();
        //创建好友聊天记录表
        query.exec("CREATE TABLE IF NOT EXISTS friend_chat_records (user_id INT, friend_id INT, message TEXT,PRIMARY KEY (user_id  , friend_id ))");
             qDebug()<< "Error create table6: " <<query.lastError().text();
            //创建群聊天记录表
        query.exec("CREATE TABLE IF NOT EXISTS group_chat_records (group_id INT PRIMARY KEY, message TEXT)");
              qDebug()<< "Error create table7: " <<query.lastError().text();
        //创建搭子征求信息表
        query.exec("CREATE TABLE IF NOT EXISTS posts ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "user_id INT,"
                   "kind VARCHAR(255),"
                   "content TEXT,"
                   "image_url TEXT,"
                   "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                   "cur_num_of_ppl INT,"//当下人数
                   "total_num_of_ppl INT,"//总人数
                   "publish_status BOOL,"//发布状态（布尔
                   "FOREIGN KEY(user_id) REFERENCES users(id))");
               qDebug()<< "Error create table8: " <<query.lastError().text();
        //加入用户与征集信息关系表
        query.exec("CREATE TABLE IF NOT EXISTS post_pal (user_id INT, post_id INT,PRIMARY KEY (user_id , post_id ) )");
                qDebug()<< "Error create table9: " <<query.lastError().text();
        //待办事项
        query.exec("CREATE TABLE IF NOT EXISTS to_do_messages (id INTEGER PRIMARY KEY AUTOINCREMENT,receiver_id INT, message TEXT)");
         qDebug()<< "Error create table10: " <<query.lastError().text();
        db.commit();
        qDebug()<<"数据库建立！";
        db.close();
    }
    else {
        qDebug() << "Database Error: " << db.lastError().text();
    }
}

bool UserDatabase::  openDatabase()
{
    return db.open();
}

void UserDatabase:: closeDatabase()
{
    db.close();
}

bool UserDatabase:: registerUser(const QString& username, const QString& password)//用户注册
{
    QSqlQuery query(db);
    qDebug()<<username<<"开始注册";
    query.prepare("INSERT INTO users(username, password, sex, age, profile, bg_photo) VALUES (?,?,1,0,1,1)");
    query.addBindValue(username);
    query.addBindValue(password);
    if(query.exec()){
        db.commit();
        return 1;
    }
    else{
        qDebug()<< "Error inserting data: " <<query.lastError().text();
        return 0;
    }
    // query.exec()&&db.commit();
}

bool UserDatabase:: loginUser(const QString& username, const QString& password)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    return query.exec() && query.next();
}

//添加好友
bool UserDatabase::addFriend(int userId, int friendId)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO friends (user_id, friend_id) VALUES (?, ?)");
    query.addBindValue(userId);
    query.addBindValue(friendId);
    return query.exec();
}

//添加群
int UserDatabase::addGroupChat(const QString &groupName)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO group_chats (name) VALUES (?)");
    query.addBindValue(groupName);
    int groupId=0;
    if(query.exec()){
        groupId=query.lastInsertId().toInt();
    }

    return groupId;
}
//添加群成员表
bool UserDatabase::addGroupMember(int userId, int groupId)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO group_members (user_id,group_id) VALUES (?,?)");
    query.addBindValue(userId);
    query.addBindValue(groupId);
    return query.exec();
}

//添加好友聊天记录
bool UserDatabase::addFriendChatRecord(int userId, int friendId, const QJsonObject &message)
{
    QSqlQuery query(db);
    query.prepare("SELECT message FROM friend_chat_records WHERE user_id = :userId AND friend_id = :friendId");
    query.bindValue(":userId",userId);
    query.bindValue(":friendId",friendId);
    QJsonArray jsonArray;
    if(query.exec()){
        QString jsonStr = query.value(0).toString();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonStr.toUtf8());
        jsonArray = jsonResponse.array();
        jsonArray.append(message);
        QString chatData = QJsonDocument(jsonArray).toJson(QJsonDocument::Compact);
        query.prepare("UPDATE friend_chat_records SET message = :updatedText WHERE user_id = :userId AND friend_id = :friendId");
        query.bindValue(":updatedText",chatData);
        query.bindValue(":userId",userId);
        query.bindValue(":friendId",friendId);
    }
    else{
        qDebug() << "Error fetching chat text" ;
        jsonArray.append(message);//两人的第一条消息
        QString chatData = QJsonDocument(jsonArray).toJson(QJsonDocument::Compact);
        query.prepare("INSERT friend_chat_records(user_id,friend_id,message) VALUES(?,?,?)");
        query.addBindValue(userId);
        query.addBindValue(friendId);
        query.addBindValue(chatData);
    }
    return query.exec();
}

//添加群聊聊天记录
bool UserDatabase::addGroupChatRecord( int groupId, const QJsonObject &message)
{
    QSqlQuery query(db);
    query.prepare("SELECT message FROM group_chat_records WHERE group_id = :groupId");
    query.bindValue(":groupId",groupId);
    QJsonArray jsonArray;
    if(query.exec()){
        QString jsonStr = query.value(0).toString();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonStr.toUtf8());
        jsonArray = jsonResponse.array();
        jsonArray.append(message);
        QString chatData = QJsonDocument(jsonArray).toJson(QJsonDocument::Compact);
        query.prepare("UPDATE friend_chat_records SET message = :updatedText WHERE group_id = :groupId");
        query.bindValue(":updatedText",chatData);
        query.bindValue(":groupId",groupId);
    }
    else{
        qDebug() << "Error fetching chat text" ;
        jsonArray.append(message);//群的第一条消息
        QString chatData = QJsonDocument(jsonArray).toJson(QJsonDocument::Compact);
        query.prepare("INSERT group_chat_records(group_id,message) VALUES(?,?)");
        query.addBindValue(groupId);
        query.addBindValue(chatData);
    }
    return query.exec();
}
//增加征求发布
bool UserDatabase::addPostRecord(int userId,const QString & kind, const QString & content, int totalPpl, const QString & timestamp,const QString & imageUrl )
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO posts(user_id, kind, content, "
                  "image_url, timestamp,"
                  " total_num_of_ppl, publish_status,cur_num_of_ppl) VALUES(?,?,?,?,?,?,1,0)");
    query.addBindValue(userId);
    query.addBindValue(kind);
    query.addBindValue(content);
    query.addBindValue(imageUrl);
    query.addBindValue(timestamp);
    query.addBindValue(totalPpl);
    bool t=0;
    int postId=0 ;
    if(query.exec()){
        t=1;
        postId= query.lastInsertId().toInt();//获得最新加入的postId
    }
    //同时创建群,并建构post和group的联系
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("M/d/yy");
    QString groupName=kind+" "+formattedDateTime;//群名，采用类型+日期的方式
    int groupId=addGroupChat(groupName);
    addGroupMember(userId,groupId);
    query.prepare("INSERT INTO post_and_group(post_id, group_id) VALUES(?,?)");
    query.addBindValue(postId);
    query.addBindValue(groupId);
    return t&&query.exec();
};


bool UserDatabase::addPostPal(int userId, int postId)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO post_pal(user_id, post_id) VALUES(?,?)");
    query.addBindValue(userId);
    query.addBindValue(postId);
    bool t=0;
    if(query.exec())
        t=1;
    int groupId=queryGroupId(postId);
    return t&&addGroupMember(userId,groupId);
}

int UserDatabase::queryUserId(QString username)
{
    QSqlQuery query(db);
    query.prepare("SELECT id FROM users where username = :username");
    query.bindValue(":username",username);
    int userId=0;
    if(query.exec()&&query.next()){
        userId=query.value(0).toInt();
    }
    else{
        qDebug()<<"无此用户名";
    }
    return userId;
}

QString UserDatabase::queryUsername(int userId)
{
    QSqlQuery query(db);
    query.prepare("SELECT username FROM users where id = :userId");
    query.bindValue(":userId",userId);
    QString username="";
    if(query.exec()&&query.next()){

        username=query.value(0).toString();

    }
    else{
        qDebug()<<"无此用户ID";
    }
    return username;

}

 bool  UserDatabase::modifyBasicInfo(int userId, QString field, const int& serial)
{
    QSqlQuery query(db);
    QString m="UPDATE users SET ";
    m.append(field);
    m.append(" = :newInfo WHERE id = :userId");
    query.prepare(m);
    query.bindValue(":newInfo",serial);
    query.bindValue(":userId",userId);
    return query.exec();
 }

 QVector<int> UserDatabase::queryGroupMembers(int groupId)
 {
     QVector<int> v;
     QSqlQuery query(db);
     query.prepare("SELECT user_id FROM group_members WHERE group_id = :groupId");
     query.bindValue(":groupId", groupId);
     if(query.exec()){
         while(query.next()){
             int userId = query.value(0).toInt();
             v.push_back(userId);
         }
     }
     return v;
 }

bool UserDatabase::addToDoMsg(int receiverId, const QJsonObject& message)
{
    QSqlQuery query(db);
    QJsonDocument jsonDoc(message);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    query.prepare("INSERT INTO to_do_messages(receiver_id,message) VALUES(?,?)");
    query.addBindValue(receiverId);
    query.addBindValue(jsonString);
    qDebug()<<"存入一条待办消息"<<message.value("senderName").toString();
    return query.exec();
}

bool UserDatabase::deleteToDoMsg(int userId,const QJsonObject& message)
{
    QSqlQuery query(db);
    query.prepare("DELETE  FROM to_do_messages WHERE receiver_id = :userId AND message = :message");
    query.bindValue(":userId",userId);
    query.bindValue(":message",message);
    return query.exec();
}

bool UserDatabase::endPost(int postId)
{
    QSqlQuery query(db);
    query.prepare("UPDATE posts SET publish_status = :newstatus WHERE id = :postId");
    query.bindValue(":newstatus",0);//用0代表这一状态
    query.bindValue(":postId",postId);
    return query.exec();
}

bool UserDatabase::overPost(int postId)//群的聊天记录删除，以及群的相关信息整体删除
{
    int groupId=queryGroupId(postId);
    QSqlQuery query(db);
    query.prepare("DELETE FROM post_and_group WHERE group_id = :groupId");//解除群与post关系
    query.bindValue(":groupId",groupId);
    bool t=0;
    if(query.exec())
        t=1;
    query.prepare("UPDATE posts SET publish_status = :newstatus WHERE id = :postId");
    query.bindValue(":newstatus",-1);//用-1代表这一状态
    query.bindValue(":postId",postId);
    return t&&query.exec()&&deleteGroup(groupId);
}
int UserDatabase::queryGroupId(int postId)
{
    QSqlQuery query(db);
    query.prepare("SELECT group_id FROM post_and_group WHERE post_id = :postId");
    query.bindValue(":postId",postId);
    if(query.exec()&&query.next())
        return query.value(0).toInt();
    return 0;
}

QString UserDatabase::queryGroupName(int groupId)
{
    QSqlQuery query(db);
    query.prepare("SELECT name FROM group_chats WHERE id = :groupId");
    query.bindValue(":groupId",groupId);
    if(query.exec()&&query.next())
        return query.value(0).toString();
    return "";
}

bool UserDatabase::deletePost(int postId)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM posts WHERE id = :postId");
    query.bindValue(":postId",postId);
    query.exec();
    int groupId=queryGroupId(postId);
    query.prepare("DELETE FROM post_and_group WHERE post_id = :postId");
    query.bindValue(":postId",postId);
    return query.exec()&&deleteGroup(groupId);
}

bool UserDatabase::deleteGroup(int groupId)
{
    QSqlQuery query(db);
    bool t=0;
    query.prepare("DELETE FROM group_chats WHERE id = :groupId");//删除群（解散群
    query.bindValue(":groupId",groupId);
    if(query.exec())
        t=1;
    query.prepare("DELETE FROM group_members WHERE group_id = :groupId");//群成员关系解除
    query.bindValue(":groupId",groupId);
    if(t&&query.exec())
        t=1;
    else
        t=0;
    query.prepare("DELETE FROM group_chat_records  WHERE group_id = :groupId");//聊天记录删除
    query.bindValue(":groupId",groupId);
    return t&&query.exec();

}

QJsonObject UserDatabase::getUserBasicInfo(int userId)
{
    QSqlQuery query(db);
    query.prepare("SELECT sex, age, profile, bg_photo,username FROM users where id = :userId");
    query.bindValue(":userId",userId);
    QJsonObject jsonObj;
    if(query.exec()&&query.next()){
        int sex=query.value(0).toInt(),age=query.value(1).toInt(),
            profile=query.value(2).toInt(),bgPhoto=query.value(3).toInt();
        QString username=query.value(4).toString();
        jsonObj["sex"]=sex;
        jsonObj["age"]=age;
        jsonObj["profile"]=profile;
        jsonObj["bgPhoto"]=bgPhoto;
        jsonObj["username"]=username;
        jsonObj["userId"]=userId;
    }
    return jsonObj;
}
QJsonArray UserDatabase::getAllFriends(int userId)
{
    QJsonArray friendsInfo;
    QSqlQuery query(db);
    query.prepare("SELECT friend_id FROM friends WHERE user_id = :userId");
    query.bindValue(":userId",userId);
    if(query.exec()){
        while(query.next()){
            int friendId=query.value(0).toInt();
            QJsonObject friendJson;
            friendJson=getUserBasicInfo(friendId);
            friendsInfo.append(friendJson);
        }
    }
    query.prepare("SELECT user_id FROM friends WHERE friend_id = :userId");
    query.bindValue(":userId",userId);
    if(query.exec()){
        while(query.next()){
            int friendId=query.value(0).toInt();
            QJsonObject friendJson;
            friendJson=getUserBasicInfo(friendId);
            friendsInfo.append(friendJson);
        }
    }
    qDebug()<<userId<<"好友数"<<friendsInfo.size();
    return friendsInfo;
}

int UserDatabase::getGroupMembersCount(int groupId){
    QSqlQuery qeury(db);
    qeury.prepare("SELECT * FROM group_members WHERE group_id = :groupId");
    if(qeury.exec()){
        return qeury.size();
    }
    return -1;
}

QJsonArray UserDatabase::getAllGroups(int userId)
{
    QJsonArray groupsInfo;
    QSqlQuery query(db);
    query.prepare("SELECT group_id FROM group_members WHERE user_id = :userId");
    query.bindValue(":userId",userId);
    if(query.exec()){
        while(query.next()){
            int groupId=query.value(0).toInt();
            QString groupName=queryGroupName(groupId);
            QJsonObject groupJson;
            groupJson["groupName"]=groupName;
            groupJson["groupId"]=groupId;
            groupsInfo.append(groupJson);
        }
    }
    return groupsInfo;
}

QJsonArray UserDatabase::getToDoList(int userId)
{
    QJsonArray todoList;
    QSqlQuery query(db);
    query.prepare("SELECT id,message FROM to_do_messages WHERE receiver_id = :userId");
    query.bindValue(":userId",userId);
    if(query.exec()){
        while(query.next()){
            //if(query.value(1).isObject())
            QString jsonString=query.value(1).toString();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
            // 获取 QJsonObject
            QJsonObject jsonObj = jsonDoc.object();
            qDebug()<<"待办消息发送者"<<jsonObj.value("senderName").toString();
            jsonObj["msgId"]=query.value(0).toInt();
            todoList.append(jsonObj);
        }
    }
    return todoList;
}


bool UserDatabase::deleteToDoMsg(int msgId)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM to_do_messages WHERE id = :msgId");
    query.bindValue(":msgId",msgId);
    return query.exec();
}

QJsonArray UserDatabase::getUserPosts(int userId)//
{
    QSqlQuery query(db);
    query.prepare("SELECT id,kind,content,timestamp, publish_status FROM posts WHERE user_id = :userId");
    query.bindValue(":userId",userId);
    query.exec();
    QJsonArray myPosts;
    while(query.next()){
        QJsonObject post;
        int postId=query.value(0).toInt();
        QString kind=query.value(1).toString(),content=query.value(2).toString(),
            timestamp=query.value(3).toString();
        int publishStatus=query.value(4).toInt();
        QJsonObject userObj=getUserBasicInfo(userId);
        QString username=userObj.value("username").toString();
        int profile=userObj.value("profile").toInt();
        post["postId"]=postId;
        post["kind"]=kind;
        post["content"]=content;
        post["timestamp"]=timestamp;
        post["username"]=username;
        post["profile"]=profile;
        post["publishStatus"]=publishStatus;
        qDebug()<<"publishStatus"<<publishStatus;
        myPosts.append(post);
    }
    return myPosts;
}
bool UserDatabase::postJoined(int userId,int postId){
    QSqlQuery query(db);
    int groupId=queryGroupId(postId);
    query.prepare("SELECT * FROM group_members WHERE group_id = ? AND user_id = ?");
    query.addBindValue(groupId);
    query.addBindValue(userId);
    if(query.exec()&&query.next()){
        return 1;
    }
    return 0;
}


QJsonArray UserDatabase::getOnlinePosts(int userId)//
{
    QSqlQuery query(db);
    QJsonArray onlinePosts;
    query.prepare("SELECT id,kind,content,timestamp,user_id FROM posts WHERE publish_status = 1");
    if(query.exec()){
        while(query.next()){
            QJsonObject post;
            int postUserId=query.value(4).toInt(),postId=query.value(0).toInt();
            QString kind=query.value(1).toString(),content=query.value(2).toString(),
                timestamp=query.value(3).toString();
            post["userId"]=postUserId;
            QJsonObject userObj=getUserBasicInfo(postUserId);
            QString username=userObj.value("username").toString();
            int profile=userObj.value("profile").toInt();
            post["username"]=username;
            post["profile"]=profile;
            post["postId"]=postId;
            post["kind"]=kind;
            post["content"]=content;
            post["timestamp"]=timestamp;
            post["publish_status"]=1;
            if(postJoined(userId,postId)){//是否参加post
                post["joined"]=1;
            }
            else{
                post["joined"]=0;
            }
            onlinePosts.append(post);
        }
    }
    return onlinePosts;
}
