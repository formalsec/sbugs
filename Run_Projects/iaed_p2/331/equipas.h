#ifndef EQUIPAS_H
#define EQUIPAS_H

typedef struct equipa{
	char * nome_eq;
	int vitorias;
	struct equipa * prev;
	struct equipa * next;
} Team;

typedef struct lst_eq{
	Team * head;
	Team * last;
} List_Teams;

/*---------------------------------------------------------------------------------------*/

/*inicia uma lista duplamente ligada de equipas*/
List_Teams * init_list_t();

/*cria uma nova equipa*/
Team * new_team(char * eq);

/*acrescenta uma nova equipa a lista de equipas, como elemento final*/
Team * add_end_team(List_Teams * l, char * eq);

/*procura uma equipa pelo seu nome numa lista de equipas*/
Team * search_team(List_Teams * l, char * nome);

/*altera o numero de vitorias de uma equipa numa lista de jogos*/
void change_wins(List_Teams * l, char * eq, int v);

/*elimina uma equipa da memoria*/
void free_team(Team * n);

/*elimina uma equipa de uma lista de equipas*/
void remove_team(List_Teams * l, char * eq);

/*elimina a primeira equipa de uma lista de equipas*/
Team * remove_first_team(Team * head);

/*elimina uma lista de equipas*/
void free_all_teams(List_Teams * l);

/*imprime informacoes relativas a uma equipa*/
void print_team(Team * n);

#endif
