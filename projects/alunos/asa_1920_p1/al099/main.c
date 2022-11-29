#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 100

typedef struct student {
    int grade;
    int id;
} student;

char* description;
int studentNum;
int relationNum;
int sum;
int counter = 0;
student ** relList[2];
student * studList;


void processFirstLine(){
    int i;
    for (i=0; i<2;i++){
        relList[i] = (student **) can_fail_malloc(sizeof(student) * relationNum);
    }
    studList = (student *)can_fail_malloc(sizeof(student) * studentNum);
}

void run(){
    int i;
    int nostop = 1;
    while (nostop == 1){
        nostop = 0;
        for(i = 0; i < relationNum; i++){
            if(relList[0][i]->grade < relList[1][i]->grade){
                relList[0][i]->grade = relList[1][i]->grade;
                nostop = 1;
            }
        }
    }
    
    for(i = 0; i < studentNum; i++){
        printf("%d\n", studList[i].grade);
    }
}


int main(){
    int i = 1;
    int err;
    int suf;
    err = scanf("%d,%d", &studentNum, &relationNum);
    if(!err){
        exit(1);
    }
    
    sum = studentNum + relationNum;
    suf = studentNum + 1;
    processFirstLine();
    while (i <= sum) {
        if(i <= studentNum){
            int grade;
            if(!scanf("%d", &grade)){
                exit(1);
            }
            studList[i - 1].id = i;
            studList[i - 1].grade = grade;
            
        } else{
            int stud, fr;
            if(!scanf("%d %d", &stud, &fr)){
                exit(1);
            }
            relList[0][i - suf] = &studList[stud - 1];
            relList[1][i - suf] = &studList[fr - 1];
        }   
        i++;
    }
    
    run();
    exit(EXIT_SUCCESS);
}