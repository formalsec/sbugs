#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "functions.h"

/*<====CONJUNTO DE FUNCOES QUE LEEM O CONTEUDO DAS HASH TABLES====>*/

/*funcao que cria uma chave para hash table*/
long int hash(char palavra[],int M){
	int i=0, sum=0;
	while(palavra[i]!='\0'){
		sum+=3^(i+3)*(int)palavra[i];
		++i;
		}
	sum = sum%M;
	return sum;}

		/*FUNCAO QUE PROCURA NA HASH TABLE DOS JOGOS*/
/*caso o jogo existe retorna pointer para esse jogo, caso contrario 
 * devolve pointer para um jogo de referencia (false_g)*/
struct Jogos *encontraJogo(struct Jogos **jogos,char nome[],bool print,\
 int M, int NL,struct Jogos *false_g){
	struct Jogos *next;
	int x = hash(nome, M);
	next = jogos[x];
	/*procura entre jogos com mesma hash key*/
	while(next != NULL){
		if(!strcmp(nome, next->ID)){
			if(print){printf("%d %s %s %s %d %d\n",\
			NL, next->ID, next->team_1, next->team_2, \
			next->score1, next->score2);}
			return next;}
		next = next-> next_tabela;}
	if(print)printf("%d Jogo inexistente.\n", NL);
	return false_g;
	}

		/*FUNCAO QUE PROCURA NA HASH TABLE DAS EQUIPAS*/
/*caso o jogo existe retorna pointer para tal equipa, caso negativo
 * devolve pointer para uma equipa de referencia (false_t)*/
struct Equipas *encontraEquipa(struct Equipas **Team, char nome[],\
bool print, int N, int NL, struct Equipas *false_t){
	struct Equipas *nt;
	int x = hash(nome, N);
	nt = Team[x];
	/*procura entre equipas com mesma hash key*/
	while(nt != NULL){
		if(!strcmp(nome, nt->ID)){
			if(print){printf("%d %s %d\n",\
			NL, nt->ID, nt->wins);}
			return nt;}
		nt = nt-> next;}
	if(print)printf("%d Equipa inexistente.\n", NL);
	return false_t;
	}
	
/* lista pela ordem de insercao todos os jogos */
void showByDate(struct Jogos *jogos, int NL) 
{ 
  while (jogos != NULL){ 
     printf("%d %s %s %s %d %d\n",NL, jogos->ID, jogos->team_1, \
     jogos->team_2, jogos->score1, jogos->score2); 
     jogos = jogos->next;}
  return; 
}

/*func auxiliar para qsort utilizado na funcao <lista>"*/
int compara_palavras(const void * team_A, const void * team_B ) {
    const char *teamA = *(const char**)team_A;
    const char *teamB = *(const char**)team_B;
    return strcmp(teamA,teamB);}


/*funcao que lista as equipas que teem maior numero de vitorias */
void lista(struct Equipas **elemento, int Nequipas,int NL,int max,int N) 
{ 
	int i, p=0, count = 0;
	/*tabela de char dunamica para guardar temporariamente os nomes de
	 * equipas com maior numero de vitorias*/
	char **tabela;
	
	/*caso nao existe nenhuma equipa na hash table*/
	if(Nequipas==0) return;
	
	tabela = (char**)can_fail_malloc(Nequipas*sizeof(char*));
    for(i = 0; i < N; i++)
    {
		if(elemento[i] != NULL){
			struct Equipas *temp = elemento[i];
			while(temp!= NULL)
			{
				/*selecao de equipas com maior numero de wins*/
				if((*temp).wins == max){
					tabela[p]=can_fail_malloc((strlen((*temp).ID)+1)*\
						sizeof(char));
					strcpy(tabela[p],(*temp).ID);
					++count;
					++p;
					temp = temp->next;}
				else temp = temp->next;
			}
	    }
    }
    /*organizacao das equipas pela ordem lexicografica*/
    qsort(tabela, count, sizeof(char *), compara_palavras);
    
    printf("%d Melhores %d\n", NL, max);
    for(i=0; i<count; i++){
		printf("%d * %s\n",NL, tabela[i]);}
		
    for(i=0; i<count; i++) free(tabela[i]);
    free(tabela);
}


/* 	Itera atraves de todas equipas na hash table e encontra o numero de
 *  maximas vitorias*/
int FindMax(struct Equipas **games_list, int N)
{
    int i, max = 0;
    for(i = 0; i < N; i++)
    {
		if(games_list[i] != NULL){
			struct Equipas *temp = games_list[i];
			while(temp!= NULL){
				if((temp->wins)> max) max=temp->wins;
				temp = temp->next;}
        }
    }
    return max;
}
