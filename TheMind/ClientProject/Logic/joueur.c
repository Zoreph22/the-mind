#include "joueur.h"
#include <stdbool.h>
#include "partie.h"

joueur j;

char setName(char nom)
{
	j.nom = nom;
	return nom;
}

int jouerCarte(int carte)
{
	int carteIndex = 0;
	for (int i = 0; i < j.nbCartes; i++) {
		if (j.cartes[i] = carte) {
			carteIndex = i;
		}
	}
	j.cartes[i] = 0;
	return carteIndex;
}

int changeNbBot(int nbBot) {
	return nbBot
}
