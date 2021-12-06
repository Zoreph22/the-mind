#pragma once

#include <stdio.h>
#include "joueur.h"
#include <stdbool.h>

typedef struct {
	int manche;
	int currentIDTerrain;
	int nbJoueurs;
	int vie;
	int terrainJeu[100];
	joueur joueurs[50];
}partie;

extern partie p;

void initPartie(joueur tab[], int n);
void gestionPartie();
void distribuerCartes();
bool gestionCarteJouer(int idJoueur, int idCarte);

bool partiePerdu();
bool partieGagner();
void manchePerdu();
void mancheGagner();
bool verifCarte(int idJoueur, int idCarte);

void ResetPartie();

