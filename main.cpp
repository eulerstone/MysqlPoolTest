#include"include/mysqlpool.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cstdlib>


std::mutex coutMutex;

void queryTask(int id, MysqlPool* pool) {

    auto result = pool->executeSql("SELECT * FROM test;");

}

int main() {
    MysqlPool& mysql = MysqlPool::getInstance();
    mysql.setParameter("localhost", "root", "000617", "mysqltest", 3306, NULL, 0, 5);

    const int threadCount = 20; // 启动20个线程
    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(queryTask, i, &mysql);
    }

    for (auto& t : threads) t.join();

    std::cout << "Final pool size: " << mysql.poolSize() << std::endl;

    return 0;
}

/*int main() {
  MysqlPool& mysql = MysqlPool::getInstance();
  mysql.setParameter("localhost","root","000617","mysqltest",0,NULL,0,2);
  std::map<std::string, std::vector<std::string> > m = mysql.executeSql("select * from test");
  for (std::map<std::string, std::vector<std::string> >::iterator it = m.begin() ; it != m.end(); ++it) {
    std::cout << it->first << std::endl;
    const std::string field = it->first;
    for (size_t i = 0;i < m[field].size();i++) {
      std::cout <<  m[field][i]  << std::endl;
    }
  }
  return 0;
}*/
