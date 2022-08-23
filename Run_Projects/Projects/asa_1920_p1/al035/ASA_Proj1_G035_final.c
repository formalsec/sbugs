/**
 * Projecto1 - ASA - Marco 2020 
 * 
 * Grupo - 035
 * Numero - 93880
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define MAXINPUT 100

/**
 * 
 * ESTRUTURAS
 * 
 */
  
/**
 *  Estrutura que representa Alunos adjacentes
 */
struct AdjStudentNode { 
    int id;
    struct AdjStudentNode* next; 
}; 
  
/**
 * Estrutura que representa uma lista de Alunos adjacentes
 */ 
struct AdjStudent { 
    int nota;
    struct AdjStudentNode *head;  
}; 
  
/**
 * Estrutura que representa um grafo, composto por todas as listas de adjacencias de Alunos
 */
struct Grafo { 
    int numAlunos; 
    struct AdjStudent* array; 
};

/**
 * 
 * VARIAVEIS GLOBAIS
 * 
 */

int numRelacoes, numAlunos;
struct Grafo* grafoGeral;

/**
 * 
 * FUNCOES
 * 
 */

/**
 * Funcao para criar uma nova lista de alunos adjacentes
 */
struct AdjStudentNode* newAdjStudentNode(int id) { 
    struct AdjStudentNode* newNode = 
     (struct AdjStudentNode*) malloc(sizeof(struct AdjStudentNode)); 
    newNode->id = id;
    newNode->next = NULL; 
    return newNode; 
}

void freeAdjStudentNode(struct AdjStudentNode* node) {
    free(node);
}

/**
 * Funcao para criar um novo grafo com N (numero de alunos) vertices
 */
struct Grafo* newGrafo(int N) {
    int i;  
    struct Grafo* grafo =  
        (struct Grafo*) malloc(sizeof(struct Grafo)); 
    grafo->numAlunos = N; 
  
    grafo->array =  
      (struct AdjStudent*) malloc(N * sizeof(struct AdjStudent)); 
    
    for (i = 0; i < N; i++) {
        grafo->array[i].head = NULL;
        grafo->array[i].nota = 0;
    }
    return grafo; 
}

/**
 * Funcao que liberta a memoria alocada pelo grafo
 */
void freeGrafo(struct Grafo * grafo) {
    int i;
    struct AdjStudentNode* dummyNext;
    for (i = 0; i < grafo->numAlunos; i++) {
        while ( grafo->array[i].head != NULL) {
            dummyNext = grafo->array[i].head->next;
            freeAdjStudentNode(grafo->array[i].head);
            grafo->array[i].head = dummyNext;
        }
    }
    free(grafo->array);
    free(grafo);
}

/**
 * Adiciona uma ligacao adjacente a um grafo 
 */
void addLigacao(struct Grafo* grafo, int src, int dest) { 
    /* Add an edge from src to dest.  A new node is  
     added to the adjacency list of src.  The node 
     is added at the begining 
    */

    struct AdjStudentNode* newNode = newAdjStudentNode(dest); 
    newNode->next = grafo->array[src-1].head; 
    grafo->array[src-1].head = newNode; 
    /** (src-1) para o indice guardado no grafo coincidir,
     * pois comeca no 0, e os alunos comecam no 1.
     */
}

/**
 * Retira as notas de cada aluno iniciais recebidas no stdin
 */
void processaNotasIniciais() {
    char str[15];
    int i;
    for (i = 0; i<numAlunos; i++) {
        if ( fgets(str, 15, stdin) == NULL) {
            /*ERRO*/
        }
        grafoGeral->array[i].nota = atoi(str);
    }
}

/**
 * Retira as relacoes entre alunos recebidas no stdin
 */
void processaRelacoes() {
    char str[20];
    int al, ami, i;
    for (i = 1; i <= numRelacoes; i++) {
        if ( fgets(str, 20, stdin) == NULL) {
            /*ERRO*/
        }
        sscanf(str, "%d %d", &al, &ami);
        addLigacao(grafoGeral, ami, al);
    }
}

/**
 * Funcao que imprime as notas de cada aluno, por ordem, no stdout
 */
void printAllNotas() {
    int i;
    for (i = 1; i<=numAlunos; i++) {
        printf("%d\n", grafoGeral->array[i-1].nota);
    }
}

/**
 * Funcao que retira Numero de Alunos e Numero e Relacoes entre alunos recebidos no stdin 
 */
void processaInput() {
    char input[MAXINPUT];
    int i = 0;
    int j = 0;

    char nAlunos[20];
    char nRelacoes[20];

    if( fgets(input, MAXINPUT, stdin) == NULL ) {
        /*ERRO*/
    }

    for(; input[i] != ','; i++) {
        nAlunos[i] = input[i];
    }
    nAlunos[i] = 0;
    i++;

    for(; input[i] != 0; i++) {
        nRelacoes[j] = input[i];
        j++;
    }
    nRelacoes[j] = 0;

    numAlunos = atoi(nAlunos);
    numRelacoes = atoi(nRelacoes);
}

/**
 * Funcao Depth First Search para ir percorrer as relacoes dos alunos
 */ 
void DFS(struct Grafo * grafo, int vertice) {
    struct AdjStudentNode* adjStudent = grafo->array[vertice].head;
    struct AdjStudentNode* temp = adjStudent;
    int notaVertice = grafo->array[vertice].nota;
    int verticeAtual;
        
    while(temp != NULL) {
        adjStudent = temp;
        verticeAtual = temp->id - 1;
        
        if(grafo->array[verticeAtual].nota < notaVertice) {
            grafo->array[verticeAtual].nota = notaVertice;
            DFS(grafo, verticeAtual);
        }
        temp = adjStudent->next;
    } 
}

/**
 * Funcao iniciadora da DFS
 */
void initDFS() {
    int i;
    for (i = 0; i<numAlunos; i++) {
        if (grafoGeral->array[i].head) {
            DFS(grafoGeral, i);
        }
    }
}

int main() {

    processaInput();

    grafoGeral = newGrafo(numAlunos);

    processaNotasIniciais();
    processaRelacoes();

    initDFS();

    printAllNotas();
    freeGrafo(grafoGeral);

    return 0; 
} 