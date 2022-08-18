#ifndef JOGOS_H
#define JOGOS_H

typedef struct node2{
    /*nome_jogo e um ponteiro para o nome do jogo.*/
    char *nome_jogo;
    /*equipa1 e um ponteiro para o nome da primeira equipa.*/
    char *equipa1;
    /*equipa2 e um ponteiro para o nome da segunda equipa.*/
    char *equipa2;
    /*golos1 armazena um inteiro correspondente aos golos da equipa1.*/
    int golos1;
    /*golos2 armazena um inteiro correspondente aos golos da equipa2.*/
    int golos2;
    /*next e um ponteiro para outro NodeJogo (o seguinte numa lista de nodes).*/
    struct node2 *next;
    /*prev e um ponteiro para outro NodeJogo (o anterior numa lista de nodes).*/
    struct node2 *prev; 
} NodeJogo;
typedef NodeJogo* linkJ;

/*Funcao freeJ liberta toda a memoria alocada para armazenar NodesJogo.*/
void freeJ(linkJ *headd);

/*Funcao NOVO_J cria um novo NodeJogo.*/
linkJ NOVO_J(char *jogo, char *e1, char *e2, int p1, int p2);

/*Funcao insereInicio_J insere uma struct de um jogo no inicio de uma fila de NodesJogo.*/
void insereInicio_J(linkJ *headptr, char *jogo, char *e1, char *e2, int p1, int p2);

/*Funcao encontra_J procura numa fila de NodesJogo um NodeJogo especifico e devolve-o.*/
linkJ encontra_J(linkJ head, char *jogo);

/*Funcao elimina_J procura um NodeJogo numa fila de NodesJogo e elimina-o.*/
void elimina_J(linkJ *headptr, char *jogo);

#endif

