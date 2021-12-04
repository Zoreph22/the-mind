#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "messaging/structs.h"
#include "messaging/enums.h"
#include "../socket.h"
#include "partie.h"


partie p;

void initPartie(joueur tab[], int n)
{
	p.joueurs[n];
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

void distribuerCartes(int* playercard)
{
	memcpy(p.jClient.cartes,playercard, p.manche * sizeof(int));
}

bool gestionCarteJouer(int idJoueur, int idCarte)
{

}

bool partiePerdu()
{

}

bool partieGagner()
{

}

void manchePerdu()
{

}

void mancheGagner()
{

}

void ResetPartie()
{
}

void setCartePose(int carte, int idJCarte) {
	p.cartePose = carte;
	p.idJCartePose = idJCarte;
}

void setNextRound(int roundNumber, int lifeRemaining, int isLastRoundWon)
{
	p.manche = roundNumber;
	p.vie = lifeRemaining;
	p.lastRoundWon = isLastRoundWon;
}
