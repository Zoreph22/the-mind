/**
 * @file lobby.h
 * @brief Interface permettant de gérer le lobby.
 */

#pragma once

#include <stdio.h>
#include "joueur.h"
#include "../socket.h"
#include "socket/consts.h"

/// Structure stockant les données du lobby.
typedef struct S_Lobby {
	int nbManches; // TODO : DELETE
	/// Nombre de robots présents.
	int nbBots;
	/// Nombre de joueurs prêts pour démarrer la partie.
	int nbPrets;
	/// Nombre de joueurs dans le lobby.
	int nbJoueurs;
	/// Tableau contenant les joueurs (index du tableau = identifiant du joueur).
	joueur joueurs[MAX_CONNECTIONS];
}lobby;

/// Instance du lobby.
extern lobby l;

/**
 * @brief Démarrer la partie et réinitialiser les données de l'ancienne partie si ce n'est pas la première.
 */
void startGame();

/**
 * @brief Initialiser le lobby. TODO : vérifier si fonction utilisée.
 */
void initLobby();

/**
 * @brief Ajouter un joueur au lobby.
 * @param id Identifiant du joueur.
 */
void addPlayerToLobby(int id);

/**
 * @brief Définir le nom d'un joueur. TODO : déplacer cette fonction
 * @param id Identifiant du joueur.
 * @param name Nouveau nom.
 */
void setPlayerName(int id, char* name);

/**
 * @brief Définir un joueur prêt. TODO : déplacer cette fonction
 * @param id Identifiant du joueur.
 */
void setReady(int id);

/**
 * @brief Définir le nombre de robots.
 * @param nb Nouveau nombre.
 */
void setNumBot(int nb);