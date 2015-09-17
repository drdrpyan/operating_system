#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 6052

int main()
{
	int serverSocket;
	int client_socket;
	int clientAddrSize;

	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;

	char rcvBuffer[1024];
	char sndBuffer[1024];

	//socket
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1)
	{
		perror("fail to create server socket");
		exit(1);
	}
	//bind
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(servaerAddr)) == -1)
	{
		perror("fail to bind socket");
		exit(1);
	}
	//listen
	if(listen(serverSocket, 5) == -1)
	{
		perror("fail to listen");
		exit(1);
	}
	return 0;
}
