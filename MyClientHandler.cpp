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
    mutex locker1;
    //locker1.lock();
    searchsolver = new OA<string, string>(BestFSsearcher);
    cm = new FileCacheManager<string,string>();
    line = getData(this->socknumber);
    //locker1.unlock();
    //cout << line << endl;
  //  locker1.lock();
    if (cm->get(line)!="-1") {
        string n = cm->get(line);
        const char *nsend = n.c_str();
        send(this->socknumber, nsend, strlen(nsend), 0);
        cout<<"sent get:"<<nsend<<endl;
        //locker1.unlock();
    } else {
        string answer = searchsolver->solve(line);
        cm->insert(line, answer);
        string n = cm->get(line);
        const char *nsend = n.c_str();
        send(this->socknumber, nsend, strlen(nsend), 0);
        cout<<"sent: "<<nsend<<endl;
       // locker1.unlock();
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