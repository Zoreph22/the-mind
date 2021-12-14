#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "stats.h"

typedef struct {
	bool ready;
	char nom[20];
	int id;
	int cartes[50];
}joueur;