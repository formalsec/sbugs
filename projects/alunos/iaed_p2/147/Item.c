#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Item.h"

/* Funcao auxiliar que inicializa a lista que guarda todos os jogos do sistema. */
pList list_init(){
    pList l = can_fail_malloc(sizeof(struct list));
    l -> head = l -> last = NULL;
    return l;
}


/* Funcao auxiliar que liberta o espaco relativo a um jogo. */
void free_jogo(pJogo j){
    free(j -> nome);
    free(j -> equipa1);
    free(j -> equipa2);
    free(j -> vencedora);
    free(j);
}


/* Funcao que liberta o espaco relativo a um link. */
void free_link(pLink l){
    free_jogo(l -> j);
    free(l);
}


/* Funcao que liberta o espaco relativo a um link_e. */
void free_link_e(pLink_e l){
    free(l -> e -> nome_e);
    free(l -> e);
    free(l);
}


/* Funcao que insere um jogo na lista de jogos. */
void list_insert(pList l, pJogo novo){
    novo -> next = NULL;
    novo -> previous = l -> last;
    if(l -> last){
        l -> last -> next = novo;
    }
    l->last = novo;
    if(!l -> head) {
        l -> head = novo;
    }
}


/* Funcao que apaga um jogo da lista de jogos. */
void list_delete(pList l, pJogo j){
    if(!j -> previous && !j -> next){
        l -> head = l -> last = NULL;
    }
    else if(j -> previous && !j -> next){
        l -> last = j -> previous;
        j -> previous -> next = NULL;
    }
    else if(!j -> previous && j -> next){
        j -> next -> previous = NULL;
        l -> head = j -> next;
    }
    else{
        j -> previous -> next = j -> next;
        j -> next -> previous = j -> previous;
    }
}
    

/* Funcao auxiliar para ponteiros que aloca memoria e copia a string dada para determinado ponteiro. */
char *dup(const char *s){
	char * dup = can_fail_malloc(strlen(s) + 1);
	if(dup != NULL){
        strcpy(dup, s);
    }
	return dup;
}


/* Funcao que cria um ponteiro para uma equipa. */
pEquipa cria_equipa(char *nome_e){
    pEquipa e = can_fail_malloc(sizeof(struct equipa));
    e -> nome_e = dup(nome_e);
    e -> wins = 0;
    return e;
}


/* Funcao que cria um ponteiro para um jogo. */
pJogo cria_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2){
    pJogo j = can_fail_malloc(sizeof(struct jogo));
    j -> nome = dup(nome);
    j -> equipa1 = dup(equipa1);
    j -> equipa2 = dup(equipa2);
    j -> score1 = score1;
    j -> score2 = score2;
    if(score1 > score2){
        j -> vencedora = dup(equipa1);
    }
    else if(score1 < score2){
        j -> vencedora = dup(equipa2);
    }
    else{
        j -> vencedora = NULL;
    }
    return j;
}

