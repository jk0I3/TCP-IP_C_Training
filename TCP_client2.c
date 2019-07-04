/*
 *
 * TCP client connect/close
 * connect(), close() functions
 *
 * COMPILATION: gcc -o TCP_client2 TCP_client2.c ...
 * 
 */

 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>


 int
 main	(int argc, char *argv[])
 {

 		struct sockaddr_in sin; 
 		int sock = 0; 
 int ret = 0; 

 			if(argc != 3)
 	{

 		printf("usage: %s: ip_address port\n", argv[0]);
 		return(1);

 	}
	/* 
		allocate socket identifier, pass AF_INET as domain arg (IP) for transport
 		SOCK_STREAM is passed as type arg indicating TCP as transport
 		0 is passed as protocol value.
 	*/
 	sock = socket(AF_INET, SOCK_STREAM, 0);
 	if(sock < 0)
 	{

 		printf("TCP client socket() connection failed.. \n");
 		return(1);

 	}

 	/*
 	* sockaddr_in init to define remote endpoint to connect to
 	*/

 	memset(&sin, 0x0, sizeof(struct sockaddr_in *));
 	
 	/* family (domain) is set as AF_INET, values matched passed to socket() line 28 */

 	sin.sin_family = AF_INET; 

 	/* port value to socket specified, port value converted with atoi function 
	   integer port value converted to 2 byte short value.
	   then assigned to the sockaddr_in struct's sin_port member
	*/
 	sin.sin_port = htons(atoi(argv[2]));

 	/*
 		remote IP address for socket connection specified via cmd
 		and passed as char array. String value converted to 32 bit.
 		inet_addr() function converts char array to 32 bit. 
 		value assigned to struc sockaddr_in's sin.addr.s_addr
 	*/

	sin.sin_addr.s_addr = inet_addr(argv[1]);

	/*
		socket connected to remote host and port.
		Three way handshake takes place
	*/

 	ret = connect(sock, struct sockaddr *)&sin
 					sizeof(struct sockaddr);


 	if(ret < 0)
 	{

 			print("TCP client connect() error! \n");
 			close (sock);
 			return(1);

 	}

 	/* Close connection */
 	printf("%s\n","TCP client is connected!(.)_(.)" );
 	close(sock);

 	printf("TCP client connection is terminated. \n"); 


 	return(0);

 }