#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_INPUT 100
#define SEPARATOR 0
#define UNEXPLORED -1
#define WHITE 0
#define GREY 1
#define BLACK 2
#define NULL_PARENT -1

typedef struct lstNode{
    int numAluno;
    struct lstNode *nextNode;
} LstNode;

int indexScc = 0, *Sccs, numComponents = 0;

int min(int num1, int num2){
    return (num1 > num2 ) ? num2 : num1;
}

int max(int num1, int num2){
    return (num1 > num2 ) ? num1 : num2;
}

int isStackEmpty(int *top){
    if((*top) == -1){
        return 1;
    }
    else{
        return 0;
    }
}

int isStackFull(int *top, int size){
    if((*top) == (size - 1)){
        return 1;
    }
    else{
        return 0;
    }
}

int popStack(int *top, int *stack){
    int data;

    if(!isStackEmpty(top)){
        data = stack[(*top)];
        (*top) -= 1;
        return data;
    }
    return 0;
}

void pushStack(int data, int *top, int *stack, int size){

    if(!isStackFull(top, size)){
        (*top) += 1;
        stack[(*top)] = data;
    }
}

int isInStack(int data, int *top, int *stack){
    int i;
    
    if(!isStackEmpty(top)){
        for (i = 0; i <= (*top); i++)
        {
            if (stack[i] == data){
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

LstNode* newNode(int numAluno)
{
    LstNode* p = can_fail_malloc(sizeof(LstNode));
    if (NULL != p) {
        p->numAluno = numAluno;
        p->nextNode  = NULL;
    }
    return p;
}

void insertNode(LstNode** lstAdjacencias, int numAluno, LstNode *node){
    LstNode *auxNode = NULL;
    if (lstAdjacencias[numAluno] == NULL){
        lstAdjacencias[numAluno] = node;
        return;
    }
    else{
        for (auxNode = lstAdjacencias[numAluno]; auxNode->nextNode != NULL; auxNode = auxNode->nextNode);
        auxNode->nextNode = node;
        return;
    }
}

void freeList(LstNode *head){
    LstNode *auxNode = NULL, *nextNodeAux = NULL;
    if (head == NULL){
        return;
    }
    auxNode = head;
    nextNodeAux = auxNode->nextNode;
    while(nextNodeAux != NULL){
        free(auxNode);
        auxNode = nextNodeAux;
        nextNodeAux = nextNodeAux->nextNode;
    }
    free(auxNode);
}

void freeLstAdjacencias(LstNode **lstAdjacencias, int size){
    int i;
    for (i = 0; i < size; i++){
        freeList(lstAdjacencias[i]);
    }
    free(lstAdjacencias);
}

void DFSUpdate(int *lstEstimativas, int aluno, int visitante, int numAlunos){
    if (lstEstimativas[visitante] < lstEstimativas[aluno]){
        lstEstimativas[visitante] = lstEstimativas[aluno];
    }
}

void DFSVisit(LstNode **lstAdjacencias, int *lstEstimativas, int *color, int *pai, int max, int aluno, int numAlunos){
    LstNode *auxNode = NULL;
    int maxAux;

    maxAux = lstEstimativas[aluno];

    color[aluno] = GREY;

    for (auxNode = lstAdjacencias[aluno]; auxNode != NULL; auxNode = auxNode->nextNode){
        if (color[(auxNode->numAluno) - 1] == WHITE){
            pai[(auxNode->numAluno) - 1] = aluno;
            DFSVisit(lstAdjacencias, lstEstimativas, color, pai, maxAux, (auxNode->numAluno) - 1, numAlunos);
            maxAux = lstEstimativas[aluno];
        }
        else if (color[(auxNode->numAluno) - 1] == BLACK){
            DFSUpdate(lstEstimativas, (auxNode->numAluno) - 1, aluno, numAlunos);
            maxAux = lstEstimativas[aluno];
        }
    }

    if ((maxAux > max) && (pai[aluno] != NULL_PARENT)){
        lstEstimativas[pai[aluno]] = maxAux;
    }
    color[aluno] = BLACK;
}

void DFS(LstNode **lstAdjacencias, int *lstEstimativas, int numAlunos){
    int i, *color, *pai, maxVal = 0;

    color = (int*) can_fail_malloc(sizeof(int)*numAlunos);
    pai = (int*) can_fail_malloc(sizeof(int)*numAlunos);

    for (i = 0; i < numAlunos; i++){
        color[i] = WHITE;
        pai[i] = NULL_PARENT;

    }
    for (i = 0; i < numAlunos; i++){
        if (color[i] == WHITE){
            DFSVisit(lstAdjacencias, lstEstimativas, color, pai, maxVal, i, numAlunos);
        }
    }

    free(color);
    free(pai);
}

void findMaxInComponents(int *lstEstimativas, int numComponents, int *maxComponents){
    int i, component = 0;

    for (i = 0; i < indexScc; i++){
        if (Sccs[i] == 0){
            component++;
        }
        else if (lstEstimativas[Sccs[i] - 1] > maxComponents[component]){
            maxComponents[component] = lstEstimativas[Sccs[i] - 1];
        }
    }
}

void associateComponentVertix(LstNode **ComponentsVertix){
    int i, component = 0;
    LstNode *node;

    for (i = 0; i < indexScc; i++){
        if (Sccs[i] == 0){
            component++;
            continue;
        }
        node = newNode(Sccs[i]);
        if (NULL != node) {
            insertNode(ComponentsVertix, component, node);
        }
    }
}

void associateVertixComponent(int *vertixComponents){
    int i, component = 1;

    for (i = 0; i < indexScc; i++){
        if (Sccs[i] == 0){
            component++;
            continue;
        }
        vertixComponents[Sccs[i] - 1] = component;
    }
}

void tarjanVisit(int aluno, int numAlunos, int *d, int *low, int *stack, int *top, int visited, LstNode **lstAdjacencias){
    LstNode *auxNode = NULL;
    int v;

    d[aluno - 1] = low[aluno - 1] = visited;
    visited++;
    pushStack(aluno, top, stack, numAlunos);

    for (auxNode = lstAdjacencias[aluno - 1]; auxNode != NULL; auxNode = auxNode->nextNode){
        if ((d[(auxNode->numAluno) - 1] == UNEXPLORED) || (isInStack(auxNode->numAluno, top, stack))){
            if(d[(auxNode->numAluno) - 1] == UNEXPLORED){
                tarjanVisit(auxNode->numAluno, numAlunos, d, low, stack, top, visited, lstAdjacencias);
            }
            low[aluno - 1] = min(low[aluno - 1], low[(auxNode->numAluno) - 1]);
        }
    }
    
    if (d[aluno - 1] == low[aluno - 1]){
        v = popStack(top, stack);
        Sccs[indexScc++] = v;
        while (aluno != v){
            v = popStack(top, stack);
            Sccs[indexScc++] = v;
        }
        Sccs[indexScc++] = SEPARATOR;
        numComponents++;
    }
}

void executeTarjan(LstNode **lstAdjacencias, int numAlunos){
    int *d, *low, *stack, *topP, top = -1, visited = 0, i;

    d = (int*) can_fail_malloc(sizeof(int)*numAlunos);
    low = (int*) can_fail_malloc(sizeof(int)*numAlunos);
    stack = (int*) can_fail_malloc(sizeof(int)*numAlunos);

    topP = &top;

    for (i = 0; i < numAlunos; i++){
        d[i] = UNEXPLORED;
    }
    for (i = 0; i < numAlunos; i++){
        if (d[i] == UNEXPLORED){
            tarjanVisit(i + 1, numAlunos, d, low, stack, topP, visited, lstAdjacencias);
        }
    }

    free(d);
    free(low);
    free(stack);

}

void associateComponents(LstNode **lstAdjacencias, LstNode **ComponentsVertix, int *vertixComponents, int numComponents, int numAlunos, LstNode **lstAdjacenciasCmp){
    int k, i, *components;
    LstNode *auxNode = NULL, *node = NULL, *auxNode2 = NULL;

    components = (int*) can_fail_malloc(sizeof(int)*numComponents);

    for(i = 0; i < numComponents; i++){
        components[i] = 0;
    }

    for (k = 0; k < numComponents; k++){
        for (auxNode = ComponentsVertix[k]; auxNode != NULL; auxNode = auxNode->nextNode){
            for (auxNode2 = lstAdjacencias[(auxNode->numAluno) - 1]; auxNode2 != NULL; auxNode2 = auxNode2->nextNode){
                if((components[vertixComponents[(auxNode2->numAluno) - 1] - 1] != 1) && ((vertixComponents[(auxNode2->numAluno) - 1] - 1) != k)){
                    components[vertixComponents[(auxNode2->numAluno) - 1] - 1] = 1;
                    node = newNode(vertixComponents[(auxNode2->numAluno) - 1]);
                    if (NULL != node) {
                        insertNode(lstAdjacenciasCmp, k, node);
                    }
                }
            }
        }
       
        for (auxNode = ComponentsVertix[k]; auxNode != NULL; auxNode = auxNode->nextNode){
            for (auxNode2 = lstAdjacencias[(auxNode->numAluno) - 1]; auxNode2 != NULL; auxNode2 = auxNode2->nextNode){
                components[vertixComponents[(auxNode2->numAluno) - 1] - 1] = 0;
            }
        }
    }

    free(components);
}

int main(){
    int i = 0, input[2], numAlunos, numLigacoes, *lstEstimativas, *maxComponents, *vertixComponents;
    char stringInput[MAX_INPUT], *pt;
    LstNode **lstAdjacencias, **lstAdjacenciasCmp, **ComponentsVertix;

    scanf("%s", stringInput);

    pt = strtok (stringInput,",");
    while (pt != NULL) {
        int a = atoi(pt);
        input[i++] = a;
        pt = strtok (NULL, ",");
    }
    numAlunos = input[0];
    numLigacoes = input[1];

    if((numAlunos < 2) && (numLigacoes < 1)){
        return 0;
    }
    lstEstimativas = (int *) can_fail_malloc(numAlunos*sizeof(int));

    lstAdjacencias = (LstNode **) can_fail_malloc(sizeof(LstNode *)*numAlunos);

    for (i = 0; i < numAlunos; i++)
    {
        lstAdjacencias[i] = NULL;
    }

    for(i = 0; i < numAlunos; i++){
        int est;
        if(scanf("%d", &est) != 1) {
            return -1;
        }
        lstEstimativas[i] = est;
    }

    Sccs = (int *) can_fail_malloc(sizeof(int)*(numAlunos*2));

    for(i = 0; i < numLigacoes; i++){
        int al1, al2;
        LstNode *node;

        if(scanf("%d %d", &al1, &al2) != 2 || al1 <= 0 || al1 > numAlunos || al2 <=0 || al2 > numAlunos) {
            return -1;
        }

        node = newNode(al2);
        if (NULL != node) {
            insertNode(lstAdjacencias, al1 - 1, node);
        }
    }

    executeTarjan(lstAdjacencias, numAlunos);

    lstAdjacenciasCmp = (LstNode **) can_fail_malloc(sizeof(LstNode *)*numComponents);
    ComponentsVertix = (LstNode **) can_fail_malloc(sizeof(LstNode *)*numComponents);

    maxComponents = (int *) can_fail_malloc(sizeof(int)*numComponents);
    vertixComponents = (int *) can_fail_malloc(sizeof(int)*numAlunos);

    for (i = 0; i < numComponents; i++){
        maxComponents[i] = 0;
        ComponentsVertix[i] = NULL;
        lstAdjacenciasCmp[i] = NULL;
    }

    findMaxInComponents(lstEstimativas, numComponents, maxComponents);

    associateComponentVertix(ComponentsVertix);

    associateVertixComponent(vertixComponents);
      
    associateComponents(lstAdjacencias, ComponentsVertix, vertixComponents, numComponents, numAlunos, lstAdjacenciasCmp);
 
    DFS(lstAdjacenciasCmp, maxComponents, numComponents);

    for (i = 0; i < numAlunos; i++){
        lstEstimativas[i] = maxComponents[vertixComponents[i] - 1];
    }

    for (i = 0; i < numAlunos; i++){
        printf("%d\n", lstEstimativas[i]);
    }

    free(maxComponents);
    free(vertixComponents);
    free(Sccs);
    free(lstEstimativas);
    freeLstAdjacencias(lstAdjacencias, numAlunos);
    freeLstAdjacencias(lstAdjacenciasCmp, numComponents);
    freeLstAdjacencias(ComponentsVertix, numComponents);

    return 0;
}