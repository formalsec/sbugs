/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 


struct AdjStudentNode
{
  int id;
  struct AdjStudentNode *next;
};
struct AdjStudent
{
  int nota;
  struct AdjStudentNode *head;
};
struct Grafo
{
  int numAlunos;
  struct AdjStudent *array;
};
int numRelacoes;
int numAlunos;
struct Grafo *grafoGeral;
struct AdjStudentNode *newAdjStudentNode(int id)
{
  struct AdjStudentNode *newNode = (struct AdjStudentNode *) malloc(sizeof(struct AdjStudentNode));
  newNode->id = id;
  newNode->next = 0;
  return newNode;
}

void freeAdjStudentNode(struct AdjStudentNode *node)
{
  free(node);
}

struct Grafo *newGrafo(int N)
{
  int i;
  struct Grafo *grafo = (struct Grafo *) malloc(sizeof(struct Grafo));
  grafo->numAlunos = N;
  grafo->array = (struct AdjStudent *) malloc(N * (sizeof(struct AdjStudent)));
  for (i = 0; i < N; i++)
  {
    grafo->array[i].head = 0;
    grafo->array[i].nota = 0;
  }

  return grafo;
}

void freeGrafo(struct Grafo *grafo)
{
  int i;
  struct AdjStudentNode *dummyNext;
  for (i = 0; i < grafo->numAlunos; i++)
  {
    while (grafo->array[i].head != 0)
    {
      dummyNext = grafo->array[i].head->next;
      freeAdjStudentNode(grafo->array[i].head);
      grafo->array[i].head = dummyNext;
    }

  }

  free(grafo->array);
  free(grafo);
}

void addLigacao(struct Grafo *grafo, int src, int dest)
{
  struct AdjStudentNode *newNode = newAdjStudentNode(dest);
  newNode->next = grafo->array[src - 1].head;
  grafo->array[src - 1].head = newNode;
}

void processaNotasIniciais()
{
  char str[15];
  int i;
  for (i = 0; i < numAlunos; i++)
  {
    if (fgets(str, 15, stdin) == 0)
    {
    }
    else
    {
      
    }

    grafoGeral->array[i].nota = atoi(str);
  }

}

void processaRelacoes()
{
  char str[20];
  int al;
  int ami;
  int i;
  for (i = 1; i <= numRelacoes; i++)
  {
    if (fgets(str, 20, stdin) == 0)
    {
    }
    else
    {
      
    }

    al = new_sym_var(sizeof(int) * 8);
    ami = new_sym_var(sizeof(int) * 8);
    addLigacao(grafoGeral, ami, al);
  }

}

void printAllNotas()
{
  int i;
  for (i = 1; i <= numAlunos; i++)
  {
    printf("%d\n", grafoGeral->array[i - 1].nota);
  }

}

void processaInput()
{
  char input[100];
  int i = 0;
  int j = 0;
  char nAlunos[20];
  char nRelacoes[20];
  if (fgets(input, 100, stdin) == 0)
  {
  }
  else
  {
    
  }

  for (; input[i] != ','; i++)
  {
    nAlunos[i] = input[i];
  }

  nAlunos[i] = 0;
  i++;
  for (; input[i] != 0; i++)
  {
    nRelacoes[j] = input[i];
    j++;
  }

  nRelacoes[j] = 0;
  numAlunos = atoi(nAlunos);
  numRelacoes = atoi(nRelacoes);
}

void DFS(struct Grafo *grafo, int vertice)
{
  struct AdjStudentNode *adjStudent = grafo->array[vertice].head;
  struct AdjStudentNode *temp = adjStudent;
  int notaVertice = grafo->array[vertice].nota;
  int verticeAtual;
  while (temp != 0)
  {
    adjStudent = temp;
    verticeAtual = temp->id - 1;
    if (grafo->array[verticeAtual].nota < notaVertice)
    {
      grafo->array[verticeAtual].nota = notaVertice;
      DFS(grafo, verticeAtual);
    }
    else
    {
      
    }

    temp = adjStudent->next;
  }

}

void initDFS()
{
  int i;
  for (i = 0; i < numAlunos; i++)
  {
    if (grafoGeral->array[i].head)
    {
      DFS(grafoGeral, i);
    }
    else
    {
      
    }

  }

}

int main()
{
  processaInput();
  grafoGeral = newGrafo(numAlunos);
  processaNotasIniciais();
  processaRelacoes();
  initDFS();
  printAllNotas();
  freeGrafo(grafoGeral);
  return 0;
}

