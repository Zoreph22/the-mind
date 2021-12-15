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

lobby l;

void startGame()
{
	stats_elapsedSecs(true);
	initPartie(l.joueurs, l.nbJoueurs);
}

void initLobby()
{
	l.nbBots = 0;
	l.nbJoueurs = 0;
	l.nbManches = 0;
	l.nbPrets = 0;
	bzero(l.joueurs, sizeof(l.joueurs));
}

void setPlayerName(int id, char* name)
{
	strcpy(l.joueurs[id].nom, name);
}

void setReady(int id)
{
	l.joueurs[id].ready = true;
	l.nbPrets++;
}

void setNumBot(int nb)
{
	if (nb < 0)
		return;
	l.nbBots = nb;
}

void addPlayerToLobby(int id)
{
	l.joueurs[id].id = id;
	l.joueurs[id].ready = false;
	l.nbJoueurs++;
}


