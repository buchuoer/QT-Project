#ifndef DATABASE_H
#define DATABASE_H
# include <QSqlDatabase>
# include<QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class UserDatabase
{
public:
    UserDatabase();
    bool openDatabase();

    void closeDatabase();

    bool registerUser(const QString& username, const QString& password);

    bool loginUser(const QString& username, const QString& password);

    bool addFriend(int userId, int friendId);

    int  addGroupChat(const QString &groupName);//返回groupId

    bool addGroupMember(int userId, int groupId);

    bool addFriendChatRecord(int userId, int friendId, const QJsonObject & message);

    bool addGroupChatRecord( int groupId, const QJsonObject &message);

    bool addPostRecord(int userId,const QString & kind, const QString & content, int totalPpl,const QString & timestamp, const QString &imageUrl="");

    bool addPostPal(int userId, int postId);

    int  queryUserId(QString username);

    QString queryUsername(int userId);

    QVector<int> queryGroupMembers(int groupId);

    int queryGroupId(int postId);

    QString queryGroupName(int groupId);

    //int queryPostId(int userId,const QString kind,content)

    QJsonObject getUserBasicInfo(int userId);

    QJsonArray getAllFriends(int userId);

    QJsonArray getAllGroups(int userId);

    QJsonArray getToDoList(int userId);//待办事项：好友申请、搭子申请

    QJsonArray getUserPosts(int userId);//

    QJsonArray getOnlinePosts(int userId);//

    bool modifyBasicInfo(int userId, QString field, const int& serial);//基本信息更改

    bool addToDoMsg(int receiverId, const QJsonObject& message);//插入离线数据

    bool deleteToDoMsg(int userId,const QJsonObject& message);

    bool endPost(int postId);//停止搭子招募

    bool overPost(int postId);//搭子活动彻底结束

    bool deletePost(int postId);

    bool deleteGroup(int groupId);

    bool deleteToDoMsg(int msgId);

    bool postJoined(int userId,int postId);
    int getGroupMembersCount(int groupId);


private:
    QSqlDatabase db;

};

#endif // DATABASE_H
