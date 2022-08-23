/*+-----------------------------------------------------------+
  |  First Project  Analisys and Sythesys of Algorthims       |
  |-----------------------------------------------------------+
  |Programers : David Miranda (93697) & Joao Salgueiro (93725)|
  +-----------------------------------------------------------+*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int value;
	int done;
	int num_conections;
	int size;
	int *conections;
}node;

node **graph;
int *graph_val, stack_size, previous_size, min_val;
int current_index = 0;

void initinalizeGraph(int *N)
{
	graph = calloc(*N,sizeof(node));
}

node* createNode(int *val, int *N)
{
	node *dummy = malloc(sizeof(struct node));
	dummy -> value = *val;
	dummy -> done = 1; /* Equivalent to false */
	dummy -> num_conections = 0;
	if(*N < 50){  /*Otimizacao da alocacao da memoria */
		dummy -> conections = malloc(sizeof(int)*(*N));
		dummy -> size = *N;
	}
	else{
		dummy -> conections = malloc(sizeof(int)*50);
		dummy -> size = 50;
	}
	return dummy;
}

int parseArgs(int *N, int *M){
	int i, *val, *father_node, *son_node,pos = 0,key= 0, conects;
	val = malloc(sizeof(int));
	father_node = malloc(sizeof(int));
	son_node = malloc(sizeof(int));
	
	scanf("%d,%d",N, M);
	stack_size = *N;
	initinalizeGraph(N);
	graph_val = calloc(21,sizeof(int));

	for(i = 0; i < *N; i++){
		scanf("%d",val);

		graph_val[*val] = 1;
		if(*val > key)
		{
			key = *val;
			pos = i;
		}
		if(*val < min_val)
		{
			min_val = *val;
		}
		graph[i] = createNode(val,N);
	}

	for(i = 0; i < *M; i++){
		scanf("%d %d",son_node, father_node);
		conects = graph[*father_node - 1] -> num_conections;
		
		if(conects == graph[*father_node - 1] -> size - 1)
		{
			graph[*father_node - 1] -> conections = realloc(graph[*father_node - 1] -> conections,sizeof(int)*(conects + 50));
			graph[*father_node - 1] -> size += 50;
		}
		graph[*father_node - 1] -> conections[conects] = *son_node - 1;
		graph[*father_node - 1] -> num_conections ++;

	}
	free(val);
	free(father_node);
	free(son_node);
	return pos;
}

int min(int a, int b)
{
	return a > b ? b : a;
}

void propagate(int u)
{
	int v,i, max_connections;
	max_connections = graph[u] -> num_conections;
	graph[u] -> done = 0;
	for(i = 0; i < max_connections; i++)
	{
		v = graph[u] -> conections[i];

		if(graph[v] -> done == 1){
			if(graph[u] -> value > graph[v] -> value)
				graph[v] -> value = graph[u] -> value;
			propagate(v);
		}
	}
	stack_size--;
}

void free_all(int *N)
{
	int i;
	for(i = 0; i < *N; i++)
	{
		free(graph[i] -> conections);
		free(graph[i]);
	}
	free(graph);
	free(graph_val);
}


int main(int argc, char const *argv[])
{	
	int i,big_node, max_val,e;
	int *N, *M;
	N = malloc(sizeof(int));
	M = malloc(sizeof(int));

	big_node = parseArgs(N, M);

	max_val = graph[big_node] -> value;
	propagate(big_node);

	for(i = max_val; i >= min_val; i--)
	{
		if(graph_val[i] == 1)
		{
			for(e = 0; e < *N; e++)
			{
				if(graph[e] -> value == i && graph[e] -> done == 1)
				{
					propagate(e);
				}
				if(stack_size == 0)
					break;
			}
		}
		if(stack_size == 0)
			break;
	}

	for(i = 0; i < *N;i++){
		printf("%d\n",graph[i]->value);
	}

	free(M);
	free_all(N);
	free(N);

	return 0;
}