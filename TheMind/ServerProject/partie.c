#include "partie.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
partie p;

void initPartie(joueur tab[], int n)
{
	p.nbPlayers = n;
	for (int i = 0; i < n; i++) {
		p.players[i] = tab[i];
	}
	gestionPartie();
}

void gestionPartie()
{
}

void distribuerCartes()
{
	bool tmp[100];
	int carte = 0;
	for (int i = 0; i < p.nbPlayers; i++) {
		for (int j = 0; j < p.manche; j++) {
			do {
				carte = rand() % 100 + 1;
				if (!tmp[carte]) {
					p.players[i].cartes[j] = 5;
					tmp[carte] = true;
				}
			} while (tmp[carte]);
		}
	}
}

void gestionCarteJouer()
{
}
