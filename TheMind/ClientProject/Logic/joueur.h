#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct {
	bool ready;
	char* nom;
	int id;
	int nbCartes;
	int cartes[50];
}joueur;

extern joueur j;

char setName(char nom);
int jouerCarte(int carte);