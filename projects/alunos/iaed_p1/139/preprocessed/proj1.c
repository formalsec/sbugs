#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Produto
{
  char nome[64];
  int preco;
  int peso;
  int quantidade;
} Produto;
typedef struct Encomenda
{
  Produto prod;
  int id_produto;
} Encomenda;
void adic_sub_peso(int id_produto, int peso_encomendas[], int qtd, int id_encomenda);
void adiciona_stock_prod(int id, int qtd);
void adiciona_stock_enc(int id_encomenda, int id_produto, int qtd);
int existe_encomenda_produto(int id, int marcador);
int prod_na_encomenda(int id_prod, int id_encomenda);
void retira_stock_prod(int id, int qtd);
void retira_stock_enc(int id_encomenda, int id_produto, int qtd);
int adiciona_prod();
void adiciona_stock();
int adiciona_encomenda();
void adic_prod_encomenda(int peso_encomendas[]);
void remove_stock();
void retira_produto_encomenda(int peso_encomendas[]);
void custo_encomenda();
void muda_preco();
void lista_nome_quant();
void lista_encomenda();
void merge_sort(Produto produtos[], int l, int r);
void merge(Produto produtos[], int l, int m, int r);
void organiza_produtos();
void merge_sort_char(Encomenda a[], int l, int r);
void merge_char(Encomenda a[], int l, int m, int r);
void organiza_encomenda();
Produto produtos[10000] = {0};
Encomenda encomendas[500][200];
int identificador = 0;
int ident_enc = 0;
int prod_encomenda[500] = {0};
int main()
{
  char letra;
  int peso_encomendas[500] = {0};
  letra = new_sym_var(sizeof(char) * 8);
  while (letra != 'x')
  {
    switch (letra)
    {
      case 'a':
        identificador = adiciona_prod();
        break;

      case 'q':
        adiciona_stock();
        break;

      case 'N':
        ident_enc = adiciona_encomenda();
        break;

      case 'A':
        adic_prod_encomenda(peso_encomendas);
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        retira_produto_encomenda(peso_encomendas);
        break;

      case 'C':
        custo_encomenda();
        break;

      case 'p':
        muda_preco();
        break;

      case 'E':
        lista_nome_quant();
        break;

      case 'm':
        lista_encomenda();
        break;

      case 'l':
        organiza_produtos();
        break;

      case 'L':
        organiza_encomenda();
        break;

    }

    letra = new_sym_var(sizeof(char) * 8);
  }

  return 0;
}

void adic_sub_peso(int id_produto, int peso_encomendas[], int qtd, int id_encomenda)
{
  peso_encomendas[id_encomenda] += produtos[id_produto].peso * qtd;
}

void adiciona_stock_prod(int id, int qtd)
{
  produtos[id].quantidade += qtd;
}

void adiciona_stock_enc(int id_encomenda, int id_produto, int qtd)
{
  encomendas[id_encomenda][id_produto].prod.quantidade += qtd;
}

int existe_encomenda_produto(int id, int marcador)
{
  if (id >= marcador)
  {
    return 0;
  }
  else
  {
    return 1;
  }

}

int prod_na_encomenda(int id_prod, int id_encomenda)
{
  int i;
  int j = prod_encomenda[id_encomenda];
  for (i = 0; i < j; i++)
  {
    if (encomendas[id_encomenda][i].id_produto == id_prod)
    {
      if (encomendas[id_encomenda][i].prod.quantidade != 0)
      {
        return 1;
      }
      else
      {
        
      }

      break;
    }
    else
    {
      
    }

  }

  return 0;
}

void retira_stock_prod(int id, int qtd)
{
  produtos[id].quantidade -= qtd;
}

void retira_stock_enc(int id_encomenda, int id_produto, int qtd)
{
  encomendas[id_encomenda][id_produto].prod.quantidade -= qtd;
}

int adiciona_prod()
{
  int preco;
  int peso;
  int quantidade;
  char nome[64];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  preco = new_sym_var(sizeof(int) * 8);
  peso = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  strcpy(produtos[identificador].nome, nome);
  produtos[identificador].preco = preco;
  produtos[identificador].peso = peso;
  produtos[identificador].quantidade = quantidade;
  printf("Novo produto %d.\n", identificador);
  identificador++;
  return identificador;
}

void adiciona_stock()
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (existe_encomenda_produto(id, identificador) == 1)
  {
    adiciona_stock_prod(id, qtd);
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
  }

}

int adiciona_encomenda()
{
  printf("Nova encomenda %d.\n", ident_enc);
  ident_enc++;
  return ident_enc;
}

void adic_prod_encomenda(int peso_encomendas[])
{
  int id_encomenda;
  int id_produto;
  int quant;
  int i;
  int state;
  id_encomenda = new_sym_var(sizeof(int) * 8);
  id_produto = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (existe_encomenda_produto(id_encomenda, ident_enc) == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
  }
  else
  {
    if (existe_encomenda_produto(id_produto, identificador) == 0)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
    }
    else
    {
      if (quant > produtos[id_produto].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_produto, id_encomenda);
      }
      else
      {
        if ((peso_encomendas[id_encomenda] + (produtos[id_produto].peso * quant)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_produto, id_encomenda);
        }
        else
        {
          state = prod_na_encomenda(id_produto, id_encomenda);
          for (i = 0; i < 200; i++)
          {
            if ((state == 0) && (encomendas[id_encomenda][i].prod.quantidade == 0))
            {
              adiciona_stock_enc(id_encomenda, i, quant);
              strcpy(encomendas[id_encomenda][i].prod.nome, produtos[id_produto].nome);
              encomendas[id_encomenda][i].prod.preco = produtos[id_produto].preco;
              encomendas[id_encomenda][i].id_produto = id_produto;
              prod_encomenda[id_encomenda]++;
              break;
            }
            else
            {
              if ((encomendas[id_encomenda][i].id_produto == id_produto) && (state == 1))
              {
                adiciona_stock_enc(id_encomenda, i, quant);
                break;
              }
              else
              {
                
              }

            }

          }

          adic_sub_peso(id_produto, peso_encomendas, quant, id_encomenda);
          retira_stock_prod(id_produto, quant);
        }

      }

    }

  }

}

void remove_stock()
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (existe_encomenda_produto(id, identificador) == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
  }
  else
  {
    if (qtd > produtos[id].quantidade)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
    }
    else
    {
      retira_stock_prod(id, qtd);
    }

  }

}

void retira_produto_encomenda(int peso_encomendas[])
{
  int id_produto;
  int id_encomenda;
  int i;
  int j;
  id_encomenda = new_sym_var(sizeof(int) * 8);
  id_produto = new_sym_var(sizeof(int) * 8);
  j = prod_encomenda[id_encomenda];
  if (existe_encomenda_produto(id_encomenda, ident_enc) == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_produto, id_encomenda);
  }
  else
  {
    if (existe_encomenda_produto(id_produto, identificador) == 0)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_produto, id_encomenda);
    }
    else
    {
      for (i = 0; i < j; i++)
      {
        if (encomendas[id_encomenda][i].id_produto == id_produto)
        {
          adic_sub_peso(id_produto, peso_encomendas, -encomendas[id_encomenda][i].prod.quantidade, id_encomenda);
          adiciona_stock_prod(id_produto, encomendas[id_encomenda][i].prod.quantidade);
          retira_stock_enc(id_encomenda, i, encomendas[id_encomenda][i].prod.quantidade);
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void custo_encomenda()
{
  int id_encomenda;
  int i;
  int cost = 0;
  int j;
  id_encomenda = new_sym_var(sizeof(int) * 8);
  j = prod_encomenda[id_encomenda];
  if (existe_encomenda_produto(id_encomenda, ident_enc) == 0)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_encomenda);
  }
  else
  {
    for (i = 0; i < j; i++)
    {
      cost += encomendas[id_encomenda][i].prod.preco * encomendas[id_encomenda][i].prod.quantidade;
    }

    printf("Custo da encomenda %d %d.\n", id_encomenda, cost);
  }

}

void muda_preco()
{
  int id_produto;
  int preco;
  int i;
  int j;
  id_produto = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (existe_encomenda_produto(id_produto, identificador) == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_produto);
  }
  else
  {
    produtos[id_produto].preco = preco;
    for (i = 0; i < ident_enc; i++)
    {
      for (j = 0; j < prod_encomenda[i]; j++)
      {
        if (encomendas[i][j].id_produto == id_produto)
        {
          encomendas[i][j].prod.preco = preco;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void lista_nome_quant()
{
  int id_encomenda;
  int id_produto;
  int quant = 0;
  int i;
  int j;
  id_encomenda = new_sym_var(sizeof(int) * 8);
  id_produto = new_sym_var(sizeof(int) * 8);
  j = prod_encomenda[id_encomenda];
  if (existe_encomenda_produto(id_encomenda, ident_enc) == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
  }
  else
  {
    if (existe_encomenda_produto(id_produto, identificador) == 0)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", id_produto);
    }
    else
    {
      if (prod_na_encomenda(id_produto, id_encomenda) == 1)
      {
        for (i = 0; i < j; i++)
        {
          if (encomendas[id_encomenda][i].id_produto == id_produto)
          {
            quant = encomendas[id_encomenda][i].prod.quantidade;
            break;
          }
          else
          {
            
          }

        }

      }
      else
      {
        
      }

      printf("%s %d.\n", produtos[id_produto].nome, quant);
    }

  }

}

void lista_encomenda()
{
  int id_produto;
  int i = 0;
  int max = 0;
  int id_encomenda = 0;
  int j;
  id_produto = new_sym_var(sizeof(int) * 8);
  if (existe_encomenda_produto(id_produto, identificador) == 0)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_produto);
  }
  else
  {
    for (i = 0; i < ident_enc; i++)
    {
      for (j = 0; j < prod_encomenda[i]; j++)
      {
        if (encomendas[i][j].id_produto == id_produto)
        {
          if (max < encomendas[i][j].prod.quantidade)
          {
            max = encomendas[i][j].prod.quantidade;
            id_encomenda = i;
            break;
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

    if ((ident_enc != 0) && (max != 0))
    {
      printf("Maximo produto %d %d %d.\n", id_produto, id_encomenda, max);
    }
    else
    {
      
    }

  }

}

void merge(Produto a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  Produto L[10000 / 2];
  Produto R[10000 / 2];
  for (i = 0; i < n1; i++)
    L[i] = a[l + i];

  for (j = 0; j < n2; j++)
    R[j] = a[(m + 1) + j];

  i = 0, j = 0, k = l;
  while ((i < n1) && (j < n2))
  {
    if (L[i].preco <= R[j].preco)
    {
      a[k] = L[i++];
    }
    else
    {
      a[k] = R[j++];
    }

    k++;
  }

  while (i < n1)
  {
    a[k++] = L[i++];
  }

  while (j < n2)
  {
    a[k++] = R[j++];
  }

}

void merge_sort(Produto a[], int l, int r)
{
  if (r > l)
  {
    int m = l + ((r - l) / 2);
    merge_sort(a, l, m);
    merge_sort(a, m + 1, r);
    merge(a, l, m, r);
  }
  else
  {
    
  }

}

void organiza_produtos()
{
  Produto A[10000] = {0};
  int i;
  for (i = 0; i < identificador; i++)
  {
    A[i] = produtos[i];
  }

  merge_sort(A, 0, identificador - 1);
  printf("Produtos\n");
  for (i = 0; i < identificador; i++)
  {
    printf("* %s %d %d\n", A[i].nome, A[i].preco, A[i].quantidade);
  }

}

void merge_char(Encomenda a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  Encomenda L[200];
  Encomenda R[200];
  for (i = 0; i < n1; i++)
    L[i] = a[l + i];

  for (j = 0; j < n2; j++)
    R[j] = a[(m + 1) + j];

  i = 0, j = 0, k = l;
  while ((i < n1) && (j < n2))
  {
    if (strcmp(L[i].prod.nome, R[j].prod.nome) <= 0)
    {
      a[k] = L[i++];
    }
    else
    {
      a[k] = R[j++];
    }

    k++;
  }

  while (i < n1)
  {
    a[k++] = L[i++];
  }

  while (j < n2)
  {
    a[k++] = R[j++];
  }

}

void merge_sort_char(Encomenda a[], int l, int r)
{
  if (r > l)
  {
    int m = l + ((r - l) / 2);
    merge_sort_char(a, l, m);
    merge_sort_char(a, m + 1, r);
    merge_char(a, l, m, r);
  }
  else
  {
    
  }

}

void organiza_encomenda()
{
  int i;
  int id_encomenda;
  int j;
  int k = 0;
  Encomenda A[200];
  id_encomenda = new_sym_var(sizeof(int) * 8);
  j = prod_encomenda[id_encomenda];
  if (existe_encomenda_produto(id_encomenda, ident_enc) == 1)
  {
    for (i = 0; i < j; i++)
    {
      if (encomendas[id_encomenda][i].prod.quantidade != 0)
      {
        A[k] = encomendas[id_encomenda][i];
        k++;
      }
      else
      {
        
      }

    }

    merge_sort_char(A, 0, k - 1);
    printf("Encomenda %d\n", id_encomenda);
    for (i = 0; i < k; i++)
    {
      printf("* %s %d %d\n", A[i].prod.nome, A[i].prod.preco, A[i].prod.quantidade);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_encomenda);
  }

}

