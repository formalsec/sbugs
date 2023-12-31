#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int studentNumber; 
    struct node* next;
} Node;

typedef struct arrayoflists{
	Node *head;
	Node *tail;
} ArrayOfLists;


int *grades;
ArrayOfLists *AdjLists;

int *d;
int *low;
int *arrayOfRoots;
static struct node *topNode;
int * onStack;
int currentIndex = 0;
int SccNumber = 0;

void init();
int is_empty();
void push(int value);
int pop();
int min(int u, int v);
void tarjanAlgorithm(int counter);
void createListsAndGrades(int vertices);
Node* createNode(int studentNumber);
void fillWithMarks(int vertices);
void fillFriendships(int edges);
void freeArrayOfLists(int vertices);
void changeToMaxGrade(int *array, int length);
void sharingSolucionsInScc(int vertices);


int main(){
    int vertices=0, edges=0;
    int counter;

    scanf("%d,%d", &vertices, &edges);

    if(vertices<2 || edges <1){
		exit(EXIT_FAILURE);
    }

    createListsAndGrades(vertices);

    fillWithMarks(vertices);

    fillFriendships(edges);

    init();
    
    for(counter=0; counter < vertices; counter++){
        if (d[counter] == -1){
            tarjanAlgorithm(counter);
        }
    }

    sharingSolucionsInScc(vertices);

    for(counter=0; counter < vertices; counter++)
        printf("%d\n",grades[counter]);

    freeArrayOfLists(vertices);

    return 0;
}

/*----------Stack----------*/

void init(){
    topNode = NULL;
}
    
int is_empty(){
    return topNode == NULL;
}
  
void push(int studentNumber){
    struct node *newNode;
    newNode = (struct node *) can_fail_malloc(sizeof(struct node));
    newNode->studentNumber = studentNumber;
    newNode->next = topNode;
    topNode = newNode;
}
  
int pop(){
    int studentNumber;
    struct node *previousNode;
    if (!is_empty()) {
        studentNumber = topNode->studentNumber;
        previousNode = topNode;
        topNode = topNode->next;
        free(previousNode);
        return studentNumber;
    }
    else{
        printf("Stack is empty.");
        return 0;
    }

}
  

/*-----------Tarjan----------*/

int min(int u, int v){
    if(v<u){
        return v;
    }
    return u;
}

int max(int u, int v){
    if(v>u){
        return v;
    }
    return u;
}

void tarjanAlgorithm(int counter){
    Node *aux = NULL;
    Node *head = NULL;
    int numberAux = 0;
    
    d[counter] = currentIndex;
    low[counter] = currentIndex;
    currentIndex++;

    push(AdjLists[counter].head->studentNumber);
    onStack[counter]=1;

    head = AdjLists[counter].head;

    for(aux = head->next; aux!=NULL; aux = aux->next){
        if(d[aux->studentNumber-1] == -1){
            tarjanAlgorithm(aux->studentNumber-1);
            low[head->studentNumber-1] = min(low[head->studentNumber-1] , low[aux->studentNumber-1]);
            grades[head->studentNumber-1] = max(grades[head->studentNumber-1] , grades[aux->studentNumber-1]);
        }
        else if(onStack[aux->studentNumber-1] != 0) {
            low[head->studentNumber-1] = min(low[head->studentNumber-1] , d[aux->studentNumber-1]);
            grades[head->studentNumber-1] = max(grades[head->studentNumber-1] , grades[aux->studentNumber-1]);
        }
        else{
            grades[head->studentNumber-1] = max(grades[head->studentNumber-1] , grades[aux->studentNumber-1]);
        }
    }
    if (low[counter] == d[counter] ){
        do{
            numberAux = pop();
            onStack[numberAux-1] = 0;
            arrayOfRoots[SccNumber++] = numberAux;

        }while(numberAux != counter+1 );
        arrayOfRoots[SccNumber++] = -1;
    }  
}


void changeToMaxGrade(int *array, int length){
    int i;
    int max = grades[array[length-1]-1];

    for(i=0;i<length;i++){
        grades[array[i]-1] = max;
        array[i]=0;
    }
}

void sharingSolucionsInScc(int vertices){
    int i=0,j=0,iScc=0;
    int arrayAux[vertices];
    for(i=0;i<2*vertices;i++){
        for(j=i;arrayOfRoots[j]!=-1 && j<2*vertices;j++){
            arrayAux[iScc] = arrayOfRoots[j];
            iScc++;
        }
        if(iScc != 0){
            i=j;
            changeToMaxGrade(arrayAux,iScc);
            iScc=0;
        }
    }
}



/*----------Create and Initialize used structures----------*/

void createListsAndGrades(int vertices){
    int counter=0;

    AdjLists = (ArrayOfLists *)can_fail_malloc(sizeof(ArrayOfLists)*vertices);
    grades = (int *)can_fail_malloc(sizeof(int)*vertices);
    d = (int *)can_fail_malloc(sizeof(int)*vertices);
    low = (int *)can_fail_malloc(sizeof(int)*vertices);
    arrayOfRoots = (int *)can_fail_malloc(sizeof(int)*2*vertices);
    onStack = (int *)can_fail_malloc(sizeof(int)*vertices);

    for (counter = 0; counter < vertices; counter++) {
        AdjLists[counter].head = createNode(counter+1);
        AdjLists[counter].tail = AdjLists[counter].head;
        d[counter] = -1;
        low[counter] = 0;
        onStack[0] = 0;
        grades[counter] = 0;
    }
    for (counter = 0; counter < 2*vertices; counter++)
        arrayOfRoots[counter] = -1;
}

Node *createNode(int studentNumber){
    Node *newNode;
    newNode = (Node *) can_fail_malloc(sizeof(Node));
    newNode->studentNumber = studentNumber;
    newNode->next = NULL;
    
    return newNode;
}

/*----------Input Processing Function----------*/

void fillWithMarks(int vertices){
    int mark=0;
    int counter=0;

    for (counter = 0; counter < vertices; counter++) {
        scanf("%d", &mark);
        grades[counter] = mark;
    }
}

void fillFriendships(int edges){
    int oFriend=0, dFriend=0;
    int counter=0;

    for(counter=0;counter<edges;counter++){
        scanf("%d %d", &oFriend,&dFriend);
        AdjLists[oFriend-1].tail->next = createNode(dFriend);
        AdjLists[oFriend-1].tail = AdjLists[oFriend-1].tail->next;
    }
}

void freeArrayOfLists(int vertices){
    int counter;
    Node *aux;
    Node *auxBefore;
    for (counter = 0; counter < vertices; counter++) {
        for(aux = AdjLists[counter].head; aux != NULL;){
            auxBefore = aux;
            aux = aux->next;
            free(auxBefore);
        }
        AdjLists[counter].head = NULL;
        AdjLists[counter].tail = NULL;
    }
    free(AdjLists);
    free(grades);
    free(d);
    free(low);
    free(onStack);
    free(arrayOfRoots);
}








 