#pragma once

#include "messaging/enums.h"

/**
 * @brief Définir l'adresse IP du serveur
 * @param ip Adresse IP.
*/
void socket_setIp(char* ip);

/**
 * @brief Définir le port du serveur.
 * @param port Port.
*/
void socket_setPort(unsigned short port);

/**
 * @brief Se connecter à un serveur distant.
*/
void socket_connect();

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