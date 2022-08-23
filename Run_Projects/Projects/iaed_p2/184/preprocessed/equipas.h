#ifndef EQUIPAS_H
#define EQUIPAS_H

typedef struct node{
    /*nome_equipa e um ponteiro para o nome de uma equipa.*/
    char *nome_equipa;
    /*vitorias armazena o numero de vitorias da equipa.*/
    int vitorias;
    /*next e um ponteiro para outro NodeEquipa (o seguinte numa lista de nodes).*/
    struct node *next;
} NodeEquipa;
typedef NodeEquipa* linkE;

/*Funcao freeE liberta toda a memoria alocada para armazenar NodesEquipa.*/
void freeE(linkE* head);

/*Funcao NOVO_E cria um novo NodeEquipa.*/
linkE NOVO_E(char* nome);

/*Funcao insereInicio_E insere uma struct de uma equipa no inicio de uma fila de 
NodesEquipa.*/
void insereInicio_E(linkE *headptr, char *nome);

/*Funcao encontra_E procura numa fila de NodesEquipa um NodeEquipa especifico e 
devolve-o.*/
linkE encontra_E(linkE head, char *nome);

#endif