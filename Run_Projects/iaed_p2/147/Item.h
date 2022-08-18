#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Estrutura jogo que representa um jogo no sistema. */
typedef struct jogo{
    struct jogo *next, *previous;
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1; 
    int score2;
    char *vencedora;
}*pJogo;  

/* Estrutura link que representa um no da hashtable dos jogos. */
typedef struct link{
    pJogo j;
    struct link *next;
}*pLink;


/* Estrutura equipa que representa uma equipa no sistema. */
typedef struct equipa{
    char *nome_e; 
    int wins;
}*pEquipa;


/* Estrutura link_e que representa um no da hashtable das equipas. */
typedef struct link_e{
    pEquipa e;
    struct link_e *next;
}*pLink_e;


/* Estrutura ht que representa a hastable que armazena os jogos. */
typedef struct ht{
    pLink *heads;
    int M;
}*pHash;


/* Estrutura ht_e que representa a hastable que armazena as equipas. */
typedef struct ht_e{
    pLink_e *heads_e;
    int M;
}*pHash_e;


/* Estrutura list que representa uma lista que armazena os jogos. */
typedef struct list{
    struct jogo *head, *last;
}*pList;


/* Prototipo da funcao auxiliar dup. */
char *dup(const char *s);


/* Prototipos das funcoes referente a estrutura jogo. */
pJogo cria_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2);
void free_jogo(pJogo j );


/* Prototipo da funcao referente a estrutura equipa. */
pEquipa cria_equipa(char *nome_e);


/* Prototipo da funcao referente a estrutura link_e, que eh uma entrada da hash dos jogos. */
void free_link(pLink l);


/* Prototipo da funcao referente a estrutura link, que eh uma entrada da hash das equipas. */
void free_link_e(pLink_e l);


/* Prototipos das funcoes referente a estrutura list, a lista de jogos. */
pList list_init();
void free_list(pList l);
void list_insert(pList l, pJogo novo);
void list_delete(pList l, pJogo j);
