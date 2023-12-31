#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct 
{
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
  int idp;
} produto;
typedef struct 
{
  int ide;
  produto prod[150];
  int peso_total;
} encomenda;
void Le_novo_produto(produto list_prod[], int idp)
{
  list_prod[idp].idp = idp;
  for (int list_prod_index = 0; list_prod_index < 10; list_prod_index++)
  {
    list_prod[list_prod[idp].idp].descricao[list_prod_index] = new_sym_var(sizeof(char) * 8);
  }

  list_prod[list_prod[idp].idp].descricao[10 - 1] = '\0';
  list_prod[list_prod[idp].idp].preco = new_sym_var(sizeof(int) * 8);
  list_prod[list_prod[idp].idp].peso = new_sym_var(sizeof(int) * 8);
  list_prod[list_prod[idp].idp].quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
}

void Adiciona_stock(produto list_prod[], int idp_O)
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp > (idp_O - 1))
  {
    printf("Impossivel adicionar %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    list_prod[list_prod[idp].idp].quantidade += qtd;
  }

}

void Cria_encomenda(encomenda list_enc[], int ide)
{
  int i;
  list_enc[ide].ide = ide;
  list_enc[ide].peso_total = 0;
  for (i = 0; i < 200; i++)
  {
    strcpy(list_enc[ide].prod[i].descricao, "");
    list_enc[ide].prod[i].preco = 0;
    list_enc[ide].prod[i].peso = 0;
    list_enc[ide].prod[i].quantidade = 0;
    list_enc[ide].prod[i].idp = -1;
  }

  printf("Nova encomenda %d.\n", ide);
}

void Adiciona_prod_enc(produto list_prod[], encomenda list_enc[], int idp_O, int ide_O, char enc)
{
  int ide;
  int idp;
  int qtd;
  int i;
  int n = 0;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((ide > (ide_O - 1)) || (enc != 's'))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp > (idp_O - 1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if ((list_prod[idp].quantidade - qtd) < 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((list_enc[ide].peso_total + (qtd * list_prod[idp].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          for (i = 0; i < 150; i++)
          {
            if (list_enc[ide].prod[i].idp == idp)
            {
              list_enc[ide].prod[i].quantidade += qtd;
              list_enc[ide].peso_total += list_prod[i].peso * qtd;
              list_prod[idp].quantidade -= qtd;
              n = 1;
              break;
            }
            else
            {
              
            }

          }

          if (n != 1)
          {
            strcpy(list_enc[ide].prod[list_enc[ide].ide].descricao, list_prod[idp].descricao);
            list_enc[ide].prod[list_enc[ide].ide].peso = list_prod[idp].peso;
            list_enc[ide].prod[list_enc[ide].ide].preco = list_prod[idp].preco;
            list_enc[ide].prod[list_enc[ide].ide].quantidade = qtd;
            list_enc[ide].prod[list_enc[ide].ide].idp = list_prod[idp].idp;
            list_enc[ide].peso_total += list_prod[idp].peso * qtd;
            list_prod[idp].quantidade -= qtd;
            list_enc[ide].ide += 1;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void Remove_stock(produto list_prod[], int idp_O)
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp > (idp_O - 1))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((list_prod[list_prod[idp].idp].quantidade - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      list_prod[list_prod[idp].idp].quantidade -= qtd;
    }

  }

}

void Remove_prod_enc(encomenda list_enc[], produto list_prod[], int idp_O, int ide_O)
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (ide_O - 1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp > (idp_O - 1))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      for (i = 0; i < 150; i++)
      {
        if (list_enc[ide].prod[i].idp == idp)
        {
          list_prod[list_prod[idp].idp].quantidade += list_enc[ide].prod[i].quantidade;
          list_enc[ide].prod[i].quantidade = 0;
        }
        else
        {
          
        }

      }

    }

  }

}

void Calcula_custo_enc(encomenda list_enc[], int ide_O)
{
  int ide;
  int i;
  int preco_total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > (ide_O - 1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < 150; i++)
    {
      preco_total += list_enc[ide].prod[i].preco * list_enc[ide].prod[i].quantidade;
    }

    printf("Custo da encomenda %d %d.\n", ide, preco_total);
  }

}

void Altera_preco(encomenda list_enc[], produto list_prod[], int idp_O)
{
  int idp;
  int preco;
  int a;
  int e;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp > (idp_O - 1))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < idp_O; i++)
    {
      if (list_prod[i].idp == idp)
      {
        list_prod[i].preco = preco;
      }
      else
      {
        
      }

    }

    for (e = 0; e < 500; e++)
    {
      for (a = 0; a < 150; a++)
      {
        if (list_enc[e].prod[a].idp == idp)
        {
          list_enc[e].prod[a].preco = preco;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void Lista_des_qtd(encomenda list_enc[], int ide_O, int idp_O)
{
  int ide;
  int idp;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (ide_O - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp > (idp_O - 1))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      for (i = 0; i < 150; i++)
      {
        if (list_enc[ide].prod[list_enc[i].ide].idp == idp)
        {
          printf("%s %d.\n", list_enc[ide].prod[list_enc[i].ide].descricao, list_enc[ide].prod[list_enc[i].ide].quantidade);
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void Lista_id_enc(encomenda list_enc[], int idp_O)
{
  int idp;
  int i;
  int e;
  int enc = 0;
  int maximo = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp > (idp_O - 1))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < 500; i++)
    {
      for (e = 0; e < 150; e++)
      {
        if (list_enc[i].prod[list_enc[e].ide].idp == idp)
        {
          if (list_enc[i].prod[list_enc[e].ide].quantidade > maximo)
          {
            maximo = list_enc[i].prod[list_enc[e].ide].quantidade;
            enc = i;
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

    printf("Maximo produto %d %d %d.\n", idp, enc, maximo);
  }

}

int main()
{
  char comando;
  char enc = ' ';
  int idp = 0;
  int ide = 0;
  int i;
  produto list_prod[10000];
  encomenda list_enc[500];
  for (i = 0; i < 10000; i++)
  {
    strcpy(list_prod[i].descricao, "");
    list_prod[i].preco = 0;
    list_prod[i].peso = 0;
    list_prod[i].quantidade = 0;
  }

  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        Le_novo_produto(list_prod, idp);
        idp += 1;
        break;

      case 'q':
        Adiciona_stock(list_prod, idp);
        break;

      case 'N':
        Cria_encomenda(list_enc, ide);
        enc = 's';
        ide += 1;
        break;

      case 'A':
        Adiciona_prod_enc(list_prod, list_enc, idp, ide, enc);
        break;

      case 'r':
        Remove_stock(list_prod, idp);
        break;

      case 'R':
        Remove_prod_enc(list_enc, list_prod, idp, ide);
        break;

      case 'C':
        Calcula_custo_enc(list_enc, ide);
        break;

      case 'p':
        Altera_preco(list_enc, list_prod, idp);
        break;

      case 'E':
        Lista_des_qtd(list_enc, ide, idp);
        break;

      case 'm':
        Lista_id_enc(list_enc, idp);
        break;

      default:
        break;

    }

  }

  return 0;
}

