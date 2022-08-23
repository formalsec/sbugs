/* al153 - Rodrigo Santos */

#include <stdio.h>
#include <stdlib.h>

/* Student structure */
typedef struct student {
    int d_time;
    int f_time;
    int student_index;
    int grade;
    struct student* friend;
} student;

/* Global vars */
int i;
student** class;
int *visited;
int n, m;

void readUserInput();
void putFriend(int, int);
void doDfs();
void doDfsVisit(int);
void spreadMaxGrade();
void clean();

void readUserInput() {

    int grade_input;
    int u, v;

    scanf("%d,%d", &n, &m);
    class = (student**)malloc(n*sizeof(student*));

    /* The *class Array index differs from student idex by 1 integer*/
    for (i = 0; i < n; i++) {
        class[i] = (student*)malloc(sizeof(student));
        scanf("%d", &grade_input);
        class[i]->d_time = class[i]->f_time = -1;
        class[i]->student_index = i;
        class[i]->grade = grade_input;
        class[i]->friend = NULL;
    }
    for (i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        putFriend(u - 1, v - 1);
    }
}

void putFriend(int u, int v) {

    student *c, *u_buddy;

    /* The elements d_time and f_time of the new allocated
    structure u_buddy are not initialized*/
    u_buddy = (student*)malloc(sizeof(student));
    u_buddy->student_index = v;
    u_buddy->grade = class[v]->grade;
    u_buddy->friend = NULL;

    if (class[u]->friend == NULL)
        class[u]->friend = u_buddy;
    else {
        c = class[u]->friend;

        while (c->friend != NULL)
            c = c->friend;
        c->friend = u_buddy;
    }
}

void doDfs() {

    /* visited array is all set to zero */
    visited = (int*)calloc(n, sizeof(int));

    for (i = 0; i < n; i++)
        if (!visited[i])
            doDfsVisit(i);

}

void doDfsVisit(int src) {

    static int k = 1;
    int node;
    student *s;

    s = class[src];
    visited[src] = 1;
    class[src]->d_time = k++;

    while (s != NULL) {
        node = s->student_index;
        if (!visited[node])
            doDfsVisit(node);
        s = s->friend;
    }
    class[src]->f_time = k++;
}

void spreadMaxGrade() {

    int j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (class[i]->d_time < class[j]->d_time &&
             class[i]->f_time > class[j]->f_time &&
             class[i]->grade < class[j]->grade)
                class[i]->grade = class[j]->grade;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (class[j]->grade > class[i]->grade &&
             class[i]->friend != NULL &&
             class[i]->friend->student_index == class[j]->student_index)
                class[i]->grade = class[j]->grade;
}

void clean() {

    student* temp;

    for (i = 0; i < n; i++)
        while (class[i]) {
            temp = class[i];
            class[i] = class[i]->friend;
            free(temp);
        }
    free(class);
    free(visited);
}

int main() {

    readUserInput();

    doDfs();

    spreadMaxGrade();

    for (i = 0; i < n; i++)
        printf("%d\n", class[i]->grade);

    clean();

    return 0;
}
