#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

int flag = 1;

typedef struct student {
    int id;
    int grade;
    struct student* next;
} student;

struct Graph {
    int numStudents;
    int* visited;
    int* grades; 
    struct student** relationships; 
};

struct Graph* createGraph(int students) {
    struct Graph* graph = can_fail_malloc(sizeof(struct Graph));
    graph->numStudents = students;
    graph->grades = can_fail_malloc(students * sizeof(int));
    graph->relationships = can_fail_malloc(students * sizeof(struct student*));
    
    graph->visited = can_fail_malloc(students * sizeof(int));
 
    int i;
    for (i = 0; i < students; i++) {
        graph->relationships[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void freeRelationships(struct student* student) {
  if (!student) {
    return;
  }
  freeRelationships(student->next);
  free(student);
}


void freeGraph(struct Graph* graph, int students) {
  free(graph->grades);
  free(graph->visited);
  int i;
  for (i = 0; i < students; i++) {
    freeRelationships(graph->relationships[i]);
  }
  free(graph->relationships);
  free(graph);

}

struct student* createStudent(int id, int grade) {
    struct student* newStudent = can_fail_malloc(sizeof(struct student));
    newStudent->id = id;
    newStudent->grade = grade;
    newStudent->next = NULL;
    return newStudent;
}

void addEdge(struct Graph* graph, int src, int dest) {
  struct student* newStudent = createStudent(dest, graph->grades[dest]);
  newStudent->next = graph->relationships[src];
  graph->relationships[src] = newStudent;
}

void DFSVisited(struct Graph* graph, int id) {
  struct student* relationships = graph->relationships[id];
  struct student* temp = relationships;
        
        graph->visited[id] = 1;
    
        while(temp!=NULL) {
            int connectedId = temp->id;



            if(graph->visited[connectedId] == 0) {
                DFSVisited(graph, connectedId);
            }
            if(graph->grades[id] < graph->grades[connectedId]) {
              graph->grades[id] = graph->grades[connectedId];
              flag = 0;
            }
            temp = temp->next;
        }  
}

void checkGrades(struct Graph* graph, int id) {
  struct student* relationships = graph->relationships[id];
  struct student* temp = relationships;
    
        while(temp!=NULL) {
            int connectedId = temp->id;
            if(graph->grades[id] < graph->grades[connectedId]) {
              graph->grades[id] = graph->grades[connectedId];
              flag = 0;
            }
            temp = temp->next;
        }  
}

void DFS(struct Graph* graph, int students) {
  int i;
  for(i = 0; i < students; i++) {
    if(graph->visited[i] == 0){
      DFSVisited(graph, i);
    }
  }
  while(!flag) {
    flag = 1;
    for(i = 0; i < students; i++){
      checkGrades(graph, i);
    }
  }
}


int main(int argc, char* argv[]) {

  int students;
  int relationships;
  int grade;
  int src;
  int dest;
  int i;

  scanf("%d,%d", &students, &relationships);

  if((students < 2) || (relationships < 1)) {
    exit(EXIT_FAILURE);
  }

  struct Graph* graph = createGraph(students);

  for(i = 0; i < students; i++) {
    scanf("%d", &grade);
    if(grade > 20) {
      exit(EXIT_FAILURE);
    }
    graph->grades[i] = grade;
  }

  for(i = 0; i <relationships; i++) {
    scanf("%d %d", &src, &dest);
    if((src > students) || (dest > students)) {
      exit(EXIT_FAILURE);
    }
    addEdge(graph, src-1, dest-1);
  }

  DFS(graph, students);


  for (i = 0; i < students; i++) {
    printf("%d\n", graph->grades[i]);
  }

  freeGraph(graph, students);
  return 0;

}