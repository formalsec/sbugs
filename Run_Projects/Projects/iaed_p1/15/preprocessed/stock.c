/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "stock.h"


Stock *stock_init()
{
  Stock *stock = (Stock *) malloc(sizeof(Stock));
  if (errno > 0)
  {
    perror("stock_init: criar_stock");
    exit(errno);
  }
  else
  {
    
  }

  ;
  stock->count = 0;
  stock->products = 0;
  stock->last_product = 0;
  return stock;
}

void stock_product_free(Stock_Product *sp)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_free");
    exit(1);
  }
  else
  {
    
  }

  ;
  product_free((Product *) sp->product);
  free(sp);
}

void stock_free(Stock *s)
{
  Stock_Product *sp;
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_free");
    exit(1);
  }
  else
  {
    
  }

  ;
  sp = s->products;
  while (sp != 0)
  {
    Stock_Product *next = sp->next;
    stock_product_free(sp);
    sp = next;
  }

  free(s);
}

int stock_count(const Stock *s)
{
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_count");
    exit(1);
  }
  else
  {
    
  }

  ;
  return s->count;
}

Stock_Product *stock_get_product(const Stock *s, int pid)
{
  Stock_Product *sp;
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_get_product");
    exit(1);
  }
  else
  {
    
  }

  ;
  sp = s->products;
  while (sp != 0)
  {
    if (sp->product->id == pid)
    {
      return sp;
    }
    else
    {
      
    }

    sp = sp->next;
  }

  return 0;
}

Stock_Product *stock_add_product(Stock *s, const Product *p, int qtd)
{
  Stock_Product *sp;
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_add_product: Stock");
    exit(1);
  }
  else
  {
    
  }

  ;
  if (p == 0)
  {
    printf("%s: null pointer\n", "stock_add_product: Product");
    exit(1);
  }
  else
  {
    
  }

  ;
  if (s->count == 10000)
  {
    return 0;
  }
  else
  {
    
  }

  sp = (Stock_Product *) malloc(sizeof(Stock_Product));
  if (errno > 0)
  {
    perror("stock_add_product: criar_stock_product");
    exit(errno);
  }
  else
  {
    
  }

  ;
  sp->product = p;
  sp->qtd = qtd;
  sp->qtd_reserved = 0;
  sp->next = 0;
  sp->previous = s->last_product;
  s->count++;
  if (s->last_product != 0)
  {
    s->last_product->next = sp;
  }
  else
  {
    
  }

  s->last_product = sp;
  if (s->products == 0)
  {
    s->products = sp;
  }
  else
  {
    
  }

  return sp;
}

Product *stock_product_get_product(const Stock_Product *sp)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_get_product");
    exit(1);
  }
  else
  {
    
  }

  ;
  return (Product *) sp->product;
}

int stock_product_get_quantity(const Stock_Product *sp)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_get_quantity");
    exit(1);
  }
  else
  {
    
  }

  ;
  return sp->qtd;
}

int stock_product_get_reserved(const Stock_Product *sp)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_get_reserved");
    exit(1);
  }
  else
  {
    
  }

  ;
  return sp->qtd_reserved;
}

int stock_product_get_available(const Stock_Product *sp)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_get_available");
    exit(1);
  }
  else
  {
    
  }

  ;
  return sp->qtd - sp->qtd_reserved;
}

int stock_product_update_quantity(Stock_Product *sp, int qtd)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_update_quantity");
    exit(1);
  }
  else
  {
    
  }

  ;
  if ((stock_product_get_available(sp) + qtd) < 0)
  {
    return -1;
  }
  else
  {
    
  }

  sp->qtd += qtd;
  return 0;
}

int stock_product_reserve_quantity(Stock_Product *sp, int qtd)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_reserve_quantity");
    exit(1);
  }
  else
  {
    
  }

  ;
  if (stock_product_get_available(sp) < qtd)
  {
    return -1;
  }
  else
  {
    
  }

  sp->qtd_reserved += qtd;
  return 0;
}

char *stock_to_string(const Stock *s, char *buf, int buf_size)
{
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_to_string");
    exit(1);
  }
  else
  {
    
  }

  ;
  snprintf(buf, buf_size, "Stock: C=%d", stock_count(s));
  return buf;
}

void stock_product_print(const Stock_Product *sp)
{
  if (sp == 0)
  {
    printf("%s: null pointer\n", "stock_product_print");
    exit(1);
  }
  else
  {
    
  }

  ;
  printf("Stock_Product: ID=%d Q=%d R=%d A=%d\n", product_get_id(stock_product_get_product(sp)), stock_product_get_quantity(sp), stock_product_get_reserved(sp), stock_product_get_available(sp));
}

void stock_list_products(const Stock *s)
{
  Stock_Product *sp;
  const Product *p;
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_list_products");
    exit(1);
  }
  else
  {
    
  }

  ;
  sp = s->products;
  puts("Produtos");
  while (sp != 0)
  {
    p = sp->product;
    printf("* %s %d %d\n", p->descricao, p->preco, stock_product_get_available(sp));
    sp = sp->next;
  }

}

void stock_list_products_by_price(const Stock *s)
{
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_list_products_by_price");
    exit(1);
  }
  else
  {
    
  }

  ;
  stock_list_products(s);
}

void stock_print(const Stock *s)
{
  char buf[100];
  if (s == 0)
  {
    printf("%s: null pointer\n", "stock_print");
    exit(1);
  }
  else
  {
    
  }

  ;
  printf("%s\n", stock_to_string(s, buf, 100));
}
