#include "dbms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* revert */

DB db_init(uint max) {
	DB db = malloc(sizeof(struct db));

	db->matches_table = M_HT_init(max);
	db->matches_list = M_DLL_init();
	db->teams_table = T_HT_init(max);
	
	return db;
}

void db_destroy(DB db, uint max) {
	destroy_m_hash(db->matches_table, max);

	destroy_t_hash(db->teams_table, max);

	destroy_DLList(db->matches_list);
	free(db);

}

void dbms_destroy(DBMS dbms) {
	db_destroy(dbms->db, dbms->M);
	free(dbms);
}


m_link* M_HT_init(uint max) {
	uint i;
	m_link* heads = (m_link*) malloc(sizeof(m_link) * max);

	for(i = 0; i < max; i++) {
		heads[i] = NULL;
	}
	return heads;
}


M_DLL* M_DLL_init() {
	M_DLL* list = malloc(sizeof(M_DLL));
	list->head = NULL;
	list->tail = NULL;
	return list;
}


t_link* T_HT_init(uint max) {
	uint i;
	t_link* heads = (t_link*) malloc(sizeof(t_link) * max);

	for(i = 0; i < max; i++) {
		heads[i] = NULL;
	}
	return heads;
}


DBMS dbms_init(uint max) {
	DBMS dbms = malloc(sizeof(struct dbms));

	dbms->M = max;
	dbms->match_count = 0;
	dbms->team_count = 0;
	dbms->NL = 1;
	dbms->db = db_init(max);
	
	return dbms;
}

/*  */
int hash(const char *v, uint max) {
	uint h = 0, a = 31415, b = 27183;
	for(;*v != '\0'; v++,a = a*b % (max-1))
		h = (a*h + *v) % max;
	return h;
}



m_link new_match_node(Match match, m_link ht_next, m_link l_tail) {
	m_link new_m_link = malloc(sizeof(struct m_node));

	new_m_link -> match = match;
	new_m_link -> ht_next = ht_next;
	new_m_link -> l_next = NULL;
	new_m_link -> l_prev = l_tail;

	if (l_tail != NULL)
		l_tail->l_next = new_m_link;

	return new_m_link;
}

/*Add to beggining of the list*/
m_link push_match_node(m_link ht_head, m_link l_tail, Match m) {
	m_link aux = new_match_node(m, ht_head, l_tail);

	return aux;
}



Match search_match_list(m_link head, const char* match_name) {
	m_link current;
	for (current = head; current; current = current->ht_next) {
		if (strcmp(current->match->name, match_name)==0)
			return current->match;
	}
	return NULL;
}

Match search_match(m_link* MT_head, const char* key, const uint max) {
	uint i = hash(key, max);
	return search_match_list(MT_head[i], key);
}





t_link new_team_node(Team team, t_link next) {
	t_link new_t_link = malloc(sizeof(struct t_node));
	
	new_t_link -> team = team;
	new_t_link -> next = next;
	return new_t_link;
}

/*Add team node to beggining of the list*/
t_link push_team_node(t_link head, Team t) {
	t_link aux = new_team_node(t, head);
	return aux;
}


/* Initializes Teams Hashtable */
Team search_team_list(t_link head, const char* team_name) {
	t_link current;
	for (current = head; current; current = current->next) {
		if (strcmp(current->team->name, team_name)==0)
			return current->team;
	}
	return NULL;
}

Team search_team(t_link* T_HT_head, const char* key, const uint max) {
	uint i = hash(key, max);
	return search_team_list(T_HT_head[i], key);
}






void insert_match(m_link* MT_head, M_DLL* list, Match match, uint max) {
	uint i = hash(match->name, max);
	m_link aux = push_match_node(MT_head[i],list->tail, match);

	MT_head[i] = aux;
	list->tail = aux;

	if (list->head == NULL)
		list->head = aux;
}



void add_match(DBMS dbms, const char *match_name, const char* team1_name, 
			    const char* team2_name, const uint score1, const uint score2) {
	
	DB db = dbms->db;
	Match match;

	Team team1 = search_team(db->teams_table, team1_name, dbms->M);
	Team team2 = search_team(db->teams_table, team2_name, dbms->M);

	if(search_match(db->matches_table, match_name, dbms->M)) {
		printf("%u Jogo existente.\n", dbms->NL);
		return;

	}
	if(!team1 || !team2 ) {
		printf("%u Equipa inexistente.\n", dbms->NL);
		return;

	}

	dbms->match_count++;
	match = new_match(match_name, team1, team2, score1, score2);

	insert_match(db->matches_table, db->matches_list, match, dbms->M);
}

void insert_team(t_link* T_HT_head, Team team, uint max) {
	uint i = hash(team->name, max);
	T_HT_head[i] = push_team_node(T_HT_head[i], team);
}

void add_team(DBMS dbms, const char *team_name) {
	DB db = dbms->db;
	Team team;

	if(search_team(db->teams_table, team_name, dbms->M)) {
		printf("%u Equipa existente.\n", dbms->NL);
		return;
	}

	team = new_team(team_name);

	dbms->team_count++;

	insert_team(db->teams_table, team, dbms->M);
}

void list_team(DBMS dbms, const char *team_name) {
	DB db = dbms->db;
	Team team = search_team(db->teams_table, team_name, dbms->M);

	if(team == NULL) {
		printf("%u Equipa inexistente.\n", dbms->NL);
		return;
	}

	printf("%u %s %u\n", dbms->NL, team->name, team->matches_won);
}

void list_match(DBMS dbms, const char *match_name) {
	DB db = dbms->db;
	Match match = search_match(db->matches_table, match_name, dbms->M);

	if(match == NULL) {
		printf("%u Jogo inexistente.\n", dbms->NL);
		return;
	}
	printf("%u %s %s %s %u %u\n", dbms->NL, match->name, match->team_1->name, 
				match->team_2->name, match->score_1, match->score_2);
}

Team check_winning_team(Match match) {
	Team winning_team = NULL;

	if(match->score_1 > match->score_2)
		winning_team = match->team_1;
	else if(match->score_1 < match->score_2)
		winning_team = match->team_2;
	
	return winning_team;
}

void change_match_score(DBMS dbms, const char *match_name, const uint score_1, 
							const uint score_2) {
	DB db = dbms->db;
	Match match = search_match(db->matches_table, match_name, dbms->M);
	Team old_winning_team = NULL, 
		 new_winning_team = NULL;

	if(match == NULL) {
		printf("%u Jogo inexistente.\n", dbms->NL);
		return;
	}

	old_winning_team = check_winning_team(match);

	match->score_1 = score_1;
	match->score_2 = score_2;

	new_winning_team = check_winning_team(match);

	if(old_winning_team)
		old_winning_team->matches_won--;
	
	if(new_winning_team)
		new_winning_team->matches_won++;
}


void free_m_node(m_link node) {
	free_match(node->match);
	free(node);
}

void pop(M_DLL* list) {
	m_link oldHead ;

	if (list->head == NULL)
		return;

	oldHead = list->head;
	list->head = oldHead->l_next;

	if(list->head != NULL)
		list->head->l_prev = NULL;
	else
		list->tail = NULL;
}

void remove_last(M_DLL* list) {
	m_link oldTail;

	if (list == NULL)
		return;

	oldTail = list->tail;

	list->tail = oldTail->l_prev;

	if (list->tail != NULL) 
		list->tail->l_next = NULL;
	else 
		list->head = NULL;
}

m_link remove_m_node(m_link head, M_DLL* list, m_Key key) {
	m_link curr, prev;
	for (curr = head, prev = NULL; curr; prev = curr, curr = curr->ht_next) {
		if (m_eq(key, m_key(curr->match))) {

			/* Remove from hashtable */
			if (curr == head) 
				head = curr->ht_next;
			else 
				prev->ht_next = curr->ht_next;

			/* Remove from double linked list */
			if (curr == list->head)
				pop(list);
			else if (curr == list->tail)
				remove_last(list);
			else {
				curr->l_prev->l_next = curr->l_next;
				curr->l_next->l_prev = curr->l_prev;
			}

			free_m_node(curr);
			return head;
		}
	}
	return head;
}

void delete_match(m_link* heads, M_DLL* list, m_Key k, const uint M) {
	uint i = hash(k, M);
	heads[i] = remove_m_node(heads[i], list, k);
}

void remove_match(DBMS dbms, const char * match_name) {
	DB db = dbms->db;
	Match match = search_match(db->matches_table, match_name, dbms->M);

	if(match == NULL) {
		printf("%u Jogo inexistente.\n", dbms->NL);
		return;
	}

	if(match->score_1 > match->score_2) {
		match->team_1->matches_won--;
	}
	else if(match->score_1 < match->score_2) {
		match->team_2->matches_won--;	
	}
	
	delete_match(db->matches_table, db->matches_list, match_name, dbms->M);

	dbms->match_count--;
}


void list_all_matches(DBMS dbms) {
	DB db = dbms->db;
	m_link head = db->matches_list->head;
	Match curr_match;
	if(dbms->match_count == 0)
		return;


	while(head != NULL) {
		curr_match = head->match;
		printf("%u %s %s %s %u %u\n", dbms->NL, curr_match->name, 
				curr_match->team_1->name, curr_match->team_2->name, 
				curr_match->score_1, curr_match->score_2);
		head = head->l_next;
	}

}


int compare_team_wins(const void *t1, const void *t2) { 
    const Team team1 = (*(const Team *) t1); 
    const Team team2 = (*(const Team *) t2);

	return t_cmp(team1->name, team2->name);
}


void list_best_teams(DBMS dbms) {
	DB db = dbms->db;
	Team *team_list;
	t_link current;
	Team curr_team;
	uint i, j, 
		most_matches_won = 0,
		number_max_teams = 0;

	if(dbms->team_count == 0)
		return;

	for(i = 0; i < dbms->M; i++) {
		for (current = db->teams_table[i]; current; current = current->next) {
			if(current->team->matches_won == most_matches_won) {
				number_max_teams++;
			}
			else if (current->team->matches_won > most_matches_won) {
				most_matches_won = current->team->matches_won;
				number_max_teams = 1;
			}	
		}
	}

	team_list = malloc(sizeof(Team)*number_max_teams);

	for(i=0, j=0; i < dbms->M && j < number_max_teams;i++) {
		for (current = db->teams_table[i]; current ; current = current->next) {
			if(current->team->matches_won == most_matches_won) {
				team_list[j] = current->team;
				j++;
			}	
		}
	}

	qsort(team_list, number_max_teams , sizeof(Team), compare_team_wins);

	printf("%u Melhores %u\n", dbms->NL, most_matches_won);

	for(j = 0; j < number_max_teams; j++) {
		curr_team = team_list[j];
		printf("%u * %s\n", dbms->NL, curr_team->name);
	}

	free(team_list);
}


void free_t_node(t_link node) {
	free_team(node->team);
	free(node);
}

t_link remove_t_node(t_link head, const char* k) {
	t_link curr, prev;
	for (curr = head, prev = NULL; curr; prev = curr, curr = curr->next) {
		if (strcmp(k, curr->team->name)==0) {
			if (curr == head) head = curr->next;
			else prev->next = curr->next;
			free_t_node(curr);
			return head;
		}
	}
	return head;
}

void delete_team(t_link* heads, const char* k, const uint M) {
	uint i = hash(k, M);
	heads[i] = remove_t_node(heads[i], k);
}

void destroy_team_list(t_link head) {
	t_link current, aux;
	if (!head)
		return;
	
	for (current = head, aux = head->next; current; current = aux){
		aux = current->next;
		free_t_node(current);
	}
}

void destroy_t_hash(t_link* heads, const uint M) {
	uint i;
	for (i = 0; i < M; i++) {
		destroy_team_list(heads[i]);
	}
	free(heads);
}

void destroy_match_list(m_link head) {
	m_link current, aux;

	if (!head)
		return;
	
	for (current = head, aux = head->ht_next; current; current = aux){
		aux = current->ht_next;
		free_m_node(current);
	}
}

void destroy_DLList(M_DLL* list) {
	if (list == NULL)
		return;
	free(list);
}

void destroy_m_hash(m_link* heads, const uint M) {
	uint i;
	for (i = 0; i < M; i++) {
		destroy_match_list(heads[i]);
	}
	free(heads);
}



