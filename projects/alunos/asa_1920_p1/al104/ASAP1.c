#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Álvaro Saldanha 92416
   Guilherme Fernandes 92473
   ASA - 1º PROJETO */

#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define BLACK 2

typedef struct node{
	int grade;
	int color;
} Node;

typedef struct adjListNode{
	int index;
	struct adjListNode * next;
} adjListNode;

typedef struct gradeListNode{
	int index;
	struct gradeListNode * next;
} gradeListNode;

Node * graph;
adjListNode ** adjList;
gradeListNode * gradeList[21] = {NULL};
int nCount, eCount,min = 20, max = 0;
gradeListNode * rightNode;


void initialize_nodes(){
	int i, tempGrade;
	for (i = 0; i < nCount; i++){
		scanf("%d",&tempGrade);
		graph[i].grade = tempGrade;
		graph[i].color = WHITE;
		adjList[i] = NULL;
		gradeListNode * temp = can_fail_malloc(sizeof(gradeListNode));
		temp->index = i;
		if (gradeList[tempGrade] == NULL){
			temp->next = NULL;
		}
		else{
			temp->next = gradeList[tempGrade];
		}
		gradeList[tempGrade] = temp;
		if (tempGrade > max) max = tempGrade;
		if (tempGrade < min) min = tempGrade;

	}

}

void connect(int node1, int node2){
	adjListNode * temp = can_fail_malloc(sizeof(adjListNode));
	temp->index = node2;
	if (adjList[node1] == NULL){
		temp->next = NULL;
	}
	else{
		temp->next = adjList[node1];
	}
	adjList[node1] = temp;
}

void initialize_connections(){
	int i,node1, node2;
	for (i = 0; i < eCount; i++){
		scanf("%d %d",&node2,&node1);
		connect(node1-1,node2-1);
	}
}

void propagate(int node, int grade){
	adjListNode * temp = adjList[node];
	graph[node].color = BLACK;
	graph[node].grade = grade;
	for(;temp != NULL;temp = temp->next){
		if(graph[temp->index].color == WHITE){
			propagate(temp->index,grade);
		}
	}
}


/* Finds the person with the highest grade and calls the "propagate" 
function passing the index of the person and the respective highest grade. */
void algorithm(){
	int i;
	gradeListNode * temp;
	for (i = max; i > min - 1; i--){
		for(temp = rightNode; temp != NULL;temp = temp->next){
			if(graph[temp->index].color == WHITE){
				propagate(temp->index,graph[temp->index].grade); 				
			}
		}
		rightNode = gradeList[i - 1];
	}
}


void output(){
	int i=0;
	for (;i<nCount;i++){
		printf("%d\n",graph[i].grade);
	}
}

int main(){
	scanf("%d, %d",&nCount,&eCount);
	graph = can_fail_malloc(sizeof(Node)*nCount);
	adjList = can_fail_malloc(sizeof(adjListNode*) * nCount);
	initialize_nodes();
	initialize_connections();
	rightNode = gradeList[max];
	algorithm();
	output();
	free(adjList);
	free(graph);
	return 0;
}
