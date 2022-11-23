#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "processos.h"



char *strdup(const char *src) {
    char *dst = can_fail_malloc(strlen (src) + 1);  
    if (dst == NULL) return NULL;          
    strcpy(dst, src);                      
    return dst;                           
}

int goodHash(char *str, int max){
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    hash = hash % max;
    return hash;
}

pJogo* JOGOinit(int max, pJogo *tabJ) {
    int i;
    tabJ = (pJogo*) can_fail_malloc(max*sizeof(pJogo));
    for(i = 0; i<max; i++) {
        tabJ[i] = NULL;
    }
    return tabJ;
}


void JOGOinsert(pJogo jogo,  pJogo *tabJ, int max) {
    int i;
    i = goodHash(jogo->nome, max);
    while(tabJ[i] != NULL) {
        i = (i+1) % max;
    }
    tabJ[i] = jogo;
}


pJogo JOGOsearch(char *nome, pJogo *tabJ, int max) {
    int i;
    i = goodHash(nome, max);
    while(tabJ[i] != NULL) {
        if(strcmp(tabJ[i]->nome, nome)==0){
            return tabJ[i];
        } else {
            i = (i+1) % max;
        }
    }
    return NULL;
}

void JOGOdelete(char *nome, pJogo *tabJ, int max) {
    pJogo p;
    int j, i;
    i = goodHash(nome, max);
    while(tabJ[i] != NULL) {
        if (strcmp(tabJ[i]->nome,nome)==0){
            if(tabJ[i] == NULL) return;
            free(tabJ[i]);
            tabJ[i]=NULL;
            for(j = (i+1)%max;tabJ[j]!=NULL;j = (j+1)%max) {
                p = tabJ[j];
                tabJ[j] = NULL;
                JOGOinsert(p,tabJ,max);
            }
        }else{
            i = (i+1) % max;
        }
        
    }
}

pJogo* JOGOexpand(pJogo *tabJ, int max){
    int i;
    pJogo *t = tabJ;
    tabJ = JOGOinit(max, tabJ);
    for(i=0; i<max/2; i++){
        if(t[i]!=NULL){
            JOGOinsert(t[i],tabJ,max);
        }
    }
    free(t);
    return tabJ;
}



DLinkedList JOGOlist_init(){
    DLinkedList list = can_fail_malloc(sizeof(struct MasterNode));
    list->load = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

qlink JOGOappend(DLinkedList list, pJogo jogo){
    qlink newNode = addNode(list->tail,NULL,jogo);
    list->tail = newNode;
    if(list->head == NULL){
         list->head = newNode;
    }
    list->load++;
    return newNode;
}

qlink addNode(qlink prev, qlink next, pJogo jogo){
    qlink new = can_fail_malloc(sizeof(struct QUEUEnode));
    new->jogo = jogo;
    new->prev = prev;
    new->next = next;
    if(prev != NULL) prev->next = new;
    if(next != NULL) next->prev = new;
    
    return new;
}
void JOGOshow(pJogo jogo,int contComandos) {
    printf("%d %s %s %s %d %d\n",contComandos,jogo->nome,jogo->equipa1,jogo->equipa2,jogo->score1,jogo->score2);
}

void JOGOlist(int contComandos, DLinkedList list) {
    qlink c;
    for( c = list->head; c!= NULL; c = c ->next) {
        JOGOshow(c -> jogo, contComandos);
    }
}


void JOGOQdelete(qlink jogo, DLinkedList list){
    qlink current = jogo;

    if(strcmp(current->jogo->nome, list->head->jogo->nome)==0){
        pop(list);
    } else if(strcmp(current->jogo->nome, list->tail->jogo->nome)==0){
        removeLastNode(list);
    }else{
        current->prev->next =current->next;
        current->next->prev = current->prev;
        free(current);
    }
    list->load--;
}

void pop(DLinkedList list){
    qlink oldHead = list->head;
    list->head = oldHead->next;
    if(list->head!=NULL) list->head->prev = NULL;
    else list->tail = NULL;
    free(oldHead);
}

void removeLastNode(DLinkedList list){
    qlink oldTail = list->tail;
    list->tail = oldTail->prev;
    if(list->tail != NULL) list->tail->next = NULL;
    else list->head = NULL;
    free(oldTail);
}

