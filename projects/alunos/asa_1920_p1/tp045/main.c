#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

/* Definitions */

typedef struct node *link;
struct node {
	long connection;
	link next;
};

typedef struct {
    int index;
    int score;
    int visited;
    link listOfAdj;
} Student;

/* DFS */

/** returns score **/
void DFSUtil(Student** studs, int idx, int grade) {
    link adj = studs[idx]->listOfAdj;
    studs[idx]->visited = 1;
    
    if( grade > studs[idx]->score ) {
        studs[idx]->score = grade;
    }

    /*printf("Node: %d\n", studs[idx]->index);*/
    /** cycle connections **/
    for( ; adj != NULL; adj = adj->next ) {
        /** -1 because reasons **/
        /*printf("Node: %d\n\tscore - %d\n\tvisiting - %ld\n\tvisit score: %d\n", studs[idx]->index, studs[idx]->score, adj->connection, studs[adj->connection-1]->score);*/
        if( studs[adj->connection-1]->visited == 0 ) {
            DFSUtil(studs, adj->connection-1, studs[idx]->score);
        } else if( studs[idx]->score > studs[adj->connection-1]->score ) {
            DFSUtil(studs, adj->connection-1, studs[idx]->score);
        }
    }
    /*printf("Finishing node %d\n", studs[idx]->index);*/
}

void DFS(Student** graph, int vertexs) {
    int i = 0;

    for( i=0; i<vertexs; i++ ) {
        if( graph[i]->visited == 0 ) DFSUtil(graph, i, 0);
    }
} 

/** Auxiliar functions **/

void createLink(link clink, int rela) {
    clink->next = NULL;
    clink->connection = rela;
}

/** inserts a new connection */
void insertLink(Student** graph, int rela, int relb) {
    link newAdj = can_fail_malloc(sizeof(struct node));
    if( graph[relb-1]->listOfAdj == NULL ) {
        graph[relb-1]->listOfAdj = newAdj;
        createLink(graph[relb-1]->listOfAdj, rela);
    } else {
        link adj = graph[relb-1]->listOfAdj;
        while( adj->next != NULL ) adj = adj->next;
        adj->next = newAdj;
        createLink(newAdj, rela);
    }
}

/* main */

int main(int argc, char** argv) {
    long int N, M, rela, relb;
    int i = 0;
    
    scanf("%ld,%ld", &N, &M);
    Student* listOfStudents[N];

    while( i < N ) {
        /** scan Ns **/
        listOfStudents[i] = (Student*)can_fail_malloc(sizeof(Student));
        scanf("%d", &listOfStudents[i]->score);
        listOfStudents[i]->index = i+1;
        listOfStudents[i]->visited = 0;
        i++;
    }

    i = 0;

    while( i < M ) {
        /** scan Ms **/
        scanf("%ld %ld", &rela, &relb);
        if( rela > N || relb > N ) {
            exit(0);
        }
        
        insertLink(listOfStudents, rela, relb);
        i++;
    }

    DFS(listOfStudents, N);
    
    /** print output **/
    i = 0;

    while( i < N ) {
        /*printf("Student %d:\n\tscore - %d\n", listOfStudents[i]->index, listOfStudents[i]->score);*/
        printf("%d\n", listOfStudents[i]->score);
        i++;
    }

    return 0;
}