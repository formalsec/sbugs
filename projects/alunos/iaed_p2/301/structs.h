#ifndef _STRUCTS_H_
#define _STRUCTS_H_
#include <stdlib.h>
#define MAX_NOME 1024			/*capacidade maxima dos nomes de equipas e jogos*/
#define SIZE_TABLE_J 853		/*capacidade maxima da hash table de jogos      */
#define SIZE_TABLE_E 853		/*capacidade maxima da hash table das equipas   */



/**********************************************************/
/**********************************************************/
/*************  Declaracoes de estruturas  ****************/
/**********************************************************/
/**********************************************************/



/*****************  Estruturas dos jogos  *****************/

typedef struct node{
	struct node *prev,*next;
	char *nome, *equipa1, *equipa2;
	int score1, score2;
} Node;

typedef struct hash_node{
	struct hash_node *next;
	Node *jogo;
} Hash_node;

typedef struct hash_table{
	Hash_node **table;
	int capacity;
} Hash_table;

/**********************************************************/

/***************  Estruturas das equipas  *****************/


typedef struct node_eq{
	struct node_eq *next;
	char *nome;
	int vitorias;
} NodeEq;


typedef struct hash_node_eq{
	struct hash_node_eq *next;
	NodeEq *equipa;
} Hash_nodeEq;

typedef struct hash_table_eq{
	Hash_nodeEq **table;
	int capacity;
} Hash_tableEq;


/**********************************************************/
/**********************************************************/
/*************  Inicializacao das funcoes  ****************/
/**********************************************************/
/**********************************************************/

/*funcao dos controlos do programa*/
void comandos(Node *head, Hash_table *jogosT, Hash_tableEq *equipasT, NodeEq *headEq);

/*funcao hash*/
int hash(char *nome, int M);

/*funcoes de inicializacao de tabelas*/
Hash_table *init_table(int size_table);
Hash_tableEq *init_tableEq(int size_table);

/*funcoes de insercao em hash tables*/
void insertJogo_T(Hash_table *t, Node *jogoIns);
Hash_node *insertJogo_N(Hash_node *head, Node *jogoIns);
void insertEquipa_T(Hash_tableEq *t, NodeEq *equipaIns);
Hash_nodeEq *insertEquipa_N(Hash_nodeEq *head, NodeEq *equipaIns);

/*funcoes que adicionam nas hash tables*/
Node* adicionaJogo(Node *head, Hash_table *t, Hash_tableEq *tEq, int nl);
NodeEq* adicionaEquipas(NodeEq *headEq, Hash_tableEq *equipasT, int nl);

/*funcoes que procuram nas hash tables*/
void procuraJogo(Hash_table *t, int nl);
void procuraEquipa(Hash_tableEq *equipasT, int nl);

/*funcoes que listam tabelas*/
void listaJogos(Node *head, int nl);
void listaEquipas(NodeEq *head);
void listaVencedores(Hash_tableEq *equipasT, int nl);

/*funcoes que removem de tabelas ou apagam completamente*/
Node* removeJogo(Hash_table *jogosT, Hash_tableEq *equipasT, Node *head, int nl);
Node* removeTable(Hash_table *t, Hash_tableEq *equipasT, char *aux, int nl);

/*funcao que altera o score*/
void alteraScore(Hash_table *jogosT, Hash_tableEq *equipasT, int nl);


/*funcoes que imprimem hash tables*/
void printTable(Hash_table *t);
void printTableEq(Hash_tableEq *t);

/*funcoes de merge sort*/
void mergesort(char **aux, char **a, int l, int r);
void merge(char **aux, char **a, int l, int m, int r);

/*funcoes que libertam a memoria ocupada*/
void destroyTable(Hash_table *t);
void destroyTableEq(Hash_tableEq *t);
#endif