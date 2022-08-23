#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HASHTABLES.h"

/*----------------------------------------------------------------------*/
/* funcao_dispersao(char *nome, unsigned int M): esta funcao recebe o   */
/*    nome de um jogo, o tamanho da tabela de dispersao, M, e devolve o */
/*    valor do indice da tabela de dispersao onde deve ficar o jogo.    */
/*----------------------------------------------------------------------*/
unsigned int funcao_dispersao(char *nome, unsigned int M) {
    unsigned int h, a = 31415, b = 27183;
    
    for (h = 0; *nome != '\0'; nome++, a = a*b % (M-1)) {
        h = (a*h + *nome) % M;
    }
    return h;
}

/*----------------------------------------------------------------------*/
/* init_tab_dispersao(unsigned int M): esta funcao recebe o tamanho da  */
/*    tabela de dispersao, M, e inicializa a tabela de dispersao a NULL.*/
/*----------------------------------------------------------------------*/
pJogo *init_tab_dispersao(unsigned int M) {
    unsigned int i;
    pJogo *tab_dispersao = NULL;

    tab_dispersao = (pJogo*)malloc(M*sizeof(pJogo));
    for (i = 0; i < M; i++) {
        tab_dispersao[i] = NULL; /* inicializo tudo a NULL */
    }
    return tab_dispersao;
}

/*----------------------------------------------------------------------*/
/* tab_dispersao_insere(pJogo *tab_dispersao, char *nome, char *equipa1,*/ 
/*    char *equipa2, int score1, int score2, unsigned int M): esta      */
/*    funcao recebe o ponteiro para a tabela de dispersao, o nome de um */
/*    jogo, os ponteiros para os nomes das equipas, o score de cada     */
/*    equipa e o tamanho da tabela dispersao, M, e insere o jogo na     */
/*    tabela de dispersao.                                              */
/*----------------------------------------------------------------------*/
pJogo tab_dispersao_insere(pJogo *tab_dispersao, char *nome, char *equipa1, char *equipa2, 
                            int score1, int score2, unsigned int M) {
    unsigned int i = funcao_dispersao(nome, M);
    while (tab_dispersao[i] != NULL) {
        i = (i+1) % M;
    }
    tab_dispersao[i] = (pJogo)malloc(sizeof(struct Jogo));
    tab_dispersao[i]->nome =  (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy( tab_dispersao[i]->nome, nome);
    tab_dispersao[i]->equipa1 = equipa1;
    tab_dispersao[i]->equipa2 = equipa2;
    tab_dispersao[i]->score1 = score1;
    tab_dispersao[i]->score2 = score2;

    return tab_dispersao[i];
}

/*----------------------------------------------------------------------*/
/* procura_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido,     */
/*    unsigned int M): esta funcao recebe o ponteiro para a tabela de   */
/*    dispersao, o nome de um jogo e o tamanho da tabela, M, e          */
/*    devolve a linha da tabela de dispersao onde esse jogo esta, se o  */
/*    jogo estiver na tabela, caso contrario devolve NULL.              */
/*----------------------------------------------------------------------*/
pJogo procura_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido, unsigned int M) {
    unsigned int i = funcao_dispersao(nome_recebido, M);

    while (tab_dispersao[i] != NULL){
        if (!strcmp(tab_dispersao[i]->nome, nome_recebido))
            return tab_dispersao[i];
        else
            i = (i+1) % M;
    }
    return NULL;
}

/*----------------------------------------------------------------------*/
/* apaga_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido,       */ 
/*    unsigned int M): esta funcao recebe o ponteiro para a tabela de   */
/*    dispersao, o nome de um jogo e o tamanho da tabela, M, e apaga da */
/*    tabela de dispersao esse jogo, e coloca na posicao correta        */
/*    eventuais jogos que tenham sido colocados noutras posicoes da     */
/*    tabela devido a uma colisao.                                      */
/*----------------------------------------------------------------------*/
void apaga_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido, unsigned int M) {
    unsigned int j, aux, i = funcao_dispersao(nome_recebido, M);

    while (tab_dispersao[i] != NULL) {
        if (!strcmp(tab_dispersao[i]->nome, nome_recebido)) 
            break;
        i = (i+1) % M;
    }
    if (tab_dispersao[i]== NULL) return;
    
    free(tab_dispersao[i]->nome); 
    free(tab_dispersao[i]); 
    tab_dispersao[i]=NULL;

    do { /* reposicao das posicoes alteradas por colisoes */
        for (j = (i+1) % M; tab_dispersao[j] != NULL; j = (j+1) % M) {
            aux = funcao_dispersao(tab_dispersao[j]->nome, M);
            if(aux <= i){
                tab_dispersao[i] = tab_dispersao[j];
                tab_dispersao[j] = NULL;
                i = j;
                break;
            }
        }
    } while(i==j);
    return;
}

/*----------------------------------------------------------------------*/
/* expande(pJogo *tab_dispersao, unsigned int M): esta funcao recebe o  */
/*    ponteiro para a tabela de dispersao e o novo tamanho da tabela, M,*/
/*    e cria uma nova tabela de dispersao com o tamanho recebido.       */
/*----------------------------------------------------------------------*/
pJogo *expande(pJogo *tab_dispersao, unsigned int M) {
    unsigned int i,j;
    pJogo *nova_tab_dispersao = NULL;

    nova_tab_dispersao = init_tab_dispersao(M);

    for (i = 0; i < M/2; i++) {
        if (tab_dispersao[i] != NULL) {
            /* colocacao na nova tabela de dispersao dos jogos da tabela anterior */
            j = funcao_dispersao(tab_dispersao[i]->nome, M);
            while (nova_tab_dispersao[j] != NULL) {
                j = (j+1) % M;
            }
            nova_tab_dispersao[j] = tab_dispersao[i];
        }
    }
    free(tab_dispersao);
    return nova_tab_dispersao;
}

/*----------------------------------------------------------------------*/
/* free_tab_dispersao(pJogo *tab_dispersao, unsigned int M): esta funcao*/
/*    recebe o ponteiro para a tabela de dispersao e o tamanho da       */
/*    tabela, M, e faz a libertacao da memoria reservada para a tabela. */
/*----------------------------------------------------------------------*/
void free_tab_dispersao(pJogo *tab_dispersao, unsigned int M) {
    unsigned int i;
    for(i = 0; i < M ; i++) {
        if(tab_dispersao[i]!=NULL){
            free(tab_dispersao[i]->nome);
            free(tab_dispersao[i]);
        }
    }
    free(tab_dispersao);
}

/*----------------------------------------------------------------------*/
/* funcao_tab_equipas(char *equipa): esta funcao recebe o nome de uma   */
/*    equipa e devolve o valor do indice da tabela de equipas onde      */
/*    devera ficar a equipa.                                            */
/*----------------------------------------------------------------------*/
unsigned int funcao_tab_equipas(char *equipa) {
    unsigned int h;
    /* equipas com apenas uma letra possuem dois caracteres devido ao terminador */
    h = (int)equipa[0]+(int)equipa[1];
    return h;
}

/*----------------------------------------------------------------------*/
/* free_tab_equipas(link_equipa *tab_equipas): esta funcao recebe o     */
/*    ponteiro da tabela de equipas e faz a libertacao da memoria       */
/*    reservada para essa tabela.                                       */
/*----------------------------------------------------------------------*/
void free_tab_equipas(link_equipa *tab_equipas) {
    int i;
    link_equipa e = NULL, e_next = NULL;
    
    for(i = 0; i < MAX_TAB;i++)
        for(e = tab_equipas[i]; e != NULL; e = e_next) {
            e_next = e->next;
            free(e->equipa);
            free(e);
        }
}