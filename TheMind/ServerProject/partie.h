#pragma once

#include <stdio.h>
#include "joueur.h"

typedef struct {
	int manche : 1;
	int terrainJeu[100];
	joueur players[10];
	int nbPlayers;
}partie;

void initPartie(joueur tab[], int n);
void gestionPartie();
void distribuerCartes();
void gestionCarteJouer();
