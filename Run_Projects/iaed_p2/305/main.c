#include "data_structures.h"
#include "aux_functions.h"

/*-------------------------------------------------------------------------------------------------
	Command a - Adds a new game
-------------------------------------------------------------------------------------------------*/

/* Reads the input for a given game */
void reads_input_game_full(Game *ng){
	getchar(); /* skips ' ' */
	ng->n  = read_string(':');
	ng->t1 = read_string(':');
	ng->t2 = read_string(':');
	ng->s1 = read_number(':');
	ng->s2 = read_number('\n');
}

/* Checks for errors */
int error_check_a(Game *g, Game **G, int *G_sz, Team **T, int *T_sz, int *NL){
	/* checks if game already exists */
	if(HT_G_search(g->n, G, G_sz) != NULL){
		printf("%d Jogo existente.\n", *NL);
		return 1;
	/* checks if teams exist */
	} else if(HT_T_search(g->t1, T, T_sz) == NULL || HT_T_search(g->t2, T, T_sz) == NULL){
		printf("%d Equipa inexistente.\n", *NL);
		return 1;
	}
	return 0;
}

/* Updates the number of games won of the teams of a given game */
void update_games_won(char *slct, Game *g, Team **T, int *T_sz){
	Team *t1_HT = HT_T_search(g->t1, T, T_sz); /* teams of the game g */
	Team *t2_HT = HT_T_search(g->t2, T, T_sz);
	int l;	/* logical value for selection */

	if((l = (strcmp(slct, "tie 1") == 0)) || (strcmp(slct, "tie 2") == 0)){
		if(l && t1_HT->w > 0)
			t1_HT->w -= 1;
		else
			if(t2_HT->w > 0)
				t2_HT->w -= 1;
	}
	else{
		if(g->s1 > g->s2){
			t1_HT->w += 1;
			if(strcmp(slct, "g not new") == 0 && t2_HT->w > 0)
				t2_HT->w -= 1;
		}
		else if(g->s1 < g->s2){
			t2_HT->w += 1;
			if(strcmp(slct, "g not new") == 0 && t1_HT->w > 0)
				t1_HT->w -= 1;
		}
	}
}

/*-------------------------------------------------------------------------------------------------
	Command A - Adds a new team
-------------------------------------------------------------------------------------------------*/

Team ** A(Team **T, int *T_sz, int *T_n, int *NL){
	Team *nt = (Team *) malloc(sizeof(Team));
	
	getchar(); /* skips ' ' */
	nt->n = read_string('\n');
	nt->w = 0;

	/* checks if team already exists */
	if(HT_T_search(nt->n, T, T_sz) != NULL){
		printf("%d Equipa existente.\n", *NL);
		free(nt->n);
		free(nt);
		return T;
	}

	*T_n += 1;

	T = HT_T_insert(nt, T, T_sz, T_n);

	return T;
}


/*-------------------------------------------------------------------------------------------------
	Command p - searches for a game given its name
-------------------------------------------------------------------------------------------------*/

void p(Game **G, int *G_sz, int *NL){
	char *name;	  	/* name read from input */
	Game *srch; 	/* pointer to the result of the search */
	
	getchar(); 	/* skips ' ' */
	name = read_string('\n');
	
	srch = HT_G_search(name, G, G_sz);
	if(srch == NULL){
		printf("%d Jogo inexistente.\n", *NL);
	} else {
		printf("%d %s %s %s %d %d\n", *NL, srch->n, srch->t1, srch->t2, srch->s1, srch->s2);
	}

	free(name);
}

/*-------------------------------------------------------------------------------------------------
	Command P - searches for a team given its name
-------------------------------------------------------------------------------------------------*/

void P(Team **T, int *T_n, int *NL){
	char *name; 	/* name read from input */
	Team *srch;		/* pointer to the result of the search */

	getchar(); /* skips ' ' */
	name = read_string('\n');

	srch = HT_T_search(name, T, T_n);
	if(srch == NULL){
		printf("%d Equipa inexistente.\n", *NL);
	} else {
		printf("%d %s %d\n", *NL, srch->n, srch->w);
	}

	free(name);
}

/*-------------------------------------------------------------------------------------------------
	Command l - lists all games by order of insertion
-------------------------------------------------------------------------------------------------*/

void l(node **ends, Game **G, int *G_sz, int *G_n, int *NL){
	Game *g;	/* pointer to a game */
	node *head = ends[HEAD];
	node *t;
	
	getchar(); /* skips '\n' */

	if(*G_n == 0){
		return;
	}

	for(t = head; t != NULL; t = t->next){
		g = HT_G_search(t->text, G, G_sz);
		printf("%d %s %s %s %d %d\n", *NL, g->n, g->t1, g->t2, g->s1, g->s2);
	}
}

/*-------------------------------------------------------------------------------------------------
	Command r - deletes a game given it's name 
-------------------------------------------------------------------------------------------------*/

node ** r(Game **G, int *G_sz, int *G_n, node **ends, Team **T, int *T_sz, int *NL){
	char *name; 			/* name of the game read from the input */
	Game *srch;				/* pointer to the searched game */
	char *selector;			/* string that tells update_games_won() what to do */
	int needs_update = 1;	/* logical value: True if number of games won needs an update */

	getchar(); /* skips ' ' */
	name = read_string('\n');

	srch = HT_G_search(name, G, G_sz);
	if(error_check_r_s(srch, name, NL))
		return ends;
	
	/* game is tied? */
	if(srch->s1 == srch->s2)
		needs_update = 0;
	/* which team was originally the winner? */
	else if(srch->s1 > srch->s2)
		selector = "tie 1";
	else
		selector = "tie 2";

	if(needs_update)
		update_games_won(selector, srch, T, T_sz);

	ends = lst_delete(ends, name);

	HT_G_delete(name, G, G_sz);

	*G_n -= 1;

	free(name);

	return ends;
}



/*-------------------------------------------------------------------------------------------------
	Command s - changes the score of a game given it's name
-------------------------------------------------------------------------------------------------*/

void s(Game **G, int *G_sz, Team **T, int *T_sz, int *NL){
	Game *srch;				/* pointer to the searched game */
	char *name;				/* name read from input */
	char *prev_greater;		/* string that tells update_games_won() which team
						       had the greater score */
	int new_s1;				/* new scores */
	int new_s2;			
	int its_a_tie = 0;		/* logical value: True if new score is a tie */
	int needs_update = 1;	/* logical value: True if number of games won needs an update */
	int g_prev_tied = 0;	/* logical value: True if game's original score is a tie */

	getchar(); 	
	name   = read_string(':');
	new_s1 = read_number(':');
	new_s2 = read_number('\n');

	srch = HT_G_search(name, G, G_sz);
	if(error_check_r_s(srch, name, NL))
		return;
	
	/* checks if game was previously tied */
	if(srch->s1 == srch->s2)
		g_prev_tied = 1;

	/* is the relation of order the same? */
	if((srch->s1 > srch->s2 && new_s1 > new_s2) || (srch->s1 < srch->s2 && new_s1 < new_s2)
		|| (srch->s1 == srch->s2 && new_s1 == new_s2)){
		needs_update = 0;
	}
	/* is the new score a tie? */
	else if(new_s1 == new_s2){
		its_a_tie = 1;
		if(srch->s1 > srch->s2)
			prev_greater = "tie 1";
		else
			prev_greater = "tie 2";
	}

	/* updates score */
	srch->s1 = new_s1;
	srch->s2 = new_s2;
	if(needs_update){
		if(its_a_tie)
			update_games_won(prev_greater, srch, T, T_sz);
		else if(g_prev_tied)
			update_games_won("g not new prev tied", srch, T, T_sz);
		else
			update_games_won("g not new", srch, T, T_sz);

	}

	free(name);
}

/*-------------------------------------------------------------------------------------------------
	Command g - Finds the teams with most games won...
-------------------------------------------------------------------------------------------------*/

void g(Team **T, int *T_sz, int *T_n, int *NL){
	int sz = *T_sz;
	int i;
	int max = 0;		/* biggest number of games won */
	char **t_names = (char **) malloc(*T_n * sizeof(char*)); /* names of the teams with 
																the max games won */
	int len_t_names=0;	/* number of elements of t_names */

	getchar(); /* skips ' ' */

	if(*T_n == 0){
		free(t_names);
		return;
	}

	/* goes through teams hash table */
	for(i=0; i < sz; i++){
		if(T[i] != NULL){
			/* finds a new max, resets t_names */
			if(T[i]->w > max){
				max = T[i]->w;
				len_t_names = 1;
				t_names[0] = T[i]->n;
			}
			/* finds another team with max games won, adds it's name to t_names */
			else if(T[i]->w == max){
				len_t_names += 1;
				t_names[len_t_names - 1] = T[i]->n;
			}
		}
	}

	qsort(t_names, len_t_names, sizeof(char*), comparator);

	printf("%d Melhores %d\n", *NL, max);
	for(i=0; i < len_t_names; i++){
		printf("%d * %s\n", *NL, t_names[i]);
	}

	free(t_names);

}

/*-------------------------------------------------------------------------------------------------
	Main loop
-------------------------------------------------------------------------------------------------*/

int main(){
	int *NL = (int *) malloc(sizeof(int));	/* lines of the commands to ease debugging */
	Game **G = NULL; 						/* games hash table */
	int *G_sz = (int *) malloc(sizeof(int));/* games hash table size */
	int *G_n  =	(int *) malloc(sizeof(int));/* number of existant games */
	Team **T = NULL; 						/* teams hash table */
	int *T_sz = (int *) malloc(sizeof(int));/* teams hash table size */
	int *T_n  = (int *) malloc(sizeof(int));/* number of existant teams */
	node **ends = malloc(sizeof(node*) * 2);/* vector with ends of the list with the game's
											   names sorted by order of entry */
	int idc;								/* command's identifier*/
	Game *ng;								/* new game pointer used by command a */
	
	*NL = 0;
	*G_sz = HT_SZ;
	*G_n = 0;
	G = HT_G_init(G, G_sz);
	*T_sz = HT_SZ;
	*T_n = 0;
	T = HT_T_init(T, T_sz);
	ends[HEAD] = NULL;
	ends[TAIL] = NULL;

	while((idc = getchar()) != 'x'){
		*NL += 1;
		switch(idc){
			case 'a':
				ng = malloc(sizeof(Game));
				reads_input_game_full(ng);
				if(error_check_a(ng, G, G_sz, T, T_sz, NL)){
					free(ng->n);
					free(ng->t1);
					free(ng->t2);
					free(ng);
					break;
				}
				update_games_won("new", ng, T, T_sz);
				*G_n += 1;
				HT_G_insert(ng, G, G_sz);
				if(*G_n > *G_sz/2){
					G = HT_G_expand(G, G_sz);
				}
				ends = insert_END(ends, ng->n);
				break;
			case 'r':
				ends = r(G, G_sz, G_n, ends, T, T_sz, NL);
				break;
			case 'A':
				T = A(T, T_sz, T_n, NL);
				break;
			case 'p':
				p(G, G_sz, NL);
				break;
			case 'P':
				P(T, T_sz, NL);
				break;
			case 'l':
				l(ends, G, G_sz, G_n, NL);
				break;
			case 's':
				s(G, G_sz, T, T_sz, NL);
				break;
			case 'g':
				g(T, T_sz, T_n, NL);
				break;
		}
	}

	HT_G_free(G, G_sz);
	HT_T_free(T, T_sz);
	free_list(ends);
	free(NL);
	free(G_n);
	free(G_sz);
	free(T_n);
	free(T_sz);
	
	return 0;
}