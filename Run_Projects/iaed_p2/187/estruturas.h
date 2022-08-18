#ifndef PAO
#define PAO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 1024
#define TAM_HASH 1507

typedef struct node_equipa
{
    char *nome;
    int vitorias;
    struct node_equipa *next;
}NodeE;

typedef struct node_jogo
{
    char *nome, *casa, *fora;
    int resCasa, resFora;
    struct node_jogo *next_lista, *prev_lista, *next_tabela;
}NodeJ;

NodeJ *insertEnd_lista_tabelaJ(NodeJ *cabeca, NodeJ *x);
/* insere um jogo num indice da hash table (encadeamento externo) */
void freeJ(NodeJ *x);
/* liberta um jogo */
void free_lista_tabelaJ(NodeJ *cabeca);
/* liberta um indice da hash table */
NodeJ *remove_lista_tabelaJ(NodeJ *cabeca, char *nomenclatura);
/* remove um elemento de uma lista correspondente a um indice da hash table */
void print_lista_tabelaJ(int cont, NodeJ *cabeca);
/* imprime um indice da hash table */
NodeJ *encontra_lista_tabelaJ(NodeJ *cabeca, char *nomenclatura);
/* dado um nome e um indice, retorna o jogo correspondente */
unsigned int hash(const char *key);
/* funcao que transforma a string key num inteiro (indice da hash table) */
void hash_table_insertJ(NodeJ **hash_table, NodeJ *jogo);
/* funcao que recebe um jogo e insere o na hash table */
void hash_table_removeJ(NodeJ **hash_table, char *nome);
/* funcao que recebe um jogo e remove o da hash table */
void free_listaJ(NodeJ *cabeca);
/* funcao que liberta uma lista encadeada de jogos */
NodeJ *insertEnd_listaJ(NodeJ *cabeca, NodeJ **cauda, NodeJ **tabela, char *nome, char *casa, char *fora, int resCasa, int resFora);
/* funcao que recebe os componentes do jogo e junta-os a uma struct, alocando a memoria (na heap). 
De seguida, chama a funcao para inserir este mesmo jogo na hash table e so depois e que o insere na lista ligada */
NodeJ *remove_listaJ(NodeJ *cabeca, NodeJ **cauda, NodeJ **tabela, char *nomenclatura);
/* funcao que recebe um nome e remove o da tabela e da lista, libertando o jogo na segunda */
void print_listaJ(int cont, NodeJ *cabeca);
/* funcao que imprime uma lista encadeada dada uma cabeca */
void print_jogo(int cont, NodeJ *jogo);
/* funcao que imprime um jogo de acordo com as regras estabelecidas no enunciado */
NodeJ *encontra_listaJ(NodeJ *cabeca, char *nomenclatura);
/* funcao que dado um nome, devolve o jogo correspondente dentro da lista */
NodeJ **init_hash_tableJ();
/* funcao que inicializa a tabela a NULL */
void print_tableJ(int cont, NodeJ **hash_table);
/* imprime a tabela */
void free_tabelaJ(NodeJ **tabela);
/* liberta toda a tabela */ 
NodeJ *encontra_tabelaJ(NodeJ **tabela, char *nome);
/* dado um nome, devolve o jogo correspondente */
NodeJ *apagaNodeJ(NodeJ *cabeca, NodeJ **cauda, NodeJ* del);
/* apaga um jogo da lista ligada */

/*_________________________________________________________________________________________________________________________________________________*/


/* o mesmo que esta descrito para as funcoes com o 'J' para as equipas, mas com o 'E' */
void freeE(NodeE *x);
void free_listaE(NodeE *cabeca);
NodeE *insertEnd_listaE(NodeE *cabeca, char *nome, int wins);
NodeE *remove_listaE(NodeE *cabeca, char *nomenclatura);
void print_equipa(int cont, NodeE *equipa);
NodeE *encontra_listaE(NodeE *cabeca, char *nomenclatura);
NodeE **init_hash_tableE();
void hash_table_insertE(NodeE **hash_table, char *nome, int vitorias);
void hash_table_removeE(NodeE **hash_table, char *nome);
void free_tabelaE(NodeE **tabela);
NodeE *encontra_tabelaE(NodeE **tabela, char *nome);


#endif 
/*___________________________________________________________________________________________________________________*/