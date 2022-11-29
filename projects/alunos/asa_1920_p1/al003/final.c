#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))



typedef struct List {
    struct Node* node;
    struct List* next;
}List;

typedef struct Node {
    int grade;
    int visited;
    struct List* head;
}Node;

typedef struct Graph {
    int n_students;
    int n_friendships;
    Node* lst_Nodes;

} Graph;


Graph* creategraph() {

    Graph* new_graph = can_fail_malloc(sizeof(Graph));

    scanf("%d,%d", &new_graph->n_students, &new_graph->n_friendships);
    new_graph->lst_Nodes = can_fail_calloc(new_graph->n_students, sizeof(Node));

    return new_graph;
}

void create_students(Graph* graph) {
    int i;
    for (i = 0; i < graph->n_students; i++) {
        Node* student = &graph->lst_Nodes[i];
        scanf("%d", &student->grade);
        student->visited = -1;
        student->head = NULL;
    }
}

void read_friendships(Graph* graph) {
    int i, i_student1, i_student2;
    for (i = 0; i < graph->n_friendships; i++)
    {
        scanf("%d %d", &i_student1, &i_student2);

        i_student1 = i_student1 - 1;
        i_student2 = i_student2 - 1;

        Node* student1 = &graph->lst_Nodes[i_student1];
        Node* student2 = &graph->lst_Nodes[i_student2];

        if(student1->head){
            List* adj = (List*)can_fail_malloc(sizeof(List));    
            adj->next = student1->head;
            student1->head =adj;
            student1->head->node = student2;
            
        }
        else{
            student1->head = (List*)can_fail_malloc(sizeof(List));;
            student1->head->node = student2;
        }    
}

}

void print_grades(Graph* graph) {
    int i;
    for (i = 0; i < graph->n_students; i++) {
        Node* student = &graph->lst_Nodes[i];
        printf("%d\n", student->grade);
    }
}


int DFS_UTIL(Graph* graph, Node* student) {
    if(student->visited == -1){
        student->visited = 1; 
            List* adj = student->head;
            while(adj){
                student->grade = MAX(student->grade,DFS_UTIL(graph,adj->node));
                adj = adj->next;
            }
        }   
    return student->grade;
}

void DFS(Graph* graph) {
    int i;
    for ( i = 0; i < graph->n_students; i++) {
        Node* student = &graph->lst_Nodes[i];
        if (student->visited != 1) {
            student->visited = 1;
            List* adj = student->head;
            
            while(adj){
                student->grade=MAX(student->grade,DFS_UTIL(graph,adj->node));
                adj = adj->next;
            }
        }
    }

}

void free_graph(Graph* graph) {
    int i;
    for (i = 0; i < graph->n_students; i++) {
       
        Node* student = &graph->lst_Nodes[i];
        List* adj = student->head;
        List* next; 
        
        while (adj){
    
            next = adj->next;
            free(adj);
            adj = next;
        }
    }
    free(graph->lst_Nodes);
    free(graph);
}

int main() {

    Graph* graph = creategraph();
    create_students(graph);
    read_friendships(graph);


    DFS(graph);

    print_grades(graph);
    free_graph(graph);

    return 0;
}