#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash.h"

/* Funcao que atribui um numero, um indice, consoante o nome dado. */
unsigned int hash(int M, const char *nome){
    unsigned int i;
    unsigned int index = 0; 

    for(i = 0; i < strlen(nome); i++){
        index += nome[i]; 
        index = (index * nome[i]) % M; 
    }
    return index;
}


/* Funcao auxiliar que insere o jogo na hastable dos jogos. */
pLink insertBeginList(pLink head, pJogo j){
    pLink old_head = head;
    head = can_fail_malloc(sizeof(struct link));
    head -> next = old_head;
    head -> j = j;
    return head;
}


/* Funcao auxiliar que insere a equipa na hastable das equipas. */
pLink_e insertBeginList_e(pLink_e head, pEquipa e){
    pLink_e old_head = head;
    head = can_fail_malloc(sizeof(struct link_e));
    head -> next = old_head;
    head -> e = e;
    return head;
}


/* Funcao auxiliar que procura dado jogo na hastable dos jogos. */
pJogo searchList(pLink head, char *nome){
    pLink temp = head;
    while(temp){
        if(strcmp(temp -> j -> nome, nome) == 0){
            return temp -> j;
        }
        temp = temp -> next;
    }
    return NULL;
}


/* Funcao auxiliar que procura dada equipa na hastable das equipas. */
pEquipa searchList_e(pLink_e head, char *nome){
    pLink_e temp = head;
    while(temp){
        if(strcmp(temp -> e -> nome_e, nome) == 0){
            return temp -> e;
        }
        temp = temp -> next;
    }
    return NULL;
    
}


/* Funcao auxiliar que remove o jogo da hastable dos jogos. */
pLink removeList(pLink head, char *nome){
    pLink temp = head, prev = NULL;
    if(!head){
        return NULL;
    }
    while(temp){
        if(strcmp(temp -> j -> nome, nome) == 0){
            if(temp == head){
                head = temp -> next;
            }
            else{
                prev -> next = temp -> next;
            }
            free_link(temp);
            break;
        }
        prev = temp;
        temp = temp -> next;
    }
    return head;
 }


/* Funcao que inicializa a hastable que armazenara todos os jogos presentes na base de dados sistema. */
pHash ht_init(int m){
    int i;
    pHash h = can_fail_malloc(sizeof(struct ht));
    h -> M = m;
    h -> heads = (pLink*)can_fail_malloc((h -> M) *sizeof(struct link));
    for (i = 0; i < m; i++){
        h -> heads[i] = NULL;
    }
    return h;
}


/* Funcao que inicializa a hastable que armazenara todas as equipas presentes na base de dados sistema. */
pHash_e ht_init_e(int m){
    int i;
    pHash_e h_e = can_fail_malloc(sizeof(struct ht_e));
    h_e -> M = m;
    h_e -> heads_e = (pLink_e*)can_fail_malloc((h_e -> M)*sizeof(struct link_e));
    for (i = 0; i < m; i++) {
        h_e -> heads_e[i] = NULL;
    }
    return h_e;
}


/* Funcao que liberta todos a hastable dos jogos. */
void ht_destroy(pHash h) {
    int i;
    pLink t1;
    for (i = 0; i < h -> M; i++) {
        t1 = h -> heads[i];
        while(h -> heads[i]) {
            t1 = h -> heads[i];
            h -> heads[i] = h -> heads[i] -> next;
            free_link(t1);
        }
    }
    free(h -> heads);
    free(h);
}


/* Funcao que liberta todas as equipas da base de dados sistema. */
void ht_e_destroy(pHash_e h_e) {
    int i;
    pLink_e t1;
    for (i = 0; i < h_e -> M; i++) {
        t1 = h_e -> heads_e[i];
        while(h_e -> heads_e[i]) {
            t1 = h_e -> heads_e[i];
            h_e -> heads_e[i] = h_e -> heads_e[i] -> next;
            free_link_e(t1);
        }
    }
    free(h_e -> heads_e);
    free(h_e);
}


/* Funcao que encontra um jogo na base de dados do sistema, dado o seu nome. */
pJogo ht_search(pHash h, char *nome) {
    int i = hash(h -> M, nome);
    if(h -> heads[i] != NULL){
        return searchList(h -> heads[i], nome);
    }
    else{
        pJogo j = NULL;
        return j;
    }
}


/* Funcao que encontra uma equipa na base de dados do sistema, dado o seu nome. */
pEquipa ht_search_e(pHash_e h_e, char *nome_e) {
    int i = hash(h_e -> M, nome_e);
    if(h_e -> heads_e[i] != NULL){
        return searchList_e(h_e -> heads_e[i], nome_e);
    }
    else{
        pEquipa e = NULL;
        return e;
    }
}


/* Funcao que insere um jogo na base de dados do sistema. */
void ht_insert(pHash h, pJogo j) {
    int i = hash(h -> M, j -> nome);
    h -> heads[i] = insertBeginList(h -> heads[i], j);
}


/* Funcao que insere uma equipa na base de dados do sistema. */
void ht_insert_e(pHash_e h_e, pEquipa e) {
    int i = hash(h_e -> M, e -> nome_e);
    h_e -> heads_e[i] = insertBeginList_e(h_e -> heads_e[i], e);
}


/* Funcao que apaga um jogo hastable dos jogos. */
void ht_delete(pHash h, char *nome) {
    int i = hash(h -> M, nome);
    h -> heads[i] = removeList(h -> heads[i], nome);
}
