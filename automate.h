#include <stdio.h>
typedef enum {
    EtatDebut,
    ChevronG,
    NomBalise,
    EspaceApresNomBalise,
    NomAttribut,
    EgalAttribut,
    ValeurBruteAttribut,
    DoubleQuoteAttribut1,
    DoubleQuoteAttribut2,
    SimpleQuoteAttribut1,
    SimpleQuoteAttribut2,
    NomBaliseFermante1,
    NomBaliseFermante2,
    EtatErreur
} Etats;

int is_letter(char c);

int is_number(char c);

int is_separator(char c);

int automate(FILE *);