/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct 
{
  int id;
  char description[64];
  int price;
  int weight;
  int amount;
  int state;
} Product;
typedef struct 
{
  Product products[10001];
  int price;
  int weight;
  int state;
  int id;
} Order;
int getId();
int getOrderId();
int calcOrderId(int id, int x);
int getHighest(int id);
int getSortedN();
void clear();
void copyList(int id);
void updatePrice(int id, int price);
void sort();
void mergeAlpha(int left, int right);
void mergeAux(int left, int m, int right);
void mergeSort(int left, int right);
void merge(int left, int m, int right);
void addProduct();
void addStock();
void addOrder();
void addToOrder();
void removeAmount();
void removeFromOrder();
void orderPrice();
void changePrice();
void listProduct();
void listHighest();
void listStock();
void listAlpha();
Product stock[10001];
Product sortedList[10001];
Order orders[501];
char *token;
char input[200];
int main()
{
  char command;
  do
  {
    command = getchar();
    if (command == 'a')
    {
      addProduct();
    }
    else
    {
      if (command == 'q')
      {
        addStock();
      }
      else
      {
        if (command == 'N')
        {
          addOrder();
        }
        else
        {
          if (command == 'A')
          {
            addToOrder();
          }
          else
          {
            if (command == 'r')
            {
              removeAmount();
            }
            else
            {
              if (command == 'R')
              {
                removeFromOrder();
              }
              else
              {
                if (command == 'C')
                {
                  orderPrice();
                }
                else
                {
                  if (command == 'p')
                  {
                    changePrice();
                  }
                  else
                  {
                    if (command == 'E')
                    {
                      listProduct();
                    }
                    else
                    {
                      if (command == 'm')
                      {
                        listHighest();
                      }
                      else
                      {
                        if (command == 'l')
                        {
                          listStock();
                        }
                        else
                        {
                          if (command == 'L')
                          {
                            listAlpha();
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
  while (command != 'x');
  return 0;
}

void addProduct()
{
  int id;
  getchar();
  fgets(input, sizeof(input), stdin);
  id = getId();
  if (id != (-1))
  {
    for (int stock_index = 0; stock_index < 10; stock_index++)
    {
      stock[id].description[stock_index] = new_sym_var(sizeof(char) * 8);
    }

    stock[id].description[10 - 1] = '\0';
    stock[id].price = new_sym_var(sizeof(int) * 8);
    stock[id].weight = new_sym_var(sizeof(int) * 8);
    stock[id].amount = new_sym_var(sizeof(int) * 8);
    stock[id].id = id;
    stock[id].state = 1;
    printf("Novo produto %d.\n", id);
  }
  else
  {
    
  }

}

int getId()
{
  int i;
  for (i = 0; i < 10001; i++)
  {
    if (stock[i].state == 0)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void addStock()
{
  int id;
  int amount;
  fgets(input, sizeof(input), stdin);
  id = new_sym_var(sizeof(int) * 8);
  amount = new_sym_var(sizeof(int) * 8);
  if (stock[id].state == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
  }
  else
  {
    stock[id].amount += amount;
  }

}

void addOrder()
{
  int id = getOrderId();
  if (id != (-1))
  {
    orders[id].state = 1;
    printf("Nova encomenda %d.\n", id);
  }
  else
  {
    
  }

}

int getOrderId()
{
  int i;
  for (i = 0; i < 501; i++)
  {
    if (orders[i].state == 0)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void addToOrder()
{
  int idOrder;
  int idProduct;
  int amount;
  fgets(input, sizeof(input), stdin);
  idOrder = new_sym_var(sizeof(int) * 8);
  idProduct = new_sym_var(sizeof(int) * 8);
  amount = new_sym_var(sizeof(int) * 8);
  if (orders[idOrder].state == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idProduct, idOrder);
    return;
  }
  else
  {
    if (stock[idProduct].state == 0)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idProduct, idOrder);
      return;
    }
    else
    {
      if (stock[idProduct].amount < amount)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idProduct, idOrder);
        return;
      }
      else
      {
        if ((orders[idOrder].weight + (stock[idProduct].weight * amount)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idProduct, idOrder);
          return;
        }
        else
        {
          
        }

      }

    }

  }

  if (orders[idOrder].products[idProduct].state == 0)
  {
    orders[idOrder].products[idProduct] = stock[idProduct];
    orders[idOrder].products[idProduct].amount = amount;
    orders[idOrder].price += stock[idProduct].price * amount;
    orders[idOrder].weight += stock[idProduct].weight * amount;
    stock[idProduct].amount -= amount;
    return;
  }
  else
  {
    
  }

  orders[idOrder].products[idProduct].amount += amount;
  orders[idOrder].price += stock[idProduct].price * amount;
  orders[idOrder].weight += stock[idProduct].weight * amount;
  stock[idProduct].amount -= amount;
}

void removeAmount()
{
  int id;
  int amount;
  fgets(input, sizeof(input), stdin);
  id = new_sym_var(sizeof(int) * 8);
  amount = new_sym_var(sizeof(int) * 8);
  if (stock[id].state == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    if (stock[id].amount < amount)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", amount, id);
      return;
    }
    else
    {
      
    }

  }

  stock[id].amount -= amount;
}

void removeFromOrder()
{
  int idOrder;
  int idProduct;
  fgets(input, sizeof(input), stdin);
  idOrder = new_sym_var(sizeof(int) * 8);
  idProduct = new_sym_var(sizeof(int) * 8);
  if (orders[idOrder].state == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idProduct, idOrder);
    return;
  }
  else
  {
    if (stock[idProduct].state == 0)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idProduct, idOrder);
      return;
    }
    else
    {
      
    }

  }

  if (orders[idOrder].products[idProduct].state == 1)
  {
    orders[idOrder].weight -= orders[idOrder].products[idProduct].weight * orders[idOrder].products[idProduct].amount;
    orders[idOrder].price -= orders[idOrder].products[idProduct].price * orders[idOrder].products[idProduct].amount;
    stock[idProduct].amount += orders[idOrder].products[idProduct].amount;
    orders[idOrder].products[idProduct].amount = 0;
    orders[idOrder].products[idProduct].state = 0;
  }
  else
  {
    
  }

}

void orderPrice()
{
  int id;
  fgets(input, sizeof(input), stdin);
  id = new_sym_var(sizeof(int) * 8);
  if (orders[id].state == 0)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  printf("Custo da encomenda %d %d.\n", id, orders[id].price);
}

void changePrice()
{
  int id;
  int price;
  fgets(input, sizeof(input), stdin);
  id = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if (stock[id].state == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  updatePrice(id, price);
  stock[id].price = price;
}

void updatePrice(int id, int price)
{
  int i;
  for (i = 0; i < 501; i++)
  {
    if (orders[i].products[id].state == 1)
    {
      orders[i].price -= stock[id].price * orders[i].products[id].amount;
      orders[i].products[id].price = price;
      orders[i].price += price * orders[i].products[id].amount;
    }
    else
    {
      
    }

  }

}

void listProduct()
{
  int idOrder;
  int idProduct;
  fgets(input, sizeof(input), stdin);
  idOrder = new_sym_var(sizeof(int) * 8);
  idProduct = new_sym_var(sizeof(int) * 8);
  if (orders[idOrder].state == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idOrder);
    return;
  }
  else
  {
    if (stock[idProduct].state == 0)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idProduct);
      return;
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", stock[idProduct].description, orders[idOrder].products[idProduct].amount);
}

void listHighest()
{
  int idProduct;
  int highest;
  int idOrder;
  fgets(input, sizeof(input), stdin);
  idProduct = new_sym_var(sizeof(int) * 8);
  if (stock[idProduct].state == 0)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idProduct);
    return;
  }
  else
  {
    
  }

  highest = getHighest(idProduct);
  idOrder = calcOrderId(idProduct, highest);
  if ((idOrder != (-1)) && (highest != 0))
  {
    printf("Maximo produto %d %d %d.\n", idProduct, idOrder, highest);
  }
  else
  {
    
  }

}

int getHighest(int id)
{
  int highest = 0;
  int i;
  for (i = 0; i < 501; i++)
  {
    if (orders[i].state == 1)
    {
      if (orders[i].products[id].state == 1)
      {
        if (orders[i].products[id].amount > highest)
        {
          highest = orders[i].products[id].amount;
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

  return highest;
}

int calcOrderId(int id, int x)
{
  int i;
  for (i = 0; i < 501; i++)
  {
    if (orders[i].products[id].amount == x)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void listStock()
{
  int right;
  int i;
  sort();
  right = getId() - 1;
  mergeSort(0, right);
  printf("Produtos\n");
  for (i = 0; i < (right + 1); i++)
    printf("* %s %d %d\n", sortedList[i].description, sortedList[i].price, sortedList[i].amount);

  clear();
}

void sort()
{
  int i;
  for (i = 0; i < 10001; i++)
    sortedList[i] = stock[i];

}

void clear()
{
  int i;
  for (i = 0; i < 10001; i++)
    sortedList[i].state = 0;

}

void mergeSort(int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergeSort(left, m);
  mergeSort(m + 1, right);
  merge(left, m, right);
}

void merge(int left, int m, int right)
{
  int i;
  int j;
  int k;
  Product aux[10001];
  for (i = m + 1; i > left; i--)
    aux[i - 1] = sortedList[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = sortedList[j + 1];

  for (k = left; k <= right; k++)
    if ((aux[j].price < aux[i].price) || (i > m))
  {
    sortedList[k] = aux[j--];
  }
  else
  {
    if (((aux[j].price == aux[i].price) && (aux[j].id < aux[i].id)) || (i > m))
    {
      sortedList[k] = aux[j--];
    }
    else
    {
      sortedList[k] = aux[i++];
    }

  }


}

void listAlpha()
{
  int id;
  int i;
  int right;
  fgets(input, sizeof(input), stdin);
  id = new_sym_var(sizeof(int) * 8);
  if (orders[id].state == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id);
    return;
  }
  else
  {
    
  }

  copyList(id);
  right = getSortedN() - 1;
  mergeAlpha(0, right);
  printf("Encomenda %d\n", id);
  if (right != (-2))
  {
    for (i = 0; i < (right + 1); i++)
      printf("* %s %d %d\n", sortedList[i].description, sortedList[i].price, sortedList[i].amount);

  }
  else
  {
    
  }

  clear();
}

void copyList(int id)
{
  int i;
  int k = 0;
  for (i = 0; i < 10001; i++)
  {
    if (orders[id].products[i].state == 1)
    {
      sortedList[k] = orders[id].products[i];
      k++;
    }
    else
    {
      
    }

  }

}

int getSortedN()
{
  int i;
  for (i = 0; i < 10001; i++)
  {
    if (sortedList[i].state == 0)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void mergeAlpha(int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergeAlpha(left, m);
  mergeAlpha(m + 1, right);
  mergeAux(left, m, right);
}

void mergeAux(int left, int m, int right)
{
  int i;
  int j;
  int k;
  Product aux[10001];
  for (i = m + 1; i > left; i--)
    aux[i - 1] = sortedList[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = sortedList[j + 1];

  for (k = left; k <= right; k++)
    if ((aux[j].description[0] < aux[i].description[0]) || (i > m))
  {
    sortedList[k] = aux[j--];
  }
  else
  {
    if (((aux[j].description[0] == aux[i].description[0]) && (aux[j].description[1] < aux[i].description[1])) || (i > m))
    {
      sortedList[k] = aux[j--];
    }
    else
    {
      if ((((aux[j].description[0] == aux[i].description[0]) && (aux[j].description[1] == aux[i].description[1])) && (aux[j].description[2] < aux[i].description[2])) || (i > m))
      {
        sortedList[k] = aux[j--];
      }
      else
      {
        if ((((aux[j].description[0] == aux[i].description[0]) && (aux[j].description[1] == aux[i].description[1])) && ((aux[j].description[2] == aux[i].description[2]) && (aux[j].description[3] < aux[i].description[3]))) || (i > m))
        {
          sortedList[k] = aux[j--];
        }
        else
        {
          sortedList[k] = aux[i++];
        }

      }

    }

  }


}

