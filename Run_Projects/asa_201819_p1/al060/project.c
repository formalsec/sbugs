#include <stdio.h>
#include <stdlib.h>

#define GREY -1
#define WHITE 0
#define BLACK 1


/*#####################################################*/
/*						Estruturas					   */
/*#####################################################*/

typedef struct Router{
	int id;
	int l_size;
	int *ligacoes;
	int state;
	int weak;
	int parent;
	int l_time;
	int d_time;
} Router;

typedef struct Network{
	int num_routers;
	int num_ligacoes;
	Router *routers;
} Network;

/*######################################################*/

/*Protótipos*/
void createNetwork(int n_routers, int n_ligacoes, Network *n);
void stronglyConnectedRouters(Network *n);
void weaknessPoints(Network *n);
void weaknessPointsAux(Network *n, int v, int *t);
void biggestSubNetwork(Network *n);

/*Funcoes auxiliares*/
int sort(const void * elem1, const void * elem2){
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int min(int a,int b)
{
    return(a < b ? a : b);
}

/*########################################################*/

int main(){

	Network *n = malloc(sizeof(Network));
	int n_routers, n_ligacoes, id1, id2, s1, s2, i = 0;
	
	if(scanf("%d", &n_routers) != 1)
		exit(0);
	if(scanf("%d", &n_ligacoes) != 1)
		exit(0);
	createNetwork(n_routers, n_ligacoes, n);
	
	while(i < n->num_ligacoes){
		if (scanf("%d %d", &id1, &id2) != 2)
			exit(0);
		s1 = n->routers[id1 - 1].l_size;
		n->routers[id1 - 1].ligacoes[s1] = id2;
		n->routers[id1 - 1].l_size++;
		s2 = n->routers[id2 - 1].l_size;
		n->routers[id2 - 1].ligacoes[s2] = id1;
		n->routers[id2 - 1].l_size++;
		i++;
	}

	stronglyConnectedRouters(n);
	weaknessPoints(n);
	biggestSubNetwork(n);

	/*Libertacao da memoria*/
	for(i = 0; i < n->num_routers; i++){
		free(n->routers[i].ligacoes);
	}
	free(n->routers);
	free(n);

	return 0;
}

void createNetwork(int n_routers, int n_ligacoes, Network *n){

	int i;
	
	n->routers = malloc(n_routers * sizeof(Router));
	n->num_routers = n_routers;
	n->num_ligacoes = n_ligacoes;
	Router *tmp_r = malloc(sizeof(Router));
	
	for (i=0; i < n_routers;i++){
		
		tmp_r->id = i + 1;
		tmp_r->l_size = 0;
		tmp_r->ligacoes = malloc(n_routers * sizeof(int));
		tmp_r->parent = GREY;
        tmp_r->weak = WHITE;
		n->routers[i] = *tmp_r;
		
	}
	free(tmp_r);
}

void dfs(int v, Network *n, int *max, int *size){

	int i;
	
	n->routers[v].state = BLACK;
	*size = *size + 1;
	
	if(*max < v + 1)
		*max = v + 1;
	
	for(i = 0; i < n->routers[v].l_size; i++){
		if(n->routers[n->routers[v].ligacoes[i] - 1].state != BLACK){
			dfs(n->routers[v].ligacoes[i] - 1, n, max, size);
		}
	}
}

void stronglyConnectedRouters(Network *n){

	int i, scc = 1, max, j = 0;
	int *scc_id = malloc(scc * sizeof(int));
	
	for(i = 0; i < n->num_routers; i++)
		n->routers[i].state = WHITE;
	
	for (i = 0 ; i < n->num_routers ; i++){
		if (n->routers[i].state != BLACK){
			max = 0;
			scc_id = realloc(scc_id, scc * sizeof(int));
			dfs(i, n, &max, &j);
			scc_id[scc - 1] = max;
			scc++;
		}
	}

	printf("%d\n", scc -1);

	qsort(scc_id, scc-1, sizeof(int), sort);
	
	for(i = 0; i < scc - 1; i++){
		if(i!=scc-2)
			printf("%d ", scc_id[i]);
		else
			printf("%d",scc_id[i]);
	}
	printf("\n");

	free(scc_id);
}


void weaknessPointsAux(Network *n, int v, int *t){

    int children = 0, i = 0;
	n->routers[v].state = BLACK;
    *t = *t + 1;
    n->routers[v].d_time = n->routers[v].l_time = *t;

    while(i < n->routers[v].l_size){
		
		int adj = n->routers[v].ligacoes[i] - 1;

    	if(n->routers[adj].state == WHITE){
          children++;
          n->routers[adj].parent = v;
          weaknessPointsAux(n,adj, t);
		  
		  n->routers[v].l_time = min(n->routers[v].l_time,n->routers[adj].l_time);
		  
		  if(n->routers[v].parent == GREY && children > 1){
			n->routers[v].weak = BLACK;
		  }
		  
		  if(n->routers[v].parent != GREY && n->routers[v].d_time <= n->routers[adj].l_time){ 
		  	n->routers[v].weak = BLACK;
		  }           
        }

        else if(adj != n->routers[v].parent){
            n->routers[v].l_time = min(n->routers[v].l_time, n->routers[adj].d_time);
        }
		
		i++;
      }
}

void weaknessPoints(Network *n){

    int i, weak_p = 0, t = 0;

    
    for(i = 0; i < n->num_routers; i++){
        n->routers[i].state = WHITE;
    }

    for(i = 0; i < n->num_routers; i++){
        if(n->routers[i].state == WHITE){
            weaknessPointsAux(n, i, &t);
        }
    }
    
    for(i = 0 ; i < n->num_routers; i++){
        if(n->routers[i].weak == BLACK){
	  		weak_p++;
		}
    }
    printf("%d\n",weak_p);
}

void biggestSubNetwork(Network *n){
	
	int i, size, max_size = 0, k = 0;

	for(i = 0; i < n->num_routers; i++){
		if(n->routers[i].weak == BLACK)
			n->routers[i].state = BLACK;
		else
			n->routers[i].state = WHITE;
	}

	for(i = 0; i < n->num_routers; i++){
		if (n->routers[i].state != BLACK){
			size = 0;
			dfs(i, n, &k, &size);
			if(size > max_size)
				max_size = size;
		}
	}
	printf("%d\n", max_size);
}