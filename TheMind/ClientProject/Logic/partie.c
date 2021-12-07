#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "../input.h"
#include "messaging/structs.h"
#include "messaging/enums.h"
#include "../socket.h"
#include "partie.h"
#include "lobby.h"
#include "joueur.h"
#include "../utils.h"

partie p = { 0 };

void distribuerCartes(int* playercard)
{
	j.nbCartes = p.manche;
	bzero(j.cartes, (j.nbCartes - 1) * sizeof(int));
	memcpy(j.cartes, playercard, j.nbCartes * sizeof(int));
}

void setCartePose(int carte, int idJCarte) {
	l.joueurs[idJCarte].nbCartes--;
	p.cartePose = carte;
	p.idJCartePose = idJCarte;
}

void setNextRound(int roundNumber, int lifeRemaining, int isLastRoundWon)
{
	p.manche = roundNumber;
	p.vie = lifeRemaining;

	p.cartePose = 0;
	p.idJCartePose = 0;

	p.lastRoundWon = isLastRoundWon;

	for (int i = 0; i < l.nbJoueurs; i++)
	{
		l.joueurs[i].nbCartes = p.manche;
	}
}

void finPartie()
{
	clear();
	printf("-------------------\n");

	printf("Game Over !\n");
	printf("Vous avez perdu toutes vos vies.\n");

	printf("\n");

	printf("Nombre de manches gagnées : %i.\n", p.manche - 1);

	printf("\n\n");

	printf("Saisir la touche R pour recommencer une partie.\n");

	printf("-------------------\n");
}

void printManche()
{
	if (l.inLobby)
	{
		return;
	}

	clear();

	printf("--------------------\n");

	printf("Numéro de la manche : %i.\n", p.manche);
	printf(p.lastRoundWon ? "La manche précédente a été gagnée.\n" : "La manche précédente a été perdue.\n");

	printf("\n");

	printf("Nombre restant de vie(s) : %i.\n", p.vie);

	printf("\n");

	if (!p.cartePose)
	{
		printf("Aucune carte n'a été jouée.\n");
	}
	else
	{
		printf("Carte posée par le joueur %s : %i.\n", p.idJCartePose == j.id ? j.nom : l.joueurs[p.idJCartePose].nom, p.cartePose);
	}


	printf("\n\n");

	printf("Nombre restant de cartes des autres joueurs :\n");

	for (int i = 0; i < l.nbJoueurs; i++)
	{
		if (i == j.id) continue;
		printf("\t%s : %i / %i\n", l.joueurs[i].nom, l.joueurs[i].nbCartes, p.manche);
	}

	printf("\n\n");

	printf("Votre main :");
	for (int i = 0; i < p.manche; i++)
	{
		int numCarte = j.cartes[i];

		if (numCarte > 0)
		{
			printf(" %i", numCarte);
		}
	}

	printf("\n");

	printf("Saisir le numéro de la carte que vous voulez poser.\n");

	printf("--------------------\n");
}

void gestionInputCarteJouer()
{
	char* input = getUserInput();
	int numCarte = atoi(input);

	if (numCarte <= 0)
	{
		return;
	}

	jouerCarte(numCarte);
}

void gestionInputFinPartie()
{
	char* input = getUserInput();

	if (strcmp(input, "R") == 0 || strcmp(input, "r") == 0)
	{
		socket_send(CLI_MSG_REPLAY_GAME, NULL, 0);
	}
}