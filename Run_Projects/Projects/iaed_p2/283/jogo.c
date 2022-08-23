#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"

/*Liberta o jogo em causa*/

void free_jogo(Jogo* j){
	free(j->nome_jogo);
	free(j->equipa_1);
	free(j->equipa_2);
	free(j);
}


/*cria o jogo em causa recebendo tudo aquilo que o caracteriza */ 

Jogo *cria_jogo(char nome_jogo[],char equipa_1[],char equipa_2[],int score_1,int score_2){
	Jogo *novo_jogo;
	novo_jogo = malloc(sizeof(Jogo));
	novo_jogo->nome_jogo = malloc( sizeof(char)*(strlen(nome_jogo)+1));
	novo_jogo->equipa_1 = malloc( sizeof(char)*(strlen(equipa_1)+1));
	novo_jogo->equipa_2 = malloc( sizeof(char)*(strlen(equipa_2)+1));
	strcpy(novo_jogo->equipa_1,equipa_1);
	strcpy(novo_jogo->equipa_2,equipa_2);
	strcpy(novo_jogo->nome_jogo,nome_jogo);
	novo_jogo->score_1 = score_1;
	novo_jogo->score_2 = score_2;
	return novo_jogo;


}

