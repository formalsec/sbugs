/*File generated by PreProcessor.py*/


#include <stdio.h>
#include "products.h"
#include "misc.h"
#include <string.h>


Product stock[10000] = {0};
void get_desc(char string[])
{
  int position = 0;
  int character = getchar();
  while ((character != ':') && (position < (64 - 1)))
  {
    string[position] = character;
    position++;
    character = getchar();
  }

  string[position] = '\0';
}

void new_product()
{
  static int id = 0;
  char description[64];
  int price;
  int weight;
  int quantity;
  Product prod;
  getchar();
  get_desc(description);
  price = new_sym_var(sizeof(int) * 8);
  weight = new_sym_var(sizeof(int) * 8);
  quantity = new_sym_var(sizeof(int) * 8);
  strcpy(prod.description, description);
  prod.price = price;
  prod.weight = weight;
  prod.quantity = quantity;
  prod.id = id;
  stock[id] = prod;
  printf("Novo produto %d.\n", id);
  id++;
}

int prod_exists(int id)
{
  if (((id >= 0) && (id < 10000)) && (strlen(stock[id].description) != 0))
  {
    {
      return 1;
    }
  }
  else
  {
    
  }

  return 0;
}

void add_stock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (prod_exists(idp))
  {
    {
      stock[idp].quantity += qtd;
    }
  }
  else
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
  }

}

void remove_stock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (prod_exists(idp))
  {
    {
      if (stock[idp].quantity < qtd)
      {
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
      }
      else
      {
        {
          stock[idp].quantity -= qtd;
        }
      }

    }
  }
  else
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
  }

}

void change_price()
{
  int idp;
  int price;
  idp = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if (prod_exists(idp))
  {
    {
      stock[idp].price = price;
    }
  }
  else
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }

}

void sort_products()
{
  int i;
  int j;
  Product stock_copy[10000];
  memcpy(stock_copy, stock, sizeof(stock));
  for (j = 0; j < 10000; j++)
  {
    if (!prod_exists(j))
    {
      {
        break;
      }
    }
    else
    {
      
    }

  }

  price_sort(stock_copy, 0, j - 1);
  printf("Produtos\n");
  for (i = 0; i < j; i++)
  {
    printf("* %s %d %d\n", stock_copy[i].description, stock_copy[i].price, stock_copy[i].quantity);
  }

}
