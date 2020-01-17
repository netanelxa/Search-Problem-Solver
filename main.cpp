#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"

int main() {
    MySerialServer *ms= new MySerialServer();
    ClientHandler *ch=new MyTestClientHandler();
    ms->open(5402,ch);
    CacheManager<string,string>  *cm = new FileCacheManager<string,string>();

    return 0;
}
