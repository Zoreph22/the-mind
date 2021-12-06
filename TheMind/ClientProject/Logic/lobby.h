#pragma once

#include <stdio.h>
#include "joueur.h"
#include "../socket.h"

typedef struct {
	bool inLobby;
	int nbManches;
	int nbBots;
	int nbPrets;
	int nbJoueurs;
	joueur joueurs[50];
}lobby;

extern lobby l;

void initLobby();
void addPlayerToLobby(int id, char* name);

void setInfoLobby(int roundCount, int bCount, int readyCount);

void printLobby();
void gestionInputLobby();