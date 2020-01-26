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

/**
*this class represents boot namespace. The class contains the main and boots the class MySerialServer.
 */

namespace boot {
    class Main {
    public:
        Main() {}

        void main(int port) {
            server_side::Server *ps = new MyParallelServer();
            ClientHandler *ch = new MyClientHandler();
            ps->open(port, ch);
        }
    };
}
#endif //EX4_BOOT_H
