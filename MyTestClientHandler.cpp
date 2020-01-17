//
// Created by netanel on 12/01/2020.
//

#include <zconf.h>
#include "MyTestClientHandler.h"
#include "StringReverser.h"


MyTestClientHandler::MyTestClientHandler() {
}

void MyTestClientHandler::handleClient(int sockfd) {
    this->socknumber = sockfd;
    char buffer[1024] = {0};
    stringsolver = new StringReverser();
    while (buffer != "\0") {
        read(socknumber, buffer, 1024);
        if (cm->get(buffer) != "-1") {
            cout << cm->get(buffer);
        } else {
            cout << buffer << endl;
            string answer = stringsolver->solve(buffer);
            cm->insert(answer);
        }
    }
    std::cout << socknumber << std::endl;

}
