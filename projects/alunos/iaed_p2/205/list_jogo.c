#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "list_jogo.h"
#include <stdio.h>


link_jogo list_jogo_init(Jogo* jogo){
        link_jogo x = can_fail_malloc(sizeof(struct node_jogo));
        x->jogo = can_fail_malloc(sizeof(Jogo)); 
        x->jogo->nome=jogo->nome;
        x->jogo->equipa1=jogo->equipa1;
        x->jogo->equipa2=jogo->equipa2;
        x->jogo->score1=jogo->score1;
        x->jogo->score2=jogo->score2;
        x->next = NULL;
        return x;
}

link_jogo list_jogo_insert_begin(link_jogo head, Jogo* jogo){
    link_jogo x = list_jogo_init(jogo);
    x->next = head;
    return x;
}

link_jogo list_jogo_insert_end(link_jogo head, Jogo* jogo) {
    link_jogo x;
    if(head == NULL){
        return list_jogo_init(jogo);
    }    
    x=head;    
    while(x->next != NULL){
        x=x->next;
    }
    x->next = list_jogo_init(jogo);
    return head;
}

link_jogo list_jogo_lookup(link_jogo head, Jogo* jogo) {
    link_jogo t;

    for(t = head; t != NULL; t = t->next){
        if(strcmp(t->jogo->nome, jogo->nome) == 0){
            return t;
        }

    }
       
    return NULL;
}




void list_jogo_print(link_jogo head, int nl){
    link_jogo t;
    for(t = head; t != NULL; t = t->next){
        printf("%d %s %s %s %i %i\n", nl, t->jogo->nome, t->jogo->equipa1, t->jogo->equipa2, t->jogo->score1, t->jogo->score2);
    } 
}


link_jogo list_jogo_delete(link_jogo head, Jogo* jogo){
    link_jogo t, prev;
    for(t = head, prev = NULL; t != NULL;prev = t, t = t->next){
        if(strcmp(t->jogo->nome, jogo->nome) == 0){
            if(t == head){
                head = t->next;
            }
            else{
                prev->next = t->next; 
            }
            free(t->jogo->nome);
            free(t->jogo->equipa1);
            free(t->jogo->equipa2);
            free(t->jogo);
            free(t);
            break;
        }
    }
    return head;
}                      
