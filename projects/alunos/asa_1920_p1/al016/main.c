#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct vertex {
    int num;
    int predicted_grade;
    int d;
    int low;
    int is_in_stack;
}* vertex;

typedef struct node {
    struct node* next;
    vertex vertex;
}* node;

int min(int i, int j);
int max(int i, int j);
vertex new_vertex(int num);
node new_node(vertex v);
void insert_ad_list_table(vertex u, vertex v);
void free_ad_list(node ad_list_head);
void push(vertex v);
vertex pop();
void Tarjan_visit(vertex v);
void SCC_Tarjan();
void inicialise_ad_list_table();
void initialise_vertexes();
void process_input();
void print_predicted_grades();
void free_vertexes();
void free_ad_list_table();
void free_sccs_ad_list_table();
int main();

int num_vertexes;
vertex* vertexes;
node* ad_list_table;
node stack_head;
int time;

int min(int i, int j) {
    if(i < j) {
        return i;
    }
    return j;
}

int max(int i, int j) {
    if(i > j) {
        return i;
    }
    return j;
}

vertex new_vertex(int num) {
    vertex v = (vertex)can_fail_malloc(sizeof(struct vertex));
    v->num = num;
    v->predicted_grade = -1;
    v->d = -1;
    v->low = -1;
    v->is_in_stack = FALSE;
    return v;
}

node new_node(vertex v) {
    node new_node = (node)can_fail_malloc(sizeof(struct node));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

void insert_ad_list_table(vertex u, vertex v) {
    node cur_node, prev_node;
    if(ad_list_table[u->num-1] == NULL) {
        ad_list_table[u->num-1] = new_node(v);
    }
    else {
        cur_node = ad_list_table[u->num-1];
        while(cur_node != NULL) {
            prev_node = cur_node;
            cur_node = prev_node->next;
        }
        prev_node->next = new_node(v);
    }
}

void free_ad_list(node ad_list_head) {
    node cur_node, next_node;
    cur_node = ad_list_head;

    while(cur_node != NULL) {
        next_node = cur_node->next;
        free(cur_node);
        cur_node = next_node;
    }
}


void push(vertex v) {
    node new_node = (node)can_fail_malloc(sizeof(struct node));

    new_node->vertex = v;

    new_node->next = stack_head;
    stack_head = new_node;
}

vertex pop() {
    node top_node = stack_head;
    vertex v = top_node->vertex;

    stack_head = stack_head ->next;

    free(top_node);

    return v;
}

void Tarjan_visit(vertex v) {
    node a = ad_list_table[v->num-1];
    vertex popped_vertex = NULL;

    v->d = time;
    v->low = time;
    time++;

    push(v);
    v->is_in_stack = TRUE;

    while(a != NULL) {
        if(a->vertex->d == -1) {
            Tarjan_visit(a->vertex);
            v->low = min(v->low, a->vertex->low);
        }
        else if(a->vertex->is_in_stack) {
            v->low = min(v->low, a->vertex->low);
        }

        v->predicted_grade = max(v->predicted_grade, a->vertex->predicted_grade);

        a = a->next;
    }

    if(v->d == v->low) {
        popped_vertex = pop();

        popped_vertex->is_in_stack = FALSE;

        while(popped_vertex->num != v->num) {
            popped_vertex->predicted_grade = v->predicted_grade;

            popped_vertex = pop();
            
            popped_vertex->is_in_stack = FALSE;
        }
    }
}

void SCC_Tarjan() {
    int i;
    time = 0;
    for(i = 0; i < num_vertexes; i++) {
        vertexes[i]->d = -1;
        vertexes[i]->low = -1;
        vertexes[i]->is_in_stack = FALSE;
    }
    for(i = 0; i < num_vertexes; i++) {
        if(vertexes[i]->d == -1) {
            Tarjan_visit(vertexes[i]);
        }
    }
}

void inicialise_ad_list_table() {
    int i;
    ad_list_table = (node*)can_fail_malloc(sizeof(node)*num_vertexes);
    for(i = 0; i < num_vertexes; i++) {
        ad_list_table[i] = NULL;
    }
}

void initialise_vertexes() {
    int i;
    vertexes = (vertex*)can_fail_malloc(sizeof(vertex)*num_vertexes);
    for(i = 0; i < num_vertexes; i++) {
        vertexes[i] = new_vertex(i + 1);
    }
}

void process_input() {
    int num_students;
    int num_friendships;
    int predicted_grade;
    int student;
    int friend;
    int i;

    scanf("%d, %d", &num_students, &num_friendships);

    if(num_students < 2) {
        perror("Number of students must be greater than 2\n");
        exit(-1);
    }

    if(num_friendships < 1) {
         perror("Number of friendships must be greater than 1\n");
         exit(-1);
    }

    num_vertexes = num_students;

    initialise_vertexes();

    inicialise_ad_list_table();

    for(i = 0; i < num_vertexes; i++) {
        scanf("%d", &predicted_grade);
        vertexes[i]->predicted_grade = predicted_grade;
    }

    for(i = 0; i < num_friendships; i++) {
        scanf("%d %d", &student, &friend);
        insert_ad_list_table(vertexes[student-1], vertexes[friend-1]);
    }
}

void print_predicted_grades() {
    int i;
    for(i = 0; i < num_vertexes; i++) {
        printf("%d\n", vertexes[i]->predicted_grade);
    }
}

void free_vertexes() {
    int i;
    for(i = 0; i < num_vertexes; i++) {
        free(vertexes[i]);
    }
    free(vertexes);
}

void free_ad_list_table() {
    int i;
    for(i = 0; i < num_vertexes; i++) {
        free_ad_list(ad_list_table[i]);
    }
    free(ad_list_table);
}

int main() {
    /*Aqui acontece o processamento do input*/
    process_input();

    SCC_Tarjan();

    /*Aqui o resultado é impresso*/
    print_predicted_grades();

    /*frees*/
    free_vertexes();
    free_ad_list_table();

    return 0;
}
