#include <stdio.h>
#include <stdlib.h>

#include "turing.h"

void execute_action(unsigned int action)
{ unsigned int a=(action>>6);
	unsigned int b=(action>>5) & 0b0001;
	unsigned int c=(action>>3) & 0b000011;
	unsigned int d =(action>>2) &0b0000001;
	unsigned int e = action & 	 0b000000011;
	
	
	ecrire_tete(1,b);
	
	ecrire_tete(2,d);
	
	if (c==0b10){
		gauche(1);}

	else if (c==0b11){
		droite(1);}
		
	if (e==0b10){
		gauche(2);}

	else if (e==0b11){
		droite(2);}
		
	ecrire_etat(a);
}

void run()
{
    int n = 0;
    affiche();
    while(lire_etat()!=(Netats-1))
    {
        unsigned int act = lire_prog(lire_etat(), lire_tete(1), lire_tete(2));
        execute_action(act);
        n++; printf("Etape %d\n",n);
        affiche();
        getchar();
    }
}

int main()
{
    printf("Simulation d'une machine de Turing a 2 bandes\n");
    run();
    printf("Fin d'execution\n");
    return 0;
}

/// 00 01 01 02 03 05 08 13 07 06
/// 13 05 04 09 13 08 07 01 08 09
/// 03 12 01 13 00 13 13 12 11 09
/// 06 01 07 08 01 09 10 05 01 06
/// 07 13 06 05 11 02 13 01

