#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


struct produto
{
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
};
struct produto p[10000];
struct encomenda
{
  struct produto p[10000];
};
struct encomenda e[500];
void addprod(int idp)
{
  for (int p_index = 0; p_index < 10; p_index++)
  {
    p[idp].descricao[p_index] = new_sym_var(sizeof(char) * 8);
  }

  p[idp].descricao[10 - 1] = '\0';
  p[idp].preco = new_sym_var(sizeof(int) * 8);
  p[idp].peso = new_sym_var(sizeof(int) * 8);
  p[idp].quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
}

void addstock(int nprodutos)
{
  int quant;
  int idprod;
  idprod = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (nprodutos > idprod)
  {
    p[idprod].quantidade = p[idprod].quantidade + quant;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idprod);
  }

}

void newenco(int ide)
{
  printf("Nova encomenda %d.\n", ide);
}

void addprodenc(int nencomendas, int nprodutos, int pesototalenc[500], int nprodenc[500])
{
  int idenc;
  int idprod;
  int quant;
  idenc = new_sym_var(sizeof(int) * 8);
  idprod = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (nencomendas <= idenc)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idprod, idenc);
  }
  else
  {
    if (nprodutos <= idprod)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idprod, idenc);
    }
    else
    {
      if (quant > p[idprod].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idprod, idenc);
      }
      else
      {
        if ((pesototalenc[idenc] + (p[idprod].peso * quant)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idprod, idenc);
        }
        else
        {
          if (e[idenc].p[idprod].preco == 0)
          {
            nprodenc[idenc]++;
          }
          else
          {
            
          }

          e[idenc].p[idprod].quantidade = e[idenc].p[idprod].quantidade + quant;
          p[idprod].quantidade = p[idprod].quantidade - quant;
          e[idenc].p[idprod].preco = p[idprod].preco;
          e[idenc].p[idprod].peso = p[idprod].peso;
          strcpy(e[idenc].p[idprod].descricao, p[idprod].descricao);
          pesototalenc[idenc] = pesototalenc[idenc] + (e[idenc].p[idprod].peso * quant);
        }

      }

    }

  }

}

void remstock(int nprodutos)
{
  int quant;
  int idprod;
  idprod = new_sym_var(sizeof(int) * 8);
  quant = new_sym_var(sizeof(int) * 8);
  if (nprodutos <= idprod)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idprod);
  }
  else
  {
    if ((p[idprod].quantidade - quant) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, idprod);
    }
    else
    {
      p[idprod].quantidade = p[idprod].quantidade - quant;
    }

  }

}

void remprodenc(int nprodutos, int nencomendas, int pesototalenc[500])
{
  int idenc;
  int idprod;
  idenc = new_sym_var(sizeof(int) * 8);
  idprod = new_sym_var(sizeof(int) * 8);
  if (nencomendas <= idenc)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idprod, idenc);
  }
  else
  {
    if (nprodutos <= idprod)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idprod, idenc);
    }
    else
    {
      pesototalenc[idenc] = pesototalenc[idenc] - (e[idenc].p[idprod].peso * e[idenc].p[idprod].quantidade);
      p[idprod].quantidade = p[idprod].quantidade + e[idenc].p[idprod].quantidade;
      e[idenc].p[idprod].quantidade = 0;
    }

  }

}

void enccost(int nencomendas)
{
  int idenc;
  int i;
  int custo = 0;
  idenc = new_sym_var(sizeof(int) * 8);
  if (nencomendas <= idenc)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idenc);
  }
  else
  {
    for (i = 0; i < 10000; i++)
    {
      if (e[idenc].p[i].preco > 0)
      {
        custo = custo + (e[idenc].p[i].preco * e[idenc].p[i].quantidade);
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", idenc, custo);
  }

}

void mudaprecoprod(int nprodutos, int nencomendas)
{
  int idprod;
  int precop;
  int x;
  idprod = new_sym_var(sizeof(int) * 8);
  precop = new_sym_var(sizeof(int) * 8);
  if (nprodutos <= idprod)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idprod);
  }
  else
  {
    p[idprod].preco = precop;
    for (x = 0; x < nencomendas; x++)
    {
      e[x].p[idprod].preco = precop;
    }

  }

}

void descquant(int nencomendas, int nprodutos)
{
  int idenc;
  int idprod;
  idenc = new_sym_var(sizeof(int) * 8);
  idprod = new_sym_var(sizeof(int) * 8);
  if (nencomendas <= idenc)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idenc);
  }
  else
  {
    if (nprodutos <= idprod)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idprod);
    }
    else
    {
      printf("%s %d.\n", p[idprod].descricao, e[idenc].p[idprod].quantidade);
    }

  }

}

void prodocorremaisx(int nencomendas, int nprodutos)
{
  int i;
  int idprod;
  int idenc;
  int maxtimes = 0;
  idprod = new_sym_var(sizeof(int) * 8);
  if (nprodutos <= idprod)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idprod);
  }
  else
  {
    
  }

  for (i = 0; i < nencomendas; i++)
  {
    if (e[i].p[idprod].quantidade > maxtimes)
    {
      maxtimes = e[i].p[idprod].quantidade;
      idenc = i;
    }
    else
    {
      
    }

  }

  if (maxtimes != 0)
  {
    printf("Maximo produto %d %d %d.\n", idprod, idenc, maxtimes);
  }
  else
  {
    
  }

}

void mergepre(struct produto cp[10000], int s, int e)
{
  int mid = (s + e) / 2;
  int i = s;
  int j = mid + 1;
  int k = s;
  struct produto atemp[10000];
  while ((i <= mid) && (j <= e))
  {
    if (cp[i].preco <= cp[j].preco)
    {
      atemp[k++] = cp[i++];
    }
    else
    {
      atemp[k++] = cp[j++];
    }

  }

  while (i <= mid)
    atemp[k++] = cp[i++];

  while (j <= e)
    atemp[k++] = cp[j++];

  for (j = s; j <= e; j++)
    cp[j] = atemp[j];

}

void mergesortpre(struct produto cp[10000], int s, int e)
{
  int mid = (s + e) / 2;
  if (s >= e)
  {
    return;
  }
  else
  {
    
  }

  mergesortpre(cp, s, mid);
  mergesortpre(cp, mid + 1, e);
  mergepre(cp, s, e);
}

void sortpreco(int nprodutos)
{
  int x;
  int s;
  int e;
  struct produto cp[10000];
  s = 0;
  e = nprodutos - 1;
  for (x = 0; x < nprodutos; x++)
  {
    cp[x] = p[x];
  }

  mergesortpre(cp, s, e);
  printf("Produtos\n");
  for (x = 0; x < nprodutos; x++)
  {
    printf("* %s %d %d\n", cp[x].descricao, cp[x].preco, cp[x].quantidade);
  }

}

void mergealfa(struct produto cp[10000], int l, int r)
{
  int m = (l + r) / 2;
  int i;
  int j;
  int k;
  struct produto atemp[10000];
  for (i = m + 1; i > l; i--)
    atemp[i - 1] = cp[i - 1];

  for (j = m; j < r; j++)
    atemp[(r + m) - j] = cp[j + 1];

  for (k = l; k <= r; k++)
  {
    if ((strcmp(atemp[j].descricao, atemp[i].descricao) < 0) || (i > m))
    {
      cp[k] = atemp[j--];
    }
    else
    {
      cp[k] = atemp[i++];
    }

  }

}

void mergesortalfa(struct produto cp[10000], int l, int r)
{
  int mid = (l + r) / 2;
  if (l >= r)
  {
    return;
  }
  else
  {
    
  }

  mergesortalfa(cp, l, mid);
  mergesortalfa(cp, mid + 1, r);
  mergealfa(cp, l, r);
}

void sortalfa(int nencomendas)
{
  int x;
  int l;
  int r;
  int idenc;
  struct produto cp[10000];
  idenc = new_sym_var(sizeof(int) * 8);
  l = 0;
  r = 10000 - 1;
  if (nencomendas <= idenc)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idenc);
  }
  else
  {
    for (x = 0; x < 10000; x++)
    {
      cp[x].preco = 0;
      cp[x].quantidade = 0;
    }

    for (x = 0; x < 10000; x++)
    {
      if (e[idenc].p[x].preco > 0)
      {
        cp[x] = e[idenc].p[x];
      }
      else
      {
        
      }

    }

    mergesortalfa(cp, l, r);
    printf("Encomenda %d\n", idenc);
    for (x = 0; x < 10000; x++)
    {
      if (cp[x].quantidade > 0)
      {
        printf("* %s %d %d\n", cp[x].descricao, cp[x].preco, cp[x].quantidade);
      }
      else
      {
        
      }

    }

  }

}

int main()
{
  int idp;
  int ide;
  int nencomendas;
  int nprodutos;
  int nprodenc[500] = {0};
  int pesototalenc[500] = {0};
  char c;
  idp = 0;
  ide = 0;
  nencomendas = 0;
  nprodutos = 0;
  c = getchar();
  while (c != 'x')
  {
    switch (c)
    {
      case 'a':
        addprod(idp);
        idp++;
        nprodutos++;
        break;

      case 'q':
        addstock(nprodutos);
        break;

      case 'N':
        newenco(ide);
        ide++;
        nencomendas++;
        break;

      case 'A':
        addprodenc(nencomendas, nprodutos, pesototalenc, nprodenc);
        break;

      case 'r':
        remstock(nprodutos);
        break;

      case 'R':
        remprodenc(nprodutos, nencomendas, pesototalenc);
        break;

      case 'C':
        enccost(nencomendas);
        break;

      case 'p':
        mudaprecoprod(nprodutos, nencomendas);
        break;

      case 'E':
        descquant(nencomendas, nprodutos);
        break;

      case 'm':
        prodocorremaisx(nencomendas, nprodutos);
        break;

      case 'l':
        sortpreco(nprodutos);
        break;

      case 'L':
        sortalfa(nencomendas);
        break;

    }

    c = getchar();
  }

  return 0;
}

