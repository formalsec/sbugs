#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "listasEQ.h"

void freeNode(Link link){
    freeEq(link->equipa);
    free(link);
}

Link inicializaLista(){
    return NULL;
}

Link criaNode(Equipa* equipa){
    Link node;
    node = (Link)can_fail_malloc(sizeof(Node));
    node->equipa = equipa;
    node->next = NULL;
    return node;
}

Link addEqLista(Link head,Equipa* equipa){
    if (head == NULL) {
        return criaNode(equipa);
    }
    else{
        head->next = addEqLista(head->next,equipa);
        return head;
    }
}

Link apagaNode(Link head,Equipa* equipa){
    Link link;
    Link _link;
    for (link = head, _link = NULL; link != NULL; _link = link, link = link->next){
        if (link->equipa == equipa) {
            if(link == head){
                head = link->next;
            }
            else{
                _link->next = link->next;
            }
            freeNode(link);
            break;
        }
        
    }
    return head;
}

Link limpaLista(Link head){
    while (head != NULL){
        head = apagaNode(head,head->equipa);
    }
    return NULL;
}

Equipa* procuraEquipa(Link head, char* nome){
    while (head != NULL){
        if(strcmp(head->equipa->nome,nome) == 0){
            return head->equipa;
        }
        head = head->next;
    }
    return NULL;
}