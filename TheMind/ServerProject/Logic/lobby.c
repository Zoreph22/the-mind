#include "lobby.h"
#include "partie.h"
#include <stdlib.h>
#include <strings.h>

lobby l;

void startGame()
{
	if (l.nbPrets == l.nbJoueurs) {
		initPartie(l.joueurs, l.nbJoueurs);
	}
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
	l.joueurs[id].nom = name;
}

void setReady(int id)
{
	l.joueurs[id].ready = true;
	l.nbPrets++;

	startGame();
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


