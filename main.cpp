#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"

int main() {
    MySerialServer *ms= new MySerialServer();
    ClientHandler *ch=new MyTestClientHandler();
    ms->open(5405,ch);
    return 0;
}
