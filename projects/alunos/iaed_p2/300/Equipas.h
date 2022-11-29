#ifndef Equipas
#define Equipas

typedef struct Equipa /* Estrutura das equipas */
{
    char *nome;
    int vitorias;
    struct Equipa *next;
} * pEquipa;

int hash(char *nome, int m);                         /* Funcao que identifica em que index da hastable e que o jogo esta */
pEquipa NEW(char *nome);                             /* Funcao que cria uma equipa */
pEquipa insertBeginList(pEquipa head, char *nome);   /* Funcao auxiliar de STinsert*/
pEquipa removeEquipaList(pEquipa head, char *nome);  /* Funcao auxiliar de STdelete */
pEquipa searchList(pEquipa head, char *nome);        /* Funcao auxiliar de STsearch*/
pEquipa *STinit(int m);                              /* Funcao que inicializa a hashtable das equipas*/
void STinsert(pEquipa *heads, char *nome, int m);    /* Funcao que insere uma equipa ao inicio da lista de um determinado index da hashtable*/
void STdelete(pEquipa *heads, char *nome, int m);    /* Funcao que remove uma equipa da lista de um determinado index da hashtable */
pEquipa STsearch(pEquipa *heads, char *nome, int m); /* Funcao que procura se uma determinada equipa faz parte da hashtable */
void freeEquipa(pEquipa a);                          /* Funcao que da free a um determinada equipa */
void printEquipa(pEquipa a, int nl);                 /* Funcao que da print a uma equipa */
#endif