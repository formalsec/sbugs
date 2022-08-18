/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  char d[63];
  int price;
  int w;
  int s;
} produto;
typedef struct encomenda
{
  int peso;
  int num_p;
  int ordenado;
  int p_ordenado[10000];
  int produtos[10000];
  int jaesteve[10000];
} encomenda;
int idp = 0;
int ide = 0;
produto produtos[10000];
encomenda encomendas[500];
int pricesorted[10000] = {-1};
int aux[10000];
int prod_alterado;
int sorted;
int preco_alterado;
void add_produto();
void add_stock();
void remove_stock();
void muda_preco();
void lista_produtos();
void adiciona_p_encomenda();
void remove_p_encomenda();
void calcula_preco();
void produto_encomenda();
void produto_mais_repetido();
void lista_produtos_encomenda();
void merge(int array[], int inicio, int meio, int fim, int (*compare)(int, int));
void mergesort(int a[], int left, int right, int (*compare)(int, int));
int compara_preco(int i1, int i2);
int compara_str(int i1, int i2);
int main()
{
  char c;
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
        add_produto();
        break;

      case 'q':
        add_stock();
        break;

      case 'N':
        printf("Nova encomenda %d.\n", ide);
        ide++;
        break;

      case 'A':
        adiciona_p_encomenda();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        remove_p_encomenda();
        break;

      case 'C':
        calcula_preco();
        break;

      case 'p':
        muda_preco();
        break;

      case 'E':
        produto_encomenda();
        break;

      case 'm':
        produto_mais_repetido();
        break;

      case 'l':
        lista_produtos();
        break;

      case 'L':
        lista_produtos_encomenda();
        break;

      default:
        break;

    }

  }

  return 0;
}

void add_produto()
{
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[idp].d[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[idp].d[10 - 1] = '\0';
  produtos[idp].price = new_sym_var(sizeof(int) * 8);
  produtos[idp].w = new_sym_var(sizeof(int) * 8);
  produtos[idp].s = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
  pricesorted[idp] = idp;
  prod_alterado = 1;
  idp++;
}

void add_stock()
{
  int ip;
  int qtd;
  ip = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp <= ip)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", ip);
    }
  }
  else
  {
    {
      produtos[ip].s += qtd;
    }
  }

}

void remove_stock()
{
  int ip;
  int qt;
  ip = new_sym_var(sizeof(int) * 8);
  qt = new_sym_var(sizeof(int) * 8);
  if (idp <= ip)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", ip);
    }
  }
  else
  {
    if (produtos[ip].s < qt)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qt, ip);
      }
    }
    else
    {
      {
        produtos[ip].s -= qt;
      }
    }

  }

}

void muda_preco()
{
  int ip;
  int preco;
  ip = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp <= ip)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", ip);
    }
  }
  else
  {
    {
      prod_alterado = 1;
      preco_alterado = 1;
      produtos[ip].price = preco;
    }
  }

}

void lista_produtos()
{
  int i;
  if (prod_alterado)
  {
    {
      if (!sorted)
      {
        {
          mergesort(pricesorted, 0, idp - 1, compara_preco);
          sorted = idp;
        }
      }
      else
      {
        if (preco_alterado)
        {
          {
            mergesort(pricesorted, 0, idp - 1, compara_preco);
            sorted = idp;
          }
        }
        else
        {
          {
            mergesort(pricesorted, sorted, idp - 1, compara_preco);
            merge(pricesorted, 0, sorted - 1, idp - 1, compara_preco);
            sorted = idp;
          }
        }

      }

      prod_alterado = 0;
      preco_alterado = 0;
    }
  }
  else
  {
    
  }

  printf("Produtos\n");
  for (i = 0; i != idp; i++)
  {
    printf("* %s %d %d\n", produtos[pricesorted[i]].d, produtos[pricesorted[i]].price, produtos[pricesorted[i]].s);
  }

}

void adiciona_p_encomenda()
{
  int ie;
  int ip;
  int qtd;
  ie = new_sym_var(sizeof(int) * 8);
  ip = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide <= ie)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", ip, ie);
    }
  }
  else
  {
    if (idp <= ip)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", ip, ie);
      }
    }
    else
    {
      if (produtos[ip].s < qtd)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", ip, ie);
        }
      }
      else
      {
        if ((encomendas[ie].peso + (produtos[ip].w * qtd)) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", ip, ie);
          }
        }
        else
        {
          {
            if (!encomendas[ie].jaesteve[ip])
            {
              {
                encomendas[ie].p_ordenado[encomendas[ie].num_p] = ip;
                encomendas[ie].ordenado = 0;
                encomendas[ie].num_p += 1;
                encomendas[ie].jaesteve[ip] = 1;
              }
            }
            else
            {
              
            }

            encomendas[ie].produtos[ip] += qtd;
            encomendas[ie].peso += produtos[ip].w * qtd;
            produtos[ip].s -= qtd;
          }
        }

      }

    }

  }

}

void remove_p_encomenda()
{
  int ie;
  int ip;
  ie = new_sym_var(sizeof(int) * 8);
  ip = new_sym_var(sizeof(int) * 8);
  if (ide <= ie)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", ip, ie);
    }
  }
  else
  {
    if (idp <= ip)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", ip, ie);
      }
    }
    else
    {
      {
        encomendas[ie].peso -= encomendas[ie].produtos[ip] * produtos[ip].w;
        produtos[ip].s += encomendas[ie].produtos[ip];
        encomendas[ie].produtos[ip] = 0;
      }
    }

  }

}

void calcula_preco()
{
  int ie;
  int i;
  int preco = 0;
  ie = new_sym_var(sizeof(int) * 8);
  if (ide <= ie)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ie);
    }
  }
  else
  {
    {
      for (i = 0; i != encomendas[ie].num_p; i++)
      {
        preco += encomendas[ie].produtos[encomendas[ie].p_ordenado[i]] * produtos[encomendas[ie].p_ordenado[i]].price;
      }

      printf("Custo da encomenda %d %d.\n", ie, preco);
    }
  }

}

void produto_encomenda()
{
  int ie;
  int ip;
  ie = new_sym_var(sizeof(int) * 8);
  ip = new_sym_var(sizeof(int) * 8);
  if (ide <= ie)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ie);
    }
  }
  else
  {
    if (idp <= ip)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", ip);
      }
    }
    else
    {
      {
        printf("%s %d.\n", produtos[ip].d, encomendas[ie].produtos[ip]);
      }
    }

  }

}

void produto_mais_repetido()
{
  int ip;
  int ie;
  int iemaior;
  int mais = 0;
  ip = new_sym_var(sizeof(int) * 8);
  if (idp <= ip)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", ip);
    }
  }
  else
  {
    {
      for (ie = 0; ie != ide; ie++)
      {
        if (encomendas[ie].produtos[ip] > mais)
        {
          {
            mais = encomendas[ie].produtos[ip];
            iemaior = ie;
          }
        }
        else
        {
          
        }

      }

      if (mais > 0)
      {
        {
          printf("Maximo produto %d %d %d.\n", ip, iemaior, mais);
        }
      }
      else
      {
        
      }

    }
  }

}

void lista_produtos_encomenda()
{
  int ie;
  int i;
  ie = new_sym_var(sizeof(int) * 8);
  if (ide <= ie)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ie);
    }
  }
  else
  {
    {
      mergesort(encomendas[ie].p_ordenado, 0, encomendas[ie].num_p - 1, compara_str);
      encomendas[ie].ordenado = 1;
      printf("Encomenda %d\n", ie);
      for (i = 0; i != encomendas[ie].num_p; i++)
      {
        if (encomendas[ie].produtos[encomendas[ie].p_ordenado[i]] != 0)
        {
          {
            printf("* %s %d %d\n", produtos[encomendas[ie].p_ordenado[i]].d, produtos[encomendas[ie].p_ordenado[i]].price, encomendas[ie].produtos[encomendas[ie].p_ordenado[i]]);
          }
        }
        else
        {
          
        }

      }

    }
  }

}

void merge(int array[], int inicio, int meio, int fim, int (*compare)(int, int))
{
  int i;
  int j;
  int k;
  for (i = meio + 1; i > inicio; i--)
  {
    aux[i - 1] = array[i - 1];
  }

  for (j = meio; j < fim; j++)
  {
    aux[(fim + meio) - j] = array[j + 1];
  }

  for (k = inicio; k <= fim; k++)
  {
    if (compare(aux[j], aux[i]))
    {
      {
        array[k] = aux[j--];
      }
    }
    else
    {
      {
        array[k] = aux[i++];
      }
    }

  }

}

void mergesort(int a[], int left, int right, int (*compare)(int, int))
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, left, m, compare);
  mergesort(a, m + 1, right, compare);
  merge(a, left, m, right, compare);
}

int compara_preco(int i1, int i2)
{
  return (produtos[i1].price < produtos[i2].price) || ((produtos[i1].price == produtos[i2].price) && (i1 < i2));
}

int compara_str(int i1, int i2)
{
  return strcmp(produtos[i1].d, produtos[i2].d) < 0;
}

