#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"


/*----------------------------------------------------------------------------*/
/*                              FUNCOES                                       */
/*----------------------------------------------------------------------------*/

/* adiciona uma nova equipa*/
void comando_A(int cont, lista_equipa le, ht_equipas ht_e){
    /* ptexto e o ponteiro para o nome da equipa e reservo espaco*/
    char *ptexto = (char *)can_fail_malloc(sizeof(char)*MAX_STR);

    /* le o espaco*/
    getchar();
    /* le o nome da equipa*/
    scanf("%[^\n]", ptexto);


    /*verificar se a equipa ja existe*/
    if (procura_equipa_hash_equipas(ht_e, ptexto) != -1) {
        printf("%d Equipa existente.\n", cont);
    }


    else{

        /*vamos adicionar a equipa a lista de equipas*/
        inserir_equipa(le, ptexto);
        /* vamos adicionar a equipa a hastable de equipas*/
        insere_equipa_hash_equipas(ht_e, le->head->e);
    }

    /* liberto o ponteiro*/
    free(ptexto);

}


/* procura uma equipa*/
void comando_P(int cont, ht_equipas ht_e){
    /* i vai ser a posicao da equipa na hashtable de equipas*/
    int i;
    /* ptexto e o ponteiro para o nome da equipa e reservo espaco*/
    char *ptexto = (char *)can_fail_malloc(sizeof(char) *MAX_STR);

    /*le o espaco*/
    getchar();
    /* le o nome da equipa*/
    scanf("%[^\n]", ptexto);

    /* procura a equipa na hastable de equipas e devolve a posicao*/
    i = procura_equipa_hash_equipas(ht_e, ptexto);

    /* caso a posicao seja -1, significa que a equipa nao existe*/
    if (i==-1) {
        printf("%d Equipa inexistente.\n", cont);
    }

    else{
        /* imprimimos o nome da equipa e o numero de jogos ganhos*/
        printf("%d %s %d\n", cont, ht_e->hash_equipas[i]->nome,
               ht_e->hash_equipas[i]->vitorias);
    }

    /* libertamos o ponteiro*/
    free(ptexto);
}

/* cria um novo jogo*/
void comando_a(int cont, lista_jogos lj, ht_jogos ht_j, ht_equipas ht_e){
    /* ie1 - posicao da equipa 1 na hashtable das equipas
     * ie2 - posicao da equipa 2 na hashtable das equipas
     * score1 - pontuacao da equipa 1
     * score 2 - pontuacao da equipa 2*/
    int ie1, ie2, score1, score2;

    /* ptexto e o ponteiro para o nome do jogo e reservo espaco*/
    char *ptexto = (char *)can_fail_malloc(sizeof(char) *MAX_STR);
    /* ptexto_e1 e o ponteiro para o nome da equipa 1 e reservo espaco*/
    char *ptexto_e1 = (char *)can_fail_malloc(sizeof(char) *MAX_STR);
    /* ptexto_e1 e o ponteiro para o nome da equipa 2 e reservo espaco*/
    char *ptexto_e2 = (char *)can_fail_malloc(sizeof(char) *MAX_STR);

    /*le o espaco*/
    getchar();
    /* le o nome do jogo*/
    scanf("%[^:\n]", ptexto);
    /*le o espaco*/
    getchar();
    /* le o nome da equipa 1*/
    scanf("%[^:\n]", ptexto_e1);
    /*le o espaco*/
    getchar();
    /* le o nome da equipa 2*/
    scanf("%[^:\n]", ptexto_e2);
    /* le as pontuacoes das equipas*/
    scanf(":%d:%d", &score1, &score2);

    /* encontra a posicao da equipa 1 na hashtable de equipas*/
    ie1 = procura_equipa_hash_equipas(ht_e, ptexto_e1);
    /* encontra a posicao da equipa 2 na hashtable de equipas*/
    ie2 = procura_equipa_hash_equipas(ht_e, ptexto_e2);

    /* caso o jogo ja se encontre no sistema*/
    if(procura_jogo_hash_jogos(ht_j, ptexto) != -1) {
        printf("%d Jogo existente.\n", cont);
    }

    /* caso uma ou ambas as equipas nao existem*/
    else if((ie1 == -1) || (ie2 == -1)){
        printf("%d Equipa inexistente.\n", cont);
    }

    else {
        /* inserimos o jogo da lista de jogos*/
        inserir_jogo(lj, ptexto, ht_e->hash_equipas[ie1],
                ht_e->hash_equipas[ie2], score1, score2);
        /* inserimos o jogo na hastable de jogos*/
        insere_jogo_hash_jogos(ht_j, lj->tail);
        /* aumento o numero de jogos ganhos a equipa com mais pontuacao no jogo*/
        aumenta_vitorias(lj->tail->j);
    }

    /* libertamos os ponteiros*/
    free(ptexto);
    free(ptexto_e1);
    free(ptexto_e2);

}


/* procura um jogo no sistema*/
void comando_p(int cont, ht_jogos ht_j){
    /* i vai ser a posicao do jogo na hashtable de jogos*/
    int i;
    /* ptexto e o ponteiro para o nome do jogo e reservo espaco*/
    char *ptexto = (char *)can_fail_malloc(sizeof(char) *MAX_STR);

    /*le o espaco*/
    getchar();

    /* le o nome do jogo*/
    scanf("%[^\n]", ptexto);

    /* procura o jogo na hastable dos jogo e devolve a posicao onde se encontra*/
    i = procura_jogo_hash_jogos(ht_j, ptexto);


    /* se i for igual a -1, significa que o jogo nao existe*/
    if (i == -1) {
        printf("%d Jogo inexistente.\n", cont);
    }
    else{
        /* imprime o nome do jogo, das equipas e os scores*/
        printf("%d %s %s %s %d %d\n",
               cont,
               ht_j->hash_jogos[i]->j->nome,
               ht_j->hash_jogos[i]->j->e1->nome,
               ht_j->hash_jogos[i]->j->e2->nome,
               ht_j->hash_jogos[i]->j->s1,
               ht_j->hash_jogos[i]->j->s2);
    }

    free(ptexto);

}


/* lista todos os jogos pela ordem em que foram introduzidos*/
void comando_l(int cont, lista_jogos lj) {
    imprimir_lista_jogos(cont, lj);
}

/* altera a pontuacao de um jogo*/
void comando_s(int cont, ht_jogos ht_j){
    /* 'i' e a posicao do jogo na hastable de jogos
     * novo_s1 e a nova pontuacao da equipa 1
     * novo_s2 e a nova pontuacao da equipa 2*/
    int i, novo_s1, novo_s2;
    /* ptexto e o ponteiro para o nome do jogo e reservo espaco*/
    char *ptexto = (char *)can_fail_malloc(sizeof(char) *MAX_STR);

    /* le o espaco*/
    getchar();
    /* le o nome do jogo*/
    scanf("%[^:\n]", ptexto);
    /* le as novas pontuacoes*/
    scanf(":%d:%d", &novo_s1, &novo_s2);


    /* encontra a posicao do jogo na hashtable dos jogos*/
    i = procura_jogo_hash_jogos(ht_j, ptexto);

    /* caseo 'i' seja igual a -1, significa que o jogo nao existe*/
    if (i == -1){
        printf("%d Jogo inexistente.\n", (cont));
    }

    /* caso o jogo exista, altera os scores*/
    else{
        altera_scores(ht_j->hash_jogos[i], novo_s1, novo_s2);
    }

    /* liberto o ponteiro*/
    free(ptexto);
}


/* apaga um jogo*/
void comando_r(int cont, ht_jogos ht_j, lista_jogos lj){
    /* i e a posicao do jogo na hastable de jogos*/
    int i;
    /* ptexto e o ponteiro para o nome do jogo*/
    char *ptexto = (char *)can_fail_malloc(sizeof(char) *MAX_STR);

    /*le o espaco*/
    getchar();

    /*leio do nome do jogo*/
    scanf("%[^\n]", ptexto);
    /* encontra a posicao para o jogo*/
    i = procura_jogo_hash_jogos(ht_j, ptexto);

    /* caso i seja -1, significa que o jogo nao existe*/
    if (i == -1) {
        printf("%d Jogo inexistente.\n", cont);
    }

    /* caso o jogo exista*/
    else{
        /* diminuimos o numero de jogos ganhos da equipa que teve mais pontuacao
         * neste jogo*/
        diminui_vitorias(ht_j->hash_jogos[i]->j);
        /* eliminamos o jogo da lista de jogos*/
        elimina_jogo_lista_jogos(lj, ht_j->hash_jogos[i]);
        /* eliminamos o jogo da hastable de jogos*/
        elimina_jogo_hash_jogos(ht_j, i);
    }


    /* libertamos o ponteiro */
    free(ptexto);
}


/* encontra as equipas que venceram mais jogos*/
void comando_g(int cont, lista_equipa le){
    /* caso o tamanho da lista de equipas for 0, nao existe nenhum jogo*/
    if (le->tamanho == 0)
        return;

    /* caso existam equipas*/
    else{
        /* procura o numero maximo de vitorias e quantas equipas tem o numero
         * maximo de vitorias atualizando esses parametros na lista de equipas*/
        procura_max_vitorias(le);
        /* encontra as equipas que tem o numero maximo de vitorias e lista-as
         * por ordem lexicografica*/
        encontra_max_vitorias(cont, le);

        /* atualiza novamente os parametros a 0*/
        le->max_vitorias = 0;
        le->cont_equipas_max_vit = 0;
    }
}

/* elimina as estruturas criadas no programa*/
void comando_x(lista_equipa le, lista_jogos lj, ht_equipas ht_e, ht_jogos ht_j){
    /* elimina a lista de jogos*/
    eliminar_lista_jogos(lj);
    /* elimina a hashtables de jogos*/
    eliminar_hash_jogos(ht_j->hash_jogos, ht_j->max);
    /* elimna a hashtable de equipas*/
    eliminar_hash_equipas(ht_e->hash_equipas, ht_e->max);
    /* elimina a lista de equipas*/
    eliminar_lista_equipa(le);

    /* liberta o ponteiro da estutura da hashtable das equipas*/
    free(ht_e);
    /* liberta o ponteiro da estutura da hashtable dos jogos*/
    free(ht_j);
}
