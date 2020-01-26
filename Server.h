//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"

/**
*this class represents server.
 */
namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *c) = 0;

        virtual void stop(int sockfd) = 0;

        virtual ~Server() {}
    };
}


#endif //EX4_SERVER_H
