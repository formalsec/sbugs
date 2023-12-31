#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


typedef struct 
{
  int id;
  char desc[64];
  int preco;
  int peso;
  int quant;
  int quantEmEncomendas;
} Produto;
typedef struct 
{
  int ordenado[200];
  int peso;
  int numero_produtos;
} Encomenda;
int matriz[500][10000];
Produto stock[10000];
int stock_ordenado[10000];
Encomenda encomendas[500];
int num_encomendas;
int num_produtos;
void a();
void q();
void N();
void A();
void r();
void R();
void C();
void p();
void m();
void E();
void l();
void L();
void adicionaOrdenado(int arr[], int n, int idp, char key);
void removeOrdenado(int arr[], int n, int idp);
int cmpProdutos(Produto p1, Produto p2, char key);
int procura(int arr[], int n, int id);
int main()
{
  while (1)
  {
    switch (getchar())
    {
      case 'a':
        a();
        break;

      case 'q':
        q();
        break;

      case 'N':
        N();
        break;

      case 'A':
        A();
        break;

      case 'r':
        r();
        break;

      case 'R':
        R();
        break;

      case 'C':
        C();
        break;

      case 'p':
        p();
        break;

      case 'E':
        E();
        break;

      case 'm':
        m();
        break;

      case 'l':
        l();
        break;

      case 'L':
        L();
        break;

      case 'x':
        return 0;

    }

  }

  return 1;
}

void a()
{
  Produto p = {0};
  for (int p_index = 0; p_index < 10; p_index++)
  {
    p.desc[p_index] = new_sym_var(sizeof(char) * 8);
  }

  p.desc[10 - 1] = '\0';
  p.preco = new_sym_var(sizeof(int) * 8);
  p.peso = new_sym_var(sizeof(int) * 8);
  p.quant = new_sym_var(sizeof(int) * 8);
  stock[p.id = num_produtos] = p;
  printf("Novo produto %d.\n", p.id);
  adicionaOrdenado(stock_ordenado, num_produtos, p.id, 'p');
  num_produtos++;
}

void q()
{
  int idp;
  int quant;
  idp = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (idp < num_produtos)
  {
    stock[idp].quant += quant;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void N()
{
  printf("Nova encomenda %d.\n", num_encomendas);
  num_encomendas++;
}

void A()
{
  int ide;
  int idp;
  int quant;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (!(ide < num_encomendas))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (!(idp < num_produtos))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if ((stock[idp].quantEmEncomendas + quant) > stock[idp].quant)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (((stock[idp].peso * quant) + encomendas[ide].peso) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          if (!matriz[ide][idp])
          {
            adicionaOrdenado(encomendas[ide].ordenado, encomendas[ide].numero_produtos, idp, 'd');
            encomendas[ide].numero_produtos++;
          }
          else
          {
            
          }

          matriz[ide][idp] += quant;
          encomendas[ide].peso += stock[idp].peso * quant;
          stock[idp].quantEmEncomendas += quant;
        }

      }

    }

  }

}

void r()
{
  int idp;
  int quant;
  idp = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (!(idp < num_produtos))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((stock[idp].quant - quant) < stock[idp].quantEmEncomendas)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idp);
    }
    else
    {
      stock[idp].quant -= quant;
    }

  }

}

void R()
{
  int ide;
  int idp;
  int quant;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (!(ide < num_encomendas))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (!(idp < num_produtos))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (encomendas[ide].numero_produtos)
      {
        quant = matriz[ide][idp];
        if (quant)
        {
          matriz[ide][idp] = 0;
          encomendas[ide].peso -= stock[idp].peso * quant;
          stock[idp].quantEmEncomendas -= quant;
          removeOrdenado(encomendas[ide].ordenado, encomendas[ide].numero_produtos, idp);
          encomendas[ide].numero_produtos--;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

}

void C()
{
  int ide;
  int i;
  int j;
  int max;
  int custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  max = encomendas[ide].numero_produtos;
  if (!(ide < num_encomendas))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0, j = 0; (i < 10000) && (j < max); i++)
    {
      if (matriz[ide][i])
      {
        j++;
        custo += matriz[ide][i] * stock[i].preco;
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", ide, custo);
  }

}

void p()
{
  int idp;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (!(idp < num_produtos))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    removeOrdenado(stock_ordenado, num_produtos, idp);
    num_produtos--;
    stock[idp].preco = preco;
    adicionaOrdenado(stock_ordenado, num_produtos, idp, 'p');
    num_produtos++;
  }

}

void E()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (!(ide < num_encomendas))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (!(idp < num_produtos))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      printf("%s %d.\n", stock[idp].desc, matriz[ide][idp]);
    }

  }

}

void m()
{
  int idp;
  int i;
  int max;
  int maxValor;
  int valor;
  idp = new_sym_var(sizeof(int) * 8);
  if (!(idp < num_produtos))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    maxValor = INT_MIN;
    for (i = 0; i < 500; i++)
    {
      valor = matriz[i][idp];
      if (valor > maxValor)
      {
        maxValor = valor;
        max = i;
      }
      else
      {
        
      }

    }

    if (maxValor)
    {
      printf("Maximo produto %d %d %d.\n", idp, max, maxValor);
    }
    else
    {
      
    }

  }

}

void l()
{
  int i;
  int quant;
  Produto p;
  printf("Produtos\n");
  for (i = 0; i < num_produtos; i++)
  {
    quant = stock[stock_ordenado[i]].quant - stock[stock_ordenado[i]].quantEmEncomendas;
    p = stock[stock_ordenado[i]];
    printf("* %s %d %d\n", p.desc, p.preco, quant);
  }

}

void L()
{
  int i;
  int ide;
  int n;
  Produto p;
  ide = new_sym_var(sizeof(int) * 8);
  if (!(ide < num_encomendas))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    n = encomendas[ide].numero_produtos;
    printf("Encomenda %d\n", ide);
    for (i = 0; i < n; i++)
    {
      p = stock[encomendas[ide].ordenado[i]];
      printf("* %s %d %d\n", p.desc, p.preco, matriz[ide][p.id]);
    }

  }

}

int cmpProdutos(Produto p1, Produto p2, char key)
{
  if (key == 'p')
  {
    if (p1.preco == p2.preco)
    {
      return 0;
    }
    else
    {
      
    }

    return (p1.preco > p2.preco) ? (1) : (-1);
  }
  else
  {
    return strcmp(p1.desc, p2.desc);
  }

}

void adicionaOrdenado(int arr[], int n, int p, char key)
{
  int i;
  int j;
  for (i = n - 1; (i >= 0) && (cmpProdutos(stock[arr[i]], stock[p], key) > 0); i--)
  {
    arr[i + 1] = arr[i];
  }

  for (j = i; ((j >= 0) && (p < arr[j])) && (cmpProdutos(stock[arr[j]], stock[p], key) == 0); j--)
  {
    arr[j + 1] = arr[j];
  }

  arr[j + 1] = p;
}

void removeOrdenado(int arr[], int n, int p)
{
  int i;
  int pos = procura(arr, n - 1, p);
  for (i = pos; i < (n - 1); i++)
    arr[i] = arr[i + 1];

}

int procura(int arr[], int n, int id)
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (arr[i] == id)
    {
      return i;
    }
    else
    {
      
    }

  }

  return i;
}

