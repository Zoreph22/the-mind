#pragma once

/**
 * @brief Se connecter à un serveur distant.
 * @param ip Adresse IP du serveur.
 * @param port Port du serveur.
*/
void socket_connect(const char* ip, unsigned short port);

/**
 * @brief Se déconnecter du serveur actuel.
*/
void socket_disconnect();

/**
 * @brief Envoyer un message au serveur.
 * @param msg Message à envoyer.
 * @param size Taille du message.
*/
void socket_send(const char* msg, size_t size);