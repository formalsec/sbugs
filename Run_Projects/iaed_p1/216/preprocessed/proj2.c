/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


typedef struct produto
{
  int idp;
  char desc[63];
  long preco;
  long peso;
  long quant;
} Produto;
typedef struct encomenda
{
  int ide;
  long quant[10000];
  int proE;
  long pesoE;
} Encomenda;
Encomenda enc[500];
Produto prod[10000];
char buf[1800];
char tok[2] = ":";
int idpcount = 0;
int idecount = 0;
void printProd(Produto prods[], int count)
{
  int i;
  for (i = 0; i < count; ++i)
  {
    printf("* %s %ld %ld\n", prods[i].desc, prods[i].preco, prods[i].quant);
  }

}

void addEnc()
{
  enc[idecount].ide = idecount;
  enc[idecount].pesoE = 0;
  enc[idecount].proE = 0;
}

void listProd()
{
  int i;
  int j;
  int k;
  Produto temp;
  Produto prodaux[200];
  for (k = 0; k < idpcount; ++k)
  {
    prodaux[k] = prod[k];
  }

  printf("Produtos\n");
  for (i = 0; i < idpcount; ++i)
  {
    for (j = i + 1; j < idpcount; ++j)
    {
      if (prodaux[i].preco > prodaux[j].preco)
      {
        {
          temp = prodaux[i];
          prodaux[i] = prodaux[j];
          prodaux[j] = temp;
        }
      }
      else
      {
        if (prodaux[i].preco == prodaux[j].preco)
        {
          {
            if (prodaux[i].idp > prodaux[j].idp)
            {
              {
                temp = prodaux[i];
                prodaux[i] = prodaux[j];
                prodaux[j] = temp;
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

  }

  printProd(prodaux, idpcount);
}

void addProd()
{
  char *t;
  char *ptr;
  prod[idpcount].idp = idpcount;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  strcpy(prod[idpcount].desc, t);
  t = strtok(0, tok);
  prod[idpcount].preco = strtol(t, &ptr, 10);
  t = strtok(0, tok);
  prod[idpcount].peso = strtol(t, &ptr, 10);
  t = strtok(0, tok);
  prod[idpcount].quant = strtol(t, &ptr, 10);
}

void addStock()
{
  long id;
  long q;
  char *t;
  char *ptr;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  id = strtol(t, &ptr, 10);
  if (id >= idpcount)
  {
    {
      printf("Impossivel adicionar produto %ld ao stock. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      t = strtok(0, tok);
      q = strtol(t, &ptr, 10);
      prod[id].quant += q;
    }
  }

}

void addToEnc()
{
  long e;
  long ip;
  long q;
  long npeso;
  char *t;
  char *ptr;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  e = strtol(t, &ptr, 10);
  t = strtok(0, tok);
  ip = strtol(t, &ptr, 10);
  t = strtok(0, tok);
  q = strtol(t, &ptr, 10);
  npeso = enc[e].pesoE + (q * prod[ip].peso);
  if (e >= idecount)
  {
    {
      printf("Impossivel adicionar produto %ld a encomenda %ld. Encomenda inexistente.\n", ip, e);
      return;
    }
  }
  else
  {
    if (ip >= idpcount)
    {
      {
        printf("Impossivel adicionar produto %ld a encomenda %ld. Produto inexistente.\n", ip, e);
        return;
      }
    }
    else
    {
      if (q > prod[ip].quant)
      {
        {
          printf("Impossivel adicionar produto %ld a encomenda %ld. Quantidade em stock insuficiente.\n", ip, e);
          return;
        }
      }
      else
      {
        if (npeso > 200)
        {
          {
            printf("Impossivel adicionar produto %ld a encomenda %ld. Peso da encomenda excede o maximo de 200.\n", ip, e);
          }
        }
        else
        {
          {
            prod[ip].quant -= q;
            enc[e].quant[ip] += q;
            enc[e].proE++;
            enc[e].pesoE = npeso;
          }
        }

      }

    }

  }

}

void remStock()
{
  long id;
  long q;
  char *t;
  char *ptr;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  id = strtol(t, &ptr, 10);
  t = strtok(0, tok);
  q = strtol(t, &ptr, 10);
  if (id >= idpcount)
  {
    {
      printf("Impossivel remover stock do produto %ld. Produto inexistente.\n", id);
      return;
    }
  }
  else
  {
    if (q > prod[id].quant)
    {
      {
        printf("Impossivel remover %ld unidades do produto %ld do stock. Quantidade insuficiente.\n", q, id);
      }
    }
    else
    {
      {
        prod[id].quant -= q;
      }
    }

  }

}

void remProd()
{
  long e;
  long ip;
  long quanti;
  char *t;
  char *ptr;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  e = strtol(t, &ptr, 10);
  t = strtok(0, tok);
  ip = strtol(t, &ptr, 10);
  if (e >= idecount)
  {
    {
      printf("Impossivel remover produto %ld a encomenda %ld. Encomenda inexistente.\n", ip, e);
      return;
    }
  }
  else
  {
    if (ip >= idpcount)
    {
      {
        printf("Impossivel remover produto %ld a encomenda %ld. Produto inexistente.\n", ip, e);
        return;
      }
    }
    else
    {
      {
        quanti = enc[e].quant[ip];
        enc[e].quant[ip] = 0;
        enc[e].proE--;
        enc[e].pesoE -= quanti * prod[ip].peso;
        prod[ip].quant += quanti;
      }
    }

  }

}

void calcCusto()
{
  long id;
  long total;
  long q;
  long p;
  char *t;
  char *ptr;
  int i;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  id = strtol(t, &ptr, 10);
  if (id >= idecount)
  {
    {
      printf("Impossivel calcular custo da encomenda %ld. Encomenda inexistente.\n", id);
    }
  }
  else
  {
    {
      total = 0;
      for (i = 0; i < idpcount; ++i)
      {
        q = enc[id].quant[i];
        if (q > 0)
        {
          {
            p = prod[i].preco;
            total += p * q;
          }
        }
        else
        {
          
        }

      }

      printf("Custo da encomenda %ld %ld.\n", id, total);
    }
  }

}

void chPri()
{
  long id;
  long p;
  char *t;
  char *ptr;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  id = strtol(t, &ptr, 10);
  if (id >= idpcount)
  {
    {
      printf("Impossivel alterar preco do produto %ld. Produto inexistente.\n", id);
    }
  }
  else
  {
    {
      t = strtok(0, tok);
      p = strtol(t, &ptr, 10);
      prod[id].preco = p;
    }
  }

}

void listProdOrd()
{
  long e;
  long ip;
  long q;
  char *t;
  char *ptr;
  char *d;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  e = strtol(t, &ptr, 10);
  t = strtok(0, tok);
  ip = strtol(t, &ptr, 10);
  if (e >= idecount)
  {
    {
      printf("Impossivel listar encomenda %ld. Encomenda inexistente.\n", e);
      return;
    }
  }
  else
  {
    if (ip >= idpcount)
    {
      {
        printf("Impossivel listar produto %ld. Produto inexistente.\n", ip);
        return;
      }
    }
    else
    {
      {
        d = malloc(strlen(prod[ip].desc) + 1);
        strcpy(d, prod[ip].desc);
        q = enc[e].quant[ip];
        printf("%s %ld.\n", d, q);
        free(d);
      }
    }

  }

}

void listMaxProd()
{
  long id;
  long ide;
  long quant;
  long quantaux;
  int e;
  char *t;
  char *ptr;
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  id = strtol(t, &ptr, 10);
  quant = 0;
  ide = 0;
  if (id >= idpcount)
  {
    {
      printf("Impossivel listar maximo do produto %ld. Produto inexistente.\n", id);
    }
  }
  else
  {
    if (idecount != 0)
    {
      {
        for (e = 0; e < idecount; ++e)
        {
          quantaux = enc[e].quant[id];
          if (quantaux > quant)
          {
            {
              quant = quantaux;
              ide = e;
            }
          }
          else
          {
            
          }

        }

        if (quant > 0)
        {
          {
            printf("Maximo produto %ld %ld %ld.\n", id, ide, quant);
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

void listProdEnc()
{
  long id;
  long q;
  int p;
  int i;
  int j;
  int k;
  Produto temp;
  char *t;
  char *ptr;
  Produto prodaux[200];
  fgets(buf, 1800, stdin);
  strtok(buf, "\n");
  t = strtok(buf, tok);
  id = strtol(t, &ptr, 10);
  q = 0;
  p = 0;
  if (id >= idecount)
  {
    {
      printf("Impossivel listar encomenda %ld. Encomenda inexistente.\n", id);
    }
  }
  else
  {
    {
      printf("Encomenda %ld\n", id);
      for (i = 0; i < idpcount; ++i)
      {
        q = enc[id].quant[i];
        if (q > 0)
        {
          {
            prodaux[p] = prod[i];
            prodaux[p].quant = q;
            p++;
          }
        }
        else
        {
          
        }

      }

      for (k = 0; k < p; ++k)
      {
        for (j = k + 1; j < p; ++j)
        {
          if (strcmp(prodaux[k].desc, prodaux[j].desc) > 0)
          {
            {
              temp = prodaux[k];
              prodaux[k] = prodaux[j];
              prodaux[j] = temp;
            }
          }
          else
          {
            
          }

        }

      }

      printProd(prodaux, p);
    }
  }

}

int main()
{
  while (1)
  {
    char c = getchar();
    switch (c)
    {
      case 'x':
        exit(0);

      case 'N':
        addEnc();
        printf("Nova encomenda %d.\n", idecount++);
        break;

      case 'l':
        listProd();
        break;

      case 'a':
        getchar();
        addProd();
        printf("Novo produto %d.\n", idpcount++);
        break;

      case 'q':
        getchar();
        addStock();
        break;

      case 'A':
        getchar();
        addToEnc();
        break;

      case 'r':
        getchar();
        remStock();
        break;

      case 'R':
        getchar();
        remProd();
        break;

      case 'C':
        getchar();
        calcCusto();
        break;

      case 'p':
        getchar();
        chPri();
        break;

      case 'E':
        getchar();
        listProdOrd();
        break;

      case 'm':
        getchar();
        listMaxProd();
        break;

      case 'L':
        getchar();
        listProdEnc();
        break;

    }

  }

  return 0;
}

