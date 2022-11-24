#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "data_structures.h"

/*-------------------------------------------------------------------------------------------------
	List functions
-------------------------------------------------------------------------------------------------*/

/* Creates a new node */
node * NEW(char *text){
	node *x = can_fail_malloc(sizeof(node));
	x->text = text;
	x->next = NULL;
	x->prev = NULL;
	return x;
}

/* Inserts a new node at the end of the list */
node ** insert_END(node **ends, char *text){
	node *head = ends[HEAD];
	node *tail = ends[TAIL];
	/* empty list */
	if(head == NULL){
		head = NEW(text);
		tail = head;
		ends[HEAD] = head;
		ends[TAIL] = tail;
		return ends;
	}
	/* non empty list */
	tail->next = NEW(text);
	tail->next->prev = tail;
	tail = tail->next;

	ends[HEAD] = head;
	ends[TAIL] = tail;
	return ends;
}

/* Deletes a node of a list */
node ** lst_delete(node **ends, char *text){
	node *t;
	node *head = ends[HEAD];
	node *tail = ends[TAIL];
	for(t = head; t != NULL; t = t->next){
		if(strcmp(t->text, text) == 0){
			if(t == head && t == tail){
				head = t->next;
				tail = t->next;
			}
			else if(t == head){
				head = t->next;
				if(head != NULL)
					head->prev = NULL;
			}
			else if(t == tail){
				tail = t->prev;
				tail->next = NULL;
			}
			else{
				t->prev->next = t->next;
				t->next->prev = t->prev;
			}
			free(t);
			break;
		}
	}
	ends[HEAD] = head;
	ends[TAIL] = tail;
	return ends;
}

/* Frees a list */
void free_list(node **ends){
	node *head = ends[HEAD];
	node *t;
	node *next;

	if(head == NULL){
		free(ends);
		return;
	}

	for(t = head, next = t->next; next != NULL; t = next, next = next->next){
		free(t);
	}
	free(t);
	free(ends);
}

/*-------------------------------------------------------------------------------------------------
	Hash tables functions
-------------------------------------------------------------------------------------------------*/

/* Taken from slides */
int hash(char *v, int M){
	int h , a = 31415, b = 27183;

	for(h=0; *v != '\0'; v++, a = a*b % (M-1))
		h = (a*h + *v) % M;


	return abs(h);
}

/* Initializes the hash table that stores all games
   and returns it's pointer */
Game ** HT_G_init(Game **G, int *G_sz){
	int i;
	int sz = *G_sz;
	
	G = can_fail_malloc(sz * sizeof(Game));
	
	for (i=0; i < sz; i++)
		G[i] = NULL;
	
	return G;
}
 
/* Initializes the hash table that stores all teams
   and returns it's pointer */
Team ** HT_T_init(Team **T, int *T_sz){
	int i;
	int sz = *T_sz;
	
	T = can_fail_malloc(sz * sizeof(Team));
	
	for (i=0; i < sz; i++)
		T[i] = NULL;
	
	return T;
}

/* Frees G */
void HT_G_free(Game **G, int *G_sz){
	int i;
	int sz = *G_sz;
	
	for(i=0; i < sz; i++){
		if(G[i] != NULL){
			free(G[i]->n);
			free(G[i]->t1);
			free(G[i]->t2);
			free(G[i]);
		}
	}
	free(G);
}

/* Frees T */
void HT_T_free(Team **T, int *T_sz){
	int i;
	int sz = *T_sz;
	
	for(i=0; i < sz; i++){
		if(T[i] != NULL){
			free(T[i]->n);
			free(T[i]);
		}
	}
	free(T);
}

/* Expands G and returns the pointer to the updated hash table */
Game ** HT_G_expand(Game **G, int *G_sz){
	int i;
	Game **temp_G = G;	/* temporary G hash table */
	
	/* reinitializes G with double the size */
	*G_sz *= 2;
	G = HT_G_init(G, G_sz);
	/* refills the G hash table */
	for(i=0; i < *G_sz/2; i++){
		if(temp_G[i] != NULL){
			HT_G_insert(temp_G[i], G, G_sz);
		}
	}
	free(temp_G);
	
	return G;
}

/* Expands T and returns the pointer to the updated hash table */
Team ** HT_T_expand(Team **T, int *T_sz, int *T_n){
	int i;
	Team **temp_T = T;	/* temporary T hash table */
	

	/* reinitializes T with double the size */
	*T_sz *= 2;
	T = HT_T_init(T, T_sz);
	/* refills the T hash table */
	for(i=0; i < *T_sz/2; i++)
		if(temp_T[i] != NULL)
			HT_T_insert(temp_T[i], T, T_sz, T_n);
	
	free(temp_T);

	return T;
}

/* Inserts a game in G */
void HT_G_insert(Game *g, Game **G, int *G_sz){
	int sz = *G_sz;
	int i = hash(g->n, sz);

	while(G[i] != NULL)
		i = (i+1) % sz;
	G[i] = g;
}

/* Inserts a team in T */
Team ** HT_T_insert(Team *t, Team **T, int *T_sz, int *T_n){
	int sz = *T_sz;
	int i = hash(t->n, sz);

	while(T[i] != NULL){
		i = (i+1) % sz;
	}
	T[i] = t;

	if(*T_n > *T_sz/2){
		T = HT_T_expand(T, T_sz, T_n);
	}

	return T;

}

/* Searches for a game in G given its name and returns it's pointer */
Game * HT_G_search(char *name, Game **G, int *G_sz){
	int sz = *G_sz;
	int i = hash(name, sz);
	
	while(G[i] != NULL){
		if(strcmp(G[i]->n, name) == 0){
			return G[i];
		}
		else
			i = (i+1) % sz;
	}
	return NULL;
}

/* Searches for a team in T given its name and returns it's pointer */
Team * HT_T_search(char *name, Team **T, int *T_sz){
	int sz = *T_sz;
	int i = hash(name, sz);

	while(T[i] != NULL){
		if(strcmp(T[i]->n, name) == 0){
			return T[i];
		}
		else
			i = (i+1) % sz;
	}
	return NULL;
}

/* Deletes a game in G given it's name */
void HT_G_delete(char *name, Game **G, int *G_sz){
	Game *g;
	int sz = *G_sz;
	int j;
	int i = hash(name, sz);
	
	/* search */
	while(G[i] != NULL){
		if (strcmp(G[i]->n, name) == 0) 
			break;
		else i = (i+1) % sz;
	}
	if (G[i] == NULL) return;

	/* frees memory and makes the changed position point to NULL */
	free(G[i]->n); 
	free(G[i]->t1); 
	free(G[i]->t2); 
	free(G[i]); 
	G[i] = NULL;
	
	/* reinserts the following elements until it finds NULL */
	for(j=(i+1) % sz; G[j] != NULL; j = (j+1) % sz){
		g = G[j];
		G[j] = NULL;
		HT_G_insert(g, G, G_sz);
	}
}