/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct ProdutoE
{
  int id;
  int quantidade;
  int peso;
  int z;
  int z1;
} ProdutoE;
typedef struct Produto
{
  char descricao[64];
  int preco;
  int peso;
  int quantidade;
} Produto;
typedef struct Encomenda
{
  int peso;
  int quantidade;
  ProdutoE produtos[200];
} Encomenda;
void funcao_a(Produto produtos[], int id)
{
  for (int produtos_index = 0; produtos_index < 10; produtos_index++)
  {
    produtos[id].descricao[produtos_index] = new_sym_var(sizeof(char) * 8);
  }

  produtos[id].descricao[10 - 1] = '\0';
  produtos[id].preco = new_sym_var(sizeof(int) * 8);
  produtos[id].peso = new_sym_var(sizeof(int) * 8);
  produtos[id].quantidade = new_sym_var(sizeof(int) * 8);
  printf("Novo produto %d.\n", id);
}

void funcao_q(Produto produtos[], int id)
{
  int quantidade = 0;
  int ip = 0;
  ip = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (ip >= id)
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", ip);
  }
  else
  {
    produtos[ip].quantidade += quantidade;
  }

}

int funcao_A(Produto produtos[], Encomenda encomendas[], int ide, int id)
{
  int ideP = 0;
  int idP = 0;
  int quantidade = 0;
  int q = 0;
  int i;
  ideP = new_sym_var(sizeof(int) * 8);
  idP = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (ideP >= ide)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idP, ideP);
    return 1;
  }
  else
  {
    if (idP >= id)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idP, ideP);
      return 1;
    }
    else
    {
      if (quantidade > produtos[idP].quantidade)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idP, ideP);
        return 1;
      }
      else
      {
        
      }

    }

  }

  encomendas[ideP].peso += quantidade * produtos[idP].peso;
  if (encomendas[ideP].peso > 200)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idP, ideP);
    encomendas[ideP].peso -= quantidade * produtos[idP].peso;
    return 1;
  }
  else
  {
    q = encomendas[ideP].quantidade;
    for (i = 0; i <= q; i++)
    {
      if ((encomendas[ideP].produtos[i].peso > 0) && (encomendas[ideP].produtos[i].id == idP))
      {
        encomendas[ideP].produtos[i].quantidade += quantidade;
        produtos[idP].quantidade -= quantidade;
        return 1;
      }
      else
      {
        
      }

    }

    encomendas[ideP].produtos[q].quantidade += quantidade;
    produtos[idP].quantidade -= quantidade;
    encomendas[ideP].produtos[q].id = idP;
    encomendas[ideP].produtos[q].peso = produtos[idP].peso;
    encomendas[ideP].quantidade += 1;
    return 1;
  }

}

int funcao_E(Encomenda encomendas[], Produto produtos[], int ide, int id)
{
  int ideP = 0;
  int idP = 0;
  int q = 0;
  int i;
  int ind = 0;
  ideP = new_sym_var(sizeof(int) * 8);
  idP = new_sym_var(sizeof(int) * 8);
  if (ideP >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ideP);
    return 1;
  }
  else
  {
    if (idP >= id)
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", idP);
      return 1;
    }
    else
    {
      q = encomendas[ideP].quantidade;
      for (i = 0; i < q; i++)
      {
        if ((ind = encomendas[ideP].produtos[i].id) == idP)
        {
          printf("%s %d.\n", produtos[ind].descricao, encomendas[ideP].produtos[i].quantidade);
          return 1;
        }
        else
        {
          
        }

      }

      printf("%s 0.\n", produtos[idP].descricao);
      return 1;
    }

  }

}

void funcao_r(Produto produtos[], int id)
{
  int idP;
  int quantidade;
  idP = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (idP >= id)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idP);
  }
  else
  {
    if (quantidade > produtos[idP].quantidade)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idP);
    }
    else
    {
      produtos[idP].quantidade -= quantidade;
    }

  }

}

void funcao_R(Encomenda encomendas[], int id, int ide, Produto produtos[])
{
  int ideP;
  int idP;
  int i;
  int q = 0;
  ideP = new_sym_var(sizeof(int) * 8);
  idP = new_sym_var(sizeof(int) * 8);
  if (ideP >= ide)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idP, ideP);
  }
  else
  {
    if (idP >= id)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idP, ideP);
    }
    else
    {
      q = encomendas[ideP].quantidade;
      for (i = 0; i < q; i++)
      {
        if (encomendas[ideP].produtos[i].id == idP)
        {
          produtos[idP].quantidade += encomendas[ideP].produtos[i].quantidade;
          encomendas[ideP].peso -= encomendas[ideP].produtos[i].quantidade * produtos[idP].peso;
          encomendas[ideP].produtos[i].quantidade = 0;
        }
        else
        {
          
        }

      }

    }

  }

}

void quicksort(int number[], int first, int last)
{
  int i;
  int j;
  int pivot;
  int temp;
  if (first < last)
  {
    pivot = first;
    i = first;
    j = last;
    while (i < j)
    {
      while ((number[i] <= number[pivot]) && (i < last))
        i++;

      while (number[j] > number[pivot])
        j--;

      if (i < j)
      {
        temp = number[i];
        number[i] = number[j];
        number[j] = temp;
      }
      else
      {
        
      }

    }

    temp = number[pivot];
    number[pivot] = number[j];
    number[j] = temp;
    quicksort(number, first, j - 1);
    quicksort(number, j + 1, last);
  }
  else
  {
    
  }

}

int removeDuplicates(int arr[], int n)
{
  int *temp;
  int j = 0;
  int i;
  temp = (int *) malloc(n * (sizeof(int)));
  if ((n == 0) || (n == 1))
  {
    return n;
  }
  else
  {
    
  }

  for (i = 0; i < (n - 1); i++)
  {
    if (arr[i] != arr[i + 1])
    {
      temp[j++] = arr[i];
    }
    else
    {
      
    }

  }

  temp[j++] = arr[n - 1];
  for (i = 0; i < j; i++)
  {
    arr[i] = temp[i];
  }

  return j;
}

void funcao_l(Produto produtos[], int id)
{
  int i;
  int i2;
  int s = 0;
  int *prod;
  prod = (int *) malloc(id * (sizeof(int)));
  for (i = 0; i < id; i++)
  {
    prod[i] = produtos[i].preco;
  }

  quicksort(prod, 0, id - 1);
  s = removeDuplicates(prod, id);
  printf("Produtos\n");
  for (i = 0; i < s; i++)
  {
    for (i2 = 0; i2 < id; i2++)
    {
      if (produtos[i2].preco == prod[i])
      {
        printf("* %s %d %d\n", produtos[i2].descricao, produtos[i2].preco, produtos[i2].quantidade);
      }
      else
      {
        
      }

    }

  }

}

void swap(char arr[200][64], int i, int l)
{
  char aux[64];
  strcpy(aux, arr[i]), strcpy(arr[i], arr[l]), strcpy(arr[l], aux);
}

void heapify(char arr[200][64], int n, int i)
{
  int largest = i;
  int l = (2 * i) + 1;
  int r = (2 * i) + 2;
  if ((l < n) && (strcmp(arr[l], arr[largest]) > 0))
  {
    largest = l;
  }
  else
  {
    
  }

  if ((r < n) && (strcmp(arr[r], arr[largest]) > 0))
  {
    largest = r;
  }
  else
  {
    
  }

  if (largest != i)
  {
    swap(arr, i, largest);
    heapify(arr, n, largest);
  }
  else
  {
    
  }

}

void heapSort(char arr[200][64], int n)
{
  int i;
  for (i = (n / 2) - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (i = n - 1; i > 0; i--)
  {
    swap(arr, 0, i);
    heapify(arr, i, 0);
  }

}

int funcao_L(Encomenda encomendas[], int ide, Produto produtos[])
{
  int ideP;
  int i;
  int i2;
  int r = 0;
  int c = 0;
  int ind = 0;
  char desc[200][64];
  ideP = new_sym_var(sizeof(int) * 8);
  if (ideP >= ide)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ideP);
    return 0;
  }
  else
  {
    
  }

  r = encomendas[ideP].quantidade;
  printf("Encomenda %d\n", ideP);
  for (i = 0; i < r; i++)
  {
    if (encomendas[ideP].produtos[i].quantidade > 0)
    {
      ind = encomendas[ideP].produtos[i].id;
      strcpy(desc[c], produtos[ind].descricao);
      c += 1;
    }
    else
    {
      
    }

  }

  heapSort(desc, c);
  for (i = 0; i < c; i++)
  {
    for (i2 = 0; i2 < r; i2++)
    {
      ind = encomendas[ideP].produtos[i2].id;
      if (strcmp(produtos[ind].descricao, desc[i]) == 0)
      {
        printf("* %s %d %d\n", desc[i], produtos[ind].preco, encomendas[ideP].produtos[i2].quantidade);
      }
      else
      {
        
      }

    }

  }

  return 0;
}

void funcao_C(Encomenda encomendas[], int ide, Produto produtos[])
{
  int ideP;
  int custo = 0;
  int i;
  int n = 0;
  int ind;
  ideP = new_sym_var(sizeof(int) * 8);
  if (ideP >= ide)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ideP);
  }
  else
  {
    n = encomendas[ideP].quantidade;
    for (i = 0; i < n; i++)
    {
      ind = encomendas[ideP].produtos[i].id;
      custo += encomendas[ideP].produtos[i].quantidade * produtos[ind].preco;
    }

    printf("Custo da encomenda %d %d.\n", ideP, custo);
  }

}

void funcao_p(Produto produtos[], int id)
{
  int idP;
  int preco;
  idP = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (idP >= id)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idP);
  }
  else
  {
    produtos[idP].preco = preco;
  }

}

void funcao_m(Encomenda encomendas[], int id, int ide)
{
  int i;
  int idP;
  int max = 0;
  int ind;
  int i2;
  int n;
  idP = new_sym_var(sizeof(int) * 8);
  if (idP >= id)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idP);
  }
  else
  {
    for (i = 0; i < ide; i++)
    {
      n = encomendas[i].quantidade;
      for (i2 = 0; i2 < n; i2++)
      {
        if ((encomendas[i].produtos[i2].id == idP) && (encomendas[i].produtos[i2].quantidade > max))
        {
          max = encomendas[i].produtos[i2].quantidade;
          ind = i;
        }
        else
        {
          
        }

      }

    }

    if (max > 0)
    {
      printf("Maximo produto %d %d %d.\n", idP, ind, max);
    }
    else
    {
      
    }

  }

}

int main()
{
  char c;
  int id = 0;
  int ide = 0;
  Produto produtos[10000];
  Encomenda encomendas[500];
  while (1)
  {
    c = new_sym_var(sizeof(char) * 8);
    if (c == 'a')
    {
      funcao_a(produtos, id);
      id += 1;
    }
    else
    {
      if (c == 'q')
      {
        funcao_q(produtos, id);
      }
      else
      {
        if (c == 'N')
        {
          ide++;
          printf("Nova encomenda %d.\n", ide - 1);
          encomendas[ide - 1].peso = 0;
          encomendas[ide - 1].quantidade = 0;
        }
        else
        {
          if (c == 'A')
          {
            funcao_A(produtos, encomendas, ide, id);
          }
          else
          {
            if (c == 'r')
            {
              funcao_r(produtos, id);
            }
            else
            {
              if (c == 'R')
              {
                funcao_R(encomendas, id, ide, produtos);
              }
              else
              {
                if (c == 'C')
                {
                  funcao_C(encomendas, ide, produtos);
                }
                else
                {
                  if (c == 'p')
                  {
                    funcao_p(produtos, id);
                  }
                  else
                  {
                    if (c == 'E')
                    {
                      funcao_E(encomendas, produtos, ide, id);
                    }
                    else
                    {
                      if (c == 'm')
                      {
                        funcao_m(encomendas, id, ide);
                      }
                      else
                      {
                        if (c == 'l')
                        {
                          funcao_l(produtos, id);
                        }
                        else
                        {
                          if (c == 'L')
                          {
                            funcao_L(encomendas, ide, produtos);
                          }
                          else
                          {
                            if (c == 'x')
                            {
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

            }

          }

        }

      }

    }

  }

  return 0;
}
