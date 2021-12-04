#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include "socket/consts.h"
#include "socket/utils_io.h"
#include "socket/utils_io.h"
#include "messaging/cli_handlers.h"
#include "socket.h"

#define FATAL_ERR(msg) perror(msg); socket_close(); exit(errno);

/// Port du serveur.
#define SERVER_PORT 25565
/// Nombre maximal de connexions au socket.
#define MAX_CONNECTIONS 2

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

	while (cliSockets[clientId].isOpened)
	{
		struct MsgHeader header;
		char data[MAX_MSG_SIZE];

		// Lecture en-tête message : taille contenu du message & type du message.
		if (recvn(cliSockets[clientId].fd, &header, sizeof(header)) == -1)
		{
			FATAL_ERR("recvn()");
		};

		// Lecture contenu message.
		if (recvn(cliSockets[clientId].fd, data, header.dataLen) == -1)
		{
			FATAL_ERR("recvn()");
		};

		printf("Message received (type %i) from client id %i (%lu bytes).\n", header.msgType, clientId, header.dataLen + sizeof(header));

		// Appel du gestionnaire correspondant au type du message.
		cliMsgHandler[header.msgType](clientId, data);
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

		/*sleep(1);

		socket_send(clientId, SRV_MSG_NONE, NULL, 0);
		socket_send(clientId, SRV_MSG_MAX, NULL, 0);

		struct SrvMsg_InfoLobby smil = { 5, 6, 7 };
		socket_send(clientId, SRV_MSG_INFO_LOBBY, &smil, sizeof smil);

		struct SrvMsg_PlayerConnected smpc = { 2, "Ducon" };
		socket_send(clientId, SRV_MSG_PLAYER_CONNECTED, &smpc, sizeof smpc);

		struct SrvMsg_CardPlayed smcp = { 2, 256 };
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &smcp, sizeof smcp);

		struct SrvMsg_NextRound smnr = { 2, 3, 1, {22, 33, 44} };
		socket_send(clientId, SRV_MSG_NEXT_ROUND, &smnr, sizeof smnr);

		struct SrvMsg_GameEnd smge = { 1 };
		socket_send(clientId, SRV_MSG_GAME_END, &smge, sizeof smge);*/

		// TEST BOT //
		// round 1
		/*sleep(1);
		struct SrvMsg_NextRound msgData = { 3, 3, 1, {21, 5, 36} };
		socket_send(clientId, SRV_MSG_NEXT_ROUND, &msgData, sizeof(msgData));

		sleep(3);
		struct SrvMsg_CardPlayed msgData2 = { .cardNumber = 5, .playerId = 1 };
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));

		sleep(3);
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));

		sleep(3);
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));

		// round 2
		//sleep(3);
		struct SrvMsg_NextRound msgData3 = { 4, 3, 1, {1, 4, 8, 9} };
		socket_send(clientId, SRV_MSG_NEXT_ROUND, &msgData3, sizeof(msgData3));

		sleep(3);
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));

		sleep(3);
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));

		// round 3
		//sleep(3);
		struct SrvMsg_NextRound msgData4 = { 1, 3, 1, {2} };
		socket_send(clientId, SRV_MSG_NEXT_ROUND, &msgData4, sizeof(msgData4));

		sleep(3);
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));

		sleep(3);
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));

		sleep(3);
		socket_send(clientId, SRV_MSG_CARD_PLAYED, &msgData2, sizeof(msgData2));*/

		/*sleep(1);
		struct SrvMsg_PlayerInfo msgData = { .playerId = 1 };
		socket_send(clientId, SRV_MSG_PLAYER_INFO, &msgData, sizeof(msgData));*/
	}

	printf("Stopped listening client connections. Total of clients connected: %i.\n", nbConnections);
}

void socket_broadcast(enum SrvMsg type, const void* msg, size_t size)
{
	if (size > MAX_MSG_SIZE)
	{
		fprintf(stderr, "Could not broadcast message (type %i) as the size %lu exceed the max. size %i.\n", type, size, MAX_MSG_SIZE);
		return;
	}

	struct MsgHeader header = { size, type };

	for (unsigned int i = 0; i < nbConnections; i++)
	{
		// Envoyer l'en-tête du message.
		if (sendn(cliSockets[i].fd, &header, sizeof(header)) == -1)
		{
			FATAL_ERR("socket_broadcast - sendn()");
		}

		// Envoyer le contenu du message.
		if (sendn(cliSockets[i].fd, msg, size) == -1)
		{
			FATAL_ERR("socket_broadcast - sendn()");
		}
	}

	printf("Broadcasted message (type %i) (%lu bytes).\n", header.msgType, header.dataLen + sizeof(header));
}

void socket_send(unsigned int clientId, enum SrvMsg type, const void* msg, size_t size)
{
	if (size > MAX_MSG_SIZE)
	{
		fprintf(stderr, "Could not send message (type %i) to client id %i as the size %lu exceed the max. size %i.\n", type, clientId, size, MAX_MSG_SIZE);
		return;
	}

	if (clientId >= nbConnections)
	{
		fprintf(stderr, "Could not send message (type %i) as client id %i does not exist.\n", type, clientId);
		return;
	}

	struct MsgHeader header = { size, type };

	// Envoyer l'en-tête du message.
	if (sendn(cliSockets[clientId].fd, &header, sizeof(header)) == -1)
	{
		FATAL_ERR("socket_send - sendn()");
	}

	// Envoyer le contenu du message.
	if (sendn(cliSockets[clientId].fd, msg, size) == -1)
	{
		FATAL_ERR("socket_send - sendn()");
	}

	printf("Sent message to client id %i (type %i) (%lu bytes).\n", clientId, header.msgType, header.dataLen + sizeof(header));
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
		FATAL_ERR("socket()");
	}

	// Autoriser la réutilisation du port pour pouvoir immédiatement réouvrir un serveur,
	// quand un vient d'être fermé.
	int reuseAddr = 1;
	setsockopt(srvSocket, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(int));

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
		FATAL_ERR("listen()");
	}

	listenConnections();

	while (isSocketOpened);
}