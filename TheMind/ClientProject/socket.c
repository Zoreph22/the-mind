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
#include "messaging/srv_handlers.h"
#include "socket.h"

#define FATAL_ERR(msg) perror(msg); socket_disconnect(); exit(errno);

/// Descripteur du socket.
SOCKET cliSocket;
/// Socket est-il ouvert ?
bool isOpened = false;

/**
 * @brief [Thread] Écouter les messages du serveur et appeler le bon gestionnaire selon le message reçu.
*/
void* listenMessages(void* unused)
{
	while (isOpened)
	{
		struct MsgHeader header;
		char data[MAX_MSG_SIZE];

		// Lecture en-tête message : taille contenu du message & type du message.
		if (recvn(cliSocket, &header, sizeof(header)) == -1)
		{
			FATAL_ERR("recvn()");
		};

		// Lecture contenu message.
		if (recvn(cliSocket, data, header.dataLen) == -1)
		{
			FATAL_ERR("recvn()");
		};

		// Appel du gestionnaire correspondant au type du message.
		srvMsgHandler[header.msgType](data);

		printf("Message received (type %i) (%lu bytes).\n", header.msgType, header.dataLen + sizeof(header));
	}

	printf("Stopped communication with the server.\n");
}

void socket_send(enum CliMsg type, const void* msg, size_t size)
{
	struct MsgHeader header = { size, type };

	// Envoyer l'en-tête du message.
	if (sendn(cliSocket, &header, sizeof(header)) == -1)
	{
		FATAL_ERR("sendn()");
	};

	// Envoyer le contenu du message.
	if (sendn(cliSocket, msg, size) == -1)
	{
		FATAL_ERR("sendn()");
	};

	printf("Sent message (type %i) (%li bytes).\n", header.msgType, header.dataLen + sizeof(header));
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

	printf("Connected to the server.\n");

	// Démarrer l'écoute des messages reçus.
	pthread_t threadId;
	if (pthread_create(&threadId, NULL, &listenMessages, NULL) == -1)
	{
		FATAL_ERR("listenMessages - pthread_create()");
	}

	/*socket_send(CLI_MSG_NONE, NULL, 0);
	//sleep(1);

	struct CliMsg_SetName clsn = { "Kévin" };
	socket_send(CLI_MSG_SET_NAME, &clsn, sizeof clsn);
	//sleep(1);

	socket_send(CLI_MSG_SET_READY, NULL, 0);
	//sleep(1);

	struct CliMsg_SetNumBot cmsnb = { 5 };
	socket_send(CLI_MSG_SET_NUM_BOT, &cmsnb, sizeof cmsnb);
	//sleep(1);

	struct CliMsg_PlayCard cmpc = { 1 };
	socket_send(CLI_MSG_PLAY_CARD, &cmpc, sizeof cmpc);
	//sleep(1);

	socket_send(CLI_MSG_REPLAY_GAME, NULL, 0);
	//sleep(1);

	socket_send(CLI_MSG_MAX, NULL, 0);
	//sleep(1);*/

	while (isOpened);
}

void socket_disconnect()
{
	isOpened = false;
	close(cliSocket);

	printf("Disconnected from the server.\n");
}