#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <sds/sds.h>

typedef struct {
	bool ready;
	sds nom;
	int id;
	int nbCartes;
	int cartes[50];
}joueur;

extern joueur j;

char setName(char nom);
int jouerCarte(int carte);