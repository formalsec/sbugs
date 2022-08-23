#include <stdio.h>
#include <stdlib.h>

int students = 0;
int friendships = 0;
int **adjmatrix;
int highestgrade = 0, currentgrade = -1;
int *visited;

void InitMatrix(){

    int i = 0, j = 0;

    adjmatrix = (int **) malloc(students * sizeof(int *));

    if(adjmatrix == NULL)
        exit(0);

    for(i = 0; i < students; i++){
        adjmatrix[i] = (int *) malloc(students * sizeof(int));

        if(adjmatrix[i] == NULL)
            exit(0);
    }

    for(i = 0; i < students; i++){
        for(j = 0; j < students; j++){
            adjmatrix[i][j] = -1;
        }
    }

    visited = (int *) malloc(students * sizeof(int));

    if(visited == NULL)
        exit(0);

    for(i = 0; i < students; i++)
        visited[i] = 0;
}

void ProcessInput(){

    int i = 0;
    int numTokens = 0;
    int grade = 0;
    int friend_1 = 0, friend_2 = 0;

    numTokens = scanf("%d,%d", &students, &friendships);

    if(numTokens != 2 || students < 2 || friendships < 1)
        exit(0);

    InitMatrix();
    
    for(i = 0; i < students; i++){

        numTokens = scanf("%d", &grade); 

        if(numTokens != 1)
            exit(0);

        if(highestgrade < grade)
            highestgrade = grade;
        
        adjmatrix[i][i] = grade;
    }

    for(i = 0; i < friendships; i++){

        numTokens = scanf("%d %d", &friend_1, &friend_2);

        if(numTokens != 2)
            exit(0);

        adjmatrix[friend_1 - 1][friend_2 - 1] = adjmatrix[friend_2 - 1][friend_2 - 1]; 
    }
}

void DFS(int v){

    int i = 0;

    visited[v] = 1;

    for(i = 0; i < students; i++){

        if(adjmatrix[v][i] != -1 && !visited[i] && i != v){

            if(currentgrade < adjmatrix[v][i])
                currentgrade = adjmatrix[v][i];

            if(currentgrade == highestgrade)
                return;

             DFS(i);   
        }
    }
}

void ResetDFS(){

    int i = 0;

    for(i = 0; i < students; i ++)
        visited[i] = 0;

    currentgrade = -1;
}

void GetNewGrades(){

    int i = 0;

    for(i = 0; i < students; i++){
        currentgrade = adjmatrix[i][i];
        DFS(i);
        printf("%d\n", currentgrade);
        ResetDFS();
    } 

    free(visited);

    for(i = 0; i < students; i++){
        free(adjmatrix[i]);
    }
    
    free(adjmatrix);
}

int main(int argc, char* argv[]){

    ProcessInput();

    GetNewGrades();
    
    exit(0);
}