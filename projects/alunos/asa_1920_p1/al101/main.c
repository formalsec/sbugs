#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Miguel Gonçalves Jardim */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

#define FALSE 0
#define TRUE (!FALSE)

typedef struct {
    int id;
    int grade;
    int graded;
    int grading;
} student;

struct node;
typedef struct node* link;

typedef struct node {
    student* student;
    struct node* next;
} node;

typedef struct {
    node *head, *tail;
} list;

list** adj;

void insert(int src, int dest) {
    link new = (link) can_fail_malloc(sizeof(node));
    new->next = NULL;
    new->student = adj[dest]->head->student;

    list* l = adj[src];

    l->tail->next = new;
    l->tail = new;
}

void split(int* n, int* m, char arg) {

    char mStr[SIZE], nStr[SIZE];

    char c = getchar();
    int j = 0;
    while (c != arg) {
        if (c != ' ') nStr[j] = c;
        j++;
        c = getchar();
    }
    nStr[j] = '\0';
    
    c = getchar();
    j = 0;
    while (c != '\n' && c != '\0' && c != EOF) {
        if (c != ' ') mStr[j] = c;
        j++;
        c = getchar();
    }
    mStr[j] = '\0';

    *n = atoi(nStr);
    *m = atoi(mStr);
}

void processStudents(int n) {
    int i;

    for (i = 0; i < n; i++) {
        student* new = (student*) can_fail_malloc(sizeof(student));

        scanf("%d", &(new->grade));
        new->graded = FALSE;
        new->id = i;
        new->grading = FALSE;

        list* newList = (list*) can_fail_malloc(sizeof(list));
        link newNode = (link) can_fail_malloc(sizeof(node));

        newNode->student = new;
        newNode->next = NULL;

        adj[i] = newList;
        adj[i]->head = newNode;
        adj[i]->tail = newNode;
    }
}


void processRelationships(int m) {
    int i;

    int u, v;
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        insert(u - 1, v - 1);
    }

}

void grade(int id) {
    list* l = adj[id];
    l->head->student->grading = TRUE;

    link current = l->head->next;

    int finished = TRUE;
    
    while (current != NULL) {
        if (!current->student->grading) {
            if (!adj[current->student->id]->head->student->graded) {
                grade(current->student->id);
                if (!current->student->graded) finished = FALSE;
            }
        }
        else {
            finished = FALSE;
        }

        if (current->student->grade > l->head->student->grade) {
            l->head->student->grade = current->student->grade;
        }

        current = current->next;
    }

    l->head->student->graded = finished;
    l->head->student->grading = FALSE;
}

void compute(int n) {
    int i = 0;
    for (i = 0; i < n; i++) {
        if (!adj[i]->head->student->graded) {
            grade(i);
            adj[i]->head->student->graded = TRUE;
        }
    }
    
}

int main() {
    int n, m, i;
    split(&n, &m, ',');

    if (n < 2 || m < 1) {
        printf("Invalid input.");
    }

    adj = (list**) can_fail_malloc(sizeof(list*) * n);

    processStudents(n);
    
    processRelationships(m);

    compute(n);
     
    for (i = 0; i < n; i++) {
        printf("%d\n", adj[i]->head->student->grade);
    }

    for (i = 0; i < n; i++) {
        list* l = adj[i];
        link head = l->head;
        link next;
        link current = head->next;;

        free(head->student);
        free(head);

        if (current != NULL) {
            while (current->next != NULL) {
                next = current->next;
                free(current);
                current = next;
            }
            free(current);
        }
        free(l);
    }
    free(adj);

    return 0;
}