/**
 * @file joueur.h
 * @brief Interface permettant la gestion d'un joueur.
 */

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "stats.h"

/// Structure stockant les données d'un joueur.
typedef struct S_Joueur {
	/// Le joueur est-il prêt pour démarrer la partie ?
	bool ready;
	/// Nom du joueur.
	char nom[20];
	/// Identifiant du joueur.
	int id;
	/// Liste des cartes du joueur. La valeur de la carte vaut @a 0 si celle-ci a été jouée.
	int cartes[50];
}joueur;