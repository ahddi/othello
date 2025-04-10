#include "../include/plateau.h"
#include "../include/ui_term.h"
#include "../include/jeu.h"
#include <time.h>
#include <stdlib.h>

int main(){
  srand(time(NULL));
  boucleJeu(1);
  exit(EXIT_SUCCESS);
}
