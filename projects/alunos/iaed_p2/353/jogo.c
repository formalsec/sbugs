#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "jogo.h"

/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.| FUNCOES |.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/


/* ESTA FUNCAO INICIALIZA A HASHTABLE COM AS ENTRADAS VAZIAS */
ht_jogo *ht_init(void){
    
    int i = 0;

    /* aloca a tabela */
    ht_jogo *hashtable = can_fail_malloc(sizeof(ht_jogo));

    /* aloca as entradas da tabela */
    hashtable->links = can_fail_malloc(sizeof(link_jogo*) * TAM_TABELA);

    /* inicializa vazio */
    for(;i < TAM_TABELA; ++i){
        hashtable->links[i] = NULL;
    }

    return hashtable;
}

/* ESTA FUNCAO ALOCA E GUARDA MEMORIA E INFORMACAO NA HASHTABLE */
link_jogo *ht_pair(ht_jogo *hashtable, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2){
    
    unsigned int slot = hash(nome);

    /* aloca x */
    link_jogo *x = can_fail_malloc(sizeof(link_jogo));
    x->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
    x->equipa1 = can_fail_malloc(sizeof(char) * (strlen(equipa1) + 1));
    x->equipa2 = can_fail_malloc(sizeof(char) * (strlen(equipa2) + 1));

    /* copia o nome, as equipas e o score no lugar */
    strcpy(x->nome, nome);
    strcpy(x->equipa1, equipa1);
    strcpy(x->equipa2, equipa2);
    x->score1 = score1;
    x->score2 = score2;

    x->next = hashtable->links[slot];
    hashtable->links[slot] = x;

    return x;
}

/* ESTA FUNCAO INSERE O JOGO NA HASHTABLE */
void ht_set(ht_jogo *hashtable, ll_jogos **ll_head, ht_equipas *hashtable_equipas, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2,int NL){

    link_equipa *estado_equipa1 = st_search(hashtable_equipas, equipa1);
    link_equipa *estado_equipa2 = st_search(hashtable_equipas, equipa2);
    link_jogo *jogo = st_search_jogo(hashtable, nome);
    link_jogo *new;

    /* se o jogo ja existir da erro */
    if(jogo != NULL){
        printf("%d Jogo existente.\n",NL);
        return;
    }

    /* se a equipa nao existir da erro */
    if(estado_equipa1 == NULL || estado_equipa2 == NULL){
        printf("%d Equipa inexistente.\n",NL);
        return;
    }
    
    /* atualiza o nr de vitorias consoante o resultado */
    if(score1 > score2){
        estado_equipa1->nr_vitorias ++;
    }
    if(score1 < score2){
        estado_equipa2->nr_vitorias ++;
    }

    /* caso contrario resolve por encadeamento externo */
    new = ht_pair(hashtable,nome,equipa1,equipa2,score1,score2);
    insertEndJogos(ll_head,new);
}

/* ESTA FUNCAO ENCONTRA O JOGO NA HASHTABLE */
link_jogo* st_search_jogo(ht_jogo *hashtable, const char *nome){
    
    unsigned int slot = hash(nome);
    link_jogo *x = hashtable->links[slot];

    /* vai percorrer todos os elementos da linked list da hashtable */
    while(x != NULL){
        /* se tiverem nomes iguais */
        if(strcmp(x->nome,nome) == 0){
            return x;
        }
        x = x->next;
    }
    return NULL;
}


void ht_search(ht_jogo* hashtable, const char* nome, int NL){

    link_jogo* x = st_search_jogo(hashtable, nome);

    /* se o jogo nao existir na hashtable */
    if(x == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }
    printf("%d %s %s %s %d %d\n",NL,x->nome,x->equipa1,x->equipa2,x->score1,x->score2);
}

/* ESTA FUNCAO ELIMINA UM JOGO DA HASHTABLE */
void ht_del(ht_jogo *hashtable, const char *nome, int NL) {
    
    unsigned int slot = hash(nome);
    int indice = 0;
    link_jogo *x = hashtable->links[slot];
    link_jogo *anterior;
    
    /* se a entrada estiver vazia, o jogo nao existe na hashtable */
    if(x == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }
    
    /* corre todas as slots ate ao final  */
    while (x != NULL) {
        /* verifica o nome */
        if (strcmp(x->nome, nome) == 0) {
            /* primeiro elemento sem um prox elemento */
            if (x->next == NULL && indice == 0) {
                hashtable->links[slot] = NULL;
            }
            /* primeiro elemento com um elemento prox */
            if (x->next != NULL && indice == 0) {
                hashtable->links[slot] = x->next;
            }
            /* ultimo elemento */
            if (x->next == NULL && indice != 0) {
                anterior->next = NULL;
            }
            /* elemento no meio */
            if (x->next != NULL && indice != 0) {
                anterior->next = x->next;
            }
            /* liberta a entrada apagada */
            free(x->nome);
            free(x->equipa1);
            free(x->equipa2);
            free(x);

            return;
        }
        /* passa para o prox */
        anterior = x;
        x = anterior->next;

        ++indice;
    }
    /* se chegar aqui quer dizer que nao encontrou nenhum jogo na hashtable */ 
    printf("%d Jogo inexistente.\n",NL);
}

/* ESTA FUNCAO ALTERA OS RESULTADOS DE UM CERTO JOGO */
void ht_change(ht_jogo *hashtable, ht_equipas *hashtable_equipas, const char *nome, int score1, int score2, int NL){

    link_jogo *x = st_search_jogo(hashtable, nome);
    link_equipa* equipa1;
    link_equipa* equipa2;

    /* se nao houve esse jogo da erro e sai */
    if(x == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }

    equipa1 = st_search(hashtable_equipas, x->equipa1);
    equipa2 = st_search(hashtable_equipas, x->equipa2);

    /* atualiza o nr de vitorias consoante o resultado */
    /* score do input */
    if(score1 > score2){
        /* score dos jogos a ser mudado */
        if(x->score1 < x->score2){
            equipa1->nr_vitorias++;
            equipa2->nr_vitorias--;
        }
        if(x->score1 == x->score2)
            equipa1->nr_vitorias++;
    }
    if(score1 < score2){
        if(x->score1 > x->score2){
            equipa1->nr_vitorias--;
            equipa2->nr_vitorias++;
        }
        if(x->score1 == x->score2)
            equipa2->nr_vitorias++;    
    }
    if(score1 == score2){
        if(x->score1 > x->score2)
            equipa1->nr_vitorias--;
        if(x->score1 < x->score2)
            equipa2->nr_vitorias--;
    }

    /* altera o score */
    x->score1 = score1;
    x->score2 = score2;
}

/* NESTA FUNCAO E DADO POR REFERENCIA (PONTEIRO PARA PONTEIRO) A CABECA 
   DA LISTA E UM NOME, INSERE O NOVO NODE NO FIM DA LISTA */
void insertEndJogos(ll_jogos **head_ref, link_jogo *jogo){
    
    /* 1. aloca o node */
    ll_jogos *last = *head_ref;                      /* usado no passo 5 */
	ll_jogos *novo_node = can_fail_malloc(sizeof(ll_jogos));
    
    /* 2. guarda a data */
	novo_node->jogo = jogo;

    /* 3. este novo node vai ser o ultimo node, entao o next deste e NULL */
	novo_node->next = NULL;

    /* 4. se a linked list esta vazia, o novo node e uma cabeca */
    if(*head_ref == NULL){
        *head_ref = novo_node;
        return;
    }

    /* 5. caso contrario atravessa ate ao ultimo node */
    while(last->next != NULL)
        last = last->next;
    
    /* 6. muda o next do ultimo node */
    last->next = novo_node;

    return;
}

/* NESTA FUNCAO E DADO POR REFERENCIA (PONTEIRO PARA PONTEIRO) A CABECA 
   DA LISTA E UM NOME, ELIMINA A OCORRENCIA DO NOME NA LISTA */
void deleteNode(ll_jogos* *head_ref, link_jogo *jogo){

    /* guarda a head node */
    ll_jogos* temp = *head_ref;
    ll_jogos* anterior;

    /* se a head guarda o nome que tem de ser eliminado */
    if(temp != NULL && temp->jogo == jogo){
        *head_ref = temp->next;             /* muda a head */
        free(temp);
        return;
    }

    /* procura pelo nome a ser eliminado, mantem a procura pelo node
    anterior ja que temos de mudar o 'prev->next' */
    while(temp != NULL && temp->jogo != jogo){
        anterior = temp;
        temp = temp->next;
    }

    /* se o nome nao pertencer a linked list */
    if(temp == NULL) return;

    /* elimina a ligacao do node da linked list */
    anterior->next = temp->next;
    free(temp);
}

/* NESTE FUNCAO E DADA POR REFERENCIA (PONTEIRO PARA PONTEIRO) A CABECA
   DA LISTA, ELIMINA A LISTA TODA LIBERTANDO A MEMORIA */
void deleteList(ll_jogos** head){

    /* 1. 'dereferencia' head_ref para obter a head */
    ll_jogos* atual = *head;
    ll_jogos* antigo;

    /* 2. percorre todos os nodes e liberta a memoria */
    while(atual != NULL){
        antigo = atual;
        atual = atual->next;
        free(antigo);
    }

    /* 3. 'dereferencia' head_ref para afetar a cabeca */
    *head = NULL;
}