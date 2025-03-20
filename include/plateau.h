#ifndef PLATEAU_H_
#define PLATEAU_H_
#define TAILLE_PLATEAU 8

typedef int **plateau; /* 1 si blanc, 2 si noir, 0 sinon */

/* Représente un coup */
typedef struct{
  int x,y;
  int joueur;
  plateau p;
}coup;

/* Alloue une zone mémoire pour un plateau */
plateau creerPlateau();

/* Libere la zone mémoire d'un plateau */
void libererPlateau(plateau p);

/* Initialise un nouveau plateau :
 * mets toutes les cases à zéro sauf les 4 sur
 * lesquelles les pions de base sont placés.
 */
void initPlateau(plateau p);

/* Créé un nouveau coup :
 * alloue une zone mémoire et la remplit avec
 * les données d'un coup
 */
coup *creerCoup(plateau p, int x, int y, int joueur);

/* Libère la zone mémoire d'un coup
 * NB : je separerai creerCoup en deux fonctions pour n'avoir
 * qu'un ou deux pointeurs créés tout au long de la partie (histoire d'opti meme
 * si c pas hyper important), mais plus tard pcq là bon
 */
void libererCoup(coup *c);

/* Renvoie la validité d'un coup */
int estCoupValide(coup *c);

/* Joue un coup :
 * place le pion correspondant sur le plateau
 */
void jouerCoup(coup *c);

#endif
