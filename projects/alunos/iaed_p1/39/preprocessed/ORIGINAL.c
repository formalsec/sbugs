#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int products = 0;
int deliveries = 0;
typedef struct 
{
  int ID;
  char description[64];
  int price;
  int weight;
  int amount;
} Product;
typedef struct 
{
  Product products[10000];
  int delivery_weight;
  int delivery_ID;
  int different_products;
} Delivery;
Product all_products[10000];
Delivery company[500];
Product all_products_sort[10000];
Product temporary;
int Exists_Product(int product_ID)
{
  if (product_ID >= products)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

int Exists_Delivery(int delivery_ID)
{
  if (delivery_ID >= deliveries)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

void add_product()
{
  char input[220];
  fgets(input, 220, stdin);
  for (int all_products_index = 0; all_products_index < 10; all_products_index++)
  {
    all_products[products].description[all_products_index] = new_sym_var(sizeof(char) * 8);
  }

  all_products[products].description[10 - 1] = '\0';
  all_products[products].price = new_sym_var(sizeof(int) * 8);
  all_products[products].weight = new_sym_var(sizeof(int) * 8);
  all_products[products].amount = new_sym_var(sizeof(int) * 8);
  all_products[products].ID = products;
  printf("Novo produto %d.\n", products);
  products++;
  ;
}

void add_amount()
{
  char input[220];
  int product_ID;
  int _amount;
  fgets(input, 220, stdin);
  product_ID = new_sym_var(sizeof(int) * 8);
  _amount = new_sym_var(sizeof(int) * 8);
  if (Exists_Product(product_ID) == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", product_ID);
    return;
  }
  else
  {
    
  }

  all_products[product_ID].amount += _amount;
}

void add_delivery()
{
  company[deliveries].delivery_ID = deliveries;
  company[deliveries].delivery_weight = 0;
  company[deliveries].different_products = 0;
  printf("Nova encomenda %d.\n", deliveries);
  deliveries++;
}

void add_product_to_delivery()
{
  int delivery_ID;
  int product_ID;
  int k;
  int _amount;
  char input[220];
  fgets(input, 220, stdin);
  delivery_ID = new_sym_var(sizeof(int) * 8);
  product_ID = new_sym_var(sizeof(int) * 8);
  _amount = new_sym_var(sizeof(int) * 8);
  if (Exists_Delivery(delivery_ID) == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", product_ID, delivery_ID);
    return;
  }
  else
  {
    
  }

  if (Exists_Product(product_ID) == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", product_ID, delivery_ID);
    return;
  }
  else
  {
    
  }

  if (all_products[product_ID].amount < _amount)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", product_ID, delivery_ID);
    return;
  }
  else
  {
    
  }

  if ((company[delivery_ID].delivery_weight + (all_products[product_ID].weight * _amount)) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", product_ID, delivery_ID);
    return;
  }
  else
  {
    
  }

  for (k = 0; k < company[delivery_ID].different_products; k++)
  {
    if (company[delivery_ID].products[k].ID == product_ID)
    {
      company[delivery_ID].products[k].amount += _amount;
      all_products[product_ID].amount = all_products[product_ID].amount - _amount;
      company[delivery_ID].delivery_weight += all_products[product_ID].weight * _amount;
      return;
    }
    else
    {
      
    }

  }

  company[delivery_ID].delivery_weight += all_products[product_ID].weight * _amount;
  all_products[product_ID].amount = all_products[product_ID].amount - _amount;
  company[delivery_ID].products[company[delivery_ID].different_products] = all_products[product_ID];
  company[delivery_ID].products[company[delivery_ID].different_products].amount = _amount;
  company[delivery_ID].different_products++;
  return;
}

void remove_product_stock()
{
  int _amount;
  int product_ID;
  char input[220];
  fgets(input, 220, stdin);
  product_ID = new_sym_var(sizeof(int) * 8);
  _amount = new_sym_var(sizeof(int) * 8);
  if (Exists_Product(product_ID) == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", product_ID);
    return;
  }
  else
  {
    
  }

  if (all_products[product_ID].amount < _amount)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", _amount, product_ID);
    return;
  }
  else
  {
    
  }

  all_products[product_ID].amount -= _amount;
}

void remove_delivery_product()
{
  int delivery_ID;
  int product_ID;
  int i;
  char input[220];
  fgets(input, 220, stdin);
  delivery_ID = new_sym_var(sizeof(int) * 8);
  product_ID = new_sym_var(sizeof(int) * 8);
  if (Exists_Delivery(delivery_ID) == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", product_ID, delivery_ID);
    return;
  }
  else
  {
    
  }

  if (Exists_Product(product_ID) == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", product_ID, delivery_ID);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < company[delivery_ID].different_products; i++)
  {
    if (company[delivery_ID].products[i].ID == product_ID)
    {
      company[delivery_ID].delivery_weight -= company[delivery_ID].products[i].weight * company[delivery_ID].products[i].amount;
      all_products[product_ID].amount += company[delivery_ID].products[i].amount;
      temporary = company[delivery_ID].products[company[delivery_ID].different_products - 1];
      company[delivery_ID].products[company[delivery_ID].different_products - 1] = company[delivery_ID].products[i];
      company[delivery_ID].products[i] = temporary;
      company[delivery_ID].different_products--;
      return;
    }
    else
    {
      
    }

  }

}

void price_generator()
{
  char input[220];
  int delivery_ID;
  int i;
  int full_price = 0;
  fgets(input, 220, stdin);
  delivery_ID = new_sym_var(sizeof(int) * 8);
  if (Exists_Delivery(delivery_ID) == 0)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", delivery_ID);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < company[delivery_ID].different_products; i++)
  {
    full_price += company[delivery_ID].products[i].price * company[delivery_ID].products[i].amount;
  }

  printf("Custo da encomenda %d %d.\n", delivery_ID, full_price);
}

void price_change()
{
  char input[220];
  int product_ID;
  int price;
  int k;
  int j;
  fgets(input, 220, stdin);
  product_ID = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if (Exists_Product(product_ID) == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", product_ID);
    return;
  }
  else
  {
    
  }

  all_products[product_ID].price = price;
  for (k = 0; k < deliveries; k++)
  {
    for (j = 0; j < company[k].different_products; j++)
    {
      if (company[k].products[j].ID == product_ID)
      {
        company[k].products[j].price = price;
      }
      else
      {
        
      }

    }

  }

}

void look_product()
{
  char input[220];
  int product_ID;
  int delivery_ID;
  int i;
  fgets(input, 220, stdin);
  delivery_ID = new_sym_var(sizeof(int) * 8);
  product_ID = new_sym_var(sizeof(int) * 8);
  if (Exists_Delivery(delivery_ID) == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", delivery_ID);
    return;
  }
  else
  {
    
  }

  if (Exists_Product(product_ID) == 0)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", product_ID);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < company[delivery_ID].different_products; i++)
  {
    if (company[delivery_ID].products[i].ID == product_ID)
    {
      printf("%s %d.\n", company[delivery_ID].products[i].description, company[delivery_ID].products[i].amount);
      return;
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", all_products[product_ID].description, 0);
}

void product_ocurrences()
{
  char input[220];
  int product_ID;
  int j;
  int k;
  int max = 0;
  int max_ID;
  fgets(input, 220, stdin);
  product_ID = new_sym_var(sizeof(int) * 8);
  if (Exists_Product(product_ID) == 0)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", product_ID);
    return;
  }
  else
  {
    
  }

  for (j = 0; j < deliveries; j++)
  {
    for (k = 0; k < company[j].different_products; k++)
    {
      if (company[j].products[k].ID == product_ID)
      {
        if (company[j].products[k].amount > max)
        {
          max = company[j].products[k].amount;
          max_ID = company[j].delivery_ID;
        }
        else
        {
          if (company[j].products[k].amount == max)
          {
            if (company[j].delivery_ID < max_ID)
            {
              max_ID = company[j].products[k].ID;
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
      else
      {
        
      }

    }

  }

  if (max != 0)
  {
    printf("Maximo produto %d %d %d.\n", product_ID, max_ID, max);
  }
  else
  {
    
  }

}

void merge_letter(int left, int m, int right)
{
  Product aux[10000];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = all_products_sort[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = all_products_sort[j + 1];

  for (k = left; k <= right; k++)
    if (strcmp(aux[j].description, aux[i].description) < 0)
  {
    all_products_sort[k] = aux[j--];
  }
  else
  {
    all_products_sort[k] = aux[i++];
  }


}

void mergesort_letter(int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort_letter(left, m);
  mergesort_letter(m + 1, right);
  merge_letter(left, m, right);
}

void merge_price(int left, int m, int right)
{
  Product aux[10000];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
    aux[i - 1] = all_products_sort[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = all_products_sort[j + 1];

  for (k = left; k <= right; k++)
    if (aux[j].price < aux[i].price)
  {
    all_products_sort[k] = aux[j--];
  }
  else
  {
    if ((aux[j].price == aux[i].price) && (aux[j].ID < aux[i].ID))
    {
      all_products_sort[k] = aux[j--];
    }
    else
    {
      all_products_sort[k] = aux[i++];
    }

  }


}

void mergesort_price(int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort_price(left, m);
  mergesort_price(m + 1, right);
  merge_price(left, m, right);
}

void price_list()
{
  int i;
  for (i = 0; i < products; i++)
  {
    all_products_sort[i] = all_products[i];
  }

  mergesort_price(0, products - 1);
  printf("Produtos\n");
  for (i = 0; i < products; i++)
  {
    printf("* %s %d %d\n", all_products_sort[i].description, all_products_sort[i].price, all_products_sort[i].amount);
  }

  for (i = 0; i < products; i++)
  {
    all_products_sort[i].amount = 0;
  }

}

void letter_order()
{
  char input[220];
  int i;
  int delivery_ID;
  fgets(input, 220, stdin);
  delivery_ID = new_sym_var(sizeof(int) * 8);
  if (Exists_Delivery(delivery_ID) == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", delivery_ID);
    return;
  }
  else
  {
    
  }

  if (company[delivery_ID].different_products == 0)
  {
    printf("Encomenda %d\n", delivery_ID);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < company[delivery_ID].different_products; i++)
  {
    all_products_sort[i] = company[delivery_ID].products[i];
  }

  mergesort_letter(0, company[delivery_ID].different_products - 1);
  printf("Encomenda %d\n", delivery_ID);
  for (i = 0; i < company[delivery_ID].different_products; i++)
  {
    if (all_products_sort[i].amount != 0)
    {
      printf("* %s %d %d\n", all_products_sort[i].description, all_products_sort[i].price, all_products_sort[i].amount);
    }
    else
    {
      
    }

  }

  for (i = 0; i < company[delivery_ID].different_products; i++)
  {
    all_products_sort[i].amount = 0;
  }

}

int main()
{
  char function;
  do
  {
    function = getchar();
    getchar();
    switch (function)
    {
      case 'a':
        add_product();
        break;

      case 'q':
        add_amount();
        break;

      case 'N':
        add_delivery();
        break;

      case 'A':
        add_product_to_delivery();
        break;

      case 'r':
        remove_product_stock();
        break;

      case 'R':
        remove_delivery_product();
        break;

      case 'C':
        price_generator();
        break;

      case 'p':
        price_change();
        break;

      case 'E':
        look_product();
        break;

      case 'm':
        product_ocurrences();
        break;

      case 'l':
        price_list();
        break;

      case 'L':
        letter_order();
        break;

    }

  }
  while (function != 'x');
  return 0;
}

