#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "list.h"

/* Initializes list. */
LinkedList init_list(){
	LinkedList list = can_fail_malloc(sizeof(struct masterNode));
	list->load = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

/* Creates game in the beginning of the list. */
Link add_node_before_list(Link next, ItemGame item){
	Link new = can_fail_malloc(sizeof(Node));
	new->item = item;
	new->next = next;
	return new;
}

/* Creates game in the end of the list. */
Link add_node_after_list(Link prev, ItemGame item){
	Link new, aux;
	if(prev == NULL){
		return add_node_before_list(prev, item);
	}
	new = can_fail_malloc(sizeof(Node));
	new->item = item;
	aux = prev->next;
	new->next = aux;
	prev->next = new;
	return new;
}

/* Deletes game from list. */
void delete_node_list(Link node){
	deleteItem_game(node->item);
	free(node);
}

/* Returns pointer to the game with the given name from list. */
ItemGame search_list(LinkedList list, char* name){
	Link t;
	for(t = list->head; t != NULL; t = t->next){
		if(strcmp(t->item->name, name) == 0){
			return t->item;
		}
	}
	return NULL;
}

/* Adds game to the end of the list. */
void append_list(LinkedList list, ItemGame item){
	Link newNode = add_node_after_list(list->tail, item);
	list->tail = newNode;
	if(list->head == NULL){
		list->head = newNode;
	}
	list->load++;
}

/* Removes element with given name from list. */
void remove_elem_list(LinkedList list, char* name){
	Link t, prev;
	for(t = list->head, prev = NULL; t != NULL;
		  prev = t, t = t->next){
		if(strcmp(name, t->item->name) == 0){
			if(t == list->head){
				list->head = t->next;
			}
			else{
				prev->next = t->next;
			}
			list->load--;
			delete_node_list(t);
			if(t == list->tail){
				list->tail = list->head;
			}
			break;
		}
	}
}

/* Print list layout. */
void show_list(LinkedList list, int counter){
	Link t;
	for(t = list->head; t != NULL; t = t->next){
		printf("%d ", counter);
		showItem_game(t->item);
	}
}

/* Delete list. */
void destroy_list(LinkedList list){
	Link t, aux;
	if(list == NULL){
		return;
	}
	if(list->load != 0){
		for(t = list->head, aux = list->head->next; t != NULL;
			  aux = t->next, delete_node_list(t), t = aux){}
	}
	free(list);
}
