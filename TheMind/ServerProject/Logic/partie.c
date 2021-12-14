#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "stats.h"
#include "messaging/structs.h"
#include "messaging/enums.h"
#include "../socket.h"
#include "partie.h"


partie p = {0};

void initPartie(joueur tab[], int n)
{
	p.nbJoueurs = n;
	p.manche = 0;
	p.currentIDTerrain = 0;
	p.vie = 3;

	for (int i = 0; i < n; i++) {
		p.joueurs[i] = tab[i];
	}

	mancheGagner(); // Débuter le 1ère manche.
}

void distribuerCartes()
{
	bool tmp[100] = { 0 };
	int carte = 0;
	for (int i = 0; i < p.nbJoueurs; i++) {
		for (int j = 0; j < p.manche; j++) {
			do {
				carte = rand() % (101 - 1) + 1;
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
	// Mettre à jour les statistiques.
	unsigned int reactionTime = stats_elapsedSecs(false);
	stats_updatePlayerReactionTimes(idJoueur, reactionTime);
	stats_updateReactionTimes(reactionTime);
	stats_elapsedSecs(true);

	// Gérer la carte.
	int numCarte = p.joueurs[idJoueur].cartes[idCarte];
	
	p.joueurs[idJoueur].cartes[idCarte] = 0; // Retirer la carte de la main du joueur.

	// La carte posée fait gagner la manche et toutes les cartes ont été posées.
	if (isCardWinner(numCarte) && areAllCardsPlayed()) {
		mancheGagner();
		return false;
	}

	// La carte posée fait perdre la manche.
	if (!isCardWinner(numCarte)) {
		stats_updatePlayerFailCount(idJoueur);
		manchePerdu();
		return false;
	}

	// Continuer la manche.
	p.terrainJeu[p.currentIDTerrain] = numCarte; // Poser la carte.
	return true;
}

bool partiePerdu()
{
	stats_updateGameStats();

	struct SrvMsg_GameEnd msgData = { .isGameWon = false };
	socket_broadcast(SRV_MSG_GAME_END, &msgData, sizeof(msgData));
}

bool partieGagner()
{
	stats_updateGameStats();

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

	p.terrainJeu[p.currentIDTerrain] = 0;
	distribuerCartes();

	for (int i = 0; i < p.nbJoueurs; i++) {
		struct SrvMsg_NextRound msgData = { .roundNumber = p.manche, .lifeRemaining = p.vie, .isLastRoundWon = false };
		memcpy(msgData.playerCards, p.joueurs[i].cartes, p.manche * sizeof(int));
		socket_send(i, SRV_MSG_NEXT_ROUND, &msgData, sizeof(msgData));
	}
}

void mancheGagner()
{
	p.manche = p.manche + 1;
	p.terrainJeu[p.currentIDTerrain] = 0;
	distribuerCartes();

	for (int i = 0; i < p.nbJoueurs; i++) {
		struct SrvMsg_NextRound msgData = { .roundNumber = p.manche, .lifeRemaining = p.vie, .isLastRoundWon = true };
		memcpy(msgData.playerCards, p.joueurs[i].cartes, p.manche * sizeof(int));
		socket_send(i, SRV_MSG_NEXT_ROUND, &msgData, sizeof(msgData));
	}
}

/// Vérifier si la carte posée fait perdre ou continuer/gagner la manche.
bool isCardWinner(int numCarte)
{
	if (p.terrainJeu[p.currentIDTerrain] < numCarte) {
		return true;
	}
	return false;
}

/// Vérifier si tous les joueurs ont joués toutes leurs cartes.
bool areAllCardsPlayed()
{
	bool allCardsPlayed = true;

	for (int i = 0; i < p.nbJoueurs; i++)
	{
		for (int j = 0; j < p.manche; j++)
		{
			if (p.joueurs[i].cartes[j] != 0)
			{
				allCardsPlayed = false;
				break;
			}
		}
	}

	return allCardsPlayed;
}

void setCartePose(int carte, int idJCarte)
{
}

void ResetPartie()
{
}
