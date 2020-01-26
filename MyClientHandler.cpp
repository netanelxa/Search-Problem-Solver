//
// Created by netanel on 18/01/2020.
//
#include "MyClientHandler.h"

#define bufferlength 1024

/**
*this class reads and handles problem from client.
 */


//return problem from client
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

//read one line from client's problem
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

    searchsolver = new OA<string, string>(BestFSsearcher); //using Object Adaptor
    cm = new FileCacheManager<string,string>();
    line = getData(this->socknumber);
    if (cm->get(line)!="-1") {            // if solution exists in cache- send solution to client.
        string n = cm->get(line);
        const char *nsend = n.c_str();
        send(this->socknumber, nsend, strlen(nsend), 0);
      //  cout<<"sent get:"<<nsend<<endl;
    } else {
        string answer = searchsolver->solve(line);   //else- solve problem
        cm->insert(line, answer);
        string n = cm->get(line);
        const char *nsend = n.c_str();
        send(this->socknumber, nsend, strlen(nsend), 0);
    //    cout<<"sent: "<<nsend<<endl;
    }

}

//return true if the buffer reached end of problem.
bool MyClientHandler::isEnd(string buffer) {
    int x = buffer.find("end");
    if (x < 0)
        return false;
    if (x >= 0) {
        buffer.erase(buffer.find("end"), 3);
        return true;
    }
}