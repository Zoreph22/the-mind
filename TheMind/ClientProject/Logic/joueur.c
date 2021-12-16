/**
 * @file joueur.c
 * @brief Implémentation de la gestion du joueur.
 */

#include <stdbool.h>
#include <string.h>
#include "partie.h"
#include "joueur.h"
#include "messaging/structs.h"
#include "messaging/enums.h"
#include "../socket.h"

joueur j = {0};

void setName(const char * nom)
{
	strcpy(j.nom, nom);
}

void jouerCarte(int carte)
{
	int carteIndex = -1;

	// Récupérer l'index de la carte à partir de son numéro.
	for (int i = 0; i < j.nbCartes; i++) {
		if (j.cartes[i] == carte) {
			carteIndex = i;
		}
	}

	// Carte non présente dans la main, ou déjà jouée.
	if (carteIndex == -1)
	{
		return;
	}

	j.cartes[carteIndex] = 0;

	struct CliMsg_PlayCard msgData = { .cardIndex = carteIndex };
	socket_send(CLI_MSG_PLAY_CARD, &msgData, sizeof(msgData));
}

void setId(int id)
{
	j.id = id;
}