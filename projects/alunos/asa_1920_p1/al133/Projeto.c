#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Nome: Rodrigo Foito de Amoreira Cidra, No: 92549 
   Nome: Joao Filipe Dias dos Santos, No: 92489 */

/* Librarys */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Data Structure */
typedef struct {
	int grade;
    int nfriends;
 	int* friends; 
    int color; 
} Student;

/*----------
 Prototypes
-----------*/

/* Functions */
void init();
void getGrades();
void addFriends();
void DFS();
void DFS_Visit(int student, int original);
void out();
void aux(int student, int pos);

/* Global Variables */
int NStudents, NFriendships = 0;        /* Number of students and number of friendships existing in whole class */
Student* class;                         /* Class that contains all students */
int state;
 
 /* Code */
int main() {
    init();
    getGrades();
    addFriends();
    while(state != 1)
        DFS();
    out();

    return 0;
} 

/*---------------------------
init(): Class initialization
---------------------------*/
void init() {
    int i;

    if(scanf("%d,%d", &NStudents, &NFriendships));
    class = can_fail_malloc(sizeof(Student)*NStudents);

    for(i = 0; i < NStudents; i++) {
        class[i].grade = 0;
        class[i].nfriends = 0;
        class[i].color = 0;
        class[i].friends = 0;
    }
}

/*----------------------------------
getGrades(): Grade that each student 
obtained in their first test
----------------------------------*/
void getGrades() {
    int value, i;
    for(i = 0; i < NStudents; i++) {
        if(scanf("%d", &value));
        class[i].grade = value;
    }
}

/*-----------------------
addFriends(): Friendships 
students have
-----------------------*/
void addFriends() {
    int student, friend, position, i;
    for(i = 0; i < NFriendships; i++) {
        if(scanf("%d %d", &student, &friend));

        class[student - 1].nfriends++;
        position = class[student - 1].nfriends;
        
        if (position == 1) 
            class[student - 1].friends = can_fail_malloc(sizeof(int));
        else   
            class[student - 1].friends = can_fail_realloc(class[student - 1].friends, sizeof(int)*(position));
        class[student - 1].friends[position - 1] = friend;
    }
}

/*-------------------
DFS(): DFS algorithm
-------------------*/
void DFS() {
    int i;
    state = 1;
    for (i = 0; i < NStudents; i++) {
        DFS_Visit(i, i);       
    }
}

void DFS_Visit(int student, int original) {
    int friend, i;
    int k = 0;
    class[student].color = 1;
    for (i = 0; i < class[student].nfriends; i++) {  
        friend = class[student].friends[i] - 1;
        if (class[original].grade < class[friend].grade)
            class[original].grade = class[friend].grade;
        if (class[friend].color == 0) 
            DFS_Visit(friend, original);
        else if (class[friend].color == 1 && class[friend].friends[k + 1] != 0)
            aux(friend, k + 1);
        if (class[student].grade < class[friend].grade) {
            class[student].grade = class[friend].grade; 
            state = 0;
        }
        k = i;
    }
    class[student].color = 2;
    k = 0;
}

void aux(int student, int pos) {
    int friend, i;
    for(i = pos; i < class[student].nfriends; i++) {
        friend = class[student].friends[i] - 1;
        if (class[friend].color == 0) 
            DFS_Visit(friend, student);
        if (class[friend].color == 1 && class[friend].friends[pos + 1] != 0)
            aux(friend, pos + 1);
        if (class[student].grade < class[friend].grade) {
            class[student].grade = class[friend].grade; 
            state = 0;
        }
    }
    class[student].color = 2;
}

/*-------------------------
out(): Prints the expected 
grades from each student
-------------------------*/
void out() {
    int i;
    for (i = 0; i < NStudents; i++) {
        printf("%d\n", class[i].grade);
    }
}