#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*  Made by:
 *      ist192470 - Guilherme Baeta Campos da Rocha Fontes
 *      ist192537 - Pedro Filipe Coelho Perpétua
 *  Group: al147
 */

/* ──────────────────────────────── Constants ─────────────────────────────── */

#define IN_SIZE 1024
#define EMPTY -1
#define BOTTOM 0
#define to_index(ID) (ID - 1)
#define min(A, B) (A < B) ? A : B /* Find min and return it */
#define max(A, B) (A > B) ? A : B /* Find max and return it */

/* ───────────────────────────── Libraries used ───────────────────────────── */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ───────────────────────────── Error Handling ──────────────────────────── */

void panic(char* msg) {
    /* Terminates the program with a panic message! */
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

/* ─────────────────────────────── Stack struct ───────────────────────────── */

typedef struct Stack {
    int top_index;
    int* stack_list;
} Stack;

Stack* initialize_stack() {
    /* Initializes a new stack structure. */
    Stack* new_stack = (Stack*)can_fail_malloc(sizeof(Stack));
    new_stack->top_index = EMPTY;
    return new_stack;
}

void push_stack(Stack* stack, int number) {
    /* Places a number into the stack. */
    if (stack->top_index == EMPTY) {
        stack->stack_list = (int*)can_fail_malloc(sizeof(int));
        if (!stack->stack_list) {
            panic("Failed to allocate memory for the stack.");
        }
    } else {
        stack->stack_list = (int*)can_fail_realloc(stack->stack_list,
                                          sizeof(int) * (stack->top_index + 2));
        if (!stack->stack_list) {
            panic("Failed to reallocate memory for the stack!");
        }
    }
    stack->top_index++;
    stack->stack_list[stack->top_index] = number;
}

int pop_stack(Stack* stack) {
    /* Returns the top number in the stack and decreases it's size. */
    int item;
    if (stack->top_index == EMPTY) {
        item = -1;
    } else if (stack->top_index == BOTTOM) {
        item = stack->stack_list[stack->top_index];
        stack->top_index = EMPTY;
        free(stack->stack_list);
    } else {
        item = stack->stack_list[stack->top_index];
        stack->top_index--;
        stack->stack_list = (int*)can_fail_realloc(stack->stack_list,
                                          sizeof(int) * (stack->top_index + 1));
        if (!stack->stack_list) {
            panic("Failed to reallocate memory for the stack!");
        }
    }
    return item;
}

void free_stack(Stack* stack) {
    /* Frees the allocated memory for the stack. */
    if (stack->top_index != EMPTY) {
        free(stack->stack_list);
    }
    free(stack);
}

/* ─────────────────────────────── Graph struct ────────────────────────────────
 */

typedef struct GraphNode GraphNode;

struct GraphNode { /* A node contains the id of a friend and a pointer to the
                      next node. */
    int index;
    GraphNode* next;
};

typedef struct StudentGraph {
    int num_students;
    int* grades;
    GraphNode** nodes; /* Pointers for the friends of each student */
} StudentGraph;

StudentGraph* new_student_graph(int size) {
    /* Initializes a new StudentGraph structure. */
    int i;
    StudentGraph* student_system = (StudentGraph*)can_fail_malloc(sizeof(StudentGraph));
    if (!student_system) {
        panic("Failed to allocate memory for the student system!");
    }
    student_system->num_students = size;
    student_system->grades = (int*)can_fail_malloc(sizeof(int) * size);
    if (!student_system->grades) {
        panic("Failed to allocate memory for the grade vector!");
    }
    student_system->nodes = (GraphNode**)can_fail_malloc(sizeof(GraphNode*) * size);
    if (!student_system->nodes) {
        panic("Failed to allocate memory for the nodes array!");
    }

    for (i = 0; i < size; i++) {
        student_system->nodes[i] = NULL;
    }
    return student_system;
}

void add_student(StudentGraph* student_system, int grade, int index) {
    student_system->grades[index] = grade;
}

void add_friend(StudentGraph* student_system, int student, int friend) {
    GraphNode* new_node = (GraphNode*)can_fail_malloc(sizeof(GraphNode));
    if (!new_node) {
        panic("Failed to allocate memory for a friend!");
    }
    new_node->index = friend;
    new_node->next = NULL;
    if (student_system->nodes[student] != NULL) {
        new_node->next = student_system->nodes[student];
    }
    student_system->nodes[student] = new_node;
}

void free_system(StudentGraph* student_graph) {
    /* Frees all the memory allocated for the StudentGraph structure. */
    int i;
    free(student_graph->grades);
    for (i = 0; i < student_graph->num_students; i++) {
        if (student_graph->nodes[i] != NULL) {
            GraphNode* current_node = student_graph->nodes[i];
            GraphNode* temp_node;
            while (current_node != NULL) {
                temp_node = current_node;
                current_node = current_node->next;
                free(temp_node);
            }
        }
    }
    free(student_graph->nodes);
    free(student_graph);
}

/* ───────────────────────── Miscellaneous functions ──────────────────────── */

StudentGraph* get_input() {
    /* Gets the input from stdin and organizes it into a graph, returning it. */
    int i, n_students, n_relationships;
    char line[IN_SIZE];

    if (!fgets(line, IN_SIZE, stdin)) {
        panic("Failed to get Input!");
    }
    if (sscanf(line, "%d,%d", &n_students, &n_relationships) != 2) {
        panic("Invalid Input!");
    }

    StudentGraph* student_graph = new_student_graph(n_students);

    /* Grade estimates of each student */
    int grade;
    for (i = 0; i < n_students; i++) {
        if (!fgets(line, IN_SIZE, stdin)) {
            panic("Failed to get Input!");
        }
        if (sscanf(line, "%d", &grade) != 1) {
            panic("Invalid Input");
        }
        add_student(student_graph, grade, i);
    }

    /* For each relationship, student [0] has [1] as a friend. */
    int student, friend;
    for (i = 0; i < n_relationships; i++) {
        if (!fgets(line, IN_SIZE, stdin)) {
            panic("Failed to get Input!");
        }
        if (sscanf(line, "%d %d", &student, &friend) != 2) {
            panic("Invalid Input!");
        }
        add_friend(student_graph, to_index(student), to_index(friend));
    }

    return student_graph;
}

void print_grades_formatted(StudentGraph* student_graph) {
    int i;
    for (i = 0; i < student_graph->num_students; i++) {
        printf("%d\n", student_graph->grades[i]); /* Print all student grades */
    }
}

/* ─────────────────────────────── Algorithm ───────────────────────────── */

typedef enum State { /* Student state */
                     NOT_VISITED,
                     ON_STACK,
                     VISITED,
} State;

typedef struct AlgorithmData { /* Data used in Tarjan's Algorithm */
    State* states;
    int* disc;
    int* lows;
    Stack* stack;
} AlgorithmData;

AlgorithmData* initialize_data(int num_students) {
    AlgorithmData* new_data = (AlgorithmData*)can_fail_malloc(sizeof(AlgorithmData));

    new_data->states = (State*)can_fail_calloc(
        num_students, sizeof(int)); /* Initialized as 0 (NOT_VISITED) */

    new_data->disc
        = (int*)can_fail_malloc(sizeof(int) * num_students); /* Time of discovery */
    new_data->lows
        = (int*)can_fail_malloc(sizeof(int) * num_students); /* Low-link values */

    new_data->stack = initialize_stack(); /* Assign stack to algorithm data */

    return new_data;
}

void free_data(AlgorithmData* data) {
    free(data->states);
    free(data->disc);
    free(data->lows);
    free_stack(data->stack);
    free(data);
}

/* Visit current student (node) */
void visit_maximize_grade(StudentGraph* student_graph, int node, int* time,
                          AlgorithmData* data) {
    (*time)++;
    data->states[node] = ON_STACK;
    data->disc[node] = *time;      /*Set initial time to current time*/
    data->lows[node] = *time;      /*Set low time to current time*/
    push_stack(data->stack, node); /*Push to the stack*/

    GraphNode* current_node = student_graph->nodes[node];
    int friend;
    while (current_node != NULL) {
        /* Checks every friend */
        friend = current_node->index;
        if (data->states[friend] == NOT_VISITED) {
            /* If the friend hasn't been visited, visits him */
            visit_maximize_grade(student_graph, friend, time, data);
            data->lows[node]
                = min(data->lows[node], data->lows[current_node->index]);
            student_graph->grades[node] = max(student_graph->grades[node],
                                              student_graph->grades[friend]);
        } else if (data->states[current_node->index] == ON_STACK) {
            data->lows[node]
                = min(data->lows[node], data->lows[current_node->index]);
            student_graph->grades[node] = max(student_graph->grades[node],
                                              student_graph->grades[friend]);
        } else {
            student_graph->grades[node] = max(student_graph->grades[node],
                                              student_graph->grades[friend]);
        }
        current_node = current_node->next;
    }

    if (data->disc[node] == data->lows[node]) {
        /* If the low time is equal to the initial time, then we found an SCC
         * and need to close it */
        int popped = pop_stack(data->stack);
        data->states[popped] = VISITED;
        student_graph->grades[popped] = student_graph->grades[node];
        while (popped != node) {
            popped = pop_stack(data->stack);
            data->states[popped] = VISITED;
            student_graph->grades[popped] = student_graph->grades[node];
        }
    }
}

void maximize_grade(StudentGraph* student_graph) {
    int i;
    int time = 0;

    AlgorithmData* data = initialize_data(student_graph->num_students);

    /* Makes sure every node is visited while the algorythm runs. */
    for (i = 0; i < student_graph->num_students; i++) {
        if (data->states[i]
            == NOT_VISITED) { /* Visit every unvisited student */
            visit_maximize_grade(student_graph, i, &time, data);
        }
    }

    free_data(
        data); /* Deallocate dynamically allocated memory for algorithm data  */
}

/* ─────────────────────────────── Main code ──────────────────────────────── */

int main() {

    StudentGraph* student_graph = get_input(); /* Get input and save it! */

    maximize_grade(student_graph); /* Maximize all students grades and... */
    print_grades_formatted(student_graph); /* ...print them in order! */

    free_system(student_graph); /* Deallocate dynamically allocated memory for
                                   the student graph */

    return 0;
}
