#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "teams.h"

/*
* Description: creates a team based on input.
*/
team create_team(){

    team new_team;
    /*array for the team name*/
    char name[MAX_CHAR];

    scanf(" %[^:\n]", name);

    /*allocates the necessary memory for the name and saves it in the team*/
    new_team.name = can_fail_malloc((strlen(name)+1)*sizeof(char));
    strcpy(new_team.name, name);

    /*set the wins of the team to 0*/
    new_team.games_won = 0;

    return new_team;
}


/*
* Description: frees the memory alloc'd to a team.
*/
void destroy_team(team t){
    free(t.name);
}


/*
* Description: creates a team node with the given name and the pointers to NULL.
*/
node_teams create_node_team(team new_team){
    
    node_teams node_new_team;

    node_new_team.t = new_team;
    node_new_team.next = NULL;
    node_new_team.next_in_hash_table = NULL;
    node_new_team.prev = NULL;
    node_new_team.prev_in_hash_table = NULL;

    return node_new_team;
}


/*
* Description: pushes the new team to the list of teams.
*/
node_teams * push_team(node_teams * head, team t){

    /*creates a pointer to a node and allocates memory for a team node*/
    node_teams *new = can_fail_malloc(sizeof(node_teams));
    /*atributes the team to the node*/
    new->t = t;
    /*sets the next node in the list to NULL*/
    new->next = NULL;

    /*if the list is empty*/
    if (head == NULL){
        /*sets the previous node to NULL and the head of the list to the new*/
        new->prev = NULL;
        head = new;
        return head;
    }

    /*sets the next node of the head to the new*/
    head->next = new;
    /*and the previous of the new to the head*/
    new->prev = head;

    return new;
}


/*
* Description: frees all memory alloc'd to the team node.
*/
void free_team(node_teams *team){
    free(team->t.name);
    free(team);
}


/*
* Description: frees all memory alloc'd to the list of games.
*/
node_teams * destroy_teams(node_teams * head){

    node_teams *tmp;
    /*goes through the list and frees the memory alloc'd to the team and node*/
    while (head != NULL){
        tmp = head->prev;
        free_team(head);
        head = tmp;
    }
    return NULL;
}

node_teams * find_team(node_teams **teams_table){

    team t;
    node_teams node_t;
    node_teams *p_node_t;
    node_teams *head_t;
    char name[MAX_CHAR];

    /*gets the name of the team and saves it in the team to search*/
    scanf(" %[^:\n]", name);
    t.name = can_fail_malloc((strlen(name)+1)*sizeof(char));
    strcpy(t.name,name);

    /*creates a node with the team to search and a pointer to that node*/
    node_t = create_node_team(t);
    p_node_t = &node_t;

    /*finds the node that contains the team to search*/
    head_t = in_table_teams(teams_table, p_node_t);

    /*frees the temporary team to search*/
    destroy_team(t);

    return head_t;
}


/*
* Description: gets the name of the team.
*/
char * get_team_name(node_teams *team){
    return team->t.name;
}


/*
* Description: gets the previous node of the teams list.
*/
node_teams * get_prev_team(node_teams *team){
    return team->prev;
}


/*
* Description: gets the number of games won by the team.
*/
int get_wins(node_teams *team){
    return team->t.games_won;
}


/*
* Description: gives a win to the team.
*/
void give_win(node_teams *team){
    team->t.games_won++;
}


/*
* Description: takes a win from the team.
*/
void take_win(node_teams *team){
    team->t.games_won--;
}


/*
* Description: auxiliar function used in qsort that compares strings.
*/
int compare_names(const void *team1, const void *team2){
    return strcmp(get_team_name(*(node_teams **)team1), 
                get_team_name(*(node_teams **)team2));
}