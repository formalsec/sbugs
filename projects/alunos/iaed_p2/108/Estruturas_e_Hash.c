#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Estruturas_e_Hash.h"

#define Primo_Random 1023

/*Codigo das funcoes da hashtable*/


int hash(char *nome,int max){
    int soma = 0; size_t i;int a = 1;
    for (i = 0; i < strlen(nome); i++){
        soma += nome[i];
        a = ( a * Primo_Random + soma) % max; /*Faz com que hashtable tenha menos colisoes */
    }
    return (a % max);
}

void Equipainit(int *max_equipas,int m,p_equipa **p_tab_e) {
    int i;*max_equipas = m;
    *p_tab_e = can_fail_malloc(*max_equipas * sizeof(p_equipa));
    for(i= 0;i< *max_equipas;i++){
        (*p_tab_e)[i] = NULL;
    }
}

/*Chamada a funcao para se poder utilizar na EquipaInsere */
void Equipaexpande(int *max_equipas,int *n_equipas,p_equipa **p_tab_e);


void EquipaInsere(int *max_equipas,int *n_equipas, p_equipa equipa,p_equipa **p_tab_e){
        int i = hash(equipa->nome,*max_equipas);
        while ((*p_tab_e)[i]!=NULL) { i = (i+1) % (*max_equipas); }
        (*p_tab_e)[i] = equipa;
        if ((*n_equipas)++ > (*max_equipas)/2){
            Equipaexpande(max_equipas,n_equipas,p_tab_e);
        }

}


void Equipaexpande(int *max_equipas,int *n_equipas,p_equipa **p_tab_e){
    int i;
    p_equipa *t = (*p_tab_e); 
    Equipainit(max_equipas,(*max_equipas)+(*max_equipas),p_tab_e); /*Duplica o tamanho da hashtable */
    for(i=0;i < (*max_equipas)/2;i++){
        if (t[i] != NULL){
            *n_equipas = (*n_equipas) - 1; /* Faz com que nao aumente o numero de equipas ao reenserir */
            EquipaInsere(max_equipas,n_equipas,t[i],p_tab_e);
        }
    }
    free(t);
}


p_equipa EquipaProcura(int *max_equipas,char *nome,p_equipa **p_tab_e){
    int key = hash(nome,*max_equipas);
    while((*p_tab_e)[key] != NULL){
        if(strcmp((*p_tab_e)[key]->nome,nome)== 0){
            return (*p_tab_e)[key];
        }
        else{
            key = (key+1) % (*max_equipas); /*Ve as posicoes a seguir a key ate encontrar um NULL */    
        }
    }
    return NULL;
}


void Jogoinit(int *max_jogos,int m,p_jogo **p_tab_j) {
    int i;*max_jogos = m;
    *p_tab_j = can_fail_malloc(*max_jogos * sizeof(p_jogo));
    for(i= 0;i< *max_jogos;i++){
        (*p_tab_j)[i] = NULL;
    }
}
void Jogoexpande(int *max_jogos,int *n_jogos,p_jogo **p_tab_j);

void JogoInsereHash(int *max_jogos,int *n_jogos, p_jogo jogo,p_jogo **p_tab_j){
        int i = hash(jogo->nome_j,*max_jogos);
        while ((*p_tab_j)[i]!=NULL) { i = (i+1) % (*max_jogos); }
        (*p_tab_j)[i] = jogo;
        if ((*n_jogos)++ > (*max_jogos)/2){
            Jogoexpande(max_jogos,n_jogos,p_tab_j);
        }

}
void Jogoexpande(int *max_jogos,int *n_jogos,p_jogo **p_tab_j){
    int i;
    p_jogo *t = (*p_tab_j); 
    Jogoinit(max_jogos,(*max_jogos)+(*max_jogos),p_tab_j);
    for(i=0;i < (*max_jogos)/2;i++){
        if (t[i] != NULL){
            *n_jogos = (*n_jogos) - 1;
            JogoInsereHash(max_jogos,n_jogos,t[i],p_tab_j);
        }
    }
    free(t);
}



p_jogo JogoProcura(int *max_jogos,char *nome,p_jogo **p_tab_j){
    int key = hash(nome,*max_jogos);
    while((*p_tab_j)[key] != NULL){
        if(strcmp((*p_tab_j)[key]->nome_j,nome)== 0){
            return (*p_tab_j)[key];
        }
        else{
            key = (key+1) % (*max_jogos);    
        }
    }
    return NULL;
}



/*Funcoes que so o jogo tem */


void JogoInsereLista(p_jogo jogo,link *head,link *tail){
    link new;
    if((*head) == NULL){ /* Quando e o primeiro elemento a ser inserido */
        (*head) = can_fail_malloc(sizeof(struct node));
        (*head)->next = NULL; (*head)->prev = NULL; 
        (*head)->jogo = jogo;
    }
    else if((*tail)== NULL){ /* Quando e o segundo elemento a ser inserido */
        (*tail) = can_fail_malloc(sizeof(struct node));
        (*tail)->jogo = jogo; (*tail)->next = NULL; (*tail)->prev = (*head);
        (*head)->next = (*tail); /*Lista passa a ter head e tail */
    }
    else{ /*Qualquer outro elemento e inserido pela tail */
        new = can_fail_malloc(sizeof(struct node));
        new->jogo = jogo;
        new->prev = (*tail);
        new->next = NULL;
        (*tail)->next = new;
        (*tail)= new; /* Atualizamos a tail para passar a apontar para o novo membro*/
    }
}


void JogoApagaHash(p_jogo jogo,int *max_jogos,int *n_jogos,p_jogo **p_tab_j){
    int i;int key; p_jogo v;
    key = hash(jogo->nome_j,*max_jogos);
    while((*p_tab_j)[key] != NULL){ /* Procura onde esta o jogo na hashtable */
        if((*p_tab_j)[key] == jogo) break;
        else key = (key + 1) % (*max_jogos);
    }
    (*n_jogos)--;(*p_tab_j)[key] = NULL; /* Nao da free aqui porque vai dar no apaga lista */
    for(i = (key + 1)% (*max_jogos);(*p_tab_j)[i] != NULL; i = (i + 1) %(*max_jogos),(*n_jogos)--){ 
        /* Re insere todos os elementos a seguir ao elemento retirado */
        v = (*p_tab_j)[i];
        (*p_tab_j)[i] = NULL;
        JogoInsereHash(max_jogos,n_jogos,v,p_tab_j); 
    }
}


void JogoApagaLista(p_jogo jogo, link *head,link *tail){
    link aux;
    if((*head)->jogo == jogo){ /* Se o jogo estiver na head,
        a head passa a ser o elemento a seguir e da se free a head antiga*/
        aux = (*head)->next;
        free((*head)->jogo->nome_j);
        free((*head)->jogo);
        free(*head);
        (*head) = aux;
    }
    else if((*tail)->jogo == jogo){ /* Se o jogo estiver na tail,
        a tail passa a ser o elemento anterior e da se free a tail antiga*/
        aux = (*tail)->prev;
        free((*tail)->jogo->nome_j);
        free((*tail)->jogo);
        free(*tail);
        aux->next = NULL;
        (*tail) = aux;
    }
    else{ /*Se nao, procura se  na lista
        ligasse a lista e liberta se o elemento */
        link t;
        t = (*head);
        while(t->jogo != jogo){
            t = t->next;
        }
        (t->prev)->next = t->next;
        (t->next)->prev = t->prev;
        free(t->jogo->nome_j);
        free(t->jogo);
        free(t);
    }
}
