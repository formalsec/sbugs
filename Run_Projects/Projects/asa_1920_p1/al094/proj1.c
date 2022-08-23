#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct student {
    int id;
    int grade;
    int nFriends;
    int visited;
    int visiting;
    int wait;
    struct student* *friends; /*filhos na arvore*/
} Student;

typedef Student* pStudent; /*ponteiro para estudantes*/

typedef struct friendship {
    int id;
    int friend;
} Friendship;

char* readInput(int length){
    int c;
    int i = 0;
    char *v = (char*) malloc(sizeof(char) * length);
    c = getchar();
    while (c != EOF && c != '\0'){
        if (i == (length - 1)){
            length = length * 2;
            v = (char*) realloc(v, sizeof(char) * length);
        }
        v[i++] = c;
        c = getchar();
    }
    v[i] = '\0';
    return v;
}

char* processFirstLine(char *input, int *position, char mark){
    int j = 0, pos = *position, length = 3;
    char *s = (char*) malloc(sizeof(char) * length);
    while (input[pos] != mark && input[pos] != '\0'){
        if (j == (length - 1)){
            length = length * 2;
            s = (char*) realloc(s, sizeof(char) * length);
        }
        s[j++] = input[pos++];
    }
    s[j] = '\0';
    *position = ++pos;
    return s;
}

void processGrades(char *input, int *vec, int *position, int n){
    int j, i, pos = *position, lenght = 3;
    char *c = (char*) malloc(sizeof(char) * lenght);
    for (j = 0; j < n - 1; j++){
        i = 0;
        while (input[pos] != '\n' && input[pos] != EOF) {
            if (i == (lenght - 1)) {
                lenght = lenght * 2;
                c = (char*) realloc(c, sizeof(char) * lenght);
            }
            c[i++] = input[pos++];
        }
        pos++;
        c[i] = '\0';
        vec[j] = atoi(c);
    }
    vec[j] = '\0';
    *position = pos;
    free(c);
}

char* nextChar(char *input, char *c, int *position){
    int i, pos = *position, length = 3;
    i = 0;
    while (input[pos] != '\n' && input[pos] != ' ' && input[pos] != '\0') {
        if (i == (length - 1)) { 
            length = length * 2;
            c = (char*) realloc(c, sizeof(char) * length);
        }
        c[i++] = input[pos++];
    }
    c[i] = '\0';
    *position = ++pos;
    return c;
}

void processFriendships(char *input, Friendship *vec, int *position, int n){
    int j;
    char *c = (char*) malloc(sizeof(char) * 3);
    for (j = 0; j < n; j++){
        nextChar(input, c, position);
        vec[j].id = atoi(c);
        nextChar(input, c, position);
        vec[j].friend = atoi(c);
    }
    free(c);
}

void initializeStudents(pStudent *s, int *g, int n){
    int i;
    for (i = 0; i < n; i++){
        pStudent student = (pStudent) malloc(sizeof(Student));
        student->id = i + 1;
        student->grade = g[i];
        student->nFriends = 0;
        student->visited = FALSE;
        student->visiting = FALSE;
        student->wait = FALSE;
        student->friends = NULL;
        s[i] = student;
    }
}
void addFriends(pStudent *s, Friendship *f, int n){
    int i, id, friend;
    for (i = 0; i < n; i++){
        id = f[i].id;
        friend = f[i].friend;
        if (s[id - 1]->nFriends == 0)
            s[id - 1]->friends = (pStudent*) malloc(sizeof(pStudent));
        else
            s[id - 1]->friends = (pStudent*) realloc(s[id - 1]->friends, sizeof(pStudent) * (s[id - 1]->nFriends + 1));
        s[id - 1]->friends[s[id - 1]->nFriends] = s[friend - 1];
        s[id - 1]->nFriends++;
    }
}

int visit(pStudent s){
    if(s->visited)
        return FALSE;
    else if(s->visiting)
        return TRUE;
    else {
        int d;
        s->visiting = TRUE;
        for (d = 0; d < s->nFriends; d++){
            s->wait = visit(s->friends[d]);
            if (s->grade < s->friends[d]->grade)
                s->grade = s->friends[d]->grade;
        }
        if(s->wait){
            s->visiting = FALSE;
            return TRUE;     /*todos os anterios ficam tambem em espera, terão de ser propagados novamente*/
        }
        s->visited = TRUE;
    }
    return s->visited;
}

void spreadFriends(pStudent *s, int n){
    int i;
    for (i = 0; i < n; i++)
        visit(s[i]);
}

void finalPrint(pStudent *s, int n){
    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", s[i]->grade);
}

int main(){
    char *input;
    char *numStudents, *numFriendships;
    int *grades, x = 0, *pos = &x;
    Friendship *friendships;
    pStudent *students;

    input = readInput(60);
    numStudents = processFirstLine(input, pos, ',');
    numFriendships = processFirstLine(input, pos, '\n');

    grades = (int*) malloc(sizeof(int) * (atoi(numStudents) + 1));
    processGrades(input, grades, pos, atoi(numStudents) + 1);
    friendships = (Friendship*) malloc(sizeof(Friendship) * atoi(numFriendships));
    processFriendships(input, friendships, pos, atoi(numFriendships));

    free(input);
    students = (pStudent*) malloc(sizeof(pStudent) * atoi(numStudents));
    initializeStudents(students, grades, atoi(numStudents));
    free(grades);
    addFriends(students, friendships, atoi(numFriendships));
    free(friendships);
    free(numFriendships);
    spreadFriends(students, atoi(numStudents));
    finalPrint(students, atoi(numStudents));

    for(x = 0; x < atoi(numStudents); x++){
        free(students[x]->friends);
        free(students[x]);
    }
    free(students);
    free(numStudents);

    return 0;
}