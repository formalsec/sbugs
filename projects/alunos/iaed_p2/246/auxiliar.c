#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "structs.h"

/*##################################################################################################

hash returns an integer depending on the char received as an argument. The integer that will be
returned will be used to indicate the hashtable index where the information is or will be.

##################################################################################################*/
int hash(char *nome){
    int i, a = 31415, b = 27183, t = TableSize;
    
    for (i = 0;  *nome != '\0'; nome++, a = a*b % (t-1))
        i = (a*i + *nome) % t;
    return i;
}

/*##################################################################################################

init functions will can_fail_malloc space for my hashtables(both game and team) depending on the 'TableSize' 
defined on structs.h . These functions will also set every index of the hashtables to NULL.

##################################################################################################*/
link_game* init_j(){
    int i;
    link_game *heads = can_fail_malloc(TableSize*sizeof(struct game));

    for(i = 0; i < TableSize; i++){
         heads[i] = NULL;                    /*starts each index at NULL*/
    }
    return heads;
}

link_team* init_t(){
    int i;
    link_team *heads = can_fail_malloc(TableSize*sizeof(struct team));

    for(i = 0; i < TableSize; i++){
         heads[i] = NULL;                   /*starts each index at NULL*/  
    }
    return heads;
}


/*##################################################################################################

Both NEWgame and NEWteam will can_fail_malloc space to the information needed, put the information on the 
right spots and point the next pointer to NULL.  

##################################################################################################*/
link_game NEWgame(char *name, link_team t1, link_team t2, int r1, int r2){
    link_game x = can_fail_malloc(sizeof(struct game));
    x->name =  can_fail_malloc(sizeof(char)*(strlen(name)+1));
    strcpy(x->name, name);
    x->element_t1 = t1;
    x->element_t2 = t2;
    x->r1 = r1;
    x->r2 = r2;
    x->next = NULL;
    return x;
}   

link_team NEWteam(char *name){
    link_team x = can_fail_malloc(sizeof(struct team));
    x->name =  can_fail_malloc(sizeof(char)*(strlen(name)+1));
    strcpy(x->name, name);
    x->v = 0;
    x->next = NULL;
    return x;
}


/*##################################################################################################

insertBegin will can_fail_malloc space for the necessary information and insert that node at the beginning
of the linked list.

##################################################################################################*/
link_game_order insertBegin(link_game_order head, link_game game){
    link_game_order x;
    if(head == NULL){
        x = can_fail_malloc(sizeof(struct order_game));
        x->element = game;
        x->next = NULL;
        return x;
    }
    else{
        x = can_fail_malloc(sizeof(struct order_game));
        x->element = game;
        x->next = head;
        head = x;
        return head;  
    }
    return head;
}


/*##################################################################################################

Both lookup functions will look up for a team or a game on the hash tables. If that team/game really 
exists this function returns the node were the informaticion is if not it returns NULL

##################################################################################################*/
link_game lookup_game(link_game *htable_game, char *nome){
    int a = hash(nome);

    link_game aux = htable_game[a];
    for(;aux != NULL; aux = aux->next){
        if(strcmp(aux->name, nome) == 0){
            /*the game was found*/
            return aux;
        }
    }
    return NULL; 
}

link_team lookup_team(link_team *htable_team, char *nome){
    int a = hash(nome);

    link_team aux = htable_team[a];
    for(;aux != NULL; aux = aux->next){
        if(strcmp(aux->name, nome) == 0){ 
            /*the team was found*/
            return aux;
        }
    }
    return NULL;
}

/*##################################################################################################

print_list_betterTeams receives an lexicographical ordered linked list and prints out all the
iformation contained in the list.

##################################################################################################*/
void print_list_betterTeams(link_Team_lexicographical_order list_betterTeams, int NL_counter){
    link_Team_lexicographical_order aux;
    for (aux = list_betterTeams; aux != NULL ; aux = aux->next){
        printf("%d * %s\n", NL_counter, aux->elemente->name);
    }
}


/*##################################################################################################

deletegame deletes a node containing the information about a game from a certain index of the hash 
table and correctly indicates the pointers on that index that were affected by the elimination of
the node. 

##################################################################################################*/
link_game deletegame(link_game head, char *name){
    link_game aux, prev;
    for(aux = head, prev = NULL; aux != NULL; prev = aux, aux = aux->next){
        if(strcmp(aux->name, name) == 0){
            /*the game was found*/
            if(aux == head){
                head = aux->next;
            }
            else{
                prev->next = aux->next;
            }
            freeGame(aux);
            return head;
        }
    }
    return head;
}

/*##################################################################################################

Lookup_BiggerNumVictories goes through all the hash table team and returns the higher number of
wins.

##################################################################################################*/
int Lookup_BiggerNumVictories(link_team *head){
    link_team aux;
    int i, Vcounter = -1;
    for (i = 0; i < TableSize; i++){
        aux = head[i];
        for (; aux !=NULL; aux = aux->next){
            if(aux->v > Vcounter){
                /*if the number of victories is higher that the one in Vcounter, Vcounter will be
                equal to the new higher number of victories*/
                Vcounter = aux->v;
            }
        }  
    }
    return Vcounter;
}

/*##################################################################################################

insert_lexicographical_order will add a new node to a linked list in lexographic order. Each node
that enters the function will go through the entire list until it finds the place where it will be
placed. The place where this node is placed is determined by comparing that name associated to that 
node with the nodes that are already in the linked list.

##################################################################################################*/
link_Team_lexicographical_order insert_lexicographical_order(link_Team_lexicographical_order *head, 
link_team target){
    link_Team_lexicographical_order aux; 
    link_Team_lexicographical_order x;
    x = can_fail_malloc(sizeof(struct Team_lexicographical_order));
    x->elemente = target;
    x->next = NULL;
    if (*head == NULL ) { 
        x->next = *head; 
        return x; 
    }
    if (strcmp((*head)->elemente->name, target->name) > 0) { 
        x->next = *head; /*if the new element is the lower one that new element turns the head*/
        return x; 
    }  
    else{ 
        aux = *head; 
        /*this while either searches for the last element on the linked list or searches for a 
        correct place of lexographic insertion by comparing the team names*/
        while (aux->next!=NULL && strcmp(aux->next->elemente->name, x->elemente->name) < 0){ 
            aux = aux->next; 
        } 
        x->next = aux->next; 
        aux->next = x;
        return *head; 
    } 
}