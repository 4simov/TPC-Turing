#include <stdio.h>
#include <stdlib.h>
#include "program.h"



typedef struct {
	int taille1;
	int taille2;
	char* tab1;
	char* tab2;
	int tete;
} bande;


void initialiser(bande* b){
	b->taille1=5;
	b->taille2=5;
	b->tab1=(char*)(malloc(sizeof(char)*(b->taille1)));
	b->tab2=(char*)(malloc(sizeof(char)*(b->taille2)));
	b->tete=0;
}

int lire(bande* b){
	return b->tete;
}

void ecrire_tete(bande* b,unsigned char val){
	if (b->tete<0){
		b->tab1[-b->tete-1]=val;
	} 
	else {
		b->tab2[b->tete]=val;
	}
}
void agrandirdroite(bande* b){
	b->tab2=(char*)(realloc(b->tab2,sizeof(char)*(b->taille2+10)));
	b->taille2=b->taille2+10;
}
void agrandirgauche(bande* b){
	b->tab1=(char*)(realloc(b->tab1,sizeof(char)*(b->taille1+10)));
	b->taille1=b->taille1+10;
}
void gauche(bande* b){
	b->tete--;
	if(-b->tete-1 >= b->taille1)
		agrandirgauche(b);
}
void droite(bande* b){
	b->tete++;
	if(b->tete >= b->taille2)
		agrandirdroite(b);
}
void _affiche( bande* b)
{
	int i=0;
	printf(" ");
	for (i=b->taille1-1;i>=0;i--){
		if( i == b->tete){
			printf("[");
		}
		if (b->tab1[i]==0){
			printf("-");
		}
		else {
			printf("%d",b->tab1[i]);
		}
		if( i == b->tete){
			printf("]");
		}
		printf("  ");
	}
	printf("||");
	printf(" ");
	
	for (i=0;i<b->taille2;i++){
		if( i == b->tete){
			printf("[");
		}
		if (b->tab2[i]==0){
			printf("-");
		}
		else {
			printf("%d",b->tab2[i]);
		}	
		if( i == b->tete){
			printf("]");
		}
		printf("  ");
		}
	printf("\n");
}
void execute_action(unsigned int action, bande* ba)
{ 
	unsigned int a=(action>>6);
	unsigned int b=(action>>5) & 0b0001;
	unsigned int c=(action>>3) & 0b000011;
	//unsigned int d =(action>>2) &0b0000001;
	//unsigned int e = action & 0b000000011;
	
	ecrire_tete( ba, b);
	
	if (c==0b10){
		gauche(ba);
	}

	else if (c==0b01){
		droite(ba);
	}
		
	ecrire_etat(a);
}


void run(bande* b) {
	int n=0;
	_affiche(b);
	while(!test_stop(lire_etat())) {
		unsigned int act = lire_prog(lire_etat(),lire(b),lire(b));
		execute_action(act,b);
		n++;
		printf("Etape %d\n",n);
		_affiche(b);
		getchar();
	}
}

int main()
{
	bande b;
	initialiser(&b);
	_affiche(&b);
    init();
    printf("Simulation d'une machine de Turing a 2 bandes\n");
    run(&b);
    printf("Fin d'execution\n");
    return 0; 
}

/// 00 01 01 02 03 05 08 13 07 06
/// 13 05 04 09 13 08 07 01 08 09
/// 03 12 01 13 00 13 13 12 11 09
/// 06 01 07 08 01 09 10 05 01 06
/// 07 13 06 05 11 02 13 01

