#include "equipas.h"
#include "jogos.h"

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Hash_Jogo *STinit_jogos(int m)  /*recebe tamanho da hash e inicia a hash*/
{
    int i;
    Hash_Jogo *HashTable = (Hash_Jogo *)malloc(sizeof(Hash_Jogo));
    linkjogo *heads;

    heads = malloc(m * sizeof(linkjogo));
    for (i = 0; i < m; i++)
        heads[i] = NULL;

    HashTable->heads = heads;

    return HashTable;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

linkjogo lookup_jogo(linkjogo head, char *name) /*percorre a lista para encontrar dar search do nome, auxiliar da search*/
{
    linkjogo t;
    for (t = head; t != NULL; t = t->nextHash)
    {
        if (strcmp(t->jogo->name, name) == 0)
        {
            return t;
        }
    }
    return NULL;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

linkjogo STsearch_jogo(Hash_Jogo *HashTable, char name[], int m) /*faz search na hashtable de um nome*/
{
    linkjogo *heads;
    int i;
    heads = HashTable->heads;
    i = hashU(name, m);                 /*recebe nome do jogo*/
    return lookup_jogo(heads[i], name); /*da return dum ponteiro po jogo*/
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


jogo NEW_jogo(Hash *HashTable, char *buffer, char equipa1[], char equipa2[], int score1, int score2,
              int m) /*cria uma estrutura do novo elemento, auxiliar da insertBegin*/
{
    link s, t;
    jogo x;
    x = malloc(sizeof(struct jogo));
    x->name = strdup(buffer);
    t = STsearch(HashTable, equipa1, m);
    x->equipa1 = t->equipa;
    s = STsearch(HashTable, equipa2, m);
    x->equipa2 = s->equipa;
    x->score1 = score1;
    x->score2 = score2;

    return x;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

linkjogo insertBegin_jogo(Hash *HashTable, linkjogo head, char name[], char equipa1[],
                          char equipa2[], int score1, int score2, int m)
{      /*auxiliar da STinsert permite adicionar novo jogo na lista de uma "fila" da hash, auxiliar da STinsert*/
    linkjogo y;
    jogo x;
    y = (struct nodejogo *)malloc(sizeof(struct nodejogo));

    x = NEW_jogo(HashTable, name, equipa1, equipa2, score1, score2, m);

    if (head == NULL)                 /*caso nao existam elementos nessa lista da hash*/
    {

        y->jogo = x;
        y->nextHash = NULL;
        y->previousHash = NULL;

        return y;
    }

    y->jogo = x;
    head->previousHash = y;
    y->nextHash = head;
    y->previousHash = NULL;

    return y;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void STinsert_jogo(Hash *HashTable, Hash_Jogo *HashTablejogo, char name[], char equipa1[], char equipa2[], int score1, int score2, int m, int m_jogo) /*JOGOS*/
{  /*funcao que permite inserir um jogo dado um nome scores e equipas*/
    linkjogo *heads;
    int i;
    heads = HashTablejogo->heads;
    i = hashU(name, m_jogo);
    heads[i] = insertBegin_jogo(HashTable, heads[i], name, equipa1, equipa2, score1, score2,
                                m);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

list *STinit_Lista_ordenada() /*inicializa lista ordenada*/
{
    list *lst;
    lst = (list *)malloc(sizeof(list));
    lst->head = NULL;
    lst->tail = NULL;
    return lst;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void add_last(list *lista, char name[], Hash_Jogo *HashTable, int m)  /*adiciona no final da lista ordenada um jogo recebe nome ponteiro para lista e hash do jogo*/
{

    linkordenado *lst;
    linkjogo t;
    linkordenado *antiga_tail;
    lst = (linkordenado *)malloc(sizeof(linkordenado));
    t = STsearch_jogo(HashTable, name, m);
    lst->nextLista = NULL;
    lst->previouslista = NULL;
    lst->jogo = t->jogo;

    if (lista->head == NULL)  /*caso nao existam elementos na lista*/
    {
        lista->head = lst;
        lista->tail = lst;
    }

      else
    {
        antiga_tail = lista->tail;        /*em qualquer outro caso*/
        antiga_tail->nextLista = lst;
        lst->previouslista = antiga_tail;
        lista->tail = lst;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void free_lista(list *lst) /*apagar a lista ordenada*/
{

    linkordenado *head;
    linkordenado *next;

    for (head = lst->head; head != NULL;)
    {
        next = head->nextLista;
        free(head);
        head = next;
    }

    free(lst);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void procurar_ordenado(list *ponteiro_lista_unica, linkjogo linkjogo) /*procura e apaga um jogo da lista ordenada*/
{
    linkordenado *y, *yantes, *ydepois;
    y = ponteiro_lista_unica->head;
    while (strcmp(y->jogo->name, linkjogo->jogo->name) != 0)
    {
        y = y->nextLista;
    }

    if ((y->previouslista == NULL) && (y->nextLista != NULL))            /*caso elemento a apagar seja um head*/
    {
        ydepois = y->nextLista;
        ydepois->previouslista = NULL;
        ponteiro_lista_unica->head = ydepois;
    }
    else if ((y->previouslista != NULL) && (y->nextLista == NULL))     /*caso elemento a apagar seja um tail*/
    {
        yantes = y->previouslista;
        yantes->nextLista = NULL;
        ponteiro_lista_unica->tail = yantes;
    }
    else if ((y->previouslista == NULL) && (y->nextLista == NULL))  /*caso elemento a apagar seja unico numa lista*/
    {
        ponteiro_lista_unica->head = NULL;
        ponteiro_lista_unica->tail = NULL;
    }
    else
    {
        yantes = y->previouslista;
        ydepois = y->nextLista;
        yantes->nextLista = ydepois;
        ydepois->previouslista = yantes;
    }
    free(y);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void deletejogos(linkjogo head) /*apagar jogos auxiliar*/
{
    linkjogo t, t2;
    t = head;

    while (t != NULL)
    {

        free(t->jogo->name);
        free(t->jogo);
        t2 = t->nextHash;
        free(t);
        t = t2;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void STdeletejogos(Hash_Jogo *HashTable, int tamanhohash) /*apagar jogos*/
{

    linkjogo *heads;
    int m = 0;
    heads = HashTable->heads;

    while (m < tamanhohash)
    {

        deletejogos(heads[m]);
        m++;
    }

    free(HashTable->heads);
    free(HashTable);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
