#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipa.h"


/* cria uma euipa com a estrutura: nome | jogos_ganhos */
equipa_t *criar_equipa(char *nome){

	equipa_t *t = can_fail_malloc(sizeof(equipa_t));

	t->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1 ));

	t->numero_de_jogos = 0;

	strcpy(t->nome, nome);

	return t;
}


/* adiciona a lista ligada */
htable_entrada_t* adicionar_a_lista(htable_entrada_t *lista, equipa_t *equipa){

	htable_entrada_t *nova_entrada = can_fail_malloc(sizeof(htable_entrada_t));

	nova_entrada->equipa = equipa;

	nova_entrada->next = lista;

	return nova_entrada;
}


/* adiciona por ordem ASCII a lista ligada existente para o comando g*/
void adicionar_a_lista_de_equipas_introduzidas(lista_equipas_intruduzidas_t **cabeca, equipa_t *equipa){

	lista_equipas_intruduzidas_t *nova_entrada = can_fail_malloc(sizeof(lista_equipas_intruduzidas_t));

	lista_equipas_intruduzidas_t *ultimo = *cabeca;
	lista_equipas_intruduzidas_t *trail = NULL;
	lista_equipas_intruduzidas_t *temp = NULL;

	
	nova_entrada->equipa = equipa;
	nova_entrada->next = NULL;

	if (*cabeca == NULL){

		*cabeca = nova_entrada;

		return;

	}
	else{


		/* encontra o sitio onde temos de inserir a nova equipa*/
		while (ultimo->next != NULL){

			if(strcmp(ultimo->equipa->nome,nova_entrada->equipa->nome) >= 0){

				/* encontrou o sitio onde vamos inserir a equipa*/ 
				break;

			}
			else{

				/*passa ao proximo node */
				trail = ultimo;
				ultimo = ultimo->next;
			}
		}

		/* caso seja para inserir no inicio da lista*/
		if (ultimo == *cabeca){

			if (strcmp(ultimo->equipa->nome,nova_entrada->equipa->nome) >= 0){

				nova_entrada->next = *cabeca;
				*cabeca = nova_entrada;
			}

			else{

				trail = ultimo->next;
				ultimo->next = nova_entrada;
				nova_entrada->next = trail;
			}
		}

		/* caso seja para inserir depois da cabeca da lista*/
		else{

			if (strcmp(ultimo->equipa->nome,nova_entrada->equipa->nome) >= 0){

			nova_entrada->next = ultimo;
			trail->next = nova_entrada;

			}
			else{

				temp = ultimo->next;
				ultimo->next = nova_entrada;
				nova_entrada->next = temp;

			}
		}

	}	
}


/* obtem o indice da hashtable onde se vai colocar o novo elemento */
unsigned long obter_hash_string(char *str){

	unsigned long hash;

	int a = 31415, b = 27183 ;

	for (hash = 0; *str !='\0' ; str++, a =a*b % (HASHTABLE_TAMANHO -1)){

		hash = ( a*hash + *str) % HASHTABLE_TAMANHO;
	}

	return hash;
}


/* cria a hashtable das quipas */
htable_entrada_t **cria_hashtable(){

	int i; 
	htable_entrada_t **hashtable;

	hashtable = can_fail_malloc(sizeof(htable_entrada_t) * HASHTABLE_TAMANHO);

	for (i = 0; i < HASHTABLE_TAMANHO; i++){

		hashtable[i] = NULL;

	}

	return hashtable;
}


/* adiciona a equipa no indice correto da hashtable e a lista ligada para o comando g */
void adiciona_equipa_a_hashtable(htable_entrada_t **ht, lista_equipas_intruduzidas_t **cabeca, char *nome){

	equipa_t *equipa;
	long hash;

	equipa = criar_equipa(nome);
	hash = obter_hash_string(equipa->nome);

	ht[hash] = adicionar_a_lista(ht[hash], equipa);

	adicionar_a_lista_de_equipas_introduzidas(cabeca, equipa);
}


/* encontra uma dada equipa na hashtable dado o nome dela*/
/* Retorna uma equipa ou entao null caso nao exista*/
equipa_t* encontra_equipa(htable_entrada_t **ht, char* nome){

	long hash = obter_hash_string(nome);

	htable_entrada_t *bucket = ht[hash];

	while (bucket != NULL && strcmp(nome, bucket->equipa->nome) != 0){

		bucket = bucket->next;
	}

	return bucket == NULL ? NULL : bucket->equipa;
}


/* da free a todas as entradas da hashtable das equipas*/	
void destroi_hashtable(htable_entrada_t **ht){

	int i;
	htable_entrada_t *node, *temp_node;

	for(i = 0; i < HASHTABLE_TAMANHO; i++){

		node = ht[i];

		while (node != NULL){

			free(node->equipa->nome);
			free(node->equipa);

			temp_node = node;
			node = node->next;
			free(temp_node);
		}
	}
	free(ht);
}


/* descobre o maior numero de jogos ganhos no total*/
int max_jogos_ganhos(lista_equipas_intruduzidas_t *lista){

	int max = 0;
	lista_equipas_intruduzidas_t *pt;


	for(pt = lista; pt!=NULL; pt = pt->next){

		if(pt->equipa->numero_de_jogos > max){

			max = pt->equipa->numero_de_jogos;
		}
	}
	return max;
}


/* imprime todas as equipas que tenham ganho o max numero de jogos*/
void imprime_melhores_equipas(lista_equipas_intruduzidas_t *lista, int n, int nl){

	lista_equipas_intruduzidas_t *pt;

	if (lista == NULL){
		return;
	}

	printf("%d Melhores %d\n", nl, n);

	for(pt = lista; pt!=NULL; pt = pt->next){

		if(pt->equipa->numero_de_jogos == n){

			printf("%d * %s\n", nl,pt->equipa->nome);
		}
	}
}


/* destroi a lista*/
void destroi_lista_equipas(lista_equipas_intruduzidas_t *lista){

	lista_equipas_intruduzidas_t *temp;

	while (lista!= NULL){

		temp = lista;
		lista = lista->next;
		free(temp);
	}
}
