#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Binary_G2.h"

/* Returns NULL, the initial value of the head */
BGlink BGinit(){
    return NULL;
}

/* Allocs memory for a Tree Node. Returns a pointer to the Node */
BGlink BGnew(Game game){
    BGlink new = (BGlink) can_fail_malloc(sizeof(struct BGnode));
    new->game = game;
    new->l = NULL;
    new->r = NULL;
    return new;
}

/* Returns the item with the maximum value in the Tree */
BGlink BGmax(BGlink link){
    if (link == NULL || link->r == NULL)
        return link;
    else
        return BGmax(link->r);
}

/* Insert the game into the Tree acording to less */
BGlink BGinsert(BGlink link, Game game){
    if (link == NULL)
        return BGnew(game);
    if (less(key(game), key(BGgetgame(link))))
        link->l = BGinsert(link->l, game);
    else
        link->r = BGinsert(link->r, game);
    return link;
}

/* Returns the Game associated with name in the tree */
Game BGsearch(BGlink link, char *name){
    if (link == NULL)
        return NULL;
    if (eq(key(BGgetgame(link)), name))
        return BGgetgame(link);
    if (less(name, key(BGgetgame(link))))
        return BGsearch(link->l, name);
    else
        return BGsearch(link->r, name);
}

/* Deletes the game from the Tree */
BGlink BGdelete(BGlink link, Game game){
    BGlink aux;
    Game game_aux;
    if (link == NULL)
        return link;
    else if (less(key(game), key(BGgetgame(link))))
        link->l = BGdelete(link->l, game);
    else if (less(key(BGgetgame(link)), key(game)))
        link->r = BGdelete(link->r, game);
    else{
        if (link->l != NULL && link->r != NULL){
            aux = BGmax(link->l);
            game_aux = BGgetgame(link);
            link->game = BGgetgame(aux);
            aux->game = game_aux;
            link->l = BGdelete(link->l, BGgetgame(aux));
        }
        else{
            aux = link;
            if (link->l == NULL && link->r == NULL)
                link = NULL;
            else if (link->l == NULL)
                link = link->r;
            else
                link = link->l;
            free(aux);
        }
    }
    return link;
}

/* Traverses the tree adding to game all games. Returns number of games added */
int Traverse(BGlink link, Game *game, int i){
    if (link == NULL)
        /* End of branch */
        return i;
    /* Add game */
    game[i] = BGgetgame(link);
    i++;
    i = Traverse(link->l, game, i);
    i = Traverse(link->r, game, i);
    return i;
}


/* Returns the game in the pointer link */
Game BGgetgame(BGlink link){
    return link->game;
}