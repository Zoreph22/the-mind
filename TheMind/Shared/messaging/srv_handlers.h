#pragma once

#include "enums.h"
#include "structs.h"

void SrvMsg_NoneHandler(void* data);
void SrvMsg_InfoLobbyHandler(void* data);
void SrvMsg_PlayerConnectedHandler(void* data);
void SrvMsg_CardPlayedHandler(void* data);
void SrvMsg_NextRoundHandler(void* data);
void SrvMsg_GameEndHandler(void* data);
void SrvMsg_MaxHandler(void* data);

/**
 * @brief Tableau associatif (type du message serveur => fonction qui gère le message).
 * Les fonctions gestionnaires ont un paramètre : pointeur vers la structure correspondant au type du message.
 * TODO : see les enums.
*/
__attribute__((unused)) static void (*srvMsgHandler[SRV_MSG_MAX + 1])(void* data) = {
	[0] = &SrvMsg_NoneHandler,[SRV_MSG_MAX] = &SrvMsg_MaxHandler,
	[1] = &SrvMsg_InfoLobbyHandler,
	[2] = &SrvMsg_PlayerConnectedHandler,
	[3] = &SrvMsg_CardPlayedHandler,
	[4] = &SrvMsg_NextRoundHandler,
	[5] = &SrvMsg_GameEndHandler
};