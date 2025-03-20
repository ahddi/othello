#include "../include/plateau.h"
#include <stdio.h>
#include <stdlib.h>

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
  return;
}

coup *creerCoup(plateau p, int x, int y, int joueur){
  coup *c = NULL;

  if ((c = (coup *) malloc(sizeof(coup))) == NULL){
    fprintf(stderr, "Erreur d'allocation\n");
    exit(EXIT_FAILURE);
  }

  if (x > 0 && x <= TAILLE_PLATEAU && y > 0 && y <= TAILLE_PLATEAU){
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

/* A COMPLETER */
int estCoupValide(coup *c){
  return 1;
}

void jouerCoup(coup *c){
  if (estCoupValide(c)){
    c->p[c->x - 1][c->y - 1] = c->joueur;
  }
  return;
}

/* Manque validité coup, encadrement, fin de partie & ordinateur */
