#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct product
{
  int idp;
  char description[64];
  int price;
  int weight;
  int stock;
} product;
typedef struct order
{
  int ido;
  int weight;
  int number_prod;
  product prods[200];
} order;
void addProduct(char str[64], int p, int w, int qt);
void addStock(int idp, int qtd);
void createOrder();
void addProdOrder(int ido, int idp, int qt);
void removeStock(int idp, int qt);
void removeProdOrder(int ido, int idp);
void costOrder(int ido);
void changePrice(int ide, int p);
void productOrder(int ido, int ide);
void mostProdOrder(int idp);
void getAllProds();
void listOrder(int ido);
void readString(char desc[64]);
void copyString(char str1[64], char str2[64]);
void mergeSort(product arr[10000], int ido, int inf, int sup, int control);
void mergePrice(product arr[10000], int inf, int middle, int sup);
void mergeAlph(product arr[10000], int ido, int inf, int middle, int sup);
void swapProduct(product arr[10000], int i, int j);
void outputProduct(char str[64], int p, int qt);
int product_counter;
int order_counter;
product products[10000];
order orders[500];
int main()
{
  char ch;
  int price;
  int weight;
  int qt;
  int ido;
  int idp;
  char description[64] = {0};
  int not_finished = 1;
  while (not_finished)
  {
    switch (ch = getchar())
    {
      case 'a':
        readString(description);
        price = new_sym_var(sizeof(int) * 8);
        weight = new_sym_var(sizeof(int) * 8);
        qt = new_sym_var(sizeof(int) * 8);
        getchar();
        addProduct(description, price, weight, qt);
        break;

      case 'q':
        idp = new_sym_var(sizeof(int) * 8);
        qt = new_sym_var(sizeof(int) * 8);
        getchar();
        addStock(idp, qt);
        break;

      case 'N':
        createOrder();
        getchar();
        break;

      case 'A':
        ido = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        qt = new_sym_var(sizeof(int) * 8);
        getchar();
        addProdOrder(ido, idp, qt);
        break;

      case 'r':
        idp = new_sym_var(sizeof(int) * 8);
        qt = new_sym_var(sizeof(int) * 8);
        getchar();
        removeStock(idp, qt);
        break;

      case 'R':
        ido = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        getchar();
        removeProdOrder(ido, idp);
        break;

      case 'C':
        ido = new_sym_var(sizeof(int) * 8);
        getchar();
        costOrder(ido);
        break;

      case 'p':
        idp = new_sym_var(sizeof(int) * 8);
        price = new_sym_var(sizeof(int) * 8);
        getchar();
        changePrice(idp, price);
        break;

      case 'E':
        ido = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        getchar();
        productOrder(ido, idp);
        break;

      case 'm':
        idp = new_sym_var(sizeof(int) * 8);
        getchar();
        mostProdOrder(idp);
        break;

      case 'l':
        getAllProds();
        getchar();
        break;

      case 'L':
        ido = new_sym_var(sizeof(int) * 8);
        getchar();
        listOrder(ido);
        break;

      default:
        not_finished = 0;
        break;

    }

  }

  return 0;
}

void addProduct(char str[64], int p, int w, int qt)
{
  copyString(products[product_counter].description, str);
  products[product_counter].idp = product_counter;
  products[product_counter].price = p;
  products[product_counter].weight = w;
  products[product_counter].stock = qt;
  printf("Novo produto %d.\n", product_counter);
  product_counter++;
}

void addStock(int idp, int qt)
{
  if (idp >= product_counter)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    int i;
    for (i = 0; i < product_counter; i++)
    {
      if (products[i].idp == idp)
      {
        products[i].stock += qt;
        break;
      }
      else
      {
        
      }

    }

  }

}

void createOrder()
{
  orders[order_counter].ido = order_counter;
  printf("Nova encomenda %d.\n", order_counter);
  order_counter++;
}

void addProdOrder(int ido, int idp, int qt)
{
  if (ido >= order_counter)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
  }
  else
  {
    if (idp >= product_counter)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
    }
    else
    {
      int i;
      int pos;
      for (i = 0; i < 10000; i++)
      {
        if (products[i].idp == idp)
        {
          pos = i;
          break;
        }
        else
        {
          
        }

      }

      if (qt > products[pos].stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ido);
      }
      else
      {
        if (((qt * products[pos].weight) + orders[ido].weight) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ido);
        }
        else
        {
          int product_in = 0;
          for (i = 0; i < orders[ido].number_prod; i++)
          {
            if (orders[ido].prods[i].idp == idp)
            {
              orders[ido].prods[i].stock += qt;
              product_in = 1;
              break;
            }
            else
            {
              
            }

          }

          if (!product_in)
          {
            orders[ido].prods[orders[ido].number_prod] = products[pos];
            orders[ido].prods[orders[ido].number_prod].idp = idp;
            orders[ido].prods[orders[ido].number_prod].stock = qt;
            orders[ido].number_prod++;
          }
          else
          {
            
          }

          orders[ido].weight += qt * products[pos].weight;
          removeStock(idp, qt);
        }

      }

    }

  }

}

void removeStock(int idp, int qt)
{
  if (idp >= product_counter)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    int i;
    for (i = 0; i < product_counter; i++)
    {
      if (products[i].idp == idp)
      {
        if (qt > products[i].stock)
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qt, idp);
        }
        else
        {
          products[i].stock -= qt;
        }

        break;
      }
      else
      {
        
      }

    }

  }

}

void removeProdOrder(int ido, int idp)
{
  if (ido >= order_counter)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
  }
  else
  {
    if (idp >= product_counter)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
    }
    else
    {
      int i;
      for (i = 0; i < orders[ido].number_prod; i++)
      {
        if (orders[ido].prods[i].idp == idp)
        {
          orders[ido].weight -= orders[ido].prods[i].stock * orders[ido].prods[i].weight;
          addStock(idp, orders[ido].prods[i].stock);
          orders[ido].prods[i].stock = 0;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void costOrder(int ido)
{
  if (ido >= order_counter)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ido);
  }
  else
  {
    int value = 0;
    int i;
    for (i = 0; i < orders[ido].number_prod; i++)
      value += orders[ido].prods[i].stock * orders[ido].prods[i].price;

    printf("Custo da encomenda %d %d.\n", ido, value);
  }

}

void changePrice(int idp, int p)
{
  if (idp >= product_counter)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    int i;
    int j;
    for (i = 0; i < product_counter; i++)
    {
      if (products[i].idp == idp)
      {
        products[i].price = p;
        break;
      }
      else
      {
        
      }

    }

    for (i = 0; i < order_counter; i++)
    {
      for (j = 0; j < orders[i].number_prod; j++)
      {
        if (orders[i].prods[j].idp == idp)
        {
          orders[i].prods[j].price = p;
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void productOrder(int ido, int idp)
{
  if (ido >= order_counter)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
  }
  else
  {
    if (idp >= product_counter)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      int i;
      int quantity = 0;
      for (i = 0; i < orders[ido].number_prod; i++)
      {
        if (orders[ido].prods[i].idp == idp)
        {
          quantity = orders[ido].prods[i].stock;
          break;
        }
        else
        {
          
        }

      }

      for (i = 0; i < product_counter; i++)
      {
        if (products[i].idp == idp)
        {
          printf("%s", products[i].description);
          printf(" %d.\n", quantity);
          break;
        }
        else
        {
          
        }

      }

    }

  }

}

void mostProdOrder(int idp)
{
  if (idp >= product_counter)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (order_counter == 0)
    {
      ;
    }
    else
    {
      int i;
      int j;
      int prod_exists = 0;
      int max = 0;
      int max_order = 0;
      for (i = 0; i < order_counter; i++)
      {
        for (j = 0; j < orders[i].number_prod; j++)
        {
          if (orders[i].prods[j].idp == idp)
          {
            if (orders[i].prods[j].stock > max)
            {
              prod_exists = 1;
              max = orders[i].prods[j].stock;
              max_order = i;
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

      if (prod_exists)
      {
        printf("Maximo produto %d %d %d.\n", idp, max_order, max);
      }
      else
      {
        
      }

    }

  }

}

void getAllProds()
{
  int i;
  product aux[10000];
  if (product_counter > 1)
  {
    mergeSort(aux, 0, 0, product_counter - 1, 1);
  }
  else
  {
    
  }

  printf("Produtos\n");
  for (i = 0; i < product_counter; i++)
  {
    putchar('*');
    putchar(' ');
    outputProduct(products[i].description, products[i].price, products[i].stock);
  }

}

void listOrder(int ido)
{
  if (ido >= order_counter)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
  }
  else
  {
    if (order_counter == 0)
    {
      printf("Encomenda %d\n", ido);
    }
    else
    {
      int i;
      product aux[10000];
      if (orders[ido].number_prod > 1)
      {
        mergeSort(aux, ido, 0, orders[ido].number_prod - 1, 2);
      }
      else
      {
        
      }

      printf("Encomenda %d\n", ido);
      for (i = 0; i < orders[ido].number_prod; i++)
      {
        if (orders[ido].prods[i].stock != 0)
        {
          putchar('*');
          putchar(' ');
          outputProduct(orders[ido].prods[i].description, orders[ido].prods[i].price, orders[ido].prods[i].stock);
        }
        else
        {
          
        }

      }

    }

  }

}

void readString(char desc[64])
{
  int i;
  int ch;
  getchar();
  for (i = 0; (ch = getchar()) != ':'; i++)
    desc[i] = ch;

  desc[i] = '\0';
}

void copyString(char str1[64], char str2[64])
{
  int j;
  for (j = 0; str2[j] != '\0'; j++)
    str1[j] = str2[j];

  str1[j] = '\0';
}

void mergeSort(product arr[10000], int ido, int inf, int sup, int control)
{
  int middle = (inf + sup) / 2;
  if (sup <= inf)
  {
    return;
  }
  else
  {
    
  }

  mergeSort(arr, ido, inf, middle, control);
  mergeSort(arr, ido, middle + 1, sup, control);
  if (control == 1)
  {
    mergePrice(arr, inf, middle, sup);
  }
  else
  {
    if (control == 2)
    {
      mergeAlph(arr, ido, inf, middle, sup);
    }
    else
    {
      
    }

  }

}

void mergePrice(product arr[10000], int inf, int middle, int sup)
{
  int i;
  int j;
  int k;
  for (i = middle + 1; i > inf; i--)
    arr[i - 1] = products[i - 1];

  for (j = middle; j < sup; j++)
    arr[(sup + middle) - j] = products[j + 1];

  for (k = inf; k <= sup; k++)
  {
    if ((arr[j].price < arr[i].price) || (i > middle))
    {
      products[k] = arr[j--];
    }
    else
    {
      if (arr[j].price == arr[i].price)
      {
        if (arr[j].idp < arr[i].idp)
        {
          products[k] = arr[j--];
        }
        else
        {
          products[k] = arr[i++];
        }

      }
      else
      {
        products[k] = arr[i++];
      }

    }

  }

}

void mergeAlph(product arr[10000], int ido, int inf, int middle, int sup)
{
  int i;
  int j;
  int k;
  for (i = middle + 1; i > inf; i--)
    arr[i - 1] = orders[ido].prods[i - 1];

  for (j = middle; j < sup; j++)
    arr[(sup + middle) - j] = orders[ido].prods[j + 1];

  for (k = inf; k <= sup; k++)
  {
    if ((strcmp(arr[j].description, arr[i].description) < 0) || (i > middle))
    {
      orders[ido].prods[k] = arr[j--];
    }
    else
    {
      orders[ido].prods[k] = arr[i++];
    }

  }

}

void swapProduct(product arr[10000], int i, int j)
{
  product temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void outputProduct(char str[64], int p, int qt)
{
  printf("%s %d %d\n", str, p, qt);
}

