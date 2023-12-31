#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct produto
{
  int idp;
  char descricao[63];
  int preco;
  int peso;
  int qtd;
};
struct produto produtos[10000];
int indice_produto_atual;
struct encomenda
{
  int ide;
  struct produto prod;
};
struct encomenda encomendas[500][200];
int indice_encomenda_atual;
void inicializar_encomendas()
{
  int a;
  int b;
  for (a = 0; a < 500; a++)
  {
    for (b = 0; b < 200; b++)
    {
      encomendas[a][b].ide = -5;
    }

  }

}

void comando_a()
{
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[indice_produto_atual].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[indice_produto_atual].descricao[10 - 1] = '\0';
  produtos[indice_produto_atual].preco = new_sym_var(sizeof(int) * 8);
  produtos[indice_produto_atual].peso = new_sym_var(sizeof(int) * 8);
  produtos[indice_produto_atual].qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", indice_produto_atual);
  indice_produto_atual++;
}

void comando_q()
{
  int indice_aux;
  int qtd;
  indice_aux = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (strcmp(produtos[indice_aux].descricao, "") == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", indice_aux);
  }
  else
  {
    produtos[indice_aux].qtd += qtd;
  }

}

void comando_N()
{
  int i;
  for (i = 0; i < 200; i++)
  {
    encomendas[indice_encomenda_atual][i].ide = indice_encomenda_atual;
  }

  printf("Nova encomenda %d.\n", indice_encomenda_atual);
  indice_encomenda_atual++;
}

void comando_A()
{
  int ide;
  int idp;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide][0].ide == (-5))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (strcmp(produtos[idp].descricao, "") == 0)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (qtd > produtos[idp].qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        
      }

    }

  }

}

void comando_r()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (strcmp(produtos[idp].descricao, "") == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (qtd > produtos[idp].qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, qtd);
    }
    else
    {
      
    }

  }

  produtos[idp].qtd -= qtd;
}

void comando_R()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide][0].ide == (-5))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (strcmp(produtos[idp].descricao, "") == 0)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      
    }

  }

}

void comando_C()
{
  int ide;
  int i;
  int custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide][0].ide == (-5))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    
  }

  for (i = 0; i < 200; i++)
  {
    custo += encomendas[ide][i].prod.preco * encomendas[ide][i].prod.qtd;
  }

  printf("Custo da encomenda %d %d.\n", ide, custo);
}

void comando_p()
{
  int idp;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (strcmp(produtos[idp].descricao, "") == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  produtos[idp].preco = preco;
}

void comando_E()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (encomendas[ide][0].ide == (-5))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (strcmp(produtos[idp].descricao, "") == 0)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      
    }

  }

}

void comando_m()
{
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  if (strcmp(produtos[idp].descricao, "") == 0)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

}

void comando_l()
{
}

void comando_L()
{
}

int main()
{
  int c;
  inicializar_encomendas();
  c = getchar();
  while (c != EOF)
  {
    switch (c)
    {
      case 'a':
        comando_a();
        break;

      case 'q':
        comando_q();
        break;

      case 'N':
        comando_N();
        break;

      case 'A':
        comando_A();
        break;

      case 'r':
        comando_r();
        break;

      case 'R':
        comando_R();
        break;

      case 'C':
        comando_C();
        break;

      case 'p':
        comando_p();
        break;

      case 'E':
        comando_E();
        break;

      case 'm':
        comando_m();
        break;

      case 'l':
        comando_l();
        break;

      case 'L':
        comando_L();
        break;

      case 'x':
        exit(0);

    }

    c = getchar();
  }

  return 0;
}

