/**
 * @file main.c
 * @brief Fichier de démarrage du programme.
 */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <time.h>
#include <linux/limits.h>
#include "socket.h"

/// Quitter le programme proprement en déconnectant les clients et le serveur.
void quit()
{
	socket_close();
	exit(EXIT_SUCCESS);
}

/// Initialiser l'état du programme.
void init()
{
	srand(time(NULL));
	signal(SIGINT, &quit);

	// Changer le répertoire courant vers le répertoire où se trouve l'exécutable.
	char path[PATH_MAX] = "";
	readlink("/proc/self/exe", path, sizeof(path));
	chdir(dirname(path));
}

int main(int argc, char* argv[])
{
	init();
	socket_open();

	return EXIT_SUCCESS;
}
