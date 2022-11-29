#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*PROJECTO 1 ASA*/
/*86524 Vadym Volkovinskyy*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int index;
	int value;
	struct node* next;
}Node;

typedef struct list{
	Node* head;
} List;

typedef struct graph{
	int numStudents;
    int* visited;
	List* array;
} Graph;

Node* newList(int scores[], int dest){
	Node* newStudent = (Node*) can_fail_malloc(sizeof(Node));
    newStudent->index = dest;
	newStudent->value = scores[dest];
	newStudent->next = NULL;
    return newStudent;
}

Graph* createGraph(int numStudents){
	Graph* graph = (Graph*) can_fail_malloc(sizeof(Graph));
	graph->numStudents = numStudents;
	graph->array = (List*) can_fail_malloc(numStudents * sizeof(List));
    graph->visited = can_fail_malloc(numStudents * sizeof(int));

	int i;
	for(i = 0; i < numStudents; i++){
		graph->array[i].head = NULL;

        graph->visited[i] = 0;
	}
	return graph;
}

void addRelation(Graph* graph, int student, int friend, int scores[]){
	Node* newStudent = newList(scores,friend);
	newStudent->next = graph->array[student].head;
	graph->array[student].head = newStudent;
}

int max = 0;
void DFS(Graph* graph, int index, int scores[]) {
    Node* array = graph->array[index].head;
    Node* temp = array;

    if(max < scores[index]){
        max = scores[index];
    }

    graph->visited[index] = 1;
    
    while(temp!=NULL) {
        int nextFriend = temp->index;
        
        if(graph->visited[nextFriend] == 0) {
            DFS(graph, nextFriend, scores);
        }
        temp = temp->next;
    }     
}

void newScores(Graph* graph, int numStudents, int scores[]){

    int k;
    for(k = 0; k < numStudents; k++){

        DFS(graph, k, scores);

        printf("%d\n", max);

        max=0;
        int l;
        for(l = 0; l < numStudents; l++){
            graph->visited[l] = 0;
	    }
    }
}

int main() {

	int numStudents;
	int numRelations;

	int friend;
	int student;

	scanf("%d, %d",&numStudents, &numRelations);

    int scores[numStudents];

    int i;
    for(i = 0; i < numStudents; i++){
        scanf("%d",&scores[i]);
    }

	Graph* graph = createGraph(numStudents);

    int j;
	for(j = 0; j < numRelations; j++){
		scanf("%d %d", &student, &friend);
		addRelation(graph, student-1, friend-1, scores);
	}

    newScores(graph, numStudents, scores);
    
	return 0;
}