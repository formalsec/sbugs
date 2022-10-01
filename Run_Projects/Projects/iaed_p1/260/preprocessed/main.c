/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"


int product_count = 0;
int order_count = 0;
Product p_info[10000];
Order orders[500];
Product *products[10000];
void shift_right_array(void **arr, int start_pos, int stop_pos)
{
  int i;
  for (i = start_pos; i >= stop_pos; arr[i] = arr[i - 1], i--)
    ;

}

int find_product_pos(int o_id, int p_id)
{
  int i;
  for (i = 0; i < orders[o_id].ref_cnt; i++)
    if (orders[o_id].p_refs[i].id == p_id)
  {
    return i;
  }
  else
  {
    
  }


  return -1;
}

void insert_product(Product *product)
{
  int i;
  int insert_pos = product_count;
  for (i = 0; i < product_count; i++)
    if (((*products[i]->price) > (*product->price)) || (((*product->price) == (*products[i]->price)) && (product->id < products[i]->id)))
  {
    insert_pos = i;
    break;
  }
  else
  {
    
  }


  shift_right_array((void *) products, product_count++, insert_pos);
  products[insert_pos] = product;
}

void insert_into_order(Product_ref prod_arr[], int ref_cnt, Product_ref p_ref)
{
  int pos;
  int id = p_ref.id;
  for (pos = 0; (pos < ref_cnt) && (strcmp(p_info[prod_arr[pos].id].desc, p_info[id].desc) < 0); pos++)
    ;

  shift_right_array((void *) prod_arr, ref_cnt, pos);
  prod_arr[pos] = p_ref;
}

void add_stock(int p_id, int quantity)
{
  if (p_id >= product_count)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p_id);
  }
  else
  {
    p_info[p_id].stock += quantity;
  }

}

void remove_stock(int p_id, int quantity)
{
  if (p_id >= product_count)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p_id);
  }
  else
  {
    if (p_info[p_id].stock < quantity)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantity, p_id);
    }
    else
    {
      p_info[p_id].stock -= quantity;
    }

  }

}

void add_product(char *desc, int price, int weight, int stock)
{
  Product product;
  product.desc = malloc((strlen(desc) * (sizeof(char))) + 1);
  product.price = malloc(sizeof(int));
  strcpy(product.desc, desc);
  product.id = product_count;
  product.weight = weight;
  *product.price = price;
  product.stock = stock;
  p_info[product.id] = product;
  insert_product(&p_info[product.id]);
  printf("Novo produto %d.\n", product.id);
}

void remove_product(int o_id, int p_id)
{
  if (o_id >= order_count)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
  }
  else
  {
    if (p_id >= product_count)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
    }
    else
    {
      int pos;
      if ((pos = find_product_pos(o_id, p_id)) > (-1))
      {
        int id = orders[o_id].p_refs[pos].id;
        add_stock(orders[o_id].p_refs[pos].id, orders[o_id].p_refs[pos].stock);
        orders[o_id].weight -= p_info[id].weight * orders[o_id].p_refs[pos].stock;
        orders[o_id].p_refs[pos].stock = 0;
      }
      else
      {
        
      }

    }

  }

}

void alter_price(int p_id, int new_price)
{
  if (p_id >= product_count)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p_id);
  }
  else
  {
    Product *prod;
    int i;
    *p_info[p_id].price = new_price;
    for (i = 0; products[i]->id != p_id; i++)
      ;

    prod = products[i];
    for (; i < product_count; products[i] = products[i + 1], i++)
      ;

    product_count--;
    insert_product(prod);
  }

}

void add_to_order(int o_id, int p_id, int stock)
{
  if (o_id >= order_count)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
  }
  else
  {
    if (p_id >= product_count)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
    }
    else
    {
      if (p_info[p_id].stock < stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p_id, o_id);
      }
      else
      {
        if (((p_info[p_id].weight * stock) + orders[o_id].weight) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", p_id, o_id, 200);
        }
        else
        {
          Product_ref p_ref;
          int pos;
          p_info[p_id].stock -= stock;
          orders[o_id].weight += p_info[p_id].weight * stock;
          if ((pos = find_product_pos(o_id, p_id)) > (-1))
          {
            orders[o_id].p_refs[pos].stock += stock;
            return;
          }
          else
          {
            
          }

          p_ref.id = p_id;
          p_ref.stock = stock;
          insert_into_order(orders[o_id].p_refs, orders[o_id].ref_cnt, p_ref);
          orders[o_id].ref_cnt++;
        }

      }

    }

  }

}

void new_order()
{
  Order order;
  order.weight = 0;
  order.ref_cnt = 0;
  orders[order_count] = order;
  printf("Nova encomenda %d.\n", order_count++);
}

void find_most_product(int p_id)
{
  if (p_id >= product_count)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p_id);
  }
  else
  {
    int x;
    int pos;
    int order = -1;
    int stock = 0;
    for (x = 0; x < order_count; x++)
      if (((pos = find_product_pos(x, p_id)) > (-1)) && (orders[x].p_refs[pos].stock > stock))
    {
      order = x;
      stock = orders[x].p_refs[pos].stock;
    }
    else
    {
      
    }


    if (stock)
    {
      printf("Maximo produto %d %d %d.\n", p_id, order, stock);
    }
    else
    {
      
    }

  }

}

void calc_order_cost(int o_id)
{
  if (o_id >= order_count)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", o_id);
  }
  else
  {
    int i;
    int total = 0;
    for (i = 0; i < orders[o_id].ref_cnt; i++)
      total += orders[o_id].p_refs[i].stock * (*p_info[orders[o_id].p_refs[i].id].price);

    printf("Custo da encomenda %d %d.\n", o_id, total);
  }

}

void show_product(int o_id, int p_id)
{
  if (o_id >= order_count)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
  }
  else
  {
    if (p_id >= product_count)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", p_id);
    }
    else
    {
      int pos;
      if ((pos = find_product_pos(o_id, p_id)) > (-1))
      {
        int id = orders[o_id].p_refs[pos].id;
        printf("%s %d.\n", p_info[id].desc, orders[o_id].p_refs[pos].stock);
        return;
      }
      else
      {
        
      }

      printf("%s 0.\n", p_info[p_id].desc);
    }

  }

}

void show_order(int o_id)
{
  if (o_id >= order_count)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
  }
  else
  {
    int i;
    printf("Encomenda %d\n", o_id);
    for (i = 0; i < orders[o_id].ref_cnt; i++)
      if (orders[o_id].p_refs[i].stock)
    {
      int id = orders[o_id].p_refs[i].id;
      printf("* %s %d %d\n", p_info[id].desc, *p_info[id].price, orders[o_id].p_refs[i].stock);
    }
    else
    {
      
    }


  }

}

void show_products()
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < product_count; i++)
    printf("* %s %d %d\n", products[i]->desc, *products[i]->price, products[i]->stock);

}

void free_memory()
{
  int i;
  for (i = 0; i < product_count; i++)
  {
    free(p_info[i].desc);
    free(p_info[i].price);
  }

}

int main()
{
  char buff[64];
  char input[80];
  char command;
  int nums_in[3];
  void (*funcs[256])();
  funcs['N'] = new_order;
  funcs['p'] = alter_price;
  funcs['l'] = show_products;
  funcs['q'] = add_stock;
  funcs['r'] = remove_stock;
  funcs['R'] = remove_product;
  funcs['L'] = show_order;
  funcs['A'] = add_to_order;
  funcs['C'] = calc_order_cost;
  funcs['a'] = add_product;
  funcs['E'] = show_product;
  funcs['m'] = find_most_product;
  for (;;)
  {
    fgets(input, 80, stdin);
    command = new_sym_var(sizeof(char) * 8);
    for (int buff_index = 0; buff_index < 10; buff_index++)
    {
      buff[buff_index] = new_sym_var(sizeof(char) * 8);
    }

    buff[10 - 1] = '\0';
    nums_in[0] = new_sym_var(sizeof(int) * 8);
    nums_in[1] = new_sym_var(sizeof(int) * 8);
    nums_in[2] = new_sym_var(sizeof(int) * 8);
    if (command == 'x')
    {
      break;
    }
    else
    {
      
    }

    if (strchr("N l", command))
    {
      funcs[(int) command]();
    }
    else
    {
      
    }

    if (strchr("L C m", command))
    {
      funcs[(int) command](atoi(buff));
    }
    else
    {
      
    }

    if (strchr("q E R r p", command))
    {
      funcs[(int) command](atoi(buff), nums_in[0]);
    }
    else
    {
      
    }

    if (strchr("A", command))
    {
      funcs[(int) command](atoi(buff), nums_in[0], nums_in[1]);
    }
    else
    {
      
    }

    if (strchr("a", command))
    {
      funcs[(int) command](buff, nums_in[0], nums_in[1], nums_in[2]);
    }
    else
    {
      
    }

  }

  free_memory();
  return 0;
}
