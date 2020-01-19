#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"


int main(int argc, char *argv[]) {
    MySerialServer *ms = new MySerialServer();
    ClientHandler *ch = new MyClientHandler();
    ms->open(stoi(argv[1]), ch);
    return 0;
}