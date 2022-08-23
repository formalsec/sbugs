/*Andre Silva -84700
  Francisco Almeida - 81955 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WHITE 0
#define GREY 1
#define BLACK 2
#define oo  1000000000


typedef struct matrix m;
struct matrix{
 	int** mt;
 	int nodes;
};

typedef struct ligacao l;
struct ligacao{
 	int o;
 	int d;
};

int totalNodes, fornecedores, estacoes, numero_ligacoes, headBfs, tailBfs = 0;
int *predecessorBFS;
int *colorsBFS;
struct matrix* capacity;
struct matrix* flux;
struct matrix* transposed;
int *queueBFS;
int *queueDFS;
l* ligacoesAumentadas;

void matrixesInit();
int bfs(int start, int end);
int dequeue();
void enqueue(int node);
int fordFulkerson (int source, int sink);
int min (int x, int y);
void dfs(int i);
void freeAll();
int cmpfunc(const void *a, const void *b);

int main(){
	int j,o,d,c;
	scanf("%d %d %d", &fornecedores, &estacoes, &numero_ligacoes);
	totalNodes = fornecedores + estacoes*2 + 2;
	colorsBFS = (int*)malloc(sizeof(int)*totalNodes+2);
	queueBFS = (int*)malloc(sizeof(int)*totalNodes+2);
	predecessorBFS = (int*)malloc(sizeof(int)*totalNodes);
	capacity = (struct matrix*)malloc(sizeof(struct matrix));
	flux = (struct matrix*)malloc(sizeof(struct matrix));
	transposed = (struct matrix*)malloc(sizeof(struct matrix));
	queueDFS = (int*)malloc(sizeof(int)*totalNodes);
	ligacoesAumentadas = (l*)malloc(totalNodes * sizeof(struct ligacao));
	matrixesInit();

	int i=2;
	while(i<(fornecedores+2)){
		scanf("%d", &c);
		capacity->mt[0][i] = c;
		i++;
	}

	
	while(i<(fornecedores+estacoes+2)){
		scanf("%d", &c);
		capacity->mt[i][i+estacoes] = c;
		i++;
	}

	for(j = 0; j < numero_ligacoes; j++){
		scanf("%d %d %d", &o, &d, &c);
		if(o>=(totalNodes-estacoes*2)){
			capacity->mt[o+estacoes][d] = c;
		}
		else{
			capacity->mt[o][d] = c;
		}
	}
	int max_flow = fordFulkerson(0, 1);
	printf("%d\n", max_flow);

	for( i=0;i<totalNodes;i++){
		for( j=0;j<totalNodes;j++){
			transposed->mt[j][i] = capacity->mt[i][j];
		};
	}

	for(i=0; i<=totalNodes-1; i++){
		queueDFS[i] = 0;
	}

	dfs(1);
	
	int *estacoesAumentadas = (int*)malloc(sizeof(int)*totalNodes);
	int countE = 0;
	int countL = 0;
	for (i = 0; i <= totalNodes-1; ++i){
		if(queueDFS[i]==1){
			for(j=0; j <= totalNodes-1; j++){
				if(transposed->mt[i][j]!=0){
					if(queueDFS[j]==0){
						if(j!=0){
							if (transposed->mt[i][j] == flux->mt[j][i]){
								if(i>=(1+fornecedores+estacoes) && j>=(1+fornecedores+estacoes)){
									estacoesAumentadas[countE]= i-estacoes;
									countE++;
								}
								else if(j>=(2+fornecedores+estacoes)){
									ligacoesAumentadas[countL].o = j-estacoes;
									ligacoesAumentadas[countL].d = i;
									countL++;
								}

								else if(i>=(2+fornecedores+estacoes)  && (abs(i-j)==estacoes)){
									ligacoesAumentadas[countL].o = j;
									ligacoesAumentadas[countL].d = i-estacoes;	
									countL++;
								}

								else{
									ligacoesAumentadas[countL].o = j;
									ligacoesAumentadas[countL].d = i;	
									countL++;
								}
							}		
						}
						else{
							memset(ligacoesAumentadas, 0, countL*sizeof(l));
							break;
						}
					}
				}
			}
		}
	}

	qsort(ligacoesAumentadas, countL, sizeof(struct ligacao), cmpfunc );

	if(countE == 0){
		printf("\n");
	}
	else{
		for(i=0; i<=countE-1; i++){
			printf("%d",estacoesAumentadas[i]);
			if(i==countE-1){
				printf("\n");
			}
		}
	}
	for(i=0; i<=countL-1; i++){
		if(ligacoesAumentadas[i].o==0 && ligacoesAumentadas[i].d ==0){
			break;
		}
		printf("%d %d\n",ligacoesAumentadas[i].o, ligacoesAumentadas[i].d);
	}
	free(estacoesAumentadas);
	freeAll();
	return 0;

}

 void matrixesInit(){
	
	int i,z,j;
	capacity->mt = (int **)malloc(sizeof(int *) * totalNodes);
	flux->mt = (int **)malloc(sizeof(int *) * totalNodes);
	transposed->mt = (int **)malloc(sizeof(int *) * totalNodes);
	
	for(i=0; i<totalNodes; i++){
		capacity->mt[i] = (int *)malloc(totalNodes * sizeof(int));
		flux->mt[i] = (int *)malloc(totalNodes * sizeof(int));
		transposed->mt[i] = (int *)malloc(totalNodes * sizeof(int));

	} 

	for(z = 0; z <  totalNodes; z++){
      	for(j = 0; j < totalNodes; j++){
         	capacity->mt[z][j] = 0;
         	flux->mt[z][j] = 0;
         	transposed->mt[z][j] = 0;
        }
	}

}

int bfs(int start, int end){
	int i,j;
	for(i = 0; i <= totalNodes-1; i++){
		colorsBFS[i] = WHITE;
	}
	headBfs = tailBfs = 0;
	enqueue(start);
	predecessorBFS[start] = -1;
	while(headBfs != tailBfs){
		i = dequeue();
		for(j=0; j<=totalNodes-1; j++){
			if(colorsBFS[j]==WHITE && capacity->mt[i][j]-flux->mt[i][j]>0){
				enqueue(j);
				predecessorBFS[j] = i;
			}
		}
	}
	return colorsBFS[end] == BLACK;
}

void enqueue(int node){
	queueBFS[tailBfs] = node;
	tailBfs++;
	colorsBFS[node] = GREY;
}

int dequeue(){
	int node = queueBFS[headBfs];
	headBfs++;
	colorsBFS[node] = BLACK;

	return node;
}

int fordFulkerson (int source, int sink) {
    int u = 0;
    int max_flow = 0;
    /* While there exists an augmenting path,
     increment the flow along this path.*/
    while (bfs(source, sink)) {
        /* Determine the amount by which we can increment the flow.*/
		int increment = oo;
		for(u=sink; predecessorBFS[u]>=0; u=predecessorBFS[u]) {
	    	increment = min(increment,capacity->mt[predecessorBFS[u]][u]-flux->mt[predecessorBFS[u]][u]);
		}
        /*Now increment the flow. */
		for(u = sink; predecessorBFS[u]>=0; u=predecessorBFS[u]) {
	    	flux->mt[predecessorBFS[u]][u] += increment;
	    	flux->mt[u][predecessorBFS[u]] -= increment;
		}
		max_flow += increment;
    }
    /* No augmenting path anymore. We are done. */
    return max_flow;
}

int min (int x, int y) {
    return x<y ? x : y;  
}

void dfs(int node){
	int j;
	queueDFS[node] = 1;
	for(j = 0; j <= totalNodes-1; j++){
		if(queueDFS[j] == 0 && transposed->mt[node][j] != 0  && transposed->mt[node][j] != flux->mt[j][node]){			
			dfs(j);
		}
	}
}

void freeAll(){
	int i;
	for(i=0; i<totalNodes; i++){
		free(capacity->mt[i]);
		free(flux->mt[i]);
		free(transposed->mt[i]);
	} 
	free(capacity->mt);
	free(flux->mt);
	free(transposed->mt);

	free(colorsBFS);
	free(queueDFS);
	free(queueBFS);
	free(predecessorBFS);
	free(capacity);
	free(flux);
	free(transposed);
	free(ligacoesAumentadas);
}

int cmpfunc(const void *a, const void *b){
  const struct ligacao *ca = a;
  const struct ligacao *cb = b;

  if(ca->o == cb->o){
    return (ca->d - cb->d);
  }
  return (ca->o - cb->o);
}