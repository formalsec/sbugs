#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Hash.h"
#include "Estruturas.h"

/*
    Nota: Ao longo deste ficheiro e usada varias vezes a operacao
          "% TAM_HASH" que permite garantir que a procura linear
          nao passa dos limites da tabela                         
                                                                  */


/* Funcao que calcula a posicao ideal de um nome numa tabela */
int dispersao(char *nome)
{
    int posicao = 29, a = 37; 
    
    while (*nome != '\0')
    {
        posicao = (posicao*a + *nome) % TAM_HASH;
        nome++;
    }
    return posicao;
}

/* Funcao que cria e inicializa a tabela usada para guardar os jogos */
p_jogo* inicializa_jogos()
{
    p_jogo *tabela;
    int i;
    
    tabela = (p_jogo*) can_fail_malloc(TAM_HASH * sizeof(p_jogo));

    for (i = 0 ; i < TAM_HASH ; i++)
    {
        /* Tudo inicializado a NULL */
        tabela[i] = NULL; 
        
    }
    return tabela;
}

/* Funcao que cria e inicializa a tabela usada para guardar as equipas */
p_equipa* inicializa_equipas()
{
    p_equipa *tabela;
    int i;
    
    tabela = (p_equipa*) can_fail_malloc(TAM_HASH * sizeof(p_equipa));
    
    for (i = 0 ; i < TAM_HASH ; i++)
    {
        /* Tudo inicializado a NULL */
        tabela[i] = NULL; 
        
    }
    return tabela;
}

/* Funcao que insere um jogo na tabela devida */
void insere_jogo(p_jogo novo, p_jogo *tab_j)
{
    int posicao;
    
    /* Posicao  ideal */
    posicao = dispersao(novo->nome);

    /* Procura um lugar vazio */
    while (tab_j[posicao] != NULL)
    {
        posicao = (posicao + 1) % TAM_HASH;
    }
    /* Insere o jogo "novo" */
    tab_j[posicao] = novo;
}

/* Funcao que insere uma equipa na tabela devida */
void insere_equipa(p_equipa nova, p_equipa *tabela_equipas)
{
    int posicao;

    /* Posicao ideal */
    posicao = dispersao(nova->nome);

    /* Procura um espaco vazio */
    while (tabela_equipas[posicao] != NULL)
    {
        posicao = (posicao + 1) % TAM_HASH;
    }
    /* Insere a equipa "nova" */
    tabela_equipas[posicao] = nova;
}

/* Funcao que retorna o ponteiro do jogo chamado "nome" e indica a sua posicao */
p_jogo encontra_jogo(char *nome, p_jogo *tab_j, int *pos)
{
    int posicao;

    /* Posicao ideal */
    posicao = dispersao(nome);

    /* Procura linear */
    while (tab_j[posicao] != NULL)
    {
        /* Encontra o jogo com o nome certo */
        if (!strcmp(nome, tab_j[posicao]->nome))
        {
            *pos = posicao;
            break;
        }
        else
        {
            posicao = (posicao+1) % TAM_HASH;
        }
    }
    return tab_j[posicao];
}

/* Funcao que retorna o ponteiro da equipa chamada "nome" */
p_equipa encontra_equipa(char *nome, p_equipa *tabela_equipas)
{
    int posicao;

    /* Posicao ideal */
    posicao = dispersao(nome);

    /* Procura linear */
    while (tabela_equipas[posicao] != NULL)
    {
        /* Encontra a equipa com nome certo */
        if (!strcmp(nome, tabela_equipas[posicao]->nome))
        {
            return tabela_equipas[posicao];
        }
        else
        {
            posicao = (posicao+1) % TAM_HASH;
        }
    }
    /* Caso nao encontre a equipa */
    return NULL;
}

/* Funcao que elimina um jogo da tabela devida */
void remove_jogo(p_jogo *tab_j, int *posicao)
{
    int i;
    p_jogo aux;
    
    /* Elimina o jogo da tabela */
    tab_j[*posicao] = NULL;

    /* Reinsere os jogos para a frente */
    for (i = (*posicao+1) % TAM_HASH ; tab_j[i] != NULL ; i = (i+1) % TAM_HASH)
    {
        aux = tab_j[i];
        tab_j[i] = NULL;
        insere_jogo(aux, tab_j);
    }
}


