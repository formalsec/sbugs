#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipa.h"
#include "jogos.h"


/* cria um jogo com a estrutura: jogo | nome | eq1 | eq2 | pts1 |pts2 */
jogo_t *criar_jogo(char *nome, char *eq1, char *eq2, int pt1, int pt2){

	jogo_t *t = malloc(sizeof(jogo_t));

	t->nome = malloc(sizeof(char) * (strlen(nome) + 1 ));

	t->eq1 = malloc(sizeof(char) * (strlen(eq1) + 1 ));

	t->eq2 = malloc(sizeof(char) * (strlen(eq2) + 1 ));

	t->pts_1 = pt1;

	t->pts_2 = pt2;


	strcpy(t->nome, nome);
	strcpy(t->eq1, eq1);
	strcpy(t->eq2, eq2);

	return t;
}


/* adiciona a lista ligada */
htable_entrada_jogo_t* adicionar_a_lista_de_jogo(htable_entrada_jogo_t *lista, jogo_t *jogo){

	htable_entrada_jogo_t *nova_entrada = malloc(sizeof(htable_entrada_jogo_t));

	nova_entrada->jogo = jogo;

	nova_entrada->next = lista;

	return nova_entrada;
}


/* adiciona no inicio da lista ligada existente para o comando l*/
void adicionar_a_lista_de_introduzidos(lista_intruduzidos_t **cabeca, jogo_t *jogo){

	lista_intruduzidos_t *nova_entrada = malloc(sizeof(lista_intruduzidos_t));
	
	nova_entrada->jogo = jogo;
	nova_entrada->next = *cabeca;

	*cabeca = nova_entrada;
	return;
}


/* obtem o indice da hashtable onde se vai colocar o novo elemento */
unsigned long obter_hash_string_jogo(char *str){

	unsigned long hash;

	int a = 31415, b = 27183 ;

	for(hash = 0; *str !='\0' ; str++, a =a*b % (HASHTABLE_JOGO_TAMANHO -1)){

		hash = ( a*hash + *str) % HASHTABLE_JOGO_TAMANHO;
	}

	return hash;
}


/* cria a hashtable dos jogos */
htable_entrada_jogo_t **cria_hashtable_jogo(){

	int i; 

	htable_entrada_jogo_t **hashtable_jogo;

	hashtable_jogo = malloc(sizeof(htable_entrada_jogo_t) * HASHTABLE_JOGO_TAMANHO);

	for (i = 0; i < HASHTABLE_JOGO_TAMANHO; i++){

		hashtable_jogo[i] = NULL;

	}

	return hashtable_jogo;
}


/* adiciona o jogo no indice correto da hashtable e a lista ligada para o comando l */
void adiciona_jogo_a_hashtable(htable_entrada_jogo_t **ht,lista_intruduzidos_t **cabeca, char *nome, char *eq1, char *eq2, int pt1, int pt2){

	jogo_t *jogo;
	long hash;

	jogo = criar_jogo(nome, eq1, eq2, pt1, pt2);

	hash = obter_hash_string_jogo(jogo->nome);

	ht[hash] = adicionar_a_lista_de_jogo(ht[hash], jogo);

	adicionar_a_lista_de_introduzidos(cabeca, jogo);
}


/* encontra um dado jogo na hashtable dado o nome dela*/
/* Retorna um jogo ou entao null caso nao exista*/
jogo_t* encontra_jogo(htable_entrada_jogo_t **ht, char* nome){

	long hash = obter_hash_string_jogo(nome);

	htable_entrada_jogo_t *bucket = ht[hash];

	while (bucket != NULL && strcmp(nome, bucket->jogo->nome) != 0){

		bucket = bucket->next;
	}

	return bucket == NULL ? NULL : bucket->jogo;
}


/* imprime a lista de jogos ligada do comando l ao contrario, para ficar por ordem de entrada*/
void imprime_lista(lista_intruduzidos_t *entrada, int nl){


	if ( entrada == NULL){
		return;
	}

	imprime_lista(entrada->next, nl);

	
		printf("%d %s %s %s %d %d\n", nl, entrada->jogo->nome, entrada->jogo->eq1, entrada->jogo->eq2,entrada->jogo->pts_1,entrada->jogo->pts_2);
		entrada = entrada->next;	
}


/* da free a todas as entradas da hashtable de jogos*/
void destroi_hashtable_jogo(htable_entrada_jogo_t **ht){

	int i;
	htable_entrada_jogo_t *node, *temp_node;

	for(i = 0; i < HASHTABLE_JOGO_TAMANHO; i++){

		node = ht[i];

		while (node != NULL){

			free(node->jogo);

			temp_node = node;
			node = node->next;
			free(temp_node);
		}
	}
	free(ht);
}


/* remove um jogo da hashtable*/
void remove_jogo(htable_entrada_jogo_t **ht, char *nome){


		long hash = obter_hash_string_jogo(nome);

		htable_entrada_jogo_t *bucket = ht[hash % HASHTABLE_JOGO_TAMANHO];

		htable_entrada_jogo_t *prev;

		if ( bucket != NULL && strcmp(bucket->jogo->nome, nome) == 0){


				ht[hash] = ht[hash]->next;
				free(bucket->jogo->nome);
				free(bucket->jogo->eq1);
				free(bucket->jogo->eq2);
				free(bucket->jogo);
				free(bucket);
				return;

		}

		while ( bucket != NULL && strcmp(bucket->jogo->nome, nome) != 0){

			prev = bucket;
			bucket = bucket->next;

		}

		if (bucket == NULL){

			return;
		}

		prev->next = bucket->next;
		free(bucket->jogo->nome);
		free(bucket->jogo->eq1);
		free(bucket->jogo->eq2);
		free(bucket->jogo);
		free (bucket);
}


/* destroi a lista */
void destroi_lista(lista_intruduzidos_t *lista){

	lista_intruduzidos_t *temp;

	while (lista!= NULL){

		free(lista->jogo->nome);
		free(lista->jogo->eq2);
		free(lista->jogo->eq1);

		temp = lista;
		lista = lista->next;
		free(temp);
	}
}


/* remove um jogo da lista ligada do comando l*/
void retira_da_lista(lista_intruduzidos_t **lista, char *nome ){

	lista_intruduzidos_t *prev;
	lista_intruduzidos_t *bucket;

	prev = *lista;
	bucket = *lista;


	if (bucket != NULL && strcmp(bucket->jogo->nome, nome) == 0){


				*lista = bucket->next;
				free(bucket);
				return;

		}

		while ( bucket != NULL && strcmp(bucket->jogo->nome, nome) != 0){

			prev = bucket;
			bucket = bucket->next;

		}

		if (bucket == NULL){

			return;
		}

		prev->next = bucket->next;
		free (bucket);
}



