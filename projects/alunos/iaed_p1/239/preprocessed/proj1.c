#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  int id;
  char desc[63];
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct 
{
  int numprods;
  produto produtos[200];
} encomenda;
produto prods[10000];
int num_p;
encomenda encomendas[500];
int num_e;
produto a[10000];
produto aux[10000];
void add_prod()
{
  for (int prods_index = 0; prods_index < 10; prods_index++)
  {
    prods[num_p].desc[prods_index] = new_sym_var(sizeof(char) * 8);
  }

  prods[num_p].desc[10 - 1] = '\0';
  prods[num_p].preco = new_sym_var(sizeof(int) * 8);
  prods[num_p].peso = new_sym_var(sizeof(int) * 8);
  prods[num_p].qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", prods[num_p].id = num_p);
  num_p++;
}

void add_stock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp < num_p)
  {
    prods[idp].qtd += qtd;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }

}

void add_enc()
{
  encomendas[num_e].numprods = 0;
  printf("Nova encomenda %d.\n", num_e++);
}

int peso(encomenda enc)
{
  int i;
  int val = 0;
  for (i = 0; i < enc.numprods; i++)
    val += enc.produtos[i].peso * enc.produtos[i].qtd;

  return val;
}

int ind(int idp, int ide)
{
  int i;
  for (i = 0; i < encomendas[ide].numprods; i++)
  {
    if (encomendas[ide].produtos[i].id == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int novo_prod_enc(int idp, int ide)
{
  int n = encomendas[ide].numprods;
  encomendas[ide].produtos[n] = prods[idp];
  encomendas[ide].produtos[n].qtd = 0;
  return encomendas[ide].numprods++;
}

void add_prod_enc()
{
  int ide;
  int idp;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide >= num_e)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= num_p)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if (prods[idp].qtd < qtd)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((peso(encomendas[ide]) + (prods[idp].peso * qtd)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          int i = ind(idp, ide);
          if (i == (-1))
          {
            i = novo_prod_enc(idp, ide);
          }
          else
          {
            
          }

          encomendas[ide].produtos[i].qtd += qtd;
          prods[idp].qtd -= qtd;
        }

      }

    }

  }

}

void rm_stock()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= num_p)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (prods[idp].qtd < qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      prods[idp].qtd -= qtd;
    }

  }

}

void rm_prod_enc()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= num_e)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= num_p)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      int i = ind(idp, ide);
      if (i != (-1))
      {
        prods[idp].qtd += encomendas[ide].produtos[i].qtd;
        encomendas[ide].produtos[i].qtd = 0;
      }
      else
      {
        
      }

    }

  }

}

void cost()
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= num_e)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    int i;
    int val = 0;
    for (i = 0; i < encomendas[ide].numprods; i++)
      val += encomendas[ide].produtos[i].qtd * encomendas[ide].produtos[i].preco;

    printf("Custo da encomenda %d %d.\n", ide, val);
  }

}

void update_preco(int idp)
{
  int i;
  int npreco = prods[idp].preco;
  for (i = 0; i < num_e; i++)
  {
    int j = ind(idp, i);
    if (j != (-1))
    {
      encomendas[i].produtos[j].preco = npreco;
    }
    else
    {
      
    }

  }

}

void alt_preco()
{
  int idp;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp >= num_p)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    prods[idp].preco = preco;
    update_preco(idp);
  }

}

void prod_info()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= num_e)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= num_p)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      int i = ind(idp, ide);
      if (i == (-1))
      {
        printf("%s %d.\n", prods[idp].desc, 0);
      }
      else
      {
        printf("%s %d.\n", encomendas[ide].produtos[i].desc, encomendas[ide].produtos[i].qtd);
      }

    }

  }

}

void max_prod()
{
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= num_p)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    int i;
    int ide = 0;
    int high = 0;
    for (i = 0; i < num_e; i++)
    {
      int j = ind(idp, i);
      if ((j >= 0) && (encomendas[i].produtos[j].qtd > high))
      {
        ide = i;
        high = encomendas[i].produtos[j].qtd;
      }
      else
      {
        
      }

    }

    if (high > 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, high);
    }
    else
    {
      
    }

  }

}

void merge_p(int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
  {
    if ((aux[j].preco < aux[i].preco) || (i > m))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void mergesort_p(int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort_p(l, m);
  mergesort_p(m + 1, r);
  merge_p(l, m, r);
}

void cpyprods(produto to[], produto from[], int lim)
{
  int i;
  for (i = 0; i <= lim; i++)
    to[i] = from[i];

}

void sort_price()
{
  int l = 0;
  int r = num_p - 1;
  cpyprods(a, prods, r);
  mergesort_p(l, r);
  printf("Produtos\n");
  for (l = 0; l < num_p; l++)
    printf("* %s %d %d\n", a[l].desc, a[l].preco, a[l].qtd);

}

void merge_n(int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
  {
    if ((strcmp(aux[j].desc, aux[i].desc) < 0) || (i > m))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void mergesort_n(int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort_n(l, m);
  mergesort_n(m + 1, r);
  merge_n(l, m, r);
}

void sort_name()
{
  int ide;
  int l;
  int r;
  ide = new_sym_var(sizeof(int) * 8);
  l = 0;
  r = encomendas[ide].numprods - 1;
  if (ide >= num_e)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    cpyprods(a, encomendas[ide].produtos, r);
    mergesort_n(l, r);
    printf("Encomenda %d\n", ide);
    for (l = 0; l <= r; l++)
    {
      if (a[l].qtd > 0)
      {
        printf("* %s %d %d\n", a[l].desc, a[l].preco, a[l].qtd);
      }
      else
      {
        
      }

    }

  }

}

void comand(char c)
{
  switch (c)
  {
    case 'a':
      add_prod();
      break;

    case 'q':
      add_stock();
      break;

    case 'N':
      add_enc();
      break;

    case 'A':
      add_prod_enc();
      break;

    case 'r':
      rm_stock();
      break;

    case 'R':
      rm_prod_enc();
      break;

    case 'C':
      cost();
      break;

    case 'p':
      alt_preco();
      break;

    case 'E':
      prod_info();
      break;

    case 'm':
      max_prod();
      break;

    case 'l':
      sort_price();
      break;

    case 'L':
      sort_name();
      break;

  }

}

int main()
{
  char c;
  while ((c = getchar()) != 'x')
    comand(c);

  return 0;
}
