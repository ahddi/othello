#ifndef UI_TERM_H_
#define UI_TERM_H_

#include "plateau.h"
/* Affiche un plateau sur le terminal */
void afficherPlateauTerminal(plateau p);

/* Demande au joueur le coup qu'il veut jouer,
 * le crée et le joue.
*/
int tourJoueurTerminal(plateau p, int joueur);

#endif
