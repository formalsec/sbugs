/* 1o projecto de ASA 2019/2020
    Tomas Sequeira n.92565
    Miguel Pereira n.92530
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct student_link {
    int num;
    struct student_link* next;
} *link;

typedef struct student {
    int num, grade;
    link links;
    int visited;
} Student;

typedef struct visit {
    int num;
    struct visit *next;
} Visit;

link newLink(Student* s) {
    link l;
    l = (link) malloc(sizeof(struct student_link));

    l->num = s->num;
    l->next = NULL;

    return l;
}

void insertLink(Student* first, Student* second) {
    link new_l = newLink(second);

    if (first->links == NULL) {
        first->links = new_l;
    }
    else {
        new_l->next = first->links;
        first->links = new_l;
    }
}

void freeLinks(link head) {
    link item = head;
    link aux = NULL;
    while (item != NULL) {
        aux = item;
        item = item->next;
        free(aux);
    }
}

Visit* newVisit(int num) {
    Visit* v = (Visit*) malloc(sizeof(Visit));

    v->num = num;
    v->next = NULL;

    return v;
}

Visit* addVisit(Visit* head, int num) {
    Visit* v = newVisit(num);

    if (head == NULL)
        head = v;
    else {
        v->next = head;
        head = v;
    }
    
    return head;
}

void freeVisits(Visit* head) {
    Visit* item = head;
    Visit* aux = NULL;
    while (item != NULL) {
        aux = item;
        item = item->next;
        free(aux);
    }
}

Student* students;

Visit *visits;

void visit(int num) {
    students[num].visited = 1;
}

void resetVisited(int num) {
    students[num].visited = 0;
}

int visited(int num) {return students[num].visited;}

int maxN(int n1, int n2) {
    if (n1 > n2) return n1;
    else         return n2;
}

int calcMax(int size, Visit* visits) {
    int num, max = 0;
    Visit* aux;
    for (aux = visits; aux != NULL; aux = aux->next) {
        num = aux->num;
        max = maxN(students[num].grade, max);
        resetVisited(num);
    }
    return max;
}

Visit* calcLinks(int num, Visit* visits) {
    link aux;
    int naux;
    if (!visited(num)) {
        visit(num);
        visits = addVisit(visits, num);
        for (aux = students[num].links; aux != NULL; aux = aux->next) {
            naux = aux->num;
            visits = calcLinks(naux, visits);
        }
    }
    return visits;
}

int main() {
    int i = 0, temp1 = 0, temp2 = 0;
    int n_size, n_links;

    /* input numero de alunos e de ligacoes entre alunos */
    scanf("%d,%d", &n_size, &n_links);
    students = (Student*) malloc(sizeof(Student)*n_size);

    /* input alunos */
    for (i = 0; i < n_size; i++) {
        students[i].num = i;
        scanf("%d", &(students[i].grade));
        students[i].links = NULL;
        students[i].visited = 0;
    }
    /* input ligacoes entre alunos */
    for (i = 0; i < n_links; i++) {
        scanf("%d %d", &temp1, &temp2);
        insertLink(&students[temp1-1], &students[temp2-1]);
    }

    /* algoritmo para recalcular notas */
    for (i = 0; i < n_size; i++) {
        Visit* visits = NULL;
        visits = calcLinks(i, visits);
        printf("%d\n", calcMax(n_size, visits));
        freeVisits(visits);
    }

    for (i = 0; i < n_size; i++) {
        freeLinks(students[i].links);
    }
    free(students);
    
    return 0;
}