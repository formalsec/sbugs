#include "constants.h"
#include "db.h"

#ifndef DBMS_H
#define DBMS_H


/* Database Management System Structure */
typedef struct dbms {
	/* System Database */
	DB db;

	/* Max Size for the (Hash)Tables in the Database */
	uint M;

	/* Line number of the input command that originated that output */
	uint NL;

	/* Total number of matches in the system. */
	uint match_count;

	/* Total number of teams inputed in the Database. */
	uint team_count;

	/* Total number of teams in the database. */
	uint most_matches_won;
}* DBMS;

/* Initialize Database */
DB db_init(uint max);

/* Destroy Database */
void db_destroy(DB db, uint max);

/* Hash Function */
int hash(const char *v, uint max);

/* Initialize Matches Hashtable. */
m_link* M_HT_init(uint max);

/* Initialize Matches Double Linked List. */
M_DLL* M_DLL_init();

/* Initialize Teams Hashtable. */
t_link* T_HT_init(uint max);

/* Initialize Database Management System. */
DBMS dbms_init(uint max);

/* Destroy Database Management System */
void dbms_destroy(DBMS dbms);


/* Match Hashtable Funcitons */

/*  */
void free_m_node(m_link node);


/*Remove from beggining of the list*/
void pop(M_DLL* list);

/*Remove from end of the list*/
void remove_last(M_DLL* list);

/*  */
m_link remove_m_node(m_link head, M_DLL* list, const char* k);


/*  */
void delete_match(m_link* heads, M_DLL* list, const char* k, const uint M);


/*  */
void destroy_match_list(m_link head);

/*  */
void destroy_DLList(M_DLL* list);

/*  */
void destroy_m_hash(m_link* heads, const uint M);




/*  */
void insert_match(m_link* MT_head, M_DLL* list, Match match, uint max);

/* 
 * Returns the team, with the given name, from the Teams Hashtable.
 * Returns NULL if the teams doesn't exist.
 */
Match search_match_list(m_link head, const char* match_name);

/*  */
Match search_match(m_link* MT_head, const char* key, const uint max);


/*  */
m_link new_match_node(Match match, m_link ht_next, m_link l_tail);

/*Add match node to beggining of the list*/
m_link push_match_node(m_link ht_head, m_link l_tail, Match m);



/* Team Hashtable Funcitons */
void free_t_node(t_link node);

/*  */
t_link remove_t_node(t_link head, const char* k);


/*  */
void delete_team(t_link* heads, const char* k, const uint M);

/*  */
void destroy_team_list(t_link head);


/*  */
void destroy_t_hash(t_link* heads, const uint M);

/*Add team node to beggining of the list*/
t_link push_team_node(t_link head, Team t);

/* Search team list for a team with the given name */
Team search_team_list(t_link head, t_Key team_name);

/* Search teams (Hash)table for a team with the given name */
Team search_team(t_link* T_HT_head, t_Key key, const uint max);


/*  */
void insert_team(t_link* T_HT_head, Team team, uint max);

/* 
 * Returns the team, with the given name, from the Teams Hashtable.
 * Returns NULL if the teams doesn't exist.
 */
Team search_team(t_link* T_HT_head, const char* key, const uint max);



/* 
 * Management Functions
 */


/* Adds a new match to the database. */
void add_match(DBMS dbms, const char *match_name, const char* team_1, 
			    const char* team_2, const uint score_1, const uint score_2);

/* Adds a new team to the database. */
void add_team(DBMS dbms, const char *team_name);

/* Search for a team with the given name in the database. */
void list_team(DBMS dbms, const char *team_name);

/* Search for a match with the given name in the database. */
void list_match(DBMS dbms, const char *match_name);

/* Change the score for the match with the given name. */
void change_match_score(DBMS dbms, const char *match_name, const uint score_1, const uint score_2);

/* Remove match with the given name. */
void remove_match(DBMS dbms, const char *match_name);

/* Lists all matches in the database by input order. */
void list_all_matches(DBMS dbms);

/* Lists teams in the database with most games won. */
void list_best_teams(DBMS dbms);


/* 
 * Auxiliary Functions
 */


/* 
 * Returns the winning team of the given match.
 * Returns NULL if the match is tied.
 */
Team check_winning_team(Match match);


/*  */
int compare_team_wins(const void *t1, const void *t2);


#endif /* DBMS_H */
