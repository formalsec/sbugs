#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "struct.h"
#include "add.h"
#include "list.h"
#include "search.h"
#include "remove.h"
#include "change.h"
#include "champs.h"

#define MAXC 1024
#define T_SIZE 1999 /*Constante utilizada para fazer o hash na hashtable.*/


/*VARIAVEIS GLOBAIS*/
hashTable games[T_SIZE];
hashTable teams[T_SIZE];
int counter = 0;


/*Funcao que recebe uma hashtable e a inicia a NULL.*/
hashTable *startHash(hashTable *hash){

	int i;

	for(i = 0; i < T_SIZE; i++){
		hash[i].head = NULL;
	}

	return hash;
}


/*Funcao que inicia uma lista a NULL*/
list *startList(){

	list *ls;
	ls = can_fail_malloc(sizeof(list));
	ls->head = ls->end = NULL;

	return ls;
}


/*Funcao que recebe um nome e com base nos seus caracteres o coloca 
* na hashtable no indice calculado atraves da divisao pelo numero primo T_SIZE.*/
int getHashKey(char name[MAXC]){

	int i, res = 0;
	int len = strlen(name);

	for(i = 0; i < len; i++){
		res += name[i];
	}

	return res % T_SIZE;
}


/*Estas duas funcoes recebem um nome e retornam um no da hashtable
* que possui esse nome fornecido.*/
hashNode *getNodeGames(char n_name[MAXC]){

	int i = getHashKey(n_name);
	hashNode *aux = games[i].head;

	while(aux != NULL){
		if(strcmp(n_name, aux->point->name) == 0){
			return aux;
		}

		aux = aux->next;
	}

	return NULL;
}

hashNode *getNodeTeams(char n_name[MAXC]){

	int i = getHashKey(n_name);
	hashNode *aux = teams[i].head;

	while(aux != NULL){
		if(strcmp(n_name, aux->point->name) == 0){
			return aux;
		}

		aux = aux->next;
	}

	return NULL;
}


/*Funcao que trata da libertacao de memoria alocada a uma lista.
* caso a flag esteja a 0 elimina a lista de jogos e caso 1 a de equipas.*/
void deleteList(list *ls, int flag){

	int i;

	for(i = 0; i < T_SIZE; i++){
		switch(flag){
			case 0:
				while(games[i].head != NULL){
					eraseGames(ls, games[i].head->point->name);
					i++;
				}
				break;

			case 1:
				while(teams[i].head != NULL){
					eraseTeams(ls, teams[i].head->point->name);
					i++;
				}
				break;
		}
	}
}


int main(){

	list *lGames, *lTeams;

	char cmd = '\0';

	lGames = startList();
	lTeams = startList();

	startHash(games);
	startHash(teams);

	while(cmd != 'x'){
        cmd = getchar();

        switch(cmd){
			case 'a':
				counter++;
				addGame(lGames, lTeams);
				break;

			case 'A':
				counter++;
				addTeam(lTeams);
				break;

			case 'l':
				counter++;
				listGames(lGames);
				break;

			case 'p':
				counter++;
				searchGame();
				break;

			case 'P':
				counter++;
				searchTeam();
				break;

			case 'r':
				counter++;
				removeGame(lGames, lTeams);
				break;

			case 's':
				counter++;
				changeScore(lGames, lTeams);
				break;

			case 'g':
				counter++;
				findChamps(lTeams);
				break;
		}
	}
	deleteList(lGames, 0);
	deleteList(lTeams, 1);
	free(lGames);
	free(lTeams);

	return 0;
}