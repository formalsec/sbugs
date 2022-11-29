#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Games.h"

/* inicializes and allocates all the info needed for the game System */
void Init_Games(GS *gs){
	int i, M;
	gs->HTsize = THGsize;
	M = gs->HTsize;
	gs->number_games = 0;
	gs->headsgames = can_fail_malloc(M*sizeof(struct nodeG)); 
	for (i = 0; i < M; i++) gs->headsgames[i] = NULL;	
	gs->list = can_fail_malloc(sizeof(struct list));
	gs->list->head = NULL;
	gs->list->last = NULL;
}

/* inserts a pointer to  a game at the end of the list of games*/
pGNode add_lastListG(plist list, pGame game){
    pGNode nnode = can_fail_malloc(sizeof(struct GNode));
    nnode->next = NULL;
    nnode->prev = list->last;
    nnode->g = game;

    if(list->last)list->last->next = nnode;

    list->last = nnode;

    if(!list->head)
       list->head = nnode;

   	return nnode;
}

/* 
inserts the game as the tail of the double 
linked list and in the correct position in the hash table
*/
void STinsertG(GS *gs, pGame game){
	int i;
	pNode new = can_fail_malloc(sizeof(struct nodeG));
	new->gms = add_lastListG(gs->list, game);
	i = hash(game->name, gs->HTsize);
	new->next = gs->headsgames[i];
	gs->headsgames[i] = new;
}

/* 
if the game exits returns a pointer to the hash table node 
containing the game otherwise returns NULL
*/
pNode searchHTG(pNode list, char *name){
	pNode head;
	for (head = list;head; head = head->next)
		if (strcmp(head->gms->g->name, name) == 0)
			return head; 
		else{
			continue;
		}
	return NULL;
}

/* searches for a game in the System through the hash table */
pNode STsearchG(char *name, GS *gs){
	int i=hash(name, gs->HTsize);
	return searchHTG(gs->headsgames[i], name);
}

/* alters the number of wins of a team when a score is altered */
void change_wins(pGNode gms, int scoret1, int scoret2){
	if (gms->g->scoreteam1 > gms->g->scoreteam2){
			if(scoret1 == scoret2)
				gms->g->team1->wins -= 1; 
			
			else if(scoret1 < scoret2){
				gms->g->team1->wins -= 1; 
				gms->g->team2->wins += 1; 
			}
	}

	else if(gms->g->scoreteam1 < gms->g->scoreteam2){
		if(scoret1 > scoret2){
				gms->g->team1->wins += 1; 
				gms->g->team2->wins -= 1; 
		}

		else if(scoret1 == scoret2)
				gms->g->team2->wins -= 1;
	}

	else{
		if(scoret1 > scoret2)
			gms->g->team1->wins += 1; 

		else if(scoret1 < scoret2)
			gms->g->team2->wins += 1; 
	}
	
	gms->g->scoreteam1 = scoret1;	
	gms->g->scoreteam2 = scoret2;
}

/* 
Deleates a node from the hash table 
returning the altered hash table list 
*/
pNode remove_gameaux(pNode head, pGNode game){
	pNode t, prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
		
		if(t->gms == game) {
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			free(t->gms->g);
			free(t->gms);
			free(t);
			break;	
		}
	}
	return head;
}

/* 
	Deleates a node from the hash table and the list  
	returning the result of that operation 
*/
pNode remove_gamefinal(pNode head, pGNode game){
	pNode t, prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
		if(!t->gms)
			return head;
		if(t->gms == game) {
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			free(t->gms->g->name);
			free(t->gms->g);
			free(t->gms);
			free(t);
			break;	
		}
	}
	return head;
}

/* frees all the memory remaining related to the games */
void Stop_Games(GS *gs){
	int i;
	pGNode nodelist;

	while (gs->list->head){
		nodelist = gs->list->head->next;  
		i = hash(gs->list->head->g->name, gs->HTsize);
		gs->headsgames[i] = remove_gamefinal(gs->headsgames[i], gs->list->head);
		gs->list->head = nodelist;
	}
	
	free(gs->headsgames);
	free(gs->list);
}