#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"


/*----------------------------------------------------------------------------*/
/*                      FUNCOES - LISTA JOGOS                                 */
/*----------------------------------------------------------------------------*/
/* inicio a lista de jogos a NULL*/
lista_jogos inicia_lista_jogos(){
    /* reservamos espaco para a lista de jogos*/
    lista_jogos lj = (lista_jogos)malloc(sizeof(struct jlist));

    lj->head = NULL;
    lj->tail = NULL;
    lj->tamanho = 0;

    return lj;
}

/* cria um novo jogo*/
pjogo novo_jogo(char *buffer, pequipa pe1, pequipa pe2, int score1, int score2){
    /* reservamos espaco para o ponteiro do jogo*/
    pjogo x = (pjogo) malloc(sizeof(struct jogo));
    /* o ponteiro para o nome do jogo e o primeiro argumento*/
    /*x->nome = buffer;*/
    x->nome = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(x->nome, buffer);
    /* o ponteiro para a equipa 1 e o segundo argumento*/
    x->e1 = pe1;
    /* o ponteiro para a equipa 2 e o terceiro argumento*/
    x->e2 = pe2;
    /* introduzo o score da equipa 1*/
    x->s1 = score1;
    /* introduzo o score da equipa 2*/
    x->s2 = score2;

    return x;
}



/*insiro jogo da lista de jogos*/
void inserir_jogo(lista_jogos lj, char* texto, pequipa pe1, pequipa pe2,
        int score1, int score2){
    /* reservamos espaco na memoria para o ponteiro*/
    jlink x = (jlink)malloc(sizeof(struct jnode));
    /* criamos um novo jogo e guardamos no no*/
    x->j = novo_jogo(texto, pe1, pe2, score1, score2);

    /*se a lista de jogos estiver vazia*/
    if  (lj->tamanho == 0){
        lj->head = x;
    }

    /* caso a lista de jogos tiver pelo menos um elemento*/
    else{
        /* o proximo elemento do ultimo elemento da lista e o x*/
        lj->tail->next = x;
        /* apontamos o proximo anterior de x para o elemento que e atualmente
         * a cauda da lista */
        x->prev = lj->tail;
    }

    /* x e agora a cauda da lista de jogos*/
    lj->tail = x;
    /* atualizamos o numero de jogos*/
    lj->tamanho ++;

}

/* libertamos o no do jogo*/
void libertar_jogo(jlink x){
    if(x!= NULL) {
        /* libertamos o ponteiro para o nome do jogo*/
        free(x->j->nome);
        x->j->e1 = NULL;
        x->j->e2 = NULL;
        /* libertamos o ponteiro para o jogo*/
        free(x->j);
        /* libertamos o ponteiro para o no do jogo*/
        free(x);
    }
}

/*aumento o numero de vitorias da equipa que tem mais score*/
void aumenta_vitorias(pjogo x) {
    if (x->s1 > x->s2)
        x->e1->vitorias ++;

    else if (x->s1 < x->s2)
        x->e2->vitorias ++;
}

/* diminui vitorias da equipa que tem mais score*/
void diminui_vitorias(pjogo x) {
    if (x->s1 > x->s2)
        x->e1->vitorias --;

    else if (x->s1 < x->s2)
        x->e2->vitorias --;
}


/* eliminamos jogo da lista de jogos*/
void elimina_jogo_lista_jogos(lista_jogos lj, jlink x){
    /*se o jogo for o do inicio da lista*/
    if (lj->tamanho == 1){
        lj->head = NULL;
        lj->tail = NULL;
    }

    /*o jogo nao e o primeiro nem o ultimo elemento da lista*/
    else if ( (x!= lj->tail) && (x!= lj->head)){
        (x->prev)->next = x->next;
        (x->next)->prev = x->prev;
    }

    /* o jogo e o primeiro elemento*/
    else if (x==lj->head){
        lj->head = x->next;
        lj->head->prev = NULL;
    }

    /* o jogo e o ultimo elemento*/
    else if(x == lj->tail){
        lj->tail = x->prev;
        lj->tail->next = NULL;
    }

    libertar_jogo(x);

    /*diminuo o numero de jogos da lista de jogos*/
    lj->tamanho --;
}


/* imprimo os jogos da lista de jogos pela ordem em qe foram introduzidos*/
void imprimir_lista_jogos(int cont, lista_jogos lj){
    jlink x;
    for(x=lj->head; x != lj->tail; x=x->next){
        printf("%d %s %s %s %d %d\n", cont, x->j->nome, x->j->e1->nome,
                x->j->e2->nome,
               x->j->s1,x->j->s2);
    }
    if (lj->tail!=NULL)
        printf("%d %s %s %s %d %d\n", cont, lj->tail->j->nome,
                lj->tail->j->e1->nome,lj->tail->j->e2->nome,lj->tail->j->s1,
                lj->tail->j->s2);
}

/* eliminamos a lista de jogos*/
void eliminar_lista_jogos(lista_jogos lj){
    jlink atual, prox;
    atual = lj->head;

    while(atual != lj->tail) {
        prox = atual->next;
        /* libertamos o no do jogo*/
        libertar_jogo(atual);
        atual = prox;
    }

    libertar_jogo(lj->tail);

    /* libertamos o ponteiro para a lista de jogos*/
    free(lj);
}


/*----------------------------------------------------------------------------*/
/*                      FUNCOES - HASTABLE EQUIPAS                            */
/*----------------------------------------------------------------------------*/
/* inicio a estrutura da tabela de equipas*/
ht_jogos iniciar_tabela_jogos(){
    /* reservo espaco para o ponteiro para a tabela de jogos*/
    ht_jogos ht_j = (ht_jogos)malloc(sizeof(struct hashtable_jogos));
    /* o ponteiro da hashtable de jogos vai apontar para NULL*/
    ht_j->hash_jogos = NULL;
    ht_j->max = MAX_H_EQUIPAS;
    /* nao existe nenhum jogo na hashtable*/
    ht_j->atual = 0;

    return ht_j;
}

/* inicio a hashtable de jogos*/
jlink* iniciar_hash_jogos(int M) {
    int i;
    /* reservo espaco*/
    jlink * hash_jogos = (jlink*)malloc(M*sizeof(jlink));
    for (i = 0; i < M; i++)
        /* inicializo tudo a NULL*/
        hash_jogos[i] = NULL;

    return hash_jogos;
}

/* eliminar a hashtable de jogos do sistema*/
void eliminar_hash_jogos(jlink * hash_jogos, int M){
    int i;
    /* percorro toda a hashtable*/
    for (i=0; i<M; i++){
        if(hash_jogos[i] != NULL)
            /* coloco todos os ponteiros a NULL*/
            hash_jogos[i] = NULL;
    }
    /* liberto o ponteiro da hashtable de jogos*/
    free(hash_jogos);
}

void expandir_hash_jogos (ht_jogos ht_j);

/* coloco o ponteiro do jogo na hashtable de jogos*/
void insere_jogo_hash_jogos(ht_jogos ht_j, jlink x) {
    /* 'i' e o indice da posicao onde o ponteiro devera ser colocar*/
    int i = hash(x->j->nome, ht_j->max);

    /* caso ja haja outro ponteiro nessa posicao, determino outra posicao*/
    while (ht_j->hash_jogos[i] != NULL)
        i = (i + 1) % ht_j->max;

    /* coloco o ponteiro da equipa na posicao da hashtable*/
    ht_j->hash_jogos[i] = x;
    /* aumento o numero de equipas que existem nas hashtable*/
    (ht_j->atual)++;


    /* caso a hashtable ja esteja com metade da capacidade ocupada, vamos
     * aumentar o seu tamanho*/
    if (ht_j->atual > (ht_j->max/ 2))
        expandir_hash_jogos(ht_j);

}

/* expande o tamanho da hashtable de jogos*/
void expandir_hash_jogos (ht_jogos ht_j) {
    int i;

    /* crio outro ponteiro para apontar para a hashtables de jogos atual*/
    jlink *t = ht_j->hash_jogos;

    /* crio outra hashtable com o dobro do tamanho*/
    ht_j->hash_jogos = iniciar_hash_jogos((2*ht_j->max));

    /* atualizo o tamanho da nova hashtable e o numero atual de equipas*/
    ht_j->max = 2* ht_j->max;
    ht_j->atual = 0;

    for (i = 0; i < (ht_j->max/2); i++){
        if (t[i] != NULL) {
            /* reinsiro os ponteiros dos jogos da hastable antiga na nova
             * hashtable*/
            insere_jogo_hash_jogos(ht_j, t[i]);
        }
    }

    /* liberto o ponteiro da antiga hashtable*/
    free(t);
}


/* procura um jogo na hashtable de jogos*/
int procura_jogo_hash_jogos(ht_jogos ht_j, char*texto){
    /* determina a posicao que o jogo possa estar de acordo com o seu nome*/
    int i = hash(texto, ht_j->max);


    while (ht_j->hash_jogos[i] != NULL)
        /* caso os nomes sejam iguais, retorna a posicao em que o jogo
         * se encontra*/
        if ( strcmp(ht_j->hash_jogos[i]->j->nome, texto) == 0) {
            return i;
        }
        else
            /* determino a proxima posicao onde o jogo a possa estar*/
            i = (i+1) % ht_j->max;

    /* caso o jogo nao esteje na hashtable, retorna -1 */
    return -1;
}

/* elimina jogo da hastable dos jogos*/
void elimina_jogo_hash_jogos(ht_jogos ht_j, int i) {
    int j;
    jlink x;
    /* a posicao passa a apontar para NULL*/
    ht_j->hash_jogos[i] = NULL;

    /*recoloca os elementos da hashtable*/
    for (j = (i + 1) % ht_j->max; ht_j->hash_jogos[j] != NULL;
    j = (j + 1) % ht_j->max) {
        x = ht_j->hash_jogos[j];
        ht_j->hash_jogos[j] = NULL;
        insere_jogo_hash_jogos(ht_j, x);
    }

    /* diminui o numero de jogos na hashtable*/
    ht_j->atual --;
}


/* altera os scores do jogo*/
void altera_scores(jlink x, int novo_s1, int novo_s2){
    if (novo_s1 > novo_s2){
        if(x->j->s2 > x->j->s1) {
            /*aumentar vitorias do e1*/
            x->j->e1->vitorias++;
            /*diminuir vitorias do e2*/
            x->j->e2->vitorias --;
        }

        else if (x->j->s1 == x->j->s2) {
            /*aumentar vitorias do e1*/
            x->j->e1->vitorias++;
        }
    }

    else if (novo_s2 > novo_s1){
        if(x->j->s1 > x->j->s2) {
            /*aumentar vitorias do e1*/
            x->j->e2->vitorias++;
            /*diminuir vitorias do e2*/
            x->j->e1->vitorias --;
        }

        else if (x->j->s1 == x->j->s2) {
            /*aumentar vitorias do e1*/
            x->j->e2->vitorias++;
        }
    }

        /* novo_si == novo_s2*/
    else{
        if (x->j->s1 > x->j->s2){
            /*diminuir vitorias do e1*/
            x->j->e1->vitorias--;
        }

        else if (x->j->s2 > x->j->s1){
            /*diminuir vitorias do e1*/
            x->j->e2->vitorias--;
        }
    }

    /* atualizo os scores*/
    x->j->s1 = novo_s1;
    x->j->s2 = novo_s2;
}