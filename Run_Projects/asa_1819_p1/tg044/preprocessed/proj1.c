/*File generated by PreProcessor.py*/


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef int verticeId;
typedef struct node verticeDoGrafo;
typedef struct grafo Grafo;
struct node
{
  verticeId Id;
  verticeDoGrafo *next;
};
struct grafo
{
  int V;
  int E;
  int numeroDeArvores;
  verticeDoGrafo **listaAdjacencias;
};
int *maiorVerticeLista;
int maiorVertice = 0;
int *subtreeIds;
int tamanhoArvoreFinal = 0;
int tamanhoArvoreInstancia = 0;
bool ciclo = false;
Grafo *initGraph(int V)
{
  Grafo *grafo = 0;
  if ((V > 0) && ((grafo = (Grafo *) malloc(sizeof(struct grafo))) != 0))
  {
    grafo->V = V;
    grafo->E = 0;
    grafo->numeroDeArvores = 0;
    grafo->listaAdjacencias = (verticeDoGrafo **) malloc(V * (sizeof(struct node *)));
  }
  else
  {
    
  }

  return grafo;
}

void libertaGrafo(Grafo *grafo)
{
  int i;
  for (i = 0; i < grafo->V; ++i)
  {
    verticeDoGrafo *cabeca = grafo->listaAdjacencias[i];
    while (cabeca != 0)
    {
      verticeDoGrafo *temp = cabeca;
      cabeca = cabeca->next;
      free(temp);
    }

  }

  free(grafo->listaAdjacencias);
  free(grafo);
}

void adicionaPonteAoGrafo(Grafo *grafo, verticeId u, verticeId v)
{
  if (((u > 0) && (u <= grafo->V)) && ((v > 0) && (v <= grafo->V)))
  {
    verticeDoGrafo *w = (verticeDoGrafo *) malloc(sizeof(struct node));
    verticeDoGrafo *x = (verticeDoGrafo *) malloc(sizeof(struct node));
    w->Id = u;
    x->Id = v;
    w->next = grafo->listaAdjacencias[v - 1];
    x->next = grafo->listaAdjacencias[u - 1];
    grafo->listaAdjacencias[v - 1] = w;
    grafo->listaAdjacencias[u - 1] = x;
    grafo->E++;
  }
  else
  {
    
  }

}

void tarjanVisit(Grafo *grafo, verticeId u, int **lista, int pontosDeArticulacao[1])
{
  verticeDoGrafo *node = grafo->listaAdjacencias[u - 1];
  verticeId adj;
  bool pontoDeArticulacaoCandidato = false;
  int outDegree = 0;
  lista[1][u - 1] = lista[0][0];
  lista[2][u - 1] = lista[0][0];
  ++lista[0][0];
  tamanhoArvoreFinal = (tamanhoArvoreFinal < tamanhoArvoreInstancia) ? (tamanhoArvoreInstancia) : (tamanhoArvoreFinal);
  if (maiorVertice < u)
  {
    subtreeIds[u] = 1;
    subtreeIds[maiorVertice] = 0;
    maiorVertice = (maiorVertice < u) ? (u) : (maiorVertice);
  }
  else
  {
    
  }

  maiorVerticeLista[grafo->numeroDeArvores] = (maiorVerticeLista[grafo->numeroDeArvores] < u) ? (u) : (maiorVerticeLista[grafo->numeroDeArvores]);
  while (node != 0)
  {
    adj = node->Id;
    if (lista[4][u - 1] == 1)
    {
      tamanhoArvoreFinal = (tamanhoArvoreFinal < tamanhoArvoreInstancia) ? (tamanhoArvoreInstancia) : (tamanhoArvoreFinal);
      tamanhoArvoreInstancia = 0;
      break;
    }
    else
    {
      if (lista[1][adj - 1] == (-1))
      {
        lista[3][adj - 1] = u;
        tamanhoArvoreInstancia++;
        outDegree++;
        tarjanVisit(grafo, adj, lista, pontosDeArticulacao);
        if ((lista[1][u - 1] <= lista[2][adj - 1]) && (lista[4][u - 1] != 1))
        {
          tamanhoArvoreFinal = (tamanhoArvoreFinal < tamanhoArvoreInstancia) ? (tamanhoArvoreInstancia) : (tamanhoArvoreFinal);
          tamanhoArvoreInstancia = 0;
          ciclo = true;
          pontoDeArticulacaoCandidato = true;
        }
        else
        {
          lista[2][u - 1] = (lista[2][u - 1] < lista[2][adj - 1]) ? (lista[2][u - 1]) : (lista[2][adj - 1]);
        }

      }
      else
      {
        if (adj != lista[3][u - 1])
        {
          lista[2][u - 1] = (lista[2][u - 1] < lista[1][adj - 1]) ? (lista[2][u - 1]) : (lista[1][adj - 1]);
        }
        else
        {
          
        }

      }

    }

    node = node->next;
  }

  tamanhoArvoreFinal = (tamanhoArvoreFinal < tamanhoArvoreInstancia) ? (tamanhoArvoreInstancia) : (tamanhoArvoreFinal);
  if (((lista[3][u - 1] == (-1)) && (outDegree > 1)) || ((lista[3][u - 1] != (-1)) && pontoDeArticulacaoCandidato))
  {
    ++pontosDeArticulacao[0];
    lista[4][u - 1] = 1;
  }
  else
  {
    
  }

}

void inicializaTarjan(Grafo *grafo, int pontosDeArticulacao[1], int **lista)
{
  int i;
  pontosDeArticulacao[0] = 0;
  for (i = 0; i < grafo->V; i++)
  {
    if (lista[1][i++] == (-1))
    {
      grafo->numeroDeArvores++;
      maiorVerticeLista[grafo->numeroDeArvores] = 1;
      maiorVertice = 0;
      tarjanVisit(grafo, i, lista, pontosDeArticulacao);
    }
    else
    {
      
    }

  }

}

int compare(const void *a, const void *b)
{
  return (*((int *) a)) - (*((int *) b));
}

int main()
{
  int V = 0;
  int E = 0;
  int i;
  int origem = 0;
  int destino = 0;
  int **lista;
  int pontosDeArticulacao[1];
  Grafo *grafo;
  lista = (int **) malloc(5 * (sizeof(int *)));
  V = new_sym_var(sizeof(int) * 8);
  E = new_sym_var(sizeof(int) * 8);
  int a[V + 1];
  int s[V + 1];
  for (i = 0; i <= V; i++)
  {
    s[i] = 0;
  }

  subtreeIds = s;
  maiorVerticeLista = a;
  grafo = initGraph(V);
  if (lista != 0)
  {
    lista[0] = (int *) malloc(sizeof(int));
    lista[1] = (int *) malloc(grafo->V * (sizeof(int)));
    lista[2] = (int *) malloc(grafo->V * (sizeof(int)));
    lista[3] = (int *) malloc(grafo->V * (sizeof(int)));
    lista[4] = (int *) malloc(grafo->V * (sizeof(int)));
  }
  else
  {
    
  }

  lista[0][0] = 0;
  for (i = 0; i < grafo->V; i++)
  {
    s[i] = 0;
    lista[1][i] = -1;
    lista[3][i] = -1;
    lista[4][i] = -1;
  }

  for (i = 0; i < E; i++)
  {
    origem = new_sym_var(sizeof(int) * 8);
    destino = new_sym_var(sizeof(int) * 8);
    adicionaPonteAoGrafo(grafo, origem, destino);
  }

  inicializaTarjan(grafo, pontosDeArticulacao, lista);
  printf("%d\n", grafo->numeroDeArvores);
  maiorVerticeLista[0] = -1;
  for (i = 0; i <= V; i++)
  {
    if (subtreeIds[i] == 1)
    {
      printf("%d", i);
      if (i < grafo->V)
      {
        printf(" ");
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  printf("\n");
  printf("%d\n", pontosDeArticulacao[0]);
  lista[0][0] = 0;
  for (i = 0; i < grafo->V; i++)
  {
    lista[3][i] = -1;
    lista[2][i] = -1;
    lista[1][i] = -1;
  }

  tamanhoArvoreFinal = 0;
  tamanhoArvoreInstancia = 0;
  inicializaTarjan(grafo, pontosDeArticulacao, lista);
  if (ciclo)
  {
    printf("%d\n", tamanhoArvoreFinal + 1);
  }
  else
  {
    printf("%d\n", tamanhoArvoreFinal);
  }

  libertaGrafo(grafo);
  free(lista[0]);
  free(lista[1]);
  free(lista[2]);
  free(lista[3]);
  free(lista[4]);
  free(lista);
  return 0;
}

