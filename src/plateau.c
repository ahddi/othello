#include "../include/plateau.h"
#include <stdio.h>
#include <stdlib.h>

/* on stocke en global un tableau représentant les delta (un décalage quoi) à effectuer pour parcourir dans telle ou telle direction
 * par ex, pour aller dans la diagonale gauche depuis (x,y) on doit aller sur (x--, y--)
 * on décide que les fonctions de parcours visiteront toutes les directions dans le sens horaire en partant de "<-- o" */
const int dx[8] = { 0, -1, -1, -1,  0,  1, 1, 1 };
const int dy[8] = {-1, -1,  0,  1,  1,  1, 0, -1};

plateau creerPlateau(){
  plateau p = NULL;
  int i;

  if ((p = (plateau) malloc(TAILLE_PLATEAU * sizeof(int *))) == NULL){
    fprintf(stderr, "Erreur d'allocation\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < TAILLE_PLATEAU; i ++){
    p[i] = (int *) malloc(TAILLE_PLATEAU * sizeof(int));
    if (p[i] == NULL){
       fprintf(stderr, "Erreur d'allocation\n");
       for (; i > 0; i--){
         free(p[i]);
       }
       exit(EXIT_FAILURE);
    }
  }
  return p;
}

void libererPlateau(plateau p){
  int i;

  for (i = 0; i < TAILLE_PLATEAU; i++){
    free(p[i]);
  }
  free(p);
  return;
}

void initPlateau(plateau p){
  int i, j;

  for (i = 0; i < TAILLE_PLATEAU; i++){
    for (j = 0; j < TAILLE_PLATEAU; j++){
      p[i][j] = 0;
    }
  }
  p[3][3] = 1;
  p[4][4] = 1;
  p[3][4] = 2; 
  p[4][3] = 2;
  return;
}

coup *creerCoup(plateau p, int x, int y, int joueur){
  coup *c = NULL;

  if ((c = (coup *) malloc(sizeof(coup))) == NULL){
    fprintf(stderr, "Erreur d'allocation\n");
    exit(EXIT_FAILURE);
  }

  if (x >= 0 && x < TAILLE_PLATEAU && y >= 0 && y < TAILLE_PLATEAU){
    c->p = p;
    c->joueur = joueur;
    c->x = x;
    c->y = y;

    return c;
  }else{
    fprintf(stderr, "Coordonnées invalides\n");
    return NULL;
  }
}

void libererCoup(coup *c){
  free(c);
  return;
}

int estHorsPlateau(int x, int y){
  if (x < 0 || x >= TAILLE_PLATEAU || y < 0 || y >= TAILLE_PLATEAU){
    return 1; 
  }
  return 0;
}

int opposant(int joueur){
  if (joueur == 1) return 2; 
  else return 1;
}

int estLigneValide(coup *c, int direction){
  int x = c->x + dx[direction];
  int y = c->y + dy[direction];
  int opposantsTrouves = 0; 

  /* tant qu'on est pas sorti du plateau et que le pion courant est un opposant : */
  while (!estHorsPlateau(x, y) && c->p[x][y] == opposant(c->joueur)){
    /* on avance dans la direction */
    x += dx[direction];
    y += dy[direction];
    opposantsTrouves++;
  }

  if (opposantsTrouves != 0  && !estHorsPlateau(x, y) && c->p[x][y] == c->joueur){
    return 1;
  }

  return 0; 
}

int estCoupValide(coup *c){
  int i, res = 0;
  
  /* si la case n'est pas vide */
  if (c->p[c->x][c->y] != 0){
    return 0;
  }
  
  for (i = 0; i < 8; i++){
      if (estLigneValide(c, i)){
        res = 1;
      }
  }
  return res;
}

void retournerPionsVers(coup *c, int direction){
  int x = c->x + dx[direction];
  int y = c->y + dy[direction];

  while (!estHorsPlateau(x, y) && c->p[x][y] == opposant(c->joueur)){
    c->p[x][y] = c->joueur;
    printf("retourne (%d,%d)\n", x, y);
    x += dx[direction];
    y += dy[direction];
  }
  return;
}

void retournerPions(coup *c){
  int i;
  for (i = 0; i < 8; i++){
    if (estLigneValide(c, i)){
      retournerPionsVers(c, i);
    }
  }
  return;
}

void jouerCoup(coup *c){
  c->p[c->x][c->y] = c->joueur;
  retournerPions(c);
  return;
}

/* A optimiser ==> Stocker un tableau des coups valides que l'ordi réutilisera pour jouer son tour*/
int nbCoupsValides(plateau p, int joueur){
  int i, j, res = 0;
  coup *c;
  for (i = 0; i < TAILLE_PLATEAU; i++){
    for (j = 0; j < TAILLE_PLATEAU; j++){
      c = creerCoup(p, i, j, joueur);
      if (estCoupValide(c)){
	res++;
      }
    }
  }
  return res;
}

/* A optimiser ==> Stocker le nb de chaque couleur dans des variables  */
int positionGagnante(plateau p, int joueur){
  int nbNoirs = 0, nbBlancs = 0;
  int i, j;
  if (nbCoupsValides(p, joueur) == 0){
    for (i = 0; i < TAILLE_PLATEAU; i++){	
      for (j = 0; j < TAILLE_PLATEAU; j++){
	if (p[i][j] == 1) nbBlancs++;
	else{
	  if (p[i][j] == 2) nbNoirs++;
	}
      }
    }
  }
  if (joueur == 1){
    return nbBlancs > nbNoirs;
  }else{
    return nbNoirs > nbBlancs;
  }
}

int jouerOrdi(plateau p, int ordi){
  int i, j, k = 0;
  coup *tabCoupsValides[TAILLE_PLATEAU * TAILLE_PLATEAU];
  coup *c = NULL;
  printf("TOUR DE L'ORDI\n");
  for (i = 0; i < TAILLE_PLATEAU; i++){
    for (j = 0; j < TAILLE_PLATEAU; j++){
      c = creerCoup(p, i, j, ordi);
      if (estCoupValide(c)){
        tabCoupsValides[k] = c; 
        k++;
      }
      else{
        libererCoup(c);
      }
    }
  }
  if (k == 0) 
    return 0;

  jouerCoup(tabCoupsValides[rand() % k]);
  return 1;
} 


