/*
    Projeto 1 - ASA

    Paulo do O, 92535

    The program first recieves a number of students and a number of one-sided friendships, then
    the grades of each student, then every friendship relation, and calculates the grade of every
    student, assuming they'll get the same grade as their friends (by sharing solutions).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CLEAR - wasn't visited yet; VISITED - visited at least once; CLOSED - visited all parent nodes*/
typedef enum state {CLEAR, VISITED, CLOSED} State;

typedef struct student{
    int grade;
    State state;
    int friend_amount;
    /* instead of people they have as friends, each student stores the 
    people that have them as friends (aka parent nodes)*/
    struct student** is_friends;
} Student;

Student *new_student(int grade, int total_students){
    Student *student = malloc(sizeof(Student));
    student->grade = grade;
    student->state = CLEAR;
    student->friend_amount = 0;
    student->is_friends = NULL;
    return student;
}

/* visits a given student */
void visit_friend(Student* friend){
    if(friend->friend_amount == 0)
        return;
    friend->state = VISITED;

    int i;
    for(i = 0; i < friend->friend_amount; i++){
        /* only visits the student whose friend I am if my grade changes theirs; 
        otherwise everyone that is friends with them already has a better grade 
        than me so don't need to visit*/
        if(friend->grade > friend->is_friends[i]->grade){
            friend->is_friends[i]->grade = friend->grade;
            visit_friend(friend->is_friends[i]);
        }
    }
    friend->state = CLOSED;
}

int main(){
    char *line = malloc(sizeof(char)*100);
    fgets(line, 100, stdin);

    int n = 0, m = 0;
    n = atoi(strtok(line, ","));
    m = atoi(strtok(NULL, ","));

    /* value verification */
    if(n < 2)
        n = 2;
    if(m < 1)
        m = 1;

    int student_counter = 0;
    Student **students = malloc(n * sizeof(Student));

    while(student_counter < n){
        fgets(line, 100, stdin);
        int grade = atoi(line);
        students[student_counter] = new_student(grade, n);
        student_counter++;
    }

    int a = 0, b = 0;
    int i;
    for(i = 0; i < m; i++){
        fgets(line, 100, stdin);
        sscanf(line, "%d %d", &a, &b);
        students[b-1]->friend_amount++;
        students[b-1]->is_friends = realloc(students[b-1]->is_friends, students[b-1]->friend_amount*sizeof(Student));
        students[b-1]->is_friends[students[b-1]->friend_amount-1] = students[a-1];
    }

    free(line);
    /* visit every student that hasn't been visited yet */
    for(i = 0; i < n; i++)
        if(students[i]->state == CLEAR)
            visit_friend(students[i]);

    for(i = 0; i < n; i++){
        printf("%d\n", students[i]->grade);
        free(students[i]->is_friends);
        free(students[i]);
    }

    free(students);

    return 0;
}
