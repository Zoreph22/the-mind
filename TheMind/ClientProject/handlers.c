#include <stdio.h>
#include "messaging/srv_handlers.h"
#include "Logic/lobby.h"
#include "Logic/partie.h"
#include "Logic/joueur.h"
#include "input.h"
#include "utils.h"

void SrvMsg_NoneHandler(void* data)
{
	pDebug("Message Handler: SRV_MSG_NONE - Unhandled message.\n");
}

void SrvMsg_InfoLobbyHandler(void* data)
{
	struct SrvMsg_InfoLobby* msg = (struct SrvMsg_InfoLobby*)data;
	pDebug("Message Handler: SRV_MSG_INFO_LOBBY - Round count: %i - Bot count: %i - Ready count: %i.\n", msg->roundCount, msg->botCount, msg->readyCount);

	setInfoLobby(msg->roundCount, msg->botCount, msg->readyCount);
	printLobby();
}

void SrvMsg_PlayerConnectedHandler(void* data)
{
	struct SrvMsg_PlayerConnected* msg = (struct SrvMsg_PlayerConnected*)data;
	pDebug("Message Handler: SRV_MSG_PLAYER_CONNECTED - Player id: %i - Player name: %s.\n", msg->playerId, msg->name);

	if (msg->playerId == (unsigned int) j.id)
	{
		return;
	}

	addPlayerToLobby(msg->playerId, msg->name);
	printLobby();
}

void SrvMsg_CardPlayedHandler(void* data)
{
	struct SrvMsg_CardPlayed* msg = (struct SrvMsg_CardPlayed*)data;
	pDebug("Message Handler: SRV_MSG_CARD_PLAYED - Player id: %i - Card number: %i.\n", msg->playerId, msg->cardNumber);

	setCartePose(msg->cardNumber, msg->playerId);
	printManche();
	setInputCallback(&gestionInputCarteJouer);
}

void SrvMsg_NextRoundHandler(void* data)
{
	struct SrvMsg_NextRound* msg = (struct SrvMsg_NextRound*)data;

	pDebug("Message Handler: SRV_MSG_NEXT_ROUND - Round number: %i - Remaining life: %i - Is the last round won: %i - Player cards:", msg->roundNumber, msg->lifeRemaining, msg->isLastRoundWon);
	for (unsigned int i = 0; i < msg->roundNumber; i++) pDebug(" [%i] = %i", i, msg->playerCards[i]);
	pDebug(".\n");

	l.inLobby = false;
	setNextRound(msg->roundNumber, msg->lifeRemaining, msg->isLastRoundWon);
	distribuerCartes((int *) msg->playerCards);
	printManche();
	setInputCallback(&gestionInputCarteJouer);
}

void SrvMsg_GameEndHandler(void* data)
{
	struct SrvMsg_GameEnd* msg = (struct SrvMsg_GameEnd*)data;
	pDebug("Message Handler: SRV_MSG_GAME_END - Is game won: %i.\n", msg->isGameWon);

	setInputCallback(&gestionInputFinPartie);
	finPartie();
}

void SrvMsg_PlayerInfo(void* data)
{
	struct SrvMsg_PlayerInfo* msg = (struct SrvMsg_PlayerInfo*)data;
	pDebug("Message Handler: SRV_MSG_PLAYER_INFO - Player id: %i.\n", msg->playerId);

	setId(msg->playerId);
	initLobby();

	setInputCallback(&gestionInputLobby);
	printLobby();
}

void SrvMsg_DisconnectAll(void* data)
{
	pDebug("Message Handler: SRV_MSG_DISCONNECT_ALL - Disconnected from the server.\n");

	socket_disconnect();
	printfc(TERM_YELLOW, "Déconnecté du serveur. Vous pouvez fermer le jeu.\n");
}

void SrvMsg_MaxHandler(void* data)
{
	pDebug("Message Handler: SRV_MSG_MAX - Unhandled message.\n");
}