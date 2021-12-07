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
#include "Logic/joueur.h"
#include "input.h"
#include "utils.h"

void quit()
{
	socket_disconnect();
	exit(EXIT_SUCCESS);
}

void connectMenu()
{
	char ip[15];
	unsigned short port;
	char name[20];

	printf("Server IP address: ");
	fgets(ip, sizeof ip, stdin);

	printf("Server port: ");
	scanf("%hu", &port);
	fgetc(stdin);

	printf("Type your name: ");
	fgets(name, sizeof name, stdin);

	ip[strcspn(ip, "\n")] = 0;
	name[strcspn(name, "\n")] = 0;

	setName(name);

	socket_connect("127.0.0.1", 25565);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, &quit);
	connectMenu();

	beginInputLoop();

	return EXIT_SUCCESS;
}