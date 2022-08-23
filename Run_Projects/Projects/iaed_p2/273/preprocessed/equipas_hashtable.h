#ifndef HASH_EQUIPAS_H
#define HASH_EQUIPAS_H


/* devolve o indice correspondente a chave passada,
 para a inserir na hash table */
/* input: chave - string
		  tamanho da hash table*/
/* output: indice para insercao na hashtable */
int hash(char *str, int M);


/* cria dinamicamente uma hash table de equipas */
/* input: tamanho maximo da hash table de equipas
		  numero atual de elementos na hash table de equipas */
/* output: ponteiro para a nova hash table de equipas */
equipa** inicia_hashtable_equipas(int *max, int *num_elem);


/* insere dinamicamente uma equipa na hash table,
se esta chegar a 50% da carga, e redimensionada */
/* input: ponteiro para a nova equipa a adicionar 
		  ponteiro para o tamanho atual da hash table de equipas
		  ponteiro para a hashtable de equipas
		  ponteiro para numero atual de elementos na hash table de equipas */
/* output: retorna o ponteiro para a equipa colocada na hash table se o elemento
		   foi inserido com sucesso, ou NULL caso ja exista uma equipa com o 
		   mesmo nome da equipa a inserir, para assinalar o erro */
equipa* insere_equipa(equipa *nova_equipa, int *pt_max_ht_equipas, equipa **hashtable_equipas, int *pt_num_elem);


/* liberta toda a a memoria alocada pela hash table de equipas */
/* input: ponteiro para a hash table de equipas a libertar */
void liberta_hashtable_equipas(equipa **ht_equipas, int max_ht_equipas);


/* redimensiona a hash table de equipas para o dobro do tamanho atual, faz
rehashing dos valores ja inseridos */
/* input: ponteiro para hah table de equipas
		  ponteiro para o tamanho atual da hash table de equipas
		  ponteiro para numero atual de elementos na hash table de equipas */
/* output: ponteiro para a nova hash table de equipas */
equipa** expande_hashtable_equipas(equipa **ht_equipas, int *pt_max_ht_equipas, int *pt_num_elem);


/* procura na hash table uma equipa dada */
/* input: ponteiro para a hash table de equipas
		  nome da equipa a procurar
		  tamanho da hash table de equipas*/
/* output: ponteiro para a equipa encontrada, ou NULL se a equipa nao 
		   existe na hash table */
equipa* procura_equipa_ht(equipa **ht_equipas, char nome_equipa_procurar[], int max_ht_equipas);

#endif


