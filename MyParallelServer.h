//
// Created by netanel on 22/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include <vector>
#include <thread>
#include "vector"
#include "Server.h"
using namespace std;
class MyParallelServer: public server_side::Server{
vector<std::thread> m_threads;
ClientHandler* m_handler;

private:
static void clientHandlerObjectFunctionAdapter(ClientHandler* ch, int sockfd);

public:
MyParallelServer();
virtual ~MyParallelServer();

virtual void open(int port, ClientHandler* ch);
virtual void stop(int sockfd);


};


#endif //EX4_MYPARALLELSERVER_H
