#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"
#include "Boot.h"


int main(int argc, char *argv[]) {
    if (argc == 1) {
        int port = 5600;
        auto *m = new boot::Main();
        m->main(port);
    } else {
        int port = stoi(argv[1]);
        auto *m = new boot::Main();
        m->main(port);
    }
    return 0;
}
