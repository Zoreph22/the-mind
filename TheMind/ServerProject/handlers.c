#include <stdio.h>
#include "messaging/cli_handlers.h"

void CliMsg_NoneHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_NONE - Client: %i - Unhandled message.\n", senderId);
}

void CliMsg_SetNameHandler(unsigned int senderId, void* data)
{
	struct CliMsg_SetName* msg = (struct CliMsg_SetName*)data;
	printf("Message Handler: CLI_MSG_SET_NAME - Client: %i - New name: %s.\n", senderId, msg->name);
}

void CliMsg_SetReadyHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_SET_READY - Client: %i - Is now ready to play.\n", senderId);
}

void CliMsg_SetNumBotHandler(unsigned int senderId, void* data)
{
	struct CliMsg_SetNumBot* msg = (struct CliMsg_SetNumBot*)data;
	printf("Message Handler: CLI_MSG_SET_NUM_BOT - Client: %i - New bot count: %i.\n", senderId, msg->botCount);
}

void CliMsg_PlayCardHandler(unsigned int senderId, void* data)
{
	struct CliMsg_PlayCard* msg = (struct CliMsg_PlayCard*)data;
	printf("Message Handler: CLI_MSG_PLAY_CARD - Client: %i - Play card index: %i.\n", senderId, msg->cardIndex);
}

void CliMsg_ReplayGameHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_REPLAY_GAME - Client: %i - Want to replay a game.\n", senderId);
}

void CliMsg_MaxHandler(unsigned int senderId, void* data)
{
	printf("Message Handler: CLI_MSG_MAX - Client: %i - Unhandled message.\n", senderId);
}