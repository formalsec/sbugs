#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct graphNode{
    int d_DFS; /*tempo de descoberta*/
    int d_SCC; /*tempo de descoberta*/
    int src; /*predecessor do vertice */
    int grade; /*nota do vertice/aluno*/
    int *adj; /*lista de vertices adjacentes*/
    int num_adj; 
    int on_stack; /*"boolean" vertice na stack ou nao*/
    int low; /*low value para descobrir os SCCs*/
    int SCC; /*SCC a que pertence*/
} graphNode;

int *gradesSCCs; /*lista das notas de cada  SCC*/
int num_SCCS = 0;  /*numero de SCCs no grafo*/
int num_students = 0; /*numero de vertices*/
int time = 0; /*tempo de d/f*/
int *stack; 
int stack_size = 0;
graphNode *nodes; /*lista de estrutura dos vertices*/


/*adiciona elemento no topo da pilha*/
void push(int v){
    stack[stack_size++] = v;
}

/*retira elemento do topo da pilha*/
int pop(){
    int v = stack[stack_size - 1];
    stack_size--;
    return v;
}

/*devolve o minimo entre a e b*/
int min(int a, int b) {
    return a < b ? a : b;
}

/*devolve o maximo entre a e b*/
int max(int a, int b) {
    return a > b ? a : b;
}

/*Liberta a memoria alocada*/
void freeMemory(){
    int i = 0;
    for(i = 0; i < num_students;i++){
        free(nodes[i].adj);
    }
    free(stack);
    free(nodes);
    free(gradesSCCs);
}

/*Imprime as notas de cada aluno*/
void printGrades(){
    int v = 0;
    for(v = 0; v < num_students;v++){
        printf("%d\n", gradesSCCs[nodes[v].SCC]);
    }
}

/*Processa o input dado*/
void processInput(){
    int num_friendships = 0, 
    grade = 0,
    i = 0, j = 0, v = 0;

    scanf("%d,%d\n", &num_students, &num_friendships);

    stack = (int*)malloc(sizeof(int)*num_students);

    nodes = (graphNode*)malloc(sizeof(graphNode) * num_students);

    /*Associa a nota do teste de cada estudante e inicializa os vertices*/
    for(v = 0; v < num_students; v++){
        scanf("%d\n", &grade);
        nodes[v].adj = 0;
        nodes[v].num_adj = 0;
        nodes[v].grade = grade;
        nodes[v].src = -1;
        nodes[v].d_DFS = 0;
        nodes[v].d_SCC = 0;
        nodes[v].on_stack = FALSE;
        nodes[v].low = -1;
        nodes[v].SCC = -1;
    }

    /*Associa as relacoes entre estudantes (adiciona 'a lista de vertices adjacentes)*/
    for(v = 0;v < num_friendships;v++){
        scanf("%d %d\n", &i, &j);
        nodes[i-1].num_adj++;   
        nodes[i-1].adj = (int*)realloc(nodes[i-1].adj, sizeof(int) * nodes[i-1].num_adj);
        nodes[i-1].adj[nodes[i-1].num_adj-1] = j-1;
        
    }
}

/*Visita cada vertice para descobrir a que SCC pertence(Algortimo de Tarjan) */
void SCCS_VISIT(int v){
    int i = 0, adj;
    time++;
    nodes[v].d_SCC = time;
    nodes[v].low = time;
    nodes[v].on_stack = TRUE;
    push(v);
    for(i = 0; i < nodes[v].num_adj; i++){
        adj = nodes[v].adj[i];
        if(nodes[adj].d_SCC == 0)
            SCCS_VISIT(adj);

        if(nodes[adj].on_stack)
            nodes[v].low = min(nodes[v].low, nodes[adj].low);
    
    }
    if(nodes[v].low == nodes[v].d_SCC){
        gradesSCCs = (int*)realloc(gradesSCCs, sizeof(int) * (num_SCCS+1));
        gradesSCCs[num_SCCS] = 0;
        while(TRUE){
            i = pop();
            gradesSCCs[num_SCCS] = max(gradesSCCs[num_SCCS], nodes[i].grade);
            nodes[i].on_stack = FALSE;
            nodes[i].SCC = num_SCCS;
            if(i == v) 
                break;
        }
        num_SCCS++;
    }
}

/*Descobre os SCCs (Algortimo de Tarjan)*/
void SCCS(){
    int v = 0;
    for(v = 0; v < num_students;v++){
        if(nodes[v].d_SCC == 0){
            SCCS_VISIT(v);
        }
    }
}

/*Visita cada vertice nao pertencente ao mesmo SCC atribuindo-lhe a nota indicada*/
void DFS_VISIT(int v){
    int i = 0, adj;
    time++;
    nodes[v].d_DFS = time;
    for(i = 0; i < nodes[v].num_adj; i++){
        adj = nodes[v].adj[i];
        gradesSCCs[nodes[v].SCC] = max(gradesSCCs[nodes[v].SCC], gradesSCCs[nodes[adj].SCC]);
        if(nodes[adj].d_DFS == 0){
            nodes[adj].src = v;
            DFS_VISIT(adj);
        }
    }
    if(nodes[v].src >= 0){
        int v_src_SCC = nodes[nodes[v].src].SCC;
        gradesSCCs[v_src_SCC] = max(gradesSCCs[v_src_SCC], gradesSCCs[nodes[v].SCC]);
    }
}

/*Atribui a nota a cada SCC (Algortimo DFS)*/
void DFS(){
    int v = 0;
    for(v = 0; v < num_students;v++){
        if(nodes[v].d_DFS == 0){
            DFS_VISIT(v);

        }
    }
}

int main(){
    processInput();
    SCCS();
    time = 0;
    DFS();
    printGrades();
    freeMemory();
    return 0;
}