#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>


typedef struct product
{
  int id;
  int price;
  int weight;
  int quantity;
  char description[63];
} Product;
typedef struct order
{
  int id;
  int weight;
  int size;
  int price;
  Product items[200];
} Order;
Product productList[10000];
Order orderList[500];
int NextProductID;
int NextOrderID;
void copyString(char str[], char newStr[], int size)
{
  int i;
  for (i = 0; i < size; ++i)
  {
    newStr[i] = str[i];
  }

}

int compareString(char str1[], char str2[])
{
  int i;
  i = 0;
  while ((str1[i] != '\0') || (str2[i] != '\0'))
  {
    if (str1[i] < str2[i])
    {
      return -1;
    }
    else
    {
      if (str1[i] > str2[i])
      {
        return 1;
      }
      else
      {
        
      }

    }

    ++i;
  }

  return 0;
}

int linearProductSearch(Product productList[], int idp, int size)
{
  int i;
  for (i = 0; i < size; ++i)
  {
    if (productList[i].id == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

Product createProduct(int id, char description[], int price, int weight, int quantity)
{
  Product p;
  p.id = id;
  p.price = price;
  p.weight = weight;
  p.quantity = quantity;
  copyString(description, p.description, 63);
  return p;
}

void newProduct(char description[], int price, int weight, int quantity)
{
  productList[NextProductID] = createProduct(NextProductID, description, price, weight, quantity);
  printf("Novo produto %d.\n", NextProductID);
  ++NextProductID;
}

void addStock(int idp, int quantity)
{
  if (idp >= NextProductID)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  productList[idp].quantity += quantity;
}

Order createOrder(int id)
{
  Order e;
  e.id = id;
  e.weight = 0;
  e.size = 0;
  e.price = 0;
  return e;
}

void addOrder()
{
  orderList[NextOrderID] = createOrder(NextOrderID);
  printf("Nova encomenda %d.\n", NextOrderID);
  ++NextOrderID;
}

void removeStock(int idp, int quantity)
{
  if (idp >= NextProductID)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    if (productList[idp].quantity < quantity)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, idp);
      return;
    }
    else
    {
      
    }

  }

  productList[idp].quantity -= quantity;
}

void addProduct(int idp, int ide, int quantity)
{
  int pos;
  if (ide >= NextOrderID)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    if (idp >= NextProductID)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
    else
    {
      if (productList[idp].quantity < quantity)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
      }
      else
      {
        if ((orderList[ide].weight + (productList[idp].weight * quantity)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          return;
        }
        else
        {
          
        }

      }

    }

  }

  pos = linearProductSearch(orderList[ide].items, idp, orderList[ide].size);
  if (pos != (-1))
  {
    orderList[ide].items[pos].quantity += quantity;
  }
  else
  {
    if (orderList[ide].size < (200 - 1))
    {
      orderList[ide].items[orderList[ide].size] = productList[idp];
      orderList[ide].items[orderList[ide].size].quantity = quantity;
      ++orderList[ide].size;
    }
    else
    {
      for (pos = 0; pos < orderList[ide].size; ++pos)
      {
        if (orderList[ide].items[pos].quantity == 0)
        {
          orderList[ide].items[pos] = productList[idp];
          orderList[ide].items[pos].quantity = quantity;
          break;
        }
        else
        {
          
        }

      }

    }

  }

  orderList[ide].weight += productList[idp].weight * quantity;
  orderList[ide].price += productList[idp].price * quantity;
  removeStock(idp, quantity);
}

void removeProduct(int ide, int idp)
{
  int pos;
  if (ide >= NextOrderID)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    if (idp >= NextProductID)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      return;
    }
    else
    {
      
    }

  }

  pos = linearProductSearch(productList, idp, 10000);
  orderList[ide].weight -= productList[idp].weight * orderList[ide].items[pos].quantity;
  orderList[ide].price -= productList[idp].price * orderList[ide].items[pos].quantity;
  addStock(idp, orderList[ide].items[pos].quantity);
  orderList[ide].items[pos].quantity = 0;
}

void getOrderCost(int ide)
{
  if (ide >= NextOrderID)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  printf("Custo da encomenda %d %d.\n", ide, orderList[ide].price);
}

void changePrice(int idp, int price)
{
  int pos;
  int i;
  int delta;
  if (idp >= NextProductID)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  delta = price - productList[idp].price;
  productList[idp].price = price;
  for (i = 0; i < NextOrderID; ++i)
  {
    pos = linearProductSearch(orderList[i].items, idp, orderList[i].size);
    if ((pos != (-1)) && (orderList[i].items[pos].quantity != 0))
    {
      orderList[i].items[pos].price = price;
    }
    else
    {
      
    }

    orderList[i].price += delta;
  }

}

void listProduct(int ide, int idp)
{
  int pos;
  if (ide >= NextOrderID)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    if ((pos = linearProductSearch(orderList[ide].items, idp, orderList[ide].size)) == (-1))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      return;
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", orderList[ide].items[pos].description, orderList[ide].items[pos].quantity);
}

void listOccurrences(int idp)
{
  int count;
  int most;
  int i;
  int j;
  if (idp >= NextProductID)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  count = 0;
  most = -1;
  for (i = 0; i < NextOrderID; ++i)
  {
    for (j = 0; j < orderList[i].size; ++j)
    {
      if ((orderList[i].items[j].id == idp) && (orderList[i].items[j].quantity > count))
      {
        count = orderList[i].items[j].quantity;
        most = i;
        break;
      }
      else
      {
        
      }

    }

  }

  if (most != (-1))
  {
    printf("Maximo produto %d %d %d.\n", idp, most, count);
  }
  else
  {
    
  }

}

void mergeProducts(Product list[], Product temp[], int left, int middle, int right)
{
  int i;
  int j;
  int k;
  for (i = middle + 1; i > left; --i)
  {
    temp[i - 1] = list[i - 1];
  }

  for (j = middle; j < right; ++j)
  {
    temp[(right + middle) - j] = list[j + 1];
  }

  for (k = left; k <= right; ++k)
  {
    if ((temp[j].price < temp[i].price) || (i > middle))
    {
      list[k] = temp[j--];
    }
    else
    {
      list[k] = temp[i++];
    }

  }

}

void mergeOrder(Product list[], Product temp[], int left, int middle, int right)
{
  int i;
  int j;
  int k;
  for (i = middle + 1; i > left; --i)
  {
    temp[i - 1] = list[i - 1];
  }

  for (j = middle; j < right; ++j)
  {
    temp[(right + middle) - j] = list[j + 1];
  }

  for (k = left; k <= right; ++k)
  {
    if ((compareString(temp[j].description, temp[i].description) <= 0) || (i > middle))
    {
      list[k] = temp[j--];
    }
    else
    {
      list[k] = temp[i++];
    }

  }

}

void merge(Product list[], Product temp[], int left, int middle, int right, char option)
{
  if (option == 'p')
  {
    mergeProducts(list, temp, left, middle, right);
  }
  else
  {
    if (option == 'e')
    {
      mergeOrder(list, temp, left, middle, right);
    }
    else
    {
      
    }

  }

}

void mergeSort(Product list[], Product temp[], int left, int right, char option)
{
  int middle = (left + right) / 2;
  if (left >= right)
  {
    return;
  }
  else
  {
    
  }

  mergeSort(list, temp, left, middle, option);
  mergeSort(list, temp, middle + 1, right, option);
  merge(list, temp, left, middle, right, option);
}

void listAllProducts()
{
  Product list[10000];
  Product temp[10000];
  int i;
  for (i = 0; i < NextProductID; ++i)
  {
    list[i] = productList[i];
  }

  mergeSort(list, temp, 0, NextProductID - 1, 'p');
  printf("Produtos\n");
  for (i = 0; i < NextProductID; ++i)
  {
    printf("* %s %d %d\n", list[i].description, list[i].price, list[i].quantity);
  }

}

void listOrder(int ide)
{
  Product list[200];
  Product temp[200];
  int i;
  if (ide >= NextOrderID)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < orderList[ide].size; ++i)
  {
    list[i] = orderList[ide].items[i];
  }

  mergeSort(list, temp, 0, orderList[ide].size - 1, 'e');
  printf("Encomenda %d\n", ide);
  for (i = 0; i < orderList[ide].size; ++i)
  {
    if (list[i].quantity != 0)
    {
      printf("* %s %d %d\n", list[i].description, list[i].price, list[i].quantity);
    }
    else
    {
      
    }

  }

}

int main()
{
  char description[63];
  int idp;
  int ide;
  int price;
  int weight;
  int quantity;
  int i;
  char command;
  char c;
  NextProductID = 0;
  NextOrderID = 0;
  i = 0;
  command = getchar();
  while (command != 'x')
  {
    switch (command)
    {
      case 'a':
        getchar();
        while ((((c = getchar()) != ':') && (c != EOF)) && (i < 63))
      {
        description[i] = c;
        ++i;
      }

        description[i] = '\0';
        price = new_sym_var(sizeof(int) * 8);
        weight = new_sym_var(sizeof(int) * 8);
        quantity = new_sym_var(sizeof(int) * 8);
        newProduct(description, price, weight, quantity);
        break;

      case 'q':
        idp = new_sym_var(sizeof(int) * 8);
        quantity = new_sym_var(sizeof(int) * 8);
        addStock(idp, quantity);
        break;

      case 'N':
        addOrder();
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        quantity = new_sym_var(sizeof(int) * 8);
        addProduct(idp, ide, quantity);
        break;

      case 'r':
        idp = new_sym_var(sizeof(int) * 8);
        quantity = new_sym_var(sizeof(int) * 8);
        removeStock(idp, quantity);
        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        removeProduct(ide, idp);
        break;

      case 'C':
        ide = new_sym_var(sizeof(int) * 8);
        getOrderCost(ide);
        break;

      case 'p':
        idp = new_sym_var(sizeof(int) * 8);
        price = new_sym_var(sizeof(int) * 8);
        changePrice(idp, price);
        break;

      case 'E':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        listProduct(ide, idp);
        break;

      case 'm':
        idp = new_sym_var(sizeof(int) * 8);
        listOccurrences(idp);
        break;

      case 'l':
        listAllProducts();
        break;

      case 'L':
        ide = new_sym_var(sizeof(int) * 8);
        listOrder(ide);
        break;

      default:
        break;

    }

    command = getchar();
    i = 0;
  }

  return 0;
}

