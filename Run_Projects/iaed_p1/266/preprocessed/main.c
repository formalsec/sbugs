/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct product
{
  int id;
  char desc[63];
  int *price;
  int weight;
  int qtd;
} product;
typedef struct order
{
  int id;
  int iter;
  product products[200];
} order;
int in_order(product products[], int idp, int iter)
{
  int i;
  for (i = 0; i < iter; ++i)
  {
    if (products[i].id == idp)
    {
      {
        if ((idp == 0) && (products[i].weight == 0))
        {
          {
            return -1;
          }
        }
        else
        {
          
        }

        return i;
      }
    }
    else
    {
      
    }

  }

  return -1;
}

void merge(product arr[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  product *L = (product *) malloc(n1 * (sizeof(product)));
  product *R = (product *) malloc(n2 * (sizeof(product)));
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];

  for (j = 0; j < n2; j++)
    R[j] = arr[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if ((*L[i].price) < (*R[j].price))
    {
      {
        arr[k] = L[i];
        i++;
      }
    }
    else
    {
      if (((*L[i].price) == (*R[j].price)) && (L[i].id < R[j].id))
      {
        {
          arr[k] = L[i];
          i++;
        }
      }
      else
      {
        {
          arr[k] = R[j];
          j++;
        }
      }

    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

  free(L);
  free(R);
}

void merge_sort(product arr[], int l, int r)
{
  if (l < r)
  {
    {
      int m = l + ((r - l) / 2);
      merge_sort(arr, l, m);
      merge_sort(arr, m + 1, r);
      merge(arr, l, m, r);
    }
  }
  else
  {
    
  }

}

void system_sort(product system[], int size)
{
  int i;
  product *copy = (product *) malloc(size * (sizeof(product)));
  for (i = 0; i < size; ++i)
  {
    copy[i] = system[i];
  }

  merge_sort(copy, 0, size - 1);
  printf("Produtos\n");
  for (i = 0; i < size; ++i)
  {
    printf("* %s %d %d\n", copy[i].desc, *copy[i].price, copy[i].qtd);
  }

  free(copy);
}

void swap(product *p1, product *p2)
{
  product aux = *p1;
  *p1 = *p2;
  *p2 = aux;
  return;
}

void alphabetic_sort(product products[], int size, int ide)
{
  int i;
  int j;
  product *copy = (product *) malloc(size * (sizeof(product)));
  for (i = 0; i < size; ++i)
  {
    copy[i] = products[i];
  }

  for (i = 0; i < (size - 1); i++)
  {
    for (j = i + 1; j < size; j++)
    {
      if (strcmp(copy[i].desc, copy[j].desc) > 0)
      {
        {
          swap(&copy[i], &copy[j]);
        }
      }
      else
      {
        
      }

    }

  }

  printf("Encomenda %d\n", ide);
  for (i = 0; i < size; ++i)
  {
    if (copy[i].qtd != 0)
    {
      printf("* %s %d %d\n", copy[i].desc, *copy[i].price, copy[i].qtd);
    }
    else
    {
      
    }

  }

  free(copy);
}

int main()
{
  char input[80];
  product p;
  product *system = (product *) malloc(10000 * (sizeof(product)));
  order o;
  order *orders = (order *) malloc(500 * (sizeof(order)));
  int product_counter;
  int order_counter;
  int ide;
  int idp;
  int qtd;
  int price;
  int weight;
  int i;
  int product_index;
  product_counter = 0;
  order_counter = 0;
  while (1)
  {
    fgets(input, 80, stdin);
    switch (input[0])
    {
      case 'a':
        ;
        printf("Novo produto %d.\n", product_counter);
        p.price = (int *) malloc(sizeof(int));
        input[0] = ' ';
        for (i = 0; i < 80; ++i)
        if (input[i] == ':')
      {
        input[i] = ' ';
      }
      else
      {
        
      }


        for (int p_index = 0; p_index < 10; p_index++)
      {
        p.desc[p_index] = new_sym_var(sizeof(char) * 8);
      }

        p.desc[10 - 1] = '\0';
        for (int p_index = 0; p_index < 10; p_index++)
      {
        p.price[p_index] = new_sym_var(sizeof(int) * 8);
      }

        p.weight = new_sym_var(sizeof(int) * 8);
        p.qtd = new_sym_var(sizeof(int) * 8);
        p.id = product_counter;
        system[product_counter] = p;
        product_counter++;
        break;

      case 'q':
        ;
        input[0] = ' ';
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        if ((product_counter - idp) <= 0)
      {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
      }
      else
      {
        system[idp].qtd = system[idp].qtd + qtd;
      }

        break;

      case 'r':
        ;
        input[0] = ' ';
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        if ((product_counter - idp) <= 0)
      {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        if ((system[idp].qtd - qtd) < 0)
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
        else
        {
          system[idp].qtd = system[idp].qtd - qtd;
        }

      }

        break;

      case 'p':
        ;
        input[0] = ' ';
        idp = new_sym_var(sizeof(int) * 8);
        price = new_sym_var(sizeof(int) * 8);
        if ((product_counter - idp) <= 0)
      {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        *system[idp].price = price;
      }

        break;

      case 'l':
        ;
        system_sort(system, product_counter);
        break;

      case 'm':
        ;
        input[0] = ' ';
        idp = new_sym_var(sizeof(int) * 8);
        if ((product_counter - idp) <= 0)
      {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        {
          int orid;
          int prid;
          qtd = -1;
          for (orid = 0; orid < order_counter; ++orid)
          {
            o = orders[orid];
            for (prid = 0; prid < o.iter; ++prid)
            {
              if ((o.products[prid].id == idp) && (o.products[prid].qtd > qtd))
              {
                {
                  qtd = o.products[prid].qtd;
                  ide = o.id;
                }
              }
              else
              {
                
              }

            }

          }

          if (qtd != (-1))
          {
            {
              product_index = in_order(orders[ide].products, idp, orders[ide].iter);
              if (orders[ide].products[product_index].qtd != 0)
              {
                printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
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

        break;

      case 'N':
        ;
        o.iter = 0;
        o.id = order_counter;
        orders[order_counter] = o;
        printf("Nova encomenda %d.\n", order_counter);
        order_counter++;
        break;

      case 'A':
        ;
        input[0] = ' ';
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        qtd = new_sym_var(sizeof(int) * 8);
        if ((order_counter - ide) <= 0)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
          break;
        }
      }
      else
      {
        
      }

        weight = 0;
        for (i = 0; i < orders[ide].iter; ++i)
      {
        weight = (orders[ide].products[i].weight * orders[ide].products[i].qtd) + weight;
      }

        if ((product_counter - idp) <= 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
      else
      {
        if ((system[idp].qtd - qtd) < 0)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
        else
        {
          if ((weight + (system[idp].weight * qtd)) > 200)
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          }
          else
          {
            {
              product_index = in_order(orders[ide].products, idp, orders[ide].iter);
              if (product_index != (-1))
              {
                orders[ide].products[product_index].qtd = orders[ide].products[product_index].qtd + qtd;
              }
              else
              {
                {
                  p.id = idp;
                  strcpy(p.desc, system[idp].desc);
                  p.price = system[idp].price;
                  p.weight = system[idp].weight;
                  p.qtd = qtd;
                  orders[ide].products[orders[ide].iter] = p;
                  orders[ide].iter++;
                }
              }

              system[idp].qtd = system[idp].qtd - qtd;
            }
          }

        }

      }

        break;

      case 'E':
        ;
        input[0] = ' ';
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        if ((order_counter - ide) <= 0)
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        if ((product_counter - idp) <= 0)
        {
          printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
        else
        {
          {
            product_index = in_order(orders[ide].products, idp, orders[ide].iter);
            if (product_index == (-1))
            {
              printf("%s 0.\n", system[idp].desc);
            }
            else
            {
              printf("%s %d.\n", orders[ide].products[product_index].desc, orders[ide].products[product_index].qtd);
            }

          }
        }

      }

        break;

      case 'R':
        ;
        input[0] = ' ';
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        if ((order_counter - ide) <= 0)
      {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      }
      else
      {
        if ((product_counter - idp) <= 0)
        {
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
          {
            product_index = in_order(orders[ide].products, idp, orders[ide].iter);
            if (product_index != (-1))
            {
              {
                system[idp].qtd = system[idp].qtd + orders[ide].products[product_index].qtd;
                orders[ide].products[product_index].qtd = 0;
              }
            }
            else
            {
              
            }

          }
        }

      }

        break;

      case 'C':
        ;
        input[0] = ' ';
        ide = new_sym_var(sizeof(int) * 8);
        if ((order_counter - ide) <= 0)
      {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        {
          price = 0;
          for (i = 0; i < orders[ide].iter; ++i)
            price = (orders[ide].products[i].qtd * (*orders[ide].products[i].price)) + price;

          printf("Custo da encomenda %d %d.\n", ide, price);
        }
      }

        break;

      case 'L':
        ;
        input[0] = ' ';
        ide = new_sym_var(sizeof(int) * 8);
        if ((order_counter - ide) <= 0)
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        alphabetic_sort(orders[ide].products, orders[ide].iter, ide);
      }

        break;

      case 'x':
        ;
        return 0;

      default:
        ;
        break;

    }

  }

}
