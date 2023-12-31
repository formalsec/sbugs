#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char command[100];
int price = 0;
int weight = 0;
int quantity = 0;
int idp = 0;
int ido = 0;
int empty_spot_products_table = 0;
int empty_spot_orders_table = 0;
int i = 0;
int j = 0;
int product_found = -1;
struct product
{
  int idp;
  char description[64];
  int price;
  int weight;
  int quantity;
};
typedef struct product product;
struct order
{
  int ido;
  int empty_spot_products_on_orders_table;
  int total_weight;
  int total_price;
  product products_in_order[200];
};
typedef struct order order;
product products_table[10000];
order orders_table[500];
void a()
{
  products_table[empty_spot_products_table].idp = empty_spot_products_table;
  strcpy(products_table[empty_spot_products_table].description, strtok(0, ":"));
  products_table[empty_spot_products_table].price = atoi(strtok(0, ":"));
  products_table[empty_spot_products_table].weight = atoi(strtok(0, ":"));
  products_table[empty_spot_products_table].quantity = atoi(strtok(0, ":"));
  printf("Novo produto %d.\n", products_table[empty_spot_products_table].idp);
  empty_spot_products_table++;
}

void q()
{
  idp = atoi(strtok(0, ":"));
  quantity = atoi(strtok(0, ":"));
  if (products_table[idp].price == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  products_table[idp].quantity += quantity;
}

void N()
{
  printf("Nova encomenda %d.\n", empty_spot_orders_table);
  orders_table[empty_spot_orders_table].products_in_order[0].idp = -1;
  empty_spot_orders_table++;
}

int search_product(int product, int order)
{
  for (i = 0; (i < orders_table[order].empty_spot_products_on_orders_table) && (i < 200); i++)
  {
    if ((orders_table[order].products_in_order[i].idp == product) && (orders_table[order].products_in_order[i].price != 0))
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void A()
{
  int possible_weight;
  ido = atoi(strtok(0, ":"));
  idp = atoi(strtok(0, ":"));
  quantity = atoi(strtok(0, ":"));
  if (ido < empty_spot_orders_table)
  {
    if (idp < empty_spot_products_table)
    {
      if (quantity <= products_table[idp].quantity)
      {
        possible_weight = orders_table[ido].total_weight;
        possible_weight += quantity * products_table[idp].weight;
        if (possible_weight <= 200)
        {
          product_found = search_product(idp, ido);
          if (product_found != (-1))
          {
            orders_table[ido].products_in_order[product_found].quantity += quantity;
            products_table[idp].quantity -= quantity;
            orders_table[ido].total_weight += quantity * orders_table[ido].products_in_order[product_found].weight;
            orders_table[ido].total_price += quantity * orders_table[ido].products_in_order[product_found].price;
          }
          else
          {
            orders_table[ido].products_in_order[orders_table[ido].empty_spot_products_on_orders_table] = products_table[idp];
            orders_table[ido].products_in_order[orders_table[ido].empty_spot_products_on_orders_table].quantity = quantity;
            products_table[idp].quantity -= quantity;
            orders_table[ido].total_weight += quantity * products_table[idp].weight;
            orders_table[ido].total_price += quantity * products_table[idp].price;
            orders_table[ido].empty_spot_products_on_orders_table++;
          }

        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ido);
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ido);
      }

    }
    else
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
    }

  }
  else
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
  }

}

void r()
{
  idp = atoi(strtok(0, ":"));
  quantity = atoi(strtok(0, ":"));
  if (idp < empty_spot_products_table)
  {
    if ((products_table[idp].quantity - quantity) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
    }
    else
    {
      products_table[idp].quantity -= quantity;
    }

  }
  else
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }

}

void clean_blank_line(int line)
{
  for (; (line < (orders_table[ido].empty_spot_products_on_orders_table - 1)) && (line < (200 - 1)); line++)
  {
    orders_table[ido].products_in_order[line] = orders_table[ido].products_in_order[line + 1];
  }

  orders_table[ido].empty_spot_products_on_orders_table--;
  strcpy(orders_table[ido].products_in_order[line].description, "");
  orders_table[ido].products_in_order[line].idp = -1;
  orders_table[ido].products_in_order[line].price = 0;
  orders_table[ido].products_in_order[line].weight = 0;
  orders_table[ido].products_in_order[line].quantity = 0;
}

void R()
{
  ido = atoi(strtok(0, ":"));
  idp = atoi(strtok(0, ":"));
  if (ido < empty_spot_orders_table)
  {
    if (idp < empty_spot_products_table)
    {
      product_found = search_product(idp, ido);
      if (product_found != (-1))
      {
        products_table[idp].quantity += orders_table[ido].products_in_order[i].quantity;
        orders_table[ido].total_weight -= orders_table[ido].products_in_order[i].quantity * orders_table[ido].products_in_order[product_found].weight;
        orders_table[ido].total_price -= orders_table[ido].products_in_order[i].quantity * orders_table[ido].products_in_order[product_found].price;
        clean_blank_line(product_found);
      }
      else
      {
        
      }

    }
    else
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
    }

  }
  else
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
  }

}

void C()
{
  ido = atoi(strtok(0, ":"));
  if (ido < empty_spot_orders_table)
  {
    printf("Custo da encomenda %d %d.\n", ido, orders_table[ido].total_price);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ido);
  }

}

void p()
{
  int order;
  idp = atoi(strtok(0, ":"));
  price = atoi(strtok(0, ":"));
  if (idp < empty_spot_products_table)
  {
    products_table[idp].price = price;
    for (order = 0; (order < empty_spot_orders_table) && (order < 500); order++)
    {
      product_found = search_product(idp, order);
      if (product_found != (-1))
      {
        orders_table[order].total_price = orders_table[order].total_price - (orders_table[order].products_in_order[product_found].price * orders_table[order].products_in_order[product_found].quantity);
        orders_table[order].products_in_order[product_found].price = price;
        orders_table[order].total_price += orders_table[order].products_in_order[product_found].price * orders_table[order].products_in_order[product_found].quantity;
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }

}

void E()
{
  ido = atoi(strtok(0, ":"));
  idp = atoi(strtok(0, ":"));
  if (idp < empty_spot_products_table)
  {
    if (ido < empty_spot_orders_table)
    {
      product_found = search_product(idp, ido);
      if (product_found != (-1))
      {
        printf("%s %d.\n", orders_table[ido].products_in_order[product_found].description, orders_table[ido].products_in_order[product_found].quantity);
      }
      else
      {
        printf("%s 0.\n", products_table[idp].description);
      }

    }
    else
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
    }

  }
  else
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }

}

void m()
{
  int max_ido = -1;
  int max_quantity = -1;
  int order = 0;
  idp = atoi(strtok(0, ":"));
  if (idp < empty_spot_products_table)
  {
    for (order = 0; (order < empty_spot_orders_table) && (order < 500); order++)
    {
      product_found = search_product(idp, order);
      if ((product_found != (-1)) && (orders_table[order].products_in_order[product_found].quantity > max_quantity))
      {
        max_quantity = orders_table[order].products_in_order[product_found].quantity;
        max_ido = order;
      }
      else
      {
        
      }

    }

    if (max_ido != (-1))
    {
      printf("Maximo produto %d %d %d.\n", idp, max_ido, max_quantity);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }

}

void read_idp_and_price(int array[10000][2])
{
  for (i = 0; (i < empty_spot_products_table) && (i < 10000); i++)
  {
    array[i][0] = products_table[i].idp;
    array[i][1] = products_table[i].price;
  }

}

void price_sort(int array[10000][2])
{
  int price_aux;
  int idp_aux;
  for (i = 0; (i < (empty_spot_products_table - 1)) && (i < (10000 - 1)); i++)
  {
    for (j = i + 1; (j < empty_spot_products_table) && (j < 10000); j++)
    {
      if ((array[i][1] > array[j][1]) || ((array[i][1] == array[j][1]) && (array[i][0] > array[j][0])))
      {
        idp_aux = array[i][0];
        price_aux = array[i][1];
        array[i][0] = array[j][0];
        array[i][1] = array[j][1];
        array[j][0] = idp_aux;
        array[j][1] = price_aux;
      }
      else
      {
        
      }

    }

  }

}

void print_sort_by_price(int array[10000][2])
{
  printf("Produtos\n");
  for (i = 0; (i < empty_spot_products_table) && (i < 10000); i++)
  {
    printf("* %s %d %d\n", products_table[array[i][0]].description, products_table[array[i][0]].price, products_table[array[i][0]].quantity);
  }

}

void l()
{
  int sort_by_price[10000][2];
  read_idp_and_price(sort_by_price);
  price_sort(sort_by_price);
  print_sort_by_price(sort_by_price);
}

void L()
{
  struct idp_and_description
  {
    int idp_in_order;
    char description[64];
  };
  typedef struct idp_and_description idp_and_description;
  idp_and_description alphabetical_order[200];
  char aux_description[64];
  int aux_idp;
  ido = atoi(strtok(0, ":"));
  if (ido < empty_spot_orders_table)
  {
    for (i = 0; (i < orders_table[ido].empty_spot_products_on_orders_table) && (i < 200); i++)
    {
      alphabetical_order[i].idp_in_order = i;
      strcpy(alphabetical_order[i].description, orders_table[ido].products_in_order[i].description);
    }

    for (i = 0; (i < (orders_table[ido].empty_spot_products_on_orders_table - 1)) && (i < (200 - 1)); i++)
    {
      for (j = i + 1; (j < (orders_table[ido].empty_spot_products_on_orders_table - 1)) && (j < (200 - 1)); j++)
      {
        if (strcmp(alphabetical_order[i].description, alphabetical_order[j].description) > 0)
        {
          strcpy(aux_description, alphabetical_order[i].description);
          aux_idp = alphabetical_order[i].idp_in_order;
          strcpy(alphabetical_order[i].description, alphabetical_order[j].description);
          alphabetical_order[i].idp_in_order = alphabetical_order[j].idp_in_order;
          strcpy(alphabetical_order[j].description, aux_description);
          alphabetical_order[j].idp_in_order = aux_idp;
        }
        else
        {
          
        }

      }

    }

    printf("Encomenda %d\n", ido);
    for (i = 0; (i < orders_table[ido].empty_spot_products_on_orders_table) && (i < 200); i++)
    {
      printf("* %s %d %d\n", alphabetical_order[i].description, orders_table[ido].products_in_order[alphabetical_order[i].idp_in_order].price, orders_table[ido].products_in_order[alphabetical_order[i].idp_in_order].quantity);
    }

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
  }

}

char *read_command()
{
  char *first_character;
  fgets(command, 100, stdin);
  if (strlen(command) == 2)
  {
    first_character = strtok(command, "\n");
  }
  else
  {
    first_character = strtok(command, " ");
  }

  return first_character;
}

int main()
{
  char *letter;
  for (;;)
  {
    letter = read_command();
    if (strcmp(letter, "x") == 0)
    {
      break;
    }
    else
    {
      if (strcmp(letter, "a") == 0)
      {
        a();
      }
      else
      {
        if (strcmp(letter, "q") == 0)
        {
          q();
        }
        else
        {
          if (strcmp(letter, "N") == 0)
          {
            N();
          }
          else
          {
            if (strcmp(letter, "A") == 0)
            {
              A();
            }
            else
            {
              if (strcmp(letter, "r") == 0)
              {
                r();
              }
              else
              {
                if (strcmp(letter, "R") == 0)
                {
                  R();
                }
                else
                {
                  if (strcmp(letter, "C") == 0)
                  {
                    C();
                  }
                  else
                  {
                    if (strcmp(letter, "p") == 0)
                    {
                      p();
                    }
                    else
                    {
                      if (strcmp(letter, "E") == 0)
                      {
                        E();
                      }
                      else
                      {
                        if (strcmp(letter, "m") == 0)
                        {
                          m();
                        }
                        else
                        {
                          if (strcmp(letter, "l") == 0)
                          {
                            l();
                          }
                          else
                          {
                            if (strcmp(letter, "L") == 0)
                            {
                              L();
                            }
                            else
                            {
                              
                            }

                          }

                        }

                      }

                    }

                  }

                }

              }

            }

          }

        }

      }

    }

  }

  return 0;
}

