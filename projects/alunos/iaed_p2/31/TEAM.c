#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "TEAM.h"


/* Auxiliar functions of teams. */


/* Creates a system of team. */
team ** init_team(team ** team_hash){
    int i = 0;

    team_hash = can_fail_malloc(sizeof(team*) * HASH_SIZE);

    for(; i < HASH_SIZE; i++)
        team_hash[i] = NULL;

    return team_hash;
}


/* Function hash that returns a number of position/index. */
int hash(char * name){
    if(!name)
        return -1;
    
    return name[0]%HASH_SIZE;
}


/* Creates a new team. */
team * create_team(char * name){
    team * t = can_fail_malloc(sizeof(team));

    t -> name = can_fail_malloc(sizeof(char) * (strlen(name)+1));
    t -> vitories = 0;
    t -> next = NULL;
    strcpy(t->name, name);

    return t;
}


/* Inserts the team at the beginning of the list of teams. */
team * push_team(char * name, team * last){
    team * first = create_team(name);
    first->next = last;

    return first;
}


/* Removes the first element of the Team list and returns the new head.*/
team * pop_team(team * head){
    team * next;

    if(!head) 
        return NULL;
    
    next = head ->next;
    free(head->name);
    free(head);

    return next;
}


/* Destroy the teams index. */
team * destroy_index_team(team * team_index){
    for(; team_index;)
        team_index = pop_team(team_index);

    return NULL;
}


/* Frees all memory associated with the teams system. */
team ** destroy_full_team(team ** team_hash){
    int i;

    for(i = 0; i < HASH_SIZE; i++){
        team_hash[i] = destroy_index_team(team_hash[i]);   
    }

    free(team_hash);
    
    return NULL;
}

 
/* Adds new team as the last element of the lists index. */
void list_put_team(team ** team_hash, char * name, int NL){
    int index = hash(name);
    team *aux;

    if(!team_hash[index]){
        team_hash[index] = create_team(name);
        return;
    }
    
    aux = team_hash[index];
        
    for(; aux; aux = aux->next){
        if(!strcmp(aux->name, name)){
            printf("%d Equipa existente.\n", NL);
            return;
        }
        if(!aux->next) break;
    }

    aux -> next = create_team(name);      
    return;  
}


/* Gets the team in the team system. */
team * get_team(team ** team_hash, char * name){
    team * get = team_hash[hash(name)];

    for(; get; get = get->next){
        if(!strcmp(get->name, name)) 
            break;
    }

    return get;
}


/* Adds a new team in the teams list on lexicographic order.  */
team * add_order_team(team * order_team, char * name){
    team * new = order_team, *aux = NULL;

    if(!new){
        new = create_team(name);
        return new;
    } 

    if(strcmp(name, new->name) < 0){
        new = push_team(name,new);
        return new;
    }

    aux = new;
    new = new-> next;

    for(; new; new = new->next, aux = aux->next){
        if(strcmp(name, new->name) < 0){
            new = push_team(name, new);
            aux->next = new;
            return order_team;
        }
    }
    
    aux -> next = create_team(name);
    
    return order_team;
}