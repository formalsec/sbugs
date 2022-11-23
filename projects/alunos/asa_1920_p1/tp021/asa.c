#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node * next;
    int v;
} node;

typedef struct vertex{
    int id;
    int grade;
    struct node * adj_root;

    int d;
    int low;
} vertex ;

typedef struct graph{
    int d;
    int max_grade;
    node * members;
    node * adj_root;
} graph;

int min(int A, int B);

/*Linked lists*/
void addNodeToList(node ** root, int value);
int isNodeInList(node ** root, int value);
node * pop(node ** root);

void sccTarjan();
void tarjanVisit(int number);
void DFS();
void DFSVisit(int number);

/*ler input*/
int no_v;
int no_a;
int counter;

int visited;
int time;
node * L;
vertex * students;
graph * graph_sccs;


int main () {

    scanf("%d,%d", &no_v, &no_a);
    
    students = can_fail_malloc(sizeof(vertex)*no_v);
    int i;
    for(i = 0; i < no_v; ++i){
        students[i].id = i;
        scanf("%d", &students[i].grade);
        students[i].adj_root = NULL;
    } 

    int v1, v2;

    for(i = 0; i < no_a; ++i){
        scanf("%d %d", &v1, &v2);
        v1--;
        v2--;
        addNodeToList(&students[v1].adj_root, v2);
    }

    sccTarjan();

    counter = 0;
    int lows[no_v];

    for(i = 0; i < no_v; ++i){
        lows[i] = 0;
    }

    for(i = 0; i < no_v; ++i){
       lows[students[i].low]++;
    }

    for(i = 0; i < no_v; ++i){
        if(lows[i] != 0){
            counter ++;
        }
        lows[i] = -1;
    }

    int j = 0;

    for(i = 0; i < no_v; ++i){
        if(lows[students[i].low] == -1){
            lows[students[i].low] = j;
            j++;
        }
    }

    graph_sccs = can_fail_malloc(sizeof(graph)* counter);

    for (i = 0; i < counter; ++i){
        graph_sccs[i].adj_root = NULL;
        graph_sccs[i].members = NULL;
    }

    for(i = 0; i < no_v; ++i){
        addNodeToList(&graph_sccs[lows[students[i].low]].members, i);
    }

    int max;
    node * temp;

    for(i = 0; i < counter; ++i){
        temp = graph_sccs[i].members;
        max = students[temp->v].grade;
        while(temp != NULL){
            if(max < students[temp->v].grade){
                max = students[temp->v].grade;
            }
            temp = temp->next;
        }
        graph_sccs[i].max_grade = max;
    }

    for(i = 0; i < no_v; i++){
        temp = students[i].adj_root;
        while(temp!=NULL){
            if(students[i].low != students[temp->v].low && !isNodeInList(&graph_sccs[lows[students[i].low]].adj_root, lows[students[temp->v].low])){
                addNodeToList(&graph_sccs[lows[students[i].low]].adj_root,lows[students[temp->v].low]);
            }
            temp = temp->next;
        }
    }

    DFS();

    for(i = 0; i<no_v; ++i){
       printf("%d\n",graph_sccs[lows[students[i].low]].max_grade);
    }

    return 0;
}

int min(int A, int B){
    if(A > B){
        return B;
    } else {
        return A;
    }   
}

void addNodeToList(node ** root, int value){
    node * new = can_fail_malloc(sizeof(node));
    new->v = value;
    new->next = * root;
    * root = new;
}

int isNodeInList(node ** root, int value){
    node * buffer;

    buffer = * root;

    while(buffer){
        if (buffer->v == value)
            return 1;

        buffer = buffer->next;
    }
    return 0;
}

node * pop(node ** root){
    node * last = can_fail_malloc(sizeof(node));

    last = * root;

    *root = last->next;

    return last;
}

void sccTarjan(){
    visited = 0;
    L = NULL;
    int i;

    for(i = 0; i < no_v ; ++i){
        students[i].d = -1;
    }

    for(i = 0; i < no_v ; i ++){
        if(students[i].d == -1){
            tarjanVisit(i);
        }
    }
}

void tarjanVisit(int number){
    students[number].d = visited;
    students[number].low = visited;

    visited ++;

    addNodeToList(&L, students[number].id);

    node * buffer = students[number].adj_root;
    while(buffer != NULL){
        if (students[buffer->v].d == -1 || isNodeInList(&L, students[buffer->v].id)){
            if (students[buffer->v].d == -1){
                tarjanVisit(buffer->v);
            }
            students[number].low = min(students[number].low, students[buffer->v].low);
        }

        buffer = buffer->next;
    }
    
    if (students[number].d == students[number].low){
        node * removed = pop(&L);
        while(removed->v != students[number].id){
            removed = pop(&L);
        }
    }
}

void DFS(){
    int i;

    for(i = 0; i < counter; ++i){    
        graph_sccs[i].d = -1;
    }

    time = 1;

    for(i = 0; i < counter; ++i){
        DFSVisit(i);
    }
}

void DFSVisit(int number){
    int max = graph_sccs[number].max_grade;
    graph_sccs[number].d = time;

    time++;
    node * buffer2 = graph_sccs[number].adj_root;

    while(buffer2 != NULL){

        if (graph_sccs[buffer2->v].d == -1){
            DFSVisit(buffer2->v);
        }

        if(graph_sccs[buffer2->v].max_grade > max)
            max = graph_sccs[buffer2->v].max_grade;

        buffer2 = buffer2->next;
    }
    
    graph_sccs[number].max_grade = max;
    
    time++;
}