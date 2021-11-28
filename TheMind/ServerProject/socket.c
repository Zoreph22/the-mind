#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/un.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sds/sds.h>
#include "socket.h"

#define FATAL_ERR(msg) perror(msg); closeServer(); exit(errno);

#define SOCKET int
/// Nombre maximal de connexions au socket.
#define MAX_CONNECTIONS 2
#define MAX_RECV_SIZE 1024
#define SERVER_PORT 25565

/// Nombre de clients connectés.
unsigned int nbConnections = 0;

struct ClientCon
{
	SOCKET fd;
	struct sockaddr_in address;
	pthread_t threadId;
	bool isOpened;
};

struct ClientCon cliSockets[MAX_CONNECTIONS];

SOCKET srvSocket;

/// Le socket est-il ouvert ?
bool isSocketOpened = false;

void* listenMessages(void* ptrClientId)
{
	unsigned int clientId = *(unsigned int*)ptrClientId;

	char msg[MAX_RECV_SIZE];
	int nbRead = 0;

	while (cliSockets[clientId].isOpened)
	{
		bzero(msg, sizeof msg);

		if ((nbRead = recv(cliSockets[clientId].fd, msg, sizeof msg - 1, 0)) == -1)
		{
			perror("recv()");
			continue;
		}

		printf("Message received from client id %i (%i bytes): %s.\n", clientId, nbRead, msg);

		sendMessage(clientId, "Hey merci !", 12);
	}

	printf("Stopped communication with client id %i.\n", clientId);
}

void listenConnections()
{
	printf("Listening for client connections (max. %i)...\n", MAX_CONNECTIONS);

	while (nbConnections < MAX_CONNECTIONS)
	{
		SOCKET cliSocket;
		struct sockaddr_in cliAddress;
		unsigned int cliAddressSize = sizeof cliAddress;

		/// Écouter et accepter une demande de connexion.
		cliSocket = accept(srvSocket, (struct sockaddr*)&cliAddress, &cliAddressSize);

		if (cliSocket == -1)
		{
			FATAL_ERR("Error while listening client connections");
		}

		nbConnections++;

		// Sauvegarder les informations du client.
		unsigned int clientId = nbConnections - 1;
		cliSockets[clientId].fd = cliSocket;
		cliSockets[clientId].address = cliAddress;
		cliSockets[clientId].isOpened = true;


		// Création du thread gérant la communication de ce client.
		if (pthread_create(&cliSockets[clientId].threadId, NULL, &listenMessages, &clientId) == -1)
		{
			FATAL_ERR("listenMessages - thread_create()");
		}

		printf("Connection from %s accepted.\n", inet_ntoa(cliAddress.sin_addr));
	}

	printf("Stopped listening client connections. Total of clients connected: %i.\n", nbConnections);
}

void broadcastMessage(const char* msg, size_t size)
{
	for (unsigned int i = 0; i < nbConnections; i++)
	{
		if (send(cliSockets[i].fd, msg, size, 0) == -1)
		{
			perror("send()");
		}
	}

	printf("Broadcasted message (%lu bytes): \"%s\".\n", size, msg);
}

void sendMessage(unsigned int clientId, const char* msg, size_t size)
{
	if (clientId >= nbConnections)
	{
		fprintf(stderr, "Could not send message as client id %i does not exist.\n", clientId);
		return;
	}

	if (send(cliSockets[clientId].fd, msg, size, 0) == -1)
	{
		perror("send()");
		return;
	}

	printf("Sent message to client id %i (%lu bytes): %s.\n", clientId, size, msg);
}

void closeServer()
{
	printf("Closing server...\n");

	for (unsigned int i = 0; i < nbConnections; i++)
	{
		cliSockets[i].isOpened = false;
		close(cliSockets[i].fd);
	}

	isSocketOpened = false;
	close(srvSocket);
}

void startServer()
{
	printf("Starting server...\n");

	// Création du socket.
	srvSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (srvSocket == -1)
	{
		FATAL_ERR("bind()");
	}

	// Création de l'interface
	// et attribution de celle-ci au socket créé.
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(SERVER_PORT);

	if (bind(srvSocket, (struct sockaddr*)&address, sizeof address) == -1)
	{
		FATAL_ERR("bind()");
	}

	isSocketOpened = true;

	// Attendre et accepter les demandes de connexion.
	if (listen(srvSocket, MAX_CONNECTIONS) == -1)
	{
		FATAL_ERR("bind()");
	}

	listenConnections();

	while (isSocketOpened);
}