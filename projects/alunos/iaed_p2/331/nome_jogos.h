#ifndef NOME_JOGOS_H
#define NOME_JOGOS_H

#include "equipas.h"
#include "hash_table_eq.h"

typedef struct nome_j{
	char * jogo;
	struct nome_j * prev;
	struct nome_j * next;
} Name;

typedef struct lst_char{
	Name * head;
	Name * last;
} List_Names;

/*------------------------------------------------------------------------------------*/

/*inicia uma lista duplamente ligada de nomes*/
List_Names * init_list_n();

/*cria um novo nome*/
Name * new_name(char * j);

/*acrescenta um novo nome a lista de nomes, como elemento final*/
Name * add_end_name(List_Names * l, char * j);

/*procura um nome numa lista de nomes*/
Name * search_name(List_Names * l, char * nome_j);

/*elimina um nome da memoria*/
void free_name(Name * n);

/*elimina um nome de uma lista de nomes*/
void remove_name(List_Names * l, char * jogo);

/*elimina o primeiro nome de uma lista de nomes*/
Name * remove_first_name(Name * head);

/*elimina uma lista de nomes*/
void free_all_names(List_Names * l);

/*imprime todos os nomes pertencentes a lista, antecedidos pelo numero da linha do input que os 
originou*/
void print_teams(int NL, List_Names * l);

/*procura, numa lista de equipas, equipas que venceram max numero de jogos e constroi 
uma lista de nomes com elas*/
void search_teams_wins(List_Teams * lst_eq, List_Names * l, int max);

/*procura, numa hash table de equipas, equipas que venceram max numero de jogos e constroi 
uma lista de nomes com elas*/
void search_ht_t_wins(ht_teams l, List_Names * res, int max);

/*verifica se uma hash table de equipas esta vazia*/
int check_empty_ht_t(ht_teams l);

/*retorna o nome que se encontra na ind-esima posicao de l*/
Name * index_(List_Names * l, int ind);

/*ordena os elementos de uma lista de nomes por ordem alfabetica*/
void merge(List_Names * lst, int l, int m, int r);

/*ordena os elementos de uma lista de nomes por ordem alfabetica*/
void mergesort(List_Names * lst, int l, int r);

/*retorna o numero de elementos de uma lista de nomes*/
int number_elem(List_Names * l);

#endif
