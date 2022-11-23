#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "list_equipa.h"

#include <stdio.h>


link_equipa list_equipa_init(Equipa* equipa){
        link_equipa x = can_fail_malloc(sizeof(struct node_equipa));
        x->equipa = can_fail_malloc(sizeof(Equipa)); 
        x->equipa->nome=equipa->nome;
        x->equipa->total_vitorias=equipa->total_vitorias;
        x->next = NULL;
        return x;
}

link_equipa list_equipa_insert_begin(link_equipa head, Equipa* equipa){
    link_equipa x = list_equipa_init(equipa);
    x->next = head;
    return x;
}

link_equipa list_equipa_insert_end(link_equipa head, Equipa* equipa) {
    link_equipa x;

    if(head == NULL){
        return list_equipa_init(equipa);
    }    
    x=head;    
    while(x->next != NULL){
        x=x->next;
    }
    x->next = list_equipa_init(equipa);
    return head;
}

link_equipa list_equipa_lookup(link_equipa head, Equipa* equipa) {
    link_equipa t;
    for(t = head; t != NULL; t = t->next){
        if(strcmp(t->equipa->nome, equipa->nome) == 0){ 
            return t;
        }
    }        
    return NULL;
}




void list_equipa_print(link_equipa head,int nl){
    link_equipa t;
    for(t = head; t != NULL; t = t->next){
        printf("%d * %s\n",nl, t->equipa->nome);
    } 
}


link_equipa list_equipa_delete(link_equipa head, Equipa* equipa){
    link_equipa t, prev;
    for(t = head, prev = NULL; t != NULL;prev = t, t = t->next){
        if(strcmp(t->equipa->nome, equipa->nome) == 0){
            if(t == head){
                head = t->next;
            }
            else{
                prev->next = t->next; 
            }
            free(t->equipa->nome);
            free(t->equipa);
            free(t);
            break;
        }
    }
    return head;
}

link_equipa list_equipa_insert_sorted(link_equipa head, Equipa* equipa) {
    link_equipa x;
    link_equipa new;
    int cmp1;
    int cmp2;

    if(head == NULL){
        return list_equipa_init(equipa);
    }    
    x=head;

    
    if(strcmp(x->equipa->nome,equipa->nome)>0){
       return list_equipa_insert_begin(head, equipa);
    }    
    while(x->next != NULL){
        cmp1=strcmp(x->equipa->nome, equipa->nome);
        cmp2=strcmp(x->next->equipa->nome, equipa->nome);
        if(cmp1<=0 && cmp2>=0){
            /*printf("cmp1: %d;cmp2: %d; atual: %s;next: %s; equipa: %s\n", cmp1,cmp2, x->equipa->nome, x->next->equipa->nome, equipa->nome);
            printf("inserir no\n");*/
            new=list_equipa_init(equipa);
            /*printf("new: %p\n",(void*) new);
            printf("next: %p\n",(void*) x->next);
            printf("new next: %p\n",(void*) new->next);
            */
            new->next=x->next;
            /*printf("new next: %p\n",(void*) new->next);*/
            x->next=new;
            /*printf("next: %p\n",(void*) x->next);*/
            return head;
        }

        x=x->next;
    }
    x->next = list_equipa_init(equipa);
    return head;
}
