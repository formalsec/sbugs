#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct produto
{
  char descricao[64];
  int preco;
  int peso;
  int stock;
} Produto;
typedef struct encomenda
{
  int id;
  int qnt;
} Encomenda;
Produto listaProdutos[10000];
Encomenda listaEncomendas[500][200];
int listaSort[10000];
int tamListaProdutos = 0;
int tamEncomenda[500];
int tamListaEncomendas = 0;
void a()
{
  int c;
  int i;
  char preco[64];
  char peso[64];
  char stock[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    listaProdutos[tamListaProdutos].descricao[i] = c;
  }

  listaProdutos[tamListaProdutos].descricao[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    preco[i] = c;
  }

  preco[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    peso[i] = c;
  }

  peso[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    stock[i] = c;
  }

  stock[i] = '\0';
  listaProdutos[tamListaProdutos].preco = atoi(preco);
  listaProdutos[tamListaProdutos].peso = atoi(peso);
  listaProdutos[tamListaProdutos].stock = atoi(stock);
  printf("Novo produto %d.\n", tamListaProdutos++);
}

void q()
{
  int c;
  int i;
  char idP[5];
  char qnt[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    idP[i] = c;
  }

  idP[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    qnt[i] = c;
  }

  qnt[i] = '\0';
  if (atoi(idP) >= tamListaProdutos)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", atoi(idP));
    return;
  }
  else
  {
    listaProdutos[atoi(idP)].stock += atoi(qnt);
  }

}

void N()
{
  listaEncomendas[tamListaEncomendas][0].id = 10000;
  listaEncomendas[tamListaEncomendas][0].qnt = 0;
  tamEncomenda[tamListaEncomendas] = 0;
  printf("Nova encomenda %d.\n", tamListaEncomendas++);
}

int peso(int idE)
{
  int i;
  int idP;
  int ret = 0;
  for (i = 0; i < tamEncomenda[idE]; i++)
  {
    idP = listaEncomendas[idE][i].id;
    ret += listaProdutos[idP].peso * listaEncomendas[idE][i].qnt;
  }

  return ret;
}

void A()
{
  int c;
  int i;
  int pesoAdd;
  int naEncomenda = 0;
  int indiceEncomenda;
  char idE[64];
  char idP[64];
  char qnt[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    idE[i] = c;
  }

  idE[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    idP[i] = c;
  }

  idP[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    qnt[i] = c;
  }

  qnt[i] = '\0';
  if (atoi(idE) >= tamListaEncomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(idP), atoi(idE));
    return;
  }
  else
  {
    if (atoi(idP) >= tamListaProdutos)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", atoi(idP), atoi(idE));
      return;
    }
    else
    {
      
    }

  }

  if (atoi(qnt) == 0)
  {
    return;
  }
  else
  {
    
  }

  for (i = 0; i < tamEncomenda[atoi(idE)]; i++)
  {
    if (listaEncomendas[atoi(idE)][i].id == atoi(idP))
    {
      indiceEncomenda = i;
      naEncomenda = 1;
      break;
    }
    else
    {
      
    }

  }

  pesoAdd = listaProdutos[atoi(idP)].peso * atoi(qnt);
  if (atoi(qnt) > listaProdutos[atoi(idP)].stock)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(idP), atoi(idE));
    return;
  }
  else
  {
    if ((peso(atoi(idE)) + pesoAdd) > 200)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", atoi(idP), atoi(idE));
      return;
    }
    else
    {
      if (naEncomenda)
      {
        listaEncomendas[atoi(idE)][indiceEncomenda].id = atoi(idP);
        listaEncomendas[atoi(idE)][indiceEncomenda].qnt += atoi(qnt);
        listaProdutos[atoi(idP)].stock -= atoi(qnt);
      }
      else
      {
        listaEncomendas[atoi(idE)][tamEncomenda[atoi(idE)]].id = atoi(idP);
        listaEncomendas[atoi(idE)][tamEncomenda[atoi(idE)]].qnt = atoi(qnt);
        listaProdutos[atoi(idP)].stock -= atoi(qnt);
        tamEncomenda[atoi(idE)]++;
      }

    }

  }

}

void r()
{
  int c;
  int i;
  char idP[5];
  char qnt[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    idP[i] = c;
  }

  idP[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    qnt[i] = c;
  }

  qnt[i] = '\0';
  if (atoi(idP) >= tamListaProdutos)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(idP));
    return;
  }
  else
  {
    if (atoi(qnt) > listaProdutos[atoi(idP)].stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(qnt), atoi(idP));
      return;
    }
    else
    {
      listaProdutos[atoi(idP)].stock -= atoi(qnt);
    }

  }

}

void R()
{
  int c;
  int i;
  int naEncomenda = -1;
  char idE[64];
  char idP[64];
  Encomenda t;
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    idE[i] = c;
  }

  idE[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    idP[i] = c;
  }

  idP[i] = '\0';
  if (atoi(idE) >= tamListaEncomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(idP), atoi(idE));
    return;
  }
  else
  {
    if (atoi(idP) >= tamListaProdutos)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(idP), atoi(idE));
      return;
    }
    else
    {
      for (i = 0; i < tamEncomenda[atoi(idE)]; i++)
      {
        if (listaEncomendas[atoi(idE)][i].id == atoi(idP))
        {
          naEncomenda = i;
          break;
        }
        else
        {
          
        }

      }

      if (naEncomenda >= 0)
      {
        listaProdutos[atoi(idP)].stock += listaEncomendas[atoi(idE)][naEncomenda].qnt;
        for (i = naEncomenda; i < (tamEncomenda[atoi(idE)] - 1); i++)
        {
          t = listaEncomendas[atoi(idE)][i];
          listaEncomendas[atoi(idE)][i] = listaEncomendas[atoi(idE)][i + 1];
          listaEncomendas[atoi(idE)][i + 1] = t;
        }

        tamEncomenda[atoi(idE)]--;
      }
      else
      {
        
      }

    }

  }

}

void C()
{
  int c;
  int i;
  int precoTotal = 0;
  int precoParcial;
  int idP;
  char idE[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    idE[i] = c;
  }

  idE[i] = '\0';
  if (atoi(idE) >= tamListaEncomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(idE));
  }
  else
  {
    for (i = 0; i < tamEncomenda[atoi(idE)]; i++)
    {
      idP = listaEncomendas[atoi(idE)][i].id;
      precoParcial = listaEncomendas[atoi(idE)][i].qnt * listaProdutos[idP].preco;
      precoTotal += precoParcial;
    }

    printf("Custo da encomenda %d %d.\n", atoi(idE), precoTotal);
  }

}

void p()
{
  int c;
  int i;
  char idP[5];
  char preco[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    idP[i] = c;
  }

  idP[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    preco[i] = c;
  }

  preco[i] = '\0';
  if (atoi(idP) >= tamListaProdutos)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(idP));
  }
  else
  {
    listaProdutos[atoi(idP)].preco = atoi(preco);
  }

}

void E()
{
  int c;
  int i;
  int naEncomenda = 0;
  char idE[64];
  char idP[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != ':'); i++)
  {
    idE[i] = c;
  }

  idE[i] = '\0';
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    idP[i] = c;
  }

  idP[i] = '\0';
  if (atoi(idE) >= tamListaEncomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(idE));
    return;
  }
  else
  {
    if (atoi(idP) >= tamListaProdutos)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(idP));
      return;
    }
    else
    {
      for (i = 0; i < tamEncomenda[atoi(idE)]; i++)
      {
        if (listaEncomendas[atoi(idE)][i].id == atoi(idP))
        {
          naEncomenda = 1;
          break;
        }
        else
        {
          
        }

      }

      if (naEncomenda)
      {
        printf("%s %d.\n", listaProdutos[atoi(idP)].descricao, listaEncomendas[atoi(idE)][i].qnt);
      }
      else
      {
        printf("%s 0.\n", listaProdutos[atoi(idP)].descricao);
      }

    }

  }

}

void m()
{
  int c;
  int i;
  int j;
  int max[2];
  char idP[64];
  max[0] = -1;
  max[1] = -1;
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    idP[i] = c;
  }

  idP[i] = '\0';
  if (atoi(idP) >= tamListaProdutos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", atoi(idP));
  }
  else
  {
    for (i = 0; i < tamListaEncomendas; i++)
    {
      for (j = 0; j < tamEncomenda[i]; j++)
      {
        if (listaEncomendas[i][j].id == atoi(idP))
        {
          if (max[1] < listaEncomendas[i][j].qnt)
          {
            max[0] = i;
            max[1] = listaEncomendas[i][j].qnt;
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

    if (max[0] >= 0)
    {
      printf("Maximo produto %d %d %d.\n", atoi(idP), max[0], max[1]);
    }
    else
    {
      
    }

  }

}

int partition(int a[], int l, int r)
{
  int i = l;
  int j = r;
  int v = listaProdutos[a[r]].preco;
  int t;
  while (i < j)
  {
    while (listaProdutos[a[i]].preco <= v)
    {
      if (i == r)
      {
        break;
      }
      else
      {
        if ((listaProdutos[a[i]].preco == v) && (a[i] > a[r]))
        {
          break;
        }
        else
        {
          i++;
        }

      }

    }

    while (listaProdutos[a[j]].preco >= v)
    {
      if (j == l)
      {
        break;
      }
      else
      {
        if ((listaProdutos[a[j]].preco == v) && (a[j] < a[r]))
        {
          break;
        }
        else
        {
          j--;
        }

      }

    }

    if (i < j)
    {
      t = a[j];
      a[j] = a[i];
      a[i] = t;
    }
    else
    {
      
    }

  }

  t = a[r];
  a[r] = a[i];
  a[i] = t;
  return i;
}

void quicksort(int a[], int l, int r)
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

void l()
{
  int i;
  for (i = 0; i < tamListaProdutos; i++)
  {
    listaSort[i] = i;
  }

  quicksort(listaSort, 0, tamListaProdutos - 1);
  printf("Produtos\n");
  for (i = 0; i < tamListaProdutos; i++)
  {
    printf("* %s %d %d\n", listaProdutos[listaSort[i]].descricao, listaProdutos[listaSort[i]].preco, listaProdutos[listaSort[i]].stock);
  }

}

int compString(char c1[], char c2[])
{
  int i = 0;
  int ret = 0;
  while ((c1[i] != '\0') || (c2[i] != '\0'))
  {
    if (c1[i] > c2[i])
    {
      ret = 1;
      break;
    }
    else
    {
      if (c1[i] < c2[i])
      {
        ret = -1;
        break;
      }
      else
      {
        
      }

    }

    i++;
  }

  return ret;
}

void descSort(int idE, int start)
{
  int i;
  int idMin;
  int prodIdMin;
  int prodIdTemp;
  Encomenda t;
  if (start >= (tamEncomenda[idE] - 1))
  {
    return;
  }
  else
  {
    prodIdMin = listaEncomendas[idE][start].id;
    idMin = start;
    for (i = start + 1; i <= (tamEncomenda[idE] - 1); i++)
    {
      prodIdTemp = listaEncomendas[idE][i].id;
      if (compString(listaProdutos[prodIdMin].descricao, listaProdutos[prodIdTemp].descricao) >= 1)
      {
        prodIdMin = prodIdTemp;
        idMin = i;
      }
      else
      {
        
      }

    }

    if (start != idMin)
    {
      t = listaEncomendas[idE][start];
      listaEncomendas[idE][start] = listaEncomendas[idE][idMin];
      listaEncomendas[idE][idMin] = t;
    }
    else
    {
      
    }

    descSort(idE, start + 1);
  }

}

void printEncomenda(int idE)
{
  int i;
  int id;
  printf("Encomenda %d\n", idE);
  for (i = 0; i < tamEncomenda[idE]; i++)
  {
    id = listaEncomendas[idE][i].id;
    printf("* %s %d %d\n", listaProdutos[id].descricao, listaProdutos[id].preco, listaEncomendas[idE][i].qnt);
  }

}

void L()
{
  int c;
  int i;
  char idE[64];
  getchar();
  for (i = 0; ((i < 64) && ((c = getchar()) != EOF)) && (c != '\n'); i++)
  {
    idE[i] = c;
  }

  idE[i] = '\0';
  if (atoi(idE) >= tamListaEncomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(idE));
    return;
  }
  else
  {
    
  }

  if (tamEncomenda[atoi(idE)] >= 1)
  {
    descSort(atoi(idE), 0);
  }
  else
  {
    
  }

  printEncomenda(atoi(idE));
}

int main()
{
  char opt;
  while (1)
  {
    opt = new_sym_var(sizeof(char) * 8);
    switch (opt)
    {
      case 'a':
        a();
        break;

      case 'q':
        q();
        break;

      case 'N':
        N();
        break;

      case 'A':
        A();
        break;

      case 'r':
        r();
        break;

      case 'R':
        R();
        break;

      case 'C':
        C();
        break;

      case 'p':
        p();
        break;

      case 'E':
        E();
        break;

      case 'm':
        m();
        break;

      case 'l':
        l();
        break;

      case 'L':
        L();
        break;

      case 'x':
        return 0;

    }

  }

}
