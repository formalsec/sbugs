#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* ListNode;

typedef struct student {
    int grade; /* Predicted project's grade */
    int isDone; /* If student already has the highest grade possible */
    ListNode helpees; /* Linked List of students that have him as a friend */
} Student;

struct listNode {
    Student* student;
    ListNode next;
};

/**
 * Frees all the nodes of a linked list.
 * 
 * Input:
 *  -node: Head of the linked list
*/
void freeList(ListNode node) {
    if (node == NULL) return;
    freeList(node->next);
    free(node);
}

void merge(Student* arr[], int l, int m, int r) { 
    int i, j, k;
    int szL = m - l + 1;
    int szR = r - m;
    Student** L = (Student **) malloc(szL * sizeof(Student *));
    Student** R = (Student **) malloc(szR * sizeof(Student *));
    
    for (i = 0; i < szL; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < szR; j++) {
        R[j] = arr[m + 1+ j];
    }

    i = 0; j = 0; k = l;
    while (i < szL || j < szR) {
        if (j>=szR || (i<szL && L[i]->grade <= R[j]->grade)) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    free(L);
    free(R);
}

/**
 * Sorts an array of students from lowest grade to highest.
 * 
 * Input:
 *  -arr: Array of students to be sorted
 *  -l: Left bound
 *  -r: Right bound
*/
void mergeSort(Student* arr[], int l, int r) {
    int m;
    if (l >= r) return;

    m = (l+r)/2;
    mergeSort(arr, l, m); 
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
}

/** 
 * Adds student "u" to list of friends of student "v".
 * 
 * Input:
 *  -u: student that has "v" as a friend
 *  -v: student that is a friend of "u"
*/
void addFriend(Student* u, Student* v) {
    ListNode newNode = (ListNode) malloc(sizeof(struct listNode));
    newNode->student = u;
    newNode->next = v->helpees;
    v->helpees = newNode;
}

/**
 * Spreads the grade of "student" to all students who have a path to
 * him through friends.
 * 
 * Input:
 *  -student: Address of the student whose grade should be spread
*/
void spreadGrade(Student* student) {
    ListNode aux;
    if (student->isDone) return;
    aux = student->helpees;
    student->isDone = 1;
    while (aux != NULL) {
        if (aux->student->grade < student->grade) {
            aux->student->grade = student->grade;
        }
        spreadGrade(aux->student);
        aux = aux->next;
    }
}

/**
 * Predict the grades of all the students in a sorted array.
 * 
 * Input:
 *  -arr: Sorted array of students
 *  -size: Size of "arr"
*/
void predictGrades(Student* arr[], int size) {
    int i;
    for (i=size-1; i>=0; i--) {
        spreadGrade(arr[i]);
    }
}

int main() {
    Student *students, **studentsSorted;
    int i, numStudents, numRelations, u, v;

    scanf("%d,%d", &numStudents, &numRelations);
    /* Allocate 2 arrays to be able to sort the students while also preserving
    their original order which will be used to write the output */
    students = (Student *) malloc(numStudents * sizeof(Student));
    studentsSorted = (Student **) malloc(numStudents * sizeof(Student*));

    /* Read and register all students' grades and initialize other attributes */
    for (i=0; i<numStudents; i++) {
        scanf("%d", &students[i].grade);
        students[i].isDone = 0;
        students[i].helpees = NULL;
        studentsSorted[i] = &students[i];
    }

    /* Read and register all the friend relations */
    for (i=0; i<numRelations; i++) {
        scanf("%d %d", &u, &v);
        addFriend(&students[u-1], &students[v-1]);
    }

    /* Sort the students by grade */
    mergeSort(studentsSorted, 0, numStudents-1);
    
    predictGrades(studentsSorted, numStudents);

    /* Print the predicted grades of all the students */
    for (i=0; i<numStudents; i++) {
        printf("%d\n", students[i].grade);
        /* Free each students' helpees list */
        freeList(students[i].helpees);
    }
    free(students);
    free(studentsSorted);

    return 0;
}