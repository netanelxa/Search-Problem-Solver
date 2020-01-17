//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "Server.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <thread>
#include <string>
class MySerialServer : public server_side::Server {
public:
    virtual void open(int port, ClientHandler *c);

    virtual void stop(int sockfd);

    virtual ~MySerialServer() {}
};


#endif //EX4_MYSERIALSERVER_H
