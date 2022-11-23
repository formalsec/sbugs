#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct vertices {
    int index;
    int nota;
    int deg;
    int* gradegranters;
} grafo;

int max(int a, int b) {
    return a > b ? a : b;
}

int gradecalculator3000(int N, grafo* vertices){
	int i, j, granter;
	int changed = 0;
	int checker = 0;
	for (i = 0; i < N; i++){
		for (j = 0; j < vertices[i].deg; j++){
			granter = vertices[i].gradegranters[j];
			checker = vertices[i].nota;
			vertices[i].nota = max(vertices[i].nota, vertices[granter].nota);
			if (checker != vertices[i].nota){
				changed = 1;
			}
		}
	}
	if (changed != 0){
		gradecalculator3000(N, vertices);
	}
	return changed;
				
}


int main(){
	int N, M, i, O, D;

	if(scanf("%d,%d", &N, &M));
	else{
		printf("erro");
	}
	
	grafo* vertices;
	
	vertices = (grafo*) can_fail_malloc (sizeof(grafo)*N);
	
	for (i = 0; i < N; i++){
		vertices[i].index = i;
		if(scanf("%d", &vertices[i].nota));
		else{
					printf("erro");
		}
		vertices[i].deg = 0;
		vertices[i].gradegranters =(int*) can_fail_malloc (sizeof(int)*(vertices[i].deg+1));
	}
	for (i = 0; i < M; i++){
		if(scanf("%d %d", &O, &D));
		else{
					printf("erro");
		}
		
		vertices[O-1].gradegranters[vertices[O-1].deg] = D-1;
		vertices[O-1].deg++;
		vertices[O-1].gradegranters = (int*) can_fail_realloc (vertices[O-1].gradegranters, sizeof(int)*(vertices[O-1].deg+1));
	}
	/*em principio o grafo esta feito*/
	
	gradecalculator3000(N, vertices);
	
	for (i = 0; i < N; i++){
		printf("%d\n", vertices[i].nota);
	}
	
	/*for (i = 0; i < N; i++){
		free(vertices[i].gradegranters);
	}*/
	free(vertices);

	return 0;
	
	

}

	
