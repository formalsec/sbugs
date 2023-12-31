#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Produto
{
  int id;
  char desc[63];
  int price;
  int weight;
  int quantity;
} Produto;
Produto product_line[10000];
Produto order_line[500][200];
int add_prod_order[500] = {0};
Produto aux[10000];
Produto aux1[10000];
void function_a()
{
  static int idp = 0;
  for (int product_line_index = 0; product_line_index < 10; product_line_index++)
  {
    product_line[idp].desc[product_line_index] = new_sym_var(sizeof(char) * 8);
  }

  product_line[idp].desc[10 - 1] = '\0';
  product_line[idp].price = new_sym_var(sizeof(int) * 8);
  product_line[idp].weight = new_sym_var(sizeof(int) * 8);
  product_line[idp].quantity = new_sym_var(sizeof(int) * 8);
  product_line[idp].id = idp;
  printf("Novo produto %d.\n", idp);
  idp++;
}

void function_q(int total)
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= total)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    product_line[idp].quantity += qtd;
  }

}

void function_o()
{
  static int ido = 0;
  printf("Nova encomenda %d.\n", ido);
  ido++;
}

int weight_calculater_order(int ido, int number_prod, int weight_acc)
{
  int i;
  int weight = weight_acc;
  for (i = 0; i < number_prod; i++)
    weight += order_line[ido][i].quantity * product_line[order_line[ido][i].id].weight;

  return weight;
}

void function_A(int total_o, int total_p)
{
  int ido;
  int idp;
  int qtd;
  int l;
  int state = 0;
  int number_add = 0;
  int acc_weight = 0;
  ido = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ido >= total_o)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
  }
  else
  {
    if (idp >= total_p)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
    }
    else
    {
      if ((product_line[idp].quantity - qtd) < 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ido);
      }
      else
      {
        if ((qtd * product_line[idp].weight) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ido);
        }
        else
        {
          number_add = add_prod_order[ido];
          acc_weight = qtd * product_line[idp].weight;
          if (number_add == 0)
          {
            product_line[idp].quantity -= qtd;
            order_line[ido][0].id = idp;
            order_line[ido][0].quantity = qtd;
            add_prod_order[ido] += 1;
          }
          else
          {
            for (l = 0; l < number_add; l++)
            {
              if (order_line[ido][l].id == idp)
              {
                state = 1;
                break;
              }
              else
              {
                
              }

            }

            if (state != 0)
            {
              if (weight_calculater_order(ido, number_add, acc_weight) <= 200)
              {
                order_line[ido][l].quantity += qtd;
                product_line[idp].quantity -= qtd;
              }
              else
              {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ido);
              }

            }
            else
            {
              if (weight_calculater_order(ido, number_add, acc_weight) <= 200)
              {
                product_line[idp].quantity -= qtd;
                order_line[ido][number_add].id = idp;
                order_line[ido][number_add].quantity = qtd;
                add_prod_order[ido] += 1;
              }
              else
              {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ido);
              }

            }

          }

        }

      }

    }

  }

}

void function_r(int total)
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= total)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if ((product_line[idp].quantity - qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      product_line[idp].quantity -= qtd;
    }

  }

}

void function_R(int total_ord, int total_prod)
{
  int ido;
  int idp;
  int i;
  ido = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ido >= total_ord)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
  }
  else
  {
    if (idp >= total_prod)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
    }
    else
    {
      for (i = 0; i < add_prod_order[ido]; i++)
      {
        if (order_line[ido][i].id == idp)
        {
          product_line[idp].quantity += order_line[ido][i].quantity;
          order_line[ido][i] = order_line[ido][add_prod_order[ido] - 1];
          add_prod_order[ido] -= 1;
        }
        else
        {
          
        }

      }

    }

  }

}

void merge(int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux1[i - 1] = aux[i - 1];

  for (j = m; j < r; j++)
    aux1[(r + m) - j] = aux[j + 1];

  for (k = l; k <= r; k++)
  {
    if (aux1[j].price < aux1[i].price)
    {
      aux[k] = aux1[j--];
    }
    else
    {
      if ((aux1[j].price == aux1[i].price) && (aux1[j].id < aux1[i].id))
      {
        aux[k] = aux1[j--];
      }
      else
      {
        aux[k] = aux1[i++];
      }

    }

  }

}

void function_l(int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  function_l(l, m);
  function_l(m + 1, r);
  merge(l, m, r);
}

void function_p(int total_prod)
{
  int idp;
  int price;
  idp = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  if (idp >= total_prod)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    product_line[idp].price = price;
  }

}

void function_C(int total_ord)
{
  int i;
  int acc = 0;
  int ido;
  ido = new_sym_var(sizeof(int) * 8);
  if (ido >= total_ord)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ido);
  }
  else
  {
    for (i = 0; i < add_prod_order[ido]; i++)
      acc += order_line[ido][i].quantity * product_line[order_line[ido][i].id].price;

    printf("Custo da encomenda %d %d.\n", ido, acc);
  }

}

void function_E(int total_prod, int total_ord)
{
  int i;
  int ido;
  int idp;
  int state = -1;
  ido = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ido >= total_ord)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
  }
  else
  {
    if (idp >= total_prod)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      for (i = 0; i < add_prod_order[ido]; i++)
        if (order_line[ido][i].id == idp)
      {
        state = i;
      }
      else
      {
        
      }


      if (state != (-1))
      {
        printf("%s %d.\n", product_line[idp].desc, order_line[ido][state].quantity);
      }
      else
      {
        printf("%s 0.\n", product_line[idp].desc);
      }

    }

  }

}

void function_L(int total_ord)
{
  Produto aux;
  int ido;
  int i;
  int j;
  int min;
  int l = 0;
  ido = new_sym_var(sizeof(int) * 8);
  if (ido >= total_ord)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
  }
  else
  {
    for (i = 0; i < add_prod_order[ido]; i++)
    {
      min = i;
      for (j = i + 1; j < add_prod_order[ido]; j++)
        if (strcmp(product_line[order_line[ido][j].id].desc, product_line[order_line[ido][min].id].desc) < 0)
      {
        min = j;
      }
      else
      {
        
      }


      aux = order_line[ido][i];
      order_line[ido][i] = order_line[ido][min];
      order_line[ido][min] = aux;
    }

    printf("Encomenda %d\n", ido);
    while (l < add_prod_order[ido])
    {
      printf("* %s %d %d\n", product_line[order_line[ido][l].id].desc, product_line[order_line[ido][l].id].price, order_line[ido][l].quantity);
      l++;
    }

  }

}

void function_m(int total, int total_ord)
{
  int idp;
  int acc = 0;
  int final;
  int i;
  int l;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= total)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    for (i = 0; i < total_ord; i++)
    {
      for (l = 0; l < add_prod_order[i]; l++)
      {
        if ((order_line[i][l].id == idp) && (order_line[i][l].quantity > acc))
        {
          acc = order_line[i][l].quantity;
          final = i;
        }
        else
        {
          
        }

      }

    }

    if (acc == 0)
    {
      return;
    }
    else
    {
      printf("Maximo produto %d %d %d.\n", idp, final, acc);
    }

  }

}

int main()
{
  int control;
  int run = 1;
  int total_product = 0;
  int total_orders = 0;
  int l;
  int z;
  while (run)
  {
    control = getchar();
    switch (control)
    {
      case 'a':
        function_a();
        total_product++;
        break;

      case 'q':
        function_q(total_product);
        break;

      case 'N':
        function_o();
        total_orders++;
        break;

      case 'A':
        function_A(total_orders, total_product);
        break;

      case 'x':
        run = 0;
        break;

      case 'r':
        function_r(total_product);
        break;

      case 'R':
        function_R(total_orders, total_product);
        break;

      case 'l':
        for (z = 0; z < total_product; z++)
        aux[z] = product_line[z];

        function_l(0, total_product - 1);
        printf("Produtos\n");
        for (l = 0; l < total_product; l++)
        printf("* %s %d %d\n", aux[l].desc, aux[l].price, aux[l].quantity);

        break;

      case 'p':
        function_p(total_product);
        break;

      case 'E':
        function_E(total_product, total_orders);
        break;

      case 'C':
        function_C(total_orders);
        break;

      case 'L':
        function_L(total_orders);
        break;

      case 'm':
        function_m(total_product, total_orders);
        break;

      default:
        run = 0;
        break;

    }

    getchar();
  }

  return 0;
}

