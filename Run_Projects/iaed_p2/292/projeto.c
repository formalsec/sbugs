#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "functions.h"
#define MAX_buffer 3075	/*1+1023*3+1+1*/
#define MAX_rest   3074 /*1023*3+1+1*/
#define TeamsHTsize 20287
#define GamesHTsize 20287


int main(){
	int M, N;
/*counter-variavel que guarda o numero do comando introduzido -> (NL)*/
	int x = 0, counter = 1, Nequipas = 0, max = 0;
	char buffer[MAX_buffer], comando, rest[MAX_rest];
/* hash table dos jogos*/
	games *games_list;
/* hash table das equipas */
	teams *lista_equipas;
	
/*pointer do primeiro elemento da linked list*/struct Jogos*first=NULL;
/*pointer do ultimo elemento da linked list*/struct Jogos *top= NULL;

/*false_t-struct que devolvo em vez de FALSE quando procuro uma equipa*/
	struct Equipas *false_t=(struct Equipas*)malloc(sizeof(struct Equipas));
/*false_g-struct que devolvo em vez de FALSE quando procuro um jogo*/
	struct Jogos *false_g = (struct Jogos*)malloc(sizeof(struct Jogos));
	
/* Inicializacao das constantes para a funcao hash*/	
	M = GamesHTsize; N=TeamsHTsize;

/* none/NONE-utilizo como flags devolvido pelas funcoes que procuram
 * jogo/equipa no caso destas nao existirem*/
	false_t->ID = malloc((strlen("NONE")+1)*sizeof(char));
	strcpy(false_t->ID, "NONE");
	false_g->ID = malloc((strlen("none")+1)*sizeof(char));
	strcpy(false_g->ID, "none");
	
/*Inicilizacao das tabelas dinamicas dos jogos e equipas*/	
	lista_equipas = malloc(N*sizeof(teams));
	games_list = malloc(M*sizeof(games));
	for(x=0; x<M; x++) games_list[x]=NULL;
	for(x=0; x<N; x++) lista_equipas[x]=NULL;
	
        /*leitura do primeiro comando*/
	scanf("%[^\n]",buffer);
	sscanf(buffer, "%c%*c%[^\n]", &comando, rest);
	
    while (comando != 'x'){
		if(comando=='a'){
			Inseret(games_list, &first, rest, M, counter,lista_equipas,\
			 false_t, &top, false_g, N);} 
		if(comando=='A'){ x =InseretEquipa(lista_equipas, rest, N, \
			counter, false_t);
			if(x==1) ++Nequipas;}
		if(comando=='p'){encontraJogo(games_list,rest,true, M, counter,\
		 false_g);}
		if(comando=='P') encontraEquipa(lista_equipas, rest, true, N, \
		counter, false_t);
		if(comando=='l') showByDate(first, counter);
		if(comando=='r') {deleteGame(games_list, &first, rest,\
		lista_equipas, false_t, M, counter, false_g, &top, N);}
		if(comando=='s') {alteraScore(games_list, rest, M, counter, \
		lista_equipas, false_t, N);}
		if(comando=='g') {max = FindMax(lista_equipas, N); 
			lista(lista_equipas, Nequipas, counter, max, N); }
		if(comando == 'w') {max = FindMax(lista_equipas, N);
			printf("<%d>\n", max);}
	
	++counter;	
	/*leitura do proximo comando*/		
	scanf(" %[^\n]",buffer);
	sscanf(buffer, "%c%*c%[^\n]", &comando, rest);	
	}
	
	/*da free em tudo que nao foi fechado*/
	freeStruct(&first, lista_equipas, N);
	free(false_t->ID); free(false_t);
	free(false_g->ID); free(false_g);
	free(lista_equipas);
	free(games_list);
	return 0;
	}
