#include "equipas.h"
#include "jogos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* funcoes auxiliares aos comandos*/
int checkins_j(char *jogo, hashtable_jogos *h_jogos, int hash)
{														/* funcao que descobre se um jogo esta na lista ligada, TRUE se nao estiver*/
	hash_node_jogos *checker;
	for (checker= h_jogos->tb[hash]; checker!=NULL; checker=checker->next)
		if(strcmp(checker->pointer->jogo, jogo)== 0)
			return 0;
	return 1;
}

void altera_v(hashtable_equipas *h_equipas, char *equipa, int hash)
{														/* funcao que aumenta as vitorias de uma certa equipa*/
	hash_node_equipas *checker;
	for (checker= h_equipas->tb[hash]; checker!=NULL; checker=checker->next)
		if(strcmp(checker->pointer->equipa, equipa)== 0)
			(checker->pointer->pontos)++;
}

void altera_v2(hashtable_equipas *h_equipas, char *equipa, int hash)
{														/* funcao que diminui as vitorias de uma certa equipa*/
	hash_node_equipas *checker;
	for (checker= h_equipas->tb[hash]; checker!=NULL; checker=checker->next)
		if(strcmp(checker->pointer->equipa, equipa)== 0)
			(checker->pointer->pontos)--;
}

/* funcoes de inicializacao das estruturas*/
hashtable_jogos *mk_hash_table_j() 
{
	hashtable_jogos * hash_jogos = malloc(sizeof(hashtable_jogos));
	hash_jogos->capacity = CAP;
	hash_jogos->tb = calloc(hash_jogos->capacity, sizeof(hash_node_jogos*));
	return hash_jogos;
}

hash_node_jogos *make_hashnode_j(hash_node_jogos *head, node_jogos *node)
{
	hash_node_jogos * hashnode_jogos = malloc(sizeof(hash_node_jogos));
	hashnode_jogos->next=head;
	hashnode_jogos->pointer=node;
	head = hashnode_jogos;
	return head;
}

lista_jogos *mk_list()
{														/* funcao de inicializacao da lista duplamente ligada*/
	lista_jogos *jogos = malloc(sizeof(lista_jogos));
	jogos->head = jogos->last = NULL;
	return jogos;
}

void make_node_j(char *jogo, char *equipa1, char *equipa2, int sc1, int sc2, lista_jogos *jogos)
{														/* funcao de inicializacao do node da lista duplamente ligada*/
	node_jogos * new_node = malloc(sizeof(node_jogos));
	new_node->previous= jogos->last;
	new_node->next= NULL;
	new_node->equipa1=malloc(sizeof(char)*(strlen(equipa1)+1));
	strcpy(new_node->equipa1, equipa1);
	new_node->equipa2=malloc(sizeof(char)*(strlen(equipa2)+1));
	strcpy(new_node->equipa2, equipa2);
	new_node->jogo=malloc(sizeof(char)*(strlen(jogo)+1));
	strcpy(new_node->jogo, jogo);
	new_node->sc1=sc1;
	new_node->sc2=sc2;
	if (jogos->last)
		jogos->last->next = new_node;
	else
		jogos->head = new_node;
	jogos->last = new_node;
}

/* funcoes que libertam memoria alocada as estruturas dos jogos*/
void free_node(node_jogos *n)
{														/* funcao de free do node da lista duplamente ligada*/
	free(n->jogo);
    free(n->equipa1);
    free(n->equipa2);
    free(n);
}

void free_list(lista_jogos *l)
{														/* funcao de free da lista duplamente ligada*/
	while(l->head)
	{
		node_jogos *tmp = l->head->next;
		free_node(l->head);
		l->head = tmp;
	}
	free(l);
}

void lib_espaco_jogos(hashtable_jogos *h_jogos)
{
	hash_node_jogos *tmp2;
    size_t i;
    for (i=0; i<h_jogos->capacity; i++)
    {													/* ciclo que percorre a hashtable e liberta a memoria*/
    	while(h_jogos->tb[i])
    	{
    		tmp2= h_jogos->tb[i]->next;
    		free(h_jogos->tb[i]);
    		h_jogos->tb[i]= tmp2;
    	}
    }
    free(h_jogos->tb);
    free(h_jogos);
}

/* Funcoes responsaveis por executar os comandos do utilizador*/
void a(int NL, lista_jogos *jogos, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas)
{
	char equipa1[MAX_NOME], equipa2[MAX_NOME], jogo[MAX_NOME];
	int hash_j, hash_e1, hash_e2, sc1, sc2;
	getchar();
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", jogo, equipa1, equipa2, &sc1, &sc2);
	hash_j = hash(jogo, h_jogos->capacity);
	hash_e1 = hash(equipa1, h_equipas->capacity);
	hash_e2 = hash(equipa2, h_equipas->capacity);
	if(!checkins_j(jogo, h_jogos, hash_j)) 			
		printf("%d Jogo existente.\n", NL);
	else if((checkins(equipa1, h_equipas, hash_e1)|checkins(equipa2, h_equipas, hash_e2)))
		printf("%d Equipa inexistente.\n", NL);
	else												/* se o jogo ainda nao existir entao acrescenta-o na lista e na hashtable*/
	{													/* funcoes make que acrescentam o novo jogo a hashtable e a lista duplamente ligada*/ 
		make_node_j(jogo, equipa1, equipa2, sc1, sc2, jogos);	
		h_jogos->tb[hash_j]=make_hashnode_j(h_jogos->tb[hash_j], jogos->last);
		if (sc1 > sc2)									/* aumenta as vitoras da equipa que venceu*/
			altera_v(h_equipas, equipa1, hash_e1);	
		if (sc2 > sc1)
			altera_v(h_equipas, equipa2, hash_e2);		
	}
}

void l(int NL, lista_jogos *jogos)
{
	node_jogos *checker;								/* ciclo que percorre e printa a lista ligada dos jogos mas pela ordem inserida (atraves da entrada head da lista)*/
	for (checker= jogos->head; checker; checker=checker->next)
		printf("%d %s %s %s %d %d\n", NL, checker->jogo, checker->equipa1, checker->equipa2, checker->sc1, checker->sc2);
}

void p(int NL, hashtable_jogos *h_jogos)
{
	char jogo[MAX_NOME];
	int hash_j;
	hash_node_jogos *checker;
	getchar();
	scanf("%[^:\n]", jogo);
	hash_j = hash(jogo, h_jogos->capacity);
	if (checkins_j(jogo, h_jogos, hash_j))	 			/* verifica se o jogo existe*/
		printf("%d Jogo inexistente.\n", NL);
	else
	{
		for (checker= h_jogos->tb[hash_j]; checker!=NULL; checker=checker->next)
			if(strcmp(checker->pointer->jogo, jogo)== 0)
				printf("%d %s %s %s %d %d\n", NL, checker->pointer->jogo, checker->pointer->equipa1, checker->pointer->equipa2, checker->pointer->sc1, checker->pointer->sc2);
	}
}

void s(int NL, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas)
{
	char jogo[MAX_NOME];
	int hash_j, sc1, sc2, hash_e1, hash_e2;
	hash_node_jogos *checker;
	getchar();
	scanf("%[^:\n]:%d:%d", jogo, &sc1, &sc2);
	hash_j = hash(jogo, h_jogos->capacity);
	if (checkins_j(jogo, h_jogos, hash_j))
		printf("%d Jogo inexistente.\n", NL);
	else
	{
		for (checker= h_jogos->tb[hash_j]; checker!=NULL; checker=checker->next)
			if(strcmp(checker->pointer->jogo, jogo)== 0)
			{											/* grupo de condicoes que verificam o vencedor com o score anterior e alteram o numero de vitorias se o score mudar quem vence*/
				hash_e1 = hash(checker->pointer->equipa1, h_equipas->capacity);
				hash_e2 = hash(checker->pointer->equipa2, h_equipas->capacity);
				if (checker->pointer->sc1 > checker->pointer->sc2)
					altera_v2(h_equipas, checker->pointer->equipa1, hash_e1);	
				if (checker->pointer->sc2 > checker->pointer->sc1)
					altera_v2(h_equipas, checker->pointer->equipa2, hash_e2);		
				checker->pointer->sc1=sc1; 
				checker->pointer->sc2=sc2;
				if (checker->pointer->sc1 > checker->pointer->sc2)
					altera_v(h_equipas, checker->pointer->equipa1, hash_e1);	
				if (checker->pointer->sc2 > checker->pointer->sc1)
					altera_v(h_equipas, checker->pointer->equipa2, hash_e2);	
			}
	}
}

void r(int NL, lista_jogos *jogos, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas)
{
	char jogo[MAX_NOME];
	int hash_j, hash_e1, hash_e2;
	hash_node_jogos *checker, *previous;
	getchar();
	scanf("%[^:\n]", jogo);
	hash_j = hash(jogo, h_jogos->capacity);
	if (checkins_j(jogo, h_jogos, hash_j))
		printf("%d Jogo inexistente.\n", NL);
	else
	{
		for (checker= h_jogos->tb[hash_j]; checker!=NULL; checker=checker->next)
			{											/* ciclo que encontra o node onde esta o jogo a remover*/
			if(strcmp(checker->pointer->jogo, jogo)== 0)
				break;
			previous=checker;
			}							
		hash_e1 = hash(checker->pointer->equipa1, h_equipas->capacity);
		hash_e2 = hash(checker->pointer->equipa2, h_equipas->capacity);
														/* diminui as vitorias da equipa que tinha ganho o jogo*/
		if (checker->pointer->sc1 > checker->pointer->sc2)
			altera_v2(h_equipas, checker->pointer->equipa1, hash_e1);	
		if (checker->pointer->sc2 > checker->pointer->sc1)
			altera_v2(h_equipas, checker->pointer->equipa2, hash_e2);		
														/* remove o node da lista ligada dupla e une o node anterior ao seguinte*/
		if (checker->pointer->previous == NULL)
			jogos->head = checker->pointer->next;
		else
			checker->pointer->previous->next = checker->pointer->next;
		if (checker->pointer->next == NULL)
			jogos->last = checker->pointer->previous;
		else
			checker->pointer->next->previous = checker->pointer->previous;
		free_node(checker->pointer);					/* liberta o node da memoria*/ 
		if (checker== h_jogos->tb[hash_j])				/* verifica se o hashnode era o primeiro e, se sim substitui pelo seguinte*/
		{
			h_jogos->tb[hash_j]= checker->next;
			free(checker);								/* liberta o hashnode da memoria*/ 	
			return;
		}
		previous->next = checker->next; 				/* se o hashnode nao for o primeiro entao remove e une o anterior ao seguinte*/
		free(checker);									/* liberta o hashnode da memoria*/ 
	}
}