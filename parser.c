#include <stdio.h>
#include "automate.h"


int main () {
    FILE *pFile;
    if ((pFile = fopen("./data/fichier.html","rt"))) {          // Ouverture fichier
        if (automate(pFile)) {
            printf("Le fichier respecte les normes SGML.\n");
        } else {
            printf("Le fichier NE respecte PAS les normes SGML.\n");
        }
        fclose (pFile);                     // Le fichier à été entierement scanné
    } else {
        printf("Erreur d'ouverture du fichier\n");              // Si l'ouverture renvoie une erreur
        return 0;
    }

    
    return 0;
}
