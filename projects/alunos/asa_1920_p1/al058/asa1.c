#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define WHITE 1
#define GRAY 2
#define BLACK 3

int initialize(int nstudents);
void startgraph(int connections);
void insertfriend(int s1, int s2);
int DFSVisit(int v, int max_grade);
void free_graph();

typedef struct{
    int color;
    int grade;
    int nfriends;    
}Student;

Student *students;

typedef struct Node{
    struct Node *next;
    int v;
}Node;

typedef struct{
    Node *head;
}Graph;

Graph *graph;



int main(){
    int nstudents, connections, v, i, max_grade;
    scanf("%d,%d", &nstudents, &connections);
    graph = can_fail_malloc(sizeof(Graph) *nstudents);
    students = can_fail_malloc(sizeof(Student) *nstudents);

    max_grade = initialize(nstudents);
    startgraph(connections);


    for (v=0; v<nstudents; v++){
        if (students[v].nfriends == 0 || students[v].grade == max_grade) {
          students[v].color = BLACK;
        }
      }

    for (v=0; v<nstudents; v++){
        if (students[v].color != BLACK){
            DFSVisit(v, max_grade);
            students[v].color = BLACK;
        }
        printf("%d\n", students[v].grade);
    }


    free(students);
    for (i=0; i<nstudents; i++){
        Node *iter;
        while(graph[i].head != NULL){
            iter = graph[i].head;
            graph[i].head = graph[i].head->next;
            free(iter);
        }
    }
    free(graph);

    return 0;
}


int initialize(int nstudents){
    int i, max_grade = 0;
    for (i=0; i<nstudents; i++){
        scanf("%d\n", &students[i].grade);
        if (students[i].grade > max_grade) max_grade = students[i].grade;
        students[i].color = WHITE;
        students[i].nfriends = 0;
        graph[i].head = NULL;
    }
    return max_grade;
}

void startgraph(int connections){
    int s1, s2, i;
    for (i=0; i<connections; i++){
        scanf("%d %d", &s1, &s2);
        insertfriend(s1, s2);
    }
}

void insertfriend(int s1, int s2){
    Node *node = can_fail_malloc(sizeof(Node));
    node->v = s2-1;
    node->next = graph[s1-1].head;
    graph[s1-1].head = node;
    students[s1-1].nfriends++;
}


int DFSVisit(int i, int max_grade){
    Node *iter;
    students[i].color = GRAY;

    iter = graph[i].head;
    while (iter != NULL){
        if (students[iter->v].grade == max_grade) {
          students[i].grade = max_grade;
          students[i].color = BLACK;
          return students[i].grade;
        }
        if (students[iter->v].color == WHITE)
            students[iter->v].grade = DFSVisit(iter->v, max_grade);
        if (students[i].grade < students[iter->v].grade)
            students[i].grade = students[iter->v].grade;
    iter = iter->next;
    }
    students[i].color = WHITE;
    return students[i].grade;
}
