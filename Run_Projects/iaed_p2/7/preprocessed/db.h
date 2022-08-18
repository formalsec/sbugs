#include "constants.h" /*  */
#include "Team.h" /*  */
#include "Match.h" /*  */

#ifndef DB_H
#define DB_H


/* Team Related Structures */

/* Node Structure for Team */
typedef struct t_node {
	Team team;
	struct t_node *next;
}* t_link;


/* Match Related Structures*/

/*
 * m_node has a different structure than usual. it has 3 node, 
 * 2 for the double linked list wich stores the matches by their inputted order
 * and 1 for the corresponding linked list on the hashtable.
 * This way we can always locate the match easily on the list by simply 
 * searching it on the hashtable, etc.
 * This structure ws mainly used to have all the data synced between the 
 * hashtable and the dllist for when we need to print all the matches present 
 * in the dtabase by input order. Using the same node for both ensures faster
 * deletion because we only have to search on the hashtable (which is faster 
 * overall) and we have the info for the list on the node so wecan delete the 
 * node on the list and rearrange it without needing to go through it.
 */


/* Node Structure for Match */
typedef struct m_node {
	Match match;
	struct m_node *ht_next;
	struct m_node *l_prev;
	struct m_node *l_next;
}* m_link;


/* 
 * Double Linked List Structure
 *  - To save the matches by input order 
 */
typedef struct M_DLL {
	m_link head;
	m_link tail;
} M_DLL;


/* 
 * Database Structure
 *  - Structure containing all the tables and lists used by the DBMS
 */
typedef struct db {
	/* (Hash)Table containing all the matches in the Database */
	m_link* matches_table;

	/* (Double Linked) List containing all the matches in the Database */
	M_DLL* matches_list;

	/* (Hash)Table containing all the matches in the Database */
	t_link* teams_table;
}* DB;

#endif /* DB_H */
