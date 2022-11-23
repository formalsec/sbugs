#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"

void comando_a(int linha, jlink *hash_jogos, elink * hash_equipas, Lista_Jogos lista)
{
    Jogo jogo = can_fail_malloc(sizeof(struct jogo));
    Equipa equipa1;
    Equipa equipa2;

    char nome_jogo[MAXNOME], eq1_nome[MAXNOME], eq2_nome[MAXNOME];
    int res1, res2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, eq1_nome, eq2_nome, &res1, &res2);

    /* Neste caso so fazemos free(jogo) porque so fizemos can_fail_malloc ao jogo */
    /* Se uma das equipas for NULL significa que nao existe */

    /* so adiciono se o jogo nao existir */
    if (!existe_jogo(hash_jogos, nome_jogo))
    {
        equipa1 = procura_equipa(hash_equipas, eq1_nome);
        if (equipa1 == NULL)
        {
            free(jogo);
            printf("%d Equipa inexistente.\n", linha);
            return;
        }
        else
        {
            /* so procura a sugunda equipa se encontrar a primeira*/
            equipa2 = procura_equipa(hash_equipas, eq2_nome);
            if (equipa2 == NULL)
            {
                free(jogo);
                printf("%d Equipa inexistente.\n", linha);
                return;
            }
        }
        /* vejo qual e a vencedor */
        if (res1 > res2)
        {
            jogo->vencedora = equipa1;
            equipa1->total_ganhos++;
        }
        else if (res1 < res2)
        {
            jogo->vencedora = equipa2;
            equipa2->total_ganhos++;
        }
        /* se for empate, vencedora e NULL */
        else
            jogo->vencedora = NULL;
        
        jogo->nome = can_fail_malloc(sizeof(char)*(strlen(nome_jogo) + 1));
        jogo->nome = strcpy(jogo->nome, nome_jogo);

        jogo->eq1 = equipa1;
        jogo->eq2 = equipa2;
            
        jogo->res1 = res1;
        jogo->res2 = res2;
            
        adiciona_jogo(hash_jogos, lista, jogo);
        }
    else
    {
        free(jogo);
        printf("%d Jogo existente.\n", linha);
    }
}

void comando_A(int linha, elink * hash_equipas)
{
    char nome_equipa[MAXNOME];
    Equipa equipa = can_fail_malloc(sizeof(struct equipa));
    scanf(" %[^:\n]", nome_equipa);
    equipa->nome = can_fail_malloc(sizeof(char)*(strlen(nome_equipa) + 1));
    strcpy(equipa->nome, nome_equipa);
    equipa->total_ganhos = 0;

    /* so adiciono se a equipa nao existir */
    if (!existe_equipa(hash_equipas, equipa->nome))
    {
        adiciona_equipa(hash_equipas, equipa);
    }
    else
    {
        printf("%d Equipa existente.\n", linha);
        FREEequipa(equipa);
    }
}

void comando_l(int linha, Lista_Jogos lista)
{
    /* x comeca como o primeiro introduzido */
    jog_lig x = lista->primeiro;

    /* Nao ha jogos */
    if(lista->primeiro == NULL)
    {
        return;
    }
    /* Se so tiver um jogo nao entra no while */
    while(x != lista->ultimo)
    {
        printf("%d %s %s %s %d %d\n", linha, x->jogo->nome, x->jogo->eq1->nome, 
            x->jogo->eq2->nome, x->jogo->res1, x->jogo->res2);
        x = x->seguinte;
    }
    printf("%d %s %s %s %d %d\n", linha, x->jogo->nome, x->jogo->eq1->nome, 
        x->jogo->eq2->nome, x->jogo->res1, x->jogo->res2);
}

void comando_p(int linha, jlink *hash_jogos)
{
    char nome_jogo[MAXNOME];
    Jogo jogo;
    scanf(" %[^:\n]", nome_jogo);
    jogo = procura_jogo(hash_jogos, nome_jogo);
    if (jogo != NULL)
    {
        printf("%d %s %s %s %d %d\n", linha, jogo->nome, jogo->eq1->nome, 
            jogo->eq2->nome, jogo->res1, jogo->res2);
    }
    else
        printf("%d Jogo inexistente.\n", linha);
}

void comando_P(int linha, elink * hash_equipas)
{
    char nome_equipa[MAXNOME];
    Equipa equipa;
    scanf(" %[^:\n]", nome_equipa);
    equipa = procura_equipa(hash_equipas, nome_equipa);
    if (equipa != NULL)
    {
        printf("%d %s %d\n", linha, equipa->nome, equipa->total_ganhos);
    }
    else
    {
        printf("%d Equipa inexistente.\n", linha);
    }
    
}

void comando_r(int linha, jlink *hash_jogos, Lista_Jogos lista)
{
    char nome_jogo[MAXNOME];
    Jogo x;
    scanf(" %[^:\n]", nome_jogo);
    
    x = procura_jogo(hash_jogos, nome_jogo);
    if (x != NULL)
    {
        /* Retiramos uma vitoria a vencedora, 
        pois fica sem efeito */
        if (x->vencedora != NULL)
            x->vencedora->total_ganhos--;
        remove_jogo(hash_jogos, lista, x);
    }
    else
        printf("%d Jogo inexistente.\n", linha);
}

void comando_s(int linha, jlink *hash_jogos)
{
    char nome_jogo[MAXNOME];
    int novo_1, novo_2;
    Jogo x;
    scanf(" %[^:\n]:%d:%d", nome_jogo, &novo_1, &novo_2);

    if (novo_1 < 0 || novo_2 < 0)
        return;

    x = procura_jogo(hash_jogos, nome_jogo);
    if (x != NULL)
    {
        x->res1 = novo_1;
        x->res2 = novo_2;
        
        if (x->vencedora != NULL)
        {
            /* Como o resultado pode mudar,
            retiramos uma vitoria a vencedora */
            x->vencedora->total_ganhos--;
        }
        if (novo_1 > novo_2)
        {
            x->vencedora = x->eq1;
            x->vencedora->total_ganhos++;
        }
        else if (novo_1 < novo_2)
        {
            x->vencedora = x->eq2;
            x->vencedora->total_ganhos++;
        }
        /* Se for empate, vencedora passa a ser NULL */
        else
            x->vencedora = NULL;        
    }
    else
        printf("%d Jogo inexistente.\n", linha);
}

void comando_g(int linha, elink *hash_equipas)
{
	int i, max_ganhos = 0;

    /* Inicializa-se a lista dentro da funcao pois o max_ganhos pode mais tarde mudar */
    Lista_Equipas lista = init_lista_eq();

    max_ganhos = calcula_max_ganhos(hash_equipas, max_ganhos);

    for (i = 0; i < MAXHASH; i++)
    {
        obter_equipas(hash_equipas[i], lista, max_ganhos);
    }

    print_lista_eq(lista, linha, max_ganhos);

    /* Como se inicializou tambem se destroi dentro da funcao */
    destroi_eq_ligadas(lista);

}
