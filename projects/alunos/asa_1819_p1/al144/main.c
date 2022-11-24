#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*ASA 1ºProjeto*/
/*Grupo 144 - Tiago Prata N 86516 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int number;
    struct node* next;
}*Node;

typedef struct routers{
  int visit;
  int low;
  Node head;
}*Routers;

typedef struct graph{
  int numberRouters;
  Routers arrayOfRouters;
}*Graph;

typedef struct stack{
    int top;
    int capacity;
    int* array;
}*Stack;

/*Variaveis Globais*/
int countSCCs = 0;
int time = 1;
int routQuebra = 0;
int auxiliarSCCs = 0;
int biggestSCC = 0;

/*stack related*/
Stack createStack(int capacity){
    Stack stack = (Stack) can_fail_malloc(sizeof(struct stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) can_fail_malloc(stack->capacity * sizeof(int));
    return stack;
}

void push(Stack stack, int num){
    stack->array[++stack->top] = num;
}

int pop(Stack stack){
    return stack->array[stack->top--];
}

void deleteStack(Stack stack){
	free(stack->array);
	free(stack);
}

Graph createGraph(int routers){
  int i;
  Graph graph = (Graph)can_fail_malloc(sizeof(struct graph));
  graph->numberRouters = routers;
  graph->arrayOfRouters= (Routers)can_fail_malloc(routers*sizeof(struct routers));
  for(i=0; i< routers; i++){
    graph->arrayOfRouters[i].head=NULL;
  }
  return graph;
}

Node createNode(int num){
  Node node = (Node)can_fail_malloc(sizeof(struct node));
  node->number = num;
  node->next = NULL;
  return node;
}

void addEdge(Graph graph, int router1, int router2){
  Node temp = createNode(router2);
  temp->next = graph->arrayOfRouters[router1].head;
  graph->arrayOfRouters[router1].head = temp;
}

/*funcao que retorna o menor numero entre dois*/
int min(int num1, int num2){
	if(num1>num2)
		return num2;
	else
		return num1;
}

/*TARJAN SEARCH*/

/*funcao auxiliar a findSCCs*/
void auxSCCs(Graph graph, int num,Stack stack,int inStack[], int lowToSmallestRouters[], int sccID[]){
	push(stack,num); /*colocar na stack o vertice*/
	inStack[num] = 1; /*assinalar que o vertice esta na stack*/
	graph->arrayOfRouters[num].visit = time;
	graph->arrayOfRouters[num].low = time;
	time++;
	/*percorrer os nodes do grafo*/
	Node temp = graph->arrayOfRouters[num].head;
	while(temp!=NULL){
		/*0 stands for an unvisited vertice*/
		if(graph->arrayOfRouters[temp->number].visit == 0){
			auxSCCs(graph, temp->number,stack,inStack,lowToSmallestRouters, sccID);
		}

		if(inStack[temp->number]==1){
			graph->arrayOfRouters[num].low =
				min(graph->arrayOfRouters[num].low ,graph->arrayOfRouters[temp->number].low);
		}

		temp=temp->next;
	}
	/*caso o visit seja igual ao low encontramos um potencial scc e vamos retirando da stack*/
	if(graph->arrayOfRouters[num].visit==graph->arrayOfRouters[num].low){
		int smallest = graph->numberRouters; /*variavel que identifica o vertice com menor indice no scc*/
		int vertex;
		for (vertex = pop(stack);;vertex=pop(stack)){
      if(vertex>sccID[countSCCs]){
        sccID[countSCCs] = vertex;
      }
			/*mecanismo para encontrar o vertice com menor indice*/
			if(vertex<smallest) smallest = vertex;
			inStack[vertex] = 0;
			/*dado que os scc podem ter vertices com lows diferentes com esta instrucao unformizamos o low para
			todos os vertices do mesmo scc*/
			graph->arrayOfRouters[vertex].low = graph->arrayOfRouters[num].low;
			/*fazer pop da stack ate encontar o ultimo vertice*/
			if(vertex==num) break;
		}
		/*correspondencia do low com o menor vertice*/
		/*sabendo o low do vertice sabemos o menor indice do seu scc*/
		lowToSmallestRouters[graph->arrayOfRouters[num].low] = smallest;
		/*encontramos um scc logo incrementamos a variavel*/
		countSCCs++;
	}

}

/*algoritmo de tarjan para encontrar os componentes fortemente ligados de um grafo*/
void findSCCs(Graph graph,Stack stack,int inStack[], int lowToSmallestRouters[], int sccID[]){
	int numRout=graph->numberRouters;
	int i;
	/*inicializar os valores dos arrays*/
	for(i=0;i<numRout;i++){
		inStack[i] = 0;
		graph->arrayOfRouters[i].low = 0;
		/*0 stands for an unvisited router*/
		graph->arrayOfRouters[i].visit = 0;
	}

	for(i=0;i<numRout;i++){
		/*0 stands for an unvisited router*/
		if(graph->arrayOfRouters[i].visit == 0)
			auxSCCs(graph,i,stack,inStack,lowToSmallestRouters, sccID);
	}

	deleteStack(stack);
}

void printInOrder(int sccID[]){
  int a;
  int i;
  int j;
  int p;
  for (i=0; i<countSCCs;++i){
    for (j=i+1; j<countSCCs;++j){
      if(sccID[i] > sccID[j]){
        a = sccID[i];
        sccID[i] = sccID[j];
        sccID[j] = a;
      }
    }
  }
  for(p=0;p<countSCCs;p++){
    printf("%d ", sccID[p]+1);
  }
  printf("\n");
}

int main(){
  int numRouters, numLigacoes;
  int router1, router2;
  scanf("%d",&numRouters);
  scanf("%d",&numLigacoes);

  Graph graph = createGraph(numRouters);

  int i;
  int* sccID = (int*) can_fail_malloc(numRouters * sizeof(int));

  for(i=0; i<numLigacoes;i++){
    scanf("%d %d", &router1, &router2);
    /*Graph starts in 0*/
    addEdge(graph, router1-1, router2-1);
    addEdge(graph, router2-1, router1-1);
  }
	int inStack[numRouters];
  Stack stack = createStack(numRouters);
  int lowToSmallestRouters[numRouters];

  for(i=0; i<numRouters;i++){
    sccID[i]=-1;
  }

  findSCCs(graph,stack,inStack,lowToSmallestRouters,sccID);
	printf("%d\n", countSCCs);

  printInOrder(sccID);

  printf("%d\n", routQuebra);

  printf("%d\n", biggestSCC);

  free(sccID);
  return 0;
}
