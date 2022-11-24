#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipas.h"
#include "jogos.h"

#define DIM 10001
#define DIMJOGOS 13009
#define MILVINTEQUATRO 1024

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaoa(Hash_Jogo *HashTableJogo, Hash *HashTableEquipas, int nl, list *ponteiro_lista_unica)  /*adiciona novo jogo recebe hashs e ponteiro_lista_unica*/
{

    char palavra1[MILVINTEQUATRO], palavra2[MILVINTEQUATRO], palavra3[MILVINTEQUATRO];
    int a, b;
    link x, z;
    linkjogo y;

    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", palavra1, palavra2, palavra3, &a, &b);
    y = STsearch_jogo(HashTableJogo, palavra1, DIMJOGOS);

    if (y != NULL)
    {
        printf("%d Jogo existente.\n", nl);
        nl++;
        return;
    }

    x = STsearch(HashTableEquipas, palavra2, DIM);
    if (x == NULL)
    {
        printf("%d Equipa inexistente.\n", nl);
        nl++;
        return;
    }

    z = STsearch(HashTableEquipas, palavra3, DIM);
    if (z == NULL)
    {
        printf("%d Equipa inexistente.\n", nl);
        nl++;
        return;
    }

    STinsert_jogo(HashTableEquipas, HashTableJogo, palavra1, palavra2, palavra3, a, b, DIM, DIMJOGOS); /*meter equipa na hash*/

    add_last(ponteiro_lista_unica, palavra1, HashTableJogo, DIMJOGOS);        /*meter equipa na lista*/

    if (a > b)                                                                                  /*aumentar vitorias nas equipas*/
    {
        x->equipa->vitorias++;
    }
    else if (a < b)
    {
        z->equipa->vitorias++;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaol(list *ponteiro_lista_unica, int nl)  /*Lista todos os jogos introduzidos por ordem recebe ponteiro pa lista ordenada*/
{
    linkordenado *y;
    y = ponteiro_lista_unica->head;
    while (y != NULL)
    {
        printf("%d %s %s %s %d %d\n", nl, y->jogo->name, y->jogo->equipa1->name,
               y->jogo->equipa2->name, y->jogo->score1, y->jogo->score2);
        y = y->nextLista;
    }
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaop(Hash_Jogo *HashTableJogo, int nl)              /*Procura um jogo com o nome dado.*/
{

    char palavra1[MILVINTEQUATRO];
    linkjogo y;

    scanf(" %[^:\n]", palavra1);
    y = STsearch_jogo(HashTableJogo, palavra1, DIMJOGOS);
    if (y == NULL)
    {
        printf("%d Jogo inexistente.\n", nl);
        nl++;
        return;
    }
    printf("%d %s %s %s %d %d\n", nl, palavra1, y->jogo->equipa1->name,
           y->jogo->equipa2->name, y->jogo->score1, y->jogo->score2);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaor(Hash_Jogo *HashTableJogo, int m_jogo, int nl, list *ponteiro_lista_unica) /*recebe hash jogo dimensao da hash jogo e ponteiro pa
                                                                                        lista ordenada Apaga um jogo dado um nome.*/
{

    linkjogo y, yantes, ydepois, *heads;
    int i;
    char palavra1[MILVINTEQUATRO];

    scanf(" %[^:\n]", palavra1);
    heads = HashTableJogo->heads;
    i = hashU(palavra1, m_jogo);
    y = STsearch_jogo(HashTableJogo, palavra1, m_jogo);

    if (y == NULL)
    {
        printf("%d Jogo inexistente.\n", nl);
        nl++;
        return;
    }

    if (y->jogo->score1 > y->jogo->score2)              /*tratar assunto de vitorias por apagar jogo*/
    {
        y->jogo->equipa1->vitorias--;
    }
    else if (y->jogo->score1 < y->jogo->score2)
    {
        y->jogo->equipa2->vitorias--;
    }

    if ((y->previousHash == NULL) && (y->nextHash != NULL))         /*caso elemento a apagar seja um head*/
    {
        ydepois = y->nextHash;
        ydepois->previousHash = NULL;
        heads[i] = ydepois;
    }
    else if ((y->previousHash != NULL) && (y->nextHash == NULL))    /*caso elemento a apagar seja um tail*/
    {
        yantes = y->previousHash;
        yantes->nextHash = NULL;
    }
    else if ((y->previousHash == NULL) && (y->nextHash == NULL))  /*caso elemento a apagar seja unico numa lista*/
    {
        heads[i] = NULL;
    }
    else
    {
        yantes = y->previousHash;
        ydepois = y->nextHash;
        yantes->nextHash = ydepois;
        ydepois->previousHash = yantes;
    }

    procurar_ordenado(ponteiro_lista_unica, y);         /*apagar na lista ordenada*/
    free(y->jogo->name);
    free(y->jogo);
    free(y);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaos(Hash_Jogo *HashTableJogo, Hash *HashTableEquipas, int nl)      /*recebe duas hashtables  Altera o score de um jogo dado o nome e dois scores*/
{

    char palavra1[MILVINTEQUATRO];
    linkjogo y;
    link x, z;
    int a, b;

    scanf(" %[^:]:%d:%d", palavra1, &a, &b);
    y = STsearch_jogo(HashTableJogo, palavra1, DIMJOGOS);
    if (y == NULL)
    {
        printf("%d Jogo inexistente.\n", nl);
        nl++;
        return;
    }
    if ((y->jogo->score1 > y->jogo->score2) && (a <= b))          /* caso scores equipa 1 seja maior q equipa 2 e novo score seja <= alterar vitorias*/
    {
        x = STsearch(HashTableEquipas, y->jogo->equipa1->name, DIM);
        x->equipa->vitorias--;
        if ((y->jogo->score1 > y->jogo->score2) && (a < b))
        {
            z = STsearch(HashTableEquipas, y->jogo->equipa2->name, DIM);
            z->equipa->vitorias++;
        }
    }

    else if ((y->jogo->score1 < y->jogo->score2) && (a >= b))       /* caso scores equipa 1 < 2 e novos scores sejam >=*/
    {

        z = STsearch(HashTableEquipas, y->jogo->equipa2->name, DIM);
        z->equipa->vitorias--;
        if (a > b)
        {
            x = STsearch(HashTableEquipas, y->jogo->equipa1->name, DIM);
            x->equipa->vitorias++;
        }
    }

    else if (y->jogo->score1 == y->jogo->score2)              /* caso scores equipa 1 = equipa 2 e novos scores nao*/
    {
        if ((a < b))
        {
            z = STsearch(HashTableEquipas, y->jogo->equipa2->name, DIM);
            z->equipa->vitorias++;
        }
        else if (a > b)
        {
            x = STsearch(HashTableEquipas, y->jogo->equipa1->name, DIM);
            x->equipa->vitorias++;
        }
    }

    y->jogo->score1 = a;
    y->jogo->score2 = b;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaoA(Hash *HashTableEquipas, int nl)          /*adiciona equipa, recebe hashtable faz scan do nome e adiciona na hash*/
{

    char palavra[MILVINTEQUATRO];
    link x;

    scanf(" %[^:\n]", palavra);
    x = STsearch(HashTableEquipas, palavra, DIM);
    if (x != NULL)
    {
        printf("%d Equipa existente.\n", nl);
        nl++;
        return;
    }
    STinsert(HashTableEquipas, palavra, DIM);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaoP(Hash *HashTableEquipas, int nl)        /*procura de um nome, recebe hashtable e faz scan do nome devolve equipa*/
{

    char palavra[MILVINTEQUATRO];
    link x;

    scanf(" %[^:\n]", palavra);
    x = STsearch(HashTableEquipas, palavra, DIM);   /*fazer search para encontrar equipa*/
    if (x == NULL)
    {
        printf("%d Equipa inexistente.\n", nl);
        nl++;
        return;
    }
    printf("%d %s %d\n", nl, x->equipa->name, x->equipa->vitorias);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaog(Hash *HashTable, int m, int nl)                /*recebe hash table equipas e tamanho has equipas*/
{
    link *heads = HashTable->heads;
    link t, *array;
    int x = 0, v = 0, contador = 0;
    array = can_fail_malloc(sizeof(link));

    while (x < m)                                         /*percorrer heads da hashtable*/
    {

        for (t = heads[x]; t != NULL; t = t->next)                /*percorrer lista da hastable correspondente a uma hashfunction*/
        {

            if (t->equipa->vitorias > v)
            {
                v = t->equipa->vitorias;
                free(array);
                array = can_fail_malloc(sizeof(link));                      /*re mallocar caso max de vitorias altere*/
                array[0] = t;
                contador = 1;
            }
            else if (t->equipa->vitorias == v)
            {
                contador++;
                array = can_fail_realloc((void *)array, sizeof(link) * contador);      /*fazer can_fail_realloc caso haja mais uma equipa com mesmas vitorias*/
                array[contador - 1] = t;
            }
        }

        x++;
    }
    qsort(array, contador, sizeof(struct node *), comparator);            /*ordenar para printar*/

    if (contador != 0)
    {
        printf("%d Melhores %d\n", nl, array[0]->equipa->vitorias);
    }

    for (x = 0; x < contador; x++)
    {
        printf("%d * %s\n", nl, array[x]->equipa->name);
    }
    free(array);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void funcaox(Hash *HashTableEquipas, Hash_Jogo *HashTableJogo, list *ponteiro_lista_unica)  /*fazer free de todos os can_fail_mallocs no projeto*/
{
    STdelete(HashTableEquipas, DIM);
    STdeletejogos(HashTableJogo, DIMJOGOS);
    free_lista(ponteiro_lista_unica);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int main()
{

    char c;
    int nl = 1;
    list *ponteiro_lista_unica;
    Hash *HashTableEquipas;
    Hash_Jogo *HashTableJogo;

    ponteiro_lista_unica = STinit_Lista_ordenada();

    HashTableEquipas = STinit(DIM);

    HashTableJogo = STinit_jogos(DIMJOGOS);

    for (;;)
    {

        switch (c = getchar())
        {
        case 'a':
            funcaoa(HashTableJogo, HashTableEquipas, nl, ponteiro_lista_unica);
            nl++;
            break;

        case 'l':
            funcaol(ponteiro_lista_unica, nl);
            nl++;
            break;

        case 'p':
            funcaop(HashTableJogo, nl);
            nl++;
            break;

        case 'r':
            funcaor(HashTableJogo, DIMJOGOS, nl, ponteiro_lista_unica);
            ++nl;
            break;

        case 's':
            funcaos(HashTableJogo, HashTableEquipas, nl);
            nl++;
            break;

        case 'A':
            funcaoA(HashTableEquipas, nl);
            nl++;
            break;

        case 'P':
            funcaoP(HashTableEquipas, nl);
            nl++;
            break;

        case 'g':
            funcaog(HashTableEquipas, DIM, nl);
            nl++;
            break;

        case 'x':
            funcaox(HashTableEquipas, HashTableJogo, ponteiro_lista_unica);
            return 0;
        }
    }
    return 0;
}
