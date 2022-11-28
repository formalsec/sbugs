#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>


typedef struct 
{
  int id;
  int preco;
  int peso;
  int qtd;
  char desc[64];
} TProduto;
struct ProdEnco
{
  int id;
  int qtd;
};
typedef struct 
{
  int N;
  struct ProdEnco prod[200];
} TEncomenda;
typedef int Item;
int N = 0;
int M = 0;
Item aux[10000];
TProduto prod[10000];
TEncomenda enco[500];
void merge(Item a[], int lo, int mid, int hi, int key)
{
  int i = lo;
  int j = mid + 1;
  int k;
  for (k = lo; k <= hi; k++)
    aux[k] = a[k];

  for (k = lo; k <= hi; k++)
    if ((i <= mid) && ((j > hi) || (((key == (-1)) && (prod[aux[i]].preco <= prod[aux[j]].preco)) || ((key >= 0) && (strcmp(prod[enco[key].prod[aux[i]].id].desc, prod[enco[key].prod[aux[j]].id].desc) <= 0)))))
  {
    a[k] = aux[i++];
  }
  else
  {
    a[k] = aux[j++];
  }


}

void mergeSort(Item a[], int lo, int hi, int key)
{
  if (hi > lo)
  {
    int mid = (lo + hi) / 2;
    mergeSort(a, lo, mid, key);
    mergeSort(a, mid + 1, hi, key);
    merge(a, lo, mid, hi, key);
  }
  else
  {
    
  }

}

int indiceProdEnco(int idp, int ide)
{
  int i;
  for (i = 0; i < enco[ide].N; i++)
    if (enco[ide].prod[i].id == idp)
  {
    return i;
  }
  else
  {
    
  }


  return -1;
}

void adicionaProdEnco(int ide, int idp, int qtd)
{
  int i = indiceProdEnco(idp, ide);
  if (i >= 0)
  {
    enco[ide].prod[i].qtd += qtd;
  }
  else
  {
    i = enco[ide].N;
    enco[ide].prod[i].id = idp;
    enco[ide].prod[i].qtd = qtd;
    enco[ide].N++;
  }

  prod[idp].qtd -= qtd;
}

int pesoEnco(int ide)
{
  int i;
  int r = 0;
  for (i = 0; i < enco[ide].N; i++)
    r += enco[ide].prod[i].qtd * prod[enco[ide].prod[i].id].peso;

  return r;
}

int quantProdEnco(int idp, int ide)
{
  int i = indiceProdEnco(idp, ide);
  if (i >= 0)
  {
    return enco[ide].prod[i].qtd;
  }
  else
  {
    return 0;
  }

}

int custoEnco(int ide)
{
  int i;
  int v = 0;
  for (i = 0; i < enco[ide].N; i++)
    v += enco[ide].prod[i].qtd * prod[enco[ide].prod[i].id].preco;

  return v;
}

void removeProdEnco(int ide, int idp)
{
  int i = indiceProdEnco(idp, ide);
  if (i >= 0)
  {
    prod[idp].qtd += enco[ide].prod[i].qtd;
    enco[ide].N--;
    for (; i < enco[ide].N; i++)
    {
      enco[ide].prod[i].id = enco[ide].prod[i + 1].id;
      enco[ide].prod[i].qtd = enco[ide].prod[i + 1].qtd;
    }

  }
  else
  {
    
  }

}

int encomendaMaiorQuantProd(int idp)
{
  int i;
  int ide = -1;
  int qtd;
  int max = 0;
  for (i = 0; i < M; i++)
  {
    if ((qtd = quantProdEnco(idp, i)) > max)
    {
      ide = i;
      max = qtd;
    }
    else
    {
      
    }

  }

  return ide;
}

void case_A()
{
  char str[64];
  int idp;
  int ide;
  int qtd;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  sprintf(str, "Impossivel adicionar produto %d a encomenda %d.", idp, ide);
  if (ide >= M)
  {
    printf("%s Encomenda inexistente.\n", str);
  }
  else
  {
    if (idp >= N)
    {
      printf("%s Produto inexistente.\n", str);
    }
    else
    {
      if (qtd > prod[idp].qtd)
      {
        printf("%s Quantidade em stock insuficiente.\n", str);
      }
      else
      {
        if ((pesoEnco(ide) + (qtd * prod[idp].peso)) > 200)
        {
          printf("%s Peso da encomenda excede o maximo de 200.\n", str);
        }
        else
        {
          adicionaProdEnco(ide, idp, qtd);
        }

      }

    }

  }

}

void case_E()
{
  int idp;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= M)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= N)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      printf("%s %d.\n", prod[idp].desc, quantProdEnco(idp, ide));
    }

  }

}

void case_q()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= N)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    prod[idp].qtd += qtd;
  }

}

void case_r()
{
  int idp;
  int qtd;
  idp = new_sym_var(sizeof(int) * 8);
  qtd = new_sym_var(sizeof(int) * 8);
  if (idp >= N)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    if (qtd > prod[idp].qtd)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
      prod[idp].qtd -= qtd;
    }

  }

}

void case_R()
{
  int idp;
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= M)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= N)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      removeProdEnco(ide, idp);
    }

  }

}

void case_C()
{
  int ide;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= M)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", ide, custoEnco(ide));
  }

}

void case_p()
{
  int idp;
  int preco;
  idp = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp >= N)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    prod[idp].preco = preco;
  }

}

void case_m()
{
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= N)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    int ide = encomendaMaiorQuantProd(idp);
    if (ide >= 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, ide, quantProdEnco(idp, ide));
    }
    else
    {
      
    }

  }

}

void imprimeProd(Item ord[])
{
  int i;
  printf("Produtos\n");
  for (i = 0; i < N; i++)
  {
    printf("* %s %d %d\n", prod[ord[i]].desc, prod[ord[i]].preco, prod[ord[i]].qtd);
  }

}

void imprimeEnco(int ide, Item ord[])
{
  int i;
  printf("Encomenda %d\n", ide);
  for (i = 0; i < enco[ide].N; i++)
    printf("* %s %d %d\n", prod[enco[ide].prod[ord[i]].id].desc, prod[enco[ide].prod[ord[i]].id].preco, enco[ide].prod[ord[i]].qtd);

}

void naturais(Item a[], int n)
{
  while ((--n) >= 0)
    a[n] = n;

}

void case_l()
{
  Item ord[10000];
  naturais(ord, N);
  mergeSort(ord, 0, N - 1, -1);
  imprimeProd(ord);
}

void case_L()
{
  int ide;
  Item ord[200];
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= M)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    naturais(ord, enco[ide].N);
    mergeSort(ord, 0, enco[ide].N - 1, ide);
    imprimeEnco(ide, ord);
  }

}

void case_k()
{
  Item ord[10000];
  naturais(ord, N);
  imprimeProd(ord);
}

void case_K()
{
  int ide;
  Item ord[200];
  ide = new_sym_var(sizeof(int) * 8);
  naturais(ord, enco[ide].N);
  imprimeEnco(ide, ord);
}

int main()
{
  char c;
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
        for (int prod_index = 0; prod_index < 10; prod_index++)
      {
        prod[N].desc[prod_index] = new_sym_var(sizeof(char) * 8);
      }

        prod[N].desc[10 - 1] = '\0';
        prod[N].preco = new_sym_var(sizeof(int) * 8);
        prod[N].peso = new_sym_var(sizeof(int) * 8);
        prod[N].qtd = new_sym_var(sizeof(int) * 8);
        prod[N].id = N;
        printf("Novo produto %d.\n", N);
        N++;
        break;

      case 'N':
        printf("Nova encomenda %d.\n", M);
        enco[M].N = 0;
        M++;
        break;

      case 'A':
        case_A();
        break;

      case 'E':
        case_E();
        break;

      case 'q':
        case_q();
        break;

      case 'r':
        case_r();
        break;

      case 'R':
        case_R();
        break;

      case 'C':
        case_C();
        break;

      case 'p':
        case_p();
        break;

      case 'm':
        case_m();
        break;

      case 'l':
        case_l();
        break;

      case 'L':
        case_L();
        break;

      case 'k':
        case_k();
        break;

      case 'K':
        case_K();
        break;

      default:
        printf("KO\n");

    }

  }

  return 0;
}
