#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct prod
{
  int idp;
  char desc[63];
  int preco;
  int peso;
  int qnt;
} Produto;
typedef struct enc
{
  int ide;
  Produto produtos[200];
  int peso_total_enc;
  int contador_prod_enc;
} Encomenda;
int idp = 0;
Produto todos_produtos[10000];
int ide = 0;
Encomenda todas_encomendas[500];
Produto aux_preco[10000];
Produto aux_desc[500];
int contador_prod = 0;
int contador_enc = 0;
void novo_prod();
void adiciona_stock();
void nova_enc();
void adic_prod_enc();
void remove_stock();
void rem_prod_enc();
void calcula_custo_enc();
void altera_preco_prod();
void desc_qnt_prod_enc();
void enc_mais_prod();
void lista_produtos();
void lista_prod_encomenda();
int main()
{
  char comando;
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      default:
        break;

      case 'a':
        novo_prod();
        contador_prod++;
        break;

      case 'q':
        adiciona_stock();
        break;

      case 'N':
        nova_enc();
        contador_enc++;
        break;

      case 'A':
        adic_prod_enc();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        rem_prod_enc();
        break;

      case 'C':
        calcula_custo_enc();
        break;

      case 'p':
        altera_preco_prod();
        break;

      case 'E':
        desc_qnt_prod_enc();
        break;

      case 'm':
        enc_mais_prod();
        break;

      case 'l':
        lista_produtos();
        break;

      case 'L':
        lista_prod_encomenda();
        break;

    }

  }

  return 0;
}

int compara_preco(Produto i, Produto j)
{
  if (i.preco != j.preco)
  {
    return i.preco < j.preco;
  }
  else
  {
    return i.idp < j.idp;
  }

}

void merge_preco(Produto a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux_preco[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux_preco[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
  {
    if (compara_preco(aux_preco[j], aux_preco[i]) || (i > m))
    {
      a[k] = aux_preco[j--];
    }
    else
    {
      a[k] = aux_preco[i++];
    }

  }

}

void mergeSort_preco(Produto arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort_preco(arr, l, m);
    mergeSort_preco(arr, m + 1, r);
    merge_preco(arr, l, m, r);
  }
  else
  {
    
  }

}

int compara_descricao(Produto a, Produto b)
{
  return strcmp(a.desc, b.desc) < 0;
}

void merge_desc(Produto a[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux_desc[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux_desc[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
  {
    if (compara_descricao(aux_desc[j], aux_desc[i]) || (i > m))
    {
      a[k] = aux_desc[j--];
    }
    else
    {
      a[k] = aux_desc[i++];
    }

  }

}

void mergeSort_desc(Produto arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort_desc(arr, l, m);
    mergeSort_desc(arr, m + 1, r);
    merge_desc(arr, l, m, r);
  }
  else
  {
    
  }

}

int prod_existe_enc(int idp, int ide)
{
  int i;
  for (i = 0; i < todas_encomendas[ide].contador_prod_enc; i++)
  {
    if (todas_encomendas[ide].produtos[i].idp == idp)
    {
      return i;
    }
    else
    {
      
    }

  }

  return i;
}

void novo_prod()
{
  Produto a;
  a.idp = idp;
  idp++;
  for (int a_index = 0; a_index < 10; a_index++)
  {
    a.desc[a_index] = new_sym_var(sizeof(char) * 8);
  }

  a.desc[10 - 1] = '\0';
  a.preco = new_sym_var(sizeof(int) * 8);
  a.peso = new_sym_var(sizeof(int) * 8);
  a.qnt = new_sym_var(sizeof(int) * 8);
  todos_produtos[a.idp] = a;
  printf("Novo produto %d.\n", a.idp);
}

void adiciona_stock()
{
  Produto p;
  int stock;
  p.idp = new_sym_var(sizeof(int) * 8);
  stock = new_sym_var(sizeof(int) * 8);
  if (p.idp >= contador_prod)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p.idp);
  }
  else
  {
    todos_produtos[p.idp].qnt += stock;
  }

}

void nova_enc()
{
  Encomenda e;
  e.ide = ide;
  ide++;
  e.peso_total_enc = 0;
  e.contador_prod_enc = 0;
  todas_encomendas[e.ide] = e;
  printf("Nova encomenda %d.\n", e.ide);
}

void adic_prod_enc()
{
  Encomenda e;
  Produto p;
  int qnt_prod;
  int i;
  e.ide = new_sym_var(sizeof(int) * 8);
  p.idp = new_sym_var(sizeof(int) * 8);
  qnt_prod = new_sym_var(sizeof(int) * 8);
  if (e.ide >= contador_enc)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, e.ide);
  }
  else
  {
    if (p.idp >= contador_prod)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p.idp, e.ide);
    }
    else
    {
      if (todos_produtos[p.idp].qnt < qnt_prod)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p.idp, e.ide);
      }
      else
      {
        if (((todos_produtos[p.idp].peso * qnt_prod) + todas_encomendas[e.ide].peso_total_enc) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p.idp, e.ide);
        }
        else
        {
          i = prod_existe_enc(p.idp, e.ide);
          if (i < todas_encomendas[e.ide].contador_prod_enc)
          {
            todas_encomendas[e.ide].peso_total_enc += todos_produtos[p.idp].peso * qnt_prod;
            todas_encomendas[e.ide].produtos[i].qnt += qnt_prod;
            todos_produtos[p.idp].qnt -= qnt_prod;
          }
          else
          {
            todas_encomendas[e.ide].peso_total_enc += todos_produtos[p.idp].peso * qnt_prod;
            todas_encomendas[e.ide].produtos[i] = todos_produtos[p.idp];
            todas_encomendas[e.ide].produtos[i].qnt = qnt_prod;
            todas_encomendas[e.ide].contador_prod_enc++;
            todos_produtos[p.idp].qnt -= qnt_prod;
          }

        }

      }

    }

  }

}

void remove_stock()
{
  Produto p;
  int stock_retirar;
  p.idp = new_sym_var(sizeof(int) * 8);
  stock_retirar = new_sym_var(sizeof(int) * 8);
  if (p.idp >= contador_prod)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p.idp);
  }
  else
  {
    if (todos_produtos[p.idp].qnt < stock_retirar)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stock_retirar, p.idp);
    }
    else
    {
      todos_produtos[p.idp].qnt -= stock_retirar;
    }

  }

}

void rem_prod_enc()
{
  Encomenda e;
  Produto p;
  int i;
  int j;
  e.ide = new_sym_var(sizeof(int) * 8);
  p.idp = new_sym_var(sizeof(int) * 8);
  if (e.ide >= contador_enc)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, e.ide);
  }
  else
  {
    if (p.idp >= contador_prod)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p.idp, e.ide);
    }
    else
    {
      i = prod_existe_enc(p.idp, e.ide);
      if (i < todas_encomendas[e.ide].contador_prod_enc)
      {
        todos_produtos[p.idp].qnt += todas_encomendas[e.ide].produtos[i].qnt;
        todas_encomendas[e.ide].peso_total_enc -= todos_produtos[p.idp].peso * todas_encomendas[e.ide].produtos[i].qnt;
        for (j = i; j < (todas_encomendas[e.ide].contador_prod_enc - 1); j++)
          todas_encomendas[e.ide].produtos[j] = todas_encomendas[e.ide].produtos[j + 1];

        todas_encomendas[e.ide].contador_prod_enc--;
      }
      else
      {
        
      }

    }

  }

}

void calcula_custo_enc()
{
  Encomenda e;
  int preco_total = 0;
  int i;
  e.ide = new_sym_var(sizeof(int) * 8);
  if (e.ide >= contador_enc)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", e.ide);
  }
  else
  {
    for (i = 0; i < todas_encomendas[e.ide].contador_prod_enc; i++)
      preco_total += todos_produtos[todas_encomendas[e.ide].produtos[i].idp].preco * todas_encomendas[e.ide].produtos[i].qnt;

    printf("Custo da encomenda %d %d.\n", e.ide, preco_total);
  }

}

void altera_preco_prod()
{
  Produto p;
  int preco_novo;
  p.idp = new_sym_var(sizeof(int) * 8);
  preco_novo = new_sym_var(sizeof(int) * 8);
  if (p.idp >= contador_prod)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p.idp);
  }
  else
  {
    todos_produtos[p.idp].preco = preco_novo;
  }

}

void desc_qnt_prod_enc()
{
  Encomenda e;
  Produto p;
  int i;
  e.ide = new_sym_var(sizeof(int) * 8);
  p.idp = new_sym_var(sizeof(int) * 8);
  if (e.ide >= contador_enc)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);
  }
  else
  {
    if (p.idp >= contador_prod)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", p.idp);
    }
    else
    {
      i = prod_existe_enc(p.idp, e.ide);
      if (i < todas_encomendas[e.ide].contador_prod_enc)
      {
        printf("%s %d.\n", todas_encomendas[e.ide].produtos[i].desc, todas_encomendas[e.ide].produtos[i].qnt);
      }
      else
      {
        printf("%s %d.\n", todos_produtos[p.idp].desc, 0);
      }

    }

  }

}

void enc_mais_prod()
{
  Produto p;
  int j;
  int i;
  int qnt_mais_alta = 0;
  int indice_qnt_mais_alta = -1;
  p.idp = new_sym_var(sizeof(int) * 8);
  if (p.idp >= contador_prod)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p.idp);
  }
  else
  {
    for (j = 0; j < contador_enc; j++)
    {
      i = prod_existe_enc(p.idp, j);
      if ((i < todas_encomendas[j].contador_prod_enc) && (todas_encomendas[j].produtos[i].qnt > qnt_mais_alta))
      {
        qnt_mais_alta = todas_encomendas[j].produtos[i].qnt;
        indice_qnt_mais_alta = j;
      }
      else
      {
        
      }

    }

    if (indice_qnt_mais_alta != (-1))
    {
      printf("Maximo produto %d %d %d.\n", p.idp, indice_qnt_mais_alta, qnt_mais_alta);
    }
    else
    {
      
    }

  }

}

void lista_produtos()
{
  int i;
  Produto copia_lista_prod[10000];
  printf("Produtos\n");
  for (i = 0; i < contador_prod; i++)
    copia_lista_prod[i] = todos_produtos[i];

  mergeSort_preco(copia_lista_prod, 0, contador_prod - 1);
  for (i = 0; i < contador_prod; i++)
    printf("* %s %d %d\n", copia_lista_prod[i].desc, copia_lista_prod[i].preco, copia_lista_prod[i].qnt);

}

void lista_prod_encomenda()
{
  int i;
  Encomenda e;
  Produto copia_prod_enc[500];
  e.ide = new_sym_var(sizeof(int) * 8);
  if (e.ide >= contador_enc)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);
  }
  else
  {
    printf("Encomenda %d\n", e.ide);
    for (i = 0; i < todas_encomendas[e.ide].contador_prod_enc; i++)
      copia_prod_enc[i] = todas_encomendas[e.ide].produtos[i];

    mergeSort_desc(copia_prod_enc, 0, todas_encomendas[e.ide].contador_prod_enc - 1);
    for (i = 0; i < todas_encomendas[e.ide].contador_prod_enc; i++)
      printf("* %s %d %d\n", copia_prod_enc[i].desc, todos_produtos[copia_prod_enc[i].idp].preco, copia_prod_enc[i].qnt);

  }

}
