//
// Created by netanel on 18/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H


#include "ClientHandler.h"
#include "OA.h"
#include "string"
#include "FileCacheManager.h"
#include <zconf.h>
#include <cstring>
#include <sys/socket.h>
#include "vector"
#include "Point.h"
#include "MatrixBuilder.h"

using namespace std;

class MyClientHandler : public ClientHandler {
    int socknumber;
    OA<string, string, string> *searchsolver;
    FileCacheManager<string,string> *cm;
    MatrixBuilder *matrixbuilder;

public:
    virtual void handleClient(int sockfd);
    bool isEnd(string buffer);
    string MatrixBuild(string line);

};


#endif //EX4_MYCLIENTHANDLER_H
