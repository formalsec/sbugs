/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct produto
{
  char desc[63 + 1];
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct encomenda
{
  int prodc;
  int peso;
  int idp[200];
  int qtd[200];
} encomenda;
char comando;
char desc[63 + 1];
int arg1;
int arg2;
int arg3;
int prodc = 0;
produto produtos[10000];
int produtos_sorted_preco[10000];
int sorted_preco_count;
int produtos_sorted_desc[10000];
encomenda encomendas[500];
int encc = 0;
void adiciona_prod(char *desc, int preco, int peso, int qtd);
void altera_qtd_prd(int idp, int qtd);
void nova_encomenda();
void adiciona_prod_enc(int ide, int idp, int qtd);
void remove_prod_enc(int ide, int idp);
void obter_custo_enc(int ide);
void altera_preco_prd(int idp, int preco);
void list_prd_enc(int ide, int idp);
void maximo_produto(int idp);
void list_produtos();
void list_encomenda(int ide);
int linear_search(int arr[], int left, int right, int x);
void merge_prd_preco(int arr[], int l, int m, int r);
void mergeSort_prd_preco(int arr[], int l, int r);
int binarySearch(int arr[], int left, int right, int x);
int qtd_prd_enc(int ide, int idp);
int main()
{
  while (1)
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        for (int desc_index = 0; desc_index < (63 + 1); desc_index++)
      {
        desc[desc_index] = new_sym_var(sizeof(char) * 8);
      }

        desc[(63 + 1) - 1] = '\0';
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        adiciona_prod(desc, arg1, arg2, arg3);
        break;

      case 'q':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        altera_qtd_prd(arg1, arg2);
        break;

      case 'N':
        nova_encomenda();
        break;

      case 'A':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        arg3 = new_sym_var(sizeof(int) * 8);
        adiciona_prod_enc(arg1, arg2, arg3);
        break;

      case 'r':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        altera_qtd_prd(arg1, -arg2);
        break;

      case 'R':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        remove_prod_enc(arg1, arg2);
        break;

      case 'C':
        arg1 = new_sym_var(sizeof(int) * 8);
        obter_custo_enc(arg1);
        break;

      case 'p':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        altera_preco_prd(arg1, arg2);
        break;

      case 'E':
        arg1 = new_sym_var(sizeof(int) * 8);
        arg2 = new_sym_var(sizeof(int) * 8);
        list_prd_enc(arg1, arg2);
        break;

      case 'm':
        arg1 = new_sym_var(sizeof(int) * 8);
        maximo_produto(arg1);
        break;

      case 'l':
        list_produtos();
        break;

      case 'L':
        arg1 = new_sym_var(sizeof(int) * 8);
        list_encomenda(arg1);
        break;

      case 'x':
        return 0;

    }

  }

}

void adiciona_prod(char *desc, int preco, int peso, int qtd)
{
  int i = prodc;
  strcpy(produtos[prodc].desc, desc);
  produtos[prodc].preco = preco;
  produtos[prodc].peso = peso;
  produtos[prodc].qtd = qtd;
  produtos_sorted_preco[prodc] = prodc;
  while ((strcmp(desc, produtos[produtos_sorted_desc[i - 1]].desc) < 0) && (i > 0))
  {
    produtos_sorted_desc[i] = produtos_sorted_desc[i - 1];
    i--;
  }

  produtos_sorted_desc[i] = prodc;
  printf("Novo produto %d.\n", prodc);
  prodc++;
  return;
}

void altera_qtd_prd(int idp, int qtd)
{
  if (idp >= prodc)
  {
    {
      if (qtd > 0)
      {
        {
          printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        }
      }
      else
      {
        {
          printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
          return;
        }
      }

    }
  }
  else
  {
    
  }

  if ((qtd < 0) && ((-qtd) > produtos[idp].qtd))
  {
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", -qtd, idp);
      return;
    }
  }
  else
  {
    
  }

  produtos[idp].qtd += qtd;
  return;
}

void nova_encomenda()
{
  encomendas[encc].prodc = 0;
  encomendas[encc].peso = 0;
  printf("Nova encomenda %d.\n", encc);
  encc++;
  return;
}

void adiciona_prod_enc(int ide, int idp, int qtd)
{
  int i;
  if (ide >= encc)
  {
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    if (idp >= prodc)
    {
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
      }
    }
    else
    {
      if (produtos[idp].qtd < qtd)
      {
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          return;
        }
      }
      else
      {
        if ((encomendas[ide].peso + (qtd * produtos[idp].peso)) > 200)
        {
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %i.\n", idp, ide, 200);
            return;
          }
        }
        else
        {
          
        }

      }

    }

  }

  i = binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc - 1, idp);
  altera_qtd_prd(idp, -qtd);
  encomendas[ide].peso += qtd * produtos[idp].peso;
  if (i == (-1))
  {
    {
      encomendas[ide].idp[encomendas[ide].prodc] = idp;
      encomendas[ide].qtd[encomendas[ide].prodc] = qtd;
      i = encomendas[ide].prodc;
      while ((encomendas[ide].idp[i - 1] > idp) && (i > 0))
      {
        encomendas[ide].idp[i] = encomendas[ide].idp[i - 1];
        encomendas[ide].qtd[i] = encomendas[ide].qtd[i - 1];
        i--;
      }

      encomendas[ide].idp[i] = idp;
      encomendas[ide].qtd[i] = qtd;
      encomendas[ide].prodc++;
      return;
    }
  }
  else
  {
    
  }

  encomendas[ide].qtd[i] += qtd;
  return;
}

void remove_prod_enc(int ide, int idp)
{
  int i;
  int j;
  if (ide >= encc)
  {
    {
      printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      return;
    }
  }
  else
  {
    if (idp >= prodc)
    {
      {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
      }
    }
    else
    {
      
    }

  }

  i = binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc - 1, idp);
  if (i != (-1))
  {
    {
      altera_qtd_prd(idp, encomendas[ide].qtd[i]);
      encomendas[ide].peso -= encomendas[ide].qtd[i] * produtos[idp].peso;
      for (j = i; j < encomendas[ide].prodc; j++)
      {
        encomendas[ide].idp[j] = encomendas[ide].idp[j + 1];
        encomendas[ide].qtd[j] = encomendas[ide].qtd[j + 1];
      }

      encomendas[ide].prodc--;
    }
  }
  else
  {
    
  }

  return;
}

void obter_custo_enc(int ide)
{
  int i;
  int total = 0;
  if (ide >= encc)
  {
    {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < encomendas[ide].prodc; i++)
  {
    total += produtos[encomendas[ide].idp[i]].preco * encomendas[ide].qtd[i];
  }

  printf("Custo da encomenda %d %d.\n", ide, total);
  return;
}

void altera_preco_prd(int idp, int preco)
{
  int i;
  if (idp >= prodc)
  {
    {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  i = linear_search(produtos_sorted_preco, 0, sorted_preco_count - 1, idp);
  if (i != (-1))
  {
    {
      while (i < sorted_preco_count)
      {
        produtos_sorted_preco[i] = produtos_sorted_preco[i + 1];
        i++;
      }

      sorted_preco_count--;
      produtos_sorted_preco[sorted_preco_count] = idp;
    }
  }
  else
  {
    
  }

  produtos[idp].preco = preco;
  return;
}

void list_prd_enc(int ide, int idp)
{
  if (ide >= encc)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    if (idp >= prodc)
    {
      {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
      }
    }
    else
    {
      
    }

  }

  printf("%s %d.\n", produtos[idp].desc, qtd_prd_enc(ide, idp));
  return;
}

void maximo_produto(int idp)
{
  int i;
  int qtd;
  int max_qtd = 0;
  int max_ide;
  if (idp >= prodc)
  {
    {
      printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < encc; i++)
  {
    qtd = qtd_prd_enc(i, idp);
    if (qtd > max_qtd)
    {
      {
        max_qtd = qtd;
        max_ide = i;
      }
    }
    else
    {
      
    }

  }

  if (max_qtd != 0)
  {
    {
      printf("Maximo produto %d %d %d.\n", idp, max_ide, max_qtd);
    }
  }
  else
  {
    
  }

  return;
}

void list_produtos()
{
  int i;
  mergeSort_prd_preco(produtos_sorted_preco, sorted_preco_count, prodc - 1);
  merge_prd_preco(produtos_sorted_preco, 0, sorted_preco_count - 1, prodc - 1);
  sorted_preco_count = prodc;
  printf("Produtos\n");
  for (i = 0; i < prodc; i++)
  {
    printf("* %s %d %d\n", produtos[produtos_sorted_preco[i]].desc, produtos[produtos_sorted_preco[i]].preco, produtos[produtos_sorted_preco[i]].qtd);
  }

  return;
}

void list_encomenda(int ide)
{
  int i;
  int printed_count = 0;
  if (ide >= encc)
  {
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      return;
    }
  }
  else
  {
    
  }

  printf("Encomenda %d\n", ide);
  for (i = 0; (i < prodc) && (printed_count < encomendas[ide].prodc); i++)
  {
    if (binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc, produtos_sorted_desc[i]) != (-1))
    {
      {
        printf("* %s %d %d\n", produtos[produtos_sorted_desc[i]].desc, produtos[produtos_sorted_desc[i]].preco, qtd_prd_enc(ide, produtos_sorted_desc[i]));
        printed_count++;
      }
    }
    else
    {
      
    }

  }

  return;
}

int linear_search(int arr[], int left, int right, int x)
{
  int i;
  for (i = left; i <= right; i++)
  {
    if (arr[i] == x)
    {
      {
        return i;
      }
    }
    else
    {
      
    }

  }

  return -1;
}

void merge_prd_preco(int arr[], int left, int m, int right)
{
  int aux[10000];
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
  {
    aux[i - 1] = arr[i - 1];
  }

  for (j = m; j < right; j++)
  {
    aux[(right + m) - j] = arr[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if (produtos[aux[j]].preco < produtos[aux[i]].preco)
    {
      {
        arr[k] = aux[j--];
      }
    }
    else
    {
      if (produtos[aux[j]].preco > produtos[aux[i]].preco)
      {
        {
          arr[k] = aux[i++];
        }
      }
      else
      {
        if (aux[i] < aux[j])
        {
          {
            arr[k] = aux[i++];
          }
        }
        else
        {
          {
            arr[k] = aux[j--];
          }
        }

      }

    }

  }

  return;
}

void mergeSort_prd_preco(int arr[], int left, int right)
{
  if (left < right)
  {
    {
      int m = left + ((right - left) / 2);
      mergeSort_prd_preco(arr, left, m);
      mergeSort_prd_preco(arr, m + 1, right);
      merge_prd_preco(arr, left, m, right);
    }
  }
  else
  {
    
  }

  return;
}

int binarySearch(int arr[], int left, int right, int x)
{
  if (right >= left)
  {
    {
      int mid = left + ((right - left) / 2);
      if (arr[mid] == x)
      {
        return mid;
      }
      else
      {
        
      }

      if (arr[mid] < x)
      {
        return binarySearch(arr, mid + 1, right, x);
      }
      else
      {
        
      }

      return binarySearch(arr, left, mid - 1, x);
    }
  }
  else
  {
    
  }

  return -1;
}

int qtd_prd_enc(int ide, int idp)
{
  int i = binarySearch(encomendas[ide].idp, 0, encomendas[ide].prodc - 1, idp);
  if (i != (-1))
  {
    {
      return encomendas[ide].qtd[i];
    }
  }
  else
  {
    
  }

  return 0;
}

