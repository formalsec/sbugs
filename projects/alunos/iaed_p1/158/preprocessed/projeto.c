#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void sistema_init();
void encomendas_init();
void produtos_init();
void adiciona_novo_produto();
void adiciona_stock();
void cria_encomenda();
void adiciona_produto_encomenda();
void remove_stock();
void remove_produto_encomenda();
void custo_encomenda();
void altera_preco();
void descri_quant_produto_encomenda();
void ide_produto_max();
void lista_produtos_sistema();
void lista_produtos_encomenda();
typedef struct produto
{
  int idp;
  char descri[64];
  int preco;
  int peso;
  int qtd;
} produto;
typedef struct encomenda
{
  int ide;
  produto produtos[200];
} encomenda;
int n_produtos;
int n_encomendas;
produto p;
encomenda e;
produto sistema[10000];
encomenda encomendas[500];
produto aux[10000];
void sistema_init()
{
  int i;
  for (i = 0; i < 10000; i++)
  {
    sistema[i].idp = -1;
  }

}

void encomendas_init()
{
  int i;
  for (i = 0; i < 500; i++)
  {
    encomendas[i].ide = -1;
  }

}

void produtos_init()
{
  int i;
  int j;
  for (i = 0; i < 500; i++)
  {
    for (j = 0; j < 200; j++)
    {
      encomendas[i].produtos[j].idp = -1;
    }

  }

}

void adiciona_novo_produto()
{
  int i = n_produtos - 1;
  sistema[i].idp = i;
  sistema[i].preco = p.preco;
  sistema[i].peso = p.peso;
  sistema[i].qtd = p.qtd;
  strcpy(sistema[i].descri, p.descri);
  printf("Novo produto %d.\n", i);
}

void adiciona_stock()
{
  if (sistema[p.idp].idp == (-1))
  {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p.idp);
  }
  else
  {
    sistema[p.idp].qtd += p.qtd;
  }

}

void cria_encomenda()
{
  int i = n_encomendas - 1;
  encomendas[i].ide = i;
  printf("Nova encomenda %d.\n", i);
}

void adiciona_produto_encomenda()
{
  int i;
  int k;
  int j;
  int peso_total = 0;
  int a = 0;
  if (encomendas[e.ide].ide == (-1))
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, e.ide);
  }
  else
  {
    if (sistema[p.idp].idp == (-1))
    {
      printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", p.idp, e.ide);
    }
    else
    {
      if ((sistema[p.idp].idp != (-1)) && (sistema[p.idp].qtd < p.qtd))
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", p.idp, e.ide);
      }
      else
      {
        for (i = 0; i < 200; i++)
        {
          if (encomendas[e.ide].produtos[i].idp != (-1))
          {
            peso_total += encomendas[e.ide].produtos[i].peso * encomendas[e.ide].produtos[i].qtd;
          }
          else
          {
            
          }

        }

        peso_total = peso_total + (p.qtd * sistema[p.idp].peso);
        if (peso_total > 200)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", p.idp, e.ide);
        }
        else
        {
          for (k = 0; k < 200; k++)
          {
            if (encomendas[e.ide].produtos[k].idp == p.idp)
            {
              encomendas[e.ide].produtos[k].qtd += p.qtd;
              a = 1;
            }
            else
            {
              
            }

          }

          if (a == 0)
          {
            for (j = 0; j < 200; j++)
            {
              if (encomendas[e.ide].produtos[j].idp == (-1))
              {
                encomendas[e.ide].produtos[j].idp = p.idp;
                encomendas[e.ide].produtos[j].qtd = p.qtd;
                strcpy(encomendas[e.ide].produtos[j].descri, sistema[p.idp].descri);
                encomendas[e.ide].produtos[j].peso = sistema[p.idp].peso;
                encomendas[e.ide].produtos[j].preco = sistema[p.idp].preco;
                break;
              }
              else
              {
                
              }

            }

          }
          else
          {
            
          }

          sistema[p.idp].qtd -= p.qtd;
        }

      }

    }

  }

}

void descri_quant_produto_encomenda()
{
  int i;
  int a = 0;
  if (encomendas[e.ide].ide == (-1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);
  }
  else
  {
    if (sistema[p.idp].idp == (-1))
    {
      printf("Impossivel listar produto %d. Produto inexistente.\n", p.idp);
    }
    else
    {
      for (i = 0; i < 200; i++)
      {
        if (encomendas[e.ide].produtos[i].idp == p.idp)
        {
          printf("%s %d.\n", sistema[p.idp].descri, encomendas[e.ide].produtos[i].qtd);
          a = 1;
          break;
        }
        else
        {
          
        }

      }

      if (a != 1)
      {
        printf("%s %d.\n", sistema[p.idp].descri, 0);
      }
      else
      {
        
      }

    }

  }

}

void custo_encomenda()
{
  int j;
  int custo_total = 0;
  if (encomendas[e.ide].ide == (-1))
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", e.ide);
  }
  else
  {
    for (j = 0; j < 200; j++)
    {
      if (encomendas[e.ide].produtos[j].idp != (-1))
      {
        custo_total += encomendas[e.ide].produtos[j].preco * encomendas[e.ide].produtos[j].qtd;
      }
      else
      {
        
      }

    }

    printf("Custo da encomenda %d %d.\n", e.ide, custo_total);
  }

}

void remove_stock()
{
  if (sistema[p.idp].idp == (-1))
  {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", p.idp);
  }
  else
  {
    if ((sistema[p.idp].qtd - p.qtd) < 0)
    {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", p.qtd, p.idp);
    }
    else
    {
      sistema[p.idp].qtd -= p.qtd;
    }

  }

}

void remove_produto_encomenda()
{
  int i;
  if (encomendas[e.ide].ide == (-1))
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", p.idp, e.ide);
  }
  else
  {
    if (sistema[p.idp].idp == (-1))
    {
      printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", p.idp, e.ide);
    }
    else
    {
      for (i = 0; i < 200; i++)
      {
        if (encomendas[e.ide].produtos[i].idp == p.idp)
        {
          encomendas[e.ide].produtos[i].idp = -1;
          sistema[p.idp].qtd += encomendas[e.ide].produtos[i].qtd;
        }
        else
        {
          
        }

      }

    }

  }

}

void altera_preco()
{
  int i;
  int j;
  if (sistema[p.idp].idp == (-1))
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", p.idp);
  }
  else
  {
    sistema[p.idp].preco = p.preco;
    for (i = 0; i < n_encomendas; i++)
    {
      for (j = 0; j < 200; j++)
      {
        if (encomendas[i].produtos[j].idp == p.idp)
        {
          encomendas[i].produtos[j].preco = p.preco;
        }
        else
        {
          
        }

      }

    }

  }

}

void ide_produto_max()
{
  int i;
  int j;
  int a = 0;
  int maior = 0;
  if (sistema[p.idp].idp == (-1))
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p.idp);
  }
  else
  {
    if (n_encomendas != 0)
    {
      for (i = 0; i < n_encomendas; i++)
      {
        for (j = 0; j < 200; j++)
        {
          if (encomendas[i].produtos[j].idp == p.idp)
          {
            a = 1;
            if (encomendas[i].produtos[j].qtd > maior)
            {
              maior = encomendas[i].produtos[j].qtd;
              e.ide = encomendas[i].ide;
            }
            else
            {
              
            }

            if ((encomendas[i].produtos[j].qtd == maior) && (e.ide > i))
            {
              maior = encomendas[i].produtos[j].qtd;
              e.ide = i;
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

      if (a == 1)
      {
        printf("Maximo produto %d %d %d.\n", p.idp, e.ide, maior);
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

void merge_preco(produto arr[], int l, int m, int r)
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
    L[i] = arr[l + i];
  }

  for (j = 0; j < n2; j++)
  {
    R[j] = arr[(m + 1) + j];
  }

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (L[i].preco <= R[j].preco)
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

}

void merge_descri(produto arr[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  produto L[200];
  produto R[200];
  for (i = 0; i < n1; i++)
  {
    L[i] = arr[l + i];
  }

  for (j = 0; j < n2; j++)
  {
    R[j] = arr[(m + 1) + j];
  }

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (strcmp(L[i].descri, R[j].descri) <= 0)
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

}

void mergeSort(produto arr[], int l, int r, int escolha)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort(arr, l, m, escolha);
    mergeSort(arr, m + 1, r, escolha);
    if (escolha == 1)
    {
      merge_preco(arr, l, m, r);
    }
    else
    {
      merge_descri(arr, l, m, r);
    }

  }
  else
  {
    
  }

}

void lista_produtos_sistema()
{
  int j;
  int i;
  for (j = 0; j < n_produtos; j++)
  {
    aux[j] = sistema[j];
  }

  mergeSort(aux, 0, n_produtos - 1, 1);
  printf("Produtos\n");
  for (i = 0; i < n_produtos; i++)
  {
    printf("* %s %d %d\n", aux[i].descri, aux[i].preco, aux[i].qtd);
  }

}

void lista_produtos_encomenda()
{
  int i;
  int j = 0;
  int n_p_encomenda = 0;
  produto a[200];
  if (encomendas[e.ide].ide == (-1))
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e.ide);
  }
  else
  {
    for (i = 0; i < 200; i++)
    {
      if (encomendas[e.ide].produtos[i].idp != (-1))
      {
        n_p_encomenda++;
        a[j] = encomendas[e.ide].produtos[i];
        j++;
      }
      else
      {
        
      }

    }

    mergeSort(a, 0, n_p_encomenda - 1, 0);
    printf("Encomenda %d\n", e.ide);
    for (i = 0; i < n_p_encomenda; i++)
    {
      printf("* %s %d %d\n", a[i].descri, a[i].preco, a[i].qtd);
    }

  }

}

int main()
{
  char comando;
  sistema_init();
  encomendas_init();
  produtos_init();
  while ((comando = getchar()) != EOF)
  {
    switch (comando)
    {
      case 'a':
        n_produtos += 1;
        for (int p_index = 0; p_index < 10; p_index++)
      {
        p.descri[p_index] = new_sym_var(sizeof(char) * 8);
      }

        p.descri[10 - 1] = '\0';
        p.preco = new_sym_var(sizeof(int) * 8);
        p.peso = new_sym_var(sizeof(int) * 8);
        p.qtd = new_sym_var(sizeof(int) * 8);
        adiciona_novo_produto();
        break;

      case 'q':
        p.idp = new_sym_var(sizeof(int) * 8);
        p.qtd = new_sym_var(sizeof(int) * 8);
        adiciona_stock();
        break;

      case 'N':
        n_encomendas += 1;
        cria_encomenda();
        break;

      case 'A':
        e.ide = new_sym_var(sizeof(int) * 8);
        p.idp = new_sym_var(sizeof(int) * 8);
        p.qtd = new_sym_var(sizeof(int) * 8);
        adiciona_produto_encomenda();
        break;

      case 'r':
        p.idp = new_sym_var(sizeof(int) * 8);
        p.qtd = new_sym_var(sizeof(int) * 8);
        remove_stock();
        break;

      case 'R':
        e.ide = new_sym_var(sizeof(int) * 8);
        p.idp = new_sym_var(sizeof(int) * 8);
        remove_produto_encomenda();
        break;

      case 'C':
        e.ide = new_sym_var(sizeof(int) * 8);
        custo_encomenda();
        break;

      case 'p':
        p.idp = new_sym_var(sizeof(int) * 8);
        p.preco = new_sym_var(sizeof(int) * 8);
        altera_preco();
        break;

      case 'E':
        e.ide = new_sym_var(sizeof(int) * 8);
        p.idp = new_sym_var(sizeof(int) * 8);
        descri_quant_produto_encomenda();
        break;

      case 'm':
        p.idp = new_sym_var(sizeof(int) * 8);
        ide_produto_max();
        break;

      case 'l':
        lista_produtos_sistema();
        break;

      case 'L':
        e.ide = new_sym_var(sizeof(int) * 8);
        lista_produtos_encomenda();
        break;

      case 'x':
        return 0;

      default:
        printf("Comando invalido!");
        return 1;

    }

    getchar();
  }

  return 0;
}

