
#define NetatsMAX 100  // Nombre d'états

// Affiche un message d'erreur et arrête le programme.
void ERREUR(char* txt);

// Initialise les bandes, les positions des têtes, le programme et l'état courant.
void init();

// Retourne l'état courant.
unsigned int lire_etat();

// Modifie l'état courant.
void ecrire_etat(unsigned int e);

// Retourne un entier représentant l'action que le programme doit exécuter pour
// l'état courant (etat = 0..Netats-1) et les valeurs lues par les deux têtes
// (val_t1 = 0 ou 1, val_T2 = 0 ou 1).
unsigned int lire_prog(unsigned int etat, unsigned char val_t1, unsigned char val_t2);

// Affichage du programme en représentation machine
void test();

// Détermine si un état est l'état stop.
int test_stop(unsigned etat);
