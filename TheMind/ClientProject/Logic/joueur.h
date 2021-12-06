#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct {
	bool ready;
	char nom[20];
	int id;
	int nbCartes;
	int cartes[50];
}joueur;

extern joueur j;

void setName(char * nom);
void jouerCarte(int carte);

void setId(int id);