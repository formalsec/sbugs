#ifndef LISTA_H
#define LISTA_H


/* Definicao de um ponteiro para uma estrutura Node. */
typedef struct node
{
    Jogo Jogo;
    struct node* next;

}Node;

typedef Node* link;


/* Prototipos de funcoes referentes ahs listas */
link NewNode(Jogo Jogo);
void insertEnd(link* head, link* tail, Jogo Jogo);
void delete(link* head, link* tail, Jogo Jogo);
void printLista(link head, int* N_linhas);
void freeLista(link head);

#endif

