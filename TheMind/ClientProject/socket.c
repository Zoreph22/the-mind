#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/un.h>
#include "socket.h"
#include <sds/sds.h>

#define FATAL_ERR(msg) perror(msg); disconnect(); exit(errno);

#define MAX_RECV_SIZE 1024

#define SOCKET int

SOCKET cliSocket;

bool isOpened = false;

void* listenMessages(void* unused)
{
	char msg[MAX_RECV_SIZE];
	int nbRead = 0;

	while (isOpened)
	{
		bzero(msg, sizeof msg);

		if ((nbRead = recv(cliSocket, msg, sizeof msg - 1, 0)) == -1)
		{
			perror("recv()");
			continue;
		}

		printf("Message received (%i bytes): %s.\n", nbRead, msg);
	}

	printf("Stopped communication with the server.\n");
}

void sendMessage(const char* msg, size_t size)
{
	if (send(cliSocket, msg, size, 0) == -1)
	{
		FATAL_ERR("send()");
	}

	printf("Sent message (%li bytes): %s.\n", size, msg);
}

void connectTo(const char* ip, unsigned short port)
{
	printf("Connecting to the server...\n");

	// Création du socket.
	cliSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (cliSocket == -1)
	{
		FATAL_ERR("socket()");
	}

	// Spécifier l'adresse IP et le port du serveur.
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	if (inet_aton(ip, &sin.sin_addr) == -1)
	{
		FATAL_ERR("inet_aton()");
	}

	// Connexion au serveur.
	if (connect(cliSocket, (struct sockaddr*)&sin, sizeof sin) == -1)
	{
		FATAL_ERR("connect()");
	}

	isOpened = true;

	// Démarrer l'écoute des messages reçus.
	pthread_t threadId;
	if (pthread_create(&threadId, NULL, &listenMessages, NULL) == -1)
	{
		FATAL_ERR("listenMessages - pthread_create()");
	}

	while (isOpened);
}

void disconnect()
{
	isOpened = false;
	close(cliSocket);

	printf("Disconnected from the server.\n");
}