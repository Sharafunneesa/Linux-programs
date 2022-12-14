/* client program using TCP(transmission control protocol) protocol*/


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
	if( argc < 2)
	{ 
		printf("usage: give port number\n");
		exit(0);
	}

	
	//taking the local ip address
	char *ip = "127.0.0.1";

	
	//taking the port number from command line argument
	int port = atoi(argv[1]);


	
	//declairing all the needed sockets, structure and variables
	int client_sock;
	struct sockaddr_in client_addr;
	char buffer[1024];
	socklen_t addr_size;
	int n;

	
	//creating the client socket and checking it created or not
	client_sock = socket(AF_INET, SOCK_STREAM,0);
	if(client_sock < 0)
	{
		perror("socket error");
		exit(1);
	} 


	//using memset we are filling the client socket with null value
	memset(&client_addr, '\0', sizeof(client_addr));


	// ip address from internet (version 4)
	client_addr.sin_family = AF_INET;
	// port we are assigning
	client_addr.sin_port = port;
	//assiging the ip address
	client_addr.sin_addr.s_addr = inet_addr(ip);


	//connecting the clinet socket with server 
	connect(client_sock,(struct sockaddr*)&client_addr,sizeof(client_addr));
	printf("connected to the server\n");

	
	//using bzero clear the buffer
	bzero(buffer, sizeof(buffer));

	
	//copy the message to buffer and printing the usage message
	strcpy(buffer, argv[2]);
	printf("client send the message\n");

	
	//sending the message to server
	send(client_sock,buffer,strlen(buffer),0);

	
	//again clear the buffer
	bzero(buffer,sizeof(buffer));

	
	//recieving the message send by the server and printing
	recv(client_sock,buffer,sizeof(buffer),0);
	printf("server sended message is :%s\n",buffer);

	
	//disconnecting from the server
	close(client_sock);
	printf("disconnected from the server\n");


	return 0;
}  




