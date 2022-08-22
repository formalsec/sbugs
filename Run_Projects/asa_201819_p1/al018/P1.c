#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _lista{
	struct _lista * next;
	int valor;
	int ligacao;
}lista;



lista * cria_lista ();
void inserir_inicio(lista * original, int inteiro);
void DFS (lista * grafo[], int numero_routers);
int visit_routers(lista *grafo[], int router, int *isVisited);
int DFS_recursive(lista *grafo[], int router, int *isVisited, int *maxs, int routers_counter);
int max_connections(lista *grafo[], int router, int *isVisited);



lista * cria_lista (){
	
	lista * novo = (lista*)malloc(sizeof(lista));
	novo->next = NULL;
	return novo;
}



void inserir_inicio(lista * original, int inteiro){
	lista * aux = original->next;
	lista * novo;
	novo = (lista*)malloc(sizeof(lista));
	novo->valor = inteiro;
	novo->next = aux;
	original->next=novo;
}



void DFS (lista * grafo[], int numero_routers){

	int routers_counter = 0, articulation_points = 0, max_connection_size = 0, i, j, counter;
	int isVisited[numero_routers],rootsChecked[numero_routers], maxs[numero_routers], articular_point[numero_routers];
	memset(isVisited, 0, sizeof(isVisited));
	memset(rootsChecked, 0, sizeof(rootsChecked));
	memset(maxs, 0, sizeof(maxs));
	memset(articular_point, 0, sizeof(articular_point));

	for (i=0;i<numero_routers;i++){
		if (!isVisited[i]){
			isVisited[i] = 1;
			counter = DFS_recursive(grafo, i, isVisited, maxs, routers_counter);
			routers_counter++;
			if (counter > 1) {
				articulation_points++;
				articular_point[i] = 1;
			}
			rootsChecked[i] = 1;
		}
	}

	for (i = 0; i<numero_routers; i++){
		if (!rootsChecked[i]){
			memset(isVisited, 0, sizeof(isVisited));
			isVisited[i] = 1;
			if (visit_routers(grafo, i, isVisited) > 1) {
				articulation_points++;
				articular_point[i] = 1;
			}
			rootsChecked[i] = 1;
		}
	}

	for (i=0;i<numero_routers;i++){
		if (!articular_point[i]){
			articular_point[i] = 1;
			int connection_size = max_connections(grafo, i, articular_point);
			if(connection_size > max_connection_size) max_connection_size = connection_size;
		}
	}

	printf("%d\n",routers_counter);
	
	for (i=0;i<routers_counter;i++){
		int index = 0;
		int min = numero_routers + 1;
		for (j = 0;j<routers_counter; j++){
			if(maxs[j] != -1){
				if(min > maxs[j]){
					min = maxs[j];
					index = j;
				}
			}
		}
		if(i==0) printf("%d",min);
		else printf(" %d",min);
		maxs[index] = -1;
	}
	
	printf("\n%d\n", articulation_points);
	printf("%d\n", max_connection_size);
}



int DFS_recursive(lista *grafo[], int router, int *isVisited, int *maxs, int routers_counter){
	
	int counter = 0;
	lista * aux = grafo[router]->next;
	
	while (aux != NULL){
		if (!isVisited[aux->valor-1]){
			isVisited[aux->valor-1] = 1;
			if(maxs[routers_counter] < aux->valor) maxs[routers_counter] = aux->valor;
			DFS_recursive(grafo, aux->valor-1, isVisited, maxs, routers_counter);
			counter++;
		}
		aux = aux->next;
	}
	return counter;
}



int visit_routers(lista *grafo[], int router, int *isVisited){
	
	int counter = 0;
	lista * aux = grafo[router]->next;
	
	while (aux != NULL){
		if (!isVisited[aux->valor-1]){
			isVisited[aux->valor-1] = 1;
			visit_routers(grafo, aux->valor-1, isVisited);
			counter++;
		}
		aux = aux->next;
	}
	return counter;
}



int max_connections(lista *grafo[], int router, int *articular_point){
	
	int counter = 1;
	lista * aux = grafo[router]->next;
	while (aux != NULL){
		if (!articular_point[aux->valor-1]){
			articular_point[aux->valor-1] = 1;
			counter += max_connections(grafo, aux->valor-1, articular_point);
		}
		aux = aux->next;
	}
	return counter;
}



int main (){
	
	int numero_routers, numero_ligacoes, primeiro_router, segundo_router,i;
	scanf ("%d %d", &numero_routers, &numero_ligacoes);
	
	lista * grafo[numero_routers];

	for (i=0; i<numero_routers; i++){
		grafo[i] = cria_lista();
	}

	for (i=0; i<numero_ligacoes; i++){
		scanf ("%d %d", &primeiro_router, &segundo_router);
		if (primeiro_router >= 1 && segundo_router >= 1 && primeiro_router != segundo_router && 
			primeiro_router <= numero_routers && segundo_router <= numero_routers){
			inserir_inicio(grafo[primeiro_router-1], segundo_router);
			inserir_inicio(grafo[segundo_router-1], primeiro_router);
		}
	}

	DFS(grafo, numero_routers);

	return 0;
}



