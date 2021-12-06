#include <stdbool.h>
#include <string.h>
#include "partie.h"
#include "joueur.h"

joueur j = {0};

void setName(char * nom)
{
	strcpy(j.nom, nom);
}

int jouerCarte(int carte)
{
	int carteIndex = 0;

	// Récupérer l'index de la carte à partir de son numéro.
	for (int i = 0; i < j.nbCartes; i++) {
		if (j.cartes[i] == carte) {
			carteIndex = i;
		}
	}

	j.cartes[carteIndex] = 0;

	return carteIndex;
}

void setId(int id)
{
	j.id = id;
}

int changeNbBot(int nbBot) {
	return nbBot;
}
