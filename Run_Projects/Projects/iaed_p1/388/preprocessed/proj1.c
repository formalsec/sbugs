/*File generated by PreProcessor.py*/


#include <stdio.h>


typedef struct produto
{
  char des[63];
  int preco;
  int kg;
  int qtd;
  int id;
} prod;
typedef struct encomenda
{
  int produtos;
  int peso;
  int idprod[10000];
  int qtprod[10000];
} enco;
enco lenco[500];
enco nenco;
int ifinder(int item, int size, int *lista)
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (item == lista[i])
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

void trcprod(int i, int j, prod *clprod)
{
  prod cprod;
  cprod = clprod[i];
  clprod[i] = clprod[j];
  clprod[j] = cprod;
}

int prcig(prod prod1, prod prod2)
{
  if (prod1.preco == prod2.preco)
  {
    return prod1.id < prod2.id;
  }
  else
  {
    
  }

  return prod1.preco < prod2.preco;
}

int divprod(prod *clprod, int e, int d)
{
  int i = e - 1;
  int j = d;
  prod p = clprod[d];
  while (i < j)
  {
    while (prcig(clprod[++i], p))
      ;

    while (prcig(p, clprod[--j]))
      if (j == e)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      trcprod(i, j, clprod);
    }
    else
    {
      
    }

  }

  trcprod(i, d, clprod);
  return i;
}

int divenco(prod *clprod, int e, int d)
{
  int i = e - 1;
  int j = d;
  int ind;
  char cdes[63];
  for (ind = 0; ind < 63; ind++)
    cdes[ind] = clprod[d].des[ind];

  while (i < j)
  {
    while (strcmp(clprod[++i].des, cdes) < 0)
      ;

    while (strcmp(cdes, clprod[--j].des) < 0)
      if (j == e)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      trcprod(i, j, clprod);
    }
    else
    {
      
    }

  }

  trcprod(i, d, clprod);
  return i;
}

void quicksort(prod *clprod, int e, int d, int estado)
{
  int i;
  if (d <= e)
  {
    return;
  }
  else
  {
    
  }

  if (estado == 1)
  {
    i = divprod(clprod, e, d);
    quicksort(clprod, e, i - 1, 1);
    quicksort(clprod, i + 1, d, 1);
  }
  else
  {
    i = divenco(clprod, e, d);
    quicksort(clprod, e, i - 1, 0);
    quicksort(clprod, i + 1, d, 0);
  }

}

void acommand(int idp, prod *lprod)
{
  prod nprod;
  getchar();
  for (int nprod_index = 0; nprod_index < 10; nprod_index++)
  {
    nprod.des[nprod_index] = new_sym_var(sizeof(char) * 8);
  }

  nprod.des[10 - 1] = '\0';
  nprod.preco = new_sym_var(sizeof(int) * 8);
  nprod.kg = new_sym_var(sizeof(int) * 8);
  nprod.qtd = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", idp);
  nprod.id = idp;
  lprod[idp] = nprod;
}

void qcommand(int idp, prod *lprod)
{
  int idpa;
  int qtda;
  getchar();
  idpa = new_sym_var(sizeof(int) * 8);
  qtda = new_sym_var(sizeof(int) * 8);
  if (idp <= idpa)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idpa);
  }
  else
  {
    lprod[idpa].qtd += qtda;
  }

}

void Ncommand(int ide, enco *lenco)
{
  printf("Nova encomenda %d.\n", ide);
  nenco.peso = 0;
  nenco.produtos = 0;
  nenco.qtprod[0] = 0;
  lenco[ide] = nenco;
}

void Acommand(int idp, int ide, prod *lprod, enco *lenco)
{
  int idea;
  int idpa;
  int qtda;
  int fres;
  getchar();
  idea = new_sym_var(sizeof(int) * 8);
  idpa = new_sym_var(sizeof(int) * 8);
  qtda = new_sym_var(sizeof(int) * 8);
  if (ide <= idea)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idpa, idea);
  }
  else
  {
    if (idp <= idpa)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idpa, idea);
    }
    else
    {
      if (lprod[idpa].qtd < qtda)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idpa, idea);
      }
      else
      {
        if ((lenco[idea].peso + (lprod[idpa].kg * qtda)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", idpa, idea, 200);
        }
        else
        {
          fres = ifinder(idpa, lenco[idea].produtos, lenco[idea].idprod);
          if (fres == (-1))
          {
            lenco[idea].idprod[lenco[idea].produtos] = lprod[idpa].id;
            lenco[idea].qtprod[lenco[idea].produtos] += qtda;
            lenco[idea].produtos++;
          }
          else
          {
            lenco[idea].qtprod[fres] += qtda;
          }

          lenco[idea].peso += lprod[idpa].kg * qtda;
          lprod[idpa].qtd -= qtda;
        }

      }

    }

  }

}

void rcommand(int idp, prod *lprod)
{
  int idpa;
  int qtda;
  getchar();
  idpa = new_sym_var(sizeof(int) * 8);
  qtda = new_sym_var(sizeof(int) * 8);
  if (idp <= idpa)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idpa);
  }
  else
  {
    if (lprod[idpa].qtd < qtda)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtda, idpa);
    }
    else
    {
      lprod[idpa].qtd -= qtda;
    }

  }

}

void Rcommand(int idp, int ide, prod *lprod, enco *lenco)
{
  int idpa;
  int idea;
  int fres;
  getchar();
  idea = new_sym_var(sizeof(int) * 8);
  idpa = new_sym_var(sizeof(int) * 8);
  if (ide > idea)
  {
    if (idp <= idpa)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idpa, idea);
    }
    else
    {
      fres = ifinder(idpa, lenco[idea].produtos, lenco[idea].idprod);
      if (fres != (-1))
      {
        lenco[idea].produtos--;
        lenco[idea].peso -= lprod[idpa].kg * lenco[idea].qtprod[fres];
        lprod[idpa].qtd += lenco[idea].qtprod[fres];
        lenco[idea].idprod[fres] = lenco[idea].idprod[lenco[idea].produtos];
        lenco[idea].qtprod[fres] = lenco[idea].qtprod[lenco[idea].produtos];
        lenco[idea].idprod[lenco[idea].produtos] = 0;
        lenco[idea].qtprod[lenco[idea].produtos] = 0;
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idpa, idea);
  }

}

void Ccommand(int ide, prod *lprod, enco *lenco)
{
  int idea;
  int i;
  int res = 0;
  getchar();
  idea = new_sym_var(sizeof(int) * 8);
  if (idea < ide)
  {
    for (i = 0; i < lenco[idea].produtos; i++)
    {
      res += lprod[lenco[idea].idprod[i]].preco * lenco[idea].qtprod[i];
    }

    printf("Custo da encomenda %d %d.\n", idea, res);
  }
  else
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idea);
  }

}

void pcommand(int idp, prod *lprod)
{
  int idpa;
  int pa;
  getchar();
  idpa = new_sym_var(sizeof(int) * 8);
  pa = new_sym_var(sizeof(int) * 8);
  if (idpa < idp)
  {
    lprod[idpa].preco = pa;
  }
  else
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idpa);
  }

}

void Ecommand(int idp, int ide, prod *lprod, enco *lenco)
{
  int idpa;
  int idea;
  int i;
  getchar();
  idea = new_sym_var(sizeof(int) * 8);
  idpa = new_sym_var(sizeof(int) * 8);
  if (ide <= idea)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idea);
  }
  else
  {
    if (idp <= idpa)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idpa);
    }
    else
    {
      i = ifinder(idpa, lenco[idea].produtos, lenco[idea].idprod);
      printf("%s %d.\n", lprod[idpa].des, lenco[idea].qtprod[i]);
    }

  }

}

void mcommand(int idp, int ide, enco *lenco)
{
  int i;
  int max = 0;
  int idea;
  int idpa;
  int j;
  getchar();
  idpa = new_sym_var(sizeof(int) * 8);
  if (idp <= idpa)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idpa);
  }
  else
  {
    for (i = 0; i < ide; i++)
    {
      j = ifinder(idpa, lenco[i].produtos, lenco[i].idprod);
      if (j == (-1))
      {
        continue;
      }
      else
      {
        
      }

      if (max < lenco[i].qtprod[j])
      {
        max = lenco[i].qtprod[j];
        idea = i;
      }
      else
      {
        
      }

    }

    if (max != 0)
    {
      printf("Maximo produto %d %d %d.\n", idpa, idea, max);
    }
    else
    {
      
    }

  }

}

void lcommand(int idp, prod *lprod)
{
  int i;
  prod clprod[10000];
  for (i = 0; i < idp; i++)
    clprod[i] = lprod[i];

  if (idp > 0)
  {
    quicksort(clprod, 0, idp - 1, 1);
  }
  else
  {
    
  }

  printf("Produtos\n");
  for (i = 0; i < idp; i++)
    printf("* %s %d %d\n", clprod[i].des, clprod[i].preco, clprod[i].qtd);

}

void Lcommand(int ide, prod *lprod, enco *lenco)
{
  int i;
  int idea;
  prod clprod[10000];
  getchar();
  idea = new_sym_var(sizeof(int) * 8);
  if (idea < ide)
  {
    for (i = 0; i < lenco[idea].produtos; i++)
    {
      clprod[i] = lprod[lenco[idea].idprod[i]];
      clprod[i].qtd = lenco[idea].qtprod[i];
    }

    quicksort(clprod, 0, lenco[idea].produtos - 1, 0);
    printf("Encomenda %d\n", idea);
    for (i = 0; i < lenco[idea].produtos; i++)
      printf("* %s %d %d\n", clprod[i].des, clprod[i].preco, clprod[i].qtd);

  }
  else
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idea);
  }

}

int main()
{
  prod lprod[10000];
  char c;
  int idp = 0;
  int ide = 0;
  while (1)
  {
    c = getchar();
    switch (c)
    {
      case 'a':
        acommand(idp, lprod);
        idp++;
        break;

      case 'q':
        qcommand(idp, lprod);
        break;

      case 'N':
        Ncommand(ide, lenco);
        ide++;
        break;

      case 'A':
        Acommand(idp, ide, lprod, lenco);
        break;

      case 'r':
        rcommand(idp, lprod);
        break;

      case 'R':
        Rcommand(idp, ide, lprod, lenco);
        break;

      case 'C':
        Ccommand(ide, lprod, lenco);
        break;

      case 'p':
        pcommand(idp, lprod);
        break;

      case 'E':
        Ecommand(idp, ide, lprod, lenco);
        break;

      case 'm':
        mcommand(idp, ide, lenco);
        break;

      case 'l':
        lcommand(idp, lprod);
        break;

      case 'L':
        Lcommand(ide, lprod, lenco);
        break;

      case 'x':
        return 0;

    }

  }

}

