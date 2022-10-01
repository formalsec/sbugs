/*File generated by PreProcessor.py*/


#include <stdio.h>


typedef struct 
{
  char description[64];
  unsigned int price;
  unsigned int weight;
  unsigned int ordernumber;
  int stock;
  int ordersList[500];
} product;
int StockOperation(product v[], int id, int qtd)
{
  int aux;
  aux = v[id].stock + qtd;
  return aux;
}

typedef struct 
{
  unsigned int NumberOfProducts;
  int list[10000];
  int idpQty[10000];
} order;
unsigned int numberProducts;
unsigned int numberOrders;
order ido[500];
product idp[10000];
enum option
{
  WEIGHT,
  PRICE,
  ALPHABETICAL
};
int x[10000];
void merge(int a[], int start, int end, int option)
{
  int mid = (start + end) / 2;
  int i = start;
  int j = mid + 1;
  int k = start;
  int aux[10000];
  if (option == ALPHABETICAL)
  {
    int c = 0;
    while ((i <= mid) && (j <= end))
    {
      if (idp[a[i]].description[c] < idp[a[j]].description[c])
      {
        aux[k++] = a[i++];
        c = 0;
      }
      else
      {
        if (idp[a[i]].description[c] > idp[a[j]].description[c])
        {
          aux[k++] = a[j++];
          c = 0;
        }
        else
        {
          c++;
        }

      }

    }

  }
  else
  {
    if (option == PRICE)
    {
      while ((i <= mid) && (j <= end))
      {
        if (idp[a[i]].price < idp[a[j]].price)
        {
          aux[k++] = a[i++];
        }
        else
        {
          if (idp[a[i]].price > idp[a[j]].price)
          {
            aux[k++] = a[j++];
          }
          else
          {
            if (a[i] < a[j])
            {
              aux[k++] = a[i++];
            }
            else
            {
              aux[k++] = a[j++];
            }

          }

        }

      }

    }
    else
    {
      
    }

  }

  while (i <= mid)
  {
    aux[k++] = a[i++];
  }

  while (j <= end)
  {
    aux[k++] = a[j++];
  }

  for (i = start; i <= end; i++)
  {
    a[i] = aux[i];
  }

}

void mergeSort(int a[], int start, int end, int option)
{
  int mid = (start + end) / 2;
  if (start < end)
  {
    mergeSort(a, start, mid, option);
    mergeSort(a, mid + 1, end, option);
    merge(a, start, end, option);
  }
  else
  {
    
  }

}

int NotValidID(unsigned short id, unsigned short MaxIdUsed)
{
  int result = 0;
  if (id >= MaxIdUsed)
  {
    result = 1;
  }
  else
  {
    
  }

  return result;
}

int PorductInOrder(unsigned short idorder, unsigned short idproduct)
{
  unsigned short result = 0;
  unsigned short i;
  for (i = 0; i < ido[idorder].NumberOfProducts; i++)
  {
    if (ido[idorder].list[i] == idproduct)
    {
      result = 1;
    }
    else
    {
      
    }

  }

  return result;
}

void CreatNewProduct(product idp[])
{
  if (numberProducts < 10000)
  {
    for (int idp_index = 0; idp_index < 10; idp_index++)
    {
      idp[numberProducts].description[idp_index] = new_sym_var(sizeof(char) * 8);
    }

    idp[numberProducts].description[10 - 1] = '\0';
    idp[numberProducts].price = new_sym_var(sizeof(unsigned int) * 8);
    idp[numberProducts].weight = new_sym_var(sizeof(unsigned int) * 8);
    idp[numberProducts].stock = new_sym_var(sizeof(int) * 8);
    printf("Novo produto %u.\n", numberProducts);
    x[numberProducts] = numberProducts;
    numberProducts++;
  }
  else
  {
    
  }

}

int QtyAlreadyOrded(int idproduct)
{
  unsigned int i;
  int Qty = 0;
  for (i = 0; i < idp[idproduct].ordernumber; i++)
  {
    Qty += ido[idp[idproduct].ordersList[i]].idpQty[idproduct];
  }

  return Qty;
}

void RemoveStock(product idp[])
{
  unsigned int id = 0;
  int qtd = 0;
  id = new_sym_var(sizeof(unsigned int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (NotValidID(id, numberProducts))
  {
    printf("Impossivel remover stock do produto %u. Produto inexistente.\n", id);
  }
  else
  {
    if ((StockOperation(idp, id, -qtd) - QtyAlreadyOrded(id)) < 0)
    {
      printf("Impossivel remover %d unidades do produto %u do stock. Quantidade insuficiente.\n", qtd, id);
    }
    else
    {
      idp[id].stock = StockOperation(idp, id, -qtd);
    }

  }

}

void AddStock(product idp[])
{
  unsigned int id = 0;
  int qtd = 0;
  id = new_sym_var(sizeof(unsigned int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (NotValidID(id, numberProducts))
  {
    printf("Impossivel adicionar produto %u ao stock. Produto inexistente.\n", id);
  }
  else
  {
    idp[id].stock = StockOperation(idp, id, qtd);
  }

}

void CreatNewOrder()
{
  if (numberOrders < 500)
  {
    printf("Nova encomenda %u.\n", numberOrders);
    numberOrders++;
  }
  else
  {
    
  }

}

int WPCalculation(int idorder, int option)
{
  unsigned int i;
  unsigned int result = 0;
  if (option == WEIGHT)
  {
    for (i = 0; i < ido[idorder].NumberOfProducts; i++)
    {
      result += ido[idorder].idpQty[ido[idorder].list[i]] * idp[ido[idorder].list[i]].weight;
    }

  }
  else
  {
    if (option == PRICE)
    {
      for (i = 0; i < ido[idorder].NumberOfProducts; i++)
      {
        result += ido[idorder].idpQty[ido[idorder].list[i]] * idp[ido[idorder].list[i]].price;
      }

    }
    else
    {
      
    }

  }

  return result;
}

void RemoveProduct()
{
  unsigned int i;
  unsigned int remove = 0;
  int idorder;
  int idproduct;
  idorder = new_sym_var(sizeof(int) * 8);
  idproduct = new_sym_var(sizeof(int) * 8);
  if (NotValidID(idorder, numberOrders))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idproduct, idorder);
  }
  else
  {
    if (NotValidID(idproduct, numberProducts))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idproduct, idorder);
    }
    else
    {
      if (PorductInOrder(idorder, idproduct))
      {
        for (i = 0; i < ido[idorder].NumberOfProducts; i++)
        {
          if (idproduct == ido[idorder].list[i])
          {
            ido[idorder].idpQty[ido[idorder].list[i]] = 0;
            ido[idorder].list[i] = 0;
            remove = 1;
          }
          else
          {
            if (remove == 1)
            {
              ido[idorder].list[i - 1] = ido[idorder].list[i];
            }
            else
            {
              
            }

          }

        }

        remove = 0;
        for (i = 0; i < idp[idproduct].ordernumber; i++)
        {
          if (idp[idproduct].ordersList[i] == idorder)
          {
            idp[idproduct].ordersList[i] = 0;
            remove = 1;
          }
          else
          {
            if (remove == 1)
            {
              idp[idproduct].ordersList[i - 1] = idp[idproduct].ordersList[i];
            }
            else
            {
              
            }

          }

        }

        ido[idorder].NumberOfProducts--;
        idp[idproduct].ordernumber--;
      }
      else
      {
        
      }

    }

  }

}

void OrderaProduct()
{
  int idproduct;
  int idorder;
  int qty;
  idorder = new_sym_var(sizeof(int) * 8);
  idproduct = new_sym_var(sizeof(int) * 8);
  qty = new_sym_var(sizeof(int) * 8);
  if (NotValidID(idorder, numberOrders))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idproduct, idorder);
  }
  else
  {
    if (NotValidID(idproduct, numberProducts))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idproduct, idorder);
    }
    else
    {
      if ((qty + QtyAlreadyOrded(idproduct)) > idp[idproduct].stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idproduct, idorder);
      }
      else
      {
        if ((WPCalculation(idorder, WEIGHT) + (qty * idp[idproduct].weight)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idproduct, idorder);
        }
        else
        {
          if (ido[idorder].idpQty[idproduct] > 0)
          {
            ido[idorder].idpQty[idproduct] += qty;
          }
          else
          {
            if (qty > 0)
            {
              ido[idorder].list[ido[idorder].NumberOfProducts] = idproduct;
              ido[idorder].idpQty[idproduct] += qty;
              ido[idorder].NumberOfProducts++;
              idp[idproduct].ordersList[idp[idproduct].ordernumber] = idorder;
              idp[idproduct].ordernumber++;
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

void PriceCalculator()
{
  int idorder;
  idorder = new_sym_var(sizeof(int) * 8);
  if (NotValidID(idorder, numberOrders))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idorder);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", idorder, WPCalculation(idorder, PRICE));
  }

}

void ChangePrice()
{
  int idproduct;
  int Price;
  idproduct = new_sym_var(sizeof(int) * 8);
  Price = new_sym_var(sizeof(int) * 8);
  if (NotValidID(idproduct, numberProducts))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idproduct);
  }
  else
  {
    idp[idproduct].price = Price;
  }

}

void ProductQtyOrder()
{
  int idorder;
  int idproduct;
  idorder = new_sym_var(sizeof(int) * 8);
  idproduct = new_sym_var(sizeof(int) * 8);
  if (NotValidID(idorder, numberOrders))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idorder);
  }
  else
  {
    if (NotValidID(idproduct, numberProducts))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idproduct);
    }
    else
    {
      printf("%s %d.\n", idp[idproduct].description, ido[idorder].idpQty[idproduct]);
    }

  }

}

void MaxProduct()
{
  unsigned int idproduct = 0;
  unsigned int i = 0;
  unsigned int aux = 0;
  idproduct = new_sym_var(sizeof(unsigned int) * 8);
  if (NotValidID(idproduct, numberProducts))
  {
    printf("Impossivel listar maximo do produto %u. Produto inexistente.\n", idproduct);
  }
  else
  {
    
  }

  if (idp[idproduct].ordernumber != 0)
  {
    for (i = 0; i < idp[idproduct].ordernumber; i++)
    {
      if (ido[idp[idproduct].ordersList[i]].idpQty[idproduct] > ido[idp[idproduct].ordersList[aux]].idpQty[idproduct])
      {
        aux = i;
      }
      else
      {
        if ((ido[idp[idproduct].ordersList[i]].idpQty[idproduct] == ido[idp[idproduct].ordersList[aux]].idpQty[idproduct]) && (idp[idproduct].ordersList[i] < idp[idproduct].ordersList[aux]))
        {
          aux = i;
        }
        else
        {
          
        }

      }

    }

    printf("Maximo produto %u %d %d.\n", idproduct, idp[idproduct].ordersList[aux], ido[idp[idproduct].ordersList[aux]].idpQty[idproduct]);
  }
  else
  {
    
  }

}

void PriceOrder()
{
  unsigned int loop;
  mergeSort(x, 0, numberProducts - 1, PRICE);
  printf("Produtos\n");
  for (loop = 0; loop < numberProducts; loop++)
    printf("* %s %u %d\n", idp[x[loop]].description, idp[x[loop]].price, idp[x[loop]].stock - QtyAlreadyOrded(x[loop]));

}

void AlphabeticalOrder()
{
  unsigned short idorder;
  unsigned short loop;
  idorder = new_sym_var(sizeof(unsigned short) * 8);
  mergeSort(ido[idorder].list, 0, ido[idorder].NumberOfProducts - 1, ALPHABETICAL);
  if (NotValidID(idorder, numberOrders))
  {
    printf("Impossivel listar encomenda %hu. Encomenda inexistente.\n", idorder);
  }
  else
  {
    printf("Encomenda %u\n", idorder);
    if (ido[idorder].NumberOfProducts > 0)
    {
      for (loop = 0; loop < ido[idorder].NumberOfProducts; loop++)
      {
        printf("* %s %u %d\n", idp[ido[idorder].list[loop]].description, idp[ido[idorder].list[loop]].price, ido[idorder].idpQty[ido[idorder].list[loop]]);
      }

    }
    else
    {
      
    }

  }

}

int main()
{
  char command;
  while ((command = getchar()) != 'x')
  {
    switch (command)
    {
      case 'a':
        CreatNewProduct(idp);
        break;

      case 'q':
        AddStock(idp);
        break;

      case 'N':
        CreatNewOrder();
        break;

      case 'A':
        OrderaProduct();
        break;

      case 'r':
        RemoveStock(idp);
        break;

      case 'R':
        RemoveProduct();
        break;

      case 'C':
        PriceCalculator();
        break;

      case 'p':
        ChangePrice();
        break;

      case 'E':
        ProductQtyOrder();
        break;

      case 'm':
        MaxProduct();
        break;

      case 'l':
        PriceOrder();
        break;

      case 'L':
        AlphabeticalOrder();
        break;

    }

    getchar();
  }

  return 0;
}
