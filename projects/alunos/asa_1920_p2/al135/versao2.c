#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ------------------------------------------------ */

int result = 0;
long offset = 0;

typedef struct cross {
	int tipo; /* 0->nenhum 1->mercado 2->cidadao 3->ambos */
	int visited;
	int parent_avn;	/*substituir por Pair struct*/
	int parent_rua; /*substituir por Pair struct*/
} *Cross; 

typedef struct pair {
	int avn, rua;
} *Pair;


typedef struct node {
	Pair coord;
	struct node *next;
} *link;

typedef struct queue {
	link head;
	link tail;
	int size; 
} *queue_t;

/* ------------------------------------------------ */

/*
 *	|---------------------------------|
 *	|------------| QUEUE |------------|
 *	|---------------------------------|
 */

link newNode(Pair coord, link head) {
	link x = (link) can_fail_malloc(sizeof(struct node));
	x->coord = coord;
	x->next = head;
	return x;
}

void initQueue(queue_t queue) {
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
}

bool emptyQueue(queue_t queue) {
	return queue->head == NULL;
}

void push(queue_t queue, Pair coord) {
	if (queue->head == NULL){
		queue->head = (queue->tail = newNode(coord, queue->head));
		return;
	}
	queue->tail->next = newNode( coord, queue->tail->next);
	queue->tail = queue->tail->next;
	(queue->size)++;
}

Pair pop(queue_t queue) {
	link x;
	Pair coord;

	coord = queue->head->coord;

	x = queue->head->next;
	free(queue->head);
	queue->head = x;

	(queue->size)--;
	return coord;
}

/* ------------------------------------------------ */

void debug(Cross** cross_table, int n_avn, int n_ruas){
	int i,j;

	for(i = 0; i < n_ruas; i++){
		puts("");
		for(j = 0; j < n_avn; j++){
			printf("[ %d | %d ]  ", cross_table[j][i]->tipo, cross_table[j][i]->visited);
		}
	}

	puts("");
}

/* ------------------------------------------------ */


bool bfs(Cross** cross_table, int avn, int rua , int i, int n_avn, int n_ruas, int n_cid, bool verifica){

	int x, y;
	int a, r;
	int k, j;

	bool found = false;

	bool ver = verifica;


	Pair coordenates 	= (Pair) can_fail_malloc(sizeof(struct pair));
	Pair current, child, market, destination, maybe_path, maybe_parent;

	Cross temp;
	

	queue_t queue = (queue_t) can_fail_malloc(sizeof(struct queue));
	initQueue(queue);

	queue_t potential = (queue_t) can_fail_malloc(sizeof(struct queue));
	initQueue(potential);


	Cross cid = cross_table[avn][rua];

	if (cid->visited != -1)
		cid->visited = i;


	coordenates->avn = avn;
	coordenates->rua = rua;
	push(queue,coordenates);


	
	while (!emptyQueue(queue)){
		current = pop(queue);
		x = current->avn;
		y = current->rua;

		if (cross_table[x][y]->visited == -1)
			break;

		if (cross_table[x][y]->tipo == 3){
			/*printf("Match: [%d | %d] -> self \n", x+1, y+1);*/
			cross_table[x][y]->visited = -1;
			result++;
			return true;
		}


		int c; 
		for (c = 0; c < 4; c++){
			if (c == 0){
				k = x+1;
				j = y;
			}
			else{
				if (c == 1){
					k = x-1;
					j = y;
				}
				else{
					if (c == 2){
						k = x;
						j = y-1;
					}
					else{
						k = x;
						j = y+1;
					}
				}
			}

			if (k >= n_avn || k < 0)
				k = x;
			
			if (j >= n_ruas || j < 0)
				j = y;
			

			if (cross_table[k][j]->tipo == 1){

				if (cross_table[k][j]->visited != i){
					market = (Pair) can_fail_malloc(sizeof(struct pair));
					market->avn = k;
					market->rua = j;

					maybe_parent = (Pair) can_fail_malloc(sizeof(struct pair));
					maybe_parent->avn = x;
					maybe_parent->rua = y;



					push(potential, market);
					push(potential, maybe_parent);

					if (cross_table[k][j]->visited != -1){

						cross_table[k][j]->parent_avn = x;
						cross_table[k][j]->parent_rua = y;

						
						/*printf("Match: [%d | %d] -> [%d | %d]\n", avn+1, rua+1, k+1, j+1);*/

						while(true){
							temp = cross_table[k][j];
							cross_table[k][j]->visited = -1;
							if (!(k == avn && j == rua)){
								k = temp->parent_avn;
								j = temp->parent_rua;
							}
							else
								break;
							
						}


						if(!ver)
							result++;

						while (!emptyQueue(potential)) {
							pop(potential);
							pop(potential);
						}
						free(potential);

						return true;
					}
					
				}
			}
			else{
				if(cross_table[k][j]->visited != i && cross_table[k][j]->tipo ==0 && cross_table[k][j]->visited != -1){
					cross_table[k][j]->parent_avn = x;
					cross_table[k][j]->parent_rua = y;
					cross_table[k][j]->visited = i;

					child = (Pair) can_fail_malloc(sizeof(struct pair));
					child->avn = k;
					child->rua = j;
					push(queue, child);
				}
			}

			

		}

	}




	while(!emptyQueue(potential)){
		destination = pop(potential);
		maybe_path = pop(potential);


		if(!ver){

			a = destination->avn;
			r = destination->rua;
			k = cross_table[a][r]->parent_avn;
			j = cross_table[a][r]->parent_rua;


			while(true){
				temp = cross_table[k][j];
				cross_table[k][j]->visited = n_cid + offset;
				if (cross_table[k][j]->tipo!=2){
					k = temp->parent_avn;
					j = temp->parent_rua;
				}
				else
					break;
				
			}

			found = bfs(cross_table, k, j, n_cid + offset, n_avn, n_ruas, n_cid, true);
			if(found){
				k = maybe_path->avn;
				j = maybe_path->rua;
				while(true){
					temp = cross_table[k][j];
					cross_table[k][j]->visited = -1;
					if (cross_table[k][j]->tipo!=2){
						k = temp->parent_avn;
						j = temp->parent_rua;
					}
					else{
						/*printf("Match: [%d | %d] -> [%d | %d]\n", k+1, j+1, a+1, r+1);*/
						result++;
						break;
					}
					
				}
			}
			else{
				a = destination->avn;
				r = destination->rua;
				k = cross_table[a][r]->parent_avn;
				j = cross_table[a][r]->parent_rua;
				while(true){
					temp = cross_table[k][j];
					cross_table[k][j]->visited = -1;
					if (cross_table[k][j]->tipo!=2){
						k = temp->parent_avn;
						j = temp->parent_rua;
					}
					else
						break;
					
				}
			}

			offset++;

		}


	}
	free(potential);
		



	while (!emptyQueue(queue)) {
		pop(queue);
	}
	free(queue);

	return false;
}



/* ------------------------------------------------ */

int main(int argc, char** argv) {

	int n_ruas, n_avn, n_merc, n_cid;

	int i, j, x, y;


	if (scanf("%d %d", &n_avn, &n_ruas) != 2){
		perror("error reading file");
		return 1;
	}


	if (scanf("%d %d", &n_merc, &n_cid) != 2){
		perror("error reading file");
		return 1;
	}


	Cross** cross_table = (Cross**) can_fail_malloc(n_avn * sizeof(Cross*));

	for(i = 0; i < n_avn; i++){
		cross_table[i] = (Cross*) can_fail_malloc(n_ruas * sizeof(Cross));
		for(j = 0; j < n_ruas; j++){
			cross_table[i][j] = (Cross) can_fail_malloc(sizeof(struct cross));
			cross_table[i][j]->tipo = 0;
			cross_table[i][j]->visited = -2;
		}
	}

	Pair* citizens = (Pair*) can_fail_malloc(n_cid * sizeof(Pair));

	for(i = 0; i < n_merc; i++){
		if (scanf("%d %d", &x, &y) != 2){
			perror("error reading file");
			return 1;
		}
		cross_table[x-1][y-1]->tipo = 1;
	}


	for(i = 0; i < n_cid; i++){
		if (scanf("%d %d", &x, &y) != 2){
			perror("error reading file");
			return 1;
		}
		if(cross_table[x-1][y-1]->tipo == 1 || cross_table[x-1][y-1]->tipo == 3){
			cross_table[x-1][y-1]->tipo = 3;
		}
		else
			cross_table[x-1][y-1]->tipo = 2;

		citizens[i] = (Pair) can_fail_malloc(sizeof(struct pair));
		citizens[i]->avn = x-1;
		citizens[i]->rua = y-1;
	}


	/*debug(cross_table, n_avn, n_ruas);*/

	/*puts ("____\n");*/

	for(i = 0; i < n_cid; i++){
		bfs(cross_table, citizens[i]->avn, citizens[i]->rua, i, n_avn, n_ruas, n_cid, false);
	}

	/*
	debug(cross_table, n_avn, n_ruas);
	puts("\nResultado:");
	*/

	printf("%d\n", result);


	return 0;

}