// main.c : Defines the entry point for the application.

#include <sds/sds.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "main.h"
#include "socket.h"
#include "input.h"

void quit()
{
	socket_disconnect();
	exit(EXIT_SUCCESS);
}

void connectMenu()
{
	char ip[15];
	unsigned short port;

	/*printf("Server IP address: ");
	fgets(ip, sizeof ip, stdin);

	printf("Server port: ");
	scanf("%hu", &port);

	ip[strcspn(ip, "\n")] = 0;*/

	socket_connect("127.0.0.1", 25565);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, &quit);
	connectMenu();

	// beginInputLoop();

	return EXIT_SUCCESS;
}

/*
void jouerCarte()
{
	int carte = atoi(getUserInput());

	if (carte < 10)
	{
		printf("Votre carte : %i !\n", carte);
		setInputCallback(NULL);
	}
	else
	{
		printf("La carte doit être < 10. Resaisir : \n");
	}
}

void* func(void* arg)
{
	int i = 0;

	while (1)
	{
		sleep(10);
		system("clear");
		printf("Carte posée : %i.\n", i++);
		printf("Test : ");
		printf("blabla.\n");
		printf("\nSaisir votre carte: ");
		fflush(stdout);
		setInputCallback(&jouerCarte);
	}
}

int main(int argc, char* argv[])
{
	pthread_t t;
	pthread_create(&t, NULL, &func, NULL);

	beginInputLoop();

	return 0;
}
*/