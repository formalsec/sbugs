#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct produto
{
  int idp;
  char descricao[64];
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct encomenda
{
  int ide;
  int conta_prod_enc;
  produto prod[200];
} encomenda;
void init_inventario_prod();
void init_inventario_enc();
encomenda init_enc();
void adiciona_stock(int idp, int qtd);
void adiciona_prod_enc(int ide, int idp, int qtd);
int peso_enc(encomenda enc);
void remove_stock_prod(int idp, int qtd);
void remove_prod_enc(int ide, int idp);
void custo_enc(int ide);
void altera_preco(int idp, int preco);
void lista_descricao_qtd(int ide, int idp);
void maior_quantidade(int idp);
void ordena_prods();
void ordena_prods_enc(int ide);
void mergeSort(produto arr[], int l, int r, int valor);
void merge(produto arr[], int l, int m, int r, int valor);
produto inventario_prod[10000];
produto inventario_prod_ord[10000];
encomenda inventario_enc[500];
int conta_prod = 0;
int conta_enc = 0;
int main()
{
  int comando;
  int idp;
  int qtd;
  int ide;
  int preco;
  produto prod;
  encomenda enc;
  init_inventario_prod();
  init_inventario_enc();
  while ((comando = getchar()) != EOF)
  {
    switch (comando)
    {
      case 'a':
        prod.idp = conta_prod;
        conta_prod++;
        for (int prod_index = 0; prod_index < 10; prod_index++)
      {
        prod.descricao[prod_index] = new_sym_var(sizeof(char) * 8);
      }

        prod.descricao[10 - 1] = '\0';
        prod.preco = new_sym_var(sizeof(int) * 8);
        prod.peso = new_sym_var(sizeof(int) * 8);
        prod.qtd = new_sym_var(sizeof(int) * 8);
        inventario_prod[prod.idp] = prod;
        printf("Novo produto %d.\n", prod.idp);
        break;

      case 'q':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        adiciona_stock(idp, qtd);
        break;

      case 'N':
        enc = init_enc();
        inventario_enc[enc.ide] = enc;
        conta_enc++;
        printf("Nova encomenda %d.\n", enc.ide);
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        adiciona_prod_enc(ide, idp, qtd);
        break;

      case 'r':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        remove_stock_prod(idp, qtd);
        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        remove_prod_enc(ide, idp);
        break;

      case 'C':
        ide = new_sym_var(sizeof(int) * 8);
        custo_enc(ide);
        break;

      case 'p':
        idp = new_sym_var(sizeof(int) * 8);
        preco = new_sym_var(sizeof(int) * 8);
        altera_preco(idp, preco);
        break;

      case 'E':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        lista_descricao_qtd(ide, idp);
        break;

      case 'm':
        idp = new_sym_var(sizeof(int) * 8);
        maior_quantidade(idp);
        break;

      case 'l':
        ordena_prods();
        break;

      case 'L':
        ide = new_sym_var(sizeof(int) * 8);
        ordena_prods_enc(ide);
        break;

      case 'x':
        return 0;

      default:
        fprintf(stderr, "Invalid input!\n");
        return 1;

    }

    getchar();
  }

  return 0;
}

void init_inventario_prod()
{
  int i;
  for (i = 0; i < 10000; i++)
  {
    inventario_prod[i].idp = -1;
  }

}

void init_inventario_enc()
{
  int i;
  for (i = 0; i < 500; i++)
  {
    inventario_enc[i].ide = -1;
  }

}

encomenda init_enc()
{
  encomenda enc;
  int i;
  enc.ide = conta_enc;
  enc.conta_prod_enc = 0;
  for (i = 0; i < 200; i++)
  {
    enc.prod[i].idp = -1;
  }

  return enc;
}

void adiciona_stock(int idp, int qtd)
{
  if (inventario_prod[idp].idp == idp)
  {
    inventario_prod[idp].qtd += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void adiciona_prod_enc(int ide, int idp, int qtd)
{
  if (inventario_enc[ide].ide == (-1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (inventario_prod[idp].idp == (-1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (inventario_prod[idp].qtd < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((peso_enc(inventario_enc[ide]) + (inventario_prod[idp].peso * qtd)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          int i;
          int index_enc_prod;
          for (i = 0; i < inventario_enc[ide].conta_prod_enc; i++)
          {
            if (inventario_enc[ide].prod[i].idp == idp)
            {
              inventario_enc[ide].prod[i].qtd += qtd;
              inventario_prod[idp].qtd -= qtd;
              return;
            }
            else
            {
              
            }

          }

          index_enc_prod = inventario_enc[ide].conta_prod_enc;
          inventario_enc[ide].prod[index_enc_prod] = inventario_prod[idp];
          inventario_enc[ide].conta_prod_enc++;
          inventario_prod[idp].qtd -= qtd;
          inventario_enc[ide].prod[index_enc_prod].qtd = qtd;
          return;
        }

      }

    }

  }

}

int peso_enc(encomenda enc)
{
  int i = 0;
  int peso_t = 0;
  for (i = 0; i < enc.conta_prod_enc; i++)
  {
    peso_t += inventario_enc[enc.ide].prod[i].peso * inventario_enc[enc.ide].prod[i].qtd;
  }

  return peso_t;
}

void remove_stock_prod(int idp, int qtd)
{
  if (inventario_prod[idp].idp == (-1))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (inventario_prod[idp].qtd < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      inventario_prod[idp].qtd -= qtd;
    }

  }

}

void remove_prod_enc(int ide, int idp)
{
  if (inventario_enc[ide].ide == (-1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (inventario_prod[idp].idp == (-1))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      int i;
      int j;
      for (i = 0; i < inventario_enc[ide].conta_prod_enc; i++)
      {
        if (inventario_enc[ide].prod[i].idp == idp)
        {
          inventario_prod[idp].qtd += inventario_enc[ide].prod[i].qtd;
          for (j = i; j < inventario_enc[ide].conta_prod_enc; j++)
          {
            inventario_enc[ide].prod[j] = inventario_enc[ide].prod[j + 1];
          }

          inventario_enc[ide].conta_prod_enc--;
          return;
        }
        else
        {
          
        }

      }

    }

  }

}

void custo_enc(int ide)
{
  if (inventario_enc[ide].ide == (-1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    int i;
    int custo = 0;
    for (i = 0; i < inventario_enc[ide].conta_prod_enc; i++)
    {
      custo += inventario_enc[ide].prod[i].preco * inventario_enc[ide].prod[i].qtd;
    }

    printf("Custo da encomenda %d %d.\n", ide, custo);
  }

}

void altera_preco(int idp, int preco)
{
  if (inventario_prod[idp].idp == (-1))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    int i;
    int j;
    inventario_prod[idp].preco = preco;
    for (i = 0; i < conta_enc; i++)
    {
      for (j = 0; j < inventario_enc[i].conta_prod_enc; j++)
      {
        if (inventario_enc[i].prod[j].idp == idp)
        {
          inventario_enc[i].prod[j].preco = preco;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void lista_descricao_qtd(int ide, int idp)
{
  if (inventario_enc[ide].ide == (-1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (inventario_prod[idp].idp == (-1))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      int i;
      for (i = 0; i < inventario_enc[ide].conta_prod_enc; i++)
      {
        if (inventario_enc[ide].prod[i].idp == idp)
        {
          printf("%s %d.\n", inventario_enc[ide].prod[i].descricao, inventario_enc[ide].prod[i].qtd);
          return;
        }
        else
        {
          
        }

      }

      printf("%s 0.\n", inventario_prod[idp].descricao);
    }

  }

}

void maior_quantidade(int idp)
{
  int maior = 0;
  int ide;
  int i;
  int j;
  int afirmativo = 0;
  if (inventario_prod[idp].idp == (-1))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < conta_enc; i++)
    {
      for (j = 0; j < inventario_enc[i].conta_prod_enc; j++)
      {
        if ((inventario_enc[i].prod[j].idp == idp) && (inventario_enc[i].prod[j].qtd > maior))
        {
          maior = inventario_enc[i].prod[j].qtd;
          ide = i;
          afirmativo = 1;
        }
        else
        {
          
        }

        if (((inventario_enc[i].prod[j].idp == idp) && (inventario_enc[i].prod[j].qtd == maior)) && (i <= ide))
        {
          ide = i;
          afirmativo = 1;
        }
        else
        {
          
        }

      }

    }

    if (afirmativo == 1)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, maior);
    }
    else
    {
      
    }

  }

}

void ordena_prods()
{
  produto produtos[10000];
  produto prod;
  int i;
  for (i = 0; i < conta_prod; i++)
  {
    produtos[i] = inventario_prod[i];
  }

  mergeSort(produtos, 0, conta_prod - 1, 0);
  printf("Produtos\n");
  for (i = 0; i < conta_prod; i++)
  {
    prod = produtos[i];
    printf("* %s %d %d\n", prod.descricao, prod.preco, prod.qtd);
  }

}

void ordena_prods_enc(int ide)
{
  if (inventario_enc[ide].ide == (-1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    produto prods_enc[200];
    produto prod;
    int i;
    int j = 0;
    for (j = 0; j < inventario_enc[ide].conta_prod_enc; j++)
    {
      prods_enc[j] = inventario_enc[ide].prod[j];
    }

    mergeSort(prods_enc, 0, inventario_enc[ide].conta_prod_enc - 1, 1);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < inventario_enc[ide].conta_prod_enc; i++)
    {
      prod = prods_enc[i];
      printf("* %s %d %d\n", prod.descricao, prod.preco, prod.qtd);
    }

  }

}

void mergeSort(produto arr[], int l, int r, int valor)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort(arr, l, m, valor);
    mergeSort(arr, m + 1, r, valor);
    merge(arr, l, m, r, valor);
  }
  else
  {
    
  }

}

void merge(produto arr[], int l, int m, int r, int valor)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  produto L[10000];
  produto R[10000];
  for (i = 0; i < n1; i++)
  {
    L[i] = arr[l + i];
  }

  for (j = 0; j < n2; j++)
  {
    R[j] = arr[(m + 1) + j];
  }

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if ((L[i].preco <= R[j].preco) && (valor == 0))
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      if ((strcmp(L[i].descricao, R[j].descricao) <= 0) && (valor == 1))
      {
        arr[k] = L[i];
        i++;
      }
      else
      {
        arr[k] = R[j];
        j++;
      }

    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

}

