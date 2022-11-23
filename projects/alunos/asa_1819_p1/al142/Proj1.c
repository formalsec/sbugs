#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <time.h>

typedef struct list{
	int id;
	struct list *next;
}*list;

void dfs(int u, int N, int *maior, int orig, int *time, list *lig, int *pi, int *d, int *lowlink, int* quebra, int* outnum);
void dfs2(int u, int N, list *lig, int *visited, int *Nnodos, int *quebra);

int cmp(const void* a, const void* b){
	return ( *(int*)a - *(int*)b);
}

void addlist(list l, int id){

	if(l->id == -1){
		l->id = id;
		return;
	}

	list new_list = can_fail_malloc(sizeof(struct list*));
	new_list->id = id;
	new_list->next = l->next;

	l->next = new_list;
	return;
}

int main(){

	/* INPUT */


	int N, M;
	int R=0, C=0, m=0;
	int i, aux1, aux2;
	int time=0, maior, outnum;

	scanf("%d", &N);
	scanf("%d", &M);

	int *subredes = can_fail_malloc(N*sizeof(int));
	int *pi = can_fail_malloc(N*sizeof(int));
	int *d = can_fail_malloc(N*sizeof(int));
	int *lowlink = can_fail_malloc(N*sizeof(int));
	int *quebra = can_fail_malloc(N*sizeof(int));
	int *visited = can_fail_malloc(N*sizeof(int));


	list *lig = can_fail_malloc(N * sizeof(list));
	for (i=0; i<N; i++)
		lig[i] = can_fail_malloc(sizeof(struct list));


	
	for (i=0; i<N; i++){
		pi[i] = -1;
		visited[i] = 0;
		d[i] = -1;
		quebra[i] = 0;
		lig[i]->id = -1;
		lig[i]->next = NULL;
	}

	char *buffer = can_fail_malloc(2*N + 1);
	fgets(buffer, 2*N + 1, stdin);


	char *token;

	while(fgets(buffer, 2*N + 1, stdin) != NULL){

		token = strtok(buffer, " ");
		aux1 = atoi(token);

		token = strtok(NULL, " ");
		aux2 = atoi(token);

		addlist(lig[aux1-1], aux2-1);
		addlist(lig[aux2-1], aux1-1);
	}



	/* INPUT OVER */

	/* DFS 1 */

	for(i=0; i<N; i++){
		maior = 0;
		if(d[i] == -1){
			outnum=0;
			dfs(i, N, &maior, i, &time, lig, pi, d, lowlink, quebra, &outnum);
			subredes[R] = maior+1;
			R++;

			if(outnum > 1)
				quebra[i] = 1;
			else
				quebra[i] = 0;
		}

		if(quebra[i])
			C++;
	}

	/* DFS 2 */

	int Nnodos;

	for(i=0; i<N; i++){
		if(quebra[i]) continue;
		Nnodos=0;

		if(visited[i] == 0){
			dfs2(i, N, lig, visited, &Nnodos, quebra);
			if(Nnodos > m)
				m = Nnodos;
		}
	}

	printf("%d\n", R);

	qsort(subredes, R, sizeof(int), cmp);

	for (i=0; i<R; i++){
		if(i!=0) printf(" ");
		printf("%d", subredes[i]);
	}
	printf("\n%d\n", C);
	printf("%d\n", m);

	return 0;
}

void dfs(int u, int N, int *maior, int orig, int *time, list *lig, int *pi, int *d, int *lowlink, int* quebra, int* outnum){

	int j;
	d[u] = *time;
	lowlink[u] = *time;
	*time += 1;

	if (orig == pi[u])
		*outnum += 1;

	list l = lig[u];
	while(l != NULL){

		if (l->id == -1)
			break;

		j = l->id;
		if (pi[u] == j){ 
			l = l->next;
			continue;
		}
		if (d[j] == -1){
			pi[j] = u;
			dfs(j, N, maior, orig, time, lig, pi, d, lowlink, quebra, outnum);

			if (d[u] <= lowlink[j])
				quebra[u] = 1;

			if (lowlink[u] >= lowlink[j])
				lowlink[u] = lowlink[j];
		}

		if (lowlink[u] >= d[j])
			lowlink[u] = d[j];

		l = l->next;

	}

	if (u>*maior)
		*maior = u;
}

void dfs2(int u, int N, list *lig, int *visited, int *Nnodos, int* quebra){
	int j;
	*Nnodos += 1;
	visited[u] = 1;

	list l = lig[u];
	while(l != NULL){
		j = l->id;
		if(quebra[j]){
			l = l->next;
			continue;
		}

		if (visited[j] == 0){
			dfs2(j, N, lig, visited, Nnodos, quebra);
		}

		l = l->next;
	}
}
