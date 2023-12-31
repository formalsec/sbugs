#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


int ind_prod = 0;
int encomenda = 0;
int variaveis[3];
char d[63];
typedef struct stock
{
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
  int idp;
} Stock;
Stock produtos[10000];
typedef struct encomendas
{
  int peso;
  int prod_enc[200];
  int qnt_prod_enc[200];
  char desc_prod_enc[200][63];
} Encomendas;
Encomendas enc[500];
void guarda_variaveis(char s[100000])
{
  int h = 0;
  int g;
  int e;
  int f = 0;
  int j;
  j = strlen(s);
  if (j > 1)
  {
    if (s[0] == 'a')
    {
      for (e = 2; e < j; e++)
      {
        if (s[e] != ':')
        {
          d[f] = s[e];
          d[f + 1] = '\0';
          f++;
        }
        else
        {
          g = e;
          break;
        }

      }

      variaveis[0] = 0;
      variaveis[1] = 0;
      variaveis[2] = 0;
      for (e = g + 1; e < j; e++)
      {
        if (s[e] == '\0')
        {
          break;
        }
        else
        {
          if (s[e] == ':')
          {
            h += 1;
          }
          else
          {
            variaveis[h] = ((variaveis[h] * 10) + s[e]) - '0';
          }

        }

      }

    }
    else
    {
      variaveis[0] = 0;
      variaveis[1] = 0;
      variaveis[2] = 0;
      for (e = 2; e < j; e++)
      {
        if (s[e] == '\0')
        {
          break;
        }
        else
        {
          if (s[e] == ':')
          {
            h += 1;
          }
          else
          {
            variaveis[h] = ((variaveis[h] * 10) + s[e]) - '0';
          }

        }

      }

    }

  }
  else
  {
    
  }

}

void merge_l(int a[], int l, int m, int r)
{
  int aux[10000];
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
    if ((produtos[aux[j]].preco < produtos[aux[i]].preco) || ((produtos[aux[j]].preco == produtos[aux[i]].preco) && (aux[j] < aux[i])))
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void mergesort_l(int a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort_l(a, l, m);
  mergesort_l(a, m + 1, r);
  merge_l(a, l, m, r);
}

int aux_merge_L(char a[], char b[])
{
  int j;
  for (j = 0; j < 63; j++)
  {
    if (a[j] > b[j])
    {
      return 1;
    }
    else
    {
      if (a[j] < b[j])
      {
        return 0;
      }
      else
      {
        
      }

    }

  }

  return 0;
}

void merge_L(int a[], int l, int m, int r)
{
  int aux[200];
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
    if (aux_merge_L(produtos[aux[i]].descricao, produtos[aux[j]].descricao))
  {
    a[k] = aux[j--];
  }
  else
  {
    a[k] = aux[i++];
  }


}

void mergesort_L(int a[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  mergesort_L(a, l, m);
  mergesort_L(a, m + 1, r);
  merge_L(a, l, m, r);
}

void comando_a()
{
  int l;
  int i;
  produtos[ind_prod].preco = variaveis[0];
  produtos[ind_prod].peso = variaveis[1];
  produtos[ind_prod].quantidade = variaveis[2];
  for (i = 0; d[i] != '\0'; i++)
    ;

  for (l = 0; l < i; l++)
  {
    produtos[ind_prod].descricao[l] = d[l];
  }

  produtos[ind_prod].idp = ind_prod;
  printf("Novo produto %d.\n", ind_prod);
  ind_prod++;
}

void comando_q()
{
  if (variaveis[0] >= ind_prod)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", variaveis[0]);
  }
  else
  {
    produtos[variaveis[0]].quantidade += variaveis[1];
  }

}

void comando_N()
{
  int w;
  enc[encomenda].peso = 0;
  for (w = 0; w < 200; w++)
  {
    enc[encomenda].prod_enc[w] = 10000;
    enc[encomenda].qnt_prod_enc[w] = 0;
  }

  printf("Nova encomenda %d.\n", encomenda);
  encomenda++;
}

void comando_A()
{
  int w;
  int x;
  if (variaveis[0] >= encomenda)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", variaveis[1], variaveis[0]);
  }
  else
  {
    if (variaveis[1] >= ind_prod)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", variaveis[1], variaveis[0]);
    }
    else
    {
      if (variaveis[2] > produtos[variaveis[1]].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", variaveis[1], variaveis[0]);
      }
      else
      {
        if ((enc[variaveis[0]].peso + (produtos[variaveis[1]].peso * variaveis[2])) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", variaveis[1], variaveis[0]);
        }
        else
        {
          produtos[variaveis[1]].quantidade -= variaveis[2];
          enc[variaveis[0]].peso += produtos[variaveis[1]].peso * variaveis[2];
          for (w = 0; w < ind_prod; w++)
          {
            if (enc[variaveis[0]].prod_enc[w] == variaveis[1])
            {
              enc[variaveis[0]].qnt_prod_enc[w] += variaveis[2];
              break;
            }
            else
            {
              if (enc[variaveis[0]].prod_enc[w] == 10000)
              {
                enc[variaveis[0]].prod_enc[w] = produtos[variaveis[1]].idp;
                enc[variaveis[0]].qnt_prod_enc[w] += variaveis[2];
                for (x = 0; x < 63; x++)
                {
                  enc[variaveis[0]].desc_prod_enc[w][x] = produtos[variaveis[1]].descricao[x];
                }

                break;
              }
              else
              {
                
              }

            }

          }

        }

      }

    }

  }

}

void comando_r()
{
  if (variaveis[0] >= ind_prod)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", variaveis[0]);
  }
  else
  {
    if (variaveis[1] > produtos[variaveis[0]].quantidade)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", variaveis[1], variaveis[0]);
    }
    else
    {
      produtos[variaveis[0]].quantidade -= variaveis[1];
    }

  }

}

void comando_R()
{
  int w;
  if (variaveis[0] >= encomenda)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", variaveis[1], variaveis[0]);
  }
  else
  {
    if (variaveis[1] >= ind_prod)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", variaveis[1], variaveis[0]);
    }
    else
    {
      for (w = 0; w < 200; w++)
      {
        if (enc[variaveis[0]].prod_enc[w] == variaveis[1])
        {
          produtos[enc[variaveis[0]].prod_enc[w]].quantidade += enc[variaveis[0]].qnt_prod_enc[w];
          enc[variaveis[0]].peso -= enc[variaveis[0]].qnt_prod_enc[w] * produtos[variaveis[1]].peso;
          enc[variaveis[0]].qnt_prod_enc[w] = 0;
        }
        else
        {
          
        }

      }

    }

  }

}

void comando_C()
{
  int w;
  int custo = 0;
  if (variaveis[0] >= encomenda)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", variaveis[0]);
  }
  else
  {
    for (w = 0; w < 200; w++)
    {
      if (enc[variaveis[0]].prod_enc[w] != 10000)
      {
        if (enc[variaveis[0]].qnt_prod_enc[w] > 0)
        {
          custo += produtos[enc[variaveis[0]].prod_enc[w]].preco * enc[variaveis[0]].qnt_prod_enc[w];
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", variaveis[0], custo);
  }

}

void comando_p()
{
  if (variaveis[0] >= ind_prod)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", variaveis[0]);
  }
  else
  {
    
  }

  produtos[variaveis[0]].preco = variaveis[1];
}

void comando_E()
{
  int a;
  int b;
  int c;
  int estado = 0;
  if (variaveis[0] >= encomenda)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", variaveis[0]);
  }
  else
  {
    if (variaveis[1] >= ind_prod)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", variaveis[1]);
    }
    else
    {
      for (a = 0; a < 200; a++)
      {
        if (enc[variaveis[0]].prod_enc[a] == produtos[variaveis[1]].idp)
        {
          estado = 1;
          b = produtos[variaveis[1]].idp;
          printf("%s %d.\n", produtos[b].descricao, enc[variaveis[0]].qnt_prod_enc[a]);
        }
        else
        {
          
        }

      }

      if (estado == 0)
      {
        c = produtos[variaveis[1]].idp;
        printf("%s %d.\n", produtos[c].descricao, 0);
      }
      else
      {
        
      }

    }

  }

}

void comando_m()
{
  int b;
  int c;
  int k = 0;
  int i = 0;
  if (variaveis[0] >= ind_prod)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", variaveis[0]);
  }
  else
  {
    
  }

  for (b = 0; b < 500; b++)
  {
    for (c = 0; c < 200; c++)
    {
      if (enc[b].prod_enc[c] == variaveis[0])
      {
        if (enc[b].qnt_prod_enc[c] > k)
        {
          k = enc[b].qnt_prod_enc[c];
          i = b;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

  if (k != 0)
  {
    printf("Maximo produto %d %d %d.\n", variaveis[0], i, k);
  }
  else
  {
    
  }

}

void comando_l()
{
  int listaids[10000];
  int f;
  int l = 0;
  int r = ind_prod;
  int y;
  printf("Produtos\n");
  for (f = 0; f < ind_prod; f++)
  {
    listaids[f] = produtos[f].idp;
  }

  mergesort_l(listaids, l, r - 1);
  for (y = 0; y < ind_prod; y++)
  {
    printf("* %s %d %d\n", produtos[listaids[y]].descricao, produtos[listaids[y]].preco, produtos[listaids[y]].quantidade);
  }

}

void comando_L()
{
  int a;
  int b = 0;
  int c;
  int l = 0;
  int lidps[10000];
  if (variaveis[0] >= encomenda)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", variaveis[0]);
  }
  else
  {
    printf("Encomenda %d\n", variaveis[0]);
    for (a = 0; a < ind_prod; a++)
    {
      if (enc[variaveis[0]].qnt_prod_enc[a] > 0)
      {
        lidps[b++] = enc[variaveis[0]].prod_enc[a];
      }
      else
      {
        
      }

    }

  }

  mergesort_L(lidps, l, b - 1);
  for (a = 0; a < b; a++)
  {
    for (c = 0; c < ind_prod; c++)
    {
      if (lidps[a] == enc[variaveis[0]].prod_enc[c])
      {
        printf("* %s %d %d\n", produtos[lidps[a]].descricao, produtos[lidps[a]].preco, enc[variaveis[0]].qnt_prod_enc[c]);
        break;
      }
      else
      {
        
      }

    }

  }

}

void direciona(char s[100000])
{
  char k;
  k = s[0];
  switch (k)
  {
    case 'a':
      comando_a();
      break;

    case 'q':
      comando_q();
      break;

    case 'N':
      comando_N();
      break;

    case 'A':
      comando_A();
      break;

    case 'r':
      comando_r();
      break;

    case 'R':
      comando_R();
      break;

    case 'C':
      comando_C();
      break;

    case 'p':
      comando_p();
      break;

    case 'E':
      comando_E();
      break;

    case 'm':
      comando_m();
      break;

    case 'l':
      comando_l();
      break;

    case 'L':
      comando_L();
      break;

  }

}

int main()
{
  int i = 0;
  char s[100000];
  char c;
  c = getchar();
  while (i < 100000)
  {
    if (c == 'x')
    {
      break;
    }
    else
    {
      
    }

    while (c != '\n')
    {
      s[i] = c;
      s[i + 1] = '\0';
      c = getchar();
      i++;
    }

    i = 0;
    guarda_variaveis(s);
    direciona(s);
    c = getchar();
  }

  return 0;
}

