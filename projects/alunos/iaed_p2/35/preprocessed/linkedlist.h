#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "jogo.h"
#include "equipa.h"


#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct nodeJogo *linkJogo;
typedef struct nodePJogo *linkPJogo;

typedef struct nodeEquipa *linkEquipa;
typedef struct nodePEquipa *linkPEquipa;

/*nodo da lista de jogos*/
struct nodeJogo {
    jogo j;
    linkJogo next;
};

/*nodo da hash table de ponteiros para jogos*/
struct nodePJogo {
    linkJogo j;
    linkPJogo next;
};

/*nodo da lista de equipas*/
struct nodeEquipa {
    equipa e;
    linkEquipa next;
};

/*nodo da hash table de ponteiros para equipas*/
struct nodePEquipa {
    linkEquipa e;
    linkPEquipa next;
};


/*funcoes que manipulam a lista de jogos*/
/*funcao que insere um nodo na lista de jogos*/
linkJogo insertNodeJogo(linkJogo *head, jogo j);

/*funcao que apaga um nodo na lista de jogos*/
void deleteNodeJogo(struct nodeJogo **head, jogo j);

/*funcao que apaga toda a lista de jogos*/
void deleteListJogo(linkJogo *head);

/*funcoes que manipulam a lista de equipas*/
/*funcao que insere um nodo na lista de equipas*/
linkEquipa insertNodeEquipa(linkEquipa *head, equipa e);

/*funcao que apaga um nodo na lista de equipas*/
void deleteNodeEquipa(struct nodeEquipa **head, equipa e);

/*funcao que apaga toda a lista de equipas*/
void deleteListEquipa(linkEquipa *head);


#endif /*LINKEDLIST_H_INCLUDED*/