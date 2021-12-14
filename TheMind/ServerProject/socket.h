#pragma once

#include <stddef.h>
#include "messaging/enums.h"

/// Port du serveur.
#define SERVER_PORT 25565
/// Nombre maximal de connexions au socket.
#define MAX_CONNECTIONS 20

/**
 * @brief Démarrer le serveur.
 * Démarrer le socket, écouter les demandes de connexion, et gérer la communication avec les clients.
*/
void socket_open();

/**
 * @brief Fermer le serveur.
 * Terminer la connexion des clients et du serveur.
*/
void socket_close();

/**
 * @brief Diffuser un message à tous les clients connectés au serveur.
 * @param type Type du message.
 * @param msg Message à envoyer. Structure correspondant au type du message envoyé. // TODO : mettre référence vers fichier où il y a les structures.
 * @param size Taille du message.
*/
void socket_broadcast(enum SrvMsg type, const void* msg, size_t size);

/**
 * @brief Envoyer un message à un client.
 * @param clientId Identifiant du client.
 * @param type Type du message.
 * @param msg Message à envoyer. Structure correspondant au type du message envoyé. // TODO : mettre référence vers fichier où il y a les structures.
 * @param size Taille du message.
*/
void socket_send(unsigned int clientId, enum SrvMsg type, const void* msg, size_t size);

/**
 * @brief Démarrer et connecter des robots au serveur.
 * @param nb Nombre de robots à connecter. 
*/
void socket_bots(unsigned int nb);