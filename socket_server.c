//student_name: ibrahim Elsheikh

/* ***Introduction to socket programming***
--A socket is one endpoint of a communication link between systems.
--Your application sends and receives all of its network data through a socket.
--Your operating system provides you with socket application programming interfaces (APIs) 
  to enable you to develop a networked application.
--Sockets come in two basic types: connection-oriented and connectionless. These terms
  refer to types of protocols.
--The two protocols that are used today are Transmission Control Protocol (TCP) and User
  Datagram Protocol (UDP). TCP is a connection-oriented protocol, and UDP is a
  connectionless protocol.

--In a connectionless protocol, such as UDP, There is no guarantee that a packet will arrive.
--UDP doesn't generally provide a method to know if a packet did not arrive, and UDP does
  not guarantee that the packets will arrive in the same order they were sent.
 
--TCP guarantees that data arrives in the same order it is sent. It prevents duplicate data from
  arriving twice, and it retries sending missing data.

**Network programming is usually done using a client-server paradigm.**
--In this paradigm:
 -A server listens for new connections at a published address. 
 -The client, knowing the server's address, is the one to establish the connection initially.
 -Once the connection is established, the client and the server can both send and receive data. 
 -This can continue until either the client or the server terminates the connection. 
*/
/* In this coding Assignment, you will use Linux sockets (connection-oriented sockets TCP) APIs to 
   implement a client-server program, where the client sends your name to the server, 
   and the server replies with (Hello your_name). Cool ha!!
*/
/* Server:
   1. define an (IP address + port number) for the server
   2. create a socket (server socket)
   3. bind the socket to the address
   4. start listening for connections
   5. accept any incoming connection
   6. send and receive data to and from the client
   7. close the socket
*/

//Follow along the code and Complete the commented parts

//TCP INT =6

//include the needed headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

//define some macros (just for program portability so that it works on windows, but we're only considered with Linux in this Assignment)
#define ISVALIDSOCKET(s) ((s) >= 0)   
#define CLOSESOCKET(s) close(s)  
#define SOCKET int    //A socket descriptor is represented by a standard file descriptor of type int
#define GETSOCKETERRNO() (errno)  //When a socket function has an error,the error number gets stored in the thread-global errno variable.

int main() {
	
	 //figure out the local address that our web server should bind to
	 printf("Configuring local address...\n");
	 struct addrinfo hints;
	 memset(&hints, 0, sizeof(hints));
	 hints.ai_family = AF_INET;
	 hints.ai_socktype = SOCK_STREAM;  //set the value to specify the socket type as TCP
	 hints.ai_flags = AI_PASSIVE;
	 struct addrinfo *bind_address;
	 getaddrinfo("127.0.9.1", "8090", &hints, &bind_address); //port number is 8090, if it's busy on your device change it // host name is 0
                                                    //you will know whether it's busy or not when you run the code	 
	 
	 //create the socket
	 printf("Creating socket...\n");
	 SOCKET socket_listen;
	 socket_listen = /*API_to_create_socket*/socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
	                            //find the missing function name
	 
	 //check that the call to socket() was successful
	 if (!ISVALIDSOCKET(socket_listen)) 
	 {
		 fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
		 return 1;
	 }
	 
	 //call bind() to associate it with our address from getaddrinfo():
	 printf("Binding socket to local address...\n");
	 if (bind(/*socket_variable*/socket_listen ,bind_address->ai_addr, bind_address->ai_addrlen)) //find the missing parameter name
	 {
		 fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
		 return 1;
	 }
	 freeaddrinfo(bind_address);
	 
	 //start listening for connections
	 printf("Listening...\n");
	 if (/*API_to_listen*/listen(/*socket_variable_to_listen_on*/socket_listen, 10) < 0) //find the missing function and parameter names
	 {
		 fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
		 return 1;
	 }

     //accept any incoming connection
     printf("Waiting for connection...\n");
	 struct sockaddr_storage client_address;
	 socklen_t client_len = sizeof(client_address);
	 SOCKET socket_client = /*API_to_accept*/accept(/*socket_variable*/socket_listen,(struct sockaddr*) &client_address, &client_len);
	                                                          //find the missing function and parameter names
	 if (!ISVALIDSOCKET(socket_client)) 
	 {
		 fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
		 return 1;
	 }

     //We read this request using the recv() function
     printf("Reading request...\n");
	 char request[1024];
     recv(socket_client, request, 1024, 0);

	 int bytes_received = strlen(request);

             //use recv() function to receive the incoming packet and save it in the *request* variable defined
	 printf("Received %d bytes.\n", bytes_received);
	 
	 //print the client's request to the console
	 printf("%.*s", bytes_received, request);   
	 
	 //send our response back
	 printf("Sending response...\n");
	 char response[] = "Hello" ;
	 strcat(response,request);
	 int bytes_sent =  send(socket_client, request, strlen(request), 0);
             //use send() function to send the *response* back to the client
	 printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));
	 
	 
	 //close the client connection
	 printf("Closing connection...\n");
	 CLOSESOCKET(socket_client);
	 
	 //close the listening socket too
	 printf("Closing listening socket...\n");
     CLOSESOCKET(socket_listen);
			 
	 printf("Finished.\n");
     return 0;
}
