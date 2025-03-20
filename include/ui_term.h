#ifndef UI_TERM_H_
#define UI_TERM_H_

#include "plateau.h"
/* Affiche un plateau sur le terminal */
void afficherPlateauTerminal(plateau p);

/* Demande au joueur le coup qu'il veut jouer,
 * le crée et le joue.
*/
int tourJoueur(plateau p, int joueur);

/* Tire un coup possible aléatoire et le jour */
int tourOrdi(plateau p, int o);

#endif
