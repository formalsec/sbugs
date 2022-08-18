#ifndef EQUIPA_H
#define EQUIPA_H

#include <stdlib.h>
#include <string.h>

#define HASH_E_SIZE 12049

typedef struct {
  char *nome;
  int wins;
} Equipa;

typedef Equipa *pEquipa;

/* Nodes e links para a hashtable */
typedef struct node_e {
  Equipa * equipa;
  struct node_e * next;
} NodeE ;

typedef NodeE *LinkE;

/* Inicializa a hashtable */
void ETable_init(LinkE * Table);
/* Adiciona uma equipa a uma lista da hashtable */
LinkE add_e_to_list(LinkE head, Equipa * equipa);
/* Calcula o index que a string de uma equipa devera ocupar na HashTable */
int hashEquipa(char *v, int M);
/* Procura numa lista da hashtable uma equipa com o nome input */
Equipa * search_lista_e(LinkE head, char * nome);
/* Adiciona uma equipa a hashtable */
int add_e_to_hash(LinkE * Table, Equipa * equipa);
/* Remove todas as equipas da base de dados */
void clear_e(LinkE * Table);
/* Funcao similar ao strcmp, mas que recebe como input equipas, e compara os seus nomes*/
int cmpstr(void const *a, void const *b);

#endif
