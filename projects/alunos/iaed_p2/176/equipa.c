#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipa.h"


/*----------------------------------------------------------------------------*/
/*                      FUNCOES - LISTA EQUIPAS                               */
/*----------------------------------------------------------------------------*/

/* inicia_lista_equipa vai inicializar a lista de equipas a NULL*/
lista_equipa inicia_lista_equipa(){
    /* reservamos espaco para a lista de equipas*/
    lista_equipa le = (lista_equipa)can_fail_malloc(sizeof(struct elist));

    le->head = NULL;
    le->tamanho = 0;
    le->max_vitorias = 0;
    le->cont_equipas_max_vit = 0;

    return le;
}


/* vai criar uma nova equipa*/
pequipa nova_equipa(char *buffer) {
    /* reservamos espaco para o ponteiro da equipa*/
    pequipa x = (pequipa)can_fail_malloc(sizeof(struct equipa));
    /* o ponteiro para o nome da equipa e o argumento recebido*/
    x->nome = (char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(x->nome, buffer);
    /*x->nome = buffer;*/
    /* como estamos a introduzir no sistema, o seu numero de vitorias e 0*/
    x->vitorias = 0;
    return x;
}



/*insero equipa na lista de equipas*/
void inserir_equipa(lista_equipa le, char* texto){
    /* reservamos espaco na memoria para o ponteiro*/
    elink x = (elink)can_fail_malloc(sizeof(struct enode));
    /* criamos uma nova equipa e guardamos no no*/
    x->e = nova_equipa(texto);

    /* caso a lista de equipas esteja vazia*/
    if (le->head == NULL) {
        x->next = NULL;
    }

    /* caso a lista de equipas ja tiver um elemento, apontamos o proximo
     * elemento de x para o elemento que e atualmente a cabeca da lista*/
    else{
        x->next = le->head;
    }

    /* x passa a ser a cabeca da lista*/
    le->head = x;
    /* o numero de equipas na da lista de equipas aumentou*/
    le->tamanho ++;
}

/* libertamos o no da equipa*/
void libertar_equipa(elink x){
    /* libertamos o ponteiro para o nome da equipa*/
    free(x->e->nome);
    /* libertamos o ponteiro para a equipa*/
    free(x->e);
    /* libertamos o ponteiro para o no da equipa*/
    free(x);
}


/* eliminamos a lista de equipas*/
void eliminar_lista_equipa(lista_equipa le){
    elink atual, prox;
    atual = le->head;

    while(atual != NULL) {
        prox = atual->next;
        /* libertamos o no da equipa*/
        libertar_equipa(atual);
        atual = prox;
    }

    /* libertamos o ponteiro para a lista de equipas*/
    free(le);
}


/* percorre toda a lista de equipas e procura o numero maximo de vitorias e
 * o numero de equipas que tiveram o numero maximo de vitorias*/
void procura_max_vitorias(lista_equipa le){
    elink x;

    /* percorre toda a lista de equipas*/
    for (x = le->head; x!= NULL; x= x->next){

        /* se o numero de vitorias da equipa atual for superior ao max_vitorias,
         * o max_vitorias passa a ser o numero de vitorias dessa equipa*/
        if( x->e->vitorias > le->max_vitorias){
            le->max_vitorias = x->e->vitorias;
            /* o numero de equipas com o maximo de vitorias e atualizado para 1*/
            le->cont_equipas_max_vit = 1;
        }

        else if(x->e->vitorias == le->max_vitorias)
            le->cont_equipas_max_vit ++;
    }
}


/* compara strings pela ordem lexicografica*/
int compara_strings(const void* a, const void* b)
{
    return strcmp(*(const char**)a, *(const char**)b);
}


/* vai encontrar as equipas com mais vitorias e imprime o nome delas por ordem
 * lexicografica*/
void encontra_max_vitorias(int cont, lista_equipa le){

    int max = le->cont_equipas_max_vit;
    /* reservamos espaco para a tabela de ponteiros dos nomes das equipas*/
    char** tab = (char**)can_fail_malloc(sizeof(char*)*max);
    elink x;
    int i = 0;

    /* percorremos a lista de equipas e colocamos os ponteiros dos nomes das
     * equipas na tabela*/
    for (x = le->head; i < le->cont_equipas_max_vit; x= x->next){
        if( x->e->vitorias == le->max_vitorias) {
            tab[i] = (x->e->nome);
            i++;
        }
    }

    /*a tabela e ordenada de acordo a ordem lexicografica do nome das equipas*/
    qsort(tab, max, sizeof(char*), compara_strings);

    printf("%d Melhores %d\n", cont, le->max_vitorias);

    /* colocamos a tabela a NULL*/
    for (i = 0; i < max; i++){
        printf("%d * %s\n", cont, tab[i]);
    }

    /* libertamos a tabela*/
    free(tab);

}

/*----------------------------------------------------------------------------*/
/*                    FUNCOES - HASTABLE EQUIPAS                              */
/*----------------------------------------------------------------------------*/

/* determina em que posicao da hastable fica o ponteiro para a equipa de acordo
 * com o seu nome*/
int hash(char* v, int M) {
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a * h + *v) % M;
    return h;
}

/* inicio a estrutura da tabela de equipas*/
ht_equipas iniciar_tabela_equipas(){
    /* reservo espaco para o ponteiro para a tabela de equipas*/
    ht_equipas ht_e = (ht_equipas)can_fail_malloc(sizeof(struct hashtable_equipas));
    /* o ponteiro da hashtable de equipas vai apontar para NULL*/
    ht_e->hash_equipas = NULL;
    ht_e->max = MAX_H_EQUIPAS;
    /* nao existe nenhuma equipa na hashtable*/
    ht_e->atual = 0;

    return ht_e;
}


/* inicio a hashtable de equipas*/
pequipa* iniciar_hash_equipas(int M) {
    int i;
    /* reservo espaco*/
    pequipa * hash_equipas = (pequipa*)can_fail_malloc(M*sizeof(pequipa));
    for (i = 0; i < M; i++)
        /* inicializo tudo a NULL*/
        hash_equipas[i] = NULL;

    return hash_equipas;
}


/* eliminar a hashtable de equipas do sistema*/
void eliminar_hash_equipas(pequipa * hash_equipas, int M){
    int i;
    /* percorro toda a hashtable*/
    for (i=0; i< M; i++){
        if(hash_equipas[i] != NULL)
            /* coloco todos os ponteiros a NULL*/
            hash_equipas[i] = NULL;
    }

    /* liberto o ponteiro da hashtable de equipas*/
    free(hash_equipas);
}


void expandir_hash_equipas(ht_equipas ht_e);


/* coloco o ponteiro da equipa na hashtable de equipas*/
void insere_equipa_hash_equipas(ht_equipas ht_e, pequipa e) {
    /* 'i' e o indice da posicao onde o ponteiro devera ser colocar*/
    int i = hash(e->nome, ht_e->max);

    /* caso ja haja outro ponteiro nessa posicao, determino outra posicao*/
    while (ht_e->hash_equipas[i] != NULL)
        i = (i + 1) % ht_e->max;

    /* coloco o ponteiro da equipa na posicao da hashtable*/
    ht_e->hash_equipas[i] = e;
    /* aumento o numero de equipas que existem nas hashtable*/
    ht_e->atual++;

    /* caso a hashtable ja esteja com metade da capacidade ocupada, vamos
     * aumentar o seu tamanho*/
    if (ht_e->atual > ( ht_e->max / 2))
        expandir_hash_equipas(ht_e);

}

/* expande o tamanho da hashtable de equipas*/
void expandir_hash_equipas(ht_equipas ht_e) {
    int i;

    /* crio outro ponteiro para apontar para a hashtables de equipas atual*/
    pequipa *t = ht_e->hash_equipas;

    /* crio outra hashtable com o dobro do tamanho*/
    ht_e->hash_equipas = iniciar_hash_equipas((2*(ht_e->max)));

    /* atualizo o tamanho da nova hashtable e o numero atual de equipas*/
    ht_e->max = 2 * ht_e->max;
    ht_e->atual = 0;

    for (i = 0; i < (ht_e->max/2); i++){
        if (t[i] != NULL) {
            /* reinsiro os ponteiros das equipas da hastable antiga na nova
             * hashtable*/
            insere_equipa_hash_equipas(ht_e, t[i]);
        }
    }

    /* liberto o ponteiro da antiga hashtable*/
    free(t);
}


/* procura uma equipa na hashtable de equipas*/
int procura_equipa_hash_equipas(ht_equipas ht_e, char*texto){
    /* determina a posicao que a equipa possa estar de acordo com o seu nome*/
    int i = hash(texto, ht_e->max);


    while (ht_e->hash_equipas[i] != NULL)
        /* caso os nomes sejam iguais, retorna a posicao em que a equipa
         * se encontra*/
        if ( strcmp(ht_e->hash_equipas[i]->nome, texto) == 0) {
            return i;
        }
        else
            /* determino a proxima posicao onde a equipa possa estar*/
            i = (i+1) % ht_e->max;

    /* caso a equipa nao esteje na hashtable, retorna -1 */
    return -1;
}
