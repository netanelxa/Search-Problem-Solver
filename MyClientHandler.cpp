//
// Created by netanel on 18/01/2020.
//
#include "MyClientHandler.h"

#define bufferlength 1024


void MyClientHandler::handleClient(int sockfd) {
    this->socknumber = sockfd;
    char buffer[1024] = {0};
    string line;
    string temp_buffer;
    vector<string> matrix_vec;
    // searchsolver = new OA<string, string, string>;
    cm = new FileCacheManager<string, string>();
    while (true) {
        memset(buffer, 0, bufferlength);
        int i = 0;
        read(socknumber, buffer, bufferlength);
        while (buffer[i] != '\0' && i < bufferlength) {
            line += buffer[i];
            i++;
        }
        i = 0;
        while (!isEnd(buffer)) {
            int i = 0;
            memset(buffer, 0, bufferlength);
            read(socknumber, buffer, 1024);
            while (buffer[i] != '\0' && i < bufferlength) {
                line += buffer[i];
                i++;
            }
        }
        cout << line << endl;
        vector<State<Point> *> StateVector = matrixbuilder->build(line);
        if (cm->get(buffer) != "-1") {
            string n = cm->get(buffer);
            const char *nsend = n.c_str();
            send(this->socknumber, nsend, strlen(nsend), 0);
        } else {
            cout << buffer << endl;
            //       string answer = searchsolver->solve(buffer);
            //    cm->insert(buffer, answer);
            string n = cm->get(buffer);
            const char *nsend = n.c_str();
            send(this->socknumber, nsend, strlen(nsend), 0);
            // cout << cm->get(buffer) << endl;

        }
    }
    std::cout << socknumber << std::endl;
}


bool MyClientHandler::isEnd(string buffer) {
    int x = buffer.find("end");
    if (x < 0)
        return false;
    if (x >= 0) {
        buffer.erase(buffer.find("end"), 3);
        return true;
    }
}