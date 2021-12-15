/**
 * @file partie.c
 * @brief Implémentation de la gestion d'une partie et des manches.
 */

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

/**
 * @brief Générer les cartes et les distribuer aux joueurs.
 */
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

bool partiePerdu()
{
	stats_updateGameStats();

	struct SrvMsg_GameEnd msgData = { .isGameWon = false };
	socket_broadcast(SRV_MSG_GAME_END, &msgData, sizeof(msgData));
}

/**
 * @brief Arrêter la partie et faire game over. // TODO : remplace par une seule fonction finPartie et return void
 */
bool partieGagner()
{
	stats_updateGameStats();

	struct SrvMsg_GameEnd msgData = { .isGameWon = true };
	socket_broadcast(SRV_MSG_GAME_END, &msgData, sizeof(msgData));
}

/**
 * @brief Vérifier si la carte posée fait perdre ou continuer/gagner la manche.
 * @param numCarte Numéro de la carte (pas l'index).
 */
bool isCardWinner(int numCarte)
{
	if (p.terrainJeu[p.currentIDTerrain] < numCarte) {
		return true;
	}
	return false;
}

/**
 * @brief Vérifier si tous les joueurs ont joués toutes leurs cartes.
 */
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

/**
 * @brief Faire perdre la manche et passer à la prochaine si possible. Retirer une vie, ou game over.
 */
void manchePerdu()
{
	p.vie = p.vie - 1;

	if (p.vie <= 0) {
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

/**
 * @brief Passer à la prochaine manche.
 */
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