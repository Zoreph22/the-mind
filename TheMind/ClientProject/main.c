/**
 * @file main.c
 * @brief Fichier de démarrage du programme.
 */

#include <sds/sds.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "socket.h"
#include "logic/joueur.h"
#include "input.h"
#include "utils.h"

/// Quitter le programme proprement en se déconnectant du serveur.
void quit()
{
	socket_disconnect();
	exit(EXIT_SUCCESS);
}

/// Afficher le menu de connexion au serveur puis s'y connecter.
void connectMenu()
{
	char ip[15];
	unsigned short port;
	char name[20];

	do
	{
		clear();

		printf("-- Connexion à un serveur de jeu --\n");
		printf("Entrez les informations de connexion pour vous connecter à un serveur.\n\n");

		printf("Adresse IP du serveur : ");
		fgets(ip, sizeof(ip), stdin);

		printf("Port du serveur: ");
		scanf("%hu", &port);
		fgetc(stdin);

		printf("Tapez votre pseudo : ");
		fgets(name, sizeof(name), stdin);
		
		printf("\nConnexion au serveur...\n");

		ip[strcspn(ip, "\n")] = 0;
		name[strcspn(name, "\n")] = 0;

		setName(name);
	} while (!socket_connect(ip, port));
}

int main(int argc, char* argv[])
{
	signal(SIGINT, &quit);
	connectMenu();

	beginInputLoop();

	return EXIT_SUCCESS;
}