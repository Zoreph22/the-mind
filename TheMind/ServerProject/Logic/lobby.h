#pragma once

#include <stdio.h>
#include "joueur.h"

typedef struct {
	int nbManche;
	int nbBots;
	int nbPrets;
	int nbJoueurs;
	joueur joueurs[];
}lobby;


void lobbyStart();