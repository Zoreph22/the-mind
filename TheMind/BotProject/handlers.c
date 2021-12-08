#include <stdio.h>
#include "logic.h"
#include "messaging/srv_handlers.h"

void SrvMsg_NoneHandler(void* data)
{
	// printf("[BOT] Message Handler: SRV_MSG_NONE - Unhandled message.\n");
}

void SrvMsg_InfoLobbyHandler(void* data)
{
	// printf("[BOT] Message Handler: SRV_INFO_LOBBY - Unhandled message.\n");
}

void SrvMsg_PlayerConnectedHandler(void* data)
{
	// printf("[BOT] Message Handler: SRV_PLAYER_CONNECTED - Unhandled message.\n");
}

void SrvMsg_CardPlayedHandler(void* data)
{
	struct SrvMsg_CardPlayed* msg = (struct SrvMsg_CardPlayed*)data;
	printf("[BOT] Message Handler: SRV_MSG_CARD_PLAYED - Player id: %i - Card number: %i.\n", msg->playerId, msg->cardNumber);

	logic_schedulePlayCard();
}

void SrvMsg_NextRoundHandler(void* data)
{
	struct SrvMsg_NextRound* msg = (struct SrvMsg_NextRound*)data;

	printf("[BOT] Message Handler: SRV_MSG_NEXT_ROUND - Round number: %i - Remaining life: %i - Is the last round won: %i - Player cards:", msg->roundNumber, msg->lifeRemaining, msg->isLastRoundWon);
	for (unsigned int i = 0; i < msg->roundNumber; i++) printf(" [%i] = %i", i, msg->playerCards[i]);
	printf(".\n");

	logic_nextRound();
	logic_setPlayerCards(msg->roundNumber, msg->playerCards);
	logic_schedulePlayCard();
}

void SrvMsg_GameEndHandler(void* data)
{
	struct SrvMsg_GameEnd* msg = (struct SrvMsg_GameEnd*)data;
	printf("[BOT] Message Handler: SRV_MSG_GAME_END - Is game won: %i.\n", msg->isGameWon);

	logic_endGame();
}

void SrvMsg_PlayerInfo(void* data)
{
	struct SrvMsg_PlayerInfo* msg = (struct SrvMsg_PlayerInfo*)data;
	printf("[BOT] Message Handler: SRV_MSG_PLAYER_INFO - Player id: %i.\n", msg->playerId);

	logic_initPlayer(msg->playerId);
}

void SrvMsg_MaxHandler(void* data)
{
	// printf("[BOT] Message Handler: SRV_MSG_MAX - Unhandled message.\n");
}