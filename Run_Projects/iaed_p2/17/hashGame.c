#include "hashGame.h"

/* Unlike the teams' hash table, when a node is freed the game isn't, becuase
   it is freed in the list. Look at command_a to better understand this. */

/* Adds game to games' hash table's head. */
LinkGame push_game(LinkGame head, ItemGame item){
	LinkGame aux = new_node_game(item, head);
	return aux;
}

/* Deletes a given name from a games' hash table's head. */
LinkGame remove_elem_game(LinkGame head, char* name){
	LinkGame t, prev;
	for(t = head, prev = NULL; t != NULL;
		prev = t, t = t->next){
			if(strcmp(name, t->item->name) == 0){
				if(t == head){
					head = t->next;
				}
				else{
					prev->next = t->next;
				}
				free(t);
				return head;
			}
	}
	return head;
}

/* Returns pointer to the game with the given name from a games' hash table's
   head. */
ItemGame search_list_game(LinkGame head, char* name){
	LinkGame t;
	for(t = head; t != NULL; t = t->next){
		if(strcmp(t->item->name, name) == 0){
         return t->item;
      }
	}
	return NULL;
}

/* Deletes a given name from a games' hash table's head. */
void destroy_list_game(LinkGame head){
	LinkGame t, aux;
	if(head == NULL){
      return;
   }
	for(t = head, aux = head->next; t != NULL;
        aux = t->next, free(t), t = aux){}
}

/* Initializes games' hash table. */
LinkGame* HASHinit_game(){
	int i;
	LinkGame* heads = malloc(MH * sizeof(LinkGame));
	for(i = 0; i < MH; i++){
		heads[i] = NULL;
	}
	return heads;
}

/* Games' hash table's hash function. */
int hash_game(char* v){
   int h = 0;
   for(; *v != '\0'; v++){
      h = (CH*h + *v) % MH;
   }
   return h;
}

/* Creates game in games' hash table's head. */
LinkGame new_node_game(ItemGame item, LinkGame head){
	LinkGame x = malloc(sizeof(NodeGame));

	x->item = item;
	x->next = head;
	return x;
}

/* Inserts a given game in the games' hash table. */
void insert_game(LinkGame* heads, ItemGame item){
	int i = hash_game(item->name);
	heads[i] = push_game(heads[i], item);
}

/* Deletes a given name from games' hash table. */
void delete_game(LinkGame* heads, char* name){
	int i = hash_game(name);
	heads[i] = remove_elem_game(heads[i], name);
}

/* Returns pointer to the game with the given name from games' hash table. */
ItemGame search_game(LinkGame* heads, char* name){
	int i = hash_game(name);
	return search_list_game(heads[i], name);
}

/* Deletes games' hash table. */
void destroy_hash_game(LinkGame* heads){
	int i;
	for(i = 0; i < MH; i++){
		destroy_list_game(heads[i]);
	}
	free(heads);
}
