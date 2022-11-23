#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
/*Students are identified by a number ID.*/

/*-------------------------------------------------------------------------------------------------------------------
Structs
-------------------------------------------------------------------------------------------------------------------*/

/*Vertices with values*/
typedef struct StudentGrade {
    int id;
    int currentGrade;
    int changed; /*0 if the grade wasn't changed, 1 if it was*/
} StudentGrade;

/*Node containing a pointer to a student a pointer to the next node*/
typedef struct Node {
    StudentGrade* student;
    struct Node* next;
} Node;

/*List of adjacencies*/
typedef struct AdjacenciesList {
    Node** nodes; /*nodes[0] points to a node whose student is a friend of student 0, etc...*/
    int size;

} AdjacenciesList;

/*-------------------------------------------------------------------------------------------------------------------
Global variables
-------------------------------------------------------------------------------------------------------------------*/

AdjacenciesList list;
StudentGrade *studentsGrades;
int *sortAux;

/*-------------------------------------------------------------------------------------------------------------------
Auxiliary functions
-------------------------------------------------------------------------------------------------------------------*/

/*Count sourt. Auxiliary function to the radix sort. Sorts the numbers in descending order*/ 
void countSort(StudentGrade** array, int n, int exp)  {
    
    int i, count[10] = {0}; 
  
    /*Counts the amount of each digit and stores it in count[]*/
    for (i = 0; i < n; i++) {
        count[9 - (array[i]->currentGrade/exp)%10]++; 
    }      
  
    /*Change count[i] so that count[i] contains the sum of all previous indexes's numbers*/
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
  
    /*Build the sortAux array*/ 
    for (i = n - 1; i >= 0; i--) { 
        sortAux[--count[9 - (array[i]->currentGrade/exp)%10]] = array[i]->id; 
    }
  
    /*Copy the sortAux array to array[], so that array[] now contains sorted numbers according to current digit*/
    for (i = 0; i < n; i++) {
        array[i] = &studentsGrades[sortAux[i]];
    }
} 
  
/*Radix sort*/ 
void sort(StudentGrade** array, int n) {
    int max = array[0]->currentGrade, i, exp; 

    /*Iterating over the array to get the maximum number*/
    for (i = 1; i < n; i++) {
        if (array[i]->currentGrade > max) {
            max = array[i]->currentGrade;
        }    
    }      
  
    /*Applying the count sort to every digit of every number*/
    for (exp = 1; max / exp > 0; exp *= 10) {
        countSort(array, n, exp);
    }     
}

/*Changes the student's grade to the new grade if the student's grade was never changed, and does the same to all his friends*/
void changeStudentsGradeAndFriends(int newGrade, int id) {
    Node *auxNode = list.nodes[id]; /*Friend's node*/

    /*If the student's grade was already changed, then it is already the highest it will ever be, as well as its friends's*/
    if(studentsGrades[id].changed) return;

    studentsGrades[id].currentGrade = newGrade;
    studentsGrades[id].changed = 1;

    /*Checking if the student has at least 1 friend*/
    if(auxNode == NULL) return;

    /*Iterating over the student's friends to change their grades*/
    while(auxNode != NULL) {
        changeStudentsGradeAndFriends(newGrade, auxNode->student->id);

        auxNode = auxNode->next;
    }
}

/*-------------------------------------------------------------------------------------------------------------------
Main
-------------------------------------------------------------------------------------------------------------------*/

int main() {
    int amountStudents, amountFriendships, id, friendId, grade, i;
    Node *friendShipNodes/*, *auxNode*/;
    StudentGrade **queue;

    /*Getting the first number, which is the amount of students, and the second, which is the amount of friendships*/
    scanf("%d,%d", &amountStudents, &amountFriendships);

    /*Allocating memory*/
    list.nodes = (Node**) can_fail_malloc(sizeof(Node*) * amountStudents);
    friendShipNodes = (Node*) can_fail_malloc(sizeof(Node) * amountFriendships); /*Allocating enough space to create enough nodes to represent the adjacencies*/
    studentsGrades = (StudentGrade*) can_fail_malloc(sizeof(StudentGrade) * amountStudents);
    queue = (StudentGrade**) can_fail_malloc(sizeof(StudentGrade*) * amountStudents);
    sortAux = (int*) can_fail_malloc(sizeof(int) * amountStudents);

    list.size = amountStudents;

    /*Filling up the studentsGrades array*/
    for(i = 0; i < amountStudents; i++) {
        scanf("%d", &grade);

        studentsGrades[i].id = i;
        studentsGrades[i].currentGrade = grade;
        studentsGrades[i].changed = 0;

        list.nodes[i] = NULL;
        queue[i] = &studentsGrades[i];
    }
    
    /*Filling the adjacencies list with adjacencies. In this list, for algorithmic simplicity reasons, the relationships will be inverted. Ex: if the input
    says that 1 is friends with 3, the adjacencies list will register it as 3 being friends with 1*/
    for(i = 0; i < amountFriendships; i++) {
        scanf("%d %d", &friendId, &id);

        id--;
        friendId--;

        friendShipNodes[i].student = &studentsGrades[friendId];    

        if(list.nodes[id] == NULL) {
            friendShipNodes[i].next = NULL;

            list.nodes[id] = &friendShipNodes[i];
        }
        else {
            friendShipNodes[i].next = list.nodes[id];

            list.nodes[id] = &friendShipNodes[i];
        }
    }

    /*Sorting the queue, such that the students with higher grades will be the first on queue*/
    sort(queue, amountStudents);

    /*Iterating over the queue*/
    for(i = 0; i < amountStudents; i++) {
        changeStudentsGradeAndFriends(queue[i]->currentGrade, queue[i]->id);
    }

    /*Printing the result*/
    for(i = 0; i < amountStudents; i++) {
        printf("%d\n", studentsGrades[i].currentGrade);
    }

    /*Freeing the allocated memory*/
    free(list.nodes);
    free(friendShipNodes);
    free(studentsGrades);
    free(queue);
    free(sortAux);

    return 0;
}