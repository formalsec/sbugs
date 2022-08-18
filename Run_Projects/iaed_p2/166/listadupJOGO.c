#include "listadupJOGO.h"

/* cria uma estrutura jogo */
Jogo * mk_jogo(char nome[MAXNOME], char eq1[MAXEQUIPA],
               char eq2[MAXEQUIPA], int score[2]){
    Jogo * novoJogo = malloc(sizeof(Jogo));
    novoJogo->nome = malloc(sizeof(char)*(strlen(nome)+1));
    memset(novoJogo->nome,'\0', sizeof(char)*(strlen(nome)+1));
    strcpy(novoJogo->nome, nome);
    novoJogo->equipa1 = malloc(sizeof(char)*(strlen(eq1)+1));
    memset(novoJogo->equipa1,'\0', sizeof(char)*(strlen(eq1)+1));
    strcpy(novoJogo->equipa1, eq1);
    novoJogo->equipa2 = malloc(sizeof(char)*(strlen(eq2)+1));
    memset(novoJogo->equipa2,'\0', sizeof(char)*(strlen(eq2)+1));
    strcpy(novoJogo->equipa2, eq2);
    novoJogo->score[0] = score[0];
    novoJogo->score[1] = score[1];
    return novoJogo;
}


/* cria lista duplamente ligada de jogos vazia */
list_jogo * mk_list_jogo(){
    list_jogo * newL = malloc(sizeof(list_jogo));
    newL->head = NULL;
    newL->last = NULL;
    return newL;
}

/* acrescenta novo jogo no final da lista */
void add_last_jogo(list_jogo * l, Jogo * j){
    node_jogo * newNode = malloc(sizeof(node_jogo));
    newNode->next = NULL;
    newNode->jogo = j;
    /* se lista estiver vazia */
    if (l->head == NULL && l->last == NULL){
        newNode->previous = NULL;
        l->head = newNode;
        l->last = newNode;
    }
    /* lista tem elementos */
    else{
        newNode->previous = l->last;
        l->last->next = newNode;
        l->last = newNode;
    }
}

void remove_jogo_aux(node_jogo * l_head, Jogo * j){
    /* o jogo nao corresponde a l_head, verifica proximo */
    if (strcmp(l_head->jogo->nome, j->nome) != 0)
        remove_jogo_aux(l_head->next, j);
    else{
        /* encontrou o jogo, vamos remove-lo da lista */
        /* se for a cabeca da lista, so vai mudar o next */
        if (l_head->previous != NULL){
            l_head->previous->next = l_head->next;
        }
        /* se for ultimo da lista, so muda previous */
        if (l_head->next != NULL)
            l_head->next->previous = l_head->previous;
        /* libertar memoria do jogo que removemos */
        free_jogo(j);
        free(l_head);
    }
}

/* Remove jogo de uma lista */
void remove_jogo(list_jogo * l, Jogo *j){
    remove_jogo_aux(l->head, j);
    /* se for o unico elemento da lista, fica vazia */
    if (l->head == l->last){
        l->head = NULL;
        l->last = NULL;
    }
}

/* liberta toda a memoria associada a um jogo */
void free_jogo(Jogo * j){
    free(j->nome);
    free(j->equipa1);
    free(j->equipa2);
    free(j);
}

/* liberta toda a memoria associada a lista */
void free_list_jogo(list_jogo * l){
    node_jogo * newLast, * lastNode = l->last;
    /* lista vazia */
    if (l->head == NULL)
        free(l);
    else{
        /* liberta todos menos cabeca */
        while (lastNode != l->head){
            newLast = lastNode->previous;
            free_jogo(lastNode->jogo);
            free(lastNode);
            newLast->next = NULL;
            lastNode = newLast;
        }
        /* liberta cabeca */
        free_jogo(lastNode->jogo);
        free(lastNode);
        free(l);
    }
}