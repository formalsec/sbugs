#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "games.h"
#include "teams.h"
#include "mysort.h"

#define N_HASH_TABLE 1500	/* numero de listas da hashtable */
#define MAX_CHAR 1024		/* maximo de 1023 caracteres + 1 ('\0') */

/* adiciona um novo jogo */
void comand_a(int nl, dlist_games ** hasht_g, dlist_teams ** hasht_t, dlist_games * dl_g){
	int score1, score2;
	char g_name[MAX_CHAR], name_t1[MAX_CHAR], name_t2[MAX_CHAR];
	game * p_g;					/* novo jogo */
	team * p_t;					/* equipa a qual vai ser aumentado o numero de vitorias */
	node_dlist_games * other;	/* ponteiro para o node da lista ordenada dos jogos */
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", g_name, name_t1, name_t2, &score1, &score2);
	if(search_hasht_g(hasht_g, g_name) != NULL) printf("%d Jogo existente.\n", nl);
	else if(search_hasht_t(hasht_t, name_t1) == NULL || search_hasht_t(hasht_t, name_t2) == NULL)
		printf("%d Equipa inexistente.\n", nl);
	else{
		p_g = new_game(g_name, name_t1, name_t2, score1, score2);
		if(score1 > score2){								/* se a equipa 1 ganhou */
			p_t = search_hasht_t(hasht_t, name_t1)->p_t;
			p_t->n_wins++;
		}
		if(score1 < score2){								/* se a equipa 2 ganhou */
			p_t = search_hasht_t(hasht_t, name_t2)->p_t;
			p_t->n_wins++;
		}
		other = addlast_dlist_games(dl_g, p_g);	/* insere na lista ordenada dos jogos */
		insert_hasht_g(hasht_g, p_g, other);	/* insere na hashtable dos jogos */
	}
}

/* adiciona uma nova equipa */
void comand_A(int nl, dlist_teams ** hasht_t){
	char t_name[MAX_CHAR];
	team * p_t;					/* nova equipa */
	scanf(" %[^:\n]", t_name);
	if(search_hasht_t(hasht_t, t_name)) printf("%d Equipa existente.\n", nl);
	else{
		p_t = new_team(t_name);
		insert_hasht_t(hasht_t, p_t);	/* insere na hashtable das equipas */
	}
}

/* lista todos os jogos pela ordem em que foram introduzidos */
void comand_l(int nl, dlist_games * dl_g){
	node_dlist_games * n_dl = dl_g->head;	/* node que vai percorrer a lista dos jogos */
	while(n_dl != NULL){
		printf("%d %s %s %s %d %d\n", nl, n_dl->p_g->g_name, n_dl->p_g->name_t1, 
			n_dl->p_g->name_t2, n_dl->p_g->score1, n_dl->p_g->score2);
		n_dl = n_dl->next;			/* node seguinte da lista dos jogos */
	}
}

/* procura um jogo */
void comand_p(int nl, dlist_games ** hasht_g){
	char g_name[MAX_CHAR];
	node_dlist_games * n_dl;	/* node do jogo procurado */
	scanf(" %[^:\n]", g_name);
	if((n_dl = search_hasht_g(hasht_g, g_name)) == NULL) printf("%d Jogo inexistente.\n", nl);
	else printf("%d %s %s %s %d %d\n", nl, g_name, n_dl->p_g->name_t1, n_dl->p_g->name_t2, n_dl->p_g->score1, n_dl->p_g->score2);
}

/* procura uma equipa */
void comand_P(int nl, dlist_teams ** hasht_t){
	char t_name[MAX_CHAR];
	node_dlist_teams * n_dl;	/* node da equipa procurada */
	scanf(" %[^:\n]", t_name);
	if((n_dl = search_hasht_t(hasht_t, t_name)) == NULL) printf("%d Equipa inexistente.\n", nl);
	else printf("%d %s %d\n", nl, t_name, n_dl->p_t->n_wins);
}

/* apaga um jogo */
void comand_r(int nl, dlist_games ** hasht_g, dlist_teams ** hasht_t, dlist_games * dl_g){
	int score1, score2, h;
	char g_name[MAX_CHAR];
	team * p_t;			/* equipa a qual vai ser diminuido o numero de vitorias */
	node_dlist_games * n_dl, * other;	/* node do jogo ao qual o score vai ser alterado */
	scanf(" %[^:\n]", g_name);			/* e ponteiro para node do jogo da lista dos jogos */
	if((n_dl = search_hasht_g(hasht_g, g_name)) == NULL) printf("%d Jogo inexistente.\n", nl);
	else{
		score1 = n_dl->p_g->score1;
		score2 = n_dl->p_g->score2;
		if(score1 > score2){
			p_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1)->p_t;
			p_t->n_wins--;
		}
		if(score1 < score2){
			p_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2)->p_t;
			p_t->n_wins--;
		}
		other = n_dl->other;
		h = hashf(g_name);
		rm_node_dlist_games(hasht_g[h], n_dl);	/* remove o node do jogo da hashtable dos jogos */
		rm_node_dlist_games(dl_g, other);		/* remove o node do jogo da lista dos jogos */
	}
}

/* altera o score de um jogo */
void comand_s(int nl, dlist_games ** hasht_g, dlist_teams ** hasht_t){
	int score1, score2, pscore1, pscore2;
	char g_name[MAX_CHAR];
	node_dlist_games * n_dl;	/* node do jogo ao qual o score vai ser alterado */
	node_dlist_teams * n_dl_t;	/* node da equipa a qual vai ser aumentado/diminuido o numero de vitorias */
	scanf(" %[^:\n]:%d:%d", g_name, &score1, &score2);
	if((n_dl = search_hasht_g(hasht_g, g_name)) == NULL) printf("%d Jogo inexistente.\n", nl);
	else{
		pscore1 = n_dl->p_g->score1;	/* guarda os scores anteriores */
		pscore2 = n_dl->p_g->score2;
		n_dl->p_g->score1 = score1;		/* atribui os novos scores */
		n_dl->p_g->score2 = score2;
		if(pscore1 > pscore2 && score1 <= score2){	/* se a equipa 1 tinha a vitoria e deixou de a ter */
			n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1);
			n_dl_t->p_t->n_wins--;
			if(score1 < score2){					/* se a equipa 2 passou a ter a vitoria */
				n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2);
				n_dl_t->p_t->n_wins++;
			}
		}
		if(pscore1 < pscore2 && score1 >= score2){	/* se a equipa 2 tinha a vitoria e deixou de a ter */
			n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2);
			n_dl_t->p_t->n_wins--;
			if(score1 > score2){					/* se a equipa 1 passou a ter a vitoria */
				n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1);
				n_dl_t->p_t->n_wins++;
			}
		}
		if(pscore1 == pscore2){						/* se nenhuma das equipas tivesse a vitoria */
			if(score1 > score2){					/* se a equipa 1 passou a ter a vitoria */
				n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1);
				n_dl_t->p_t->n_wins++;
			}
			if(score1 < score2){					/* se a equipa 2 passou a ter a vitoria */
				n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2);
				n_dl_t->p_t->n_wins++;
			}
		}
	}
}

/* encontra as equipas que venceram mais jogos */
void comand_g(int nl, dlist_teams ** hasht_t){
	int ha_equipa = 0, i, j = 0, max_wins = 0, len;
	node_dlist_teams * n_dl;	/* node que vai percorrer a hashtable das equipas */
	char ** list_t = can_fail_malloc(sizeof(char *) * N_HASH_TABLE);	/* lista de nomes das equipas com mais vitorias */
	for(i = 0; i < N_HASH_TABLE; i++){
		n_dl = hasht_t[i]->head;			/* percorre a hashtable das equipas para obter o max_wins */
		while(n_dl != NULL){
			ha_equipa = 1;
			if(n_dl->p_t->n_wins > max_wins) max_wins = n_dl->p_t->n_wins;
			n_dl = n_dl->next;
		}
	}
	if(ha_equipa){
		printf("%d Melhores %d\n", nl, max_wins);
		for(i = 0; i < N_HASH_TABLE; i++){
			n_dl = hasht_t[i]->head;		/* volta a percorrer a hashtable e se as vitorias */
			while(n_dl != NULL){			/* corresponderem guarda o nome na lista de nomes */
				if(n_dl->p_t->n_wins == max_wins){
					len = strlen(n_dl->p_t->t_name) + 1;
					list_t[j] = can_fail_malloc(sizeof(char) * len);
					strcpy(list_t[j++], n_dl->p_t->t_name);
				}
				n_dl = n_dl->next;
			}
		}
		sort_alpha(list_t, 0, j - 1);				/* ordena a lista de nomes */
		for(i = 0; i < j; i++){
			printf("%d * %s\n", nl, list_t[i]);		/* printa a lista de nomes agora ordenada */
			free(list_t[i]);						/* free nome da equipa */
		}
	}
	free(list_t);									/* free lista dos nomes */
}