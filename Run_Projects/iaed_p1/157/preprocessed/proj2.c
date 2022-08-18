/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct product
{
  char name[63];
  int weight;
  int price;
  int qtd;
  int id;
} product;
typedef struct order
{
  int ido;
  int number;
  int weight;
  int pro_id_qtd[200][2];
  int price;
  int total;
} order;
product store[10000];
order orders[500];
void add_new_product(int n)
{
  int i = 0;
  char character;
  character = getchar();
  character = getchar();
  while (character != ':')
  {
    store[n].name[i++] = character;
    character = getchar();
  }

  store[n].name[i] = '\0';
  store[n].price = new_sym_var(sizeof(int) * 8);
  store[n].weight = new_sym_var(sizeof(int) * 8);
  store[n].qtd = new_sym_var(sizeof(int) * 8);
  store[n].id = n;
  printf("Novo produto %d.\n", store[n].id);
  n += 1;
}

void add_stock(int n)
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id > n)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      store[id].qtd += qtd;
    }
  }

}

int weight_calcu(int ido)
{
  int soma = 0;
  int i = 0;
  int id;
  int qtd;
  while (orders[ido].pro_id_qtd[i][0] != (-1))
  {
    id = orders[ido].pro_id_qtd[i][0];
    qtd = orders[ido].pro_id_qtd[i][1];
    soma += store[id].weight * qtd;
    i += 1;
  }

  return soma;
}

int find_id(int ido, int id)
{
  int i;
  for (i = 0; i < 200; i++)
  {
    if (orders[ido].pro_id_qtd[i][0] == id)
    {
      {
        return i;
      }
    }
    else
    {
      
    }

  }

  return -1;
}

void add_product(int n, int no)
{
  int ido;
  int id;
  int qtd;
  int weight;
  int index;
  int i;
  ido = new_sym_var(sizeof(int) * 8);
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  weight = (qtd * store[id].weight) + weight_calcu(ido);
  if (ido > no)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id, ido);
    }
  }
  else
  {
    if (id > n)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id, ido);
      }
    }
    else
    {
      if (store[id].qtd < qtd)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id, ido);
        }
      }
      else
      {
        if (weight > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id, ido);
          }
        }
        else
        {
          {
            index = find_id(ido, id);
            if (index != (-1))
            {
              {
                orders[ido].pro_id_qtd[index][1] += qtd;
              }
            }
            else
            {
              {
                for (i = 0; i < 200; i++)
                {
                  if ((orders[ido].pro_id_qtd[i][0] == (-1)) && (index == (-1)))
                  {
                    {
                      orders[ido].pro_id_qtd[i][0] = id;
                      orders[ido].pro_id_qtd[i][1] = qtd;
                      orders[ido].total += 1;
                      index = 1;
                    }
                  }
                  else
                  {
                    
                  }

                }

              }
            }

            store[id].qtd -= qtd;
          }
        }

      }

    }

  }

}

void remove_stock(int n)
{
  int id;
  int qtd;
  id = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id > n)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
    }
  }
  else
  {
    if (store[id].qtd < qtd)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
      }
    }
    else
    {
      {
        store[id].qtd -= qtd;
      }
    }

  }

}

void remove_product(int n, int no)
{
  int ido;
  int id;
  int i;
  int index;
  ido = new_sym_var(sizeof(int) * 8);
  id = new_sym_var(sizeof(int) * 8);
  if (no < ido)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id, ido);
    }
  }
  else
  {
    if (n < id)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id, ido);
      }
    }
    else
    {
      {
        index = find_id(ido, id);
        if (index != (-1))
        {
          {
            store[id].qtd += orders[ido].pro_id_qtd[index][1];
            for (i = index; i < (200 - 1); i++)
            {
              orders[ido].pro_id_qtd[i][0] = orders[ido].pro_id_qtd[i + 1][0];
              orders[ido].pro_id_qtd[i][1] = orders[ido].pro_id_qtd[i + 1][1];
            }

            orders[ido].pro_id_qtd[199][0] = -1;
            orders[ido].total -= 1;
          }
        }
        else
        {
          
        }

      }
    }

  }

}

int price_calcu(int ido)
{
  int soma = 0;
  int i;
  int id;
  int qtd;
  for (i = 0; i < orders[ido].total; i++)
  {
    id = orders[ido].pro_id_qtd[i][0];
    qtd = orders[ido].pro_id_qtd[i][1];
    soma += store[id].price * qtd;
  }

  return soma;
}

void order_total(int no)
{
  int ido;
  ido = new_sym_var(sizeof(int) * 8);
  if (no < ido)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ido);
    }
  }
  else
  {
    {
      orders[ido].price = price_calcu(ido);
      printf("Custo da encomenda %d %d.\n", ido, orders[ido].price);
    }
  }

}

void price_change(int n)
{
  int id;
  int price;
  id = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if (id > n)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
    }
  }
  else
  {
    
  }

  store[id].price = price;
}

void orders_product(int n, int no)
{
  int id;
  int ido;
  int i;
  int x = 0;
  ido = new_sym_var(sizeof(int) * 8);
  id = new_sym_var(sizeof(int) * 8);
  if (n < id)
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", id);
    }
  }
  else
  {
    if (no < ido)
    {
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
      }
    }
    else
    {
      {
        for (i = 0; i < 200; i++)
        {
          if ((orders[ido].pro_id_qtd[i][0] == id) && (x == 0))
          {
            {
              printf("%s %d.\n", store[id].name, orders[ido].pro_id_qtd[i][1]);
              x = 1;
            }
          }
          else
          {
            
          }

        }

        if (x == 0)
        {
          {
            printf("%s 0.\n", store[id].name);
          }
        }
        else
        {
          
        }

      }
    }

  }

}

void maximum_product(int n)
{
  int id;
  int i;
  int j;
  int maior = 0;
  int ido;
  id = new_sym_var(sizeof(int) * 8);
  if (n < id)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      for (i = 0; i < 500; i++)
      {
        for (j = 0; j < 200; j++)
        {
          if (orders[i].pro_id_qtd[j][0] == id)
          {
            {
              if (orders[i].pro_id_qtd[j][1] > maior)
              {
                {
                  maior = orders[i].pro_id_qtd[j][1];
                  ido = i;
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

      if (maior != 0)
      {
        {
          printf("Maximo produto %d %d %d.\n", id, ido, maior);
        }
      }
      else
      {
        
      }

    }
  }

}

product aux_1[10000];
void merge_price(product a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    aux_1[i - 1] = a[i - 1];
  }

  for (j = m; j < r; j++)
  {
    aux_1[(r + m) - j] = a[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if (aux_1[j].price < aux_1[i].price)
    {
      {
        a[k] = aux_1[j--];
      }
    }
    else
    {
      if (aux_1[j].price == aux_1[i].price)
      {
        {
          if (aux_1[j].id < aux_1[i].id)
          {
            {
              a[k] = aux_1[j--];
            }
          }
          else
          {
            {
              a[k] = aux_1[i++];
            }
          }

        }
      }
      else
      {
        {
          a[k] = aux_1[i++];
        }
      }

    }

  }

}

void mergesort_price(product a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  mergesort_price(a, l, m);
  mergesort_price(a, m + 1, r);
  merge_price(a, l, m, r);
}

product store_copy[10000];
void sort_price(int n)
{
  int i;
  for (i = 0; i < (n + 1); i++)
  {
    store_copy[i] = store[i];
  }

  printf("Produtos\n");
  mergesort_price(store_copy, 0, n);
  for (i = 0; i < (n + 1); i++)
  {
    printf("* %s %d %d\n", store_copy[i].name, store_copy[i].price, store_copy[i].qtd);
  }

}

int aux[200];
void merge_desc(int a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1] = a[i - 1];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j] = a[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if (strcmp(store[aux[j]].name, store[aux[i]].name) < 0)
    {
      {
        a[k] = aux[j--];
      }
    }
    else
    {
      {
        a[k] = aux[i++];
      }
    }

  }

}

void mergesort_descr(int a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  mergesort_descr(a, l, m);
  mergesort_descr(a, m + 1, r);
  merge_desc(a, l, m, r);
}

void sort_description(int no)
{
  int ido;
  int i;
  int id;
  int list[200];
  int list_qtds[10000];
  ido = new_sym_var(sizeof(int) * 8);
  if (no < ido)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
    }
  }
  else
  {
    {
      for (i = 0; i < orders[ido].total; i++)
      {
        id = orders[ido].pro_id_qtd[i][0];
        list[i] = id;
        list_qtds[id] = orders[ido].pro_id_qtd[i][1];
      }

      mergesort_descr(list, 0, orders[ido].total - 1);
      printf("Encomenda %d\n", ido);
      for (i = 0; i < orders[ido].total; i++)
      {
        printf("* %s %d %d\n", store[list[i]].name, store[list[i]].price, list_qtds[list[i]]);
      }

    }
  }

}

int main()
{
  char action;
  int n = -1;
  int no = -1;
  int i;
  int j;
  for (i = 0; i < 500; i++)
  {
    for (j = 0; j < 200; j++)
    {
      orders[i].pro_id_qtd[j][0] = -1;
    }

  }

  action = getchar();
  while (action != 'x')
  {
    switch (action)
    {
      case 'a':
        n += 1;
        add_new_product(n);
        break;

      case 'q':
        add_stock(n);
        break;

      case 'N':
        no += 1;
        orders[no].ido = no;
        printf("Nova encomenda %d.\n", orders[no].ido);
        break;

      case 'A':
        add_product(n, no);
        break;

      case 'r':
        remove_stock(n);
        break;

      case 'R':
        remove_product(n, no);
        break;

      case 'C':
        order_total(no);
        break;

      case 'p':
        price_change(n);
        break;

      case 'E':
        orders_product(n, no);
        break;

      case 'm':
        maximum_product(n);
        break;

      case 'l':
        sort_price(n);
        break;

      case 'L':
        sort_description(no);
        break;

      default:
        break;

    }

    action = getchar();
  }

  return 0;
}

