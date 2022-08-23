#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aux.h"
#include "hash_j.h"
#include "hash_eq.h"

/* Constante que indica o numero maximo de caracteres das strings. */
#define MAX 1024
/* Constante que indica o tamanho da hash. */
#define HASH 1057

/*Prototipos de funcoes*/
void adiciona_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL);
void procura_jogo(hash_j hash_j, int NL);
void adiciona_equipa(hash_eq hash_eq, int NL);
void procura_equipa(hash_eq hash_eq, int NL);
void remove_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL);
void altera_score(hash_j hash_j, hash_eq hash_eq, int NL);
void lista_jogos(list ls, int NL);
void lista_equipas(hash_eq hash, int NL);

int main()
{
    /* Variavel que guardar o comando inserido pelo utilizador. */
    int comando;
    /* Variavel que guardar o numero da linha do comando de input. */
    int NL=1;
    /* Inicializacao da hashtable para os jogos. */
    hash_j hash_j = init_hash_jogo(HASH);
    /* Inicializacao da hashtable para as equipas. */
    hash_eq hash_eq = init_hash_eq(HASH);
    /* Inicializacao da lista duplamente ligada que guarda os jogos por ordem de insercao. */
    list ls = new_list();

    while((comando=getchar())!=EOF)
    {
        /* Seleciona a operacao correta para cada comando inserido. */
        switch(comando)
        {
            case 'a':
                adiciona_jogo(ls, hash_j, hash_eq, NL);
                break;

            case 'p':
                procura_jogo(hash_j, NL);
                break;

            case 'A':
                adiciona_equipa(hash_eq, NL);
                break;

            case 'P':
                procura_equipa(hash_eq, NL);

                break;

            case 'r':
                remove_jogo(ls, hash_j, hash_eq, NL);
                break;

            case 's':
                altera_score(hash_j, hash_eq, NL);
                break;

            case 'l':
                lista_jogos(ls, NL);
                break;

            case 'g':
                lista_equipas(hash_eq, NL);
                break;

            case 'x':
                freeHash_j(hash_j);
                freeHash_eq(hash_eq);
                free_list(ls);
                return EXIT_SUCCESS;
        
            default:
                fprintf(stderr, "Invalid input!\n");
                return EXIT_FAILURE;
        }
        getchar();
        NL++;
    }
    return 0;
}

/* Funcao que adiciona um jogo a hashtable e a lista duplamente ligada. */
void adiciona_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL)
{
    /* Ponteiro para uma variavel jogo generica. */
    pJogo j;
    /* Variaveis que guardam o valor do score 1 e 2 inseridos pelo utilizador. */
    int sc1, sc2;
    /* Variaveis que guardam o do nome do jogo e das equipas inseridos pelo utilizador. */
    char n_jogo[MAX], eq1[MAX], eq2[MAX];

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", n_jogo, eq1, eq2, &sc1, &sc2);

    if(STsearch_jogo(hash_j, n_jogo))
    {
        printf("%d Jogo existente.\n", NL);
        return;
    }
    else if( !STsearch_eq(hash_eq, eq1) || !STsearch_eq(hash_eq, eq2))
    {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
   
    j=cria_jogo(n_jogo, eq1, eq2, sc1, sc2, ls);

    if(j->vencedora) STsearch_eq(hash_eq, j->vencedora)->wins++;

    STinsert_jogo(hash_j, j);

}

/* Funcao que procura um jogo na hashtable. */
void procura_jogo(hash_j hash_j, int NL)
{
    /* Ponteiro para uma variavel jogo generica. */
    pJogo j;
    /* Variavel que guarda o nome do jogo inserido pelo utilizador. */
    char n_jogo[MAX];

    scanf(" %[^:\n]", n_jogo);

    j=STsearch_jogo(hash_j, n_jogo);

    if(!j)
    {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    printf("%d ", NL);
    print_j(j);
}

/* Funcao que adiciona uma equipa a hashtable. */
void adiciona_equipa(hash_eq hash_eq, int NL)
{
    /* Ponteiro para uma variavel equipa generica. */
    pEquipa eq;
    /* Variavel que guarda o nome da quipa inserido pelo utilizador. */
    char n_eq[MAX];

    scanf(" %[^:\n]", n_eq);

    if(STsearch_eq(hash_eq, n_eq))
    {
        printf("%d Equipa existente.\n", NL);
        return;
    }

    eq=cria_equipa(n_eq);

    STinsert_eq(hash_eq, eq);
}

/* Funcao que procura uma equipa na hashtable. */
void procura_equipa(hash_eq hash_eq, int NL)
{
    /* Ponteiro para uma variavel equipa generica. */
    pEquipa eq;
    /* Variavel que guarda o nome da quipa inserido pelo utilizador. */
    char n_eq[MAX];

    scanf(" %1023[^:\n]", n_eq);

    eq=STsearch_eq(hash_eq, n_eq);

    if(!eq)
    {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    printf("%d ", NL);
    print_eq(eq);
}

/* Funcao que remove um jogo da hashtable e da lista duplamente ligada. */
void remove_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL)
{
    /* Ponteiro para uma variavel jogo generica. */
    pJogo j;
    /* Variavel que guarda o nome do jogo inserido pelo utilizador. */
    char n_jogo[MAX];

    scanf(" %[^:\n]", n_jogo);

    j=STsearch_jogo(hash_j, n_jogo);

    if(!j)
    {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    if(j->vencedora) STsearch_eq(hash_eq, j->vencedora)->wins--;

    remove_el(ls, j);
    STdelete_jogo(hash_j, n_jogo);
}

/* Funcao que altera o score de um determinado jogo. */
void altera_score(hash_j hash_j, hash_eq hash_eq, int NL)
{
    /* Ponteiro para uma variavel jogo generica. */
    pJogo j;
    /* Variaveis que guardam o valor do score 1 e 2 inseridos pelo utilizador. */
    int sc1, sc2;
    /* Ponteiro para uma variavel que guarda a vencedora antes da alteracao dos scores. */
    char *old_vencedora=NULL;
    /* Variavel que guarda o nome do jogo inserido pelo utilizador. */
    char n_jogo[MAX];

    scanf(" %[^:\n]:%d:%d", n_jogo, &sc1, &sc2);

    j = STsearch_jogo(hash_j, n_jogo);

    if(!j)
    {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    if(j->vencedora) old_vencedora=strdup(j->vencedora);

    altera_score_aux(j, sc1, sc2);

    corrige_wins(hash_eq, j, old_vencedora);

    if(old_vencedora) free(old_vencedora);
}

/* Funcao que lista os jogos por ordem de insercao. */
void lista_jogos(list ls, int NL)
{
    print_list(ls, NL);
}

/* Funcao que lista as equipas que ganharam mais jogos por ordem lexicografica. */
void lista_equipas(hash_eq hash, int NL)
{
    /* Variavel que guarda o numero maximo de vitorias. */
    int max=0;
    /* Variavel que guarda o numero de equipas com o numero maximo de vitorias. */
    int num_eq=0;

    calcula_max(hash, &max, &num_eq);

    if(num_eq==0) return;

    imprime_vencedoras(hash, max, num_eq, NL);
}

