#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"


int main(int argc, char *argv[]) {
    MySerialServer *ms = new MySerialServer();
    ClientHandler *ch = new MyTestClientHandler();
    ms->open(stoi(argv[1]), ch);
    return 0;
}