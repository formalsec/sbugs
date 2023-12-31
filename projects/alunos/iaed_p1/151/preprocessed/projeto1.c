#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct Produto
{
  char ds[64];
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct Encomenda
{
  produto produtos[10000];
  int peso;
} encomenda;
produto prods[10000] = {0};
encomenda encomends[500] = {0};
int idproduto = 0;
int idencomenda = 0;
void novoProduto()
{
  produto p;
  for (int p_index = 0; p_index < 10; p_index++)
  {
    p.ds[p_index] = new_sym_var(sizeof(char) * 8);
  }

  p.ds[10 - 1] = '\0';
  p.preco = new_sym_var(sizeof(int) * 8);
  p.peso = new_sym_var(sizeof(int) * 8);
  p.qtd = new_sym_var(sizeof(int) * 8);
  prods[idproduto] = p;
  printf("Novo produto %d.\n", idproduto);
  idproduto++;
}

void adicionaStock()
{
  int q;
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  q = new_sym_var(sizeof(int) * 8);
  if (idp >= idproduto)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    prods[idp].qtd += q;
  }

}

void novaEncomenda()
{
  printf("Nova encomenda %d.\n", idencomenda);
  idencomenda++;
}

void adicionaProdEncomenda()
{
  int idp;
  int ide;
  int q;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  q = new_sym_var(sizeof(int) * 8);
  if (ide >= idencomenda)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idproduto)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      if ((prods[idp].qtd - q) < 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
      }
      else
      {
        if ((encomends[ide].peso + (q * prods[idp].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else
        {
          if (encomends[ide].produtos[idp].ds[0] != '\0')
          {
            encomends[ide].peso += q * prods[idp].peso;
            encomends[ide].produtos[idp].qtd += q;
            prods[idp].qtd -= q;
          }
          else
          {
            strcpy(encomends[ide].produtos[idp].ds, prods[idp].ds);
            encomends[ide].produtos[idp].preco = prods[idp].preco;
            encomends[ide].produtos[idp].peso = prods[idp].peso;
            encomends[ide].produtos[idp].qtd = q;
            prods[idp].qtd -= q;
            encomends[ide].peso += q * prods[idp].peso;
          }

        }

      }

    }

  }

}

void removeStock()
{
  int s;
  int id;
  id = new_sym_var(sizeof(int) * 8);
  s = new_sym_var(sizeof(int) * 8);
  if (id >= idproduto)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
  }
  else
  {
    if ((prods[id].qtd - s) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", s, id);
    }
    else
    {
      prods[id].qtd -= s;
    }

  }

}

void removeProdEncomenda()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= idencomenda)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
  }
  else
  {
    if (idp >= idproduto)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
      prods[idp].qtd += encomends[ide].produtos[idp].qtd;
      encomends[ide].peso -= encomends[ide].produtos[idp].peso * encomends[ide].produtos[idp].qtd;
      memset(encomends[ide].produtos[idp].ds, 0, 64);
      encomends[ide].produtos[idp].preco = 0;
      encomends[ide].produtos[idp].peso = 0;
      encomends[ide].produtos[idp].qtd = 0;
    }

  }

}

void calculaCusto()
{
  int ide;
  int total = 0;
  int i;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= idencomenda)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < 10000; i++)
    {
      total += encomends[ide].produtos[i].preco * encomends[ide].produtos[i].qtd;
    }

    printf("Custo da encomenda %d %d.\n", ide, total);
  }

}

void alteraPreco()
{
  int novop;
  int idp;
  int i;
  idp = new_sym_var(sizeof(int) * 8);
  novop = new_sym_var(sizeof(int) * 8);
  if (idp >= idproduto)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    prods[idp].preco = novop;
    for (i = 0; i < idencomenda; i++)
    {
      if (encomends[i].produtos[idp].ds[0] != '\0')
      {
        encomends[i].produtos[idp].preco = novop;
      }
      else
      {
        
      }

    }

  }

}

void listaDsQtdEmEncomenda()
{
  int ide;
  int idp;
  ide = new_sym_var(sizeof(int) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= idencomenda)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    if (idp >= idproduto)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
      printf("%s %d.\n", prods[idp].ds, encomends[ide].produtos[idp].qtd);
    }

  }

}

void listaProdemEncomenda()
{
  int idp;
  int maior = 0;
  int qtdM = 0;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= idproduto)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    int i;
    for (i = 0; i < idencomenda; i++)
    {
      if (encomends[i].produtos[idp].qtd > qtdM)
      {
        maior = i;
        qtdM = encomends[i].produtos[idp].qtd;
      }
      else
      {
        
      }

    }

    if (qtdM != 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, maior, qtdM);
    }
    else
    {
      
    }

  }

}

void merge(produto v[], int l, int m, int r, int Tipo)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  produto L[10000];
  produto R[10000];
  for (i = 0; i < n1; i++)
  {
    L[i] = v[l + i];
  }

  for (i = 0; i < n2; i++)
  {
    R[i] = v[(m + 1) + i];
  }

  i = 0;
  j = 0;
  k = l;
  if (Tipo == 1)
  {
    while ((i < n1) && (j < n2))
    {
      if (L[i].preco <= R[j].preco)
      {
        v[k] = L[i];
        i++;
      }
      else
      {
        v[k] = R[j];
        j++;
      }

      k++;
    }

  }
  else
  {
    while ((i < n1) && (j < n2))
    {
      if (strcmp(L[i].ds, R[j].ds) <= 0)
      {
        v[k] = L[i];
        i++;
      }
      else
      {
        v[k] = R[j];
        j++;
      }

      k++;
    }

  }

  while (i < n1)
  {
    v[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    v[k] = R[j];
    j++;
    k++;
  }

}

void mergeSort(produto v[], int l, int r, int Tipo)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort(v, l, m, Tipo);
    mergeSort(v, m + 1, r, Tipo);
    merge(v, l, m, r, Tipo);
  }
  else
  {
    
  }

}

void listaTodosProds()
{
  produto v[10000];
  int i;
  for (i = 0; i < idproduto; i++)
  {
    v[i] = prods[i];
  }

  mergeSort(v, 0, idproduto - 1, 1);
  printf("Produtos\n");
  for (i = 0; i < idproduto; i++)
  {
    printf("* %s %d %d\n", v[i].ds, v[i].preco, v[i].qtd);
  }

}

void listaTodosProdsemEncomenda()
{
  int ide;
  int counter = 0;
  int i;
  produto v[10000];
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= idencomenda)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
  }
  else
  {
    for (i = 0; i < idproduto; i++)
    {
      if (encomends[ide].produtos[i].ds[0] != '\0')
      {
        v[counter] = encomends[ide].produtos[i];
        counter++;
      }
      else
      {
        
      }

    }

    mergeSort(v, 0, counter - 1, 0);
    printf("Encomenda %d\n", ide);
    for (i = 0; i < counter; i++)
    {
      printf("* %s %d %d\n", v[i].ds, v[i].preco, v[i].qtd);
    }

  }

}

int main()
{
  char c;
  do
  {
    switch (c = getchar())
    {
      case 'a':
        novoProduto();
        break;

      case 'q':
        adicionaStock();
        break;

      case 'N':
        novaEncomenda();
        break;

      case 'A':
        adicionaProdEncomenda();
        break;

      case 'r':
        removeStock();
        break;

      case 'R':
        removeProdEncomenda();
        break;

      case 'C':
        calculaCusto();
        break;

      case 'p':
        alteraPreco();
        break;

      case 'E':
        listaDsQtdEmEncomenda();
        break;

      case 'm':
        listaProdemEncomenda();
        break;

      case 'l':
        listaTodosProds();
        break;

      case 'L':
        listaTodosProdsemEncomenda();
        break;

      default:
        break;

    }

  }
  while (c != 'x');
  return 0;
}

