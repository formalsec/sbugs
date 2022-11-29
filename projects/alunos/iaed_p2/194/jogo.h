#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ponteiro de um elemeto da lista */
typedef struct QUEUEnode *qlink;
/* ponteiro do jogo */
typedef struct Jogo{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
    qlink novoJogo;
} *pJogo;

/*******************************HashTable*************************************************/
/* copia duplicada da string passada executando um malloc e strcpy da string passada */
char *strdup(const char *src);
/* hash string retorna um numero inteiro para um string */
int goodHash(char *str, int max);
/* inicializar hashTable de jogo */
pJogo* JOGOinit(int max, pJogo *tabJ);
/* adiciona um jogo em hashTable */
void JOGOinsert(pJogo jogo, pJogo *tabJ, int max);
/* procura um jogo em hashTable */
pJogo JOGOsearch(char *nome, pJogo *tabJ, int max);
/* apaga um jogo no hashTable */
void JOGOdelete(char *nome, pJogo *tabJ, int max);
/* expande o hashTable */
pJogo* JOGOexpand(pJogo *tabJ, int max);

/* lista de jogo */
struct QUEUEnode {
    pJogo jogo;
    qlink next;
    qlink prev;
};
/* lista de jogo com head, tail e tamanho */
typedef struct MasterNode{
    int load;
    qlink head;
    qlink tail;
}* DLinkedList;

/*****************************LinkedList*********************************************/
/* inicializa a lista do jogo */
DLinkedList JOGOlist_init();
/* adiciona um jogo no fim da lista */
qlink JOGOappend(DLinkedList list, pJogo jogo);
/* aluga o espaco e ponha no fim da lista */
qlink addNode(qlink prev, qlink next, pJogo jogo);
/* mostra todos os jogo */
void JOGOlist(int contComandos, DLinkedList list);
/* apaga um jogo */
void JOGOQdelete(qlink jogo, DLinkedList list);
/* apaga um jogo no inicio da lista*/
void pop(DLinkedList list);
/* apaga um jogo no fim da lista*/
void removeLastNode(DLinkedList list);


#endif

