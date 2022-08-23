#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*tamanho inicial da hash*/
int tamanho_hash = 97;
/*numero de equipas na hash*/
int nr_equipas = 0;

/*funcao que devolve o numero do indice da equipa na hash*/
int hash(char *str){
	int aux = 0, i = 0;
	while (str[i] != '\0'){
		aux = aux + str[i];
		i++;
	}
	return aux % tamanho_hash;
}

/*funcao que cria a hash*/
void createHash(){
	int i;
	nr_equipas = 0;
	hash_e = malloc(sizeof(equipa*)*tamanho_hash);
	for(i = 0; i < tamanho_hash; i++){
		hash_e[i] = NULL;
	}
}

/*free da hash e estrutura equipa*/
void destroyHash(){
	int i;
	for(i = 0; i < tamanho_hash; i++){
		if(hash_e[i] != NULL){
			free(hash_e[i]->nome);
			free(hash_e[i]);
		}
	}
	free(hash_e);
}

/*funcao que adiciona uma nova equipa a hash*/
int A(){
	char nome[MAXINPUT];
	int i;
	scanf(" %[^:\n]", nome);
	i = hash(nome);
	while(hash_e[i] != NULL){
		if(strcmp(hash_e[i]->nome, nome) == 0){
			printf("%d Equipa existente.\n", NL);
			return 0; 
		}
		i = (i+1) % tamanho_hash;
	}
	hash_e[i] = malloc(sizeof(equipa));
	hash_e[i]->nome = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(hash_e[i]->nome, nome);
	hash_e[i]->ganhos = 0;
	/*se o numero de equipas for metade do tamanho da hash aumenta a hash*/
	if (nr_equipas++ > tamanho_hash/2){
		expand();
	}
	return 1;
}

/*funcao que readiciona as equipas depois de uma expansao*/
void insert(equipa *aux){
	int i;
	i = hash(aux->nome);
	while(hash_e[i] != NULL){
		i = (i+1) % tamanho_hash;
	}
	hash_e[i] = aux;
	nr_equipas++;
}

/*expansao da hash depois de estar meio preenchida*/
void expand(){
	int i;
	equipa **aux = hash_e;
	tamanho_hash = tamanho_hash * 2;
	createHash();
	for (i = 0; i < tamanho_hash/2; i++){
		if(aux[i] != NULL){
			insert(aux[i]);
		}
	}
	free(aux);
}

/*funcao que procura uma equipa e devolve seu indice na hash*/
/*se a equipa nao existir devolve -1*/
int procuraEquipa(char *nome){
	int aux;
	aux = hash(nome);
	while(hash_e[aux] != NULL){
		if(strcmp(hash_e[aux]->nome, nome) == 0){
			return aux;
		}
		aux++;
		aux %= tamanho_hash;
	}
	return -1;
}

/*funcao auxiliar que lista as equipas na hash*/
void printHash(){
	int i;
	for(i = 0; i < tamanho_hash; i++){
		if(hash_e[i] != NULL){
			printf("%s(%d) %d\n", hash_e[i]->nome, i, hash_e[i]->ganhos);
		}
	}
}

/*funcao que procura uma equipa*/
void P(){
	int aux;
	char nome[MAXINPUT];
	scanf(" %[^:\n]", nome);
	aux = procuraEquipa(nome);
	if(aux != -1){
		printf("%d %s %d\n",NL, hash_e[aux]->nome, hash_e[aux]->ganhos);
	}
	else{
		printf("%d Equipa inexistente.\n", NL);
	}
}

/*funcao auxiliar ao heap sort que troca duas equipas no vetor auxiliar*/
void troca(equipa **array, int pai, int filho){
	equipa *aux = array[pai];
	array[pai] = array[filho];
	array[filho] = aux;
}

/*funcao que verifica se o pai e os filhos estao por ordem lexicografica*/
/*se nao troca*/
void heapify(equipa **array, int t, int i){
	int pai = i;
  	int esquerda = 2 * i + 1;
  	int direita = 2 * i + 2;
  	if(esquerda < t && strcmp(array[esquerda]->nome, array[pai]->nome) > 0){
    	pai = esquerda;
	}
  	if(direita < t && strcmp(array[direita]->nome, array[pai]->nome) > 0){
    	pai = direita;
  	}
	if(pai != i) {
    	troca(array, i, pai);
      	heapify(array, t, pai);
    }
}

void g(){
	int i, e = 0, mais_ganhos = -1;
	if(nr_equipas > 0){
		/*vetor auxiliar para realizar o heap sort*/
		equipa **aux = malloc(sizeof(equipa*)*nr_equipas);
		/*mete no vetor so as equipas com mais jogos ganhos*/
		for(i = 0; i < tamanho_hash; i++){
			if(hash_e[i] != NULL){
				if(mais_ganhos == -1){
					aux[e++] = hash_e[i];
					mais_ganhos = hash_e[i]->ganhos;
				}
				else if(aux[0]->ganhos < hash_e[i]->ganhos){
					e = 0;
					aux[e++] = hash_e[i];
					mais_ganhos = hash_e[i]->ganhos;
				}
				else if(aux[0]->ganhos == hash_e[i]->ganhos){
					aux[e++] = hash_e[i];
				}
			}
		}
		/*transforma um vetor num heap*/
		for(i = e / 2 - 1; i >= 0; i--){
      		heapify(aux, e, i);
		}
		/*heap sort*/
		for(i = e - 1; i >= 0; i--) {
	      	troca(aux, 0, i);
	      	heapify(aux, i, 0);
	    }
		printf("%d Melhores %d\n", NL, mais_ganhos);
		for(i = 0; i < e; i++){
			printf("%d * %s\n", NL, aux[i]->nome);
		}
		free(aux);
	}
}
