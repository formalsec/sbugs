#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _JOGOS_
#define _JOGOS_
#define DIM 10001
#define DIMJOGOS 13009

typedef struct jogo       /*estrutura do jogo*/
{
    char *name;
    equipas equipa1, equipa2;
    int score1, score2;
} * jogo;

typedef struct nodejogo /*estrutura dum ponteiro para um jogo */
{
    jogo jogo;
    struct nodejogo *nextHash, *previousHash;
} * linkjogo;

typedef struct nodeordenado /*estrtura dos jogos ordenados*/
{
    jogo jogo;
    struct nodeordenado *nextLista, *previouslista;
} linkordenado;

typedef struct list /*estrutura dum ponteiro para jogos ordenados */
{
    struct nodeordenado *head, *tail;
} list;

typedef struct hash_jogo /*estrutra da hash*/
{
    linkjogo *heads;
} Hash_Jogo;

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

/*funcao que permite inserir um jogo dado um nome scores e equipas*/
void STinsert_jogo(Hash *HashTable, Hash_Jogo *HashTablejogo, char name[], char equipa1[], char equipa2[], int score1, int score2, int m, int m_jogo);

/*incializacao da hash jogos*/
Hash_Jogo *STinit_jogos(int m);

/*percorre a lista para encontrar dar search do nome, auxiliar da search*/
linkjogo lookup_jogo(linkjogo head, char *name);

/*faz search na hashtable de um nome*/
linkjogo STsearch_jogo(Hash_Jogo *HashTable, char name[], int m);

/*cria uma estrutura do novo elemento, auxiliar da insertBegin*/
jogo NEW_jogo(Hash *HashTable, char *buffer, char equipa1[], char equipa2[], int score1, int score2, int m);

/*auxiliar da STinsert permite adicionar novo jogo na hash, auxiliar da STinsert*/
linkjogo insertBegin_jogo(Hash *HashTable, linkjogo head, char name[], char equipa1[], char equipa2[], int score1, int score2, int m);

/*inicializa lista ordenada*/
list *STinit_Lista_ordenada();

/*adiciona no final da lista ordenada um jogo recebe nome ponteiro para lista e hash do jogo*/
void add_last(list *lista, char name[], Hash_Jogo *HashTable, int m);

/*apagar a lista ordenada*/
void free_lista(list *lst);

/*procura e apaga um jogo da lista ordenada*/
void procurar_ordenado(list *ponteiro_lista_unica, linkjogo linkjogo);

/*apagar jogos auxiliar*/
void deletejogos(linkjogo head);

/*apagar jogos*/
void STdeletejogos(Hash_Jogo *HashTable, int tamanhohash);


#endif
