#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Guilherme Jardim 92471
Vasco Cabral 92568
ASA - 1º Projeto*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define TRUE 1

int nStudents, nFriendships;

enum color{White, Gray, Black}; 

typedef struct Friend {
    struct Friend *next;
    int studentIndex;
} Friend;

typedef struct Student {
    Friend *friend;
    enum color color; 
    int grade;
} Student;

typedef struct Grade {
    struct Grade *next; 
    int studentIndex; 
} Grade; 
typedef struct StudentGrade {
    Grade *similarGrade; 
} StudentGrade; 

void add_grade(StudentGrade *studentGrade, int grade, int studentIndex){
    Grade *value = can_fail_malloc(sizeof(Grade)); 
    value->studentIndex = studentIndex; 
    value->next = studentGrade[grade].similarGrade;
    studentGrade[grade].similarGrade = value; 
}

void add_edge(Student *students, int student, int friend) {
    Friend *connection = can_fail_malloc(sizeof(Friend)); 
    connection->studentIndex = friend; 
    connection-> next = students[student].friend; 
    students[student].friend = connection; 
}

void dfs_visit(Student *students, int student, int grade) {

    students[student].color = Gray; 
    students[student].grade = grade;

    Friend* temp = students[student].friend; 
    while(temp != NULL){
        if(students[temp->studentIndex].color == White){
            dfs_visit(students, temp->studentIndex, grade); 
        }
        temp = temp->next; 
    }

    students[student].color=Black;

}

void dfs(Student *students, StudentGrade *studentGrade){
    int i;

    Grade *temp; 
    for (i = 20; i >= 0 ; i--) {
        temp = studentGrade[i].similarGrade; 
        while (temp != NULL){
            if (students[temp->studentIndex].color == White){
                dfs_visit(students,temp->studentIndex, students[temp->studentIndex].grade);
            }
            temp = temp->next; 
        }
            
    }   
}


int main() {

    int i, link1, link2;

    scanf("%d,%d",&nStudents,&nFriendships);
    
    Student* students = can_fail_malloc(sizeof(Student) * nStudents);
    StudentGrade *studentGrade = can_fail_malloc(sizeof(StudentGrade)*21); 

    for(i = 0; i < 21; i++) {
        studentGrade[i].similarGrade=NULL; 
    }

    for (i = 0; i < nStudents; i++) {
        scanf("%d", &students[i].grade);
        add_grade(studentGrade,students[i].grade,i); 
        students[i].friend = NULL;
        students[i].color = White; 
    }

    for (i = 0; i < nFriendships; i++){
        scanf("%d %d", &link1, &link2); 
        add_edge(students, link2 - 1, link1 - 1); 
    }

    dfs(students,studentGrade);

    for(i = 0; i < nStudents; i++){
        printf("%d\n",students[i].grade); 
    }

    free(students);
    free(studentGrade);

    return 0;
}
