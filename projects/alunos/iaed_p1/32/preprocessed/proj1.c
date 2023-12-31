#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct 
{
  char descricao[63];
  int preco;
  int peso;
  int quantidade;
} Produto;
void novo_produto(int idp);
void adiciona_stock_produto(int numero_de_produtos);
void nova_encomenda(int ide);
int encomenda_peso(int ide, int numero_de_produtos);
void adiciona_produto_a_encomenda(int numero_de_encomendas, int numero_de_produtos);
void remove_stock_produto(int numero_de_produtos);
void remove_produto_encomenda(int numero_de_encomendas, int numero_de_produtos);
void custo_encomenda(int numero_de_encomendas, int numero_de_produtos);
void altera_preco(int numero_de_produtos);
void lista_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos);
void maximo_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos);
void merge_por_preco(Produto produtos[], int l, int m, int r);
void mergesort_por_preco(Produto produtos[], int l, int r);
void lista_por_preco(int numero_de_produtos);
void exch(Produto produtos[], int i, int j);
int partition_por_alf(Produto produtos[], int left, int right);
void quicksort_por_alf(Produto produtos[], int left, int right);
void lista_por_alf(int numero_de_encomendas, int numero_de_produtos);
Produto produtos[10000];
int encomendas[500][10000] = {{0}};
int main()
{
  int idp = 0;
  int ide = 0;
  char comando;
  while (1)
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        novo_produto(idp);
        idp += 1;
        break;

      case 'q':
        adiciona_stock_produto(idp);
        break;

      case 'N':
        nova_encomenda(ide);
        ide += 1;
        break;

      case 'A':
        adiciona_produto_a_encomenda(ide, idp);
        break;

      case 'r':
        remove_stock_produto(idp);
        break;

      case 'R':
        remove_produto_encomenda(ide, idp);
        break;

      case 'C':
        custo_encomenda(ide, idp);
        break;

      case 'p':
        altera_preco(idp);
        break;

      case 'E':
        lista_produto_numa_encomenda(ide, idp);
        break;

      case 'm':
        maximo_produto_numa_encomenda(ide, idp);
        break;

      case 'l':
        lista_por_preco(idp);
        break;

      case 'L':
        lista_por_alf(ide, idp);
        break;

      case 'x':
        return 0;

    }

  }

  return -1;
}

void novo_produto(int idp)
{
  int i;
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[idp].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[idp].descricao[10 - 1] = '\0';
  produtos[idp].preco = new_sym_var(sizeof(int) * 8);
  produtos[idp].peso = new_sym_var(sizeof(int) * 8);
  produtos[idp].quantidade = new_sym_var(sizeof(int) * 8);
  for (i = 0; produtos[idp].descricao[i] != '\0'; i++)
    produtos[idp].descricao[i] = produtos[idp].descricao[i + 1];

  printf("Novo produto %d.\n", idp);
}

void adiciona_stock_produto(int numero_de_produtos)
{
  int idp;
  int quantidade;
  char S;
  idp = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(char) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (idp >= numero_de_produtos)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
  }
  else
  {
    produtos[idp].quantidade += quantidade;
  }

}

void nova_encomenda(int ide)
{
  printf("Nova encomenda %d.\n", ide);
}

int encomenda_peso(int ide, int numero_de_produtos)
{
  int idp;
  int peso = 0;
  for (idp = 0; idp < numero_de_produtos; idp++)
    peso += encomendas[ide][idp] * produtos[idp].peso;

  return peso;
}

void adiciona_produto_a_encomenda(int numero_de_encomendas, int numero_de_produtos)
{
  int ide;
  int idp;
  int quantidade;
  char S;
  ide = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(char) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(char) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (ide >= numero_de_encomendas)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp >= numero_de_produtos)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (quantidade > produtos[idp].quantidade)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if ((encomenda_peso(ide, numero_de_produtos) + (quantidade * produtos[idp].peso)) > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  encomendas[ide][idp] += quantidade;
  produtos[idp].quantidade -= quantidade;
}

void remove_stock_produto(int numero_de_produtos)
{
  int idp;
  int quantidade;
  char S;
  idp = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(char) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (idp >= numero_de_produtos)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  if (quantidade > produtos[idp].quantidade)
  {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    return;
  }
  else
  {
    
  }

  produtos[idp].quantidade -= quantidade;
}

void remove_produto_encomenda(int numero_de_encomendas, int numero_de_produtos)
{
  int idp;
  int ide;
  char S;
  ide = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(char) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= numero_de_encomendas)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  if (idp >= numero_de_produtos)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  else
  {
    
  }

  produtos[idp].quantidade += encomendas[ide][idp];
  encomendas[ide][idp] = 0;
}

void custo_encomenda(int numero_de_encomendas, int numero_de_produtos)
{
  int idp;
  int ide;
  int total = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= numero_de_encomendas)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (idp = 0; idp < numero_de_produtos; idp++)
    total += encomendas[ide][idp] * produtos[idp].preco;

  printf("Custo da encomenda %d %d.\n", ide, total);
}

void altera_preco(int numero_de_produtos)
{
  int idp;
  int preco;
  char S;
  idp = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(char) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idp >= numero_de_produtos)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else
  {
    produtos[idp].preco = preco;
  }

}

void lista_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos)
{
  int idp;
  int ide;
  char S;
  ide = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(char) * 8);
  idp = new_sym_var(sizeof(int) * 8);
  if (ide >= numero_de_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  if (idp >= numero_de_produtos)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  printf("%s %d.\n", produtos[idp].descricao, encomendas[ide][idp]);
}

void maximo_produto_numa_encomenda(int numero_de_encomendas, int numero_de_produtos)
{
  int idp;
  idp = new_sym_var(sizeof(int) * 8);
  if (idp >= numero_de_produtos)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  else
  {
    
  }

  if (numero_de_encomendas > 0)
  {
    int ide;
    int max_ide = 0;
    for (ide = 1; ide < numero_de_encomendas; ide++)
      if (encomendas[ide][idp] > encomendas[max_ide][idp])
    {
      max_ide = ide;
    }
    else
    {
      
    }


    if (encomendas[max_ide][idp] > 0)
    {
      printf("Maximo produto %d %d %d.\n", idp, max_ide, encomendas[max_ide][idp]);
    }
    else
    {
      
    }

  }
  else
  {
    
  }

}

void merge_por_preco(Produto produtos[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  Produto L[10000];
  Produto R[10000];
  for (i = 0; i < n1; i++)
    L[i] = produtos[l + i];

  for (j = 0; j < n2; j++)
    R[j] = produtos[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (L[i].preco <= R[j].preco)
    {
      produtos[k] = L[i];
      i++;
    }
    else
    {
      produtos[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    produtos[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    produtos[k] = R[j];
    j++;
    k++;
  }

}

void mergesort_por_preco(Produto produtos[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergesort_por_preco(produtos, l, m);
    mergesort_por_preco(produtos, m + 1, r);
    merge_por_preco(produtos, l, m, r);
  }
  else
  {
    
  }

}

void lista_por_preco(int numero_de_produtos)
{
  Produto produtos_aux[10000];
  int i;
  for (i = 0; i < numero_de_produtos; i++)
    produtos_aux[i] = produtos[i];

  mergesort_por_preco(produtos_aux, 0, numero_de_produtos - 1);
  printf("Produtos\n");
  for (i = 0; i < numero_de_produtos; i++)
    printf("* %s %d %d\n", produtos_aux[i].descricao, produtos_aux[i].preco, produtos_aux[i].quantidade);

}

void exch(Produto produtos[], int i, int j)
{
  Produto aux = produtos[i];
  produtos[i] = produtos[j];
  produtos[j] = aux;
}

int partition_por_alf(Produto produtos[], int left, int right)
{
  int i = left - 1;
  int j = right;
  char v[63];
  strcpy(v, produtos[right].descricao);
  while (i < j)
  {
    while (strcmp(produtos[++i].descricao, v) < 0)
      ;

    while (strcmp(v, produtos[--j].descricao) < 0)
      if (j == left)
    {
      break;
    }
    else
    {
      
    }


    if (i < j)
    {
      exch(produtos, i, j);
    }
    else
    {
      
    }

  }

  exch(produtos, i, right);
  return i;
}

void quicksort_por_alf(Produto produtos[], int left, int right)
{
  int i;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  i = partition_por_alf(produtos, left, right);
  quicksort_por_alf(produtos, left, i - 1);
  quicksort_por_alf(produtos, i + 1, right);
}

void lista_por_alf(int numero_de_encomendas, int numero_de_produtos)
{
  Produto produtos_aux[10000];
  int ide;
  int i;
  int numero_de_produtos_aux = 0;
  ide = new_sym_var(sizeof(int) * 8);
  if (ide >= numero_de_encomendas)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < numero_de_produtos; i++)
  {
    if (encomendas[ide][i] > 0)
    {
      strcpy(produtos_aux[numero_de_produtos_aux].descricao, produtos[i].descricao);
      produtos_aux[numero_de_produtos_aux].preco = produtos[i].preco;
      produtos_aux[numero_de_produtos_aux].quantidade = encomendas[ide][i];
      numero_de_produtos_aux++;
    }
    else
    {
      
    }

  }

  quicksort_por_alf(produtos_aux, 0, numero_de_produtos_aux - 1);
  printf("Encomenda %d\n", ide);
  for (i = 0; i < numero_de_produtos_aux; i++)
    printf("* %s %d %d\n", produtos_aux[i].descricao, produtos_aux[i].preco, produtos_aux[i].quantidade);

}

