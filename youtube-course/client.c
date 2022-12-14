#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    // create client socket
    int socket_peer = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_peer != -1) {
        printf("Client Socket ID: %d\n", socket_peer);

    } else {
        printf("Faild to create socket\n");
        exit(1);
    }

    // connect to client to a specific server
    struct sockaddr_in hints;
    memset(&hints, 0, sizeof(hints));

    hints.sin_family = AF_INET;
    hints.sin_addr.s_addr = inet_addr("127.0.0.1");
    hints.sin_port = htons(8090);

    if (connect(socket_peer, (struct socketaddr *) &hints, sizeof(hints)) == 0) {
        printf("Connected to server\n");
    } else {
        printf("Faild to connect to server\n");
        exit(1);
    }

    // send data to server
    char read[1024] = "Ibrahim Elsheikh\n";
    send(socket_peer, read, strlen(read), 0);

    // receive data from server
    memset(read, 0, 1024);
    recv(socket_peer, read, 1024, 0);
    printf("Received from server: %s\n", read);

    // close socket
    close(socket_peer);

    return 0;
}
