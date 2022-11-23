#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_LINE_SIZE 128
#define WHITE 0
#define GREY 1
#define BLACK 2


struct friends
{
    int idNumber;
    struct friends *next;
};
struct student
{
    int mark;
    int discoveryTime;
    int low;
    int SCC;
    struct friends *friend;
};

struct Stack{
    int *idNumber;
    int top;
};
struct SCC{
    int color;
    int internalMark;
    int FinalMark;
    struct friends *next;/*represents a node for another SCC*/
    struct friends *friend;
};

int numberStudents,numberFriendships,visited = 0, numSCC = 0;
struct Stack *stack;
struct student **students;
struct SCC **SCC;

void err_dump(char *msg){
    fprintf(stderr,msg);
    exit(EXIT_FAILURE);
}

void processInput(){
    char buffer[MAX_LINE_SIZE], *token;
    int i;
    
    if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
        if ((token = strtok(buffer, ",")) != NULL){
            numberStudents = atoi(token);
            
            if (numberStudents < 0) err_dump("Failed to process Number of Students\n");
            token = strtok(NULL, ",");
            numberFriendships = atoi(token);
            
            if (numberFriendships < 0) err_dump("Failed to process Number of Friendships\n");
        }
    }
    students = can_fail_malloc(sizeof(struct student*) * numberStudents);
    if (!students) err_dump("Fail to allocate memory!\n");

    SCC = can_fail_malloc (sizeof(struct SCC*) * numberStudents);
    if (!SCC) err_dump("Fail to allocate memory!\n");

    for (i=0; i<numberStudents; i++){

        students[i]=can_fail_malloc(sizeof(struct student));
        if (!students[i]) err_dump("Fail to allocate memory!\n");

        students[i]->friend=NULL;
        students[i]->discoveryTime=-1;
        students[i]->low=-1;

        if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
        	students[i]->mark = atoi(buffer);
            if (students[i]->mark < 0) err_dump("Failed to process student mark\n");
            
        }
        SCC[i] = can_fail_malloc(sizeof(struct SCC));
        if (!SCC[i]) err_dump("Fail to allocate memory!\n");
        SCC[i]->friend = NULL;

        
    }
    for (i=0; i<numberFriendships; i++){
        int idNumber,friendNumber;
        struct friends *friend;
        if ((fgets(buffer, sizeof(buffer), stdin)) != NULL){
            if ((token = strtok(buffer, " ")) != NULL){
                idNumber = atoi(token);
                if (idNumber < 1) err_dump("Failed to read Student Number\n");
                token=strtok(NULL," ");
                friendNumber = atoi(token);
                if (friendNumber < 1) err_dump("Failed to read Friend Number\n");
                idNumber--;
                friendNumber--;
                friend = can_fail_malloc (sizeof(struct friends));
                if (!friend) err_dump("Failed to allocate memory\n");
                    friend->idNumber=friendNumber;
                    friend->next=students[idNumber]->friend;
                    students[idNumber]->friend=friend;
            }
        }
    }
} 

void initStack(){
    stack=can_fail_malloc(sizeof(struct Stack));
    stack->idNumber=can_fail_malloc(sizeof(int)*numberStudents);
    stack->top=-1; 
}
void freeStack(){
    free(stack->idNumber);
    free(stack);
}
void push(int idNumber){
    stack->idNumber[++stack->top]=idNumber;
}
int pop(){
    int value;
    if (stack->top==-1) return -1;
    value=stack->idNumber[stack->top];
    stack->top--;
    return value;
}
int hasElement(int idNumber){
    int i;
    for (i=0;i<=stack->top;i++)
        if (idNumber == stack->idNumber[i])
            return TRUE;
    return FALSE;
}

int min(int n1,int n2){
    if (n1 < n2) return n1;
    return n2;
}

void visit(struct student *s,int idNumber){
    struct friends *f=s->friend;
    int v=-2;
    s->discoveryTime=s->low=visited;
    
    visited++;
    if (idNumber >=0)
        push(idNumber);

    for (;f && f->idNumber >=0;f=f->next){
        if (students[f->idNumber]->discoveryTime == -1){
            visit(students[f->idNumber],f->idNumber);
            students[idNumber]->low = min(students[idNumber]->low,students[f->idNumber]->low);
        }
        else if(hasElement(f->idNumber)){
            students[idNumber]->low = min(students[idNumber]->low,students[f->idNumber]->discoveryTime);
        }        
    }
    if (students[idNumber]->discoveryTime == students[idNumber]->low){
        
        while (idNumber!=v){
            v = pop();
            f = can_fail_malloc (sizeof(struct friends));
            f->idNumber=v;
            f->next=SCC[numSCC]->friend;
            SCC[numSCC]->friend=f;
            students[v]->SCC=numSCC;
        }
        numSCC++;
    }
}
int max(int n1, int n2){
    if (n1>n2) return n1;
    return n2;
}

int fastVisit(struct SCC *component){
    struct friends *f=component->next;
    if (component->color==BLACK) return component->FinalMark;
    if (!f){
        component->color=BLACK;
        component->FinalMark=component->internalMark;
        return component->FinalMark;
    }
    if (component->color == WHITE){
        component->color = GREY;
        for(;f;f=f->next){
            component->FinalMark = max(component->FinalMark,component->internalMark);   
            component->FinalMark = max(component->FinalMark,fastVisit(SCC[f->idNumber]));
        }
    }
    component->color=BLACK;
    return component->FinalMark;

}

void inspectFriendships(){
    struct friends *f,*aux,*temp;
    int i;
    for (i=0;i<numberStudents;i++)
        if (students[i]->discoveryTime == -1)/*equals infinite*/
            visit(students[i],i);
    for (i=0;i<numSCC;i++){ /*SCC have internalMark*/
        SCC[i]->internalMark=-1;
        SCC[i]->FinalMark=-1;
        SCC[i]->color=WHITE;
        SCC[i]->next=NULL;
        f=SCC[i]->friend;
        for (;f && f->idNumber >= 0;f=f->next){
            SCC[i]->internalMark = max(SCC[i]->internalMark,students[f->idNumber]->mark);/*save internalMark*/
        
            temp=students[f->idNumber]->friend;
            for(;temp && temp->idNumber!=-1 ;temp=temp->next)
                if (students[temp->idNumber]->SCC != i){
                    aux = can_fail_malloc (sizeof(struct friends));
                    aux->idNumber = students[temp->idNumber]->SCC;
                    aux->next=SCC[i]->next;
                    SCC[i]->next=aux;   
                }
        }
    }
    for (i=0;i<numSCC;i++){
        if (SCC[i]->color==WHITE)
            SCC[i]->FinalMark=fastVisit(SCC[i]);
    }
}

void freeStuff(){
    int i;
    struct friends *aux;
    for (i=0;i<numberStudents;i++){
        if (students[i]->friend){ 
            aux = students[i]->friend->next;
            for(;aux;students[i]->friend=aux,aux=aux->next)
                free(students[i]->friend);
            free(students[i]->friend);            
            }
        free(students[i]);
        
        if (SCC[i]->friend) {
            aux=SCC[i]->friend->next;
            for (;aux;SCC[i]->friend=aux,aux=aux->next)
                free(SCC[i]->friend);
            free(SCC[i]->friend);
        }
    
        if (SCC[i]->next) {
            aux=SCC[i]->next->next;
            for (;aux;SCC[i]->next=aux,aux=aux->next)
                free(SCC[i]->next);
            free(SCC[i]->next);
        }
        free(SCC[i]);
    }
    free(SCC);
    free(students);
    freeStack();
}

void printResult(){
    int i;
    for (i=0;i<numberStudents;i++)
        fprintf(stdout,"%d\n",SCC[students[i]->SCC]->FinalMark);
}

int main() {
 
    processInput();  
    initStack();
    inspectFriendships();
    printResult();
    freeStuff();
    exit(EXIT_SUCCESS);
}
