/**
 * @file lobby.c
 * @brief Implémentation de la gestion du lobby.
 */

#include "lobby.h"
#include "partie.h"
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "messaging/structs.h"
#include "messaging/enums.h"

Lobby lobby;

void startGame()
{
	stats_elapsedSecs(true);
	initPartie(lobby.joueurs, lobby.nbJoueurs);
}

void setPlayerName(int id, const char* name)
{
	strcpy(lobby.joueurs[id].nom, name);
}

void setReady(int id)
{
	lobby.joueurs[id].ready = true;
	lobby.nbPrets++;
}

void setNumBot(int nb)
{
	if (nb < 0)
		return;
	lobby.nbBots = nb;
}

void addPlayerToLobby(int id)
{
	lobby.joueurs[id].id = id;
	lobby.joueurs[id].ready = false;
	lobby.nbJoueurs++;
}


