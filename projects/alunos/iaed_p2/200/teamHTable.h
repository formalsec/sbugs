#ifndef TEAMHTABLE_H
#define TEAMHTABLE_H
#define MAX 1024/*maximo 1023 caracteres*/
#define SIZE 9677/*numero primo - tamanho da hashtable*2*/
#define WINNER 2
#define LOOSER 3

/*------------------------------------------------------------------------
| Estrutura 		team 												  
|																		  
| caracterizada por|													  
| 	.name          |string nao vazia, max 1023 caracteres
| 	.wins          |inteiro que repreenta as vitorias da equipa			  		   
--------------------------------------------------------------------------*/
typedef struct team{
	char * name;
	int wins;
}pTeam; /*pTeam e um pointer para uma struct team*/

/*------------------------------------------------------------------------
| Estrutura 		node_team 												  
|				   |no da minha tabela de equipas- team														  
| caracterizada por|													  
| 	.t        	   |ponteiro pTeam para a equipa t - estrutura team	   
--------------------------------------------------------------------------*/
typedef struct node_team{
	pTeam * t;
}tlink; /*tlink e um pointer para uma struct node_team*/

void err(const char *msg);
char * my_strdup(char *in);
int hash(char* v);
int hashtwo(char * v);

tlink ** init_HTteams(int number);
tlink ** init_abcTeam();
tlink** texpand(tlink ** HTgame, int number);
tlink * tsimplyInsert(tlink * new, tlink ** HTteams);
pTeam ** team_array(int counter);
pTeam * create_team(char * buffer0);
tlink * tLinkInsert(char * buffer0, tlink * link, tlink ** HTgame);
tlink * search_team(tlink ** HTteams, char * nome);
pTeam ** alive_team(tlink ** HTteams, pTeam ** aux);
pTeam ** search_el(pTeam ** aux, tlink ** HTteams, int count);
pTeam ** abc_winners(pTeam ** STteams, int counter);
tlink * change_win_team(tlink **HTteams, char*nome, int var);
bool teamisEmpty(tlink ** HTteams);
void teamFree(pTeam * t);
void free_tTable(tlink * ttable);

#endif
