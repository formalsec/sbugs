/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Product
{
  char info[64];
  int id;
  int price;
  int weight;
  int amount;
} Product;
typedef struct Section
{
  int id;
  int amount;
} Section;
typedef struct Package
{
  Section slot[200];
  int weight;
} Package;
int c;
int last_prod_id;
int last_pack_id;
int last_slot_id[500];
int sorted_prod_id[10000];
Product productsys[10000];
Package packagesys[500];
void do_a();
void do_q();
void do_N();
void do_A();
void do_r();
void do_R();
void do_C();
void do_p();
void do_E();
void do_m();
void do_l();
void do_L();
void doMergeSort(int [], int, int, int);
void doMerge(int [], int, int, int, int);
int prodExists(int);
int packExists(int);
void do_a()
{
  for (int productsys_index = 0; productsys_index < 10; productsys_index++)
  {
    productsys[last_prod_id].info[productsys_index] = new_sym_var(sizeof(char) * 8);
  }

  productsys[last_prod_id].info[10 - 1] = '\0';
  productsys[last_prod_id].price = new_sym_var(sizeof(int) * 8);
  productsys[last_prod_id].weight = new_sym_var(sizeof(int) * 8);
  productsys[last_prod_id].amount = new_sym_var(sizeof(int) * 8);
  productsys[last_prod_id].info[64 - 1] = '\0';
  productsys[last_prod_id].id = last_prod_id;
  printf("Novo produto %d.\n", last_prod_id);
  ++last_prod_id;
}

void do_q()
{
  int prod_id;
  int add_amount;
  prod_id = new_sym_var(sizeof(int) * 8);
  add_amount = new_sym_var(sizeof(int) * 8);
  if (!prodExists(prod_id))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", prod_id);
  }
  else
  {
    productsys[prod_id].amount += add_amount;
  }

}

void do_N()
{
  printf("Nova encomenda %d.\n", last_pack_id);
  ++last_pack_id;
}

void do_A()
{
  int i;
  int j;
  int prod_id;
  int pack_id;
  int prod_amount;
  int prod_weight;
  pack_id = new_sym_var(sizeof(int) * 8);
  prod_id = new_sym_var(sizeof(int) * 8);
  prod_amount = new_sym_var(sizeof(int) * 8);
  if (!packExists(pack_id))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod_id, pack_id);
  }
  else
  {
    if (!prodExists(prod_id))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod_id, pack_id);
    }
    else
    {
      if ((productsys[prod_id].amount - prod_amount) < 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod_id, pack_id);
      }
      else
      {
        if (((productsys[prod_id].weight * prod_amount) + packagesys[pack_id].weight) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod_id, pack_id);
        }
        else
        {
          i = last_slot_id[pack_id];
          prod_weight = productsys[prod_id].weight;
          for (j = 0; j < i; j++)
          {
            if (packagesys[pack_id].slot[j].id == prod_id)
            {
              packagesys[pack_id].slot[j].amount += prod_amount;
              productsys[prod_id].amount -= prod_amount;
              packagesys[pack_id].weight += prod_weight * prod_amount;
              return;
            }
            else
            {
              
            }

          }

          packagesys[pack_id].slot[i].id = prod_id;
          packagesys[pack_id].slot[i].amount = prod_amount;
          productsys[prod_id].amount -= prod_amount;
          packagesys[pack_id].weight += prod_weight * prod_amount;
          ++last_slot_id[pack_id];
        }

      }

    }

  }

}

void do_r()
{
  int prod_id;
  int sweep_amount;
  prod_id = new_sym_var(sizeof(int) * 8);
  sweep_amount = new_sym_var(sizeof(int) * 8);
  if (!prodExists(prod_id))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod_id);
  }
  else
  {
    if ((productsys[prod_id].amount - sweep_amount) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", sweep_amount, prod_id);
    }
    else
    {
      productsys[prod_id].amount -= sweep_amount;
    }

  }

}

void do_R()
{
  int i;
  int j;
  int prod_id;
  int pack_id;
  int prod_amount;
  int prod_weight;
  pack_id = new_sym_var(sizeof(int) * 8);
  prod_id = new_sym_var(sizeof(int) * 8);
  if (!packExists(pack_id))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod_id, pack_id);
  }
  else
  {
    if (!prodExists(prod_id))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod_id, pack_id);
    }
    else
    {
      i = last_slot_id[pack_id];
      for (j = 0; j < i; j++)
      {
        if (packagesys[pack_id].slot[j].id == prod_id)
        {
          prod_amount = packagesys[pack_id].slot[j].amount;
          prod_weight = productsys[prod_id].weight;
          packagesys[pack_id].slot[j].amount = 0;
          productsys[prod_id].amount += prod_amount;
          packagesys[pack_id].weight -= prod_amount * prod_weight;
          return;
        }
        else
        {
          
        }

      }

    }

  }

}

void do_C()
{
  int i;
  int j;
  int prod_id;
  int pack_id;
  int prod_price;
  int prod_amount;
  int total = 0;
  pack_id = new_sym_var(sizeof(int) * 8);
  if (!packExists(pack_id))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", pack_id);
  }
  else
  {
    i = last_slot_id[pack_id];
    for (j = 0; j < i; j++)
    {
      prod_id = packagesys[pack_id].slot[j].id;
      prod_price = productsys[prod_id].price;
      prod_amount = packagesys[pack_id].slot[j].amount;
      total += prod_price * prod_amount;
    }

    printf("Custo da encomenda %d %d.\n", pack_id, total);
  }

}

void do_p()
{
  int prod_id;
  int prod_new_price;
  prod_id = new_sym_var(sizeof(int) * 8);
  prod_new_price = new_sym_var(sizeof(int) * 8);
  if (!prodExists(prod_id))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", prod_id);
  }
  else
  {
    productsys[prod_id].price = prod_new_price;
  }

}

void do_E()
{
  int i;
  int j;
  int prod_id;
  int pack_id;
  pack_id = new_sym_var(sizeof(int) * 8);
  prod_id = new_sym_var(sizeof(int) * 8);
  if (!packExists(pack_id))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", pack_id);
  }
  else
  {
    if (!prodExists(prod_id))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", prod_id);
    }
    else
    {
      i = last_slot_id[pack_id];
      for (j = 0; j < i; j++)
        if (packagesys[pack_id].slot[j].id == prod_id)
      {
        printf("%s %d.\n", productsys[prod_id].info, packagesys[pack_id].slot[j].amount);
        return;
      }
      else
      {
        
      }


      printf("%s 0.\n", productsys[prod_id].info);
    }

  }

}

void do_m()
{
  int i;
  int j;
  int prod_id;
  int pack_id;
  int check_amount;
  int max_amount = 0;
  prod_id = new_sym_var(sizeof(int) * 8);
  if (!prodExists(prod_id))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod_id);
  }
  else
  {
    for (i = 0; i < last_pack_id; i++)
    {
      for (j = 0; j < last_slot_id[i]; j++)
      {
        if (packagesys[i].slot[j].id == prod_id)
        {
          check_amount = packagesys[i].slot[j].amount;
          if (max_amount < check_amount)
          {
            max_amount = check_amount;
            pack_id = i;
            break;
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

    if (max_amount)
    {
      printf("Maximo produto %d %d %d.\n", prod_id, pack_id, max_amount);
    }
    else
    {
      
    }

  }

}

void do_l()
{
  int i;
  int prod_id;
  int manner = 1;
  for (i = 0; i < last_prod_id; i++)
    sorted_prod_id[i] = productsys[i].id;

  if (last_prod_id)
  {
    doMergeSort(sorted_prod_id, 0, last_prod_id - 1, manner);
  }
  else
  {
    
  }

  printf("Produtos\n");
  for (i = 0; i < last_prod_id; i++)
  {
    prod_id = sorted_prod_id[i];
    printf("* %s %d %d\n", productsys[prod_id].info, productsys[prod_id].price, productsys[prod_id].amount);
  }

}

void do_L()
{
  int i;
  int j;
  int k;
  int prod_id;
  int pack_id;
  int prod_amount;
  int manner = 0;
  pack_id = new_sym_var(sizeof(int) * 8);
  if (!packExists(pack_id))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", pack_id);
  }
  else
  {
    i = last_slot_id[pack_id];
    for (j = 0; j < i; j++)
      sorted_prod_id[j] = packagesys[pack_id].slot[j].id;

    if (i)
    {
      doMergeSort(sorted_prod_id, 0, i - 1, manner);
    }
    else
    {
      
    }

    printf("Encomenda %d\n", pack_id);
    for (j = 0; j < i; j++)
    {
      prod_id = sorted_prod_id[j];
      for (k = 0; k < i; k++)
        if (packagesys[pack_id].slot[k].id == prod_id)
      {
        prod_amount = packagesys[pack_id].slot[k].amount;
        break;
      }
      else
      {
        
      }


      if (prod_amount)
      {
        printf("* %s %d %d\n", productsys[prod_id].info, productsys[prod_id].price, prod_amount);
      }
      else
      {
        
      }

    }

  }

}

void doMergeSort(int prod_arr[], int l, int r, int flag)
{
  int m = (l + r) / 2;
  if (r > l)
  {
    doMergeSort(prod_arr, l, m, flag);
    doMergeSort(prod_arr, m + 1, r, flag);
    doMerge(prod_arr, l, m, r, flag);
  }
  else
  {
    
  }

}

void doMerge(int prod_arr[], int l, int m, int r, int flag)
{
  int i;
  int j;
  int k;
  int lp;
  int rp;
  int result;
  int aux[10000];
  for (i = m + 1; i > l; i--)
  {
    aux[i - 1] = prod_arr[i - 1];
  }

  for (j = m; j < r; j++)
  {
    aux[(r + m) - j] = prod_arr[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if (flag == 1)
    {
      lp = productsys[aux[i]].price;
      rp = productsys[aux[j]].price;
      if (lp < rp)
      {
        prod_arr[k] = aux[i++];
      }
      else
      {
        if (lp > rp)
        {
          prod_arr[k] = aux[j--];
        }
        else
        {
          if (aux[i] < aux[j])
          {
            prod_arr[k] = aux[i++];
          }
          else
          {
            prod_arr[k] = aux[j--];
          }

        }

      }

    }
    else
    {
      if (flag == 0)
      {
        result = strcmp(productsys[aux[i]].info, productsys[aux[j]].info);
        if (result < 0)
        {
          prod_arr[k] = aux[i++];
        }
        else
        {
          if (result > 0)
          {
            prod_arr[k] = aux[j--];
          }
          else
          {
            if (aux[i] < aux[j])
            {
              prod_arr[k] = aux[i++];
            }
            else
            {
              prod_arr[k] = aux[j--];
            }

          }

        }

      }
      else
      {
        
      }

    }

  }

}

int prodExists(int prod_id)
{
  return (prod_id >= 0) && (prod_id < last_prod_id);
}

int packExists(int pack_id)
{
  return (pack_id >= 0) && (pack_id < last_pack_id);
}

int main()
{
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
        do_a();
        break;

      case 'q':
        do_q();
        break;

      case 'N':
        do_N();
        break;

      case 'A':
        do_A();
        break;

      case 'r':
        do_r();
        break;

      case 'R':
        do_R();
        break;

      case 'C':
        do_C();
        break;

      case 'p':
        do_p();
        break;

      case 'E':
        do_E();
        break;

      case 'm':
        do_m();
        break;

      case 'l':
        do_l();
        break;

      case 'L':
        do_L();
        break;

    }

  }

  return 0;
}
