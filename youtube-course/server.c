//
// Created by ibrah on 12/13/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    // 1.create a socket for server
    int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFD != -1) {
        printf("Server Socket ID: %d\n", serverSocketFD);
    } else {
        printf("Faild to create socket\n");
        exit(1);
    }

    // 2. bind the socket to a specific port
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(2000);

    if (bind(serverSocketFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == 0) {
        printf("Binded to port 2000\n");
    } else {
        printf("Faild to bind to port 2000\n");
        exit(1);
    }

    // 3. listen for connections
    if (listen(serverSocketFD, 5) == 0) {
        printf("Listening for connections\n");
    } else {
        printf("Faild to listen for connections\n");
        exit(1);
    }

    // 4. accept a connection
    struct sockaddr_in connentclientAddress;
    memset(&connentclientAddress, 0, sizeof(connentclientAddress));

    int clientaddrlenght = 0;

    int connectionServerSockFD= accept(serverSocketFD, (struct sockaddr *) &connentclientAddress, &clientaddrlenght);

    if (connectionServerSockFD == -1) {
        printf("Faild to accept connection\n");
        exit(1);
    } else {
        printf("Accepted connection from %s\n", connectionServerSockFD);
    }


    // 5. send and receive data
    char reciveveMsg[1024];
    memset(reciveveMsg, 0, 1024);

    recv(connectionServerSockFD, reciveveMsg, 1024, 0);

    printf("Received from client: %s\n", reciveveMsg);

    //6 close the scoket
    close(serverSocketFD);
    close(connectionServerSockFD);

    return 0;
}
