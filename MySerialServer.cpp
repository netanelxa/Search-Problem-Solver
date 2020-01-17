//
// Created by netanel on 12/01/2020.
//

#include "MySerialServer.h"
#include "MyTestClientHandler.h"

using namespace std;

void StartServer(ClientHandler *c, int socketfd, sockaddr_in address) {
   /* struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;*/
    while (true) {
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
     //   setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof(struct timeval));
        cout << "Client accepted" << endl;
        if (client_socket == -1) {
            std::cout << "Error accepting client" << std::endl;
        } else if (errno == EWOULDBLOCK) {
            cout << "timeout!" << endl;
            break;
        }
        c->handleClient(client_socket);
    }
}


void MySerialServer::open(int port, ClientHandler *c) {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }

    //making socket listen to the port
    if (listen(socketfd, 1) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client

    //close(socketfd); //closing the listening socket

    thread thread1([=] { StartServer(c, socketfd, address); });
    thread1.join();


};

void MySerialServer::stop(int sockfd) {
    close(sockfd);
};

