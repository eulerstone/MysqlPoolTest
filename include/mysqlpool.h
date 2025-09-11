#ifndef MYSQLPOOL_H
#define MYSQLPOOL_H

#include<iostream>
#include<mysql.h>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include<string>
#include<mutex>
#include<thread>



class MysqlPool {
  public:
    ~MysqlPool();
    std::map<std::string,std::vector<std::string> > executeSql(const char* sql);//sql语句的执行函数
    static MysqlPool& getInstance();  //单列模式获取本类的对象
    void setParameter( const char*   mysqlHost,
                       const char*   mysqlUser,
                       const char*   mysqlPwd,
                       const char*   databaseName,
                       unsigned int  port = 0,
                       const char*   socket = NULL,
                       unsigned long clientFlag = 0,
                       unsigned int  maxConnect = 50 );              //设置数据库参数
    unsigned int poolSize();                      //获取连接池的大小

  private:
    MysqlPool();
    MYSQL* createOneConnect();                    //创建一个新的连接对象
    MYSQL* getOneConnect();                       //获取一个连接对象
    void close(MYSQL* conn);                      //关闭连接对象
    bool isEmpty();                               //连接池队列池是否为空
    MYSQL* poolFront();                           //连接池队列的队头
    void poolPop();                               //弹出连接池队列的队头
    MysqlPool(const MysqlPool&) = delete;
    MysqlPool& operator=(const MysqlPool&) = delete;

private:
    std::queue<MYSQL*> mysqlpool;                 //连接池队列
    const char*   _mysqlhost;                     //mysql主机地址
    const char*   _mysqluser;                     //mysql用户名
    const char*   _mysqlpwd;                      //mysql密码
    const char*   _databasename;                  //要使用的mysql数据库名字
    unsigned int  _port;                          //mysql端口
    const char*   _socket;                        //可以设置成Socket or Pipeline，通常设置为NULL
    unsigned long _client_flag;                   //设置为0
    unsigned int  MAX_CONNECT;                    //同时允许最大连接对象数量
    unsigned int  connect_count;                  //目前连接池的连接对象数量
    std::mutex poollock;                   //连接池锁
    std::condition_variable poolcv;       // 等待/通知连接可用
    std::mutex coutMutex;
};

#endif
