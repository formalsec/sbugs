#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "arvore.h"

struct _nodetree{
    ItemT item;
    nodetree *l;
    nodetree *r;

};


nodetree* cria_nodetree(ItemT item){
    nodetree* new;
    new = (nodetree*)can_fail_malloc(sizeof(nodetree));
    new->item = item;
    new->l = new->r = NULL;

    return new;

}

nodetree* insere_tree(nodetree* nt, ItemT item) { 
    /*se node for NULL, cria*/
    if (nt == NULL){

        return cria_nodetree(item);

    } 
    /*se item a inserir for menor do que o item existente, adicionar a esquerda*/
    if (strcmp(item, nt->item)<0){
        nt->l = insere_tree(nt->l, item);
    }
    else{
    /*se item a inserir for maior do que o item existente, adicionar a direita*/
        nt->r = insere_tree(nt->r, item);
    }
         
    return nt;
}

nodetree* nodetree_left(nodetree* nt){
    return nt->l;
}

nodetree* nodetree_right(nodetree* nt){
    return nt->r;
}

ItemT nodetree_item(nodetree* nt){
    return nt->item;
}
