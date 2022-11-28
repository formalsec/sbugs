#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int idp;
  char descr[63];
  int preco;
  int peso;
  int qtd;
} Produto;
typedef struct 
{
  Produto stock;
  int ide;
} Encomenda;
static Produto stock[10000];
static Encomenda encomenda[500][200];
static int PesoEncomenda[500];
static int CustoEncomenda[500];
static int prodcont;
static int enccont;
void cria_produto();
void adiciona_stock();
void cria_encomenda();
void adiciona_prod_enc();
void remove_stock_prod();
void remove_prod_enc();
void calcula_custo();
void altera_preco();
void lista_prod_enc();
void max_produto();
void listar_alfa();
void um_produto(int j);
int main()
{
  char opcao;
  do
  {
    opcao = new_sym_var(sizeof(char) * 8);
    switch (opcao)
    {
      case 'a':
        cria_produto();
        break;

      case 'q':
        adiciona_stock();
        break;

      case 'N':
        cria_encomenda();
        break;

      case 'A':
        adiciona_prod_enc();
        break;

      case 'r':
        remove_stock_prod();
        break;

      case 'R':
        remove_prod_enc();
        break;

      case 'C':
        calcula_custo();
        break;

      case 'p':
        altera_preco();
        break;

      case 'E':
        lista_prod_enc();
        break;

      case 'm':
        max_produto();
        break;

      case 'l':
        printf("Opcao l");
        break;

      case 'L':
        listar_alfa();
        break;

      case 'x':
        break;

    }

  }
  while (opcao != 'x');
  return 0;
}

void cria_produto()
{
  if (prodcont < 10000)
  {
    for (int stock_index = 0; stock_index < 10; stock_index++)
    {
      stock[prodcont].descr[stock_index] = new_sym_var(sizeof(char) * 8);
    }

    stock[prodcont].descr[10 - 1] = '\0';
    stock[prodcont].preco = new_sym_var(sizeof(int) * 8);
    stock[prodcont].peso = new_sym_var(sizeof(int) * 8);
    stock[prodcont].qtd = new_sym_var(sizeof(int) * 8);
    stock[prodcont].idp = prodcont;
    printf("Novo produto %d.\n", stock[prodcont].idp);
    prodcont++;
  }
  else
  {
    
  }

}

void adiciona_stock()
{
  int k;
  int quantidade;
  stock[prodcont].idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  k = stock[prodcont].idp;
  if (k < prodcont)
  {
    stock[k].qtd = stock[k].qtd + quantidade;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", k);
  }

}

void cria_encomenda()
{
  if (enccont < 500)
  {
    encomenda[enccont][prodcont].ide = enccont;
    PesoEncomenda[enccont] = 0;
    printf("Nova encomenda %d.\n", encomenda[enccont][prodcont].ide);
    enccont++;
  }
  else
  {
    
  }

}

void adiciona_prod_enc()
{
  int i;
  int j;
  int quantidade;
  encomenda[enccont][prodcont].ide = new_sym_var(sizeof(int) * 8);
  stock[prodcont].idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  i = encomenda[enccont][prodcont].ide;
  j = stock[prodcont].idp;
  if (i < enccont)
  {
    if (j < prodcont)
    {
      if (quantidade <= stock[j].qtd)
      {
        if ((PesoEncomenda[i] + (stock[j].peso * quantidade)) <= 200)
        {
          PesoEncomenda[i] = PesoEncomenda[i] + (stock[j].peso * quantidade);
          CustoEncomenda[i] = CustoEncomenda[i] + (stock[j].preco * quantidade);
          strcpy(encomenda[i][j].stock.descr, stock[j].descr);
          encomenda[i][j].stock.preco = stock[j].preco;
          encomenda[i][j].stock.qtd = encomenda[i][j].stock.qtd + quantidade;
          stock[j].qtd = stock[j].qtd - quantidade;
        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", j, i);
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", j, i);
      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", j, i);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", j, i);
  }

}

void remove_stock_prod()
{
  int k;
  int quantidade;
  stock[prodcont].idp = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  k = stock[prodcont].idp;
  if (k < prodcont)
  {
    if (quantidade <= stock[k].qtd)
    {
      stock[k].qtd = stock[k].qtd - quantidade;
    }
    else
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, k);
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", k);
  }

}

void remove_prod_enc()
{
  int i;
  int j;
  encomenda[enccont][prodcont].ide = new_sym_var(sizeof(int) * 8);
  stock[prodcont].idp = new_sym_var(sizeof(int) * 8);
  i = encomenda[enccont][prodcont].ide;
  j = stock[prodcont].idp;
  if (i < enccont)
  {
    if (j < prodcont)
    {
      PesoEncomenda[i] = PesoEncomenda[i] - (stock[j].peso * encomenda[i][j].stock.qtd);
      CustoEncomenda[i] = CustoEncomenda[i] - (stock[j].preco * encomenda[i][j].stock.qtd);
      strcpy(encomenda[i][j].stock.descr, stock[j].descr);
      encomenda[i][j].stock.preco = stock[j].preco;
      stock[j].qtd = stock[j].qtd + encomenda[i][j].stock.qtd;
      encomenda[i][j].stock.qtd = 0;
    }
    else
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", j, i);
    }

  }
  else
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", j, i);
  }

}

void calcula_custo()
{
  int i;
  encomenda[enccont][prodcont].ide = new_sym_var(sizeof(int) * 8);
  i = encomenda[enccont][prodcont].ide;
  if (i < enccont)
  {
    printf("Custo da encomenda %d %d.\n", i, CustoEncomenda[i]);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", i);
  }

}

void altera_preco()
{
  int j;
  int i;
  int novopreco;
  stock[prodcont].idp = new_sym_var(sizeof(int) * 8);
  novopreco = new_sym_var(sizeof(int) * 8);
  j = stock[prodcont].idp;
  i = encomenda[enccont][prodcont].ide;
  if (j < prodcont)
  {
    CustoEncomenda[i] = CustoEncomenda[i] - (stock[j].preco * encomenda[i][j].stock.qtd);
    stock[j].preco = novopreco;
    CustoEncomenda[i] = CustoEncomenda[i] + (stock[j].preco * encomenda[i][j].stock.qtd);
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", j);
  }

}

void lista_prod_enc()
{
  int i;
  int j;
  encomenda[enccont][prodcont].ide = new_sym_var(sizeof(int) * 8);
  stock[prodcont].idp = new_sym_var(sizeof(int) * 8);
  i = encomenda[enccont][prodcont].ide;
  j = stock[prodcont].idp;
  if (i < enccont)
  {
    if (j < prodcont)
    {
      printf("%s %d.\n", encomenda[i][j].stock.descr, encomenda[i][j].stock.qtd);
    }
    else
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", j);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i);
  }

}

void max_produto()
{
  int i;
  int j;
  int max;
  int k;
  stock[prodcont].idp = new_sym_var(sizeof(int) * 8);
  i = encomenda[enccont][prodcont].ide;
  j = stock[prodcont].idp;
  max = 0;
  k = 0;
  if (j >= prodcont)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", j);
  }
  else
  {
    for (i = 0; i < enccont; i++)
    {
      if (encomenda[i][j].stock.qtd > max)
      {
        max = encomenda[i][j].stock.qtd;
        k = i;
      }
      else
      {
        
      }

    }

    if (encomenda[k][j].stock.qtd != 0)
    {
      printf("Maximo produto %d %d %d.\n", j, k, max);
    }
    else
    {
      
    }

  }

}

void listar_alfa()
{
  int i;
  int j;
  encomenda[enccont][prodcont].ide = new_sym_var(sizeof(int) * 8);
  j = stock[prodcont].idp;
  i = encomenda[enccont][prodcont].ide;
  if (i < enccont)
  {
    printf("Encomenda %d\n", i);
    if (encomenda[i][j].stock.qtd != 0)
    {
      for (j = 0; j < prodcont; j++)
      {
        um_produto(j);
        printf("\n");
      }

    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", i);
  }

}

void um_produto(int j)
{
  int i;
  i = encomenda[enccont][prodcont].ide;
  if ((j >= 0) && (j < prodcont))
  {
    printf("* %s %d %d", encomenda[i][j].stock.descr, encomenda[i][j].stock.preco, encomenda[i][j].stock.qtd);
  }
  else
  {
    
  }

}
