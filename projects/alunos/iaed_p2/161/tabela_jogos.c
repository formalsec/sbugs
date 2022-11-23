#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "tabela_jogos.h"

/* cria uma tabela de jogos vazia e devolve o seu ponteiro ----------------------------------- */

pTabela_jogos inicializa_tabela_jogos(unsigned int max) 
{
    unsigned int i;

    /* aloca memoria para a tabela */
    pTabela_jogos tabela = (pTabela_jogos)can_fail_malloc(sizeof(struct tabela_jogos));

    tabela -> num_jogos = 0;
    tabela -> tamanho = max;

    /* aloca memoria para o vetor de jogos */
    tabela -> jogos = (pJogo*)can_fail_malloc(max *sizeof(pJogo));

    for (i = 0; i < tabela -> tamanho; i++) tabela -> jogos[i] = NULL; /* inicializa tudo a NULL */
    
    return tabela;
}

/* expande a tabela para o dobro do tamanho ---------------------------------------------------- */
void expande_tabela_jogos(pTabela_jogos tabela)
{
    unsigned int i;
    pTabela_jogos tabela_aux;
    
    /* cria tabela auxiliar com o dobro do tamanho*/
    tabela_aux = inicializa_tabela_jogos((tabela -> tamanho)*2);

    /* copia os jogos para a nova tabela */
    for (i = 0; i < tabela -> tamanho; i++)
        if (tabela -> jogos[i] != NULL)
            adiciona_jogo_tabela(tabela_aux, tabela -> jogos[i]);
    
    
    free(tabela -> jogos);

    /* muda o ponteiro dos jogos e o tamanho da tabela original */
    tabela -> jogos = tabela_aux -> jogos;
    tabela -> tamanho = tabela_aux -> tamanho;

    
    free(tabela_aux);
    return;
}


/* adiciona um jogo 'a tabela ------------------------------------------------------------------ */
void adiciona_jogo_tabela(pTabela_jogos tabela, pJogo jogo) 
{
    unsigned int i = gera_hash(obtem_nome_jogo(jogo), tabela -> tamanho);
    
    /* coloca o jogo no espaco atribuido pela hash, ou no proximo que estiver vazio */
    while (tabela -> jogos[i] != NULL) 
        i = (i+1) % tabela -> tamanho;
    
    tabela -> jogos[i] = jogo;

    /* se metade da tabela estiver ocupada, expande-a */ 
    if (tabela -> num_jogos++ > tabela -> tamanho/2)
        expande_tabela_jogos(tabela);
    
    return;
}


/* se o jogo existir devolve o seu ponteiro, senao, devolve NULL ------------------------------- */
pJogo procura_jogo_tabela(pTabela_jogos tabela, char *nome_jogo)
{
    int i = gera_hash(nome_jogo, tabela -> tamanho);

    while (tabela -> jogos[i]  != NULL)
        if (strcmp(tabela -> jogos[i] -> nome, nome_jogo) == 0)
            return tabela -> jogos[i] ;
        else
            i = (i+1) % tabela -> tamanho;

    return NULL;
}

/* remove um jogo da tabela */
pJogo remove_jogo_tabela(pTabela_jogos tabela_jogos, char* nome_jogo)
{
    int i;
    unsigned tamanho_tabela;
    pJogo aux, jogo_removido;

    tamanho_tabela = tabela_jogos -> tamanho;

    i = gera_hash(nome_jogo, tamanho_tabela); 
    
    /* procura o jogo */
    while (tabela_jogos -> jogos[i] != NULL)
        if (strcmp(nome_jogo, obtem_nome_jogo(tabela_jogos -> jogos[i])) == 0)
             break;
        
        else 
            i = (i+1) % tamanho_tabela;
    
    if (tabela_jogos -> jogos[i] == NULL) 
        return NULL; 
        
    jogo_removido = tabela_jogos -> jogos[i]; /* guarda o item a ser removido em jogo_removido */
    
    tabela_jogos -> jogos[i] = NULL; /* remove da tabela */
    
    tabela_jogos -> num_jogos--;


    /* reorganiza a tabela */
    for (i = (i+1) % tamanho_tabela; tabela_jogos -> jogos[i] != NULL; i = (i+1) % tamanho_tabela)
    {
        tabela_jogos -> num_jogos--;

        aux = tabela_jogos -> jogos[i];
        tabela_jogos -> jogos[i] = NULL;    /* re-adiciona o jogo */

        adiciona_jogo_tabela(tabela_jogos, aux);
    }

    return jogo_removido;
}

/* liberta a memoria da tabela ----------------------------------------------------------------- */
void destroi_tabela_jogos(pTabela_jogos tabela)
{
    free(tabela -> jogos);
    free(tabela);

    return;
}