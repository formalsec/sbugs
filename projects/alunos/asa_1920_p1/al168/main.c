#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*================================== MACROS ==================================*/

#define MAX_GRADE 20

/*================================ STRUCTURES ================================*/

/* Student structure to store grade and friends */
typedef struct student {
    int flag; /* flag to check if this student's grade has changed already */
    int grade;
    struct node* friendlist;
} Student;

/* Linked list nodes that store students */
typedef struct node {
    struct student* content;
    struct node* next;
} Node;

/*============================= GLOBAL VARIABLES =============================*/

int num_students, num_relations;
Student** students; /* Ordered array of students */
Node* grade_table[MAX_GRADE + 1]; /* Hash table that stores students by grade */

/*============================== INITIALISATION ==============================*/

void init_student_array() {
    students = can_fail_malloc(sizeof(struct student*) * num_students);
}

void init_grade_table() {
    memset(grade_table, 0, sizeof grade_table); /* Fill wit NULL pointers */
}

Student* new_student(int grade) {
    Student* s = can_fail_malloc(sizeof(struct student));
    s->flag = 0;
    s->grade = grade;
    s->friendlist = NULL;
    return s;
}

Node* new_node(Student* s) {
    Node* n = can_fail_malloc(sizeof(Node));
    n->content = s;
    n->next = NULL;
    return n;
}

/*========================== LINKED LIST FUNCTIONS ===========================*/

void add_node(Node** head, Node* node) { /* Add node to a linked list */
    node->next = *head;
    *head = node;
}

/*============================ STUDENT FUNCTIONS =============================*/

/* Place student in the grade_table */
void assign_grade(Student* s) {
    add_node(&grade_table[s->grade], new_node(s));
}

/* Add student to a friendlist */
void add_friend(Student* s, Student* friend) {
    add_node(&s->friendlist, new_node(friend));
}

void change_grade(Student* s, int grade) {
    s->grade = grade;
    s->flag = 1; /* Signal that this student's grade has already been altered */
}

/*============================== DFS ALGORITHM ===============================*/

/* Give a student and all his friends the same grade */
void update_friend_grades(Student* s, int grade) {
    if(!s->flag) { /* Only if it hasn't already been done */
        change_grade(s, grade);

        Node* n;
        for(n = s->friendlist; n != NULL; n = n->next) { /* for each node n in a friend list */
            update_friend_grades(n->content, grade);
        }
    }
}

/* Give all students the highest grade possible */
void update_all_grades() {
    int i;
    for(i = MAX_GRADE; i >= 0; i--) {
        Node* n;
        for(n = grade_table[i]; n != NULL; n = n->next) {
            update_friend_grades(n->content, i);
        }
    }
}

/*=========================== AUXILIARY FUNCTIONS ============================*/

/* Print out the final grades */
void display_grades() {
    int i;
    for (i = 0; i < num_students; i++) {
        printf("%d\n", students[i]->grade);
    }
}

/*================================== FREES ===================================*/

void free_list(Node* head) {
    Node* n = head;
    while(n != NULL) {
        Node* tmp = n->next;
        free(n);
        n = tmp;
    }
}

void free_grade_table() {
    int i;
    for(i = 0; i <= MAX_GRADE; i++)
        free_list(grade_table[i]);
}

void free_student(Student* s) {
    free_list(s->friendlist);
    free(s);
}

void free_all_students() {
    int i;
    for(i = 0; i < num_students; i++)
        free_student(students[i]);
    free(students);
}

/*=================================== MAIN ===================================*/

int main() {
    int i;
    scanf("%d,%d", &num_students, &num_relations);

    init_grade_table();
    init_student_array();

    /* Read all the student's grades */
    for(i = 0; i < num_students; i++) {
        int grade;
        scanf("%d", &grade);
        Student* s = new_student(grade);
        students[i] = s; /* Place the student in the student array */
        assign_grade(s); /* Place the student in the grade table */
    }
    /* Read the relationships between the students */
    for(i = 0; i < num_relations; i++) {
        int index_friend, index_student;
        scanf("%d %d", &index_friend, &index_student);
        add_friend(students[index_student-1], students[index_friend-1]);
    }

    update_all_grades();

    display_grades();

    free_grade_table();
    free_all_students();

    return 0;
}
