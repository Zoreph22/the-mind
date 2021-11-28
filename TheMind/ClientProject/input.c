#include <stdlib.h>
#include <stdio.h>
#include "input.h"

/// Fonction de rappel appelée après une saisie.
void (*ptrCallback)() = NULL;
/// Buffer stockant la dernière saisie.
char buffer[1024];

void setInputCallback(void (*newPtrCallback)())
{
	ptrCallback = newPtrCallback;
}

char* getUserInput()
{
	return buffer;
}

void beginInputLoop()
{
	while (1)
	{
		fgets(buffer, sizeof buffer, stdin);

		if (ptrCallback)
		{
			ptrCallback();
		}
	}
}