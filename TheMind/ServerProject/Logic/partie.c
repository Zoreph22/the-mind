#include "partie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

partie p;

void initPartie(joueur tab[], int n)
{
	p.joueurs[n];
	p.nbJoueurs = n;
	p.manche = 1;
	p.currentIDTerrain = 0;
	p.vie = 3;
	for (int i = 0; i < n; i++) {
		p.joueurs[i] = tab[i];
	}
	gestionPartie();
}

void gestionPartie()
{

}

void distribuerCartes()
{
	bool tmp[100] = { 0 };
	int carte = 0;
	for (int i = 0; i < p.nbJoueurs; i++) {
		for (int j = 0; j < p.manche; j++) {
			do {
				carte = rand() % 101;
				if (!tmp[carte]) {
					p.joueurs[i].cartes[j] = carte;
					tmp[carte] = true;
					break;
				}
			} while (tmp[carte]);
		}
	}
}

void gestionCarteJouer(int idJoueur, int idCarte)
{
	if (verifCarte(idJoueur, idCarte)) {
		p.terrainJeu[p.currentIDTerrain] = p.joueurs[idJoueur].cartes[idCarte];
		mancheGagner();
	}
	else {
		manchePerdu();
	}
}

bool partiePerdu()
{
	if (p.vie = 0) {

	}
}

bool partieGagner()
{
	return false;
}

void manchePerdu()
{
	if (p.vie > 1) {
		p.vie = p.vie - 1;
	}
	else {
		p.vie = p.vie - 1;
		partiePerdu();
	}
}

void mancheGagner()
{
	p.manche = p.manche + 1;
	distribuerCartes();
}

bool verifCarte(int idJoueur, int idCarte)
{
	if (p.terrainJeu[p.currentIDTerrain] < p.joueurs[idJoueur].cartes[idCarte]) {
		return true;
	}
	return false;
}

void ResetPartie()
{
}
