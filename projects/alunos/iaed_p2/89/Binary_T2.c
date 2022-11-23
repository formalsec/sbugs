#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Binary_T2.h"

/* Returns NULL, the initial value of the head */
BTlink BTinit(){
    return NULL;
}

/* Allocs memory for a Tree Node. Returns a pointer to the Node */
BTlink BTnew(Team team){
    BTlink new = (BTlink) can_fail_malloc(sizeof(struct BTnode));
    new->team = team;
    new->l = NULL;
    new->r = NULL;
    return new;
}

/* Returns the item with the maximum value in the Tree */
BTlink BTmax(BTlink link){
    if (link == NULL || link->r == NULL)
        return link;
    else
        return BTmax(link->r);
}

/* Insert the team into the Tree acording to less */
BTlink BTinsert(BTlink link, Team team){
    if (link == NULL)
        return BTnew(team);
    if (less(key(team), key(BTgetteam(link))))
        link->l = BTinsert(link->l, team);
    else
        link->r = BTinsert(link->r, team);
    return link;
}

/* Returns the Team associated with name in the tree */
Team BTsearch(BTlink link, char *name){
    if (link == NULL)
        return NULL;
    if (eq(key(BTgetteam(link)), name))
        return BTgetteam(link);
    if (less(name, key(BTgetteam(link))))
        return BTsearch(link->l, name);
    else
        return BTsearch(link->r, name);
}

/* Deletes the team from the Tree */
BTlink BTdelete(BTlink link, Team team){
    BTlink aux;
    Team team_aux;
    if (link == NULL)
        return link;
    else if (less(key(team), key(BTgetteam(link))))
        link->l = BTdelete(link->l, team);
    else if (less(key(BTgetteam(link)), key(team)))
        link->r = BTdelete(link->r, team);
    else{
        if (link->l != NULL && link->r != NULL){
            aux = BTmax(link->l);
            team_aux = BTgetteam(link);
            link->team = BTgetteam(aux);
            aux->team = team_aux;
            link->l = BTdelete(link->l, BTgetteam(aux));
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

/* Traverses the tree adding to a list the teams with maximum wins. Returns number of teams added */
int Ttraverse(BTlink link, LTlink *head, int i){
    if (link == NULL)
        return i;
    if (*head != NULL){
        if (Tgetwins(BTgetteam(link)) == Tgetwins(LTgetteam(*head))){
            /* Teams with the same number of wins */
            *head = LTinsert(*head, BTgetteam(link)); 
            i++;
        }
        else if (Tgetwins(BTgetteam(link)) > Tgetwins(LTgetteam(*head))){
            /* New team with most wins */
            *head = LTclear(*head);
            *head = LTinsert(*head, BTgetteam(link));
            i = 1;
        }
    }
    else{
        /* Empty list */
        *head = LTinsert(*head, BTgetteam(link));
        i++;
    }
    i = Ttraverse(link->l, head, i);
    i = Ttraverse(link->r, head, i);
    return i;
}

/* Returns the team in the pointer link */
Team BTgetteam(BTlink link){
    return link->team;
}