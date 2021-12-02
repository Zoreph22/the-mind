#include "lobby.h"
#include "partie.h"

lobby l;

void lobbyStart()
{
	if (l.nbPrets == l.nbJoueurs) {
		initPartie(l.joueurs, l.nbJoueurs);
	}
}
