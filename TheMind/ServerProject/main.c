// main.c : Defines the entry point for the application.

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <time.h>
#include <linux/limits.h>
#include "main.h"
#include "socket.h"

#include <stdio.h>
#include "Logic/stats.h"

void quit()
{
	socket_close();
	exit(EXIT_SUCCESS);
}

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

	//stats_generatePDF();

	return EXIT_SUCCESS;
}
