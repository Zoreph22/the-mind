// main.c : Defines the entry point for the application.

#include <sds/sds.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "main.h"
#include "socket.h"

void quit()
{
	disconnect();
	exit(EXIT_SUCCESS);
}

void connectMenu()
{
	char ip[15];
	unsigned short port;

	printf("Server IP address: ");
	fgets(ip, sizeof ip, stdin);

	printf("Server port: ");
	scanf("%hu", &port);

	ip[strcspn(ip, "\n")] = 0;

	connectTo(ip, port);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, &quit);
	connectMenu();

	return 0;
}
