#include "all.h"
#include "constants.h"
#include "Team.h"
#include "Game.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /*--------------------*\
  * Funcoes auxiliares *
 \*--------------------*/

/* funcao de comparacao para o qsort */
int cmp_func(const void* a, const void* b) {
	return strcmp(*(char**)a, *(char**)b);
}

/* verifica se existe um elemento com o nome name na lista lst */
int in_list(char* name, list* lst) {
	return !!STsearch(lst->table, name);
}

/* cria um jogo novo */
node* create_game(char* name, team* t1, team* t2, int s1, int s2) {
	node* n = malloc(sizeof(node));			/* no do jogo */
	game* g = malloc(sizeof(game));			/* jogo em si */

	g->name = malloc((strlen(name) + 1) * sizeof(char));	/* aloca o espaco para o nome */
	strcpy(g->name, name);									/* copia o nome */

	/* define as equipas e os seus scores */
	g->t1 = t1;
	g->t2 = t2;
	g->s1 = s1;
	g->s2 = s2;

	/* atualiza as vitorias */
	if (s1 > s2) g->t1->wins++;
	else if (s2 > s1) g->t2->wins++;

	n->type = GAME;
	n->d.g = g;

	return n;
}

/* cria uma equipa nova */
node* create_team(char* name) {
	node* n = malloc(sizeof(node));			/* no da equipa */
	team* t = malloc(sizeof(team));			/* equipa em si */

	t->name = malloc((strlen(name) + 1) * sizeof(char));	/* aloca o espaco para o nome */
	strcpy(t->name, name);									/* copia o nome */

	t->wins = 0;

	n->type = TEAM;
	n->d.t = t;

	return n;
}

/*--------------------*\
 * Funcoes principais *
\*--------------------*/

/* adiciona um novo jogo */
void add_game(long int NL, list* game_list, list* team_list) {
	char name[GAME_MAX], t1[TEAM_MAX], t2[TEAM_MAX];
	int s1, s2;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, t1, t2, &s1, &s2);
	if (in_list(name, game_list))		/* verifica se ja existe o jogo */
		printf("%ld Jogo existente.\n", NL);

	/* verifica se ambas as equipas existem */
	else if (in_list(t1, team_list) && in_list(t2, team_list)) {
		node* n1, * n2;

		n1 = STsearch(team_list->table, t1);	/* no da equipa 1 */
		n2 = STsearch(team_list->table, t2);	/* no da equipa 2 */

		/* cria um novo jogo e adiciona-o a lista de jogos */
		n1 = create_game(name, n1->d.t, n2->d.t, s1, s2);
		append(game_list, n1);
	}
	else
		printf("%ld Equipa inexistente.\n", NL);
}

/* adiciona uma nova equipa */
void add_team(long int NL, list* team_list) {
	char name[TEAM_MAX];

	scanf(" %[^:\n]", name);
	if (in_list(name, team_list))				/* verifica se ja a equipa ja existe */
		printf("%ld Equipa existente.\n", NL);
	else {
		node* n;

		/* cria uma equipa e adiciona-a a lista de equipas */
		n = create_team(name);
		append(team_list, n);
	}
}

/* lista todos os jogos, por ordem de introducao */
void list_games(long int NL, list* game_list) {
	node* n = game_list->head;
	game* g;

	/* percorre a lista de jogos e imprime um jogo por linha */
	while (n) {
		g = n->d.g;
		printf("%ld %s %s %s %d %d\n",
			NL, g->name, g->t1->name, g->t2->name, g->s1, g->s2);
		n = n->next;
	}
}

/* encontra um jogo dado uma lista de caracteres */
void find_game(long int NL, list* game_list) {
	char name[GAME_MAX];
	node* n;
	game* g;

	scanf(" %[^:\n]", name);
	n = STsearch(game_list->table, name);		/* no correspondente ao jogo */
	if (n) {
		/* no nao e nulo logo o jogo existe */
		g = n->d.g;
		printf("%ld %s %s %s %d %d",
			NL, g->name, g->t1->name, g->t2->name, g->s1, g->s2);
	}
	else
		printf("%ld Jogo inexistente.", NL);
	printf("\n");
}

/* encontra uma equipa dada uma lista de caracteres */
void find_team(long int NL, list* team_list) {
	char name[TEAM_MAX];
	node* n;

	scanf(" %[^:\n]", name);
	n = STsearch(team_list->table, name);		/* no correspondente a equipa */
	if (n)
		/* no nao e nulo logo a equipa existe */
		printf("%ld %s %d\n", NL, name, n->d.t->wins);
	else
		printf("%ld Equipa inexistente.\n", NL);
}

/* remove uma equipa dada uma lista de caracteres */
void remove_game(long int NL, list* game_list) {
	char name[GAME_MAX];
	node* n;
	game* g;

	scanf(" %[^:\n]", name);
	n = STsearch(game_list->table, name);		/* no correspondente ao jogo */
	if (n) {
		/* no nao e nulo logo o jogo existe */
		g = n->d.g;

		/* atualiza as vitorias */
		if (g->s1 > g->s2) g->t1->wins--;
		else if (g->s1 < g->s2) g->t2->wins--;

		/* remove o jogo da lista de jogos */
		delete(game_list, n);
	}
	else
		printf("%ld Jogo inexistente.\n", NL);
}

/* altera os scores de um dado jogo */
void change_game(long int NL, list* game_list) {
	char name[GAME_MAX];
	int s1, s2;
	node* n;
	game* g;

	scanf(" %[^:\n]:%d:%d", name, &s1, &s2);
	n = STsearch(game_list->table, name);		/* no correspondente ao jogo */
	if (n) {
		/* no nao e nulo logo o jogo existe */
		g = n->d.g;

		/* verifica todas as hipoteses, para alterar as vitorias corretamente */
		if (g->s1 > g->s2 && s1 <= s2) {
			/* equipa 1 ganhou e agora perdeu ou empatou */
			g->t1->wins--;
			if (s1 < s2)
				/* equipa 1 agora perdeu */
				g->t2->wins++;
		}
		else if (g->s1 < g->s2 && s1 >= s2) {
			/* equipa 1 perdeu e agora ganou ou empatou */
			g->t2->wins--;
			if (s1 > s2)
				/* equipa 1 agora ganhou */
				g->t1->wins++;
		}
		else if (g->s1 == g->s2) {
			/* as equipas empataram */
			if (s1 > s2)
				/* equipa 1 agora ganhou */
				g->t1->wins++;
			else if (s1 < s2)
				/* equipa 2 agora ganhou */
				g->t2->wins++;
		}
		n->d.g->s1 = s1;
		n->d.g->s2 = s2;
	}
	else
		printf("%ld Jogo inexistente.\n", NL);
}

/* encontra as equipas que ganharam mais jogos, e imprimeas por ordem alfabetica */
void get_winners(long int NL, list* team_list) {
	int wins = 0;
	int j, i = 0;
	int size = INIT_SIZE;		/* tamanho da lista de equipas */
	char** lst = (char**)malloc(size * sizeof(char*));	/* lista com nome das equipas vencedoras */
	node* head = team_list->head;

	if (head) {
		while (head) {
			/* percorre a lista de equipas para encontrar o numero de vitorias maximo */
			if (head->d.t->wins > wins) {
				wins = head->d.t->wins;

				/* reinicia a lista de equipas vencedoras */
				lst[0] = head->d.t->name;
				i = 1;
			}
			else if (head->d.t->wins == wins) {
				if (i >= size) {
					size *= 2;
					lst = (char**)realloc(lst, size);
				}
				/* atualiza a lista de equipas vencedoras */
				lst[i++] = head->d.t->name;
			}

			head = head->next;
		}
		printf("%ld Melhores %d\n", NL, wins);

		/* ordena as equipas vencedoras por ordem alfabetica */
		qsort(lst, i, sizeof(char*), cmp_func);

		for (j = 0; j < i; j++)
			printf("%ld * %s\n", NL, lst[j]);
	}

	free(lst);
}
