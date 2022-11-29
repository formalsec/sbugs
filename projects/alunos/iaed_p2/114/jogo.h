#include "equipa.h"
#include <stdlib.h>

#define HASH_J_SIZE 14149

typedef struct
{
  char *nome;
  Equipa * equipa0;
  Equipa * equipa1;
  int score[2];
} Jogo;

/* Node, link e lista, da lista de todos os jogos, que tera os jogos por ordem de
introducao*/
typedef struct node_j {
  Jogo * jogo;
  struct node_j * prev;
  struct node_j * next;
} NodeJ;

typedef NodeJ *LinkJ;

typedef struct lista {
  LinkJ head;
  LinkJ tail;
} *Lista;

/* Nodes e links para as listas ligadas da hashtable */
typedef struct node {
  LinkJ linkj;
  struct node * prev;
  struct node * next;
} Node ;

typedef Node *Link;

/* Inicializa a hashtable */
void JTable_init(Link * Table);
/* Calcula o index no array a partir de uma string */
int hashJogo(char *v, int M);
/* Procura um jogo numa lista da hash table */
Link search_j_lista_Table(Link head, char * nome);
/* Procura um jogo na hashtable a partir do nome */
Link search_j_Table(Link * Table, char * nome);
/* Verifica se um jogo input pode ser adicionado, caso tenha argumentos validos */
int jogo_invalido(Link * JHTable , LinkE * EHTable , char * jogo_nome , char * equipa0_nome , char * equipa1_nome);
/* Adiciona a lista ligada principal o jogo input */
LinkJ add_j_to_main_list (LinkJ head , Jogo * jogo);
/* Adiciona o node que contem o jogo a lista da hashtable */
Link add_linkj_to_list(Link head, LinkJ linkj);
/* Adiciona o node que contem o jogo a hashtable */
void add_linkj_hash(Link * Table, LinkJ linkj, char * nome);
/* Recebe um jogo e devolve o ponteiro para a equipa vencedora */
Equipa * vencedor(Jogo * jogo);
/* Remove um jogo da base de dados, a partir do nome */
int destroy(Link * Table , LinkJ * MainList, LinkJ * Tail , char * nome);
/* Vai remover todos os jogos da base de dados */
void clear_j(Link*Table);
