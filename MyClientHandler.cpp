//
// Created by netanel on 18/01/2020.
//
#include "MyClientHandler.h"

#define bufferlength 1024

string MyClientHandler::getData(int sock_id) {
    string curr_line;
    string problem;
    while (true) { // condition to stop- inside
        curr_line = getLineFromSocket(sock_id);
        problem += curr_line;
        if (curr_line.find("end") != std::string::npos) {
            break;
        }
    }
    return problem;
}

string MyClientHandler::getLineFromSocket(int sock_id) {
    char buf[bufferlength];
    ssize_t readen_bytes;
    readen_bytes = read(sock_id, buf, bufferlength - 1);
    if (readen_bytes < 0) {
        __throw_bad_exception();
    } else if (readen_bytes == 0) {
        //connection closed
    } else {
        buf[readen_bytes] = NULL;
    }
    return buf;
}

void MyClientHandler::handleClient(int sockfd) {
    this->socknumber = sockfd;
    Searcher<Point> *DFSsearcher = new DFS<Point>();
    Searcher<Point> *ASsercher = new AStar<Point>();
    Searcher<Point> *BFSsearcher = new BFS<Point>();
    Searcher<Point> *BestFSsearcher = new BestFS<Point>();
    char buffer[1024] = {0};
    string line;
    string temp_buffer;
    vector<string> matrix_vec;
    searchsolver = new OA<string, string>(BestFSsearcher);
    cm = new FileCacheManager<string, string>();
    mutex g_i_mutex;
    g_i_mutex.lock();
    line = getData(this->socknumber);
    g_i_mutex.unlock();
    cout << line << endl;
    if (cm->get(line) != "-1") {
        g_i_mutex.lock();
        string n = cm->get(line);
        g_i_mutex.unlock();
        const char *nsend = n.c_str();
        send(this->socknumber, nsend, strlen(nsend), 0);
    } else {
        cout << buffer << endl;
        g_i_mutex.lock();
        string answer = searchsolver->solve(line);
        cm->insert(line, answer);
        string n = cm->get(line);
        g_i_mutex.unlock();

        const char *nsend = n.c_str();
        send(this->socknumber, nsend, strlen(nsend), 0);
        // cout << cm->get(buffer) << endl;
    }

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