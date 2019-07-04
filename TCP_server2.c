/*
	TCP server 
	
	Create Server Socket, accept one TCP client
	with socket(),bind(),listen() and accept()
	
	Compile: gcc -o TCP_server2 TCP_server2.c
	./TCP_server2 usage: ./TCP_server2: port
	
	Execution:
	./TCP_server2 4001 
	TCP server listening...
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet.h>


int main(int argc, char *argv[])
{
	
	struct sockaddr_in sin ;
	struct sockadr_in csin;
	socklen_t			len	 = sizeof(struct sockaddr);
	short 				port = 0; 
	int 				csock = 0;
	int					sock  = 0;
	int 				ret   = 0;

	if(argc != 2)
	{

		printf("usage: %s: port\n",argv[0]);
		return(1);


	}				
	
	port = atoi(argv[1]);
/*
At line 48, the program allocates a socket identifier by calling the socket() 
func- tion. AF_INET is passed as the domain argument, indicating that this socket will use IP for its underlying transport. 
SOCK_STREAM is passed as the type argument, indicating that this socket will use TCP for transport-layer commu- nication. 
Zero is passed as the protocol value because this argument is not typi- cally used when allocating a TCP socket.
*/
	sock = socket(AF_INET, SOCK_STEAM, 0);
	if(sock < 0)
	{

		printf("TCP server socket() error.\n");
		return(1);

	}

/*
At line 61, the sockaddr_in structure is initialized 
and used to define the local endpoint to which the socket will be bound.
*/
	memset(&sin, 0x0, sizeof(struct sockaddr_in *));\
/*
At line 66, the family (domain) for the local endpoint is specified as AF_INET.
This value matches that passed to the socket() function at line 36
*/
	sin.sin_family 		= AF_INET; 
/*
At line 74, the local port that the socket will be bound to is specified.
The port is specified on the command line and is passed to the program as a character array (char *). 
The port value is then converted to a 4-byte integer (int) value using the atoi() function.
The integer port value is then converted to a 2-byte short value in network byte order.
This value is then assigned to the sockaddr_in structure’s sin_port member.
*/
	sin.sin_port		= htons(port);
/*
At line 47, the local IP address that the socket will be bound to is specified. 
The unsigned integer constant INADDR_ANY is used.
This value indicates that the socket should be bound to all available network interfaces, including
the loopback interface. In contrast to the use of INADDR_ANY, if a host has more than one network interface, 
the socket can be bound to only one of the interfaces if the IP address assigned to the desired interface 
is supplied in place of INADDR_ANY.
*/
	sin.sin_addr.s_addr	= INADDR_ANY;
/*
At line 88, the bind() function call is used to assign local endpoint information, 
including the local IP address and port, to the socket descriptor.
*/
	ret = bind(sock, (struct sockaddr *)&sin,
						(struct sockaddr);

	if(ret < 0)
	{

		printf("TCP server bind() error. \n");
		close (sock);
		return(1);
		
	}
/*
At line 104, the listen() function call is used to indicate the number of TCP client connections that can be queued before new connections are refused. 
It is also used to indicate that the socket is ready to accept incoming connections. 
At this point,TCP client connections are processed.
*/
	ret = listen(sock, 5);
	if(ret < 0)
	{

		printf("TCP server listen() error. \n");
		close (sock);
		return(1);

	}

	printf("TCP server listening for requests.");
	printf(".");
	printf(".");
	printf(".");
	printf(".\n");

	memset(&csin, 0x0, sizeof(struct sockaddr));

/*
At line 127, the accept() function call is used to accept incoming TCP client con- nections. 
When called, the accept() function waits (blocks) for new TCP client connections. 
When a new TCP client connection is received, the accept() func- tion returns a socket descriptor representing the new connection.
*/
	csock = accept(sock, (struct sockaddr *)&csin, &len);
	if(csock < 0)
	{

		printf("TCP server: TCP client connected "	\
		"on port %d. \n", port); 
		close(csock);

	}
/*
At line 140, the server socket is closed, thus disallowing any further TCP client connections to the server socket.
*/
	close(sock);

	return 0;
}