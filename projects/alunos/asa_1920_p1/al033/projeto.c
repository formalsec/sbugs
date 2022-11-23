#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/****************************************************************************/
/*				          ASA - PROJETO 1 - main.c                   		*/
/*																			*/
/* Grupo 33 	   No 92433, 92442  	                                	*/
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define INFINITE -1
#define MAX 100

/****************************************************************************/
/*                               STRUCTURES                                 */
/****************************************************************************/

struct student_t;

/* Structure representing an adjacency list */
typedef struct adjListNode_t {
	struct student_t* dest;
	struct adjListNode_t* next;
} Friendship_t;

/* Structure representing a Student/vertex (adjacency list node) */
typedef struct student_t {
	int grade;
	int id;
	int d;
	int sccID; /* "low" for Tarjan Algorithm */
	Friendship_t* head;
} Student_t;

/* Structure representing a stack */
typedef struct stack_t {
	int capacity;
	int top;
	Student_t** items;
} Stack_t;

/* Structure representing the universe of vertex (graph) */
typedef struct graph_t {
	int num;
	Student_t** vertex;
} Graph_t;

typedef struct node_t {
	Student_t* student;
	struct node_t* next;
} Node_t;

typedef struct list_t {
	Node_t* head;
} List_t;

/****************************************************************************/
/*                               PROTOTYPES                                 */
/****************************************************************************/

Stack_t* newStack(int v);
void push(Stack_t* stackPtr, Student_t* vertex);
Student_t* pop(Stack_t* stackPtr);
int isInStack(Stack_t* stack, int item);
Student_t* createNewStudent(int grade, int id);
Graph_t* createGraph(int n);
void addFriendship(Graph_t* g, int uID, int vID);
void removeFriendship(int uID, int vID);
void tarjanVisit(Graph_t* graph, Student_t* vertex);
void SCC_tarjan(Graph_t* graph, int n);
int max(int a, int b);
int min(int a, int b);
void processInput();
void displayGrades();
void removeAllSccEdges();
void add_Node(Student_t* new_student);
Graph_t* graphScc();

/****************************************************************************/
/*                               VARIABLES                                  */
/****************************************************************************/

Graph_t* graph;
Graph_t* SccGraph;
int numberStudents = 0;
int numberRelations = 0;
int visited = 0;
Stack_t* stack;
Stack_t* auxStack;

/****************************************************************************/
/*                               FUNCTIONS                                  */
/****************************************************************************/

void processInput() {
	scanf("%d,%d", &numberStudents, &numberRelations);
	int i, grade;
	graph = createGraph(numberStudents);

	for (i = 1; i <= numberStudents; i++) {
		scanf("%d", &grade);
		graph->vertex[i] = createNewStudent(grade, i);
	}

	if (numberStudents > 0) {
		for (i = 0; i < numberRelations; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			addFriendship(graph, u, v);
		}
	}
}

void displayGrades() {
	int i;
	for (i = 1; i <= numberStudents; i++)
		printf("%d\n", graph->vertex[i]->grade);
}

/* Initiates stack */
Stack_t* newStack(int v) {
	Stack_t* stackPtr = (Stack_t*)can_fail_malloc(sizeof(Stack_t));
	int i;
	;
	stackPtr->capacity = v;
	stackPtr->top = -1;
	stackPtr->items = (Student_t**)can_fail_malloc(sizeof(Student_t) * v);
	for (i = 0; i < v; i++) {
		stackPtr->items[i] = NULL;
	}
	return stackPtr;
}

/* Add element (vertex/Student id) to stack */
void push(Stack_t* stackPtr, Student_t* vertex) {
	stackPtr->items[++stackPtr->top] = vertex;
}

/* Returns top element of the stack */
Student_t* pop(Stack_t* stackPtr) {
	if (stackPtr->top >= 0)
		return stackPtr->items[stackPtr->top--];
	return NULL;
}

int isInStack(Stack_t* stack, int id) {
	int i;
	for (i = 0; i < stack->capacity; i++) {
		if (stack->top < 0 || stack->items[i] == NULL)
			return 0;
		else if (stack->items[i]->id == id)
			return 1;
	}
	return 0;
}

/* Initiates a new student (adjacency list node) */
Student_t* createNewStudent(int grade, int id) {
	Student_t* newStudent = (Student_t*)can_fail_malloc(sizeof(Student_t));

	newStudent->grade = grade;
	newStudent->id = id;
	newStudent->head = NULL;
	return newStudent;
}

/* Initiates a new graph with n vertex */
Graph_t* createGraph(int n) {
	int i;
	Graph_t* graph = (Graph_t*)can_fail_malloc(sizeof(Graph_t));

	graph->num = n;

	graph->vertex = (Student_t**)can_fail_malloc(n * sizeof(Student_t) + 1);

	for (i = 0; i <= n; i++) {
		graph->vertex[i] = NULL;
	}

	return graph;
}

/* Establishes a friendship between two vertex where u is friends with v */
void addFriendship(Graph_t* g, int uID, int vID) {
	Friendship_t* newEdge = (Friendship_t*)can_fail_malloc(sizeof(Friendship_t));
	newEdge->dest = g->vertex[vID];
	newEdge->next = NULL;
	if(g->vertex[uID]->head==NULL){
		g->vertex[uID]->head=newEdge;
		return;
	}
	Friendship_t* aux = g->vertex[uID]->head;
	while(aux->next!=NULL) aux=aux->next;
	aux->next=newEdge;
}

/*void add_Node(Student_t* new_student) {
	Node_t* new_node = (Node_t*)can_fail_malloc(sizeof(Node_t));
	new_node->student = new_student;
	new_node->next = list->head;
	list->head = new_node;
}*/

int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

/* Recursive function for Tarjan Algorithm*/
void tarjanVisit(Graph_t* graph, Student_t* vertex) {
	Friendship_t* friends = vertex->head;
	Student_t* friend = NULL, *v = NULL;
	vertex->d = vertex->sccID = visited++;

	if (friends == NULL) {
		return;
	}

	else {
		push(stack, vertex);

		while (friends != NULL) {
			friend = friends->dest;

			if (0 != isInStack(stack, friend->id) || friend->d == INFINITE) {
				if (friend->d == INFINITE)
					tarjanVisit(graph, friend);
				vertex->sccID = min(vertex->sccID, friend->sccID);
			}

			vertex->grade = max(vertex->grade, friend->grade);

			friends = friends->next;
		}
		if (vertex->d == vertex->sccID) {
			v = pop(stack);
			while (v != NULL && v->id != vertex->id) {
				push(auxStack, v);
				v = pop(stack);
			}
			push(auxStack, vertex);
		}
	}
}

/* Searches for edge connecting students */
int isInAdjList(Friendship_t* f, int id) {
	Friendship_t* aux = f->next;
	while (aux != NULL) {
		if (aux->dest->id == id) {
			return 0;
		}
		aux = aux->next;
	}
	return 1;
}

/*Tarjan algorithm*/
void SCC_tarjan(Graph_t* graph, int n) {
	int i, j=0;
	stack = newStack(n);
	auxStack = newStack(n);
	Student_t* v = NULL;
	Friendship_t* friends;
	for (i = 1; i <= n; i++)
		graph->vertex[i]->d = INFINITE;
	for (i = 1; i <= n; i++) {
		if (graph->vertex[i]->d == INFINITE) {
			tarjanVisit(graph, graph->vertex[i]);
		}
	}
	for(v=auxStack->items[j]; v!=NULL; v=auxStack->items[++j]){
		friends=v->head;
		while(friends!=NULL){
			v->grade=max(friends->dest->grade, v->grade);
			friends=friends->next;
		}
	}
}

int main() {
	processInput();
	if (numberRelations != 0) {
		SCC_tarjan(graph, numberStudents);
	}
	displayGrades();
	return 0;
}