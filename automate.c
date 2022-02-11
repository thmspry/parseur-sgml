#include <string.h>
#include "automate.h"
#include "pile.h"


/* Determine si le caractère passé en paramètre est une lettre de l'alphabet (minuscule ou majuscule) 
 - param : 
        - char c : un caractère 
 - return : 
        - 1 si c'est une lettre
        - 0 sinon
*/
int is_letter(char c) {
    return (c == 'a' || c == 'b' || c == 'c' || c == 'd' || 
            c == 'e' || c == 'f' || c == 'g' || c == 'h' || 
            c == 'i' || c == 'j' || c == 'k' || c == 'l' || 
            c == 'm' || c == 'n' || c == 'o' || c == 'p' || 
            c == 'q' || c == 'r' || c == 's' || c == 't' || 
            c == 'u' || c == 'v' || c == 'w' || c == 'x' || 
            c == 'y' || c == 'z' ||
            c == 'A' || c == 'B' || c == 'C' || c == 'D' || 
            c == 'E' || c == 'F' || c == 'G' || c == 'H' || 
            c == 'I' || c == 'J' || c == 'K' || c == 'L' || 
            c == 'M' || c == 'N' || c == 'O' || c == 'P' || 
            c == 'Q' || c == 'R' || c == 'S' || c == 'T' || 
            c == 'U' || c == 'V' || c == 'W' || c == 'X' || 
            c == 'Y' || c == 'Z');
}

/* Determine si le caractère passé en paramètre est un chiffre
 - param : 
        - char c : un caractère 
 - return : 
        - 1 si c'est un chiffre
        - 0 sinon
*/
int is_number(char c) {
    return (c == '0' || c == '1' || c == '2' || 
            c == '3' || c == '4' || c == '5' || 
            c == '6' || c == '7' || c == '8' || c == '9');
}

/* Determine si le caractère passé en paramètre est un separateur d'attribut valable pour un fichier SGML
 - param : 
        - char c : un caractère 
 - return : 
        - 1 si c'est un separateur
        - 0 sinon
*/
int is_separator(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

/* Détermine si un fichier respecte les normes SMGL
 - param :
        - FILE *pfile : le contexte du fichier texte déjà ouvert
 - return :
        - 0 si le fichier respecte les normes SGML
        - tout autre valeur sinon
*/
int automate(FILE *pFile) {

    Etats currentEtat = EtatDebut;
    char c;
    char cur_nom_balide[TAILLE_CHAINE];
    int compteur_chaine = 0;
    Pile pile_balise;
    pile_init(&pile_balise);
    
    while(!feof(pFile) && currentEtat != EtatErreur) {      // Tant que le fichier n'est pas fini
        c = fgetc(pFile);                                   // On récupère le caractère courant
        // --------- Debug --------- 
        // printf("Caractere '%c' || Etat %d \n", c, currentEtat);
        switch(currentEtat) {
            /*  On tombe dans cet état si le caractère scanné ne permet de faire aucun trainsition
                de puis son état actuel
            */
            case EtatErreur:    
                return 0;
                break;

            case EtatDebut:
                if (c == '<') {
                    currentEtat = ChevronG;
                } else {
                    currentEtat = EtatDebut;
                }
                break; 

            case ChevronG:
                if (is_letter(c)) {
                    cur_nom_balide[compteur_chaine] = c;
                    compteur_chaine++;
                    currentEtat = NomBalise;
                } else if (c == '/') {
                    currentEtat = NomBaliseFermante1;
                } else {
                    currentEtat = EtatErreur;
                }
                break;
                

            case NomBalise:
                if (c == '>' || is_separator(c)) {          // Fin du nom de la balise
                    cur_nom_balide[compteur_chaine] = '\0';     // Caractere de fin de chaine
                    compteur_chaine = 0;                        // Remise à 0 pour le prochain nom de balise
                    pile_push(&pile_balise, cur_nom_balide);    // Ajout de cette balise dans la pile
                    if (c == '>') {
                        currentEtat = EtatDebut;
                    } else {
                        currentEtat = EspaceApresNomBalise;
                    }
                } else if (is_letter(c) || is_number(c)) {
                    cur_nom_balide[compteur_chaine] = c;        // Completion de le nom de la balise avec le caractère courant
                    compteur_chaine++;
                    currentEtat = NomBalise;

                } else {
                    currentEtat = EtatErreur;
                }
                break;

            case EspaceApresNomBalise:
                if (c == '>') {
                    currentEtat = EtatDebut;
                } else if (is_separator(c)) {
                    currentEtat = EspaceApresNomBalise;
                } else if (is_letter(c)) {
                    currentEtat = NomAttribut;
                } else {
                    currentEtat = EtatErreur;
                }
                break;

            case NomAttribut:
                if (c == '=') {
                    currentEtat = EgalAttribut;
                } else if (is_letter(c) || is_number(c) || c == '-') {
                    currentEtat = NomAttribut;
                } else {
                    currentEtat = EtatErreur;
                }
                break;
            
            case EgalAttribut:
                if (c == '"') {
                    currentEtat = DoubleQuoteAttribut1;
                } else if (c == '\'') {
                    currentEtat = SimpleQuoteAttribut1;
                } else if (is_letter(c)) {
                    currentEtat = ValeurBruteAttribut;
                } else {
                    currentEtat = EtatErreur;
                }
                break;

            case ValeurBruteAttribut:

                if (c == '>') {
                    currentEtat = EtatDebut;
                } else if (is_separator(c)) {
                    currentEtat = SimpleQuoteAttribut1;
                    break;
                } else if (is_letter(c) || is_number(c)) {
                    currentEtat = ValeurBruteAttribut;
                    break;
                } else {
                    currentEtat = EtatErreur;
                }
                break;

            case DoubleQuoteAttribut1:
                if (c != '"') {
                    currentEtat = DoubleQuoteAttribut1;
                } else {
                    currentEtat = DoubleQuoteAttribut2;
                }
                break;

            case SimpleQuoteAttribut1:
                if (c != '\'') {
                    currentEtat = SimpleQuoteAttribut1;
                } else {
                    currentEtat = SimpleQuoteAttribut2;
                }
                break;

            case DoubleQuoteAttribut2:
                if(c == '>') {
                    currentEtat = EtatDebut;
                } else if (is_separator(c)) {
                    currentEtat = EspaceApresNomBalise;
                } else {
                    currentEtat = EtatErreur;
                }
                break;

            case SimpleQuoteAttribut2:
                if(c == '>') {
                    currentEtat = EtatDebut;
                } else if (is_separator(c)) {
                    currentEtat = EspaceApresNomBalise;
                } else {
                    currentEtat = EtatErreur;
                }
                break;

            case NomBaliseFermante1:
                if (is_letter(c)) {
                    cur_nom_balide[compteur_chaine] = c;
                    compteur_chaine++;
                    currentEtat = NomBaliseFermante2;
                } else {
                    currentEtat = EtatErreur;
                }
                break;

            case NomBaliseFermante2:
                if(c == '>') {          // Fin du nom de la balise
                    cur_nom_balide[compteur_chaine] = '\0';
                    compteur_chaine = 0;
                    char *top = pile_top(&pile_balise);
                    
                    /*  On regarde le haut de la pile pour voir si la dernier balise ouverte est bien celle
                        qu'on essaye de fermer */
                    if(strcmp(top, cur_nom_balide) == 0) {  // Si les chaine sont les mêmes
                        pile_pop(&pile_balise);
                        currentEtat = EtatDebut;
                    } else {
                        currentEtat = EtatErreur;
                    }
                } else if (is_letter(c) || is_number(c)) {
                    cur_nom_balide[compteur_chaine] = c;
                    compteur_chaine++;
                    currentEtat = NomBaliseFermante2;
                } else {
                    currentEtat = EtatErreur;
                }
                break;

            default:
                currentEtat = EtatErreur;
                break;
        
        }
    }
    /*  Le fichier est bon si la dernière transition effectuée est celle du chevreron droit
        et que la pile de balise est vide (toutes la balises ont été fermées)
    */
    return currentEtat == EtatDebut && pile_taille(&pile_balise) == 0;
}