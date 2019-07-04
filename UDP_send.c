/*
	
	UDP_send.c builds on the socket code in UDP_socket.c, 
	and how to declare and initialize the sockaddr_in structure 
	as well as how to send a UDP datagram using the send() function.
	
	compilation: gcc -o UDP_send UDP_send.c
*/

#include <stdio.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
/*
	arpa/inet.h is added.This header file includes 
	function prototypes for various conversion functions used 
	for processing of IPv4 addresses in string “dot” notation 
	and unsigned integer format.
*/
#include <arpa/inet.h>
/*
	DST_ADDR/PORT are declared using pre-compiler defines.
	These values will be used to define the endpoint that 
	UDP datagrams should be sent to.
*/
#define UDP2_DST_ADDR "127.0.0.1" 
#define UDP2_DST_PORT 1234

int
main(void)
{

/*
	local variables to be used by the program are declared. 
	The variable sin of type struct sockaddr_in will be used to define the destination 
	IP address and the port that the datagrams should be sent to
*/
	struct sockaddr_in sin; char buf[100];
	int sock = 0;
	int ret =0;
/*
	UDP socket is created using the socket() function
*/
	sock = socket(AF_INET, SOCK_DGRAM, 0); 
	if(sock < 0)
	{
	
	printf("socket() failed.\n"); return(1);
	
	}

memset(&sin, 0x0, sizeof(sin));
/*
	sin_family member is set to match the AF_INET socket address family.
	his value is always assigned to the sin_family member when imple- menting UDP socket support
*/
sin.sin_family = AF_INET;

/*
	sin_port member is set to the remote port that the UDP data- grams should be delivered to.
	The port value is passed to the htons() function before being assigned to the sin_port member.
	The htons() function provides a portable means for ensuring that the port value is specified in network byte order. 
	On computer systems that use little-endian byte ordering, the bytes that make up the port value are rearranged into network-byte order. 
	On computer systems that use big-endian byte ordering, no change is required as big-endian and network-byte order are the same.
*/
sin.sin_port = htons(UDP2_DST_PORT); 

/*

 the target IP address in string “dot” notation is converted to an unsigned integer 
 format using the inet_addr() function and assigned to the sin_addr.s_addr member 
 of the sockaddr_in structure. When sending data, this value indicates the IP address 
 that the UDP datagram should be sent to.The inet_addr() function converts string in “dot” notation such as 127.0.0.1 to a 4- byte unsigned integer format in network-byte order. If the address string

*/                                       

sin.sin_addr.s_addr = inet_addr(UDP2_DST_ADDR);

/*

connect() function is used to associate the parameters stored in the sin sockaddr_in structure with the socket,
and to set the state of the socket to connected. Upon successful return from the connect() function call, 
data may be sent to or received from the socket until an error occurs or the socket is closed with the close() function.
The connect() will return a negative integer value to indicate an error condition.

*/
ret = connect(sock, (struct sockaddr *) &sin, sizeof(sin));

if(ret < 0) {
	printf("connect() failed.\n"); return(1);
}
/*
	100-byte buffer is initialized with the A character.
	This is the data that will be sent via the socket to the target IP address and port.
*/

memset(buf, 'A', 100);

/*
	the send() function is used to send data.The first parameter to the send function is a socket descriptor
	that has been successfully passed to the con- nect() function.The second parameter is a pointer to a character 
	buffer con- taining the data to be sent.The third parameter is the size in bytes of the character buffer.
	The fourth parameter may contain flag values, but is not used in this example.
	The send() function returns the number of bytes sent on suc- cess or a negative integer value to indicate an error condition
*/
ret = send(sock, buf, 100, 0); 
if(ret != 100)
	{
	printf("send() failed.\n"); return(1);
	}
/*
	 socket descriptor is closed using the close() function call
*/
close (sock); printf("send() success.\n");

return(0);

}