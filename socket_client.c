//student_name: ibrahim esmail elsheikh

/* Client:
   1. define an (IP address + port number) for the server to connect to
   2. create a socket (client socket)
   3. establish a connection to the server
   4. send and receive data to and from the server
   5. close the socket
*/

//include the needed headers
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
A
//define some macros
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

int main() {

    //set the following
    const char *server_hostname = "127.0.9.1";  //with loopback ip address
    const char *server_portnum = "8090";   //with the port number we set for the server

    //configure a remote address for connection
    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;   //set the value to specify the socket type as TCP
    struct addrinfo *peer_address;
    if (getaddrinfo(server_hostname, server_portnum, &hints, &peer_address)) {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    //create client socket
    printf("Creating socket...\n");
    SOCKET socket_peer;
    socket_peer = /*API_to_create_socket*/socket(peer_address->ai_family, peer_address->ai_socktype, peer_address->ai_protocol);
                //find the missing function name

    if (!ISVALIDSOCKET(socket_peer)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    //Establish a connection to the remote server
    printf("Connecting...\n");
    if (/*API_to_connect*/connect(socket_peer , peer_address->ai_addr, peer_address->ai_addrlen)) {
        //find the missing function and parameter names
        fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(peer_address);

    printf("Connected.\n");

    //send request to server
    printf("Sending request...\n");
    const char *request = "Ibrahim Esmail Elsheikh\n";  //send your own full name to the server
    int bytes_sent=  send(socket_peer, request, strlen(request), 0);
                              //use send() function to send the *request* to the server
    printf("Sent %d of %d bytes.\n", bytes_sent, (int) strlen(request));


    //receive response (data) from server
    char read[1024];
    recv(socket_peer, read, 1024, 0);
    int bytes_received = strlen(read);
    if (bytes_received < 1) {
        printf("Connection closed by peer.\n");
    }
    printf("Received (%d bytes): %.*s", bytes_received, bytes_received, read);


    //close the client connection

    printf("Closing socket...\n");
    CLOSESOCKET(socket_peer);

    printf("Finished.\n");
    return 0;
}

