#define TAILLE_PILE 20
#define TAILLE_CHAINE 20

typedef struct {
    char tab[TAILLE_PILE][TAILLE_CHAINE];
    int top;
} Pile;

void pile_init(Pile *pile);
char* pile_pop(Pile *pile);
char* pile_top(Pile *pile);
void pile_push(Pile *pile, char *elmt);
int pile_taille(Pile *pile);
void pile_afficher(Pile *pile);