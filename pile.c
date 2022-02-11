#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.h"

void pile_init(Pile *pile) {
  pile->top = -1;
}

char* pile_top(Pile *pile) {
  if (pile_taille(pile) == 0) {
    printf("ERREUR : La pile est vide, pop impossible\n");
    return "";
  } else {
    return pile->tab[pile->top];
  }
}

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
    
void pile_push(Pile *pile, char *new_el) {
  if (pile_taille(pile) < TAILLE_PILE) {
    pile->top++;
    strcpy(pile->tab[pile->top], new_el); 
  } else {
    printf("ERREUR : La pile est pleine, push impossible\n");
  }
}

int pile_taille(Pile *pile) {
  return ((pile->top) + 1);
}

void pile_afficher(Pile *pile) {
  printf("[ ");
  int taille = pile_taille(pile);
  for(int i = 0; i < taille; i++) {
    printf("%s", pile->tab[i]);
    if (i < taille - 1) {
      printf(", ");
    }
  }
  printf(" ]\n");
}
