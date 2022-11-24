#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipas.h"
#include "jogos.h"









/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


int hashU(char *v, int m)        /*funcao que recebe uma string e devolve um numero fruto da funcao feita*/
{
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (m - 1))
        h = (a * h + *v) % m;
    return h;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

char *strdup(const char *palavra)   /*can_fail_malloc e string copy*/
{
    char *ponteiro;
    ponteiro = can_fail_malloc(strlen(palavra) + 1);

    if (ponteiro == NULL)
    {
        return ponteiro;
    }
    else
    {
        strcpy(ponteiro, palavra);
        return ponteiro;
    }
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Hash *STinit(int m)               /*incializacao da hash equipas, recebe tamanho da hash*/
{
    int i;
    link *heads;
    Hash *HashTable = (Hash *)can_fail_malloc(sizeof(Hash));

    heads = can_fail_malloc(m * sizeof(link));
    for (i = 0; i < m; i++)
        heads[i] = NULL;

    HashTable->heads = heads;

    return HashTable;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

link lookup(link head, char *name)   /*percorre a lista para encontrar dar search do nome, auxiliar da search*/
{
    link t;
    for (t = head; t != NULL; t = t->next)
        if (strcmp(t->equipa->name, name) == 0)
            return t;
    return NULL;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

link STsearch(Hash *HashTable, char name[], int m)    /*faz search na hashtable de um nome*/
{
    link *heads;
    int i;
    heads = HashTable->heads;
    i = hashU(name, m);            /*recebe nome da equipa*/
    return lookup(heads[i], name); /*da return dum ponteiro pa equipa*/
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

equipas NEW(char *buffer)  /*(insere na lista o novo) cria uma estrutura do novo elemento, auxiliar da insertBegin*/
{
    equipas x;
    x = can_fail_malloc(sizeof(struct equipas));
    x->name = strdup(buffer);
    x->vitorias = 0;
    return x;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

link insertBegin(link head, char text[]) /*auxiliar da STinsert permite adicionar nova equipa na hash, auxiliar da STinsert*/
{
    link y;
    equipas x;
    y = (struct node *)can_fail_malloc(sizeof(struct node));

    x = NEW(text);

    if (head == NULL)
    {

        y->equipa = x;
        y->next = NULL;
        y->previous = NULL;

        return y;
    }

    y->equipa = x;
    head->previous = y;
    y->next = head;
    y->previous = NULL;

    return y;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void STinsert(Hash *HashTable, char name[], int m)       /*funcao que permite inserir uma equipa dado um nome*/
{
    link *heads;
    int i;
    heads = HashTable->heads;
    i = hashU(name, m);
    heads[i] = insertBegin(heads[i], name);
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int comparator(const void *p, const void *q)         /*funcao de comparacao para ordenacao da g*/
{
    struct node *l;
    struct node *r;
    l = *(struct node **)p;
    r = *(struct node **)q;
    return strcmp(l->equipa->name, r->equipa->name);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void delete (link head)                      /*apagar equipas auxiliar*/
{

    link t, t2;

    t = head;
    while (t != NULL)
    {
        free(t->equipa->name);
        free(t->equipa);
        t2 = t->next;
        free(t);
        t = t2;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void STdelete(Hash *HashTable, int tamanhohash)              /*apagar equipas*/
{

    link *heads;
    int m = 0;
    heads = HashTable->heads;

    while (m < tamanhohash)
    {
        delete (heads[m]);
        m++;
    }
    free(HashTable->heads);
    free(HashTable);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
