/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


typedef struct relevo
{
  int indice;
  int identificador;
  int quantidade;
} relevo;
typedef struct encomendas
{
  int identificador;
  int peso;
  int preco;
  int n_produtos_encomendas;
  relevo products[200];
} encomendas;
typedef struct produtos
{
  int identificador;
  int preco;
  int peso;
  int n_encomendas_produtos;
  char descricao[63];
  int stock;
  relevo orders[500];
} produtos;
int n_produtos = 0;
int n_encomendas = 0;
int aux[10000] = {0};
produtos produto[10000] = {0};
encomendas encomenda[500] = {0};
void adicionar_produto()
{
  for (int produto_index = 0; produto_index < 10; produto_index++)
  {
    produto[n_produtos].descricao[produto_index] = new_sym_var(sizeof(char) * 8);
  }

  produto[n_produtos].descricao[10 - 1] = '\0';
  produto[n_produtos].preco = new_sym_var(sizeof(int) * 8);
  produto[n_produtos].peso = new_sym_var(sizeof(int) * 8);
  produto[n_produtos].stock = new_sym_var(sizeof(int) * 8);
  produto[n_produtos].identificador = 1;
  printf("Novo produto %d.\n", n_produtos);
  n_produtos++;
}

void adicionar_stock_produto()
{
  int procura;
  int quantidade;
  procura = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (produto[procura].identificador == 1)
  {
    produto[procura].stock += quantidade;
  }
  else
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", procura);
  }

}

void adicionar_encomenda()
{
  encomenda[n_encomendas].identificador = 1;
  encomenda[n_encomendas].peso = 0;
  encomenda[n_encomendas].preco = 0;
  printf("Nova encomenda %d.\n", n_encomendas);
  n_encomendas++;
}

void adicionar_produto_a_encomenda(int search, int procura, int quantidade)
{
  int aux = 0;
  int indicador;
  if (encomenda[search].identificador != 1)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", procura, search);
  }
  else
  {
    if (produto[procura].identificador != 1)
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", procura, search);
    }
    else
    {
      if (quantidade > produto[procura].stock)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", procura, search);
      }
      else
      {
        if ((encomenda[search].peso + (quantidade * produto[procura].peso)) > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", procura, search);
        }
        else
        {
          if (produto[procura].orders[search].identificador == 1)
          {
            for (indicador = 0; indicador < encomenda[search].n_produtos_encomendas; indicador++)
            {
              if (encomenda[search].products[indicador].indice == procura)
              {
                aux = indicador;
                break;
              }
              else
              {
                
              }

            }

            encomenda[search].products[aux].quantidade += quantidade;
            produto[procura].orders[search].quantidade += quantidade;
          }
          else
          {
            aux = encomenda[search].n_produtos_encomendas;
            encomenda[search].products[aux].indice = procura;
            encomenda[search].products[aux].quantidade += quantidade;
            encomenda[search].products[aux].identificador = 1;
            encomenda[search].n_produtos_encomendas++;
            produto[procura].n_encomendas_produtos++;
            produto[procura].orders[search].identificador = 1;
            produto[procura].orders[search].indice = search;
            produto[procura].orders[search].quantidade = quantidade;
          }

          encomenda[search].peso += quantidade * produto[procura].peso;
          encomenda[search].preco += quantidade * produto[procura].preco;
          produto[procura].stock -= quantidade;
        }

      }

    }

  }

}

void remove_stock_a_produto()
{
  int procura;
  int quantidade;
  procura = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  if (produto[procura].identificador != 1)
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", procura);
  }
  else
  {
    if (quantidade > produto[procura].stock)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, procura);
    }
    else
    {
      produto[procura].stock -= quantidade;
    }

  }

}

void remover_produto_da_encomenda(int search, int procura)
{
  int quantidade;
  int indicador = 0;
  int aux = 0;
  if (encomenda[search].identificador != 1)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", procura, search);
  }
  else
  {
    if (produto[procura].identificador != 1)
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", procura, search);
    }
    else
    {
      if (produto[procura].orders[search].identificador == 0)
      {
        ;
      }
      else
      {
        for (indicador = 0; indicador < encomenda[search].n_produtos_encomendas; indicador++)
        {
          if (encomenda[search].products[indicador].indice == procura)
          {
            aux = indicador;
            break;
          }
          else
          {
            
          }

        }

        quantidade = encomenda[search].products[aux].quantidade;
        for (; aux < encomenda[search].n_produtos_encomendas; aux++)
        {
          encomenda[search].products[aux].indice = encomenda[search].products[aux + 1].indice;
          encomenda[search].products[aux].quantidade = encomenda[search].products[aux + 1].quantidade;
        }

        encomenda[search].n_produtos_encomendas--;
        encomenda[search].preco -= quantidade * produto[procura].preco;
        encomenda[search].peso -= quantidade * produto[procura].peso;
        produto[procura].orders[search].identificador = 0;
        produto[procura].orders[search].quantidade = 0;
        produto[procura].n_encomendas_produtos--;
        produto[procura].stock += quantidade;
      }

    }

  }

}

void custo_encomenda()
{
  int search;
  search = new_sym_var(sizeof(int) * 8);
  if (encomenda[search].identificador != 1)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", search);
  }
  else
  {
    printf("Custo da encomenda %d %d.\n", search, encomenda[search].preco);
  }

}

void alterar_preco_produto()
{
  int procura;
  int preco;
  int indicador;
  int indicador2;
  procura = new_sym_var(sizeof(int) * 8);
  preco = new_sym_var(sizeof(int) * 8);
  if (produto[procura].identificador != 1)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", procura);
  }
  else
  {
    for (indicador = 0; indicador < n_encomendas; indicador++)
    {
      for (indicador2 = 0; indicador2 < encomenda[indicador].n_produtos_encomendas; indicador2++)
      {
        if (encomenda[indicador].products[indicador2].indice == procura)
        {
          encomenda[indicador].preco += (preco - produto[procura].preco) * encomenda[indicador].products[indicador2].quantidade;
        }
        else
        {
          
        }

      }

    }

    produto[procura].preco = preco;
  }

}

void listar_descricao_e_quantidade()
{
  int procura;
  int search;
  search = new_sym_var(sizeof(int) * 8);
  procura = new_sym_var(sizeof(int) * 8);
  if (produto[procura].identificador != 1)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", procura);
  }
  else
  {
    if (encomenda[search].identificador != 1)
    {
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", search);
    }
    else
    {
      printf("%s %d.\n", produto[procura].descricao, produto[procura].orders[search].quantidade);
    }

  }

}

void listar_maior_quantidade_produto()
{
  int procura;
  int maior_encomenda = 0;
  int maior_quantidade = 0;
  int indicador = 0;
  procura = new_sym_var(sizeof(int) * 8);
  if (produto[procura].identificador != 1)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", procura);
  }
  else
  {
    for (; indicador < n_encomendas; indicador++)
    {
      if ((produto[procura].orders[indicador].identificador == 1) && (produto[procura].orders[indicador].quantidade > maior_quantidade))
      {
        maior_encomenda = indicador;
        maior_quantidade = produto[procura].orders[indicador].quantidade;
      }
      else
      {
        
      }

    }

    if (maior_quantidade > 0)
    {
      printf("Maximo produto %d %d %d.\n", procura, maior_encomenda, maior_quantidade);
    }
    else
    {
      
    }

  }

}

void merge_l(int a[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
  {
    aux[i - 1] = a[i - 1];
  }

  for (j = m; j < right; j++)
  {
    aux[(right + m) - j] = a[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if ((produto[aux[j]].preco < produto[aux[i]].preco) || ((produto[aux[j]].preco == produto[aux[i]].preco) && (aux[j] < aux[i])))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void mergesort_l(int a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort_l(a, left, m);
  mergesort_l(a, m + 1, right);
  merge_l(a, left, m, right);
}

void merge_L(int a[], int left, int m, int right)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > left; i--)
  {
    aux[i - 1] = a[i - 1];
  }

  for (j = m; j < right; j++)
  {
    aux[(right + m) - j] = a[j + 1];
  }

  for (k = left; k <= right; k++)
  {
    if (strcmp(produto[aux[j]].descricao, produto[aux[i]].descricao) < 0)
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void mergesort_L(int a[], int left, int right)
{
  int m = (right + left) / 2;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  mergesort_L(a, left, m);
  mergesort_L(a, m + 1, right);
  merge_L(a, left, m, right);
}

void lista_por_preco()
{
  int vetor[10000] = {0};
  int i;
  int j = 0;
  int max;
  printf("Produtos\n");
  for (i = 0; i < n_produtos; i++, j++)
  {
    vetor[j] = i;
  }

  max = j - 1;
  mergesort_l(vetor, 0, max);
  for (i = 0; i < (max + 1); i++)
  {
    printf("* %s %d %d\n", produto[vetor[i]].descricao, produto[vetor[i]].preco, produto[vetor[i]].stock);
  }

}

void listar_ordem_alfabetica()
{
  int search;
  int max;
  int i;
  int j = 0;
  int vetor[200];
  search = new_sym_var(sizeof(int) * 8);
  if (encomenda[search].identificador == 0)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", search);
  }
  else
  {
    printf("Encomenda %d\n", search);
    for (i = 0; i < encomenda[search].n_produtos_encomendas; i++)
    {
      vetor[j] = encomenda[search].products[i].indice;
      j++;
    }

    max = j - 1;
    mergesort_L(vetor, 0, max);
    for (i = 0; i < (max + 1); i++)
    {
      printf("* %s %d %d\n", produto[vetor[i]].descricao, produto[vetor[i]].preco, produto[vetor[i]].orders[search].quantidade);
    }

  }

}

int main()
{
  char caracter;
  int ide;
  int idp;
  int quantity;
  do
  {
    switch (caracter = getchar())
    {
      case 'a':
        adicionar_produto();
        break;

      case 'q':
        adicionar_stock_produto();
        break;

      case 'N':
        adicionar_encomenda();
        break;

      case 'A':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        quantity = new_sym_var(sizeof(int) * 8);
        adicionar_produto_a_encomenda(ide, idp, quantity);
        break;

      case 'r':
        remove_stock_a_produto();
        break;

      case 'R':
        ide = new_sym_var(sizeof(int) * 8);
        idp = new_sym_var(sizeof(int) * 8);
        remover_produto_da_encomenda(ide, idp);
        break;

      case 'C':
        custo_encomenda();
        break;

      case 'p':
        alterar_preco_produto();
        break;

      case 'E':
        listar_descricao_e_quantidade();
        break;

      case 'm':
        listar_maior_quantidade_produto();
        break;

      case 'l':
        lista_por_preco();
        break;

      case 'L':
        listar_ordem_alfabetica();
        break;

      default:
        break;

    }

  }
  while (caracter != 'x');
  return 0;
}

