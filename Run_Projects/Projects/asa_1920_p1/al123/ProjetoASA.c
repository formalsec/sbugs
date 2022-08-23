#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Id {
    long int id;
    struct Id *pnext;
};

struct Aluno {
    long int id;
    struct Id *node;
    int nota;
    bool visited;
    struct Aluno *pnext;
};


struct Aluno *pfirst = NULL;
int top = -1;

void push(int item, int stack[]) {
    stack[++top] = item;
}

int pop(int stack[]) {
    return stack[top--];
}

int peek(int stack[]) {
    return stack[top];
}

bool isStackEmpty() {
    return top == -1;
}

struct Aluno *getAluno(long int id, struct Aluno *lstAlunos[]) {
    return lstAlunos[id];
}

void addAluno(long int number, int mark, struct Aluno *lstAlunos[]) {
    struct Aluno *aluno = (struct Aluno *) calloc(1, sizeof(struct Aluno));
    aluno->id = number;
    aluno->nota = mark;
    aluno->visited = false;
    lstAlunos[number] = aluno;
}

void addEdge(long int start, long int end, struct Aluno *lstAlunos[]) {
    struct Aluno *aluno = getAluno(start, lstAlunos);
    pfirst = aluno;
    if (pfirst->node == NULL) {
        struct Id *id = (struct Id *) calloc(1, sizeof(struct Id));
        pfirst->node = id;
        pfirst->node->id = end;
    } else {
        struct Id *paux = pfirst->node;
        while (paux->pnext != NULL) {
            paux = paux->pnext;
        }
        struct Id *id = (struct Id *) calloc(1, sizeof(struct Id));
        paux->pnext = id;
        paux->pnext->id = end;
    }
}

int getAdjUnvisitedAluno(long int AlunoIndex, struct Aluno *lstAlunos[]) {
    struct Aluno *aluno = getAluno(AlunoIndex,lstAlunos);
    struct Id *paux = NULL;
    paux = aluno->node;
    while (paux != NULL) {
        struct Aluno *auxAluno = getAluno(paux->id,lstAlunos);
        if (auxAluno->visited == false) {
            return auxAluno->id;
        } else {
            if (paux->pnext != NULL)
                paux = paux->pnext;
            else
                return -1;
        }
    }
    return -1;
}

void DFS(long int start, long int AlunosCount, struct Aluno *lstAlunos[], int stack[]) {
    long int m;
    int mark;

    lstAlunos[start]->visited = true;
    mark = lstAlunos[start]->nota;
    push(start, stack);
    while (!isStackEmpty()) {
        int unvisitedAluno = getAdjUnvisitedAluno(peek(stack),lstAlunos);

        if (unvisitedAluno == -1) {
            pop(stack);
        } else {
            if (lstAlunos[unvisitedAluno]->nota >= mark) {
                mark = lstAlunos[unvisitedAluno]->nota;
            }
            lstAlunos[unvisitedAluno]->visited = true;
            push(unvisitedAluno, stack);
        }
    }
    for (m = 0; m < AlunosCount; m++) {
        lstAlunos[m]->visited = false;
    }
    printf("%d\n", mark);
}

int main() {

    long int k, z, c, a;
    long int EdgeCount;
    long int start, end, MAX;
    int mark;
    
    scanf("%lu,%lu", &MAX, &EdgeCount);

    struct Aluno *lstAlunos[MAX];
    int stack[MAX];
    if (MAX < 2 || EdgeCount < 1) {
        return 0;
    }

    for (k = 0; k < MAX; k++) {
        scanf("%d", &mark);
        addAluno(k, mark, lstAlunos);
    }

    for (z = 0; z < EdgeCount; z++) {
        scanf("%lu %lu", &start, &end);
        addEdge(start - 1, end - 1, lstAlunos);
    }

    for (c = 0; c < MAX; c++) {
        DFS(c, MAX, lstAlunos, stack);
    }
    for (a = 0; a < MAX; a++) {
        free(lstAlunos[a]);
    }
    return 0;
}