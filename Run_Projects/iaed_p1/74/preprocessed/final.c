/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  char desc[63];
  int idp;
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct 
{
  int ide;
  int peso;
  int n_produtos_encomenda;
  produto produto[200];
} encomenda;
produto armazem[10000];
encomenda encomendas[500];
int n_produtos_armazem = 0;
int n_encomendas = 0;
int idp;
int ide;
int qtd;
int i;
int preco;
int max;
int j;
int k;
produto aux[10000];
produto teste[10000];
void novo_produto()
{
  produto novo;
  int i = 0;
  char c;
  c = getchar();
  c = getchar();
  while (c != ':')
  {
    novo.desc[i] = c;
    c = getchar();
    i++;
  }

  novo.desc[i] = '\0';
  novo.preco = new_sym_var(sizeof(int) * 8);
  novo.peso = new_sym_var(sizeof(int) * 8);
  novo.qtd = new_sym_var(sizeof(int) * 8);
  novo.idp = n_produtos_armazem;
  armazem[n_produtos_armazem] = novo;
  n_produtos_armazem++;
  printf("Novo produto %d.\n", novo.idp);
}

void adiciona_stock()
{
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= n_produtos_armazem)
  {
    {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      armazem[idp].qtd += qtd;
    }
  }

}

void nova_encomenda()
{
  encomenda nova;
  nova.n_produtos_encomenda = 0;
  nova.peso = 0;
  nova.ide = n_encomendas;
  encomendas[n_encomendas] = nova;
  printf("Nova encomenda %d.\n", nova.ide);
  n_encomendas++;
}

void troca_armazem_encomenda(int ide, int i, int qtd, int idp)
{
  encomendas[ide].produto[i].qtd += qtd;
  armazem[idp].qtd -= qtd;
  encomendas[ide].peso += armazem[idp].peso * qtd;
}

void adiciona_prod_encomenda()
{
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (ide >= n_encomendas)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (idp >= n_produtos_armazem)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      if ((armazem[idp].qtd - qtd) < 0)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
      }
      else
      {
        if ((encomendas[ide].peso + (armazem[idp].peso * qtd)) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
          }
        }
        else
        {
          {
            for (i = 0; i < encomendas[ide].n_produtos_encomenda; i++)
            {
              if (encomendas[ide].produto[i].idp == idp)
              {
                {
                  troca_armazem_encomenda(ide, i, qtd, idp);
                  return;
                }
              }
              else
              {
                
              }

            }

            encomendas[ide].produto[encomendas[ide].n_produtos_encomenda].idp = idp;
            troca_armazem_encomenda(ide, encomendas[ide].n_produtos_encomenda, qtd, idp);
            encomendas[ide].n_produtos_encomenda++;
          }
        }

      }

    }

  }

}

void remove_stock()
{
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= n_produtos_armazem)
  {
    {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    if ((armazem[idp].qtd - qtd) < 0)
    {
      {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
      }
    }
    else
    {
      {
        armazem[idp].qtd -= qtd;
      }
    }

  }

}

void remover()
{
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= n_encomendas)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
  }
  else
  {
    if (idp >= n_produtos_armazem)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
      }
    }
    else
    {
      {
        for (i = 0; i < encomendas[ide].n_produtos_encomenda; i++)
        {
          if (encomendas[ide].produto[i].idp == idp)
          {
            {
              armazem[idp].qtd += encomendas[ide].produto[i].qtd;
              encomendas[ide].peso -= armazem[idp].peso * encomendas[ide].produto[i].qtd;
              for (j = i; j < encomendas[ide].n_produtos_encomenda; j++)
              {
                encomendas[ide].produto[j] = encomendas[ide].produto[j + 1];
              }

              encomendas[ide].n_produtos_encomenda--;
              return;
            }
          }
          else
          {
            
          }

        }

      }
    }

  }

}

void calcula_custo()
{
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= n_encomendas)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      preco = 0;
      for (i = 0; i < encomendas[ide].n_produtos_encomenda; i++)
      {
        idp = encomendas[ide].produto[i].idp;
        preco += encomendas[ide].produto[i].qtd * armazem[idp].preco;
      }

      printf("Custo da encomenda %d %d.\n", ide, preco);
    }
  }

}

void altera_preco()
{
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp >= n_produtos_armazem)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      armazem[idp].preco = preco;
    }
  }

}

void lista_desc_qtd()
{
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= n_encomendas)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    if (idp >= n_produtos_armazem)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
      }
    }
    else
    {
      {
        for (i = 0; i < encomendas[ide].n_produtos_encomenda; i++)
        {
          if (encomendas[ide].produto[i].idp == idp)
          {
            {
              printf("%s %d.\n", armazem[idp].desc, encomendas[ide].produto[i].qtd);
              return;
            }
          }
          else
          {
            
          }

        }

        printf("%s 0.\n", armazem[idp].desc);
      }
    }

  }

}

void lista_ide_max()
{
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= n_produtos_armazem)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
  }
  else
  {
    {
      max = 0;
      for (i = 0; i < n_encomendas; i++)
      {
        for (j = 0; j <= encomendas[i].n_produtos_encomenda; j++)
        {
          if ((encomendas[i].produto[j].idp == idp) && (encomendas[i].produto[j].qtd > max))
          {
            {
              max = encomendas[i].produto[j].qtd;
              ide = encomendas[i].ide;
            }
          }
          else
          {
            
          }

        }

      }

      if (max != 0)
      {
        {
          printf("Maximo produto %d %d %d.\n", idp, ide, max);
        }
      }
      else
      {
        
      }

    }
  }

}

void merge_preco(produto a[], int left, int m, int right)
{
  for (i = m + 1; i > left; i--)
  {
    aux[i - 1] = a[i - 1];
  }

  for (j = m; j < right; j++)
  {
    aux[(right + m) - j] = a[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if (aux[j].preco == aux[i].preco)
    {
      {
        if (aux[j].idp < aux[i].idp)
        {
          {
            a[k] = aux[j--];
          }
        }
        else
        {
          {
            a[k] = aux[i++];
          }
        }

      }
    }
    else
    {
      if (aux[j].preco < aux[i].preco)
      {
        {
          a[k] = aux[j--];
        }
      }
      else
      {
        {
          a[k] = aux[i++];
        }
      }

    }

  }

}

void mergesort_preco(produto a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  mergesort_preco(a, left, m);
  mergesort_preco(a, m + 1, right);
  merge_preco(a, left, m, right);
}

void cria_copia(produto copia[], produto copiado[], int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    copia[i] = copiado[i];
  }

}

void lista_ordem_preco()
{
  cria_copia(teste, armazem, n_produtos_armazem);
  mergesort_preco(teste, 0, n_produtos_armazem - 1);
  printf("Produtos\n");
  for (i = 0; i < n_produtos_armazem; i++)
  {
    printf("* %s %d %d\n", armazem[teste[i].idp].desc, teste[i].preco, teste[i].qtd);
  }

}

void merge_alfa(produto a[], int left, int m, int right)
{
  for (i = m + 1; i > left; i--)
  {
    aux[i - 1] = a[i - 1];
  }

  for (j = m; j < right; j++)
  {
    aux[(right + m) - j] = a[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if (strcmp(armazem[aux[j].idp].desc, armazem[aux[i].idp].desc) < 0)
    {
      {
        a[k] = aux[j--];
      }
    }
    else
    {
      {
        a[k] = aux[i++];
      }
    }

  }

}

void mergesort_alfa(produto a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  mergesort_alfa(a, left, m);
  mergesort_alfa(a, m + 1, right);
  merge_alfa(a, left, m, right);
}

void lista_ordem_alfa()
{
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= n_encomendas)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  else
  {
    {
      cria_copia(teste, encomendas[ide].produto, encomendas[ide].n_produtos_encomenda);
      mergesort_alfa(teste, 0, encomendas[ide].n_produtos_encomenda - 1);
      printf("Encomenda %d\n", ide);
      for (i = 0; i < encomendas[ide].n_produtos_encomenda; i++)
      {
        printf("* %s %d %d\n", armazem[teste[i].idp].desc, armazem[teste[i].idp].preco, teste[i].qtd);
      }

    }
  }

}

int main()
{
  char c;
  while ((c = getchar()) != EOF)
  {
    switch (c)
    {
      case 'a':
        novo_produto();
        break;

      case 'q':
        adiciona_stock();
        break;

      case 'N':
        nova_encomenda();
        break;

      case 'A':
        adiciona_prod_encomenda();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        remover();
        break;

      case 'C':
        calcula_custo();
        break;

      case 'p':
        altera_preco();
        break;

      case 'E':
        lista_desc_qtd();
        break;

      case 'm':
        lista_ide_max();
        break;

      case 'l':
        lista_ordem_preco();
        break;

      case 'L':
        lista_ordem_alfa();
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}

