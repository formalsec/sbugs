#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "listasJG.h"

void freeNode_(Link_ link){
    freeJg(link->jogo);
    free(link);
}

Link_ inicializaLista_(){
    return NULL;
}

Link_ criaNode_(Jogo* jogo){
    Link_ node;
    node = (Link_)can_fail_malloc(sizeof(Node_));
    node->jogo = jogo;
    node->next = NULL;
    return node;
}

Link_ addJgLista(Link_ head,Jogo* jogo){
    if (head == NULL) {
        return criaNode_(jogo);
    }
    else{
        head->next = addJgLista(head->next,jogo);
        return head;
    }
}

Link_ apagaNode_(Link_ head,Jogo* jogo){
    Link_ link;
    Link_ _link;
    for (link = head, _link = NULL; link != NULL; _link = link, link = link->next){
        if (link->jogo == jogo) {
            if(link == head){
                head = link->next;
            }
            else{
                _link->next = link->next;
            }
            freeNode_(link);
            break;
        }
        
    }
    return head;
}

Link_ apagaNode_caso(Link_ head,Jogo* jogo){
    Link_ link;
    Link_ _link;
    for (link = head, _link = NULL; link != NULL; _link = link, link = link->next){
        if (link->jogo == jogo) {
            if(link == head){
                head = link->next;
            }
            else{
                _link->next = link->next;
            }
            free(link);
            break;
        }
        
    }
    return head;
}

Link_ limpaLista_(Link_ head){
    while (head != NULL){
        head = apagaNode_(head,head->jogo);
    }
    return NULL;
}


Link_ limpaLista_caso(Link_ head){
    while (head != NULL){
        head = apagaNode_caso(head,head->jogo);
    }
    return NULL;
}

Jogo* procuraJogo(Link_ head, char* nome){
    while (head != NULL){
        if(strcmp(head->jogo->nome,nome)==0){
            return head->jogo;
        }
        head = head->next;
    }
    return NULL;
}

Jogo* obtemElem(Link_ node){
    return node->jogo;
}