// main.c : Defines the entry point for the application.

#include <signal.h>
#include <stdlib.h>
#include "main.h"
#include "socket.h"

void quit()
{
	socket_close();
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, &quit);
	socket_open();

	return EXIT_SUCCESS;
}
