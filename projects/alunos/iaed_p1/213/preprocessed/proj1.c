#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  char description[63];
  int price_or_id;
  int weight;
  int stock;
} Product;
typedef struct 
{
  Product products[200];
  int total_weight;
  int counter;
} Order;
typedef struct 
{
  int temp_int;
  int temp_counter;
} Instruction;
Instruction instruction_reader(char input[100], int i);
Product new_product(char input[100]);
void list_simple(Product products[9999], int id);
void restock(char input[100], Product products[9999], int id);
void order_update(char input[100], Order orders[500], Product products[9999], int order_id, int id);
void list_order_simple(char input[100], Order orders[500], Product products[9999], int order_id);
void remove_stock(char input[100], Product products[9999], int id);
void remove_product_order(char input[100], Product products[9999], Order orders[500], int order_id, int id);
void cost_of_order(char input[100], Product products[9999], Order orders[500], int order_id);
void change_price(char input[100], Product products[9999], int id);
void what_product(char input[100], Product products[9999], Order orders[500], int order_id, int id);
void which_order(char input[100], Order orders[500], int order_id, int id);
void list_by_price(Product products[9999], int id);
void list_by_name(char input[100], Order orders[500], Product products[9999], int order_id);
int is_product_in_order(int temp_order_id, int temp_product_id, Order orders[500]);
void mergesort(Product products[9999], int left, int right);
void merge(Product products[9999], int left, int m, int right);
int main()
{
  char input[100];
  Product products[9999];
  Order orders[500];
  int id = 0;
  int order_id = 0;
  do
  {
    fgets(input, 100, stdin);
    switch (input[0])
    {
      case 'a':
        products[id] = new_product(input);
        printf("Novo produto %d.\n", id);
        id++;
        break;

      case 'k':
        list_simple(products, id);
        break;

      case 'q':
        restock(input, products, id);
        break;

      case 'N':
        printf("Nova encomenda %d.\n", order_id);
        orders[order_id].counter = 0;
        order_id++;
        break;

      case 'A':
        order_update(input, orders, products, order_id, id);
        break;

      case 'K':
        list_order_simple(input, orders, products, order_id);
        break;

      case 'r':
        remove_stock(input, products, id);
        break;

      case 'R':
        remove_product_order(input, products, orders, order_id, id);
        break;

      case 'C':
        cost_of_order(input, products, orders, order_id);
        break;

      case 'p':
        change_price(input, products, id);
        break;

      case 'E':
        what_product(input, products, orders, order_id, id);
        break;

      case 'm':
        which_order(input, orders, order_id, id);
        break;

      case 'l':
        list_by_price(products, id);
        break;

      case 'L':
        list_by_name(input, orders, products, order_id);
        break;

    }

  }
  while (input[0] != 'x');
  return 0;
}

Instruction instruction_reader(char input[100], int i)
{
  Instruction reader;
  reader.temp_int = 0;
  while ((input[i] != ':') && (input[i] != '\n'))
  {
    reader.temp_int = ((reader.temp_int * 10) + input[i]) - '0';
    i++;
  }

  reader.temp_counter = i;
  return reader;
}

Product new_product(char input[100])
{
  Instruction reader;
  Product temp;
  int i = 2;
  int j = 0;
  while (input[i] != ':')
  {
    temp.description[j] = input[i];
    i++;
    j++;
  }

  temp.description[j] = '\0';
  i++;
  reader = instruction_reader(input, i);
  temp.price_or_id = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp.weight = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp.stock = reader.temp_int;
  return temp;
}

void list_simple(Product products[9999], int id)
{
  int i = 0;
  printf("Produtos\n");
  while (i < id)
  {
    printf("* %s %d %d\n", products[i].description, products[i].price_or_id, products[i].stock);
    i++;
  }

}

void restock(char input[100], Product products[9999], int id)
{
  Instruction reader;
  int temp_product_id = 0;
  int temp_amount = 0;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_product_id = reader.temp_int;
  if (temp_product_id < id)
  {
    i = reader.temp_counter + 1;
    reader = instruction_reader(input, i);
    temp_amount = reader.temp_int;
    products[temp_product_id].stock += temp_amount;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", temp_product_id);
  }

}

void order_update(char input[100], Order orders[500], Product products[9999], int order_id, int id)
{
  Instruction reader;
  int temp_order_id = 0;
  int temp_product_id = 0;
  int temp_amount = 0;
  int already_in_order = -1;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_order_id = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp_product_id = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp_amount = reader.temp_int;
  if (temp_order_id >= order_id)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", temp_product_id, temp_order_id);
  }
  else
  {
    if (temp_product_id >= id)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", temp_product_id, temp_order_id);
    }
    else
    {
      if (temp_amount > products[temp_product_id].stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", temp_product_id, temp_order_id);
      }
      else
      {
        if (((products[temp_product_id].weight * temp_amount) + orders[temp_order_id].total_weight) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", temp_product_id, temp_order_id);
        }
        else
        {
          already_in_order = is_product_in_order(temp_order_id, temp_product_id, orders);
          if (already_in_order != (-1))
          {
            orders[temp_order_id].products[already_in_order].stock += temp_amount;
            products[temp_product_id].stock -= temp_amount;
            orders[temp_order_id].total_weight += products[temp_product_id].weight * temp_amount;
          }
          else
          {
            strcpy(orders[temp_order_id].products[orders[temp_order_id].counter].description, products[temp_product_id].description);
            orders[temp_order_id].products[orders[temp_order_id].counter].price_or_id = temp_product_id;
            orders[temp_order_id].products[orders[temp_order_id].counter].stock = temp_amount;
            products[temp_product_id].stock -= temp_amount;
            orders[temp_order_id].total_weight += products[temp_product_id].weight * temp_amount;
            orders[temp_order_id].counter++;
          }

        }

      }

    }

  }

}

void list_order_simple(char input[100], Order orders[500], Product products[9999], int order_id)
{
  Instruction reader;
  int temp_order_id = 0;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_order_id = reader.temp_int;
  if (temp_order_id >= order_id)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", temp_order_id);
  }
  else
  {
    i = 0;
    printf("Encomenda %d\n", temp_order_id);
    while (i < orders[temp_order_id].counter)
    {
      printf("* %s %d %d\n", orders[temp_order_id].products[i].description, products[orders[temp_order_id].products[i].price_or_id].price_or_id, orders[temp_order_id].products[i].stock);
      i++;
    }

  }

}

void remove_stock(char input[100], Product products[9999], int id)
{
  Instruction reader;
  int temp_product_id = 0;
  int temp_amount = 0;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_product_id = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp_amount = reader.temp_int;
  if (temp_product_id >= id)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", temp_product_id);
  }
  else
  {
    if (temp_amount > products[temp_product_id].stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", temp_amount, temp_product_id);
    }
    else
    {
      products[temp_product_id].stock -= temp_amount;
    }

  }

}

void remove_product_order(char input[100], Product products[9999], Order orders[500], int order_id, int id)
{
  Instruction reader;
  int temp_order_id = 0;
  int temp_product_id = 0;
  int product_in_order = -1;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_order_id = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp_product_id = reader.temp_int;
  if (temp_order_id >= order_id)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", temp_product_id, temp_order_id);
  }
  else
  {
    if (temp_product_id >= id)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", temp_product_id, temp_order_id);
    }
    else
    {
      product_in_order = is_product_in_order(temp_order_id, temp_product_id, orders);
      if (product_in_order >= 0)
      {
        products[temp_product_id].stock += orders[temp_order_id].products[product_in_order].stock;
        orders[temp_order_id].total_weight -= products[temp_product_id].weight * orders[temp_order_id].products[product_in_order].stock;
        if (orders[temp_order_id].total_weight < 0)
        {
          orders[temp_order_id].total_weight = 0;
        }
        else
        {
          
        }

        orders[temp_order_id].products[product_in_order].stock = 0;
        strcpy(orders[temp_order_id].products[product_in_order].description, orders[temp_order_id].products[orders[temp_order_id].counter - 1].description);
        orders[temp_order_id].products[product_in_order].price_or_id = orders[temp_order_id].products[orders[temp_order_id].counter - 1].price_or_id;
        orders[temp_order_id].products[product_in_order].stock = orders[temp_order_id].products[orders[temp_order_id].counter - 1].stock;
        orders[temp_order_id].counter--;
      }
      else
      {
        
      }

    }

  }

}

void cost_of_order(char input[100], Product products[9999], Order orders[500], int order_id)
{
  Instruction reader;
  int temp_order_id = 0;
  int temp_cost = 0;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_order_id = reader.temp_int;
  if (temp_order_id >= order_id)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", temp_order_id);
  }
  else
  {
    i = 0;
    while (i < orders[temp_order_id].counter)
    {
      temp_cost += products[orders[temp_order_id].products[i].price_or_id].price_or_id * orders[temp_order_id].products[i].stock;
      i++;
    }

    printf("Custo da encomenda %d %d.\n", temp_order_id, temp_cost);
  }

}

void change_price(char input[100], Product products[9999], int id)
{
  Instruction reader;
  int temp_product_id = 0;
  int temp_price = 0;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_product_id = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp_price = reader.temp_int;
  if (temp_product_id >= id)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", temp_product_id);
  }
  else
  {
    products[temp_product_id].price_or_id = temp_price;
  }

}

void what_product(char input[100], Product products[9999], Order orders[500], int order_id, int id)
{
  Instruction reader;
  int temp_product_id = 0;
  int temp_order_id = 0;
  int product_in_order = -1;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_order_id = reader.temp_int;
  i = reader.temp_counter + 1;
  reader = instruction_reader(input, i);
  temp_product_id = reader.temp_int;
  if (temp_order_id >= order_id)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", temp_order_id);
  }
  else
  {
    if (temp_product_id >= id)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", temp_product_id);
    }
    else
    {
      product_in_order = is_product_in_order(temp_order_id, temp_product_id, orders);
      if (product_in_order >= 0)
      {
        printf("%s %d.\n", products[temp_product_id].description, orders[temp_order_id].products[product_in_order].stock);
      }
      else
      {
        printf("%s 0.\n", products[temp_product_id].description);
      }

    }

  }

}

void which_order(char input[100], Order orders[500], int order_id, int id)
{
  Instruction reader;
  int temp_product_id = 0;
  int temp_order_id = 0;
  int temp_stock = 0;
  int j;
  int i = 2;
  reader = instruction_reader(input, i);
  temp_product_id = reader.temp_int;
  if (temp_product_id >= id)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", temp_product_id);
  }
  else
  {
    i = 0;
    while (i < order_id)
    {
      j = 0;
      while (j < orders[i].counter)
      {
        if (orders[i].products[j].price_or_id == temp_product_id)
        {
          if (orders[i].products[j].stock > temp_stock)
          {
            temp_stock = orders[i].products[j].stock;
            temp_order_id = i;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

        j++;
      }

      i++;
    }

    if (temp_stock > 0)
    {
      printf("Maximo produto %d %d %d.\n", temp_product_id, temp_order_id, temp_stock);
    }
    else
    {
      
    }

  }

}

void list_by_price(Product products[9999], int id)
{
  Product temp_products[9999];
  int i;
  for (i = 0; i < id; i++)
  {
    temp_products[i] = products[i];
  }

  mergesort(temp_products, 0, id - 1);
  printf("Produtos\n");
  for (i = 0; i < id; i++)
  {
    printf("* %s %d %d\n", temp_products[i].description, temp_products[i].price_or_id, temp_products[i].stock);
  }

}

void list_by_name(char input[100], Order orders[500], Product products[9999], int order_id)
{
  Instruction reader;
  int temp_order_id = 0;
  char min_description_this_cycle[63];
  int min_position;
  int already_printed[200] = {0};
  int j;
  int k;
  int i = 2;
  Product min_name_prod;
  reader = instruction_reader(input, i);
  temp_order_id = reader.temp_int;
  if (temp_order_id >= order_id)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", temp_order_id);
  }
  else
  {
    printf("Encomenda %d\n", temp_order_id);
    for (i = 0; i < orders[temp_order_id].counter; i++)
    {
      strcpy(min_description_this_cycle, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
      for (j = 0; j < orders[temp_order_id].counter; j++)
      {
        if (!already_printed[j])
        {
          for (k = 0; k < 63; k++)
          {
            if (orders[temp_order_id].products[j].description[k] < min_description_this_cycle[k])
            {
              strcpy(min_description_this_cycle, orders[temp_order_id].products[j].description);
              min_name_prod = orders[temp_order_id].products[j];
              min_position = j;
            }
            else
            {
              if (orders[temp_order_id].products[j].description[k] > min_description_this_cycle[k])
              {
                break;
              }
              else
              {
                
              }

            }

          }

        }
        else
        {
          
        }

      }

      already_printed[min_position] = 1;
      printf("* %s %d %d\n", min_name_prod.description, products[min_name_prod.price_or_id].price_or_id, min_name_prod.stock);
    }

  }

}

int is_product_in_order(int temp_order_id, int temp_product_id, Order orders[500])
{
  int i = 0;
  while (i < orders[temp_order_id].counter)
  {
    if (orders[temp_order_id].products[i].price_or_id == temp_product_id)
    {
      return i;
    }
    else
    {
      i++;
    }

  }

  return -1;
}

void mergesort(Product products[9999], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort(products, left, m);
  mergesort(products, m + 1, right);
  merge(products, left, m, right);
}

void merge(Product products[9999], int left, int m, int right)
{
  Product aux[9999];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = products[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = products[j + 1];

  for (k = left; k <= right; k++)
    if ((aux[j].price_or_id < aux[i].price_or_id) || (i > m))
  {
    products[k] = aux[j--];
  }
  else
  {
    products[k] = aux[i++];
  }


}

