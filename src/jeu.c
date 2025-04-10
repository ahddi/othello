#include "../include/jeu.h"
#include "../include/ui_term.h"
#include "../include/plateau.h"

#include <stdlib.h>
#include <stdio.h>

int boucleJeu(int joueurCommence){
  plateau p = NULL;
  int tour = joueurCommence, statut = 1;
  int j = 1, o = 2;

  if (joueurCommence){
    j = 2;
    o = 1;
  }

  p = creerPlateau();
  initPlateau(p);
  while (statut){
    afficherPlateauTerminal(p);
    switch(tour){
    case 0:
      jouerOrdi(p, o);
      if (positionGagnante(p, o)){
	printf("Victoire de l'ordi !!\n");
      }
      tour++;
      break;
    case 1:
      tourJoueurTerminal(p, j);
      if (positionGagnante(p, j)){
	printf("Victoire du joueur !!\n");
      }
      tour--;
      break;
    }
  }

  libererPlateau(p);
  return 1;
}
