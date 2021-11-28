// main.c : Defines the entry point for the application.

#include <signal.h>
#include <stdlib.h>
#include "main.h"
#include "socket.h"

void quit()
{
	closeServer();
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
	signal(SIGINT, &quit);
	startServer();

	return 0;
}
