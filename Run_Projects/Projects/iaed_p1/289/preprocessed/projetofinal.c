/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct product
{
  int id;
  char description[64];
  int price;
  int weight;
  int stock;
} Product;
typedef struct orderProduct
{
  Product *product;
  int quantity;
} OrderProduct;
typedef struct order
{
  int id;
  int weight;
  int numProducts;
  OrderProduct products[200];
} Order;
void orderProductsMerge(Product products[], int left, int right, int middle)
{
  int size_of_ord1;
  int size_of_ord2;
  int i;
  int j;
  int k;
  Product ord1[10000 / 2];
  Product ord2[10000 / 2];
  size_of_ord1 = (middle - left) + 1;
  size_of_ord2 = right - middle;
  for (i = 0; i < size_of_ord1; i++)
  {
    ord1[i] = products[left + i];
  }

  for (i = 0; i < size_of_ord2; i++)
  {
    ord2[i] = products[(middle + 1) + i];
  }

  i = 0;
  j = 0;
  k = left;
  while ((i < size_of_ord1) && (j < size_of_ord2))
  {
    if (ord1[i].price < ord2[j].price)
    {
      products[k] = ord1[i];
      i++;
    }
    else
    {
      if (ord2[j].price < ord1[i].price)
      {
        products[k] = ord2[j];
        j++;
      }
      else
      {
        
      }

    }

    k++;
  }

  while (i < size_of_ord1)
  {
    products[k] = ord1[i];
    k++;
    i++;
  }

  while (j < size_of_ord2)
  {
    products[k] = ord2[j];
    k++;
    j++;
  }

}

void orderProductsMS(Product products[], int left, int right)
{
  if (left < right)
  {
    int middle = (left + right) / 2;
    orderProductsMS(products, left, middle);
    orderProductsMS(products, middle + 1, right);
    orderProductsMerge(products, left, right, middle);
  }
  else
  {
    
  }

}

void swap(OrderProduct *a, OrderProduct *b)
{
  OrderProduct t = *a;
  *a = *b;
  *b = t;
}

int partition(OrderProduct orderProducts[], int low, int high)
{
  OrderProduct pivot = orderProducts[high];
  int i = low - 1;
  int j;
  for (j = low; j <= (high - 1); j++)
  {
    if (strcmp(orderProducts[j].product->description, pivot.product->description) < 0)
    {
      i++;
      swap(&orderProducts[i], &orderProducts[j]);
    }
    else
    {
      
    }

  }

  swap(&orderProducts[i + 1], &orderProducts[high]);
  return i + 1;
}

void orderOrderProductsMS(OrderProduct orderProducts[], int low, int high)
{
  if (low < high)
  {
    int pi = partition(orderProducts, low, high);
    orderOrderProductsMS(orderProducts, low, pi - 1);
    orderOrderProductsMS(orderProducts, pi + 1, high);
  }
  else
  {
    
  }

}

void readDescription(char str[64])
{
  int i = 0;
  int ch;
  getchar();
  while (((ch = getchar()) != ':') && (ch != EOF))
  {
    if (i < 64)
    {
      str[i++] = ch;
    }
    else
    {
      
    }

  }

  str[i] = '\0';
}

void addProduct(Product products[10000], int id)
{
  products[id].id = id;
  readDescription(products[id].description);
  products[id].price = new_sym_var(sizeof(int) * 8);
  products[id].weight = new_sym_var(sizeof(int) * 8);
  products[id].stock = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", id);
}

void listProduct(Product products[10000], int numProducts)
{
  int i;
  orderProductsMS(products, 0, numProducts - 1);
  printf("Produtos\n");
  for (i = 0; i < numProducts; i++)
  {
    printf("* %s %d %d\n", products[i].description, products[i].price, products[i].stock);
  }

}

void addStock(Product products[10000], int numProducts)
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((id >= numProducts) || (id < 0))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
  }
  else
  {
    products[id].stock = products[id].stock + qtd;
  }

}

void removeStock(Product products[10000], int numProducts)
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((id >= numProducts) || (id < 0))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
  }
  else
  {
    if (products[id].stock < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
    }
    else
    {
      products[id].stock = products[id].stock - qtd;
    }

  }

}

void changePrice(Product products[10000], int numProducts)
{
  int id;
  int price;
  id = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if ((id >= numProducts) || (id < 0))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
  }
  else
  {
    products[id].price = price;
  }

}

void newOrder(Order orders[500], int id)
{
  orders[id].id = id;
  orders[id].weight = 0;
  orders[id].numProducts = 0;
  printf("Nova encomenda %d.\n", id);
}

void listOrderAll(Order orders[500], int numOrders)
{
  int i;
  printf("Ecomendas\n");
  for (i = 0; i < numOrders; i++)
  {
    printf("* %d %d\n", orders[i].id, orders[i].weight);
  }

}

void listOrder(Order orders[500], int numOrders)
{
  int id;
  id = new_sym_var(sizeof(int) * 8);
  if ((id >= numOrders) || (id < 0))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id);
  }
  else
  {
    int i;
    orderOrderProductsMS(orders[id].products, 0, orders[id].numProducts - 1);
    printf("Encomenda %d\n", id);
    for (i = 0; i < orders[id].numProducts; i++)
    {
      printf("* %s %d %d\n", orders[id].products[i].product->description, orders[id].products[i].product->price, orders[id].products[i].quantity);
    }

  }

}

void addProductToOrder(Order orders[500], int numOrders, Product products[10000], int numProducts)
{
  int idOrder;
  int idProd;
  int qtd;
  int orderProdId = -1;
  idOrder = new_sym_var(sizeof(int) * 8);
  idProd = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if ((idOrder >= numOrders) || (idOrder < 0))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idProd, idOrder);
  }
  else
  {
    if ((idProd >= numProducts) || (idProd < 0))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idProd, idOrder);
    }
    else
    {
      if (products[idProd].stock < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idProd, idOrder);
      }
      else
      {
        if ((orders[idOrder].weight + (products[idProd].weight * qtd)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idProd, idOrder, 200);
        }
        else
        {
          int i;
          for (i = 0; i < orders[idOrder].numProducts; i++)
          {
            if (orders[idOrder].products[i].product->id == idProd)
            {
              orderProdId = i;
              break;
            }
            else
            {
              
            }

          }

          if (orderProdId != (-1))
          {
            orders[idOrder].products[orderProdId].quantity += qtd;
            orders[idOrder].weight += products[idProd].weight * qtd;
          }
          else
          {
            orders[idOrder].weight += products[idProd].weight * qtd;
            orderProdId = orders[idOrder].numProducts;
            orders[idOrder].numProducts++;
            orders[idOrder].products[orderProdId].quantity = qtd;
            orders[idOrder].products[orderProdId].product = &products[idProd];
          }

          products[idProd].stock -= qtd;
        }

      }

    }

  }

}

void removeProductFromOrder(Order orders[500], int numOrders, int numProducts)
{
  int idOrder;
  int idProd;
  int orderProdId = -1;
  Product *p;
  OrderProduct tmp;
  idOrder = new_sym_var(sizeof(int) * 8);
  idProd = new_sym_var(sizeof(int) * 8);
  if ((idOrder >= numOrders) || (idOrder < 0))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idProd, idOrder);
  }
  else
  {
    if ((idProd >= numProducts) || (idProd < 0))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idProd, idOrder);
    }
    else
    {
      int i;
      for (i = 0; i < orders[idOrder].numProducts; i++)
      {
        if (orders[idOrder].products[i].product->id == idProd)
        {
          orderProdId = i;
          break;
        }
        else
        {
          
        }

      }

      if (orderProdId != (-1))
      {
        p = orders[idOrder].products[orderProdId].product;
        p->stock += orders[idOrder].products[orderProdId].quantity;
        orders[idOrder].weight -= p->weight * orders[idOrder].products[orderProdId].quantity;
        orders[idOrder].numProducts--;
        tmp = orders[idOrder].products[orders[idOrder].numProducts];
        orders[idOrder].products[orders[idOrder].numProducts] = orders[idOrder].products[orderProdId];
        orders[idOrder].products[orderProdId] = tmp;
      }
      else
      {
        
      }

    }

  }

}

void totalOrderPrice(Order orders[500], int numOrders)
{
  int idOrder;
  int i;
  int orderPrice = 0;
  idOrder = new_sym_var(sizeof(int) * 8);
  if ((idOrder >= numOrders) || (idOrder < 0))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idOrder);
  }
  else
  {
    for (i = 0; i < orders[idOrder].numProducts; i++)
    {
      orderPrice += orders[idOrder].products[i].product->price * orders[idOrder].products[i].quantity;
    }

    printf("Custo da encomenda %d %d.\n", idOrder, orderPrice);
  }

}

void listProductInOrder(Order orders[500], int numOrders, Product products[10000], int numProducts)
{
  int idOrder;
  int idProd;
  int i;
  idOrder = new_sym_var(sizeof(int) * 8);
  idProd = new_sym_var(sizeof(int) * 8);
  if ((idOrder >= numOrders) || (idOrder < 0))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idOrder);
  }
  else
  {
    if ((idProd >= numProducts) || (idProd < 0))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idProd);
    }
    else
    {
      for (i = 0; i < orders[idOrder].numProducts; i++)
      {
        if (orders[idOrder].products[i].product->id == idProd)
        {
          printf("%s %d.\n", orders[idOrder].products[i].product->description, orders[idOrder].products[i].quantity);
          break;
        }
        else
        {
          
        }

      }

      if (i >= orders[idOrder].numProducts)
      {
        printf("%s %d.\n", products[idProd].description, 0);
      }
      else
      {
        
      }

    }

  }

}

void searchProductInOrder(Order orders[500], int numOrders, int numProducts)
{
  int idProd;
  int idOrder;
  int i;
  int bOrder = -1;
  int bOrderAmount = -1;
  idProd = new_sym_var(sizeof(int) * 8);
  if ((idProd >= numProducts) || (idProd < 0))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idProd);
  }
  else
  {
    for (idOrder = 0; idOrder < numOrders; idOrder++)
    {
      for (i = 0; i < orders[idOrder].numProducts; i++)
      {
        if (orders[idOrder].products[i].product->id == idProd)
        {
          if (orders[idOrder].products[i].quantity > bOrderAmount)
          {
            bOrder = idOrder;
            bOrderAmount = orders[idOrder].products[i].quantity;
          }
          else
          {
            
          }

          break;
        }
        else
        {
          
        }

      }

    }

    if (bOrder != (-1))
    {
      printf("Maximo produto %d %d %d.\n", idProd, bOrder, bOrderAmount);
    }
    else
    {
      
    }

  }

}

int main()
{
  char command;
  int numProd = 0;
  int numOrder = 0;
  Product products[10000];
  Order orders[500];
  while (command = getchar())
  {
    switch (command)
    {
      case 'a':
        addProduct(products, numProd++);
        break;

      case 'q':
        addStock(products, numProd);
        break;

      case 'r':
        removeStock(products, numProd);
        break;

      case 'l':
        listProduct(products, numProd);
        break;

      case 'p':
        changePrice(products, numProd);
        break;

      case 'N':
        newOrder(orders, numOrder++);
        break;

      case 'L':
        listOrder(orders, numOrder);
        break;

      case 'U':
        listOrderAll(orders, numOrder);
        break;

      case 'A':
        addProductToOrder(orders, numOrder, products, numProd);
        break;

      case 'E':
        listProductInOrder(orders, numOrder, products, numProd);
        break;

      case 'm':
        searchProductInOrder(orders, numOrder, numProd);
        break;

      case 'C':
        totalOrderPrice(orders, numOrder);
        break;

      case 'R':
        removeProductFromOrder(orders, numOrder, numProd);
        break;

      case 'x':
        return 0;

      default:
        printf("I do not know the command '%c'.\n", command);

    }

    getchar();
  }

  return -1;
}

