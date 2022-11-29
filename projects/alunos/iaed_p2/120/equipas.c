#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipas.h"



/*Hash Funtion for the hash tables of gams and teams*/
int hash(char *v, int mod)
{
int h = 0, a = 127;
for (; *v != '\0'; v++)
h = (a*h + *v) % mod;
return h;
}

/*Function that initializes the hash table of team by making each head
  of the hash table NULL*/
void init_hash_teams(NodeTeam **heads,int mod)
{
    int i;
    for(i = 0; i < mod; i++){
        heads[i] = NULL;
    }
}

/*Function that creates a game, recieving its name and returning the new team*/
Team * create_team(char *nameT)
{
    Team *newTeam;
    char *nameTeam;
    
    /*Allocation of memory for the name of the team and the team*/
    nameTeam = str_dup(nameT);
    newTeam = (Team*) can_fail_malloc(sizeof(Team));
    
    newTeam->name = nameTeam;
    newTeam->victories = 0;
    
    return newTeam;
}

/*Function that inserts in the hash table of teams a new team*/
void hash_insert_team(NodeTeam **heads,Team *team, int mod)
{
    /*searching for the hash key of the name of the game*/
    int key = hash(team->name,mod);

    heads[key] = hash_put_begin_teams(heads[key], team);
}

/*Function that recieves the heads of the hash table of teams and
  game and adds it to the beginning of the list of its respective
  hash key,returning the altere hash table*/
NodeTeam * hash_put_begin_teams(NodeTeam *head,Team *team)
{
    NodeTeam *newHead = (NodeTeam*) can_fail_malloc(sizeof(NodeTeam));

    newHead->team = team;
    newHead->next = head;
    return newHead;
}

/*Function that recieves the heads of the hash table of teams and
  the name of a team and the module used for the hash table, and
  it returns the team to which the name of the team corresponds*/
Team * hash_search_team(NodeTeam **heads,char *name,int mod)
{
    int key = hash(name, mod);
    return search_team(heads[key],name);
}

/*Function that iterates through the several lists that constitute
  the hash table in search of the team to which the name given
  corresponds*/
Team * search_team(NodeTeam *head, char *name)
{
    NodeTeam *current = head;
    char *currentName;
    
    /*Cycle that will iterate through the list to find the team 
      to which the name of the game corresponds*/
    while(current != NULL){
        currentName = current->team->name;
        if(strcmp(currentName,name) == 0){
            
            return current->team;
        }
        current = current->next;
    }
    return NULL;
}

/*Function that recieves the heads of the lists that constitute
  the hash table of teams and the module used for it, and it 
  deletes the hash table from the database*/
void destroy_hash_teams(NodeTeam **heads,int mod)
{
    int i;
    for(i = 0; i < mod; i++){
        destroy_list_teams(heads[i]);
    }
}

/*Function that recieves an head of a list from the hash table
  of teams and it deletes the list from the hash table*/
void destroy_list_teams(NodeTeam *head)
{
    NodeTeam  *aux;

    while((aux = head) != NULL){
        head = head->next;
        
        free_team(aux->team);
        free(aux);
    }

    head = NULL;
}

/*Function that recieves a team and removes it from the database
  by freeing the memory alloctated for it*/
void free_team(Team *e)
{
    free(e->name);
    free(e);
}


/*Function that works identically to 'strdup', 
  as it allocates de memory of the string recieved and
  return the new dinamically allocated string*/
 char* str_dup(char *string)
{
    char *duplicatedString;
    
    /*Allocation of memory for the duplicated string*/
    duplicatedString = (char*) can_fail_malloc((strlen(string) + 1));
    
    strcpy(duplicatedString, string);

    return duplicatedString;
}
