#include "main_aux.h"


/* guarda os jogos pela ordem de insercao */
void guarda_lista_ord(bloco_hash_jogo *head,bloco_hash_jogo *tail,jogo *j){ 
    bloco_hash_jogo novo_el;                                      
    novo_el = malloc(sizeof(struct bloco_h_jogo));                
    novo_el->jogo = j; novo_el->next = NULL;
    if(head[0] == NULL){                /* guarda na head se esta estiver vazia */
        head[0] = novo_el;
        tail[0] = head[0];
    } 
    else{                               /* senao guarda pela tail */
        tail[0]->next = novo_el;
        tail[0] = novo_el; 
    }
}

/* apaga os jogos da lista ordenada */
void apaga_lista_ord(bloco_hash_jogo *head_ord, bloco_hash_jogo *tail_ord ,char *nome){
    bloco_hash_jogo aux = (*head_ord);                            /* variavel usada para percorrer a lista ligada */
    bloco_hash_jogo ante = NULL;                                  /* variavel que corresponde ao elemento anterior ao aux para ser possivel reconectar a lista ligada */
    while (aux != NULL && strcmp(aux->jogo->nome,nome) != 0){     /* encontra o jogo */
        ante = aux;
        aux = aux->next;

    }
    if (aux == NULL) return;        /* lista estava vazia*/
    if (ante == NULL){              /* o jogo que queremos apagar esta na head */
        (*head_ord) = aux->next;    
    }
    else{
        ante->next = aux ->next;   /* retira o jogo da sequencia da lista ligada */
    }
    if ( aux == (*tail_ord) ){     /* se o elemento que queremos apagar e a tail */
        (*tail_ord) = ante;        /* o bloco anterior ao que queremos apagar torna se a nova tail */
    }
    free(aux);                     /* liberta a memoria ocupada pelo bloco da lista uma vez que o resto ja foi libertado na funcao de apagar jogos da hash table */
}


/* guarda na lista das equipas uma equipa */
void guarda_lista_e(bloco_hash_equipa *head,equipa *e){ /* esta lista funciona como uma hash table so com uma linha */
    bloco_hash_equipa novo_e;                        /* bloco a adicionar */
    novo_e = malloc(sizeof(struct bloco_h_equipa));  /* guarda memoria para o bloco que vai guardar na hash table */
    novo_e->equipa = e;                             
    novo_e->next = head[0];                          /* insere o bloco pela head da lista ligada */
    head[0] = novo_e;                                /* guarda a equipa no bloco */  
}





/* guarda na lista ordenada das equipas uma equipa */
void guarda_ord_alfabetica(bloco_hash_equipa *lista, equipa *e){ /* esta lista funciona como uma hash table so com uma linha */
    bloco_hash_equipa novo_e,aux;                             /* bloco a adicionar e variavel para percorrer a lista*/
    novo_e = malloc(sizeof(struct bloco_h_equipa));           /* guarda memoria para o bloco que vai guardar na hash table */
    novo_e->equipa = e;                                       /* guarda a equipa no bloco */  
    if ((*lista) == NULL || strcmp((*lista)->equipa->nome,novo_e->equipa->nome) > 0){   /* se a head da lista estiver vazia ou o bloco a adicionar vir lexicograficamente antes da head*/
        novo_e->next = (*lista);                                                        /* guarda novo bloco como nova head */
        (*lista) = novo_e;
    }
    else{                       
        aux = (*lista);                                                           
        while (aux->next != NULL && strcmp(aux->next->equipa->nome,e->nome) < 0){      /* encontrar a posicao imediatamente antes a posicao do novo bloco */
            aux = aux->next;
        }
        novo_e->next = aux->next;                                                      /* colocar o bloco nessa posicao */
        aux->next = novo_e;
    }
}
