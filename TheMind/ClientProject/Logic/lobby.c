#include "lobby.h"
#include "partie.h"
#include "joueur.h"
#include <stdlib.h>
#include <strings.h>
#include "../input.h"
#include <string.h>
#include "messaging/structs.h"
#include "messaging/enums.h"
#include "../socket.h"

lobby l;

void startGame()
{
	if (l.nbPrets == l.nbJoueurs) {
		initPartie(l.joueurs, l.nbJoueurs);
	}
}

void initLobby()
{
	l.nbBots = 0;
	l.nbJoueurs = 1;
	l.nbManches = 0;
	l.nbPrets = 0;
	bzero(l.joueurs, sizeof(l.joueurs));
}

void setPlayerName(int id, char* name)
{
	strcpy(l.joueurs[id].nom, name);
}

void setReady(int id)
{
	l.joueurs[id].ready = true;
	l.nbPrets++;

	startGame();
}

void setNumBot(int nb)
{
	if (nb < 0)
		return;
	l.nbBots = nb;
}

void setInfoLobby(int roundCount, int bCount, int readyCount)
{
	l.nbManches = roundCount;
	l.nbBots = bCount;
	l.nbPrets = readyCount;
}

void printLobby()
{
	// system("clear");
	printf("-----------------------------------\n");

	printf("Lobby : En attente des autres joueurs ... \n");
	printf("Nombres de joueurs prêts : %i / %i\n", l.nbPrets, l.nbJoueurs);
	printf("Nombres de bot : %i\n", l.nbBots);
	printf("\n");
	printf("Votre pseudo : %s\n", j.nom);
	printf("Les autres joueurs :\n");
	for (int i = 1; i < l.nbJoueurs; i++) {
		printf("\t- %s\n", l.joueurs[i].nom);
	}
	printf("\n");
	if (j.ready)
	{
		printf("Vous êtes prêts.\n");
	}
	else
	{
		printf("Appuyer sur p pour devenir prêt.\n");
	}
	printf("Saisir un nombre pour changer le nombre de bot dans la partie.\n");

	printf("-----------------------------------\n");
}

void gestionInputLobby()
{
	char* str = getUserInput();
	int nbBot = atoi(str);

	if (strcmp(str, "p") == 0)
	{
		if (!j.ready)
		{
			j.ready = true;
			socket_send(CLI_MSG_SET_READY, NULL, 0);
		}
	}
	else {
		struct CliMsg_SetNumBot msgData = { .botCount = nbBot };
		socket_send(CLI_MSG_SET_NUM_BOT, &msgData, sizeof(msgData));
	}
}

void addPlayerToLobby(int id, char* name)
{
	l.joueurs[id].id = id;
	l.joueurs[id].ready = false;
	strcpy(l.joueurs[id].nom, name);
	l.nbJoueurs++;
}


