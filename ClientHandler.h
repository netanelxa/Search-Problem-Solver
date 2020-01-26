//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H


#include <string>
/**
*ClientHandler header
 */
class ClientHandler {
public:
    virtual void handleClient(int sockfd) = 0;
};


#endif //EX4_CLIENTHANDLER_H
