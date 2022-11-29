#define TABLE_SIZE 1051
#define MAX_JOGO_EQUIPA 1024

/******************************************************
*----------------------STRUCTURES---------------------*
******************************************************/

typedef struct L_T {
	char *name; /*pointer to team name*/
	int victories; /*number of victories for this team*/
	struct L_T *next; /*in case of collision, next is a 
	pointer to the next team inserted in the same entry
	of the hash table*/
} list_teams;

typedef struct HT_T{
	int size; /*size of the table*/
	list_teams **table; /*the table elements*/
} hash_table_teams;

typedef struct L_N{
	char *team_name; /*pointer to team name*/
	struct L_N *next;
}list_names; 

/******************************************************
*-------------------AUXILIAR FUNCTIONS----------------*
*-------------------------teams-----------------------*
*-----------------------PROTOTYPES--------------------*
******************************************************/

hash_table_teams *create_ht_team(int size);
int hash_teams(hash_table_teams *team_ht, char *v);
void insertBegin_teams(hash_table_teams *team_ht, char *v);
list_teams *search_team_aux(hash_table_teams *team_ht, char *v);
int compare_names(list_names *y, list_names *z);
list_names *insert_name_list(list_names *lst_name, char *name);
void print_list_names(list_names *head_lst_names, int NL);