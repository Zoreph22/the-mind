#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include "socket.h"

#define FATAL_ERR(msg) perror(msg); socket_disconnect(); exit(errno);
#define SOCKET int

/// Taille maximale d'un message.
#define MAX_MSG_SIZE 1024

/// Description du socket.
SOCKET cliSocket;
/// Socket est-il ouvert ?
bool isOpened = false;

/**
 * @brief [Thread] Écouter les messages du serveur et appeler le bon gestionnaire selon le message reçu.
*/
void* listenMessages(void* unused)
{
	char msg[MAX_MSG_SIZE];
	int nbRead = 0;

	while (isOpened)
	{
		bzero(msg, sizeof msg);

		if ((nbRead = recv(cliSocket, msg, sizeof msg - 1, 0)) == -1)
		{
			FATAL_ERR("recv()");
		}

		printf("Message received (%i bytes): %s.\n", nbRead, msg);
	}

	printf("Stopped communication with the server.\n");
}

void socket_send(const char* msg, size_t size)
{
	if (size > MAX_MSG_SIZE)
	{
		fprintf(stderr, "Could not send message as the size %lu exceed the max. size %i.\n", size, MAX_MSG_SIZE);
		return;
	}

	if (send(cliSocket, msg, size, 0) == -1)
	{
		FATAL_ERR("send()");
	}

	printf("Sent message (%li bytes): %s.\n", size, msg);
}

void socket_connect(const char* ip, unsigned short port)
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

	socket_send("Coucou le serveur !", 20);

	while (isOpened);
}

void socket_disconnect()
{
	isOpened = false;
	close(cliSocket);

	printf("Disconnected from the server.\n");
}