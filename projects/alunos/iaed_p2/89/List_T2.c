#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "List_T2.h"


/* Returns NULL, the initial value of the head */
LTlink LTinit(){
    return NULL;
}

/* Allocs memory for a List Node. Returns a pointer to the Node */
LTlink LTnew(Team team){
    LTlink new = (LTlink) can_fail_malloc(sizeof(struct LTnode));
    new->team = team;
    new->next = NULL;
    return new;
}

/* Insert the team into the List acording to LTless. Returns new head */
LTlink LTinsert(LTlink LThead, Team team){
    LTlink x, prev;
    if (LThead == NULL){
        /* List is empty */
        x = LTnew(team);
        return x;
    }
    else{
        /* Not empty */
        /* Find the right place */
        for(x = LThead, prev = NULL; x != NULL && Tless(team, LTgetteam(x)); prev = x, x = x->next);
        if(x == LThead){
            /* First position */
            x = LTnew(team);
            x->next = LThead;
            return x;
        }
        else{
            x = LTnew(team);
            x->next = prev->next;
            prev->next = x;
        }
    }
    return LThead;
}

/* Deletes the team from the List. Returns new head */
LTlink LTdelete(LTlink LThead, Team team){
    LTlink x, prev;
    /* Find Node */
    for(x = LThead, prev = NULL; x != NULL; prev = x, x = x->next){
        if (eq(Tgetname(team), Tgetname(LTgetteam(x)))){
            if (x == LThead){
                /* First position */
                LThead = x->next;
            }
            else
                prev->next = x->next;
            free(x);
            break;
        }
    }
    return LThead;
}

/* Frees all nodes from the List. Returns NULL*/
LTlink LTclear(LTlink LThead){
    Team team;
    while(LThead != NULL){
        team = LTgetteam(LThead);
        LThead = LTdelete(LThead, team);
    }
    return NULL;
}


/* Prints the first members, the ones with the most wins */
void LTprint(LTlink LThead, int NL){
    LTlink x;
    int max;
    if(LThead != NULL){
        x = LThead;
        max = Tgetwins(LTgetteam(x));
        printf("%d Melhores %d\n", NL, max);
        for(;x != NULL && Tgetwins(LTgetteam(x)) == max ; x = x->next)
            printf("%d * %s\n", NL, Tgetname(LTgetteam(x)));
    }
}

/* Returns the team */
Team LTgetteam(LTlink link){
    return link->team;
}