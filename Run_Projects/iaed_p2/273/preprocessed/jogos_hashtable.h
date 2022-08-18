#ifndef HASH_JOGOS_H
#define HASH_JOGOS_H


/* cria dinamicamente uma hash table de jogos */
/* input: tamanho maximo da hash table de jogos
		  numero atual de elementos na hash table de jogos */
/* output: ponteiro para a nova hash table de jogos */
jogo** inicia_hashtable_jogos(int *max, int *num_elem);


/* insere dinamicamente um jogo na hash table,
se esta chegar a 50% da carga, e redimensionada */
/* input: ponteiro para o novo jogo a adicionar 
		  ponteiro para o tamanho atual da hash table de jogos
		  ponteiro para a hashtable de jogos
		  ponteiro para numero atual de elementos na hash table de jogos
		  ponteiro para a lista ligada de jogos */
/* output: retorna o ponteiro para o jogo colocado na hash table se o elemento
		   foi inserido com sucesso, ou NULL caso ja exista um jogo com o 
		   mesmo nome do jogo a inserir, para assinalar o erro */
jogo* insere_jogo(jogo *novo_jogo, int *pt_max_ht_jogos, jogo **hashtable_jogos,
				  int *pt_num_elem, lista_jogos *lst_jogos);


/* liberta toda a a memoria alocada pela hash table de jogos */
/* input: ponteiro para a hash table a libertar
		  tamanho da hash table de jogos */
void liberta_hashtable_jogos(jogo **ht_jogos, int max_ht_jogos);


/* redimensiona a hash table de jogos para o dobro do tamanho atual, faz
rehashing dos valores ja inseridos */
/* input: ponteiro para a hash table de jogos
		  ponteiro para o tamanho atual da hash table de jogos
		  ponteiro para o numero de elementos na hash table de jogos
		  ponteiro para a lista ligada de jogos */
/* output: ponteiro para a nova hash table de jogos */
jogo** expande_hashtable_jogos(jogo **ht_jogos, int *pt_max_ht_jogos, 
							   int *pt_num_elem, lista_jogos *lst_jogos);


/* procura na hash table um jogo dado */
/* input: ponteiro para a hash table de jogos
		  nome do jogo a procurar
		  tamanho da hash table de jogos*/
/* output: ponteiro para o jogo encontrado, ou NULL se a jogo nao 
		   existe na hash table */
jogo* procura_jogo_ht(jogo **ht_jogos, char nome_jogo_procurar[], int max_ht_jogos);


/* encontra e liberta um jogo, depois de removido, os jogos seguintes sao
 reinseridos, ate ser encontrada uma posicao NULL */
/* input: nome do jogo a eliminar
		  ponteiro para a hash table de jogos
		  ponteiro para o tamanho atual da hash table de jogos
		  ponteiro para o numero de elementos na hash table de jogos
		  ponteiros para a lista ligada de jogos */
/* output: 0 se o item foi removido com sucesso, -1 caso contrario (se o jogo 
		   nao existir na hash table) */
int remove_jogo_ht(char nome_jogo_eliminar[], jogo **ht_jogos, int *pt_max_ht_jogos, 
				int *pt_num_elem_ht_jogos, lista_jogos *lst_jogos);

#endif
