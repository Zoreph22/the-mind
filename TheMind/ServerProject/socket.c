#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include "socket.h"

#define FATAL_ERR(msg) perror(msg); socket_close(); exit(errno);
#define SOCKET int

/// Port du serveur.
#define SERVER_PORT 25565
/// Nombre maximal de connexions au socket.
#define MAX_CONNECTIONS 2
/// Taille maximale d'un message.
#define MAX_MSG_SIZE 1024

/// Structure stockant les informations de la connexion d'un client.
struct ClientCon
{
	/// Descripteur du socket.
	SOCKET fd;
	/// Socket ouvert ?
	bool isOpened;
	/// Adresse IP et port.
	struct sockaddr_in address;
	/// Thread associé à la connexion et gérant la communication de ce client.
	pthread_t threadId;
};

/// Liste des connexions ouvertes (identifiant d'un client = index dans la liste).
struct ClientCon cliSockets[MAX_CONNECTIONS];
/// Nombre de clients connectés.
unsigned int nbConnections = 0;

/// Descripteur de socket du serveur.
SOCKET srvSocket;
/// Socket du serveur est-il ouvert ?
bool isSocketOpened = false;

/**
 * @brief [Thread] Écouter les messages d'un client et appeler le bon gestionnaire selon le message reçu.
 * @param ptrClientId Identifiant client.
*/
void* listenMessages(void* ptrClientId)
{
	unsigned int clientId = *(unsigned int*)ptrClientId;

	char msg[MAX_MSG_SIZE];
	int nbRead = 0;

	while (cliSockets[clientId].isOpened)
	{
		bzero(msg, sizeof msg);

		if ((nbRead = recv(cliSockets[clientId].fd, msg, sizeof msg - 1, 0)) == -1)
		{
			FATAL_ERR("recv()");
		}

		printf("Message received from client id %i (%i bytes): %s.\n", clientId, nbRead, msg);

		socket_send(clientId, "Hey merci !", 12);
	}

	printf("Stopped communication with client id %i.\n", clientId);
}

/**
 * @brief Écouter les demandes de connexion et les accepter si possible.
*/
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

void socket_broadcast(const char* msg, size_t size)
{
	if (size > MAX_MSG_SIZE)
	{
		fprintf(stderr, "Could not broadcast message as the size %lu exceed the max. size %i.\n", size, MAX_MSG_SIZE);
		return;
	}

	for (unsigned int i = 0; i < nbConnections; i++)
	{
		if (send(cliSockets[i].fd, msg, size, 0) == -1)
		{
			FATAL_ERR("broadcastMessage - send()");
		}
	}

	printf("Broadcasted message (%lu bytes): \"%s\".\n", size, msg);
}

void socket_send(unsigned int clientId, const char* msg, size_t size)
{
	if (size > MAX_MSG_SIZE)
	{
		fprintf(stderr, "Could not send message to client id %i as the size %lu exceed the max. size %i.\n", clientId, size, MAX_MSG_SIZE);
		return;
	}

	if (clientId >= nbConnections)
	{
		fprintf(stderr, "Could not send message as client id %i does not exist.\n", clientId);
		return;
	}

	if (send(cliSockets[clientId].fd, msg, size, 0) == -1)
	{
		FATAL_ERR("sendMessage - send()");
	}

	printf("Sent message to client id %i (%lu bytes): %s.\n", clientId, size, msg);
}

void socket_close()
{
	printf("Closing server...\n");

	for (unsigned int i = 0; i < nbConnections; i++)
	{
		cliSockets[i].isOpened = false;

		pthread_cancel(cliSockets[i].threadId); // TODO : attention, il faut que cette fonction soit appelée dans le main thread.
		pthread_join(cliSockets[i].threadId, NULL);

		close(cliSockets[i].fd);
	}

	isSocketOpened = false;
	close(srvSocket);

	printf("Server closed.\n");
}

void socket_open()
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