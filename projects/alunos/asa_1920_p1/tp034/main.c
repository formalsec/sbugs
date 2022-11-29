#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Struct of a node in the adjency list*/
typedef struct Node {
    long unsigned int id;
    struct Node* next;
}node;

/*Struct that points to the first node of an adjency list*/
typedef struct List{
    node* head;
}list;

/*Struct for the graph composed by adjency lists*/
typedef struct Graph {
    long unsigned int n;
    list* lists;
}graph;

/*
Creates a new node, used to represent a vertex.
    id is the id of the vertex
*/
node* createNode(long unsigned int id){
    node* newNode = (node*)can_fail_malloc(sizeof(node*));
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
}

/*
Creates and allocates memory for a graph.
    n is the number os vertices
*/
graph* createGraph(long unsigned int n){
    long unsigned int i;
    n++;
    graph* newGraph = (graph*)can_fail_malloc(sizeof(graph));
    newGraph->n = n;
    newGraph->lists = (list*)can_fail_malloc(sizeof(list) * (n+1));

    for(i = 1; i <= n; i++){
        newGraph->lists[i].head = NULL;
    }

    return newGraph;
}

/*
Adds a edge to the graph.
    graph is a pointer to graph to add the edge
    v1 is the first vertex of the edge
    v2 is the second vertex of the edge
*/
void addEdge(graph* graph, long unsigned int v1, long unsigned int v2){
    /*Makes edge from v1 to v2*/
    node* newNode = createNode(v2);
    newNode->next = graph->lists[v1].head;
    graph->lists[v1].head = newNode;
}

/*
**DEBUG FUNCTION**
Prints the graph
*/
void printGraph(graph* graph){
    long unsigned int v;

    for(v=1; v <= graph->n; v++){
        node* nodep = graph->lists[v].head;
        printf("Vertex %lu\n head", v);
        while(nodep){
            printf(" > %lu", nodep->id);
            nodep = nodep->next;
        }
        printf("\n\n");
    }
}
/*
**END OF DEBUG FUNCTION**
*/

/*
Reads from input all the students friendships (edges) and "draws" them on the graph.
    students is the graph to be populated
    grades is the list that contains the grades of the students
    n is the number of students (vertices)
    m is the number of friendships (edges)
*/
void parseInput(graph* students, int* grades, long unsigned int n, long unsigned int m){
    long unsigned int i, s1, s2;
    int grade;

    /*Reads the first estimative for the students and places it on the grade array*/
    for(i=1; i<=n; i++){
        if(scanf("%d", &grade));
        grades[i] = grade;
    }

    /*Reads the friendships and adds them to the graph*/
    for(i=0; i<m; i++){
        if(scanf("%lu %lu", &s1, &s2));
        addEdge(students, s2, s1);
    }
}

/*
Runs the algorithm that calculates the new estimatives
    students is the graph representing the students friendships
    grades is the list that contains the grades of the students
*/
void run(graph* students, int* grades){
    int max, maxi, n, i, left;
    node* nodep;
    max = 0;
    maxi = 1;
    n = students->n;
    left = n;

    /*Runs until all the points have been compared to their neighbors*/
    while(left > 0){
        /*Looks first for the students with the highest grade*/
        for(i=1; i<=n; i++){
            if((students->lists[i].head != NULL) && (grades[i] > max)){
                max = grades[i];
                maxi = i;
            }
        }

        /*
        Checks if the direct friends of current student have a higher grade or not.
            if they have a lower grade then their grades are updated to the grade of the current student
        */
        nodep = students->lists[maxi].head;
        while(nodep){
            if(grades[nodep->id] < max){
                grades[nodep->id] = max;
            }
            nodep = nodep->next;
        }
        /*The edges leaving the current student are erased*/
        students->lists[maxi].head = NULL;
        max = 0;
        left--;
    }
}

int main (int argc, char** argv){
    /*
    n is number of vertices and m is number of edges (defined on the project paper)
    students is the graph of all the students (vertices) and their friendships (edges)
    */
    long unsigned int i;
    long unsigned int n;
    long unsigned int m;
    graph* students;
    int* grades;

    /*Reads number of vertices and number of edges*/
    if(scanf("%lu,%lu", &n, &m));

    grades = (int*)can_fail_malloc(sizeof(int) * (n+1));

    /*Creates students graph and populates with given friendships (edges)*/
    students = createGraph(n);
    
    parseInput(students, grades, n, m);

    run(students, grades);

    /*Prints the results*/
    for(i=1; i<=n; i++){
        printf("%d\n", grades[i]);
    }

    return 0;
}
