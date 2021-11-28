#pragma once

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
 * @param msg Message à envoyer. TODO : à revoir.
 * @param size Taille du message.
*/
void socket_broadcast(const char* msg, size_t size);

/**
 * @brief Envoyer un message à un client.
 * @param clientId Identifiant du client.
 * @param msg Message à envoyer. TODO : à revoir.
 * @param size Taille du message.
*/
void socket_send(unsigned int clientId, const char* msg, size_t size);