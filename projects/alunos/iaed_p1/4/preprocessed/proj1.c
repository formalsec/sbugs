#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct product
{
  char description[63];
  int price;
  int weight;
  int quantity;
} Product;
typedef struct order_item
{
  struct order_item *next;
  int product_id;
  int quantity;
} Item;
void add_product(Product products[], Product new_product, int current);
void add_stock(Product products[], int idp, int qtd);
void remove_stock(Product products[], int idp, int qtd);
void add_product_to_order(int ide, int idp, int qtd, Product products[], Item *order);
Item *new_order_item(int idp, int qtd);
int remove_product_from_order(int idp, Item *order);
int order_cost(Item *order, Product products[]);
void change_product_price(Product products[], int idp, int price);
int get_order_item_quantity(int idp, Item *order);
void find_order_with_max_idp(Item *orders[], int idp);
int item_weight(int idp, int qtd, Product products[]);
int order_weight(Item *order, Product products[]);
void sort_print_products(Product original[], int size);
void sort_products_by_price(Product products[], int n);
void sort_print_order(Item *order, Product products[], int ide);
int main()
{
  char comando;
  Product products[10000];
  Item *orders[500] = {0};
  int current_product = 0;
  int current_order = 0;
  while (1)
  {
    Product a;
    int idp;
    int qtd;
    int ide;
    int price;
    int cost;
    comando = getchar();
    switch (comando)
    {
      case 'a':
        for (int a_index = 0; a_index < 10; a_index++)
      {
        a.description[a_index] = new_sym_var(sizeof(char) * 8);
      }

        a.description[10 - 1] = '\0';
        a.price = new_sym_var(sizeof(int) * 8);
        a.weight = new_sym_var(sizeof(int) * 8);
        a.quantity = new_sym_var(sizeof(int) * 8);
        add_product(products, a, current_product);
        printf("Novo produto %i.\n", current_product);
        current_product += 1;
        break;

      case 'q':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        if (idp < current_product)
      {
        add_stock(products, idp, qtd);
      }
      else
      {
        printf("Impossivel adicionar produto %i ao stock. Produto inexistente.\n", idp);
      }

        break;

      case 'N':
        orders[current_order] = new_order_item(-1, 0);
        printf("Nova encomenda %i.\n", current_order);
        current_order++;
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        if (ide >= current_order)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      }
      else
      {
        if (idp >= current_product)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
          if (products[idp].quantity < qtd)
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          }
          else
          {
            if ((item_weight(idp, qtd, products) + order_weight(orders[ide], products)) > 200)
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
            {
              if (orders[ide] == 0)
              {
                orders[ide] = new_order_item(idp, qtd);
                remove_stock(products, idp, qtd);
              }
              else
              {
                add_product_to_order(ide, idp, qtd, products, orders[ide]);
                remove_stock(products, idp, qtd);
              }

            }

          }

        }

      }

        break;

      case 'r':
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        if (idp >= current_product)
      {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        if (products[idp].quantity < qtd)
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
        else
        {
          remove_stock(products, idp, qtd);
        }

      }

        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        if (ide >= current_order)
      {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      }
      else
      {
        if (idp >= current_product)
        {
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
          qtd = remove_product_from_order(idp, orders[ide]);
          add_stock(products, idp, qtd);
        }

      }

        break;

      case 'C':
        ide = new_sym_var(sizeof(int) * 8);
        if (ide >= current_order)
      {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        cost = order_cost(orders[ide], products);
        printf("Custo da encomenda %d %d.\n", ide, cost);
      }

        break;

      case 'p':
        idp = new_sym_var(sizeof(int) * 8);
        price = new_sym_var(sizeof(int) * 8);
        if (idp >= current_product)
      {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        change_product_price(products, idp, price);
      }

        break;

      case 'E':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        if (ide >= current_order)
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        if (idp >= current_product)
        {
          printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
        else
        {
          int quantity = get_order_item_quantity(idp, orders[ide]);
          printf("%s %d.\n", products[idp].description, quantity);
        }

      }

        break;

      case 'm':
        idp = new_sym_var(sizeof(int) * 8);
        if (idp >= current_product)
      {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        if (current_order == 0)
        {
          break;
        }
        else
        {
          find_order_with_max_idp(orders, idp);
        }

      }

        break;

      case 'l':
        sort_print_products(products, current_product);
        break;

      case 'L':
        ide = new_sym_var(sizeof(int) * 8);
        if (ide >= current_order)
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        sort_print_order(orders[ide], products, ide);
      }

        break;

      case 'x':
        return 0;

      default:
        printf("ERRO: Comando desconhecido\n");
        break;

    }

    getchar();
  }

  return 1;
}

void add_product(Product *products, Product new_product, int current)
{
  products[current] = new_product;
}

void add_stock(Product *products, int idp, int qtd)
{
  products[idp].quantity += qtd;
}

void remove_stock(Product *products, int idp, int qtd)
{
  products[idp].quantity -= qtd;
}

void add_product_to_order(int ide, int idp, int qtd, Product products[], Item *order)
{
  Item *new;
  if (order->product_id == idp)
  {
    order->quantity += qtd;
  }
  else
  {
    if (order->next == 0)
    {
      new = new_order_item(idp, qtd);
      order->next = new;
    }
    else
    {
      add_product_to_order(ide, idp, qtd, products, order->next);
    }

  }

}

Item *new_order_item(int idp, int qtd)
{
  Item *new;
  new = (Item *) malloc(sizeof(Item));
  new->product_id = idp;
  new->quantity = qtd;
  new->next = 0;
  return new;
}

int remove_product_from_order(int idp, Item *order)
{
  Item *temp = order;
  Item *prev;
  int qtd = 0;
  while ((temp->next != 0) && (temp->product_id != idp))
  {
    prev = temp;
    temp = prev->next;
  }

  if (temp == 0)
  {
    return 0;
  }
  else
  {
    
  }

  if (temp->product_id == idp)
  {
    qtd = temp->quantity;
    if (temp->next == 0)
    {
      prev->next = 0;
    }
    else
    {
      prev->next = temp->next;
    }

    free(temp);
  }
  else
  {
    
  }

  return qtd;
}

int order_cost(Item *order, Product products[])
{
  int total = 0;
  Item *temp;
  if (order->product_id < 0)
  {
    temp = order->next;
  }
  else
  {
    
  }

  while (temp != 0)
  {
    int idp = temp->product_id;
    int qtd = temp->quantity;
    int price = products[idp].price;
    total += qtd * price;
    temp = temp->next;
  }

  return total;
}

void change_product_price(Product *products, int idp, int price)
{
  products[idp].price = price;
}

int get_order_item_quantity(int idp, Item *order)
{
  Item *temp = order;
  int quantity = 0;
  while ((temp->next != 0) && (temp->product_id != idp))
  {
    temp = temp->next;
  }

  if (temp->product_id == idp)
  {
    quantity = temp->quantity;
  }
  else
  {
    
  }

  return quantity;
}

void find_order_with_max_idp(Item *orders[], int idp)
{
  int i = 0;
  int max_order = 0;
  int max_qtd = 0;
  while (orders[i] != 0)
  {
    int qtd = get_order_item_quantity(idp, orders[i]);
    if (qtd > max_qtd)
    {
      max_qtd = qtd;
      max_order = i;
    }
    else
    {
      
    }

    i++;
  }

  if (max_qtd == 0)
  {
    return;
  }
  else
  {
    printf("Maximo produto %d %d %d.\n", idp, max_order, max_qtd);
  }

}

int item_weight(int idp, int qtd, Product products[])
{
  int weight = products[idp].weight * qtd;
  return weight;
}

int order_weight(Item *order, Product products[])
{
  int total = 0;
  Item *temp = order;
  while (temp != 0)
  {
    int idp = temp->product_id;
    int qtd = temp->quantity;
    total += item_weight(idp, qtd, products);
    temp = temp->next;
  }

  return total;
}

void sort_print_products(Product original[], int size)
{
  Product sorted[10000];
  int i;
  for (i = 0; i < size; i++)
  {
    sorted[i] = original[i];
  }

  sort_products_by_price(sorted, size);
}

void swap(Product *xp, Product *yp)
{
  Product temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void sort_products_by_price(Product products[], int size)
{
  int i;
  int j;
  int min_idx;
  for (i = 0; i < (size - 1); i++)
  {
    min_idx = i;
    for (j = i + 1; j < size; j++)
      if (products[j].price < products[min_idx].price)
    {
      min_idx = j;
    }
    else
    {
      
    }


    swap(&products[min_idx], &products[i]);
  }

  printf("Produtos\n");
  for (i = 0; i < size; i++)
  {
    printf("* %s %d %d\n", products[i].description, products[i].price, products[i].quantity);
  }

}

void sort_print_order(Item *order, Product products[], int ide)
{
  Item *temp;
  if (order->product_id < 0)
  {
    temp = order->next;
  }
  else
  {
    
  }

  printf("Encomenda %d\n", ide);
  while (temp != 0)
  {
    int price = products[temp->product_id].price;
    printf("* %s %d %d\n", products[temp->product_id].description, price, temp->quantity);
    temp = temp->next;
  }

}

