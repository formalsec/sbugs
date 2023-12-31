#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct 
{
  int identifier;
  char description[63];
  int price;
  int p_weight;
  int total_stock;
} Product;
typedef struct 
{
  Product productsOrderList[200];
  int order_weight;
  int order_number;
  int products_counter;
} Order;
int numProducts;
int numOrders;
int IDP = 0;
int IDE = 0;
Product productsList[10000];
Order ordersList[500];
void addProduct();
void createsOrder();
void addToOrder();
void addProductToOrder();
void changeProduct();
void addStock();
void remStock();
void changePrice();
void calculatesOrderPrice();
void showDetails();
void moreTimesProduct();
void remProductFromOrder();
void printOrderProductsList();
void quickSort();
void swap();
int partition();
int comparePrice();
int less();
void printProductsList();
void sortProductsOrder();
int findIDP();
int findIDE();
int findProductAtOrder();
int main()
{
  int c;
  while (1)
  {
    c = getchar();
    switch (c)
    {
      case 'a':
        addProduct();
        break;

      case 'q':
        changeProduct(1);
        break;

      case 'N':
        createsOrder();
        break;

      case 'A':
        addToOrder();
        break;

      case 'r':
        changeProduct(2);
        break;

      case 'R':
        changeProduct(5);
        break;

      case 'C':
        changeProduct(7);
        break;

      case 'p':
        changeProduct(3);
        break;

      case 'E':
        changeProduct(4);
        break;

      case 'm':
        changeProduct(6);
        break;

      case 'l':
        printProductsList(productsList);
        break;

      case 'L':
        printOrderProductsList(ordersList);
        break;

      case 'x':
        return 0;

      default:
        break;

    }

    while (c != '\n')
      c = getchar();

  }

  return 0;
}

void addProduct()
{
  Product product;
  char input[200];
  char *delimiter = ":";
  char *token;
  int i;
  for (int input_index = 0; input_index < 10; input_index++)
  {
    input[input_index] = new_sym_var(sizeof(char) * 8);
  }

  input[10 - 1] = '\0';
  token = strtok(input, delimiter);
  i = 0;
  while (token != 0)
  {
    if (i == 0)
    {
      strcpy(product.description, token);
    }
    else
    {
      if (i == 1)
      {
        product.price = atoi(token);
      }
      else
      {
        if (i == 2)
        {
          product.p_weight = atoi(token);
        }
        else
        {
          if (i == 3)
          {
            product.total_stock = atoi(token);
          }
          else
          {
            
          }

        }

      }

    }

    token = strtok(0, delimiter);
    i++;
  }

  product.identifier = IDP++;
  productsList[numProducts++] = product;
  printf("Novo produto %d.\n", product.identifier);
}

void createsOrder()
{
  Order order;
  order.order_weight = 0;
  order.order_number = IDE++;
  order.products_counter = 0;
  ordersList[numOrders++] = order;
  printf("Nova encomenda %d.\n", order.order_number);
}

void changeProduct(int n)
{
  char input[63];
  char *delimiter;
  char *idp;
  char *qtd;
  char *ide;
  for (int input_index = 0; input_index < 10; input_index++)
  {
    input[input_index] = new_sym_var(sizeof(char) * 8);
  }

  input[10 - 1] = '\0';
  delimiter = ":";
  if (n == 4)
  {
    ide = strtok(input, delimiter);
    idp = strtok(0, delimiter);
    showDetails(atoi(ide), atoi(idp));
  }
  else
  {
    if (n == 5)
    {
      ide = strtok(input, delimiter);
      idp = strtok(0, delimiter);
      remProductFromOrder(atoi(ide), atoi(idp));
    }
    else
    {
      if (n == 6)
      {
        moreTimesProduct(atoi(input));
      }
      else
      {
        if (n == 7)
        {
          calculatesOrderPrice(atoi(input));
        }
        else
        {
          idp = strtok(input, delimiter);
          qtd = strtok(0, delimiter);
          if (n == 1)
          {
            addStock(atoi(idp), atoi(qtd));
          }
          else
          {
            
          }

          if (n == 2)
          {
            remStock(atoi(idp), atoi(qtd));
          }
          else
          {
            
          }

          if (n == 3)
          {
            changePrice(atoi(idp), atoi(qtd));
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void addStock(int idp, int qtd)
{
  int foundIDP = findIDP(idp);
  if (foundIDP == (-2))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    productsList[foundIDP].total_stock += qtd;
    return;
  }

}

void remStock(int idp, int qtd)
{
  int foundIDP = findIDP(idp);
  if (foundIDP == (-2))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (productsList[foundIDP].total_stock >= qtd)
    {
      productsList[foundIDP].total_stock -= qtd;
      return;
    }
    else
    {
      
    }

    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    return;
  }

}

void changePrice(int idp, int qtd)
{
  int foundIDP = findIDP(idp);
  int i;
  int j;
  if (foundIDP == (-2))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < numOrders; i++)
    {
      for (j = 0; j < ordersList[i].products_counter; j++)
      {
        if (ordersList[i].productsOrderList[j].identifier == idp)
        {
          ordersList[i].productsOrderList[j].price = qtd;
        }
        else
        {
          
        }

      }

    }

    productsList[idp].price = qtd;
    return;
  }

}

void showDetails(int ide, int idp)
{
  int foundIDE = findIDE(ide);
  int foundIDP = findIDP(idp);
  int exists;
  int total;
  int none = 0;
  Order o = ordersList[ide];
  exists = findProductAtOrder(o, foundIDP);
  if (foundIDE == (-1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (foundIDP == (-2))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      if (exists == (-3))
      {
        printf("%s %d.\n", productsList[idp].description, none);
      }
      else
      {
        total = o.productsOrderList[exists].total_stock;
        ordersList[foundIDE] = o;
        printf("%s %d.\n", productsList[idp].description, total);
        return;
      }

    }

  }

}

void calculatesOrderPrice(int ide)
{
  int foundIDE = findIDE(ide);
  int i;
  int total = 0;
  if (foundIDE == (-1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < ordersList[ide].products_counter; i++)
    {
      total += ordersList[ide].productsOrderList[i].price * ordersList[ide].productsOrderList[i].total_stock;
    }

    printf("Custo da encomenda %d %d.\n", ide, total);
    return;
  }

}

void addToOrder()
{
  char input[63];
  char *delimiter = ":";
  char *token;
  int ide;
  int idp;
  int qtd;
  int i = 0;
  for (int input_index = 0; input_index < 10; input_index++)
  {
    input[input_index] = new_sym_var(sizeof(char) * 8);
  }

  input[10 - 1] = '\0';
  token = strtok(input, delimiter);
  while (token != 0)
  {
    if (i == 0)
    {
      ide = atoi(token);
    }
    else
    {
      if (i == 1)
      {
        idp = atoi(token);
      }
      else
      {
        if (i == 2)
        {
          qtd = atoi(token);
        }
        else
        {
          
        }

      }

    }

    token = strtok(0, delimiter);
    i++;
  }

  addProductToOrder(ide, idp, qtd);
}

void addProductToOrder(int ide, int idp, int qtd)
{
  int exists;
  int k;
  int foundIDP = findIDP(idp);
  int foundIDE = findIDE(ide);
  if (foundIDE == (-1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (foundIDP == (-2))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (productsList[foundIDP].total_stock < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if (((productsList[foundIDP].p_weight * qtd) + ordersList[foundIDE].order_weight) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          Order o = ordersList[foundIDE];
          Product p = productsList[foundIDP];
          exists = findProductAtOrder(o, foundIDP);
          if (exists == (-3))
          {
            k = o.products_counter;
            o.productsOrderList[k] = p;
            o.productsOrderList[k].total_stock = qtd;
            o.products_counter++;
            o.order_weight += p.p_weight * qtd;
            ordersList[foundIDE] = o;
            p.total_stock -= qtd;
            productsList[foundIDP] = p;
            return;
          }
          else
          {
            o.productsOrderList[exists].total_stock += qtd;
            o.order_weight += p.p_weight * qtd;
            p.total_stock -= qtd;
            ordersList[foundIDE] = o;
            productsList[foundIDP] = p;
            return;
          }

        }

      }

    }

  }

}

void remProductFromOrder(int ide, int idp)
{
  int exists;
  int qtd = 0;
  int i;
  int foundIDE = findIDE(ide);
  int foundIDP = findIDP(idp);
  Order o = ordersList[ide];
  exists = findProductAtOrder(o, foundIDP);
  if (foundIDE == (-1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (foundIDP == (-2))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (exists == (-3))
      {
        return;
      }
      else
      {
        qtd = o.productsOrderList[exists].total_stock;
        productsList[foundIDP].total_stock += qtd;
        o.order_weight -= productsList[foundIDP].p_weight * qtd;
        for (i = exists; i < o.products_counter; i++)
        {
          o.productsOrderList[i] = o.productsOrderList[i + 1];
        }

        o.products_counter--;
        ordersList[foundIDE] = o;
      }

    }

  }

}

void moreTimesProduct(int idp)
{
  int foundIDP = findIDP(idp);
  int i;
  int j;
  int max = 0;
  int lastmax = 0;
  int foundIDE = -1;
  if (foundIDP == (-2))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

  for (i = 0; i < numOrders; i++)
  {
    for (j = 0; j < ordersList[i].products_counter; j++)
    {
      if (ordersList[i].productsOrderList[j].identifier == idp)
      {
        if (ordersList[i].productsOrderList[j].total_stock > max)
        {
          max = ordersList[i].productsOrderList[j].total_stock;
          if (max > lastmax)
          {
            lastmax = max;
            foundIDE = ordersList[i].order_number;
          }
          else
          {
            
          }

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

  if (foundIDE != (-1))
  {
    printf("Maximo produto %d %d %d.\n", idp, foundIDE, lastmax);
  }
  else
  {
    
  }

}

int findIDE(int ide)
{
  int i;
  for (i = 0; i < numOrders; i++)
  {
    if (ordersList[i].order_number == ide)
    {
      return ide;
    }
    else
    {
      
    }

  }

  return -1;
}

int findIDP(int idp)
{
  int i;
  for (i = 0; i < numProducts; i++)
  {
    if (productsList[i].identifier == idp)
    {
      return idp;
    }
    else
    {
      
    }

  }

  return -2;
}

int findProductAtOrder(Order o, int idp)
{
  int i;
  for (i = 0; i < o.products_counter; i++)
  {
    if (o.productsOrderList[i].identifier == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -3;
}

void printProductsList(Product *list)
{
  Product productsListAux[10000];
  int i;
  printf("Produtos\n");
  for (i = 0; i < numProducts; i++)
  {
    productsListAux[i] = list[i];
  }

  quickSort(productsListAux, 0, numProducts - 1);
  for (i = 0; i < numProducts; i++)
    printf("* %s %d %d\n", productsListAux[i].description, productsListAux[i].price, productsListAux[i].total_stock);

}

int partition(Product *list, int low, int high)
{
  Product pivot = list[high];
  int i = low - 1;
  int j = high;
  while (i < j)
  {
    while (comparePrice(list[++i], pivot) == 1)
      ;

    while (comparePrice(pivot, list[--j]) == 1)
      if (j == low)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      swap(&list[i], &list[j]);
    }
    else
    {
      
    }

  }

  swap(&list[i], &list[high]);
  return i;
}

void swap(Product *a, Product *b)
{
  Product t = *a;
  *a = *b;
  *b = t;
}

void quickSort(Product *list, int low, int high)
{
  if (low < high)
  {
    int pi = partition(list, low, high);
    quickSort(list, low, pi - 1);
    quickSort(list, pi + 1, high);
  }
  else
  {
    
  }

}

int comparePrice(Product old, Product new)
{
  if (old.price < new.price)
  {
    return 1;
  }
  else
  {
    if (old.price > new.price)
    {
      return 0;
    }
    else
    {
      if (old.price == new.price)
      {
        if (old.identifier < new.identifier)
        {
          return 1;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      return 0;
    }

  }

}

void printOrderProductsList(Order *ordersList)
{
  Product auxOrderProductsList[10000];
  int foundIDE;
  int i;
  char input[63];
  int ide;
  for (int input_index = 0; input_index < 10; input_index++)
  {
    input[input_index] = new_sym_var(sizeof(char) * 8);
  }

  input[10 - 1] = '\0';
  ide = atoi(input);
  foundIDE = findIDE(ide);
  if (foundIDE == (-1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < ordersList[ide].products_counter; i++)
  {
    auxOrderProductsList[i] = ordersList[ide].productsOrderList[i];
  }

  sortProductsOrder(auxOrderProductsList, ordersList[ide].products_counter);
  printf("Encomenda %d\n", ordersList[foundIDE].order_number);
  for (i = 0; i < ordersList[foundIDE].products_counter; i++)
  {
    printf("* %s %d %d\n", auxOrderProductsList[i].description, auxOrderProductsList[i].price, auxOrderProductsList[i].total_stock);
  }

}

void sortProductsOrder(Product *list, int n)
{
  int i;
  int j;
  Product temp;
  for (i = 0; i < n; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (strcmp(list[i].description, list[j].description) > 0)
      {
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
      }
      else
      {
        
      }

    }

  }

}

