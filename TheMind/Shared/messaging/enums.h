/**
 * @file enums.h
 * @brief Énumérations des types de message client et serveur.
 */

#pragma once

/// Liste des types de message envoyé par le client.
enum CliMsg
{
	/// Inutilisé.
	CLI_MSG_NONE,
	/// Définir le pseudo du joueur.
	CLI_MSG_SET_NAME = 1,
	/// Mettre prêt le joueur pour débuter la partie.
	CLI_MSG_SET_READY = 2,
	/// Définir le nombre de robots dans la partie.
	CLI_MSG_SET_NUM_BOT = 3,
	/// Jouer une carte.
	CLI_MSG_PLAY_CARD = 4,
	/// Relancer une partie.
	CLI_MSG_REPLAY_GAME = 5,
	/// Confirmer la connexion d'un robot.
	CLI_MSG_BOT_CONNECT = 6,
	/// Arrêter le jeu.
	CLI_MSG_STOP_GAME = 7,
	/// Inutilisé.
	CLI_MSG_MAX
};

/// Liste des types de message envoyé par le serveur.
enum SrvMsg
{
	/// Inutilisé.
	SRV_MSG_NONE,
	/// Le lobby a changé d'état (ex. nombre de joueurs prêts, etc.).
	SRV_MSG_INFO_LOBBY = 1,
	/// Un joueur humain s'est connecté au serveur.
	SRV_MSG_PLAYER_CONNECTED = 2,
	/// Une carte a été jouée.
	SRV_MSG_CARD_PLAYED = 3,
	/// La prochaine manche débute, envoi des cartes des joueurs.
	SRV_MSG_NEXT_ROUND = 4,
	/// La partie est terminée.
	SRV_MSG_GAME_END = 5,
	/// Envoi de l'identifiant du client au joueur qui vient de se connecté.
	SRV_MSG_PLAYER_INFO = 6,
	/// Déconnexion de tous les clients.
	SRV_MSG_DISCONNECT_ALL = 7,
	/// Inutilisé.
	SRV_MSG_MAX
};