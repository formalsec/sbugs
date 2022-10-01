/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int i;
int j;
int prod_in_order[10000][500];
char command;
char descrition[10000];
int price[10000];
int weight[10000];
int stock[10000];
int idp;
int ide;
int quantity;
int price2;
int order[500];
int new_prod();
int add_stock();
int new_order();
int add_prod();
int rem_stock();
int rem_prod();
int order_cost();
int change_price();
int list_prod();
int list_max_prod();
int list_by_price();
int list_by_descrition();
int main()
{
  char input[200];
  char command;
  do
  {
    for (int input_index = 0; input_index < 10; input_index++)
    {
      input[input_index] = new_sym_var(sizeof(char) * 8);
    }

    input[10 - 1] = '\0';
    command = input[0];
    switch (command)
    {
      case 'a':
        if (i < 10000)
      {
        new_prod();
      }
      else
      {
        
      }

        i++;
        break;

      case 'q':
        add_stock();
        break;

      case 'N':
        if (j < 500)
      {
        new_order();
      }
      else
      {
        
      }

        j++;
        break;

      case 'A':
        add_prod();
        break;

      case 'r':
        rem_stock();
        break;

      case 'R':
        rem_prod();
        break;

      case 'C':
        order_cost();
        break;

      case 'p':
        change_price();
        break;

      case 'E':
        list_prod();
        break;

      case 'm':
        list_max_prod();
        break;

      case 'l':
        list_by_price();
        break;

      case 'L':
        list_by_descrition();
        break;

      case 'x':
        return 0;

    }

  }
  while (strcmp(&command, "x") != 0);
  return 0;
}

int new_prod()
{
  command = new_sym_var(sizeof(char) * 8);
  descrition[i] = new_sym_var(sizeof(char) * 8);
  price[i] = new_sym_var(sizeof(int) * 8);
  weight[i] = new_sym_var(sizeof(int) * 8);
  stock[i] = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", i);
  return 0;
}

int add_stock()
{
  command = new_sym_var(sizeof(char) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  quantity = new_sym_var(sizeof(int) * 8);
  if (idp <= (i - 1))
  {
    stock[idp] = stock[idp] + quantity;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

  return 0;
}

int new_order()
{
  printf("Nova encomenda %d.\n", j);
  order[j] = new_sym_var(sizeof(int) * 8);
  return 0;
}

int add_prod()
{
  command = new_sym_var(sizeof(char) * 8);
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  quantity = new_sym_var(sizeof(int) * 8);
  if (ide <= (j - 1))
  {
    if (idp <= (i - 1))
    {
      if (quantity < stock[idp])
      {
        if ((quantity * weight[idp]) < 200)
        {
          prod_in_order[i][j] = prod_in_order[idp][ide];
        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }

  return 0;
}

int rem_stock()
{
  command = new_sym_var(sizeof(char) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  quantity = new_sym_var(sizeof(int) * 8);
  if (idp <= (i - 1))
  {
    if ((stock[idp] - quantity) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
    }
    else
    {
      stock[idp] = stock[idp] - quantity;
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

  return 0;
}

int rem_prod()
{
  command = new_sym_var(sizeof(char) * 8);
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide <= (j - 1))
  {
    if (idp <= (i - 1))
    {
      price[idp] = (weight[idp] = (stock[idp] = 0));
    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }

  return 0;
}

int order_cost()
{
  command = new_sym_var(sizeof(char) * 8);
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > (j - 1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    
  }

  return 0;
}

int change_price()
{
  command = new_sym_var(sizeof(char) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  price2 = new_sym_var(sizeof(int) * 8);
  if (idp <= (i - 1))
  {
    price[idp] = price2;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

  return 0;
}

int list_prod()
{
  command = new_sym_var(sizeof(char) * 8);
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (j - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    
  }

  if (idp > (i - 1))
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  return 0;
}

int list_max_prod()
{
  command = new_sym_var(sizeof(char) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (idp > (i - 1))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  return 0;
}

int list_by_price()
{
  return 0;
}

int list_by_descrition()
{
  command = new_sym_var(sizeof(char) * 8);
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > (j - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    
  }

  return 0;
}
