#include <stdio.h>
#include "socket.h"
#include <string.h>
#include "Logic/partie.h"
#include "Logic/lobby.h"
#include "messaging/cli_handlers.h"

void CliMsg_NoneHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_NONE - Client: %i - Unhandled message.\n", senderId);
}

void CliMsg_SetNameHandler(unsigned int senderId, void* data)
{
	struct CliMsg_SetName* msg = (struct CliMsg_SetName*)data;
	printf("Message Handler: CLI_MSG_SET_NAME - Client: %i - New name: %s.\n", senderId, msg->name);

	setPlayerName(senderId, msg->name);
	addPlayerToLobby(senderId);

	struct SrvMsg_PlayerInfo msgData1 = {.playerId = senderId};
	socket_send(senderId, SRV_MSG_PLAYER_INFO, &msgData1, sizeof(msgData1));

	struct SrvMsg_PlayerConnected msgData2 = {0};
	strcpy(msgData2.name, msg->name);
	msgData2.playerId = senderId;
	socket_broadcast(SRV_MSG_PLAYER_CONNECTED, &msgData2, sizeof(msgData2));

	for (int i = 0; i < l.nbJoueurs; i++) {
		struct SrvMsg_PlayerConnected msgData3 = { 0 };
		strcpy(msgData3.name, l.joueurs[i].nom);
		msgData3.playerId = i;
		socket_send(senderId, SRV_MSG_PLAYER_CONNECTED, &msgData3, sizeof(msgData3));

		struct SrvMsg_InfoLobby msgData4 = { .botCount = l.nbBots, .roundCount = l.nbManches, .readyCount = l.nbPrets };
		socket_send(senderId, SRV_MSG_INFO_LOBBY, &msgData4, sizeof(msgData4));
	}
}

void CliMsg_SetReadyHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_SET_READY - Client: %i - Is now ready to play.\n", senderId);

	setReady(senderId);

	struct SrvMsg_InfoLobby msgData = { .botCount = l.nbBots, .roundCount = l.nbManches, .readyCount = l.nbPrets};
	socket_broadcast(SRV_MSG_INFO_LOBBY, &msgData, sizeof(msgData));
}

void CliMsg_SetNumBotHandler(unsigned int senderId, void* data)
{
	struct CliMsg_SetNumBot* msg = (struct CliMsg_SetNumBot*)data;
	printf("Message Handler: CLI_MSG_SET_NUM_BOT - Client: %i - New bot count: %i.\n", senderId, msg->botCount);

	setNumBot(msg->botCount);

	struct SrvMsg_InfoLobby msgData = { .botCount = l.nbBots, .roundCount = l.nbManches, .readyCount = l.nbPrets };
	socket_broadcast(SRV_MSG_INFO_LOBBY, &msgData, sizeof(msgData));
}

void CliMsg_PlayCardHandler(unsigned int senderId, void* data)
{
	struct CliMsg_PlayCard* msg = (struct CliMsg_PlayCard*)data;
	printf("Message Handler: CLI_MSG_PLAY_CARD - Client: %i - Play card index: %i.\n", senderId, msg->cardIndex);

	int numCarte = p.joueurs[senderId].cartes[msg->cardIndex];
	bool continuer = gestionCarteJouer(senderId, msg->cardIndex);

	if (continuer) {
		struct SrvMsg_CardPlayed msgData = {.playerId =senderId, .cardNumber = numCarte };
		socket_broadcast(SRV_MSG_CARD_PLAYED, &msgData, sizeof(msgData));
	}
}

void CliMsg_ReplayGameHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_REPLAY_GAME - Client: %i - Want to replay a game.\n", senderId);

	startGame();
}

void CliMsg_MaxHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_MAX - Client: %i - Unhandled message.\n", senderId);
}