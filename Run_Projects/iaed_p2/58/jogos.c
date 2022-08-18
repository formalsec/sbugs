#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "LISTAS.h"
#include "HASHTABLES.h"

/*----------------------------------------------------------------*/
/* AdicionaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao,   */
/*    link_jogo Jogos_head, int NL, unsigned int M, unsigned      */
/*    int * NJ): esta funcao recebe o ponteiro para a tabela com  */
/*    listas de equipas, o ponteiro para a tabela de dispersao, o */
/*    ponteiro para a cabeca da lista de ponteiros para jogos, o  */
/*    numero da linha, NL, o tamanho da tabela de dispersao, M e o*/
/*    numero de jogos ate ao momento introduzidos no sistema, NJ, */
/*    e procura se o jogo que pretende adicionar nao existe, assim*/
/*    como, se a equipa existe no sistema. Se se verificar, o jogo*/
/*    e inserido. Caso contrario, imprime erro.                   */
/*----------------------------------------------------------------*/
link_jogo AdicionaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao, 
                        link_jogo Jogos_head, int NL, 
                        unsigned int M, unsigned int * NJ) {

    char nome[MAX_CAR], equipa1[MAX_CAR], equipa2[MAX_CAR];
    int score1, score2;
    link_equipa equipa1_ptr = NULL, equipa2_ptr = NULL;
    pJogo jogo_ptr = NULL;

    scanf(" %1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d", nome, 
            equipa1, equipa2, 
            &score1, &score2);

    if (procura_tab_dispersao(tab_dispersao, nome, M) != NULL) {
        printf("%d Jogo existente.\n", NL);
        return Jogos_head ;
    }

    equipa1_ptr = procura_equipa_lista(tab_equipas, equipa1);
    equipa2_ptr = procura_equipa_lista(tab_equipas, equipa2);

    if (equipa1_ptr == NULL || equipa2_ptr == NULL) {
        printf("%d Equipa inexistente.\n", NL);
        return Jogos_head;
    }
    /* atribuicao de uma vitoria na equipa que ganhou o jogo */
    if(score1 > score2)
        equipa1_ptr->vitorias++;
    else if (score2 > score1)
        equipa2_ptr->vitorias++;

    /* colocacao do jogo na tabela de dispersao */
    jogo_ptr = tab_dispersao_insere(tab_dispersao, nome, equipa1_ptr->equipa, 
                                    equipa2_ptr->equipa, score1, score2, M);

    *NJ = * NJ + 1;

    /* colocacao do ponteiro para o jogo na lista de ponteiros para jogos */
    return insere_jogo_lista(Jogos_head, jogo_ptr); /* retorna a cabeca */
}

/*----------------------------------------------------------------*/
/* AdicionaEquipa(link_equipa *tab_equipas, int NL): esta funcao  */
/*    recebe o ponteiro para a tabela com listas de equipas e o   */
/*    numero da linha, NL, e caso a equipa nao exista no sistema  */
/*    insere-a na lista correspondente da tabela. Caso contrario, */
/*    imprime erro.                                               */
/*----------------------------------------------------------------*/
void AdicionaEquipa(link_equipa *tab_equipas, int NL) { 
    char equipa[MAX_CAR];

    scanf(" %1023[^:\n]", equipa);

    if (procura_equipa_lista(tab_equipas, equipa) != NULL) {
        printf("%d Equipa existente.\n", NL);
        return;
    }
    /* colocacao da equipa na lista correspondente da tabela */
    insere_equipa_lista(tab_equipas, equipa);
    return;
}

/*----------------------------------------------------------------*/
/* ApagaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao,      */
/*    link_jogo Jogos_head, unsigned int M, int NL, unsigned int  */
/*    * NJ): esta funcao recebe o ponteiro para a tabela com      */
/*    listas de equipas, o ponteiro para a tabela de dispersao, o */
/*    ponteiro para a cabeca da lista de ponteiros para jogos, o  */
/*    numero da linha, NL, o tamanho da tabela de dispersao, M e o*/
/*    numero de jogos ate ao momento introduzidos no sistema, NJ, */
/*    e verifica se o jogo existe no sistema, se existir apaga-o. */
/*    Caso contrario, imprime erro.                               */
/*----------------------------------------------------------------*/
link_jogo ApagaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao, link_jogo Jogos_head, 
                    unsigned int M, int NL, unsigned int *NJ) {
    
    char nome[MAX_CAR];
    pJogo jogo_ptr = NULL;
    link_equipa equipa1_ptr = NULL, equipa2_ptr = NULL;

    scanf(" %1023[^:\n]", nome);

    jogo_ptr = procura_tab_dispersao(tab_dispersao, nome, M);

    if (jogo_ptr == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return Jogos_head;
    }

    equipa1_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa1);
    equipa2_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa2);

    /* eliminacao da vitoria atribuida a uma das equipas que venceu o jogo apagado */
    if (jogo_ptr->score1 > jogo_ptr->score2) 
        equipa1_ptr->vitorias--; 
    else if (jogo_ptr->score1 < jogo_ptr->score2)  
        equipa2_ptr->vitorias--; 

    /* eliminacao do jogo da lista de ponteiros para jogos */
    Jogos_head = apaga_jogo_lista(Jogos_head, nome);

    /* eliminacao do jogo da tabela de dispersao */
    apaga_tab_dispersao(tab_dispersao, nome, M);

    *NJ = * NJ - 1;

    return Jogos_head;
}

/*----------------------------------------------------------------*/
/* ListaJogos(link_jogo head, int NL): esta funcao recebe um      */
/*    ponteiro para a cabeca de uma lista de ponteiros para jogos,*/
/*    o numero da linha, NL, e imprime todos os jogos pela ordem  */
/*    em que foram introduzidos no sistema.                       */
/*----------------------------------------------------------------*/
void ListaJogos(link_jogo head, int NL) { 
    if(head == NULL)
        return;
    /* esta funcao e recursiva pois a lista esta com ordem inversa da insercao */
    ListaJogos(head->next, NL);
    printf("%d %s %s %s %d %d\n", NL, head->jogo->nome, head->jogo->equipa1, 
            head->jogo->equipa2, head->jogo->score1, head->jogo->score2);
    
    return;
}

/*----------------------------------------------------------------*/
/* ProcuraEquipa(link_equipa *tab_equipas, int NL): esta funcao   */
/*    recebe o ponteiro para a tabela com listas de equipas e o   */
/*    numero da linha, NL, e imprime, se a equipa existir, o      */
/*    numero de jogos ganhos por essa equipa. Caso contrario,     */
/*    imprime erro.                                               */
/*----------------------------------------------------------------*/
void ProcuraEquipa(link_equipa *tab_equipas, int NL) { 
    char equipa[MAX_CAR];
    link_equipa equipa_ptr = NULL;

    scanf(" %1023[^:\n]", equipa);
    
    equipa_ptr = procura_equipa_lista(tab_equipas, equipa);

    if(equipa_ptr == NULL){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    printf("%d %s %d\n", NL, equipa_ptr->equipa, equipa_ptr->vitorias);
    return;
}

/*----------------------------------------------------------------*/
/* ProcuraJogo(pJogo *tab_dispersao, int NL, unsigned int M): esta*/
/*    funcao recebe o ponteiro para a tabela de dispersao, o      */
/*    numero da linha, NL e o tamanho da tabela, M, e imprime,    */
/*    se o jogo existir no sistema, todas as informacoes relativas*/
/*    ao jogo. Caso contrario imprime erro.                       */
/*----------------------------------------------------------------*/
void ProcuraJogo(pJogo *tab_dispersao, int NL, unsigned int M) {
    char nome[MAX_CAR];
    pJogo jogo_ptr = NULL;

    scanf(" %1023[^:\n]", nome);
    
    jogo_ptr = procura_tab_dispersao(tab_dispersao, nome, M);
    
    if(jogo_ptr != NULL) {
        printf("%d %s %s %s %d %d\n", NL, jogo_ptr->nome, jogo_ptr->equipa1, 
                jogo_ptr->equipa2, jogo_ptr->score1, jogo_ptr->score2);
        return;
    }
    printf("%d Jogo inexistente.\n", NL);

    return;
}

/*----------------------------------------------------------------*/
/* AlteraPontuacao(link_equipa *tab_equipas, pJogo *tab_dispersao,*/
/*    int NL, unsigned int M): esta funcao recebe o ponteiro para */
/*    a tabela com listas de equipas, o ponteiro para a tabela de */
/*    dispersao, o numero da linha, NL, e o tamanho da tabela, M, */
/*    e verifica se o jogo existe no sistema, se existir altera   */
/*    os scores da suas equipas. Caso contrario, imprime erro.    */
/*----------------------------------------------------------------*/
void AlteraPontuacao(link_equipa *tab_equipas, pJogo *tab_dispersao, int NL, unsigned int M) {
    char nome[MAX_CAR];
    int score1_new, score2_new;
    pJogo jogo_ptr = NULL;
    link_equipa equipa1_ptr = NULL, equipa2_ptr = NULL;

    scanf(" %1023[^:\n]:%d:%d", nome, &score1_new, &score2_new);
    
    jogo_ptr = procura_tab_dispersao(tab_dispersao, nome, M);

    if (jogo_ptr == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    equipa1_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa1);
    equipa2_ptr = procura_equipa_lista(tab_equipas, jogo_ptr->equipa2);

    /* alteracao dos scores implica alteracao das vitorias atribuidas */
    if (jogo_ptr->score1 > jogo_ptr->score2 && score1_new < score2_new) {
        equipa1_ptr->vitorias--; 
        equipa2_ptr->vitorias++; 
    }
    if (jogo_ptr->score1 < jogo_ptr->score2 && score1_new > score2_new) {
        equipa1_ptr->vitorias++; 
        equipa2_ptr->vitorias--; 
    }
    if (jogo_ptr->score1 < jogo_ptr->score2 && score1_new == score2_new) {
        equipa2_ptr->vitorias--;
    }
    if (jogo_ptr->score1 > jogo_ptr->score2 && score1_new == score2_new) {
        equipa1_ptr->vitorias--; 
    }
    if (jogo_ptr->score1 == jogo_ptr->score2 && score1_new < score2_new) {
        equipa2_ptr->vitorias++; 
    }
    if (jogo_ptr->score1 == jogo_ptr->score2 && score1_new > score2_new) {
        equipa1_ptr->vitorias++; 
    }
    /* atribuicao dos novos scores */
    jogo_ptr->score1 = score1_new;
    jogo_ptr->score2 = score2_new;
    
    return;
}

/*----------------------------------------------------------------*/
/* compara(const void* c_equipa1, const void* c_equipa2):         */
/*    funcao auxiliar a EquipasVencedoras que devolve a           */
/*    comparacao dos nomes de duas equipas.                       */
/*----------------------------------------------------------------*/
int compara(const void * c_equipa1, const void * c_equipa2) {
    char **equipa1 = (char **)c_equipa1;
    char **equipa2 = (char **)c_equipa2;
    return strcmp(*equipa1, *equipa2);
} 

/*----------------------------------------------------------------*/
/* EquipasVencedoras(link_equipa *tab_equipas, int NL): esta      */
/*    funcao recebe o ponteiro para a tabela com listas de        */
/*    equipas e o numero da linha, NL, e encontra as equipas que  */
/*    ganharam mais jogos e lista por ordem lexicografica.        */
/*----------------------------------------------------------------*/
void EquipasVencedoras(link_equipa *tab_equipas, int NL){
    link_equipa x, aux = NULL;
    int max = 0, tamanho_vetor = 0, i = 0, j, p = 0;
    char **equipas_vencedoras ;

    /* procura na tabela das listas de equipas qual o maximo de jogos ganhos por uma equipa */
    for(j = 0; j < MAX_TAB; j++) {
        x = tab_equipas[j];
        if(x != NULL) {
            p = 1;
            for(aux = x; aux != NULL; aux = aux->next) {
                if(aux->vitorias > max) {
                    max = aux->vitorias;
                    tamanho_vetor = 1;
                }
                /* se encontrar uma equipa com o maximo de jogos ganhos aumenta o tamanho do vetor 
                que vai ser criado */
                else if(aux->vitorias == max) {
                    tamanho_vetor++;
                }
            }
        }
    }
    /* se a tabela com as listas de equipas for vazia sai */
    if( p == 0)
        return;

    /* reserva de memoria para o vetor onde ficaram as equipas com o maximo de jogos ganhos */
    equipas_vencedoras = malloc(tamanho_vetor * sizeof(char *));

    for(j = 0; j < 256; j++) {
        for(aux = tab_equipas[j]; aux != NULL; aux = aux->next) {
            if(aux->vitorias == max) {
                equipas_vencedoras[i] = (char*) malloc(sizeof(char)*(strlen(aux->equipa)+1));
                strcpy(equipas_vencedoras[i++], aux->equipa);
            }
        }
    }
    /* ordenacao do vetor com as equipas que ganharam mais jogos */
    qsort(equipas_vencedoras, tamanho_vetor, sizeof(char *), compara);

    printf("%d Melhores %d\n", NL, max);
    for(i = 0; i < tamanho_vetor; i++) {
        if(equipas_vencedoras[i] != NULL)
             printf("%d * %s\n", NL, equipas_vencedoras[i]);
    }
    /* libertacao da memoria reservada pelo vetor equipas_vencedoras */
    for(i = 0; i < tamanho_vetor; i++)
        free(equipas_vencedoras[i]);

    free(equipas_vencedoras);
}