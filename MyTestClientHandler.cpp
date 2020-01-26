//
// Created by netanel on 12/01/2020.
//

#include <zconf.h>
#include <cstring>
#include <sys/socket.h>
#include "MyTestClientHandler.h"
#include "StringReverser.h"


MyTestClientHandler::MyTestClientHandler() {
}

/**
*this class reads from client's stream and handles the problem.
 */
void MyTestClientHandler::handleClient(int sockfd) {
    this->socknumber = sockfd;
    char buffer[1024] = {0};
    stringsolver = new StringReverser();
    cm = new FileCacheManager<string,string>();
    while (buffer != "end") {
        read(socknumber, buffer, 1024);
        if (cm->get(buffer) != "-1") {  //if the solution is n cache manager- send solution.
            string n = cm->get(buffer);
            const char *nsend = n.c_str();
            send(this->socknumber, nsend, strlen(nsend), 0);
        } else {                                  //else- solve problem
            cout << buffer << endl;
            string answer = stringsolver->solve(buffer);
            cm->insert(buffer, answer);
            string n = cm->get(buffer);
            const char *nsend = n.c_str();
            send(this->socknumber, nsend, strlen(nsend), 0);
            // cout << cm->get(buffer) << endl;

        }
    }
    std::cout << socknumber << std::endl;
}
