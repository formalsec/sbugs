#include "FuncoesAux.h"
#include "Estruturas.h"
#include "Hash.h"

/* Funcao que acerta as ligacoes prox e ant do jogo removido,
   bem como os conteudos de cab_j e fim_j */
void compensa_jogos(p_jogo jogo_apag, p_jogo *fim_j, p_jogo *cab_j)
{
    /* Caso o jogo seja o unico no momento */
    if (*fim_j == *cab_j)
    {
        *fim_j = NULL;
        *cab_j = NULL;
    }
    /* Caso seja o ultimo jogo */
    else if (*fim_j == jogo_apag)
    {
        (jogo_apag->ant)->prox = NULL;
        *fim_j = jogo_apag->ant;
    }
    /* Caso seja o primeiro jogo */
    else if (*cab_j == jogo_apag)
    {
        (jogo_apag->prox)->ant = NULL;
        *cab_j = jogo_apag->prox;
    }
    /* Caso geral */
    else
    {
        (jogo_apag->prox)->ant = jogo_apag->ant;
        (jogo_apag->ant)->prox = jogo_apag->prox;
    }    
}

/* Funcao que retorna o ponteiro do jogo chamado "nome" */
p_jogo existe_jogo(char *nome, p_jogo *tab_j)
{
    p_jogo jogo;
    int *posicao;

    /* Necessario para correr a funcao "encontra_jogo" */
    posicao = (int*) malloc(sizeof(int));
    
    jogo = encontra_jogo(nome, tab_j, posicao);
    free(posicao);

    return jogo;
}

/* Funcao que da uma vitoria a equipa chamada "nome" */
void aumenta_vitorias(char *nome, p_equipa *tab_e)
{
    p_equipa equipa;
    
    equipa = encontra_equipa(nome, tab_e);
    equipa->vitorias++;
}

/* Funcao que da uma vitoria a equipa chamada "nome" */
void remove_vitoria(char *nome, p_equipa *tab_e)
{
    p_equipa equipa;

    equipa = encontra_equipa(nome, tab_e);
    equipa->vitorias--;
}

/* Funcao que verifica se alguma equipa ganhou o jogo  e adiciona a vitoria */
void ve_vitoria(p_jogo jogo, p_equipa *tab_e)
{
    /* Vitoria da equipa1 */
    if (jogo->pontos1 > jogo->pontos2)
        {
            aumenta_vitorias(jogo->equipa1, tab_e);
        }
    /* Vitoria da equipa2 */
    else if (jogo->pontos2 > jogo->pontos1)
        {
            aumenta_vitorias(jogo->equipa2, tab_e);
        }
    /* Empate */
}

/* Funcao que verifica se alguma equipa ganhou o jogo e remove a vitoria */
void ve_derrota(p_jogo jogo, p_equipa *tab_e)
{
    if (jogo->pontos1 > jogo->pontos2)
    {
        remove_vitoria(jogo->equipa1, tab_e);
    }
    else if (jogo->pontos2 > jogo->pontos1)
    {
        remove_vitoria(jogo->equipa2, tab_e);
    }
}

/* Funcao que da free a todos os jogos e a tabela que os contem */
void free_tabela_jogos(p_jogo *tab_j, p_jogo *cab_j)
{
    p_jogo jogo, prox;

    for (jogo = *cab_j ; jogo != NULL ; jogo = prox)
    {
        prox = jogo->prox;
        free_jogo(jogo);
    }
    
    free(tab_j);
}

/* Funcao que da free a todas as equipas e a tabela que as contem */
void free_tabela_equipas(p_equipa *tab_e, p_equipa *cab_e)
{
    p_equipa equipa, prox;

    for (equipa = *cab_e ; equipa != NULL ; equipa = prox)
    {
        prox = equipa->prox;
        free_equipa(equipa);
    }
    
    free(tab_e);
}

/* Verifica se a string b vem primeiro na ordem alfabetica do que a */
int alfabetico_equipas(const void *a, const void *b)
{
    char **nome1, **nome2;
    
    nome1 = (char **) a;
    nome2 = (char **) b;

    return (strcmp(*nome2, *nome1) < 0);
}

/* Funcao que retorna um ponteiro para strings criado com o tamanho necessario */
char* novo_nome(char nome[])
{
    char *novo;

    novo = (char*) malloc(sizeof(char) * (strlen(nome)+1));
    strcpy(novo, nome);

    return novo;
}

/* Funcao que acerta as vitorias e ligacoes entre jogos apos a remocao de "jogo" */
void acerta_jogos(p_jogo jogo, p_equipa *tab_e, p_jogo *cab_j, p_jogo *fim_j)
{
    /* Liga os jogos anterior e seguinte */
    compensa_jogos(jogo, fim_j, cab_j);
    
    /* Atualiza as vitorias */
    ve_derrota(jogo, tab_e);

    free_jogo(jogo);
}