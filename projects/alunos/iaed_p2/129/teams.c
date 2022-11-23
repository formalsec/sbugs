#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "teams.h"

/*
* team_table * init_teams()
*   
*   Initializes the structure to store the teams
*   
*   Output: team_table*         -> pointer for team storing structure
*/
team_table * init_teams(){
    int i;

    team_table *teams = can_fail_malloc(sizeof(team_table));

    for(i = 0; i < TEAM_TABLE_SLOTS; i++){
        teams->table[i] = NULL;
    }

    teams->len_top_winners = LEN_TOP_WINNERS_INIT;
    teams->top_winners_names = can_fail_malloc(LEN_TOP_WINNERS_INIT * sizeof(char*));
    
    return teams;
}

/*
* int hash_team(char *name)
*   
*   determines the posiotion in the hash table for the team 
*   
*   Input: char *name           -> teams name 
*
*   Output: int                 -> pos in the hash table
*/
int hash_team(char *name){
    int key, i;

    for(key = 0, i = 0; name[i] != '\0'; i++){
        key += (MAX_TEAM_NAME_LEN - i) * name[i];
    }
    key = key % TEAM_TABLE_SLOTS;

    return key;
}

/*
* void push_team(team_table *teams, team *team)
*   
*   Stores a team in the table 
*   
*   Input: team_table *teams    -> teams structure pointer
*          team *team           -> team pointer
*/
void push_team(team_table *teams, team *team){
    int key;
    team_node *taken_node;

    team_node *new_node = can_fail_malloc(sizeof(team_node));
    key = hash_team(team->name);
    
    new_node->team = team;
    new_node->next_node = NULL;

    if(teams->table[key] == NULL){
        teams->table[key] = new_node;
        new_node->previous_node = NULL;
    
    }else{
        taken_node = teams->table[key]; 
        while(taken_node->next_node != NULL){
            taken_node = taken_node->next_node;
        }
        taken_node->next_node = new_node;
        new_node->previous_node = taken_node;
    }
}

/*
* void new_team(team_table *teams, char *name)
*   
*   Creates a new team and stores it
*   
*   Input: team_table *teams    -> teams structure pointer
*          char *name           -> new teams name
*/
void new_team(team_table *teams, char *name){
    team *new_team = can_fail_malloc(sizeof(team));
    new_team->name = name;
    new_team->won_games = 0;

    push_team(teams, new_team);
    update_team_wins(new_team, 0);
}

/*
* team * get_team(team_table *teams, char *name)
*   
*   Obtains the pointer for the team with the given name
*   
*   Input: team_table *teams    -> teams structure pointer
*          char *name           -> team name
*
*   Output: team *              -> pointer for the team or NULL if dont exist
*/
team * get_team(team_table *teams, char *name){
    int key;
    team_node *node;

    key = hash_team(name);
    node = teams->table[key];

    while(node != NULL){
        if(!(strcmp(node->team->name, name))){
            return node->team;
        }

        node = node->next_node;
    }

    return NULL;
}

/*
* char * get_team_name(team *team)
*   
*   Obtains the name for the given team 
*   
*   Input: team *team           -> team pointer
*
*   Output: char *              -> teams name
*/
char * get_team_name(team *team){
    return team->name;
}

/*
* int same_team(team *team_1, team *team_2)
*   
*   Checks if the teams are the same
*   
*   Input: team *team_1         -> 1st team pointer
*          team *team_2         -> 2st team pointer  
*
*   Output: int                 -> 1 if teams are the same, 0 if not
*/
int same_team(team *team_1, team *team_2){
    if(!(strcmp(team_1->name, team_2->name))){
        return 1;
    }
    
    return 0;
}

/*
* void update_team_wins(team *team, int value)
*   
*   Updates the number of wins for a given team adding the given value 
*   
*   Input: team *team           -> team pointer
*          int value            -> variation of wins
*/
void update_team_wins(team *team, int value){
    team->won_games += value; 
}

/*
* void print_team(team *team)
*   
*   Prints team info "<name> <no won games>\n" 
*   
*   Input: team *team           -> team pointer
*/
void print_team(team *team){
    printf("%s %d\n", 
        team->name, 
        team->won_games);
}

/*
* char ** get_top_winners_names(team_table *teams)
*   
*   Gets a list with the names of the top winner NULL in last position
*   
*   Input: team_table *teams    -> teams structure pointer
*
*   Output: char **             -> winner names list
*/
char ** get_top_winners_names(team_table *teams){
    int i, no_top_winners = 0, max_no_wins = 0;
    team_node *node;

    for(i = 0; i < TEAM_TABLE_SLOTS; i++){
        if ((node = teams->table[i]) != NULL){
            while(node != NULL){
                if(node->team->won_games == max_no_wins){
                    /* if vector is too small size is increased*/
                    if(++no_top_winners >= teams->len_top_winners){
                        teams->len_top_winners += LEN_TOP_WINNERS_INIT;
                        teams->top_winners_names = 
                            can_fail_realloc(teams->top_winners_names,
                            teams->len_top_winners * sizeof(char*));
                    }

                    teams->top_winners_names[no_top_winners - 1] = 
                    node->team->name;

                }else if(node->team->won_games > max_no_wins){
                    no_top_winners = 1;
                    max_no_wins = node->team->won_games;
                    teams->top_winners_names[0] = node->team->name;
                }
            
            node = node->next_node;
            }
        }
    }

    teams->top_winners_names[no_top_winners] = NULL;
    teams->max_no_wins = max_no_wins;

    qsort(teams->top_winners_names, no_top_winners, sizeof(char*), 
    compare_names);

    return teams->top_winners_names;
}

/*
* int compare_names(const void *pointer_1, const void *pointer_2)
*   
*   Name comparator for qsort
*   
*   Input: const void *pointer_1-> pointer for element 1
*          const void *pointer_2-> pointer for element 2
*   
*
*   Output: int                 -> <0 1 goes before 2, 0 are the same, >0 1 
*                                    goes after 2
*/
int compare_names(const void *pointer_1, const void *pointer_2){
    const char* name_1 = *(const char**) pointer_1;
    const char* name_2 = *(const char**) pointer_2;

    return strcmp(name_1, name_2);
}

/*
* int get_max_win_number(team_table *teams)
*   
*   Gets the maximum number off wins for any team accurate afer the use of 
*   get_top_winners_names
*   
*   Input: team_table *teams    -> teams structure pointer
*
*   Output: int                 -> number of max wins
*/
int get_max_win_number(team_table *teams){
    return teams->max_no_wins;
}

/*
* void free_teams(team_table *teams)
*   
*   Frees all team related structures
*   
*   Input: team_table *teams    -> teams structure pointer
*/
void free_teams(team_table *teams){
    int i;
    team_node *node, *tmp;
    
    for(i = 0; i < TEAM_TABLE_SLOTS; i++){
        if (teams->table[i] != NULL){
            node = teams->table[i];
            while(node != NULL){
                free(node->team->name);
                free(node->team);
                tmp = node->next_node;
                free(node);
                node = tmp;
            }
        }
    }
    
    free(teams->top_winners_names);
    free(teams);
}