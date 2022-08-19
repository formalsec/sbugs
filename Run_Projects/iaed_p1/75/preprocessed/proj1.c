/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int total_prods = 0;
int total_orders = 0;
typedef struct 
{
  int id;
  char description[64];
  int price;
  int weight;
  int quantity;
} Product;
typedef struct 
{
  int idp;
  int qtt;
} Order;
typedef struct 
{
  int idp;
  int price;
} sort_prod;
typedef struct 
{
  int idp;
  int quantity;
  char description[64];
} sort_order;
Product list_of_prods[10000];
Order list_of_orders[500][200];
void new_product(void);
void inc_stock(void);
void new_order(void);
void add_prod_order(void);
void rem_units(void);
void rem_prod_order(void);
void price_order(void);
void change_price(void);
void print_details_order(void);
void identifier(void);
void list_prod(void);
void list_prod_order(void);
void increment_stock(int, int);
int conditionsR_check(int, int);
void rm_prod(int, int);
int conditionsA_check(int, int, int);
void add(int, int, int);
int conditionsr_check(int, int);
void rem(int, int);
void sort_array(sort_prod [], int, int);
int partition(sort_prod [], int, int);
void print_details_prods(sort_prod []);
void exchange(sort_prod *, sort_prod *);
void sort_array_alpha(sort_order [], int, int);
int partition_alpha(sort_order [], int, int);
void exchange_alpha(sort_order *, sort_order *);
void print_details_prods_order(sort_order [], int, int);
int ordered_quantity(int, int);
int main()
{
  char command;
  while (1)
  {
    command = getchar();
    switch (command)
    {
      case 'a':
        new_product();
        break;

      case 'q':
        inc_stock();
        break;

      case 'N':
        new_order();
        break;

      case 'A':
        add_prod_order();
        break;

      case 'r':
        rem_units();
        break;

      case 'R':
        rem_prod_order();
        break;

      case 'C':
        price_order();
        break;

      case 'p':
        change_price();
        break;

      case 'E':
        print_details_order();
        break;

      case 'm':
        identifier();
        break;

      case 'l':
        list_prod();
        break;

      case 'L':
        list_prod_order();
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}

void new_product(void)
{
  for (int list_of_prods_index = 0; list_of_prods_index < 10; list_of_prods_index++)
  {
    list_of_prods[total_prods].description[list_of_prods_index] = new_sym_var(sizeof(char) * 8);
  }

  list_of_prods[total_prods].description[10 - 1] = '\0';
  list_of_prods[total_prods].price = new_sym_var(sizeof(int) * 8);
  list_of_prods[total_prods].weight = new_sym_var(sizeof(int) * 8);
  list_of_prods[total_prods].quantity = new_sym_var(sizeof(int) * 8);
  list_of_prods[total_prods].id = total_prods;
  printf("Novo produto %d.\n", total_prods);
  total_prods++;
}

void inc_stock(void)
{
  int idp;
  int qtt;
  idp = new_sym_var(sizeof(int) * 8);
  qtt = new_sym_var(sizeof(int) * 8);
  if (idp >= total_prods)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      increment_stock(idp, qtt);
    }
  }

}

void new_order(void)
{
  int i;
  for (i = 0; i < 200; i++)
  {
    list_of_orders[total_orders][i].idp = -1;
    list_of_orders[total_orders][i].qtt = -1;
  }

  printf("Nova encomenda %d.\n", total_orders);
  total_orders++;
}

void add_prod_order(void)
{
  int ide;
  int prod_idp;
  int new_qtt;
  ide = new_sym_var(sizeof(int) * 8);
  prod_idp = new_sym_var(sizeof(int) * 8);
  new_qtt = new_sym_var(sizeof(int) * 8);
  switch (conditionsA_check(ide, prod_idp, new_qtt))
  {
    case 0:
      add(ide, prod_idp, new_qtt);
      rem(prod_idp, new_qtt);
      break;

    case 1:
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod_idp, ide);
      break;

    case 2:
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod_idp, ide);
      break;

    case 3:
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod_idp, ide);
      break;

    case 4:
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod_idp, ide);
      break;

  }

}

int conditionsA_check(int ide, int prod_idp, int new_qtt)
{
  int i = 0;
  int total_weight = 0;
  int prod_weight;
  int prod_quantity;
  int index;
  if (ide >= total_orders)
  {
    {
      return 1;
    }
  }
  else
  {
    if (prod_idp >= total_prods)
    {
      {
        return 2;
      }
    }
    else
    {
      if (new_qtt > list_of_prods[prod_idp].quantity)
      {
        {
          return 3;
        }
      }
      else
      {
        
      }

    }

  }

  while (((index = list_of_orders[ide][i].idp) != (-1)) && (i < 200))
  {
    prod_weight = list_of_prods[list_of_orders[ide][i].idp].weight;
    prod_quantity = list_of_orders[ide][i].qtt;
    total_weight += prod_quantity * prod_weight;
    i++;
  }

  total_weight += list_of_prods[prod_idp].weight * new_qtt;
  if (total_weight > 200)
  {
    {
      return 4;
    }
  }
  else
  {
    {
      return 0;
    }
  }

}

void add(int ide, int prod_idp, int new_qtt)
{
  int ind;
  int i = 0;
  int exist = 0;
  while ((ind = list_of_orders[ide][i].idp) != (-1))
  {
    if (ind == prod_idp)
    {
      {
        list_of_orders[ide][i].qtt += new_qtt;
        exist = 1;
        break;
      }
    }
    else
    {
      
    }

    i++;
  }

  if (!exist)
  {
    {
      list_of_orders[ide][i].idp = prod_idp;
      list_of_orders[ide][i].qtt = new_qtt;
    }
  }
  else
  {
    
  }

}

void rem_units(void)
{
  int prod_idp;
  int prod_qtd;
  prod_idp = new_sym_var(sizeof(int) * 8);
  prod_qtd = new_sym_var(sizeof(int) * 8);
  switch (conditionsr_check(prod_idp, prod_qtd))
  {
    case 0:
      rem(prod_idp, prod_qtd);
      break;

    case 1:
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod_idp);
      break;

    case 2:
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", prod_qtd, prod_idp);
      break;

  }

}

int conditionsr_check(int prod_idp, int prod_qtd)
{
  if (prod_idp >= total_prods)
  {
    {
      return 1;
    }
  }
  else
  {
    if (prod_qtd > list_of_prods[prod_idp].quantity)
    {
      {
        return 2;
      }
    }
    else
    {
      {
        return 0;
      }
    }

  }

}

void rem_prod_order(void)
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  switch (conditionsR_check(ide, idp))
  {
    case 0:
      rm_prod(ide, idp);
      break;

    case 1:
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      break;

    case 2:
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      break;

    case 3:
      break;

  }

}

int conditionsR_check(int ide, int idp)
{
  int value;
  int i = 0;
  int exist = 0;
  if (ide >= total_orders)
  {
    {
      return 1;
    }
  }
  else
  {
    if (idp >= total_prods)
    {
      {
        return 2;
      }
    }
    else
    {
      {
        while (((value = list_of_orders[ide][i].idp) != (-1)) && (i < 200))
        {
          if (value == idp)
          {
            {
              exist = 1;
            }
          }
          else
          {
            
          }

          i++;
        }

        if (exist)
        {
          {
            return 0;
          }
        }
        else
        {
          {
            return 3;
          }
        }

      }
    }

  }

}

void rm_prod(int ide, int idp)
{
  int value;
  int quantity;
  int i = 0;
  int deleting = 0;
  quantity = ordered_quantity(ide, idp);
  increment_stock(idp, quantity);
  while (((value = list_of_orders[ide][i].idp) != (-1)) && (i < 200))
  {
    if ((value == idp) && (!deleting))
    {
      {
        deleting = 1;
      }
    }
    else
    {
      if (deleting)
      {
        {
          list_of_orders[ide][i - 1].idp = list_of_orders[ide][i].idp;
          list_of_orders[ide][i - 1].qtt = list_of_orders[ide][i].qtt;
        }
      }
      else
      {
        
      }

    }

    i++;
  }

  list_of_orders[ide][i - 1].idp = -1;
  list_of_orders[ide][i - 1].qtt = -1;
}

void price_order(void)
{
  int i = 0;
  int index;
  int ide;
  int total_cost = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= total_orders)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      while (((index = list_of_orders[ide][i].idp) != (-1)) && (i < 200))
      {
        total_cost += list_of_prods[index].price * list_of_orders[ide][i].qtt;
        i++;
      }

      printf("Custo da encomenda %d %d.\n", ide, total_cost);
    }
  }

}

void change_price(void)
{
  int idp;
  int new_price;
  idp = new_sym_var(sizeof(int) * 8);
  new_price = new_sym_var(sizeof(int) * 8);
  if (idp >= total_prods)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      list_of_prods[idp].price = new_price;
    }
  }

}

void print_details_order(void)
{
  int order_ide;
  int prod_idp;
  int quantity;
  order_ide = new_sym_var(sizeof(int) * 8);
  prod_idp = new_sym_var(sizeof(int) * 8);
  if (order_ide >= total_orders)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", order_ide);
    }
  }
  else
  {
    if (prod_idp >= total_prods)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", prod_idp);
      }
    }
    else
    {
      {
        quantity = ordered_quantity(order_ide, prod_idp);
        printf("%s %d.\n", list_of_prods[prod_idp].description, quantity);
      }
    }

  }

}

void identifier(void)
{
  int idp;
  int i;
  int index = 0;
  int ide;
  int max_qtt = -1;
  int exist = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= total_prods)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      for (i = 0; i < total_orders; i++)
      {
        for (index = 0; index < 200; index++)
        {
          if ((list_of_orders[i][index].idp == idp) && (list_of_orders[i][index].qtt > max_qtt))
          {
            {
              max_qtt = list_of_orders[i][index].qtt;
              ide = i;
              exist = 1;
            }
          }
          else
          {
            
          }

        }

      }

      if (exist)
      {
        {
          printf("Maximo produto %d %d %d.\n", idp, ide, max_qtt);
        }
      }
      else
      {
        
      }

    }
  }

}

void list_prod(void)
{
  sort_prod new_array[10000];
  int i;
  for (i = 0; i < total_prods; i++)
  {
    new_array[i].idp = i;
    new_array[i].price = list_of_prods[i].price;
  }

  sort_array(new_array, 0, total_prods - 1);
  print_details_prods(new_array);
}

void sort_array(sort_prod new_array[], int start, int end)
{
  int mid;
  if (start < end)
  {
    {
      mid = partition(new_array, start, end);
      sort_array(new_array, start, mid - 1);
      sort_array(new_array, mid + 1, end);
    }
  }
  else
  {
    
  }

}

int partition(sort_prod new_array[], int start, int end)
{
  int l = start;
  int r = end - 1;
  sort_prod pivot = new_array[end];
  while (l < r)
  {
    while ((new_array[l].price < pivot.price) || ((new_array[l].price == pivot.price) && (new_array[l].idp < pivot.idp)))
    {
      l++;
    }

    while ((new_array[r].price > pivot.price) || ((new_array[r].price == pivot.price) && (new_array[r].idp > pivot.idp)))
    {
      if (r == l)
      {
        break;
      }
      else
      {
        
      }

      r--;
    }

    if (l < r)
    {
      {
        exchange(&new_array[l], &new_array[r]);
      }
    }
    else
    {
      
    }

  }

  if ((new_array[l].price > pivot.price) || ((new_array[l].price == pivot.price) && (new_array[l].idp > pivot.idp)))
  {
    exchange(&new_array[l], &new_array[end]);
  }
  else
  {
    
  }

  return l;
}

void exchange(sort_prod *left, sort_prod *right)
{
  sort_prod temp;
  temp.idp = left->idp;
  temp.price = left->price;
  left->idp = right->idp;
  left->price = right->price;
  right->idp = temp.idp;
  right->price = temp.price;
}

void print_details_prods(sort_prod sorted_prods[])
{
  int i;
  int idp;
  printf("Produtos\n");
  for (i = 0; i < total_prods; i++)
  {
    idp = sorted_prods[i].idp;
    printf("* %s %d %d\n", list_of_prods[idp].description, list_of_prods[idp].price, list_of_prods[idp].quantity);
  }

}

void list_prod_order(void)
{
  sort_order new_array[500];
  int i = 0;
  int index = 0;
  int ide;
  int value;
  int quant;
  int total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= total_orders)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  while (((value = list_of_orders[ide][i].idp) != (-1)) && (i < 200))
  {
    if ((quant = list_of_orders[ide][i].qtt) > 0)
    {
      {
        new_array[index].idp = list_of_prods[value].id;
        strcpy(new_array[index].description, list_of_prods[value].description);
        new_array[index].quantity = quant;
        index++;
        total++;
      }
    }
    else
    {
      
    }

    i++;
  }

  sort_array_alpha(new_array, 0, total - 1);
  print_details_prods_order(new_array, ide, total);
}

void sort_array_alpha(sort_order new_array[], int start, int end)
{
  int mid;
  if (start < end)
  {
    {
      mid = partition_alpha(new_array, start, end);
      sort_array_alpha(new_array, start, mid - 1);
      sort_array_alpha(new_array, mid + 1, end);
    }
  }
  else
  {
    
  }

}

int partition_alpha(sort_order new_array[], int start, int end)
{
  int l = start;
  int r = end - 1;
  sort_order pivot = new_array[end];
  while (l < r)
  {
    while ((strcmp(new_array[l].description, pivot.description) < 0) || ((strcmp(new_array[l].description, pivot.description) == 0) && (new_array[l].idp < pivot.idp)))
    {
      l++;
    }

    while ((strcmp(new_array[r].description, pivot.description) > 0) || ((strcmp(new_array[r].description, pivot.description) == 0) && (new_array[r].idp > pivot.idp)))
    {
      if (r == l)
      {
        break;
      }
      else
      {
        
      }

      r--;
    }

    if (l < r)
    {
      {
        exchange_alpha(&new_array[l], &new_array[r]);
      }
    }
    else
    {
      
    }

  }

  if ((strcmp(new_array[l].description, pivot.description) > 0) || ((strcmp(new_array[l].description, pivot.description) == 0) && (new_array[l].idp > pivot.idp)))
  {
    exchange_alpha(&new_array[l], &new_array[end]);
  }
  else
  {
    
  }

  return l;
}

void exchange_alpha(sort_order *left, sort_order *right)
{
  sort_order temp;
  strcpy(temp.description, left->description);
  temp.idp = left->idp;
  temp.quantity = left->quantity;
  strcpy(left->description, right->description);
  left->idp = right->idp;
  left->quantity = right->quantity;
  strcpy(right->description, temp.description);
  right->idp = temp.idp;
  right->quantity = temp.quantity;
}

void print_details_prods_order(sort_order sorted_prods[], int ide, int total)
{
  int i;
  int id;
  int price;
  printf("Encomenda %d\n", ide);
  for (i = 0; i < total; i++)
  {
    id = sorted_prods[i].idp;
    price = list_of_prods[id].price;
    printf("* %s %d %d\n", sorted_prods[i].description, price, sorted_prods[i].quantity);
  }

}

int ordered_quantity(int ide, int idp)
{
  int i = 0;
  int index;
  int qtt;
  while (((index = list_of_orders[ide][i].idp) != (-1)) && (i < 200))
  {
    if (index == idp)
    {
      {
        qtt = list_of_orders[ide][i].qtt;
        return qtt;
      }
    }
    else
    {
      
    }

    i++;
  }

  return 0;
}

void increment_stock(int idp, int qtt)
{
  list_of_prods[idp].quantity += qtt;
}

void rem(int prod_idp, int prod_qtd)
{
  if ((list_of_prods[prod_idp].quantity - prod_qtd) < 0)
  {
    {
      list_of_prods[prod_idp].quantity = 0;
    }
  }
  else
  {
    {
      list_of_prods[prod_idp].quantity -= prod_qtd;
    }
  }

}
