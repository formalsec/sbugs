/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Produto
{
  int idp;
  int preco;
  int peso;
  int qtd;
  char descricao[64];
} Produto;
typedef struct Stock_Encomenda
{
  int prod;
  int qtd;
} Stock_Encomenda;
typedef struct Encomenda
{
  int ide;
  int peso;
  int n_prods;
  Stock_Encomenda prods_encomenda[200];
} Encomenda;
void cmd_a();
void cmd_q();
void cmd_N();
void cmd_A();
void cmd_r();
void cmd_R();
void cmd_C();
void cmd_p();
void cmd_E();
void cmd_m();
void cmd_l();
void cmd_L();
void quicksort(Produto a[], int l, int r);
void quicksort_str(Stock_Encomenda e[], int l, int r);
int id = 0;
int id_e = 0;
Produto lista_p[10000];
Encomenda lista_e[500];
int main()
{
  int ativo = 1;
  char c;
  while (ativo)
  {
    switch (c = getchar())
    {
      case 'a':
        printf("Novo produto %d.\n", id);
        cmd_a();
        break;

      case 'q':
        cmd_q();
        break;

      case 'N':
        printf("Nova encomenda %d.\n", id_e);
        cmd_N();
        break;

      case 'A':
        cmd_A();
        break;

      case 'r':
        cmd_r();
        break;

      case 'R':
        cmd_R();
        break;

      case 'C':
        cmd_C();
        break;

      case 'p':
        cmd_p();
        break;

      case 'E':
        cmd_E();
        break;

      case 'm':
        cmd_m();
        break;

      case 'l':
        cmd_l();
        break;

      case 'L':
        cmd_L();
        break;

      case 'x':
        ativo = 0;
        break;

    }

  }

  return 0;
}

void cmd_a()
{
  Produto p;
  for (int p_index = 0; p_index < 10; p_index++)
  {
    p.descricao[p_index] = new_sym_var(sizeof(char) * 8);
  }

  p.descricao[10 - 1] = '\0';
  p.preco = new_sym_var(sizeof(int) * 8);
  p.peso = new_sym_var(sizeof(int) * 8);
  p.qtd = new_sym_var(sizeof(int) * 8);
  p.idp = id;
  lista_p[id++] = p;
}

void cmd_q()
{
  int idp_produto = 0;
  int stock_add = 0;
  idp_produto = new_sym_var(sizeof(int) * 8);
  stock_add = new_sym_var(sizeof(int) * 8);
  if (idp_produto >= id)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_produto);
      return;
    }
  }
  else
  {
    
  }

  lista_p[idp_produto].qtd += stock_add;
}

void cmd_N()
{
  Encomenda e;
  e.ide = id_e;
  e.peso = 0;
  e.n_prods = 0;
  lista_e[id_e++] = e;
}

void cmd_A()
{
  int e = 0;
  int ide_produto = 0;
  int qtd_produto = 0;
  int idp_produto = 0;
  ide_produto = new_sym_var(sizeof(int) * 8);
  idp_produto = new_sym_var(sizeof(int) * 8);
  qtd_produto = new_sym_var(sizeof(int) * 8);
  if (ide_produto >= id_e)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_produto, ide_produto);
      return;
    }
  }
  else
  {
    
  }

  if (idp_produto >= id)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_produto, ide_produto);
      return;
    }
  }
  else
  {
    
  }

  if (qtd_produto > lista_p[idp_produto].qtd)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_produto, ide_produto);
      return;
    }
  }
  else
  {
    
  }

  if ((lista_e[ide_produto].peso + (lista_p[idp_produto].peso * qtd_produto)) > 200)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_produto, ide_produto);
      return;
    }
  }
  else
  {
    
  }

  for (e = 0; e < lista_e[ide_produto].n_prods; e++)
  {
    if (lista_e[ide_produto].prods_encomenda[e].prod == idp_produto)
    {
      {
        lista_p[idp_produto].qtd -= qtd_produto;
        lista_e[ide_produto].prods_encomenda[e].qtd += qtd_produto;
        lista_e[ide_produto].peso += lista_p[idp_produto].peso * qtd_produto;
        return;
      }
    }
    else
    {
      
    }

  }

  lista_p[idp_produto].qtd -= qtd_produto;
  lista_e[ide_produto].prods_encomenda[lista_e[ide_produto].n_prods].prod = idp_produto;
  lista_e[ide_produto].prods_encomenda[lista_e[ide_produto].n_prods++].qtd = qtd_produto;
  lista_e[ide_produto].peso += lista_p[idp_produto].peso * qtd_produto;
}

void cmd_r()
{
  int idp_produto = 0;
  int stock_remove = 0;
  idp_produto = new_sym_var(sizeof(int) * 8);
  stock_remove = new_sym_var(sizeof(int) * 8);
  if (idp_produto >= id)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_produto);
      return;
    }
  }
  else
  {
    {
      if (lista_p[idp_produto].qtd >= stock_remove)
      {
        {
          lista_p[idp_produto].qtd -= stock_remove;
          return;
        }
      }
      else
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock_remove, lista_p[idp_produto].idp);
      }

    }
  }

}

void cmd_R()
{
  int e;
  int i;
  int ide_produto = 0;
  int idp_produto = 0;
  ide_produto = new_sym_var(sizeof(int) * 8);
  idp_produto = new_sym_var(sizeof(int) * 8);
  if (ide_produto >= id_e)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_produto, ide_produto);
      return;
    }
  }
  else
  {
    
  }

  if (idp_produto >= id)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_produto, ide_produto);
      return;
    }
  }
  else
  {
    
  }

  for (e = 0; e < lista_e[ide_produto].n_prods; e++)
  {
    if (lista_e[ide_produto].prods_encomenda[e].prod == idp_produto)
    {
      {
        lista_e[ide_produto].peso -= lista_e[ide_produto].prods_encomenda[e].qtd * lista_p[lista_e[ide_produto].prods_encomenda[e].prod].peso;
        lista_p[idp_produto].qtd += lista_e[ide_produto].prods_encomenda[e].qtd;
        for (i = e; i < (lista_e[ide_produto].n_prods - 1); i++)
        {
          lista_e[ide_produto].prods_encomenda[i] = lista_e[ide_produto].prods_encomenda[i + 1];
        }

        lista_e[ide_produto].n_prods--;
        break;
      }
    }
    else
    {
      
    }

  }

}

void cmd_C()
{
  int i;
  int preco_total = 0;
  int ide_produto = 0;
  ide_produto = new_sym_var(sizeof(int) * 8);
  if (ide_produto >= id_e)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_produto);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < lista_e[ide_produto].n_prods; i++)
  {
    preco_total += lista_e[ide_produto].prods_encomenda[i].qtd * lista_p[lista_e[ide_produto].prods_encomenda[i].prod].preco;
  }

  printf("Custo da encomenda %d %d.\n", ide_produto, preco_total);
}

void cmd_p()
{
  int idp_produto = 0;
  int preco_novo = 0;
  idp_produto = new_sym_var(sizeof(int) * 8);
  preco_novo = new_sym_var(sizeof(int) * 8);
  if (idp_produto >= id)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_produto);
      return;
    }
  }
  else
  {
    
  }

  lista_p[idp_produto].preco = preco_novo;
}

void cmd_E()
{
  int e = 0;
  int ide_produto = 0;
  int idp_produto = 0;
  ide_produto = new_sym_var(sizeof(int) * 8);
  idp_produto = new_sym_var(sizeof(int) * 8);
  if (ide_produto >= id_e)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_produto);
      return;
    }
  }
  else
  {
    
  }

  if (idp_produto >= id)
  {
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp_produto);
      return;
    }
  }
  else
  {
    
  }

  for (e = 0; e < lista_e[ide_produto].n_prods; e++)
  {
    if (lista_e[ide_produto].prods_encomenda[e].prod == idp_produto)
    {
      {
        printf("%s %d.\n", lista_p[lista_e[ide_produto].prods_encomenda[e].prod].descricao, lista_e[ide_produto].prods_encomenda[e].qtd);
        return;
      }
    }
    else
    {
      
    }

  }

  printf("%s 0.\n", lista_p[idp_produto].descricao);
  return;
}

void cmd_m()
{
  int e;
  int i;
  int idp_produto = 0;
  int qtd_produto = -1;
  int indice_encomenda = 0;
  int indice_produto = 0;
  idp_produto = new_sym_var(sizeof(int) * 8);
  if (idp_produto >= id)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_produto);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < id_e; i++)
  {
    for (e = 0; e < lista_e[i].n_prods; e++)
    {
      if (lista_e[i].prods_encomenda[e].prod == idp_produto)
      {
        {
          if (lista_e[i].prods_encomenda[e].qtd > qtd_produto)
          {
            {
              qtd_produto = lista_e[i].prods_encomenda[e].qtd;
              indice_encomenda = i;
              indice_produto = e;
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

  if (qtd_produto != (-1))
  {
    printf("Maximo produto %d %d %d.\n", idp_produto, lista_e[indice_encomenda].ide, lista_e[indice_encomenda].prods_encomenda[indice_produto].qtd);
  }
  else
  {
    
  }

}

void cmd_l()
{
  int i;
  Produto lista_p_sorted[10000];
  for (i = 0; i < id; i++)
  {
    lista_p_sorted[i] = lista_p[i];
  }

  quicksort(lista_p_sorted, 0, id - 1);
  printf("Produtos\n");
  for (i = 0; i < id; i++)
  {
    printf("* %s %d %d\n", lista_p_sorted[i].descricao, lista_p_sorted[i].preco, lista_p_sorted[i].qtd);
  }

}

void cmd_L()
{
  Stock_Encomenda e[200];
  int i;
  int ide_produto = 0;
  ide_produto = new_sym_var(sizeof(int) * 8);
  if (ide_produto >= id_e)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_produto);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < lista_e[ide_produto].n_prods; i++)
  {
    e[i] = lista_e[ide_produto].prods_encomenda[i];
  }

  quicksort_str(e, 0, lista_e[ide_produto].n_prods - 1);
  printf("Encomenda %d\n", ide_produto);
  for (i = 0; i < lista_e[ide_produto].n_prods; i++)
  {
    printf("* %s %d %d\n", lista_p[e[i].prod].descricao, lista_p[e[i].prod].preco, e[i].qtd);
  }

}

void exchange(Produto a[], int i, int j)
{
  Produto aux;
  aux = a[i];
  a[i] = a[j];
  a[j] = aux;
}

int partition(Produto a[], int l, int r)
{
  int i = l - 1;
  int j = r;
  Produto v = a[r];
  while (i < j)
  {
    while ((a[++i].preco < v.preco) || ((a[i].preco == v.preco) && (a[i].idp < v.idp)))
      ;

    while ((v.preco < a[--j].preco) || ((v.preco == a[j].preco) && (v.idp < a[j].idp)))
      if (j == l)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      exchange(a, i, j);
    }
    else
    {
      
    }

  }

  exchange(a, i, r);
  return i;
}

void quicksort(Produto a[], int l, int r)
{
  int i;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = partition(a, l, r);
  quicksort(a, l, i - 1);
  quicksort(a, i + 1, r);
}

void exchange_str(Stock_Encomenda e[], int i, int j)
{
  Stock_Encomenda aux;
  aux = e[i];
  e[i] = e[j];
  e[j] = aux;
}

int partition_str(Stock_Encomenda e[], int l, int r)
{
  int i = l - 1;
  int j = r;
  Stock_Encomenda v = e[r];
  while (i < j)
  {
    while (strcmp(lista_p[e[++i].prod].descricao, lista_p[v.prod].descricao) < 0)
      ;

    while (strcmp(lista_p[v.prod].descricao, lista_p[e[--j].prod].descricao) < 0)
    {
      if (j == l)
      {
        break;
      }
      else
      {
        
      }

    }

    if (i < j)
    {
      exchange_str(e, i, j);
    }
    else
    {
      
    }

  }

  exchange_str(e, i, r);
  return i;
}

void quicksort_str(Stock_Encomenda e[], int l, int r)
{
  int i;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  i = partition_str(e, l, r);
  quicksort_str(e, l, i - 1);
  quicksort_str(e, i + 1, r);
}
