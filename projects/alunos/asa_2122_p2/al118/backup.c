#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int addEdge(int u, int v);
void prepara();
int dfs();
int visit(int node);
int novo_visit(int node);
void prepara_again();
int limpar_ancestrais();
void swap();
void bubbleSort(int arr[], int n);

typedef struct {
	int cor;
	int nfilhos;
	int* filhos;
	int count;
} Node;

typedef struct {
	int cor;
	int nfilhos;
	int* filhos;
} NodeOutro;

NodeOutro* grafo;
Node* transposed;
int* ancestrais;
int* finais;
int numero_ancestrais = 0;
int contador3 = 0;
int nodes, edges, invalid = 0;

int main() {
	
	int i, vertice1, vertice2, primeiro, segundo;

	scanf("%d %d", &vertice1, &vertice2);
	scanf("%d %d", &nodes, &edges);

	grafo = can_fail_malloc(sizeof(Node)*nodes);
	transposed = can_fail_malloc(sizeof(Node)*nodes);
	ancestrais = can_fail_malloc(sizeof(int));
	finais = can_fail_malloc(sizeof(int));

	prepara();

	for(i=0; i<edges; i++) {
		scanf("%d %d", &primeiro, &segundo);
		addEdge(primeiro, segundo);
	}
    
	dfs();
	
	if(invalid == 1) {
		printf("0\n");
		return 0;
	}

    novo_visit(vertice1);

	prepara_again();

    novo_visit(vertice2);
	
	if(numero_ancestrais==0) {
	    printf("-\n");
	    return 0;
	}

	limpar_ancestrais();
	
	bubbleSort(finais, contador3);
	

	for(i=0; i<contador3; i++) {
	    printf("%d ", finais[i]);
	}
	
	printf("\n");

	return 0;
}

int addEdge(int u, int v) {
	
	if(grafo[u].nfilhos == 0) {
		grafo[u].nfilhos = 1;
		grafo[u].filhos = can_fail_malloc(sizeof(int));
		grafo[u].filhos[0] = v;
	}
	
	if(transposed[v].nfilhos == 0) {
	    transposed[v].nfilhos = 1;
		transposed[v].filhos = can_fail_malloc(sizeof(int));
		transposed[v].filhos[0] = u;
	}

	if(grafo[u].nfilhos>0){
		int i;

		grafo[u].nfilhos++;

		int*carry1 = can_fail_malloc(sizeof(int)*grafo[u].nfilhos);

		for(i=0; i<(grafo[u].nfilhos-1); i++) {
			carry1[i] = grafo[u].filhos[i];
		}
		
		carry1[grafo[u].nfilhos-1] = v;

		grafo[u].filhos = carry1;

	}
	
	
	if(transposed[v].nfilhos>0){
	    int i;
	    
	    transposed[v].nfilhos++;
	    
	    int*carry2 = can_fail_malloc(sizeof(int)*transposed[v].nfilhos);
	    
	    for(i=0; i<(transposed[v].nfilhos-1); i++) {
			carry2[i] = transposed[v].filhos[i];
		}
		
		carry2[transposed[v].nfilhos-1] = u;
		transposed[v].filhos = carry2;
	}
	
	return 0;
}

void prepara() {

	int i;

	for(i=1; i<=nodes; i++) {
		grafo[i].cor = WHITE;
		grafo[i].nfilhos = 0;
		grafo[i].filhos = NULL;
		transposed[i].cor = WHITE;
		transposed[i].nfilhos = 0;
		transposed[i].filhos = NULL;
		transposed[i].count = 0;
	}
}

int dfs() {
	
	int i;

	for(i=1; i<= nodes; i++){
		if(grafo[i].cor == WHITE) {
			visit(i);
		}
	}
	return 0;
}

int visit(int node) {

	grafo[node].cor = GRAY;
	int i;

	for(i=0; i<grafo[node].nfilhos; i++) {
		if(grafo[grafo[node].filhos[i]].cor == GRAY) {
			invalid = 1;
		}

		else if(grafo[grafo[node].filhos[i]].cor == WHITE) {
			visit(grafo[node].filhos[i]);
		}
	}

	grafo[node].cor = BLACK;

	return 0;
}

int novo_visit(int node) {

    int i, j;
    
    transposed[node].cor = GRAY;
    transposed[node].count++;
    
    if(transposed[node].count == 2) {
        numero_ancestrais++;
        int*carry3 = can_fail_malloc(sizeof(int)*numero_ancestrais);
        for(j=0; j<numero_ancestrais; j++) {
		    carry3[j] = ancestrais[j];
		}
		carry3[numero_ancestrais-1] = node;
		ancestrais = carry3;
    }
    
    for(i=0; i<transposed[node].nfilhos; i++) {
    	if(transposed[transposed[node].filhos[i]].cor == WHITE) {
    		novo_visit(transposed[node].filhos[i]);
    	}
    }

	transposed[node].cor = BLACK;

	return 0;
}

void prepara_again() {

	int i;

	for(i=1; i<=nodes; i++) {
		transposed[i].cor = WHITE;
	}
}

int limpar_ancestrais() {
    
    int i, j, k, l;
    
    for(i=0; i<numero_ancestrais; i++) {
        
        int helper = ancestrais[i];
        
        int contador2 = 0;
        int contador = 0;
        
        for(j=0; j<grafo[helper].nfilhos; j++) {
            for(k=0; k<numero_ancestrais; k++) {
                if(grafo[helper].filhos[j] != ancestrais[k]) {
                    contador++;
                }
            }
            if(contador == numero_ancestrais) {
                contador2++;
            }
            contador = 0;
        }
        
        if(contador2 == grafo[helper].nfilhos) {
            contador3++;
            int*carry4 = can_fail_malloc(sizeof(int)*contador3);
            for(l=0; l <contador3-1; l++) {
                carry4[l] = finais[l];
            }
            carry4[contador3-1] = helper;
            finais = carry4;
        }
        contador2 = 0;
    }
    
    return 0;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
   int i, j;
   bool swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = false;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(&arr[j], &arr[j+1]);
           swapped = true;
        }
     }
  
     if (swapped == false)
        break;
   }
}