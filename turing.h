#ifndef TURING_H_INCLUDED
#define TURING_H_INCLUDED

#define Tbande 16 // Taille des bandes
#define Netats 8  // Nombre d'états

// Affiche un message d'erreur et arrête le programme.
void ERREUR(char* txt);

// Initialise les bandes, les positions des têtes, le programme et l'état courant.
void init();

// Retourne l'état courant.
unsigned int lire_etat();

// Modifie l'état courant.
void ecrire_etat(unsigned int e);

// Déplace à droite la tête indiquée (tete = 1 ou 2).
void droite(unsigned char tete);

// Déplace à gauche la tête indiquée (tete = 1 ou 2).
void gauche(unsigned char tete);

// Lit la valeur située en face de la tête indiquée (tete = 1 ou 2). 
unsigned char lire_tete(unsigned char t);

// Modifie la valeur (0 ou 1) située en face de la tête indiquée (tete = 1 ou 2).
void ecrire_tete(unsigned char t, unsigned char val);

// Retourne un entier représentant l'action que le programme doit exécuter pour
// l'état courant (etat = 0..Netats-1) et les valeurs lues par les deux têtes
// (val_t1 = 0 ou 1, val_T2 = 0 ou 1).
unsigned int lire_prog(unsigned int etat, unsigned char val_t1, unsigned char val_t2);

// Affiche la configuration actuelle de la machine.
void affiche();

#endif // TURING_H_INCLUDED
