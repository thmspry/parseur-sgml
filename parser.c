#include <stdio.h>
#include "automate.h"


int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez indiquez le chemin vers le fichier à parser en argument.\n");
        return 0;
    }
    if (argc > 2) {
        printf("Les arguments suivant le chemin vers le nom du fichier ne peuvent pas être pris en compte.\n");
    }
    FILE *pFile;
    if ((pFile = fopen(argv[1],"rt"))) {          // Ouverture fichier, indiquez le chemin adéquat
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
