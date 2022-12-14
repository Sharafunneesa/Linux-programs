/* server program using TCP(transmission control protocol) protocol*/

//including all header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


//driving code
int main(int argc,char *argv[])
{  
	//checking the given arguments and printing the usage message
	if( argc < 3)
	{ 
		printf("usage: give port number and print the message\n");
		exit(0);
	}

	//taking the local ip address
	char *ip = "127.0.0.1";

	//taking the port number by argument
	int port = atoi(argv[1]);


	//declairing all the needed sockets, structure and variables 
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024];
	socklen_t addr_size;
	int n;


	//creating the server socket and checking it created or not
	server_sock = socket(AF_INET, SOCK_STREAM,0);
	if(server_sock < 0)
	{
		perror("socket error");
		exit(1);
	} 


	//using memset we are filling the server socket with null value
	memset(&server_addr, '\0', sizeof(server_addr));


	// ip address from internet (version 4)
	server_addr.sin_family = AF_INET;
	// port we are assigning
	server_addr.sin_port = port;
	//assiging the ip address
	server_addr.sin_addr.s_addr = inet_addr(ip);



	//binding the server adress to the port number and checking its done or not
	n = bind(server_sock,(struct sockaddr*)&server_addr, sizeof(server_addr));
	if(n < 0)
	{   
		perror("bind error");
		exit(1);
	}
	printf("Bind the port number :%d\n",port);


	//listen for the client using listen command for 5 client
	listen(server_sock, 5);
	printf("listening..\n");


	//taking while loop for infinite writing
	while(1)
	{


		//taking the size of client address  
		addr_size = sizeof(client_addr);

		//accept the client connection     
		client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);
		printf("client connected\n");

		//using bzero clear the buffer
		bzero(buffer,1024);

		//receiving the message from client and printing
		recv(client_sock,buffer,sizeof(buffer),0);
		printf("client sended message is :%s\n",buffer);

		//again clearing the buffer
		bzero(buffer, 1024);

		//write a message to buffer to send back
		strcpy(buffer, argv[2]);
		printf("server send the message back\n");

		//sending the message back to client
		send(client_sock,buffer,strlen(buffer),0);

		//closing the client socket
		close(client_sock);
		printf("client disconnected\n");

	}

	return 0;
}

