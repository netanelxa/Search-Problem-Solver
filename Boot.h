//
// Created by netanel on 24/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H


#include "Server.h"
#include "MyParallelServer.h"
#include "Solver.h"
#include "OA.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"

namespace boot {
    class Main {
    public:
        Main() {}

        void main(int port) {
            server_side::Server *ps = new MyParallelServer();
            //the best algorithm for matrix problem
            ClientHandler *ch = new MyClientHandler();
            //open the connection and solve problems
            ps->open(port, ch);
        }
    };
}
#endif //EX4_BOOT_H
