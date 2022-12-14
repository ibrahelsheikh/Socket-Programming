#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    // create a socket
    int clinetSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (clinetSocketFD != -1) {
        printf("Client Socket ID: %d\n", clinetSocketFD);

    } else {
        printf("Faild to create socket\n");
        exit(1);
    }

    // connect to client to a specific server
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(2000);

    if (connect(clinetSocketFD, (struct socketaddr *) &serverAddress, sizeof(serverAddress)) == 0) {
        printf("Connected to server\n");
    } else {
        printf("Faild to connect to server\n");
        exit(1);
    }

    // send data to server
    char buffer[1024] = "Ibrahim Elsheikh\n";
    send(clinetSocketFD, buffer, strlen(buffer), 0);

    // receive data from server
    memset(buffer, 0, 1024);
    recv(clinetSocketFD, buffer, 1024, 0);
    printf("Received from server: %s\n", buffer);

    return 0;
}
