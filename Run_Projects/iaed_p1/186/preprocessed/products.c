/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include "products.h"
#include "packages.h"


Product products[10000] = {0};
int productCount = 0;
void getStringArgument(char s[], int maxSize)
{
  int position = 0;
  int c = getchar();
  while ((((c != EOF) && (c != ':')) && (c != '\n')) && (position < (maxSize - 1)))
  {
    s[position] = c;
    position++;
    c = getchar();
  }

  s[position] = '\0';
}

int productExists(int idp)
{
  return (idp >= 0) && (idp < productCount);
}

int partition(Product products[], int left, int right)
{
  Product pivot = products[right];
  int i = left - 1;
  int j;
  Product holder;
  for (j = left; j <= (right - 1); j++)
    if ((products[j].price < pivot.price) || ((products[j].price == pivot.price) && (products[j].id < pivot.id)))
  {
    {
      i++;
      if (i != j)
      {
        {
          holder = products[i];
          products[i] = products[j];
          products[j] = holder;
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


  i++;
  holder = products[i];
  products[i] = products[j];
  products[j] = holder;
  return i;
}

void sortProductsByPrice(Product products[], int left, int right)
{
  int pivot;
  if (left < right)
  {
    {
      pivot = partition(products, left, right);
      sortProductsByPrice(products, left, pivot - 1);
      sortProductsByPrice(products, pivot + 1, right);
    }
  }
  else
  {
    
  }

}

void addProductCmd()
{
  Product newProduct;
  getchar();
  getStringArgument(newProduct.description, 64);
  newProduct.price = new_sym_var(sizeof(int) * 8);
  newProduct.weight = new_sym_var(sizeof(int) * 8);
  newProduct.quantity = new_sym_var(sizeof(int) * 8);
  newProduct.id = productCount++;
  newProduct.alive = 1;
  products[newProduct.id] = newProduct;
  printf("Novo produto %d.\n", newProduct.id);
}

void addStockCmd()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (!productExists(idp))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    products[idp].quantity += qtd;
  }

}

void removeStockCmd()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (!productExists(idp))
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
      products[idp].quantity -= qtd;
    }

  }

}

void changePriceCmd()
{
  int idp;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (!productExists(idp))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    products[idp].price = preco;
  }

}

void biggestOccurrenceCmd()
{
  int idp;
  int ide;
  int qtd = 0;
  int i;
  int j;
  idp = new_sym_var(sizeof(int) * 8);
  if (!productExists(idp))
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      for (j = 0; j < packageCount; j++)
        for (i = 0; (i < 200) && packages[j][i].alive; i++)
        if (packages[j][i].id == idp)
      {
        {
          if (packages[j][i].quantity > qtd)
          {
            {
              qtd = packages[j][i].quantity;
              ide = j;
            }
          }
          else
          {
            
          }

          break;
        }
      }
      else
      {
        
      }



      if (qtd > 0)
      {
        printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
      }
      else
      {
        
      }

    }
  }

}

void listAllProductsCmd()
{
  Product productsCopy[10000];
  int i;
  memcpy(&productsCopy, &products, sizeof(products));
  sortProductsByPrice(productsCopy, 0, productCount - 1);
  printf("Produtos\n");
  for (i = 0; i < productCount; i++)
    printf("* %s %d %d\n", productsCopy[i].description, productsCopy[i].price, productsCopy[i].quantity);

}

void listAllProductsIDCmd()
{
  int i;
  printf("Produtos\n%-4s %-5s %-4s %-10s %s\n", "ID", "Preco", "Peso", "Quantidade", "Descricao");
  for (i = 0; i < productCount; i++)
    printf("%-4d %-5d %-4d %-10d %s\n", products[i].id, products[i].price, products[i].weight, products[i].quantity, products[i].description);

}

