/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct 
{
  int id;
  char descr[64];
  int price;
  int weight;
  int stock;
} Product;
typedef struct 
{
  int weight;
  int n_products;
  int products[1000];
  int prod_qnt[1000];
  int order_sort;
} Order;
Product product[100000];
Order order[500];
int n_prod = 0;
int n_order = 0;
int prod_sort = 0;
char input[5][64];
void process_input(char buffer[250]);
int lookfor(int id);
void merges_prod(int left, int right);
void mg_prod(int left, int m, int right);
void quick_sort(int o_id, int left, int right);
int partition(int o_id, int left, int right);
void a();
void q();
void r();
void p();
void N();
void A();
void R();
void C();
void E();
void m();
void l();
void L();
void k();
void K();
void process_input(char buffer[250])
{
  char *token;
  int i = 1;
  token = strtok(buffer, "' '\n");
  strcpy(input[0], token);
  while ((token = strtok(0, ":\n")) != 0)
  {
    strcpy(input[i], token);
    i++;
  }

}

int lookfor(int id)
{
  int i;
  for (i = 0; i < n_prod; i++)
  {
    if (id == product[i].id)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int main()
{
  char buffer[250];
  fgets(buffer, 250, stdin);
  process_input(buffer);
  while (atoi(input[0]) != EOF)
  {
    switch (buffer[0])
    {
      case 'a':
        a();
        break;

      case 'q':
        q();
        break;

      case 'k':
        k();
        break;

      case 'r':
        r();
        break;

      case 'p':
        p();
        break;

      case 'N':
        N();
        break;

      case 'A':
        A();
        break;

      case 'K':
        K();
        break;

      case 'R':
        R();
        break;

      case 'C':
        C();
        break;

      case 'E':
        E();
        break;

      case 'm':
        m();
        break;

      case 'l':
        l();
        break;

      case 'L':
        L();
        break;

      case 'x':
        return 0;

    }

    fgets(buffer, 250, stdin);
    process_input(buffer);
  }

  return 0;
}

void a()
{
  product[n_prod].id = n_prod;
  strcpy(product[n_prod].descr, input[1]);
  product[n_prod].price = atoi(input[2]);
  ;
  product[n_prod].weight = atoi(input[3]);
  product[n_prod].stock = atoi(input[4]);
  printf("Novo produto %d.\n", n_prod);
  prod_sort = 0;
  n_prod++;
}

void q()
{
  int i;
  int id;
  id = atoi(input[1]);
  if (id >= n_prod)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      i = lookfor(id);
      product[i].stock += atoi(input[2]);
    }
  }

}

void r()
{
  int i;
  int id;
  int qnt;
  id = atoi(input[1]);
  qnt = atoi(input[2]);
  if (id >= n_prod)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      i = lookfor(id);
      if (product[i].stock >= qnt)
      {
        {
          product[i].stock -= qnt;
        }
      }
      else
      {
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, id);
        }
      }

    }
  }

}

void p()
{
  int i;
  int id;
  id = atoi(input[1]);
  if (id >= n_prod)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
  }
  else
  {
    {
      i = lookfor(id);
      product[i].price = atoi(input[2]);
    }
  }

  prod_sort = 0;
}

void N()
{
  order[n_order].weight = 0;
  order[n_order].n_products = 0;
  order[n_order].order_sort = 0;
  printf("Nova encomenda %d.\n", n_order);
  n_order++;
}

void A()
{
  int i;
  int j;
  int o_id;
  int id;
  int qnt;
  int flag = 1;
  o_id = atoi(input[1]);
  id = atoi(input[2]);
  qnt = atoi(input[3]);
  if (o_id >= n_order)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id, o_id);
    }
  }
  else
  {
    {
      if (id >= n_prod)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id, o_id);
        }
      }
      else
      {
        {
          j = lookfor(id);
          if (qnt > product[j].stock)
          {
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id, o_id);
            }
          }
          else
          {
            {
              if (((qnt * product[j].weight) + order[o_id].weight) > 200)
              {
                {
                  printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id, o_id);
                }
              }
              else
              {
                {
                  for (i = 0; i < order[o_id].n_products; i++)
                  {
                    if (order[o_id].products[i] == id)
                    {
                      {
                        order[o_id].weight += qnt * product[j].weight;
                        order[o_id].prod_qnt[i] += qnt;
                        flag = 0;
                        break;
                      }
                    }
                    else
                    {
                      
                    }

                  }

                  if (flag)
                  {
                    {
                      order[o_id].products[order[o_id].n_products] = id;
                      order[o_id].weight += qnt * product[j].weight;
                      order[o_id].prod_qnt[order[o_id].n_products] = qnt;
                      order[o_id].n_products++;
                    }
                  }
                  else
                  {
                    
                  }

                  product[j].stock -= qnt;
                  order[o_id].order_sort = 0;
                }
              }

            }
          }

        }
      }

    }
  }

}

void R()
{
  int i;
  int id;
  int o_id;
  int pos_prod;
  o_id = atoi(input[1]);
  id = atoi(input[2]);
  if (o_id >= n_order)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id, o_id);
  }
  else
  {
    {
      if (id >= n_prod)
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id, o_id);
      }
      else
      {
        
      }

      for (i = 0; i < order[o_id].n_products; i++)
      {
        if (id == order[o_id].products[i])
        {
          {
            pos_prod = lookfor(id);
            product[pos_prod].stock += order[o_id].prod_qnt[i];
            order[o_id].weight -= product[pos_prod].weight * order[o_id].prod_qnt[i];
            order[o_id].products[i] = order[o_id].products[order[o_id].n_products - 1];
            order[o_id].prod_qnt[i] = order[o_id].prod_qnt[order[o_id].n_products - 1];
            order[o_id].n_products--;
            order[o_id].order_sort = 0;
            break;
          }
        }
        else
        {
          
        }

      }

    }
  }

}

void C()
{
  int i;
  int price = 0;
  int id;
  int o_id;
  o_id = atoi(input[1]);
  if (o_id >= n_order)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", o_id);
  }
  else
  {
    {
      for (i = 0; i < order[o_id].n_products; i++)
      {
        id = lookfor(order[o_id].products[i]);
        price += product[id].price * order[o_id].prod_qnt[i];
      }

      printf("Custo da encomenda %d %d.\n", o_id, price);
    }
  }

}

void E()
{
  int i;
  int o_id;
  int id;
  int real_id;
  int qnt = 0;
  o_id = atoi(input[1]);
  id = atoi(input[2]);
  real_id = lookfor(id);
  if (o_id >= n_order)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
  }
  else
  {
    {
      if (id >= n_prod)
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", id);
      }
      else
      {
        {
          for (i = 0; i < order[o_id].n_products; i++)
          {
            if (id == order[o_id].products[i])
            {
              {
                qnt = order[o_id].prod_qnt[i];
                break;
              }
            }
            else
            {
              
            }

          }

          printf("%s %d.\n", product[real_id].descr, qnt);
        }
      }

    }
  }

}

void m()
{
  int i;
  int j;
  int id;
  int qnt = -1;
  int o_id = -1;
  id = atoi(input[1]);
  if (id >= n_prod)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);
  }
  else
  {
    {
      for (i = 0; i < n_order; i++)
      {
        for (j = 0; j < order[i].n_products; j++)
        {
          if (id == order[i].products[j])
          {
            {
              if (order[i].prod_qnt[j] > qnt)
              {
                {
                  qnt = order[i].prod_qnt[j];
                  o_id = i;
                  break;
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

      if (qnt > 0)
      {
        printf("Maximo produto %d %d %d.\n", id, o_id, qnt);
      }
      else
      {
        
      }

    }
  }

}

void l()
{
  int i;
  if (!prod_sort)
  {
    {
      merges_prod(0, n_prod - 1);
      prod_sort = 1;
    }
  }
  else
  {
    
  }

  printf("Produtos\n");
  for (i = 0; i < n_prod; i++)
  {
    printf("* %s %d %d\n", product[i].descr, product[i].price, product[i].stock);
  }

}

void L()
{
  int i;
  int p1;
  int o_id;
  o_id = atoi(input[1]);
  if (o_id >= n_order)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
  }
  else
  {
    {
      if (!order[o_id].order_sort)
      {
        {
          quick_sort(o_id, 0, order[o_id].n_products - 1);
          order[o_id].order_sort = 1;
        }
      }
      else
      {
        
      }

      printf("Encomenda %d\n", o_id);
      for (i = 0; i < order[o_id].n_products; i++)
      {
        p1 = lookfor(order[o_id].products[i]);
        printf("* %s %d %d\n", product[p1].descr, product[p1].price, order[o_id].prod_qnt[i]);
      }

    }
  }

}

void k()
{
  int i;
  for (i = 0; i < n_prod; i++)
  {
    printf("Produto %s com preco %d, peso %d, stock %d\n", product[i].descr, product[i].price, product[i].weight, product[i].stock);
  }

}

void K()
{
  int i;
  int j;
  for (i = 0; i < n_order; i++)
  {
    printf("* Encomenda id: %d, numero produtos: %d, peso: %d\n", i, order[i].n_products, order[i].weight);
    for (j = 0; j < order[i].n_products; j++)
    {
      printf("* Produto: %d\n", order[i].products[j]);
    }

  }

}

void merges_prod(int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  merges_prod(left, m);
  merges_prod(m + 1, right);
  mg_prod(left, m, right);
}

void mg_prod(int left, int m, int right)
{
  Product *aux;
  int i;
  int j;
  int k;
  aux = malloc((sizeof(Product)) * n_prod);
  for (i = m + 1; i > left; i--)
    aux[i - 1] = product[i - 1];

  for (j = m; j < right; j++)
    aux[(right + m) - j] = product[j + 1];

  for (k = left; k <= right; k++)
  {
    if (aux[j].price < aux[i].price)
    {
      {
        product[k] = aux[j--];
      }
    }
    else
    {
      if (aux[j].price == aux[i].price)
      {
        {
          if (aux[j].id < aux[i].id)
          {
            {
              product[k] = aux[j--];
            }
          }
          else
          {
            {
              product[k] = aux[i++];
            }
          }

        }
      }
      else
      {
        {
          product[k] = aux[i++];
        }
      }

    }

  }

  free(aux);
}

void quick_sort(int o_id, int left, int right)
{
  int m;
  if (left < right)
  {
    {
      m = partition(o_id, left, right);
      quick_sort(o_id, left, m - 1);
      quick_sort(o_id, m + 1, right);
    }
  }
  else
  {
    
  }

}

int partition(int o_id, int left, int right)
{
  int i = left;
  int j;
  int id;
  int id_r = lookfor(order[o_id].products[right]);
  for (j = left; j < right; j++)
  {
    id = lookfor(order[o_id].products[j]);
    if (strcmp(product[id].descr, product[id_r].descr) < 0)
    {
      {
        {
          int t = order[o_id].products[i];
          order[o_id].products[i] = order[o_id].products[j];
          order[o_id].products[j] = t;
        }
        ;
        {
          int t = order[o_id].prod_qnt[i];
          order[o_id].prod_qnt[i] = order[o_id].prod_qnt[j];
          order[o_id].prod_qnt[j] = t;
        }
        ;
        i++;
      }
    }
    else
    {
      
    }

  }

  {
    int t = order[o_id].products[i];
    order[o_id].products[i] = order[o_id].products[right];
    order[o_id].products[right] = t;
  }
  ;
  {
    int t = order[o_id].prod_qnt[i];
    order[o_id].prod_qnt[i] = order[o_id].prod_qnt[right];
    order[o_id].prod_qnt[right] = t;
  }
  ;
  return i;
}
