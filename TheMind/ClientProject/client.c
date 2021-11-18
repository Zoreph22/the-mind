// client.c : Defines the entry point for the application.

#include <sds/sds.h>
#include "client.h"

int main(int argc, char * argv[])
{
	sds s = sdsnew("Started Client.\n");
	printf("%s", s);

	return 0;
}
