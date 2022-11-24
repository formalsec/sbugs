#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*-------------------Projeto ASA-------------------*/
/*----              Afonso Jorge;	           ----*/
/*----                 Tp93680;    		       ----*/
/*----                    &     	           ----*/
/*----               Tomas Paiva;              ----*/
/*----                 Tp96961;    		       ----*/
/*-------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

typedef struct node{
    int currentGrade;
    struct node** connections;
    int numberCon;
    int done;
} Node;

struct node* createNode(int ppls, int number)
{
    struct node* newNode = can_fail_malloc(sizeof(struct node));
    newNode->numberCon = 0;
    newNode->done = 0;
    newNode->currentGrade = number;
    newNode->connections = NULL;
    return newNode;
}

int funcao(Node* aaa){
    int temp, i;
    aaa->done = 1;
    for(i = 0; i<aaa->numberCon; i++){
        if(aaa->connections[i]->done == 0){
            temp = funcao(aaa->connections[i]);
        }else{
            temp = aaa->connections[i]->currentGrade;
        }
        if(temp > aaa->currentGrade){
            aaa->currentGrade = temp;
        }
    }   
    return aaa->currentGrade;
}

int main(){
    char str1[12];
    int ppl, con, temp1, temp2, i;
    scanf("%s", str1);
    char s[2] = ",";

    char* token;
    int fors;

    token = strtok(str1, s);
    ppl = atoi(token);
    token = strtok(NULL, s);
    con = atoi(token);

    struct node** nodeList;
    nodeList = can_fail_malloc(ppl*sizeof(Node*));

    for(fors = 0; fors<ppl; fors++){
        scanf("%s", str1);
        nodeList[fors] = createNode(ppl, atoi(str1));
    }

    
    for(fors = 0; fors<con; fors++){
        scanf("%d %d", &temp1, &temp2);
        nodeList[temp1-1]->connections = can_fail_realloc(nodeList[temp1-1]->connections, ((nodeList[temp1-1]->numberCon)+1)*sizeof(Node*));
        nodeList[temp1-1]->connections[nodeList[temp1-1]->numberCon] = nodeList[temp2-1]; 
        nodeList[temp1-1]->numberCon++;
    }

    for(i = 0; i<ppl; i++){
        if(nodeList[i]->done == 0){
            funcao(nodeList[i]);
        }
    }

    for(i = 0; i<ppl; i++){
        printf("%d\n", nodeList[i]->currentGrade);
    }
    
    return 0;
}