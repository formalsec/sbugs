/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct produto
{
  char descricao[64];
  int preco;
  int peso;
  int stock;
  int identificador;
} produto;
typedef struct encomenda
{
  int nr_produtos;
  int peso_acum;
  produto prod[200];
} encomenda;
produto produtos[10000];
encomenda encomendas[500];
int a(char descricao[64], int preco, int peso, int qtd, int idp)
{
  produto prod;
  strcpy(prod.descricao, descricao);
  prod.preco = preco;
  prod.peso = peso;
  prod.stock = qtd;
  prod.identificador = idp;
  produtos[idp] = prod;
  printf("Novo produto %d.\n", idp);
  return ++idp;
}

void k(int idpmax)
{
  int i;
  printf("Inventario atual:\n");
  for (i = 0; i < idpmax; i++)
    printf("Descri?ao: %s  Preco:%d  Peso:%d  Qtd:%d\n", produtos[i].descricao, produtos[i].preco, produtos[i].peso, produtos[i].stock);

}

void q(int idpmax, int qtd, int idp)
{
  if (idp >= idpmax)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    produtos[idp].stock += qtd;
  }

}

void init_struct()
{
  int i;
  for (i = 0; i < 500; i++)
  {
    encomendas[i].nr_produtos = 0;
    encomendas[i].peso_acum = 0;
  }

}

void A(int idpmax, int idp, int idemax, int ide, int qtd)
{
  int i;
  produto novo_produto;
  if (ide >= idemax)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idpmax)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (qtd > produtos[idp].stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((encomendas[ide].peso_acum + (qtd * produtos[idp].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          {
            encomendas[ide].peso_acum += qtd * produtos[idp].peso;
            produtos[idp].stock -= qtd;
            for (i = 0; i < encomendas[ide].nr_produtos; i++)
            {
              if (encomendas[ide].prod[i].identificador == produtos[idp].identificador)
              {
                break;
              }
              else
              {
                
              }

            }

            if (i == encomendas[ide].nr_produtos)
            {
              {
                encomendas[ide].prod[i] = produtos[idp];
                encomendas[ide].nr_produtos += 1;
                strcpy(novo_produto.descricao, produtos[idp].descricao);
                novo_produto.preco = produtos[idp].preco;
                novo_produto.peso = produtos[idp].peso;
                novo_produto.stock = qtd;
                novo_produto.identificador = produtos[idp].identificador;
                encomendas[ide].prod[i] = novo_produto;
              }
            }
            else
            {
              encomendas[ide].prod[i].stock += qtd;
            }

          }
        }

      }

    }

  }

}

void r(int idpmax, int qtd, int idp)
{
  if (idp >= idpmax)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (qtd > produtos[idp].stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      produtos[idp].stock -= qtd;
    }

  }

}

void R(int idpmax, int idp, int idemax, int ide)
{
  int i;
  if (ide >= idemax)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idpmax)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      {
        for (i = 0; i < encomendas[ide].nr_produtos; i++)
        {
          if (encomendas[ide].prod[i].identificador == produtos[idp].identificador)
          {
            {
              produtos[idp].stock += encomendas[ide].prod[i].stock;
              encomendas[ide].peso_acum -= encomendas[ide].prod[i].stock * encomendas[ide].prod[i].peso;
              encomendas[ide].nr_produtos -= 1;
              for (; i < encomendas[ide].nr_produtos; i++)
                encomendas[ide].prod[i] = encomendas[ide].prod[i + 1];

            }
          }
          else
          {
            
          }

        }

      }
    }

  }

}

void C(int idemax, int ide)
{
  int i;
  int custototal = 0;
  if (ide >= idemax)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      for (i = 0; i < encomendas[ide].nr_produtos; i++)
        custototal += encomendas[ide].prod[i].stock * encomendas[ide].prod[i].preco;

      printf("Custo da encomenda %d %d.\n", ide, custototal);
    }
  }

}

void p(int idp, int idpmax, int idemax, int preco)
{
  int corre_ide;
  int corre_prod;
  if (idp >= idpmax)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      produtos[idp].preco = preco;
      for (corre_ide = 0; corre_ide < idemax; corre_ide++)
      {
        for (corre_prod = 0; corre_prod < encomendas[corre_ide].nr_produtos; corre_prod++)
        {
          if (encomendas[corre_ide].prod[corre_prod].identificador == produtos[idp].identificador)
          {
            encomendas[corre_ide].prod[corre_prod].preco = preco;
          }
          else
          {
            
          }

        }

      }

    }
  }

}

void E(int idpmax, int idemax, int ide, int idp)
{
  int i;
  int order_stock = 0;
  if (idp >= idpmax)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (ide >= idemax)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
      {
        for (i = 0; i < encomendas[ide].nr_produtos; i++)
        {
          if (encomendas[ide].prod[i].identificador == produtos[idp].identificador)
          {
            {
              order_stock = encomendas[ide].prod[i].stock;
              break;
            }
          }
          else
          {
            
          }

        }

        printf("%s %d.\n", produtos[idp].descricao, order_stock);
      }
    }

  }

}

void m(int idp, int idpmax, int idemax)
{
  int corre_ide;
  int corre_prod;
  int ide = 0;
  int qtd_max = 0;
  if (idp >= idpmax)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    {
      for (corre_ide = 0; corre_ide < idemax; corre_ide++)
      {
        for (corre_prod = 0; corre_prod < encomendas[corre_ide].nr_produtos; corre_prod++)
        {
          if (encomendas[corre_ide].prod[corre_prod].identificador == produtos[idp].identificador)
          {
            {
              if (encomendas[corre_ide].prod[corre_prod].stock > qtd_max)
              {
                {
                  qtd_max = encomendas[corre_ide].prod[corre_prod].stock;
                  ide = corre_ide;
                }
              }
              else
              {
                
              }

            }
          }
          else
          {
            
          }

        }

      }

      if (qtd_max != 0)
      {
        printf("Maximo produto %d %d %d.\n", idp, ide, qtd_max);
      }
      else
      {
        
      }

    }
  }

}

void merge(produto prod[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  produto aux[10000];
  for (i = m + 1; i > left; i--)
    aux[i - 1] = prod[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = prod[j + 1];

  for (k = left; k <= right; k++)
  {
    if ((aux[j].preco < aux[i].preco) || (i > m))
    {
      prod[k] = aux[j--];
    }
    else
    {
      prod[k] = aux[i++];
    }

  }

}

void mergesort(produto prod[], int left, int right)
{
  int m;
  if (left < right)
  {
    m = (left + right) / 2;
  }
  else
  {
    return;
  }

  mergesort(prod, left, m);
  mergesort(prod, m + 1, right);
  merge(prod, left, m, right);
}

void l(int left, int right)
{
  int i;
  produto prod[10000];
  for (i = left; i <= right; i++)
    prod[i] = produtos[i];

  mergesort(prod, left, right);
  printf("Produtos\n");
  for (i = left; i <= right; i++)
    printf("* %s %d %d\n", prod[i].descricao, prod[i].preco, prod[i].stock);

}

void L(int idemax, int ide, int idpmax)
{
  int i;
  if (ide >= idemax)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    {
      printf("Encomenda %d\n", idemax);
      for (i = 0; i <= idpmax; i++)
        printf("* %s %d %d\n", encomendas[ide].prod[i].descricao, encomendas[ide].prod[i].preco, encomendas[ide].prod[i].stock);

    }
  }

}

int main()
{
  char action;
  char descricao[64];
  int preco = 0;
  int peso;
  int qtd;
  int idpmax = 0;
  int idp;
  int idemax = 0;
  int ide;
  init_struct();
  while (1)
  {
    action = new_sym_var(sizeof(char) * 8);
    switch (action)
    {
      case 'a':
        for (int descricao_index = 0; descricao_index < 10; descricao_index++)
      {
        descricao[descricao_index] = new_sym_var(sizeof(char) * 8);
      }

        descricao[10 - 1] = '\0';
        preco = new_sym_var(sizeof(int) * 8);
        peso = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        idpmax = a(descricao, preco, peso, qtd, idpmax);
        break;

      case 'k':
        k(idpmax);
        break;

      case 'q':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        q(idpmax, qtd, idp);
        break;

      case 'N':
        printf("Nova encomenda %d.\n", idemax++);
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        A(idpmax, idp, idemax, ide, qtd);
        break;

      case 'r':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        r(idpmax, qtd, idp);
        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        R(idpmax, idp, idemax, ide);
        break;

      case 'C':
        ide = new_sym_var(sizeof(int) * 8);
        C(idemax, ide);
        break;

      case 'p':
        idp = new_sym_var(sizeof(int) * 8);
        preco = new_sym_var(sizeof(int) * 8);
        p(idp, idpmax, idemax, preco);
        break;

      case 'E':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        E(idpmax, idemax, ide, idp);
        break;

      case 'm':
        idp = new_sym_var(sizeof(int) * 8);
        m(idp, idpmax, idemax);
        break;

      case 'l':
        l(0, idpmax - 1);
        break;

      case 'L':
        L(idemax, ide, idpmax);
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}

