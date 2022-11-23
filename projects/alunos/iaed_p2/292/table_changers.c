#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "functions.h"
#define MAX_size 1023

/*<====CONJUNTO DE FUNCOES QUE ALTERAM O CONTEUDO DAS HASH TABLES====>*/

/* Insere na hash table dos jogos um novo jogo */
void Inseret(struct Jogos **jogos, struct Jogos** first, char rest[],\
int M,int NL, struct Equipas **equipas, struct Equipas *false_t, \
struct Jogos **top, struct Jogos *false_g, int N){
	
	int s1=0,s2=0, id = 0;
	char ID[MAX_size], t1[MAX_size], t2[MAX_size];

	struct Equipas *equipa1, *equipa2;
	struct Jogos *novoJogo;	
	struct Jogos *game,*jogo = *first;
	
	/*copia o conteudo do rest para respetivas variaveis*/
	sscanf(rest,"%[^:]%*c%[^:]%*c%[^:]%*c%d%*c%d", ID ,t1,t2, &s1, &s2);

		/*verificacao da inexistencia de jogo*/
	game = encontraJogo(jogos, ID, false, M , NL, false_g);
	if(strcmp(game->ID, "none")){printf("%d Jogo existente.\n",NL);\
		return;} /*caso o jogo existe*/
			
			/*verificacao da existencia das equipas*/
	equipa1 = encontraEquipa(equipas, t1, false, N , NL, false_t);
	if(!strcmp(equipa1->ID,"NONE")){
		printf("%d Equipa inexistente.\n",NL);return;}
	equipa2 = encontraEquipa(equipas, t2, false, N , NL, false_t);
	if(!strcmp(equipa2->ID,"NONE")){
		printf("%d Equipa inexistente.\n",NL);return;}
		
		/*caso ambas equipas existem*/
	novoJogo = (struct Jogos*)can_fail_malloc(sizeof(struct Jogos));
	
	novoJogo->ID = can_fail_malloc((strlen(ID)+1)*sizeof(char));
	novoJogo->team_1 = can_fail_malloc((strlen(t1)+1)*sizeof(char));
	novoJogo->team_2 = can_fail_malloc((strlen(t2)+1)*sizeof(char));

	strcpy(novoJogo->ID, ID);
	strcpy(novoJogo->team_1, t1);
	strcpy(novoJogo->team_2, t2);
	novoJogo->score1 = s1; novoJogo->score2 = s2;
	
	id = hash(ID, M);
	       /*Insercao na hash table dos jogos*/
	if(jogos[id]==NULL){jogos[id]=novoJogo; novoJogo->next_tabela = NULL;}
	else
    {   struct Jogos *aux = jogos[id];
        while(aux->next_tabela){aux = aux->next_tabela;}
        aux->next_tabela = novoJogo;
        novoJogo->next_tabela=NULL;}
	if(s1>s2){ 
		equipa1->wins= (equipa1->wins)+1;
		}
	else if (s1<s2){
		equipa2->wins= (equipa2->wins)+1;}
    /*Insercao na lista  que contem os jogos pela ordem de insercao*/
	if((*first) == NULL){(*first) = novoJogo;novoJogo->next=NULL;\
		novoJogo->prev=NULL;(*top)=novoJogo; return;}

	else {jogo = (*top);
		jogo->next = novoJogo; 
		novoJogo->next=NULL;
		novoJogo->prev=jogo;
		(*top) = novoJogo;}
	
    return;
	}
	
	
          /*insere na hash table das equipas nova equipa*/	
int InseretEquipa(struct Equipas **equipas, char ID[],int N, int NL, \
struct Equipas *false_t){
	struct Equipas *novaEquipa;
	struct Equipas *equipa1;
	int id;
	
	/* verificacao da inexistencia de equipa a introduzir */
	equipa1 = encontraEquipa(equipas, ID, false, N , NL, false_t);
	if(strcmp(equipa1->ID,"NONE")){printf("%d Equipa existente.\n",NL);\
		 return 0;} /*se equipa existe*/
	
	novaEquipa = (struct Equipas*)can_fail_malloc(sizeof(struct Equipas));
	novaEquipa->ID = can_fail_malloc((strlen(ID)+1)*sizeof(char));
	strcpy(novaEquipa->ID, ID);
	novaEquipa->wins = 0;
	id = hash(ID, N);
	
			/*Insercao da equipa na sua hash table*/
	if(equipas[id]==NULL){equipas[id]=novaEquipa;novaEquipa->next=NULL;}
	else{
        struct Equipas *prev = equipas[id];
        while(prev->next){prev = prev->next;}
        prev->next = novaEquipa;
        novaEquipa->next=NULL;}
    return 1;}

		/*Funcao que altera o score de um dado jogo*/
void alteraScore(struct Jogos **jogos, char resto[],int M,int NL, \
struct Equipas **equipas, struct Equipas *false_t, int N){
	
	struct Equipas *equipa1, *equipa2;	
	struct Jogos *next;
	char id[MAX_size]; 
	int s1, s2, x;
	
	/*copia de conteudo do resto para respetivas variaveis*/
	sscanf(resto, "%[^:]%*c%d%*c%d",id,&s1,&s2);
	x = hash(id, M);
	next = jogos[x];
		/*Procura do jogo na hash table*/
	while(next != NULL){
		if(!strcmp(id, next->ID)){
        /*<--------caso o jogo esixte--------->*/		
		equipa1 = encontraEquipa(equipas,next->team_1 , false, N , NL, false_t);
		equipa2 = encontraEquipa(equipas,next->team_2, false, N , NL, false_t);	
	/*alteracao de numero de wins das equipas se s1 for maior que s2*/	
	if(s1>s2){
		if((next->score1)==0 && (next->score2)==0){
			equipa1->wins = (equipa1->wins)+1;}
			
		else if((next->score1)<(next->score2)){
			equipa1->wins = (equipa1->wins)+1;
		if(equipa2->wins>0) equipa2->wins=(equipa2->wins)-1;}
		else if((next->score1) == (next->score2))
			{equipa1->wins = (equipa1->wins)+1;}						
	} 
	/*alteracao de numero de wins das equipas se s2 for maior que s1*/	
	else if(s1<s2){
		if(next->score1==0 && next->score2==0){
			equipa2->wins= (equipa2->wins)+1;}
					
		else if((next->score1)>(next->score2)){
		if(equipa1->wins > 0)equipa1->wins= (equipa1->wins)-1;
			equipa2->wins=(equipa2->wins)+1;}
		else if((next->score1)==(next->score2)){
			equipa2->wins=(equipa2->wins)+1;}
	}
	/*alteracao de numero de wins das equipas se s1 for igual a s2*/	
	else if(s1==s2){
		if((next->score1)>(next->score2))
		{
			if(equipa1->wins > 0)equipa1->wins= (equipa1->wins)-1;}
		else if((next->score1)<(next->score2))
			{
			if(equipa2->wins > 0)equipa2->wins= (equipa2->wins)-1;}
		} /*<--------caso o jogo esixte--------->*/
		
		  /*alteracao do score do jogo*/
		next->score1 = s1; next->score2 = s2;	
			return;}
			
		/*se o nome do jogo nao coencide com que procuramos*/	
		next = next-> next_tabela;
	}
	/* se o jogo nao existe */
	printf("%d Jogo inexistente.\n", NL);
	return;
	}
				/*Funcao que apaga um dado jogo*/
void deleteGame(struct Jogos **jogos,struct Jogos **tabela,char nome[], \
struct Equipas **equipas, struct Equipas *false_t, int M, int NL, \
struct Jogos *false_g, struct Jogos **top, int N){
	
    struct Jogos  *elemento = *tabela, *anterior; 
    struct Equipas *equipa1;
    int score1, score2, x = hash(nome,M);
	bool encontrou = false;
	
  /*Se na hash table existe um unico jogo*/
    if (elemento != NULL && !strcmp(elemento->ID, nome)) 
    { 
		*tabela = elemento->next; 
        encontrou = true;             
    }
  /* Se existem mais que um jogo na tabela*/ 
	if(!encontrou){
	elemento=encontraJogo(jogos, nome, false, M , NL, false_g);
	
  /* caso o jogo a eliminar nao existe */
  
/*remocao do jogo da tabela onde os jogos estao pela ordem de insercao*/
    if (!strcmp(elemento->ID, "none")) \
    {printf("%d Jogo inexistente.\n", NL); return;}
    
    if(elemento->next != NULL)	elemento->next->prev = elemento->prev;
    if(elemento == (*top))  {(*top)=elemento->prev;}
    if (elemento->prev != NULL) elemento->prev->next = elemento->next; 	 
				}
				
	/*aqui ja nao e preciso verificar se o elemento existe porque se \
	 * verificou na parte anterior*/
	 
		/*remocao do jogo da hash table*/
	elemento = jogos[x];
	if(jogos[x]!=NULL && !strcmp(elemento->ID, nome)){
		if(elemento->next_tabela != NULL){
			jogos[x]=elemento->next_tabela;
			}
		else if(elemento->next_tabela == NULL){
			jogos[x]=NULL;}
		}
	else{
		while(elemento != NULL && strcmp(elemento->ID, nome)){
			anterior = elemento;
			elemento = elemento->next_tabela;}
		anterior->next_tabela = elemento->next_tabela;}
	
/* <--------ALTERACAO DAS WINS DA EQUIPA REMOVIDA------------->*/
	score1 = elemento->score1; score2 = elemento->score2;
	if(score1>score2){ 
		equipa1 = encontraEquipa(equipas, elemento->team_1 , false, N , NL, false_t); 
		equipa1->wins= (equipa1->wins)-1;}
	else if(score2 > score1){ 
		equipa1 = encontraEquipa(equipas, elemento->team_2 , false, N , NL, false_t);
		equipa1->wins= (equipa1->wins)-1;}	
/* <--------ALTERACAO DAS WINS DA EQUIPA REMOVIDA------------->*/
	
		/*libertacao da memoria alocado para o jogo removido*/
	free(elemento->ID); free(elemento->team_1); free(elemento->team_2);
    free(elemento);
	}
	
/* funcao que apaga toda a memoria alocada durante execucao*/	
void freeStruct(struct Jogos **head, struct Equipas **equipas, int N){
	int i;
	struct Jogos *antigo = *head, *atual;
	
/* remocao dos jogos atraves da linked list */	
	while(antigo != NULL){
		atual = antigo;
		antigo=antigo->next;
		free(atual->ID); free(atual->team_1); free(atual->team_2);
		free(atual);}
		
/* remocao da memoria da hash table dos jogos */
    for(i = 0; i < N; i++)
    {
		if(equipas[i] != NULL){
			struct Equipas *prev, *temp = equipas[i];
			while(temp!= NULL)
			{
				prev = temp;
				temp = temp->next;
				free(prev->ID); free(prev);
			}
		}
    }
}	
