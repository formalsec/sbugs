#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Item.h"


Item newItem( Type t, void *data)
{
    Item x = (Item)can_fail_malloc(sizeof(struct Item));
    if (t == JOGO)
    {
        x->data.jogo = (struct Jogo *)data;
        x->value = ((struct Jogo *)data)->nome;
    }
    else
    {
        x->data.equipa = data;
        x->value = ((struct Equipa *)data)->nome;
    }
    x->type = t;
    return x;
}

void deleteItem(Item i)
{
    if (i)
    {
        if (i->type == JOGO){

            free(i->data.jogo->equipa1);
            free(i->data.jogo->equipa2);
            free(i->data.jogo);
        }
            
        else{
            free(i->data.equipa);
        }
    }
    free(i->value);
    free(i);
}


