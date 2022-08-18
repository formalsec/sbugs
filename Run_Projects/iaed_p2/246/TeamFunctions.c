#include "structs.h"

/*##################################################################################################

Command_A inserts(if not already in) all the informaticion about a team in the hashtable
'htable_team'. If the team already exists there will be an error message if not the function acts
normally.

##################################################################################################*/
void command_A(link_team *htable_team, char *name, int NL_counter){
    int a = hash(name);
    link_team aux;
    if (lookup_team(htable_team, name) != NULL){
        printf("%d Equipa existente.\n", NL_counter);
    }
    else{
        aux = NEWteam(name);
        aux->next = htable_team[a];
        htable_team[a] = aux;
    }
}

/*##################################################################################################

Command_P Look for a team by the given name and if that team exists command_p prints all the
information about that team(name and number of victories) if not the function prints an error
message.

##################################################################################################*/
void command_P(link_team *htable_team, char * name, int NL_counter){
    link_team team = lookup_team(htable_team,name);
    if(team != NULL){
        printf("%d %s %d\n",NL_counter, team->name, team->v);
    }
    else{
        printf("%d Equipa inexistente.\n", NL_counter);
    }
    return;
}

/*##################################################################################################

Command_g receives as an argument the maximum number of victories and goes through the
hashtable_team in order to search for games with that number of victories. Whenever it finds a team 
with those wins the function adds the teams to a linked list where the teams will be added in 
lexicographical order so it prints correctly and finally frees the linked list so we can use it more
than one time.

##################################################################################################*/
void command_g(link_team *htable_team, int mostvictories, int NL_counter){
    int i;   
    link_team aux;
    link_Team_lexicographical_order list_betterTeams = NULL;
    for(i = 0; i < TableSize ; i++){
        aux = htable_team[i];
        for(; aux != NULL ; aux = aux->next){
            if(aux->v == mostvictories){
                /*finds the team with the same number of victories as the variable mostvictories*/
                list_betterTeams = insert_lexicographical_order(&list_betterTeams, aux);
            }
        }   /*at this point we have all teams with the higher win games in lexicographical order*/        
    }
    print_list_betterTeams(list_betterTeams, NL_counter);
    freebetterLIST(&list_betterTeams);
}