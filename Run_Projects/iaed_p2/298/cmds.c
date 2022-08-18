#include "jogos_linked.h"
#include "jogos_hash.h"
#include "equipas.h"
#include "aux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funcao que adiciona um jogo ao sistema.
    Retorna mensagem de erro caso:
        *jogo a adicionar ja exista no sistema
        *jogo contenha equipas que nao existam no sistema*/
void command_a(int * nl, JOGO_HASH ** hashtable_jogos, 
                    JOGO_LIST * lista_de_jogos, EQUIPA ** hashtable_equipas)
{
    int score1, score2;
    char nome[TAM_NOME], equipa1[TAM_NOME], equipa2[TAM_NOME];
    JOGO * novo_jogo, * jogo_procurado;
    EQUIPA * equipa1_procurada, * equipa2_procurada;

    scanf(" %[^:\n]s", nome);
    scanf(":%[^:\n]", equipa1);
    scanf(":%[^:\n]", equipa2);
    scanf(":%d:%d", &score1, &score2);

    jogo_procurado = procura_jogo(hashtable_jogos, nome);

    if (jogo_procurado != NULL) printf("%d Jogo existente.\n", *nl);
    else
    {
        equipa1_procurada = procura_equipa(hashtable_equipas, equipa1);

        if (equipa1_procurada == NULL) printf("%d Equipa inexistente.\n", *nl);
        else 
        {
            equipa2_procurada = procura_equipa(hashtable_equipas, equipa2);

            if (equipa2_procurada == NULL) printf("%d Equipa inexistente.\n", *nl);
            else 
            {
                novo_jogo = cria_jogo(lista_de_jogos, nome, equipa1, equipa2, score1, score2);
                add_jogo_hash(hashtable_jogos, novo_jogo);

                if (score1 > score2) add_score(hashtable_equipas, equipa1);
                else if (score1 < score2) add_score(hashtable_equipas, equipa2);
            }
        }
    }
}

/*Funcao que lista todos os jogos existentes no sistema pela ordem de introducao na forma:
    * nl nome-jogo nome-equipa1 nome-equipa2 score1 score2*/
void command_l(int * nl, JOGO_LIST * lista_de_jogos)
{
    JOGO * tmp = lista_de_jogos -> head;

    while(tmp != NULL)
    {
        escreve_jogo(nl, tmp);
        tmp = tmp -> next;
    }
}

/*Funcao que procura um jogo dado um nome e lista-o na forma:
    * nl nome-jogo nome-equipa1 nome-equipa2 score1 score2
    Retorna mensagem de erro caso:
        *jogo com nome dado nao exista no sistema*/
void command_p(int * nl, JOGO_HASH ** hashtable_jogos)
{
    char nome[TAM_NOME];
    JOGO * jogo_procurado;

    scanf(" %[^:\n]s", nome);

    jogo_procurado = procura_jogo(hashtable_jogos, nome);

    if (jogo_procurado == NULL) printf("%d Jogo inexistente.\n", *nl);

    else escreve_jogo(nl, jogo_procurado);
}

/*Funcao que remove um jogo do sistema dado um nome.
    Retorna mensagem de erro caso:
        *jogo com nome dado nao exista no sistema*/
void command_r(int * nl, JOGO_HASH ** hashtable_jogos, 
                    EQUIPA ** hashtable_equipas, JOGO_LIST * lista_de_jogos)
{
    char nome[TAM_NOME];
    char * nome_equipa_win;
    JOGO * jogo_eliminar;

    scanf(" %[^:\n]s", nome);

    jogo_eliminar = procura_jogo(hashtable_jogos, nome);

    if (jogo_eliminar == NULL) printf("%d Jogo inexistente.\n", *nl);
    else
    {
        nome_equipa_win = maior_score_jogo(hashtable_jogos, nome);
        if (nome_equipa_win != NULL) remove_score(hashtable_equipas, nome_equipa_win);

        remove_jogo(hashtable_jogos, lista_de_jogos, nome);
    }
}

/*Funcao que altera o score de um jogo dado um nome.
    Retorna mensagem de erro caso:
        *jogo com nome dado nao exista no sistema*/
void command_s(int * nl, JOGO_HASH ** hashtable_jogos, EQUIPA ** hashtable_equipas)
{
    char nome[TAM_NOME];
    char * nome_win, * nome_next_win;
    int score1, score2;
    JOGO * jogo_alterar;

    scanf(" %[^:\n]s", nome);
    scanf(":%d:%d", &score1, &score2);

    jogo_alterar = procura_jogo(hashtable_jogos, nome);

    if (jogo_alterar == NULL) printf("%d Jogo inexistente.\n", *nl);
    else
    {
        nome_win = maior_score_jogo(hashtable_jogos, nome);

        altera_score(hashtable_jogos, nome, score1, score2);

        nome_next_win = maior_score_jogo(hashtable_jogos, nome);

        if ((nome_win != NULL) && (nome_next_win != NULL) && 
            (strcmp(nome_win, nome_next_win) != 0)) 
        {
            add_score(hashtable_equipas, nome_next_win);
            remove_score(hashtable_equipas, nome_win);
        }
        else if ((nome_win != NULL) && (nome_next_win == NULL))
        {
            remove_score(hashtable_equipas, nome_win);
        }
        else if ((nome_win == NULL) && (nome_next_win != NULL))
        {
            add_score(hashtable_equipas, nome_next_win);
        }
    }
}

/*Funcao que adiciona uma equipa ao sistema.
    Retorna mensagem de erro caso:
        *equipa ja exista no sistema*/
void command_A(int * nl, EQUIPA ** hashtable_equipas)
{
    char nome[TAM_NOME];
    EQUIPA * nova_equipa;
    EQUIPA * equipa_procurada;

    scanf(" %[^:\n]s", nome);

    equipa_procurada = procura_equipa(hashtable_equipas, nome);

    if (equipa_procurada != NULL) printf("%d Equipa existente.\n", *nl);
    else
    {
        nova_equipa = cria_equipa(nome);
        add_equipa(hashtable_equipas, nova_equipa);
    }
}

/*Funcao que procura uma equipa existente no sistema dado um nome.
    Retorna mensagem de erro caso:
        *nao exista equipa no sistema com nome dado*/
void command_P(int * nl, EQUIPA ** hashtable_equipas)
{
    char nome[TAM_NOME];
    EQUIPA * equipa_procurada;

    scanf(" %[^:\n]s", nome);

    equipa_procurada = procura_equipa(hashtable_equipas, nome);

    if (equipa_procurada == NULL) printf("%d Equipa inexistente.\n", *nl);
    else 
    {
        printf("%d %s %d\n", *nl, nome, equipa_procurada -> score);
    }
}

/*Funcao que encontra as equipas que ganharam mais jogos de lista-as
    por ordem alfabetica dos nomes de cada uma dessas equipas na forma:
        * nl * nome equipa1
        * nl * nome equipa2
        *      (....)      */
void command_g(int * nl, EQUIPA ** hashtable_equipas)
{  
    int i, maior_score = 0, num_jogos = 0;
    char ** lista_nomes = NULL;

    maior_score = maior_score_equipa(hashtable_equipas);

    num_jogos = num_equipas(hashtable_equipas, maior_score);

    if (num_jogos != 0)
    {
        lista_nomes = malloc(sizeof(char*)*(num_jogos+1));

        cria_lista_nomes(lista_nomes, hashtable_equipas, maior_score);

        qsort(lista_nomes, num_jogos, sizeof(char *), compara_nomes);

        printf("%d Melhores %d\n", *nl, maior_score);

        for(i = 0; i < num_jogos; i++) 
        {
            printf("%d * %s\n", *nl, lista_nomes[i]);
            free(lista_nomes[i]);
        }
        free(lista_nomes);
    }
}

/*Funcao que liberta toda a memoria alocada no sistema*/
void command_x(EQUIPA ** hashtable_equipas, JOGO_LIST * lista_de_jogos, 
                    JOGO_HASH ** hashtable_jogos)
{
    destroy_hash_equipa(hashtable_equipas);
    destroy_jogos(hashtable_jogos, lista_de_jogos);
}
