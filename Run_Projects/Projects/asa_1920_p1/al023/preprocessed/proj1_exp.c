/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct No
{
  int valor;
  struct No *proximo_no;
} no;
typedef struct Grafo
{
  int num_vertices;
  int *visitado;
  int *valores;
  no **listas_adjacencia;
} grafo;
int max(int a, int b);
no *criaNo(int valor);
grafo *criaGrafo(int num_vertices);
void associaValor(grafo *grafo, int indice, int valor);
void adicionaAresta(grafo *grafo, int origem, int destino);
void DFS(grafo *grafo);
void visitaDFS(grafo *grafo, int v_pai);
void imprimeValores(grafo *grafo);
void libertaGrafo(grafo *grafo);
int main()
{
  int i;
  int num_alunos;
  int num_amizades;
  if (!2)
  {
    return -1;
  }
  else
  {
    num_alunos = new_sym_var(sizeof(int) * 8);
    num_amizades = new_sym_var(sizeof(int) * 8);
    
  }

  grafo *turma = criaGrafo(num_alunos);
  int nota;
  for (i = 1; i <= num_alunos; i++)
  {
    if (!1)
    {
      return -1;
    }
    else
    {
      nota = new_sym_var(sizeof(int) * 8);
      
    }

    associaValor(turma, i, nota);
  }

  int aluno;
  int amigo;
  for (i = 1; i <= num_amizades; i++)
  {
    if (!2)
    {
      return -1;
    }
    else
    {
      aluno = new_sym_var(sizeof(int) * 8);
      amigo = new_sym_var(sizeof(int) * 8);
      
    }

    adicionaAresta(turma, aluno, amigo);
  }

  DFS(turma);
  imprimeValores(turma);
  libertaGrafo(turma);
  return 0;
}

int max(int a, int b)
{
  return (a > b) ? (a) : (b);
}

no *criaNo(int valor)
{
  no *novo_no = malloc(sizeof(no));
  novo_no->valor = valor;
  novo_no->proximo_no = 0;
  return novo_no;
}

grafo *criaGrafo(int num_vertices)
{
  grafo *g = (grafo *) malloc(sizeof(grafo));
  g->num_vertices = num_vertices;
  g->visitado = (int *) malloc((num_vertices + 1) * (sizeof(int)));
  g->valores = (int *) malloc((num_vertices + 1) * (sizeof(int)));
  g->listas_adjacencia = (no **) malloc((num_vertices + 1) * (sizeof(no *)));
  int i;
  for (i = 0; i <= num_vertices; i++)
  {
    g->visitado[i] = 0;
    g->listas_adjacencia[i] = 0;
  }

  return g;
}

void associaValor(grafo *g, int indice, int valor)
{
  g->valores[indice] = valor;
}

void adicionaAresta(grafo *g, int origem, int destino)
{
  no *novo_no = criaNo(destino);
  novo_no->proximo_no = g->listas_adjacencia[origem];
  g->listas_adjacencia[origem] = novo_no;
}

void DFS(grafo *g)
{
  int v;
  for (v = 1; v <= g->num_vertices; v++)
    if (!g->visitado[v])
  {
    visitaDFS(g, v);
  }
  else
  {
    
  }


}

void visitaDFS(grafo *g, int n_pai)
{
  g->visitado[n_pai] = 1;
  no *v_filho = g->listas_adjacencia[n_pai];
  while (v_filho != 0)
  {
    if (!g->visitado[v_filho->valor])
    {
      visitaDFS(g, v_filho->valor);
    }
    else
    {
      
    }

    g->valores[n_pai] = max(g->valores[n_pai], g->valores[v_filho->valor]);
    v_filho = v_filho->proximo_no;
  }

}

void imprimeValores(grafo *g)
{
  int v;
  for (v = 1; v <= g->num_vertices; v++)
    printf("%d\n", g->valores[v]);

}

void libertaGrafo(grafo *g)
{
  int i;
  no *no_;
  no *proximo_no;
  for (i = 0; i <= g->num_vertices; i++)
  {
    no_ = g->listas_adjacencia[i];
    while (no_ != 0)
    {
      proximo_no = no_->proximo_no;
      free(no_);
      no_ = proximo_no;
    }

  }

  free(g->listas_adjacencia);
  free(g->visitado);
  free(g->valores);
  free(g);
}
