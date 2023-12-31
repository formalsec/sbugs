#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utilities.h"


void create_prod();
void add_stock();
void create_order();
void prod_to_order();
void rm_stock();
void rm_prod();
void calc_cost();
void change_price();
void list_prod();
void most_occ();
void list_all();
void list_order();
int main()
{
  char command;
  while ((command = getchar()) != 'x')
  {
    switch (command)
    {
      case 'a':
        create_prod();
        break;

      case 'q':
        add_stock();
        break;

      case 'N':
        create_order();
        break;

      case 'A':
        prod_to_order();
        break;

      case 'r':
        rm_stock();
        break;

      case 'R':
        rm_prod();
        break;

      case 'C':
        calc_cost();
        break;

      case 'p':
        change_price();
        break;

      case 'E':
        list_prod();
        break;

      case 'm':
        most_occ();
        break;

      case 'l':
        list_all();
        break;

      case 'L':
        list_order();
        break;

    }

  }

  return 0;
}

void create_prod()
{
  for (int sys_index = 0; sys_index < 10; sys_index++)
  {
    sys[totalp].desc[sys_index] = new_sym_var(sizeof(char) * 8);
  }

  sys[totalp].desc[10 - 1] = '\0';
  sys[totalp].price = new_sym_var(sizeof(int) * 8);
  sys[totalp].wgt = new_sym_var(sizeof(int) * 8);
  sys[totalp].qtt = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", totalp++);
}

void add_stock()
{
  int p_id;
  int qtt;
  p_id = new_sym_var(sizeof(int) * 8);
  qtt = new_sym_var(sizeof(int) * 8);
  if (p_id >= totalp)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p_id);
    return;
  }
  else
  {
    
  }

  sys[p_id].qtt += qtt;
}

void create_order()
{
  printf("Nova encomenda %d.\n", totalo++);
}

void prod_to_order()
{
  int o_id;
  int p_id;
  int qtt;
  o_id = new_sym_var(sizeof(int) * 8);
  p_id = new_sym_var(sizeof(int) * 8);
  qtt = new_sym_var(sizeof(int) * 8);
  if (o_id >= totalo)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
    return;
  }
  else
  {
    
  }

  if (p_id >= totalp)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
    return;
  }
  else
  {
    
  }

  if (sys[p_id].qtt < qtt)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p_id, o_id);
    return;
  }
  else
  {
    
  }

  if (((sys[p_id].wgt * qtt) + ords[o_id].wgt) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p_id, o_id);
    return;
  }
  else
  {
    
  }

  if (!prod_in(p_id, &ords[o_id]))
  {
    int num = ords[o_id].num++;
    ords[o_id].ids[num] = p_id;
  }
  else
  {
    
  }

  sys[p_id].qtt -= qtt;
  ords[o_id].prods[p_id] += qtt;
  ords[o_id].wgt += sys[p_id].wgt * qtt;
}

void rm_stock()
{
  int p_id;
  int qtt;
  p_id = new_sym_var(sizeof(int) * 8);
  qtt = new_sym_var(sizeof(int) * 8);
  if (p_id >= totalp)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p_id);
    return;
  }
  else
  {
    
  }

  if (sys[p_id].qtt < qtt)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtt, p_id);
    return;
  }
  else
  {
    
  }

  sys[p_id].qtt -= qtt;
}

void rm_prod()
{
  int o_id;
  int p_id;
  int *prod_qtt;
  o_id = new_sym_var(sizeof(int) * 8);
  p_id = new_sym_var(sizeof(int) * 8);
  if (o_id >= totalo)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p_id, o_id);
    return;
  }
  else
  {
    
  }

  if (p_id >= totalp)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p_id, o_id);
    return;
  }
  else
  {
    
  }

  prod_qtt = &ords[o_id].prods[p_id];
  sys[p_id].qtt += *prod_qtt;
  ords[o_id].wgt -= sys[p_id].wgt * (*prod_qtt);
  *prod_qtt = 0;
}

void calc_cost()
{
  int i;
  int o_id;
  int cost = 0;
  o_id = new_sym_var(sizeof(int) * 8);
  if (o_id >= totalo)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", o_id);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < ords[o_id].num; i++)
  {
    int id = ords[o_id].ids[i];
    int qtt = ords[o_id].prods[id];
    cost += sys[id].price * qtt;
  }

  printf("Custo da encomenda %d %d.\n", o_id, cost);
}

void change_price()
{
  int p_id;
  int new_p;
  p_id = new_sym_var(sizeof(int) * 8);
  new_p = new_sym_var(sizeof(int) * 8);
  if (p_id >= totalp)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p_id);
    return;
  }
  else
  {
    
  }

  sys[p_id].price = new_p;
}

void list_prod()
{
  int o_id;
  int p_id;
  int qtt;
  o_id = new_sym_var(sizeof(int) * 8);
  p_id = new_sym_var(sizeof(int) * 8);
  if (o_id >= totalo)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
    return;
  }
  else
  {
    
  }

  if (p_id >= totalp)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", p_id);
    return;
  }
  else
  {
    
  }

  qtt = ords[o_id].prods[p_id];
  printf("%s %d.\n", sys[p_id].desc, qtt);
}

void most_occ()
{
  int i;
  int p_id;
  int max = 0;
  int max_o;
  p_id = new_sym_var(sizeof(int) * 8);
  if (p_id >= totalp)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p_id);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < totalo; i++)
  {
    int qtt = ords[i].prods[p_id];
    if (qtt > max)
    {
      max = qtt;
      max_o = i;
    }
    else
    {
      
    }

  }

  if (max > 0)
  {
    printf("Maximo produto %d %d %d.\n", p_id, max_o, max);
  }
  else
  {
    
  }

}

void list_all()
{
  int i;
  int *ids = malloc(totalp * (sizeof(int)));
  for (i = 0; i < totalp; i++)
    ids[i] = i;

  merge_sort(ids, 0, totalp - 1, price_ordered);
  puts("Produtos");
  for (i = 0; i < totalp; i++)
    printf("* %s %d %d\n", sys[ids[i]].desc, sys[ids[i]].price, sys[ids[i]].qtt);

  free(ids);
}

void list_order()
{
  int i;
  int o_id;
  int num;
  int *ids;
  o_id = new_sym_var(sizeof(int) * 8);
  if (o_id >= totalo)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", o_id);
    return;
  }
  else
  {
    
  }

  num = ords[o_id].num;
  ids = ords[o_id].ids;
  merge_sort(ids, 0, num - 1, ab_ordered);
  printf("Encomenda %d\n", o_id);
  for (i = 0; i < num; i++)
  {
    int qtt = ords[o_id].prods[ids[i]];
    if (qtt > 0)
    {
      printf("* %s %d %d\n", sys[ids[i]].desc, sys[ids[i]].price, qtt);
    }
    else
    {
      
    }

  }

}

