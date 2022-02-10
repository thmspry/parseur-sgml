#include "automate.h"
#include <stdio.h>


/* Determine si le caractère passé en paramètre est une lettre de l'alphabet (minuscule ou majuscule) 
 - param : 
        - char c : un caractère 
 - return : 
        - 1 si c'est une lettre
        - 0 sinon*/
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
    
    while(!feof(pFile) && currentEtat != EtatErreur) {      // Tant que le fichier n'est pas fini
        c = fgetc(pFile);                                   // On récupère le caractère courant
        // --------- Debug --------- 
        //printf("Caractere '%c' || Etat %d \n", c, currentEtat);
        switch(currentEtat) {
            case EtatDebut:
                if (c == '<') {
                    currentEtat = ChevronG;
                } else {
                    currentEtat = EtatDebut;
                }
                break; 

            case ChevronG:
                if (is_letter(c)) {
                    currentEtat = NomBalise;
                    break;
                }
                if (c == '/') {
                    currentEtat = NomBaliseFermante1;
                    break;
                }
                currentEtat = EtatErreur;
                break;
                

            case NomBalise:
                if (c == '>') {
                    currentEtat = EtatDebut;
                    break;
                }
                if (is_separator(c)) {
                    currentEtat = EspaceApresNomBalise;
                    break;
                }

                if (is_letter(c) || is_number(c)) {
                    currentEtat = NomBalise;
                    break;
                }
                currentEtat = EtatErreur;
                break;

            case EspaceApresNomBalise:
                if (c == '>') {
                    currentEtat = EtatDebut;
                    break;
                }

                if (is_separator(c)) {
                    currentEtat = EspaceApresNomBalise;
                    break;
                }

                if (is_letter(c)) {
                    currentEtat = NomAttribut;
                    break;
                }
                currentEtat = EtatErreur;
                break;

            case NomAttribut:
                if (c == '=') {
                    currentEtat = EgalAttribut;
                    break;
                }

                if (is_letter(c) || is_number(c) || c == '-') {
                    currentEtat = NomAttribut;
                    break;
                }
                currentEtat = EtatErreur;
                break;
            
            case EgalAttribut:
                if (c == '"') {
                    currentEtat = DoubleQuoteAttribut1;
                    break;
                }
                if (c == '\'') {
                    currentEtat = SimpleQuoteAttribut1;
                    break;
                }
                if (is_letter(c)) {
                    currentEtat = ValeurBruteAttribut;
                    break;
                }
                currentEtat = EtatErreur;
                break;

            case ValeurBruteAttribut:

                if (c == '>') {
                    currentEtat = EtatDebut;
                    break;
                }

                if (is_separator(c)) {
                    currentEtat = SimpleQuoteAttribut1;
                    break;
                }
                
                if (is_letter(c) || is_number(c)) {
                    currentEtat = ValeurBruteAttribut;
                    break;
                }
                currentEtat = EtatErreur;
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
                    break;
                }

                if (is_separator(c)) {
                    currentEtat = EspaceApresNomBalise;
                    break;
                }
                
                currentEtat = EtatErreur;
                break;

            case SimpleQuoteAttribut2:
                if(c == '>') {
                    currentEtat = EtatDebut;
                    break;
                }

                if (is_separator(c)) {
                    currentEtat = EspaceApresNomBalise;
                    break;
                }

                return -1;

            case NomBaliseFermante1:
                if (is_letter(c)) {
                    currentEtat = NomBaliseFermante2;
                    break;
                }
                currentEtat = EtatErreur;
                break;

            case NomBaliseFermante2:
                if(c == '>') {
                    currentEtat = EtatDebut;
                    break;
                }
                
                if (is_letter(c) || is_number(c)) {
                    currentEtat = NomBaliseFermante2;
                    break;
                }
                
                currentEtat = EtatErreur;
                break;

            default:
                currentEtat = EtatErreur;
                break;
        
        }
    }
    
    return currentEtat == EtatDebut;    // Le fichier est bon si la dernière transition effectuée est celle du chevreron droit
}