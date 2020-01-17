//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "Solver.h"
#include <iostream>
#include "FileCacheManager.h"
#include "CacheManager.h"


class MyTestClientHandler : public ClientHandler {
    int socknumber;
    CacheManager<string,string> *cm;
    Solver<string,string> *stringsolver;
public:
    MyTestClientHandler();

    virtual void handleClient(int sockfd);


    virtual ~MyTestClientHandler() {}
};


#endif //EX4_MYTESTCLIENTHANDLER_H
