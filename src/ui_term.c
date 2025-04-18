#include "../include/ui_term.h"
#include "../include/plateau.h"
#include <stdio.h>
#include <stdlib.h>

void viderBuffer(){
  int c = 0;
  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }
}

void afficherPlateauTerminal(plateau p){
  int i, j;

  printf("   -----------------\n");
  for (i = 0; i < 8; i++){
    printf("%d | ", i+1);
    for (j = 0; j < 8; j++){
      if (p[i][j] == 1) printf("B ");
      else if (p[i][j] == 2) printf("N ");
      else printf(". ");
    }
    printf("| \n");
  }
  printf("   -----------------\n    A B C D E F G H\n");
  return;
}

int tourJoueurTerminal(plateau p, int joueur){
  int x, y;
  char tmp;
  coup *c;
  int statut = 0;

  while (statut == 0){
    printf("Quel coup souhaitez-vous jouer ?\n");
    printf("Quelle ligne ? : \n");
    if (scanf("%d", &x) != 1) return 0;
    viderBuffer();
    printf("Quelle colonne ? : \n");
    if (scanf("%c", &tmp) != 1) return 0;
    y = tmp - 'A' + 1;

    if ( (c = creerCoup(p, x - 1, y - 1, joueur)) == NULL) return 0;

    if (estCoupValide(c)){
      jouerCoup(c);
      statut = 1;
      libererCoup(c);
    }else{
      printf("Coup invalide !!!\n");
      libererCoup(c);
    }
  }

  return 1;
}



