#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"

/*
class Main{

    pthread_mutex_t mutexMap;
    pthread_mutex_t mutexFile;
    bool run;

    int main(int argc, char *args[]) {
        pthread_mutex_init(&mutexMap, nullptr);
        pthread_mutex_init(&mutexFile, nullptr);
        run = true;
        Searcher<Point> *searcher = new AStar<Point>();

        auto *solver = new SearcherSolver(searcher);
        CacheManager *cacheManager = new FileCacheManager();
        ClientHandler *clientHandler = new MatrixHandler(solver, cacheManager);
        server_side::Server *server = new server_side::ParallelServer();
        server->open(atoi(args[1]), clientHandler);
    }
};
*/

int main(int argc, char *argv[]) {
  //  MySerialServer *ms = new MySerialServer();
    MyParallelServer *ps=new MyParallelServer();
    ClientHandler *ch = new MyClientHandler();
    ps->open(stoi(argv[1]),ch);
   // ms->open(stoi(argv[1]), ch);
    return 0;
}