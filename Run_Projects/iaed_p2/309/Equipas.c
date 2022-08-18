#include "Structs_Jogos.h"
#include "Structs_Equipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Funcao de dispersao da Hashtable. */
int Hashcode(char *nome){

	int h = 0, a = 127;
	int M = HASH_SIZE;

	for(;*nome !='\0'; nome++)
		h = (a*h + *nome) % M;
	return h;
}


/* Funcao que cria a Hashtable. */
hashtable * CreateHash(){

	hashtable * tb = malloc(sizeof(hashtable));
	tb->heads = calloc(HASH_SIZE, sizeof(hash_node*));
	return tb; 
}


/* Funcao que cria um no na Hashtable. */
hash_node * AddNode(Equipa * new, hash_node * next){
	
	hash_node * nn = malloc(sizeof(hash_node));
	nn->pointer = new;
	nn->next = next;
	return nn;
}


/* Funcao que verifica se a equipa existe. */
int CheckTeam(hashtable * tb, char * buffer, int key){

	hash_node * n;

	for(n = tb->heads[key]; n!=NULL; n = n->next){
		if(strcmp(n->pointer->nome, buffer) == 0){
			return 0;
		}
	}
	return 1;
}


/* Funcao que adiciona uma nova equipa. */
Equipa * AddTeam(int NL, Equipa * headE, hashtable * hash){

	Equipa * new;
	char buffer[C_MAX];
	int key;
	getchar();
	scanf("%1023[^:\n]",buffer);
	key =  Hashcode(buffer);

	if(CheckTeam(hash, buffer, key)){
		
		/* Adiciona o novo no a lista simplesmente ligada das equipas. */
		new = malloc(sizeof(Equipa));
		new->nome = malloc(sizeof(char) * (strlen(buffer)+1));
		strcpy(new->nome,buffer);
		new->cont_ganhos = 0;
		new->next = headE;
		headE = new;

		/* Adiciona o novo no a Hashtable das Equipas. */
		hash->heads[key] = AddNode(new, hash->heads[key]);
	}
	else{
		printf("%d Equipa existente.\n", NL);
	}
	return headE;
}


/* Funcao que procura uma equipa. */
void SearchTeam(int NL, hashtable * hash){
	
	hash_node * n;
	char buffer[C_MAX];
	int key;
	getchar();
	scanf("%1023[^:\n]",buffer);
	key = Hashcode(buffer);
	
	if(!CheckTeam(hash, buffer, key)){
		for(n = hash->heads[key]; n!=NULL; n = n->next){
			if(strcmp(n->pointer->nome, buffer) == 0){
				printf("%d %s %d\n", NL, n->pointer->nome, n->pointer->cont_ganhos);
				break;
			}
		}
	}
	else{
		printf("%d Equipa inexistente.\n", NL);
	}
}


/* Algoritmo de ordenacao utilizado para ordenar o nome das equipas por ordem lexicografica. */
void AlphabeticalSort(char ** vetor, int contador){
	
	char * aux;
	int i, j;
	
	for(i=1; i < contador; i++) {
	  	for(j=1; j < contador; j++) {
	        if (strcmp(vetor[j-1], vetor[j]) > 0) {
	           	aux = vetor[j-1];
	           	vetor[j-1] = vetor[j];
	           	vetor[j] = aux;
	        }
	    }
	}
}


/* Funcao que printa por ordem lexicografica as equipas com mais vitorias. */
void FindTeamsWithMaxVictories(int NL, Equipa * headE){
	
	char **vetor;
	Equipa * atual = headE;
	Equipa * atual2 = headE;
	int contador = 0, max = -1, i = 0;

	/* Se houver equipas na lista simplesmente ligada. */
	if(headE){
		
		/* Procura o valor maximo de vitorias e o numero de equipas com essas vitorias. */
		while(atual != NULL){
			if (atual->cont_ganhos > max){
				contador = 1;
				max = atual->cont_ganhos;
			}
			else if(atual->cont_ganhos == max){
				contador+=1;
			}
			atual = atual->next;
		}

		vetor = malloc(sizeof(char*) * contador);
		
		/* Filtra o nome das equipas que possuem o valor maximo de vitorias para um vetor. */
		while(atual2 != NULL){
			if(atual2->cont_ganhos == max){
				vetor[i] = malloc(sizeof(char) * (strlen(atual2->nome)+1));
				strcpy(vetor[i], atual2->nome);
				i+=1;
			}
			atual2  = atual2->next;
		}

		/* Ordena as equipas por ordem lexicografica. */
		AlphabeticalSort(vetor, contador);

		printf("%d Melhores %d\n", NL, max);
		for(i = 0; i<contador; i++){
			printf("%d * %s\n", NL, vetor[i]);
			free(vetor[i]);
		}
		free(vetor);
	}
}


/* Funcao que liberta a memoria alocada pela lista simplesmente ligada. */
void DestroyE(Equipa * headE){
   
	while (headE != NULL)
    {
    	Equipa * temp = headE;
    	headE = headE->next;
    	free(temp->nome);
    	free(temp);
    }
}


/* Funcao que liberta a memoria alocada pela Hashtable. */
void DestroyH(hashtable * tb){

	hash_node * temp;
	size_t i;
	for (i=0; i < HASH_SIZE; i++){
		while(tb->heads[i]){
			temp=tb->heads[i]->next;
			free(tb->heads[i]);
			tb->heads[i]=temp;
		}
	}
	free(tb->heads);
	free(tb);
}