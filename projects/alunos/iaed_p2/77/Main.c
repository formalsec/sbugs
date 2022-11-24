#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Ficheiro que contem as estruturas usadas e funcoes inerentes */
#include "Estruturas.h"
/* Ficheiro que contem as funcoes inerentes as hash tables */
#include "Hash.h"
/* Ficheiro que contem as funcoes auxiliares */
#include "FuncoesAux.h"


/* #####################################################################

                               CONSTANTES

##################################################################### */

/* Tamanho maximo de uma string */
#define CHAR_MAX 1024


/* ##################################################################### 

                   PROTOTIPOS DAS FUNCOES PRINCIPAIS

##################################################################### */ 

void novo_jogo(int linha, p_jogo *cab_j, p_jogo *fim_j, p_jogo *tab_j, p_equipa *tab_e);
void lista_jogos(int linha, p_jogo *cab_j);
void apaga_jogo(int linha, p_jogo *tab_j, p_equipa *tab_e, p_jogo *fim_j, p_jogo *cab_j);
void procura_jogo(int linha, p_jogo *tab_j);
void procura_equipa(int linha, p_equipa *tab_e);
void nova_equipa(int linha, p_equipa *tab_e, p_equipa *cab_e, p_equipa *fim_e, int *equipas);
void muda_resultado(int linha, p_jogo *tab_j, p_equipa *tab_e);
void melhores_equipas(int linha, p_equipa *cab_e, int *equipas);


/* ##################################################################### 

                              FUNCAO MAIN

##################################################################### */

/* Inicializa as tabelas e variaveis necessarias para os dados e depois interpreta o caracter
   recebido e executa o comando pretendido */
int main()
{
    int comando;
    /* Tabela dos jogos + primeiro e ultimo elementos, respetivamente */
    p_jogo *tab_j, *cab_j, *fim_j;
    /* Tabela das equipas + primeiro e ultimo elementos, respetivamente */
    p_equipa *tab_e, *cab_e, *fim_e;
    /* Numero da linha do input */
    int linha = 0;
    /* Ponteiro que contem o numero de equipas no sistema */
    int *equipas;

    /* Inicializacao das tabelas, cabecas e fins das listas */

    tab_j = inicializa_jogos();
    tab_e = inicializa_equipas();

    cab_j = (p_jogo*) can_fail_malloc(sizeof(p_jogo));
    *cab_j = NULL;
    fim_j = (p_jogo*) can_fail_malloc(sizeof(p_jogo));
    *fim_j = NULL;

    cab_e = (p_equipa*) can_fail_malloc(sizeof(p_equipa));
    *cab_e = NULL;
    fim_e = (p_equipa*) can_fail_malloc(sizeof(p_equipa));
    *fim_e = NULL;

    
    equipas = (int*) can_fail_malloc(sizeof(int));
    /* Numero de equipas */
    *equipas = 0;

    /* Recebe o comando */
    while ((comando = getchar()) != 'x')
    {
        switch ( comando )
        {
            /* Cada letra chama a funcao correspondente ao comando */
            case 'a':
                novo_jogo(++linha, cab_j, fim_j, tab_j, tab_e);
                break;
            case 'A':
                nova_equipa(++linha, tab_e, cab_e, fim_e, equipas);
                break;
            case 'l':
                lista_jogos(++linha, cab_j);
                break;
            case 'p':
                procura_jogo(++linha, tab_j);
                break;
            case 'P':
                procura_equipa(++linha, tab_e);
                break;
            case 'r':
                apaga_jogo(++linha, tab_j, tab_e, fim_j, cab_j);
                break;
            case 's':
                muda_resultado(++linha, tab_j, tab_e);
                break;
            case 'g':
                melhores_equipas(++linha, cab_e, equipas);
                break;
            default:
                break;
        } 
    }

    /* Free de todos os dados */
    free_tabela_jogos(tab_j, cab_j);
    free_tabela_equipas(tab_e, cab_e);
    free(cab_j); free(fim_j);
    free(cab_e); free(fim_e);
    free(equipas);

    return 0;
}


/* ##################################################################### 

                              FUNCOES PRINCIPAIS

##################################################################### */

/* Funcao que cria um jogo novo e o insere na tabela dos jogos */
void novo_jogo(int linha, p_jogo *cab_j, p_jogo *fim_j, p_jogo *tab_j, p_equipa *tab_e)
{
    p_jogo jogo;
    char nome1[CHAR_MAX], nome2[CHAR_MAX], nome3[CHAR_MAX];
    int pontos1, pontos2;

    /*Recebe os dados */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome1, nome2, nome3, &pontos1, &pontos2);

    /* Verifica validade dos dados */
    if (existe_jogo(nome1, tab_j))
    {
        printf("%d Jogo existente.\n", linha);
    }
    else if (!encontra_equipa(nome2, tab_e) || !encontra_equipa(nome3, tab_e))
    {
        printf("%d Equipa inexistente.\n", linha);
    }
    else
    {
        /* Cria jogo */
        jogo = (p_jogo) can_fail_malloc(sizeof(struct jogo));

        /* Aloca memoria para as strings necessarias */
        jogo->nome = novo_nome(nome1);
        jogo->equipa1 = novo_nome(nome2);
        jogo->equipa2 = novo_nome(nome3);

        jogo->pontos1 = pontos1;
        jogo->pontos2 = pontos2;

        /* Caso nao hajam elementos o novo jogo e a cabeca */
        if (*cab_j == NULL)
        {
            *cab_j = jogo;
        }

        /* Caso contrario liga-se a tail ao novo jogo e vice-versa */
        else
        {
            (*fim_j)->prox = jogo;
            jogo->ant = *fim_j;
        }

        /* Update da tail */
        *fim_j = jogo;
        jogo->prox = NULL;

        /* Atualizacao das vitorias */
        ve_vitoria(jogo, tab_e);

        /* Insercao na tabela */
        insere_jogo(jogo, tab_j);
    }   
}

/* Funcao que apresenta os jogos por ordem de introducao no sistema */
void lista_jogos(int linha, p_jogo *cab_j)
{
    p_jogo i;

    for (i = *cab_j ; i != NULL ; i = i->prox)
    {
        printf("%d %s %s %s %d %d\n", linha, i->nome, i->equipa1,
                                      i->equipa2, i->pontos1, i->pontos2);
    }
}

/* Funcao que apresenta os dados do jogo com o nome recebido */
void procura_jogo(int linha, p_jogo *tab_j)
{
    p_jogo jogo;
    char nome[CHAR_MAX];  

    /* Recebe os dados */
    scanf(" %[^:\n]", nome);

    jogo = existe_jogo(nome, tab_j);

    /* Verifica a validade do nome */
    if (jogo)
    {
        printf("%d %s %s %s %d %d\n", linha, jogo->nome, jogo->equipa1, jogo->equipa2,
                                      jogo->pontos1, jogo->pontos2);
    }
    else
    {
        printf("%d Jogo inexistente.\n", linha);
    }
}

/* Funcao que remove o jogo com o nome recebido da tabela */
void apaga_jogo(int linha, p_jogo *tab_j, p_equipa *tab_e, p_jogo *fim_j, p_jogo *cab_j)
{
    p_jogo jogo;
    char nome[CHAR_MAX];
    int *posicao;

    posicao = (int*) can_fail_malloc(sizeof(int));

    /* Recebe os dados */
    scanf(" %[^:\n]", nome);

    jogo = encontra_jogo(nome, tab_j, posicao);

    /* Verifica a validade do nome */
    if (jogo)
    {
        /* Remove o jogo da tabela */
        remove_jogo(tab_j, posicao);
        /* Acerta os dados que "jogo" influenciava */
        acerta_jogos(jogo, tab_e, cab_j, fim_j);
    }
    else
    {
        printf("%d Jogo inexistente.\n", linha);
    }
    free(posicao);
}

/* Funcao que muda o resultado do jogo com nome recebido */
void muda_resultado(int linha, p_jogo *tab_j, p_equipa *tab_e)
{
    int new_pontos1, new_pontos2;
    char nome[CHAR_MAX];
    p_jogo jogo;

    /* Recebe os dados */
    scanf(" %[^:\n]:%d:%d", nome, &new_pontos1, &new_pontos2);

    jogo = existe_jogo(nome, tab_j);

    /* Verifica a validade do nome */
    if (jogo)
    {
        /* Atualizacao das vitorias e do resultado */
        ve_derrota(jogo, tab_e);

        jogo->pontos1 = new_pontos1;
        jogo->pontos2 = new_pontos2;

        ve_vitoria(jogo, tab_e);
    }
    else
    {
        printf("%d Jogo inexistente.\n", linha);
    }
}

/* Funcao que cria uma nova equipa com os dados recebidos e a insere na tabela */
void nova_equipa(int linha, p_equipa *tab_e, p_equipa *cab_e, p_equipa *fim_e, int *equipas)
{
    p_equipa equipa;
    char nome[CHAR_MAX];

    /* Recebe os dados */
    scanf(" %[^\n]", nome);

    /* Verifica a validade do nome */
    if(encontra_equipa(nome, tab_e))
    {
        printf("%d Equipa existente.\n", linha);
    }
    else
    {
        equipa = (p_equipa) can_fail_malloc(sizeof(struct equipa));
        equipa->nome = novo_nome(nome);
        equipa->vitorias = 0;
        equipa->prox = NULL;

        /* Caso seja a primeira equipa torna-se a cabeca */
        if (*cab_e == NULL)
        {
            *cab_e = equipa;
        }
        /* Caso contrario ligamos a tail a nova equipa */
        else
        {
            (*fim_e)->prox = equipa;
        }
        *fim_e = equipa;

        /* Insere a equipa na tabela */
        insere_equipa(equipa, tab_e);
        /* Aumento do numero de equipas */
        (*equipas)++;
    }
}

/* Funcao que apresenta os dados da equipa com o nome recebido */
void procura_equipa(int linha, p_equipa *tab_e)
{
    p_equipa equipa;
    char nome[CHAR_MAX];  

    /* Recebe os dados */
    scanf(" %[^\n]", nome);

    equipa = encontra_equipa(nome, tab_e);

    /* Verifica a validade do nome */
    if (equipa)
    {
        printf("%d %s %d\n", linha, equipa->nome, equipa->vitorias);
    }
    else
    {
        printf("%d Equipa inexistente.\n", linha);
    }
}

/* Funcao que apresenta as equipas com mais vitorias por ordem lexicografica */
void melhores_equipas(int linha, p_equipa *cab_e, int *equipas)
{
    int i = 0, j;
    /* Maior numero de vitorias e numero de equipas, respetivamente */
    int vitorias_max = 0, n_melhores = 0;
    p_equipa equipa;
    /* Vetor que guarda os nomes das melhores equipas */
    char **melhores;
    melhores = (char**) can_fail_malloc(*equipas * sizeof(char*));
    
    for (equipa = *cab_e ; equipa != NULL ; equipa = equipa->prox)
    {
        /* Adiciona a equipa aos melhores */
        if (equipa->vitorias == vitorias_max)
        {
            melhores[i++] = equipa->nome;
            n_melhores++;
        }
        /* Atualizacao do numero maximo de vitorias e reset das variaveis */
        else if (equipa->vitorias > vitorias_max)
        {
            vitorias_max = equipa->vitorias;
            n_melhores = 1;
            i = 0;

            /* Da reset as posicoes preenchidas */
            memset(melhores, 0, sizeof(char*) * n_melhores);
            melhores[i++] = equipa->nome;
        }
    }
    /* Verifica que ha equipas */
    if (n_melhores)
    {
        /* Ordena os melhores por ordem lexicografica */
        qsort(melhores, n_melhores, sizeof(char*), alfabetico_equipas);
        
        printf("%d Melhores %d\n", linha, vitorias_max);
        for (j = 0 ; j != n_melhores ; j++)
        {
            printf("%d * %s\n", linha, melhores[j]);
        } 
    }
    free(melhores);
}

