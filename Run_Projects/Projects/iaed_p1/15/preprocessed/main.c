/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "product.h"
#include "stock.h"
#include "order.h"
#include "orders.h"


Stock *stock;
Orders *orders;
void read_line(char *buf)
{
  int i;
  fgets(buf, 100, stdin);
  for (i = 0; (i < 100) && (buf[i] != 0); i++)
  {
    if (buf[i] == ':')
    {
      buf[i] = ' ';
    }
    else
    {
      
    }

  }

}

void command_a()
{
  char buf[100];
  char desc[63];
  int preco;
  int peso;
  int qtd;
  Product *p;
  read_line(buf);
  for (int desc_index = 0; desc_index < 10; desc_index++)
  {
    desc[desc_index] = new_sym_var(sizeof(char) * 8);
  }

  desc[10 - 1] = '\0';
  preco = new_sym_var(sizeof(int) * 8);
  peso = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  p = product_new(desc, preco, peso);
  stock_add_product(stock, p, qtd);
  printf("Novo produto %d.\n", product_get_id(p));
}

void command_q()
{
  char buf[100];
  int pid;
  int qtd;
  Stock_Product *sp;
  read_line(buf);
  pid = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  sp = stock_get_product(stock, pid);
  if (sp == 0)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", pid);
    return;
  }
  else
  {
    
  }

  stock_product_update_quantity(sp, qtd);
}

void command_r()
{
  char buf[100];
  int pid;
  int qtd;
  int error;
  Stock_Product *sp;
  read_line(buf);
  pid = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  sp = stock_get_product(stock, pid);
  if (sp == 0)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pid);
    return;
  }
  else
  {
    
  }

  error = stock_product_update_quantity(sp, -qtd);
  if (error)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, pid);
    return;
  }
  else
  {
    
  }

}

void command_p()
{
  char buf[100];
  int pid;
  int price;
  Stock_Product *sp;
  read_line(buf);
  pid = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  sp = stock_get_product(stock, pid);
  if (sp == 0)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pid);
    return;
  }
  else
  {
    
  }

  product_set_price(stock_product_get_product(sp), price);
}

void command_N()
{
  Order *o = order_new();
  orders_add_order(orders, o);
  printf("Nova encomenda %d.\n", order_get_id(o));
}

void command_A()
{
  char buf[100];
  int oid;
  int pid;
  int qtd;
  int error;
  Order *o;
  Stock_Product *sp;
  read_line(buf);
  oid = new_sym_var(sizeof(int) * 8);
  pid = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  o = orders_get_order(orders, oid);
  if (o == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", pid, oid);
    return;
  }
  else
  {
    
  }

  sp = stock_get_product(stock, pid);
  if (sp == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", pid, oid);
    return;
  }
  else
  {
    
  }

  if (order_add_product(o, sp->product, qtd) == 0)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", pid, oid);
    return;
  }
  else
  {
    
  }

  error = stock_product_reserve_quantity(sp, qtd);
  if (error)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", pid, oid);
    return;
  }
  else
  {
    
  }

}

void command_R()
{
  char buf[100];
  int oid;
  int pid;
  int error;
  Order *o;
  Stock_Product *sp;
  read_line(buf);
  oid = new_sym_var(sizeof(int) * 8);
  pid = new_sym_var(sizeof(int) * 8);
  o = orders_get_order(orders, oid);
  if (o == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", pid, oid);
    return;
  }
  else
  {
    
  }

  sp = stock_get_product(stock, pid);
  if (sp == 0)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", pid, oid);
    return;
  }
  else
  {
    
  }

  error = order_remove_product(o, pid);
  if (error)
  {
    return;
  }
  else
  {
    
  }

}

void command_C()
{
  char buf[100];
  int oid;
  Order *o;
  int custo;
  read_line(buf);
  oid = new_sym_var(sizeof(int) * 8);
  o = orders_get_order(orders, oid);
  if (o == 0)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", oid);
    return;
  }
  else
  {
    
  }

  custo = order_get_cost(o);
  printf("Custo da encomenda %d %d.\n", oid, custo);
}

void command_E()
{
  char buf[100];
  int oid;
  int pid;
  Order *o;
  Stock_Product *sp;
  Order_Product *op;
  read_line(buf);
  oid = new_sym_var(sizeof(int) * 8);
  pid = new_sym_var(sizeof(int) * 8);
  o = orders_get_order(orders, oid);
  if (o == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", oid);
    return;
  }
  else
  {
    
  }

  sp = stock_get_product(stock, pid);
  if (sp == 0)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", pid);
    return;
  }
  else
  {
    
  }

  op = order_get_product(o, pid);
  printf("%s %d.\n", product_get_desc(sp->product), order_product_get_quantity(op));
}

void command_m()
{
  char buf[100];
  int pid;
  Stock_Product *sp;
  read_line(buf);
  pid = new_sym_var(sizeof(int) * 8);
  sp = stock_get_product(stock, pid);
  if (sp == 0)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", pid);
    return;
  }
  else
  {
    
  }

}

void command_l(char command)
{
  if (command == 'l')
  {
    stock_list_products_by_price(stock);
  }
  else
  {
    stock_print(stock);
    stock_list_products(stock);
  }

}

void command_L(char command)
{
  char buf[100];
  int oid;
  Order *o;
  read_line(buf);
  oid = new_sym_var(sizeof(int) * 8);
  o = orders_get_order(orders, oid);
  if (o == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", oid);
    return;
  }
  else
  {
    
  }

  if (command == 'L')
  {
    order_list_products_by_desc(o);
  }
  else
  {
    order_print(o);
    order_list_products(o);
  }

}

int main()
{
  char command;
  stock = stock_init();
  orders = orders_init();
  do
  {
    command = getchar();
    switch (command)
    {
      case 'a':
        command_a();
        break;

      case 'q':
        command_q();
        break;

      case 'N':
        command_N();
        break;

      case 'A':
        command_A();
        break;

      case 'r':
        command_r();
        break;

      case 'R':
        command_R();
        break;

      case 'p':
        command_p();
        break;

      case 'E':
        command_E();
        break;

      case 'm':
        command_m();
        break;

      case 'l':

      case 'k':
        command_l(command);
        break;

      case 'L':

      case 'K':
        command_L(command);
        break;

      case 'C':
        command_C();
        break;

      case 'x':
        break;

    }

  }
  while (command != 'x');
  return 0;
}

