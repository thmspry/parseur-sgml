#include <stdio.h>
#include "automate.h"


int main () {
    FILE *pFile;
    char c;
    Etats currentEtat = EtatDebut;

    if ((pFile = fopen("./data/fichier.html","rt"))) {                  // Ouverture fichier
        for (c = fgetc(pFile); !feof(pFile); c = fgetc(pFile)) {        // Pour chaque caractère
            currentEtat = automate(c, currentEtat);
            if(currentEtat == -1) {
                printf("Le fichier NE respecte PAS les normes SGML.\n");
                return -1;
            }
        }

    fclose (pFile);         // Le fichier à été entierement scanné
    } else {
        printf("Erreur d'ouverture du fichier\n");  // Si l'ouverture renvoie une erreur
    }
    printf("Le fichier respecte les normes SGML.\n"); // Aucun -1 n'a été renvoyé par l'automate
    return 0;
}
