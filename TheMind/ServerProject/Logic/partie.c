#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "messaging/structs.h"
#include "messaging/enums.h"
#include "../socket.h"
#include "partie.h"


partie p = {0};

void initPartie(joueur tab[], int n)
{
	p.nbJoueurs = n;
	p.manche = 1;
	p.currentIDTerrain = 0;
	p.vie = 3;
	for (int i = 0; i < n; i++) {
		p.joueurs[i] = tab[i];
	}
	gestionPartie();
}

void gestionPartie()
{

}

void distribuerCartes()
{
	bool tmp[100] = { 0 };
	int carte = 0;
	for (int i = 0; i < p.nbJoueurs; i++) {
		for (int j = 0; j < p.manche; j++) {
			do {
				carte = rand() % 101;
				if (!tmp[carte]) {
					p.joueurs[i].cartes[j] = carte;
					tmp[carte] = true;
					break;
				}
			} while (tmp[carte]);
		}
	}
}

bool gestionCarteJouer(int idJoueur, int idCarte)
{
	if (verifCarte(idJoueur, idCarte)) {
		p.terrainJeu[p.currentIDTerrain] = p.joueurs[idJoueur].cartes[idCarte];
		p.joueurs[idJoueur].cartes[idCarte] = 0;
		mancheGagner();
		return true;
	}
	else {
		manchePerdu();
		return false;
	}
}

bool partiePerdu()
{
	struct SrvMsg_GameEnd msgData = { .isGameWon = false };
	socket_broadcast(SRV_MSG_GAME_END, &msgData, sizeof(msgData));
}

bool partieGagner()
{
	struct SrvMsg_GameEnd msgData = { .isGameWon = true };
	socket_broadcast(SRV_MSG_GAME_END, &msgData, sizeof(msgData));
}

void manchePerdu()
{
	p.vie = p.vie - 1;

	if (p.vie == 0) {
		partiePerdu();
		return;
	}

	for (int i = 0; i < p.nbJoueurs; i++) {
		struct SrvMsg_NextRound msgData = { .roundNumber = p.manche, .lifeRemaining = p.vie, .isLastRoundWon = false };
		memcpy(msgData.playerCards, p.joueurs[i].cartes, p.manche * sizeof(int));
		socket_send(i, SRV_MSG_NEXT_ROUND, &msgData, sizeof(msgData));
	}
}

void mancheGagner()
{
	p.manche = p.manche + 1;
	distribuerCartes();

	for (int i = 0; i < p.nbJoueurs; i++) {
		struct SrvMsg_NextRound msgData = { .roundNumber = p.manche, .lifeRemaining = p.vie, .isLastRoundWon = true };
		memcpy(msgData.playerCards, p.joueurs[i].cartes, p.manche * sizeof(int));
		socket_send(i, SRV_MSG_NEXT_ROUND, &msgData, sizeof(msgData));
	}
}

bool verifCarte(int idJoueur, int idCarte)
{
	if (p.terrainJeu[p.currentIDTerrain] < p.joueurs[idJoueur].cartes[idCarte]) {
		return true;
	}
	return false;
}

void setCartePose(int carte, int idJCarte)
{
}

void ResetPartie()
{
}
