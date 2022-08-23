/*File generated by PreProcessor.py*/


#include "auxiliar.h"
#include <stdio.h>


Produto produto[10000];
Encomenda encomenda[500];
int stock[10000];
int copia_id[10000];
int copia_stock[10000];
int size_p = 0;
int size_e = 0;
void novo_produto();
void adiciona_qtd();
void nova_encomenda();
void adiciona_encomenda();
void remove_qtd();
void remove_prod_encomenda();
void calcula_custo();
void altera_preco();
void atualiza_preco();
void lista_por_preco();
void lista_desc_qtd();
void lista_encomenda_nome();
void lista_maximo();
void novo_produto()
{
  produto[size_p].id = size_p;
  getchar();
  get_string(produto[size_p].desc);
  produto[size_p].preco = new_sym_var(sizeof(int) * 8);
  produto[size_p].peso = new_sym_var(sizeof(int) * 8);
  produto[size_p].qtd = new_sym_var(sizeof(int) * 8);
  stock[size_p] = produto[size_p].qtd;
  printf("Novo produto %d.\n", size_p);
  size_p++;
}

void adiciona_qtd()
{
  int tmp;
  int id;
  id = new_sym_var(sizeof(int) * 8);
  tmp = new_sym_var(sizeof(int) * 8);
  if (id >= size_p)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
      return;
    }
  }
  else
  {
    
  }

  produto[id].qtd += tmp;
  stock[id] += tmp;
}

void nova_encomenda()
{
  printf("Nova encomenda %d.\n", size_e);
  size_e++;
}

void adiciona_encomenda()
{
  int id_enc;
  int id_prod;
  int qtd;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id_enc >= size_e)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    if (id_prod >= size_p)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_prod, id_enc);
        return;
      }
    }
    else
    {
      
    }

  }

  if (qtd > stock[id_prod])
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    if ((encomenda[id_enc].peso + (produto[id_prod].peso * qtd)) > 200)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_prod, id_enc);
        return;
      }
    }
    else
    {
      
    }

  }

  stock[id_prod] -= qtd;
  if (encomenda[id_enc].pinfo[id_prod].set)
  {
    {
      encomenda[id_enc].pinfo[id_prod].qtd += qtd;
      encomenda[id_enc].peso += qtd * produto[id_prod].peso;
    }
  }
  else
  {
    {
      encomenda[id_enc].pinfo[id_prod].set = 1;
      encomenda[id_enc].pinfo[id_prod].qtd = qtd;
      encomenda[id_enc].peso += qtd * produto[id_prod].peso;
      encomenda[id_enc].size++;
    }
  }

}

void remove_qtd()
{
  int id_prod;
  int qtd;
  id_prod = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (id_prod >= size_p)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_prod);
      return;
    }
  }
  else
  {
    
  }

  if (qtd > stock[id_prod])
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id_prod);
      return;
    }
  }
  else
  {
    
  }

  produto[id_prod].qtd -= qtd;
  stock[id_prod] -= qtd;
}

void remove_prod_encomenda()
{
  int id_enc;
  int id_prod;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  if (id_enc >= size_e)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  if (id_prod >= size_p)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_prod, id_enc);
      return;
    }
  }
  else
  {
    
  }

  if (encomenda[id_enc].pinfo[id_prod].set)
  {
    {
      encomenda[id_enc].peso -= encomenda[id_enc].pinfo[id_prod].qtd * produto[id_prod].peso;
      stock[id_prod] += encomenda[id_enc].pinfo[id_prod].qtd;
      encomenda[id_enc].pinfo[id_prod].qtd = 0;
      encomenda[id_enc].pinfo[id_prod].set = 0;
      encomenda[id_enc].size--;
    }
  }
  else
  {
    
  }

}

void calcula_custo()
{
  int id_enc;
  int preco = 0;
  int i;
  id_enc = new_sym_var(sizeof(int) * 8);
  if (id_enc >= size_e)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_enc);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < size_p; i++)
    if (encomenda[id_enc].pinfo[i].set)
  {
    preco += produto[i].preco * encomenda[id_enc].pinfo[i].qtd;
  }
  else
  {
    
  }


  printf("Custo da encomenda %d %d.\n", id_enc, preco);
}

void altera_preco()
{
  int id_prod;
  int preco;
  id_prod = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (id_prod >= size_p)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_prod);
      return;
    }
  }
  else
  {
    
  }

  produto[id_prod].preco = preco;
}

void lista_por_preco()
{
  puts("Produtos");
  ordena_counting(produto, size_p, copia_id, ret_preco);
  imprime_ordenado(copia_id, size_p, produto, stock);
}

void lista_desc_qtd()
{
  int id_enc;
  int id_prod;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  if (id_enc >= size_e)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_enc);
      return;
    }
  }
  else
  {
    if (id_prod >= size_p)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", id_prod);
        return;
      }
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", produto[id_prod].desc, encomenda[id_enc].pinfo[id_prod].qtd);
}

void lista_encomenda_nome()
{
  int id_enc;
  int i;
  int j;
  id_enc = new_sym_var(sizeof(int) * 8);
  if (id_enc >= size_e)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_enc);
      return;
    }
  }
  else
  {
    
  }

  printf("Encomenda %d\n", id_enc);
  for (i = 0, j = 0; i < encomenda[id_enc].size; j++)
  {
    if (encomenda[id_enc].pinfo[j].set)
    {
      {
        copia_id[i++] = j;
        copia_stock[j] = encomenda[id_enc].pinfo[j].qtd;
      }
    }
    else
    {
      
    }

  }

  ordena_merge(copia_id, 0, encomenda[id_enc].size - 1, produto, cmp_str);
  imprime_ordenado(copia_id, encomenda[id_enc].size, produto, copia_stock);
}

void lista_maximo()
{
  int id_prod;
  int i;
  int max = 0;
  int ide = 0;
  id_prod = new_sym_var(sizeof(int) * 8);
  if (id_prod >= size_p)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_prod);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < size_e; i++)
  {
    if ((encomenda[i].pinfo[id_prod].qtd > max) && encomenda[i].pinfo[id_prod].set)
    {
      {
        max = encomenda[i].pinfo[id_prod].qtd;
        ide = i;
      }
    }
    else
    {
      
    }

  }

  if (max != 0)
  {
    printf("Maximo produto %d %d %d.\n", id_prod, ide, max);
  }
  else
  {
    
  }

}

