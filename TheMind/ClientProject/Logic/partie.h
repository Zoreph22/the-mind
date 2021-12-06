#pragma once

#include <stdio.h>
#include "joueur.h"
#include <stdbool.h>

typedef struct {
	int manche;
	int currentIDTerrain;
	int nbJoueurs;
	int vie;
	int cartePose;
	int idJCartePose;
	bool lastRoundWon;
	joueur jClient;
	joueur joueurs[50];
}partie;

extern partie p;

void distribuerCartes(int *playercard);

void setCartePose(int carte, int idJCarte);
void setNextRound(int roundNumber, int lifeRemaining, int isLastRoundWon);
void finPartie();

void printManche();
void gestionInputCarteJouer();
void gestionInputFinPartie();
