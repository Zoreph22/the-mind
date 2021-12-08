#pragma once

#include <stdbool.h>
#include "messaging/enums.h"

/**
 * @brief Se connecter à un serveur distant.
 * @param ip Adresse IP du serveur.
 * @param port Port du serveur.
 * @return @a true si connexion réussie, sinon @a false.
*/
bool socket_connect(const char* ip, unsigned short port);

/**
 * @brief Se déconnecter du serveur actuel.
*/
void socket_disconnect();

/**
 * @brief Envoyer un message au serveur.
 * @param type Type du message.
 * @param msg Message à envoyer.
 * @param size Taille du message.
*/
void socket_send(enum CliMsg type, const void* msg, size_t size);