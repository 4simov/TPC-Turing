#include <stdio.h>
#include <stdlib.h>
#include "program.h"


///----------- programme de démonstration au format humain ------------

unsigned NDEMO = 6;
const char* DEMO[] =
{
	"00: 00->(01)0G0G 01->(00)1D0D 10->(00)0D1D 11->(00)1D1D",
	"01: 00->(02)0D0D 01->(01)0G1G 10->(01)1G0G 11->(01)1G1G",
	"02: 00->(03)0X0X 01->(03)0X1X 10->(02)1D0X 11->(02)1D1X",
	"03: 00->(04)0G0G 01->(03)1D1D 10->(05)1G0X 11->(05)1G1X",
	"04: 00->(00)0D0D 01->(04)0X1G 10->(04)1G0X 11->(04)1G1G",
	"05: 00->(03)0D0X 01->(03)0D1X 10->(05)0G0X 11->(05)0G1X"
};

///-------------- programme au format machine et état -----------------

unsigned int etat = 0;

// représentation d'une ligne de programme contenant 4 actions
// soit une action pour chaque couple de valeurs lues pas les têtes
typedef struct
{
	unsigned etat;      // état associé à la ligen de programme
	unsigned action[4]; // actions pour tête1/tête2 = 00, 01, 10, 11
}prline;

// représentation du programme de la machine de Turing à deux bandes
typedef struct
{
	unsigned netats;       //nombre d'états utilisés
	prline tab[NetatsMAX]; //lignes associées aux états
}program;
program PROG;  // Programme à simuler en représentation machine
prline DEST;
///----------- déclarations des fonctions à compléter -------------------

unsigned str2u(const char* s, unsigned char n);
unsigned decode(const char* code_action);
void chargeProg(program* p);

///--------- fonctions permettant la compilation du programme ---------

// conversion d'un caractère ascii représentant un chiffre en la
// valeur entière correspondante.
// Par exemple '7' est transformé en 7
unsigned char char2u(char c)
{
	return c-'0';
}

// conversion d'un caractère en une direction avec la convention
// suivante : 'D' -> 0b01, 'G' -> 0b10, autres valeurs -> 0b00.
unsigned char char2dir(char c)
{
	if(c=='D') return 0b01;
	else if(c=='G') return 0b10;
	else return 0b00;
}

// compilation d'une ligne de programme :
// line désigne la ligne à compiler
// dest désigne l'emplacement du résultat de la compilation
// exemple d'une ligne (exactement 55 caractères) :
// "02: 00->(03)0X0X 01->(03)0X1X 10->(02)1D0X 11->(02)1D1X"
void compileLigne(const char* line, prline* dest)
{
	dest->etat = str2u(line,2);
	dest->action[0] = decode(line+8);
	dest->action[1] = decode(line+21);
	dest->action[2] = decode(line+34);
	dest->action[3] = decode(line+47);
}

///---------- Fonction d'accès au programme et à l'état courant -------

void ERREUR(char* txt)
{
    printf("\n");
    printf("%s",txt);
    printf("\n");
    exit(1);
}

void init()
{
	printf("Chargement du programme...\n");
    chargeProg(&PROG);
    printf("Programme chargé\n");
}

unsigned int lire_etat()
{
    return etat;
}

void ecrire_etat(unsigned int e)
{
    etat = e;
}

int test_stop(unsigned etat)
{
	return etat == PROG.netats;
}

///-------------- Fonctions de mise au point --------------------------

void printBin(unsigned val, int n)
{
	int i;
	for(i=1<<(n-1); i!=0; i=i>>1)
	{
		printf("%d",!((val&i)==0));
	}
}

void printProg(program* p)
{
	int n=p->netats;
	int i, j;// erreur de compilation lorsqu'ils sont déclaré dans la boucle "program.c:125:2: error: ‘for’ loop initial declarations are only allowed in C99 or C11 mode"+++++++++++++++++
	printf("Nombre d'etats : %d\n",n);
	for(i=0; i<n; i++)
	{
		printf("%02d : ",i);
		for(j=0; j<4; j++)
		{
			printBin(p->tab[i].action[j],13);
			printf("  ");
		}
		printf("\n");
	}
}

void test()
{
	chargeProg(&PROG);
	printProg(&PROG);
}

///------------------- FONCTIONS A COMPLETER --------------------------

// conversion en entier d'une partie de chaîne représentant un entier
// Seuls les n premiers caractères sont pris en compte.
// par exemple si la chaîne s contient "233T 5" et que n vaut 2,
// la valeur de retour est 23.
unsigned str2u(const char* s, unsigned char n)
{
	///A compléter
	int i=0;
	int p=1;
	int res=0;
	for( i=n-1; i>=0; i--) {
	res=res+char2u(s[i])*p;
	p=p*10;
	}
	return res;
}	

// décodage d'une chaîne représentant une action
// Seuls les 8 premiers caractères sont pris en compte
// exemple de chaîne à décoder : "(02)1D0X...."
// action à retourner pour cet exemple : 0b0000010101000
unsigned decode(const char* code_action)
{
	unsigned retour = 0b0;
	retour = retour | (str2u(code_action +1, 2 )<<6);
	retour = retour | (str2u(code_action+4,1)<<5);
	retour = retour | (char2dir(code_action[5]))<<3;
	retour = retour | (str2u(code_action+6,1)<<2);
	retour = retour | (char2dir(code_action[7]));
	return retour;	
}

// traduction de la représentation humaine du programme située dans DEMO en
// une représentation machine placée dans l'instance de structure program
// pointée par le paramètre p.
void chargeProg(program* p)
{
	int i=0;
	p->netats = 0;
	for(i=0; i<NDEMO; i++)
	{
		compileLigne(DEMO[i],&(p->tab[i]));
		p->netats++;
	}
}

// lecture dans le programme en représentation machine (situé dans la variable
// globale PROG) de l'action à exécuter pour l'état et les valeurs lues par les têtes
// donnés en paramètres
unsigned int lire_prog(unsigned int etat, unsigned char val_t1, unsigned char val_t2)
{
    return PROG.tab[etat].action[val_t1*2+val_t2];/// A compléter
	
}

