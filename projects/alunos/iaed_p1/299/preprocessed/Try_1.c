#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>


int prox_prod = 0;
int prox_enc = 0;
typedef struct 
{
  int identificador;
  int preco;
  char descricao[64];
  int peso;
  int stock;
} PRODUTO;
typedef struct 
{
  int identificador;
  PRODUTO conjuntos[10000];
  int tamanho;
  int geso;
} ENCOMENDA;
void adiciona();
void adciona_stock();
void adiciona_encomenda();
void adiciona_produto_encomenda();
void remove_stock();
void remove_produto();
void calcula_custo();
void lista_quantidade();
void altera_preco();
void encomenda_produto_repetido();
void merge(PRODUTO a[], int b, int c, int d);
void mergesort(PRODUTO a[], int b, int c);
void ordena_preco();
PRODUTO sistema[10000];
ENCOMENDA sestemas[500];
int main()
{
  char p;
  while (1)
  {
    switch (p = getchar())
    {
      case 'a':
        adiciona();
        break;

      case 'q':
        adciona_stock();
        break;

      case 'N':
        adiciona_encomenda();
        break;

      case 'A':
        adiciona_produto_encomenda();
        break;

      case 'r':
        remove_stock();
        break;

      case 'R':
        remove_produto();
        break;

      case 'C':
        calcula_custo();
        break;

      case 'E':
        lista_quantidade();
        break;

      case 'p':
        altera_preco();
        break;

      case 'm':
        encomenda_produto_repetido();
        break;

      case 'l':
        ordena_preco();
        break;

      case 'x':
        return 0;

    }

  }

  return 0;
}

void adiciona()
{
  char descri[64];
  int i;
  int prec;
  int pes;
  int quant;
  for (int descri_index = 0; descri_index < 10; descri_index++)
  {
    descri[descri_index] = new_sym_var(sizeof(char) * 8);
  }

  descri[10 - 1] = '\0';
  prec = new_sym_var(sizeof(int) * 8);
  pes = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < 64; i++)
  {
    sistema[prox_prod].descricao[i] = descri[i];
  }

  sistema[prox_prod].preco = prec;
  sistema[prox_prod].peso = pes;
  sistema[prox_prod].stock = quant;
  sistema[prox_prod].identificador = prox_prod;
  printf("Novo produto %d.\n", prox_prod);
  prox_prod += 1;
}

void adciona_stock()
{
  int c;
  int a;
  a = new_sym_var(sizeof(int) * 8);
  c = new_sym_var(sizeof(int) * 8);
  sistema[a].stock += c;
  if (a > (prox_prod - 1))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", a);
  }
  else
  {
    
  }

}

void adiciona_encomenda()
{
  sestemas[prox_enc].identificador = prox_enc;
  sestemas[prox_enc].tamanho = 0;
  sestemas[prox_enc].geso = 0;
  printf("Nova encomenda %d.\n", prox_enc);
  prox_enc += 1;
}

void adiciona_produto_encomenda()
{
  int a;
  int b;
  int c;
  int d;
  int i;
  int e;
  a = new_sym_var(sizeof(int) * 8);
  b = new_sym_var(sizeof(int) * 8);
  c = new_sym_var(sizeof(int) * 8);
  d = sestemas[a].tamanho;
  e = d;
  if (a > (prox_enc - 1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", b, a);
    return;
  }
  else
  {
    
  }

  if (b > (prox_prod - 1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", b, a);
    return;
  }
  else
  {
    
  }

  if (c > sistema[b].stock)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", b, a);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < d; i++)
  {
    if (sestemas[a].conjuntos[i].identificador == sistema[b].identificador)
    {
      e = i;
      sestemas[a].conjuntos[i].stock += c;
      sestemas[a].geso += sestemas[a].conjuntos[i].peso * c;
      sistema[b].stock -= c;
      break;
    }
    else
    {
      
    }

  }

  if (sestemas[a].geso > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", b, a);
    sestemas[a].conjuntos[e].stock -= c;
    sestemas[a].geso -= sestemas[a].conjuntos[e].peso * c;
    sistema[b].stock += c;
    return;
  }
  else
  {
    
  }

  if (e == d)
  {
    sestemas[a].conjuntos[d] = sistema[b];
    sestemas[a].conjuntos[d].stock = c;
    sestemas[a].geso += sestemas[a].conjuntos[d].peso * c;
    if (sestemas[a].geso > 200)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", b, a);
      sestemas[a].conjuntos[d].stock = 0;
      sestemas[a].geso -= sestemas[a].conjuntos[d].peso * c;
      return;
    }
    else
    {
      
    }

    sistema[b].stock -= c;
    sestemas[a].tamanho += 1;
  }
  else
  {
    
  }

}

void remove_stock()
{
  int a;
  int b;
  a = new_sym_var(sizeof(int) * 8);
  b = new_sym_var(sizeof(int) * 8);
  if (a > (prox_prod - 1))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", a);
  }
  else
  {
    
  }

  if (a <= (prox_prod - 1))
  {
    sistema[a].stock -= b;
  }
  else
  {
    
  }

  if (sistema[a].stock < 0)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", b, a);
    sistema[a].stock += b;
  }
  else
  {
    
  }

}

void remove_produto()
{
  int ide;
  int idp;
  int guardar;
  int i;
  guardar = -1;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide > (prox_enc - 1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp > (prox_prod - 1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < sestemas[ide].tamanho; i++)
  {
    if (sestemas[ide].conjuntos[i].identificador == sistema[idp].identificador)
    {
      guardar = i;
    }
    else
    {
      
    }

  }

  if (guardar == (-1))
  {
    return;
  }
  else
  {
    
  }

  sistema[idp].stock += sestemas[ide].conjuntos[guardar].stock;
  sestemas[ide].geso -= sestemas[ide].conjuntos[guardar].peso * sestemas[ide].conjuntos[guardar].stock;
  sestemas[ide].conjuntos[guardar].stock = 0;
}

void calcula_custo()
{
  int ide;
  int custo;
  int i;
  custo = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide > (prox_enc - 1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < sestemas[ide].tamanho; i++)
  {
    custo += sestemas[ide].conjuntos[i].preco * sestemas[ide].conjuntos[i].stock;
  }

  ;
  printf("Custo da encomenda %d %d.\n", ide, custo);
}

void altera_preco()
{
  int idp;
  int presso;
  int e;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  presso = new_sym_var(sizeof(int) * 8);
  sistema[idp].preco = presso;
  for (i = 0; i < prox_enc; i++)
  {
    for (e = 0; e < sestemas[i].tamanho; e++)
    {
      if (sestemas[i].conjuntos[e].identificador == sistema[idp].identificador)
      {
        sestemas[i].conjuntos[e].preco = sistema[idp].preco;
      }
      else
      {
        
      }

    }

  }

  if (idp > (prox_prod - 1))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

}

void lista_quantidade()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  printf(" %s %d", sestemas[ide].conjuntos[idp].descricao, sestemas[ide].conjuntos[idp].stock);
  if (ide > (prox_enc - 1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    
  }

  if (idp > (prox_prod - 1))
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    
  }

}

void encomenda_produto_repetido()
{
  int idp;
  int i;
  int e;
  int max;
  int lugar;
  max = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp > (prox_prod - 1))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < prox_enc; i++)
  {
    for (e = 0; e < sestemas[i].tamanho; e++)
    {
      if ((sestemas[i].conjuntos[e].identificador == sistema[idp].identificador) && (sestemas[i].conjuntos[e].stock > max))
      {
        max = sestemas[i].conjuntos[e].stock;
        lugar = i;
      }
      else
      {
        
      }

    }

  }

  if (max > 0)
  {
    printf("Maximo produto %d %d %d.\n", idp, lugar, max);
  }
  else
  {
    
  }

}

void ordena_preco()
{
  PRODUTO copy[10000];
  int i;
  for (i = 0; i < prox_prod; i++)
  {
    copy[i] = sistema[i];
  }

  mergesort(copy, 0, prox_prod - 1);
  printf("Produtos\n");
  for (i = 0; i < prox_prod; i++)
  {
    printf("* %s %d %d em.\n", copy[i].descricao, copy[i].preco, copy[i].stock);
  }

}

void merge(PRODUTO a[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  PRODUTO aux[10000];
  for (i = m + 1; i > left; i--)
    aux[i - 1] = a[i - 1];

  for (j = prox_enc; j < right; j++)
    aux[(right + m) - j] = a[j + 1];

  for (k = left; k <= right; k++)
    if ((aux[j].preco < aux[i].preco) || (i > m))
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void mergesort(PRODUTO a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort(a, l, m);
  mergesort(a, m + 1, r);
  merge(a, l, m, r);
}

