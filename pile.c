#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.h"

/* Initialise la pile
 - param : 
        - Pile *pile : pointeur de la structure pile
*/
void pile_init(Pile *pile) {
  pile->top = -1;
}

/* Donne l'élement au sommet de la pile 
 - param : 
        - Pile *pile : pointeur de la structure pile
 - return : 
        - la valeur (char*) en haut de la pile
*/
char* pile_top(Pile *pile) {
  if (pile_taille(pile) == 0) {
    printf("ERREUR : La pile est vide, pop impossible\n");
    return "";
  } else {
    return pile->tab[pile->top];
  }
}

/* Supprime l'élement au sommet de la pile
 - param : 
        - Pile *pile : pointeur de la structure pile
 - return : 
        - la valeur (char*) supprimée
*/
char* pile_pop(Pile *pile) {
  if (pile_taille(pile) > 0) {
    char *ptr_char;
    ptr_char = pile_top(pile);
    strcpy(ptr_char, "");       // Copie le contenu de la chaine du 2eme parametre dans le 1er
    pile->top--;
    return ptr_char;
  } else {
    printf("ERREUR : La pile est vide, pop impossible\n");
    return "";
  }
}

/* Empile un élement au haut de la pile
 - param : 
        - Pile *pile : pointeur de la structure pile
        - char *new_el : oiture sur un tableau de char (string)
 - return : 
        - la valeur (char*) en haut de la pile
*/
void pile_push(Pile *pile, char *new_el) {
  if (pile_taille(pile) < TAILLE_PILE) {
    pile->top++;
    strcpy(pile_top(pile), new_el);     // Copie le contenu de la chaine du 2eme parametre dans le 1er
  } else {
    printf("ERREUR : La pile est pleine, push impossible\n");
  }
}

/* Donne la taille de la pile
 - param : 
        - Pile *pile : pointeur de la structure pile
 - return : 
        - valeur de la taille de la pile
*/
int pile_taille(Pile *pile) {
  return ((pile->top) + 1);
}

/* Affiche la pile
 - param : 
        - Pile *pile : pointeur de la structure pile
        - char *new_el : oiture sur un tableau de char (string)
 - return : 
        - la valeur (char*) en haut de la pile
*/
void pile_afficher(Pile *pile) {
  printf("[ ");
  int taille = pile_taille(pile);

  for(int i = 0; i < taille; i++) {
    printf("%s", pile->tab[i]);
    if (i < taille - 1) printf(", ");
  }
  printf(" ]\n");
}
