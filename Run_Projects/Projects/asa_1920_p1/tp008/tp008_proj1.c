/* Primeiro projeto - Analise e Sintese de Algoritmos
 * Antonio Elias: 93690
 * Ruben Inacio:  93755
 * Grupo: tp008
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN(__X, __Y) (__X) < (__Y) ? (__X) : (__Y)
#define MAX(__X, __Y) (__X) > (__Y) ? (__X) : (__Y)
#define DEFAULT -1

typedef struct node {
    int id;
    struct node *next;
} node_t;

typedef struct student {
    int scc, d, low, grade;
    node_t *group;
} student_t;

typedef struct scc {
    int grade;
    node_t *group;
} scc_t;

typedef struct stack {
    int *lifo, *values, top;
} stack_t;

int N;          /* Number of students. */
int M;          /* Number of friendships. */
int visited;
stack_t *stack;
scc_t *scc;
int scc_counter;

scc_t* create_scc_array(){
    int i;
    scc_t *scc = malloc(N * sizeof(scc_t));
    for (i = 0; i < N; i++){
        scc[i].grade = 0;
        scc[i].group = NULL;
    }
    return scc;
}

stack_t* create_stack(){
    stack_t *stack = malloc(sizeof(stack_t));
    stack -> lifo = malloc(N * sizeof(int));
    stack -> values = malloc(N * sizeof(int));
    stack -> top = 0;
    return stack;
}

void delete_stack(){
    free(stack -> lifo);
    free(stack -> values);
    free(stack);
}

void push(stack_t *stack, int value){
    stack -> values[value] = 1;
    stack -> lifo[stack -> top++] = value;
}

int pop(stack_t *stack){
    int value = stack -> lifo[--(stack -> top)];
    stack -> values[value] = 0;
    return value;
}

int contains(stack_t *stack, int value){
    return stack -> values[value];
}

node_t* insert(node_t *head, node_t *node){
    node -> next = head;
    return node;
}

node_t* create_node(int id){
    node_t *node = malloc(sizeof(node_t));
    node -> id = id;
    node -> next = NULL;
    return node;
}

student_t new_student(int grade){
    student_t student;
    student.scc = DEFAULT;
    student.grade = grade;
    student.group = NULL;
    student.d = DEFAULT;
    student.low = DEFAULT;
    return student;
}

void create_students(student_t *students){
    int i, grade;
    for (i = 0; i < N; i++){
        scanf("%d", &grade);
        students[i] = new_student(grade);
    }
}

void create_friendships(student_t *students){
    int i, self_id, friend_id;
    for (i = 0; i < M; i++) {
        scanf("%d %d", &self_id, &friend_id);
        self_id--;
        friend_id--;
        students[self_id].group = insert(students[self_id].group, create_node(friend_id));
    }
}

void delete_groups(student_t *students){
    int i;
    for(i = 0; i < N; i++)
        while(students[i].group){
            node_t *aux = students[i].group;
            students[i].group = students[i].group -> next;
            free(aux);
        }
}

void create_scc_dag(student_t *students){
    int i;

    for(i = 0; i < N; i++){
        node_t *friend;
        for(friend = students[i].group; friend; friend = friend -> next)
            if (students[i].scc != students[friend -> id].scc)
                scc[students[i].scc].group = insert(scc[students[i].scc].group, create_node(students[friend -> id].scc));
    }
}

void tarjan_visit(student_t *students, int u){
    node_t *friend;
    int i = DEFAULT;
    students[u].low = visited;
    students[u].d = visited++;
    push(stack, u);
    for (friend = students[u].group; friend; friend = friend -> next)
        if (students[friend -> id].d == DEFAULT || contains(stack, friend -> id)){
            if(students[friend -> id].d == DEFAULT)
                tarjan_visit(students, friend -> id);

            students[u].low = MIN(students[friend -> id].low, students[u].low);
        }

    if (students[u].d == students[u].low){
        while(i != u){
            i = pop(stack);
            students[i].scc = scc_counter;
            scc[scc_counter].grade = MAX(scc[scc_counter].grade, students[i].grade);
        }  
        scc_counter++;
    }
}

void scc_tarjan(student_t *students){
    int i;
    for(i = 0; i < N; i++)
        if (students[i].d == DEFAULT)
            tarjan_visit(students, i);
}

void evaluate_dag(){
    int i;
    node_t *friend;
    for(i = 0; i < scc_counter; i++)
        for (friend = scc[i].group; friend; friend = friend -> next)
            scc[i].grade = MAX(scc[i].grade, scc[friend -> id].grade);
}

void print_grades(student_t *students){
    int i;
    for(i = 0; i < N; i++){
        students[i].grade = scc[students[i].scc].grade;
        printf("%d\n", students[i].grade);
    }
}

int main() {
    student_t *students;

    scanf("%d, %d", &N, &M);
    students = malloc(N * sizeof(student_t));
    scc = create_scc_array();
    stack = create_stack();
    scc_counter = 0;
    visited = 0;

    create_students(students);

    create_friendships(students);

    scc_tarjan(students);

    create_scc_dag(students);

    evaluate_dag();

    print_grades(students);

    delete_groups(students);
    delete_stack(stack);
    free(students);
    free(scc);
    return 0;
}

