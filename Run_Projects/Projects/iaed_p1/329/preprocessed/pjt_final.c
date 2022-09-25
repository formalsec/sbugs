/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int TABELA[10000][4];
static int ENCOMENDA[500][10000 + 1];
static char TABELA_DESCRICAO[10000][63];
char descricao[63];
char resto[150];
char comando;
char palavra[63];
void merge(int arr[], int l, int m, int r, int identificacao)
{
  int n1;
  int n2;
  int *L;
  int *R;
  int i;
  int j;
  int k;
  n1 = (m - l) + 1;
  n2 = r - m;
  L = (int *) malloc(n1 * (sizeof(int)));
  R = (int *) malloc(n2 * (sizeof(int)));
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];

  for (j = 0; j < n2; j++)
    R[j] = arr[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (identificacao == 0)
    {
      if (TABELA[L[i]][1] <= TABELA[R[j]][1])
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
    else
    {
      if (identificacao == 1)
      {
        if (strcmp(TABELA_DESCRICAO[L[i]], TABELA_DESCRICAO[R[j]]) < 0)
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
      else
      {
        
      }

    }

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

  free(L);
  free(R);
}

void mergeSort(int arr[], int l, int r, int identificacao)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    mergeSort(arr, l, m, identificacao);
    mergeSort(arr, m + 1, r, identificacao);
    merge(arr, l, m, r, identificacao);
  }
  else
  {
    
  }

}

int calcula(int TABELA[10000][4], int ENCOMENDA[500][10001], int ide, int idp, int qnt)
{
  int s = 0;
  int i;
  for (i = 0; i < 10000; i++)
  {
    s = s + (ENCOMENDA[ide][i] * TABELA[i][2]);
  }

  s = s + (qnt * TABELA[idp][2]);
  return s;
}

void a(char resto[], char descricao[], int *preco, int *peso, int *qnt)
{
  int price;
  int weight;
  int qtty;
  for (int descricao_index = 0; descricao_index < 10; descricao_index++)
  {
    descricao[descricao_index] = new_sym_var(sizeof(char) * 8);
  }

  descricao[10 - 1] = '\0';
  price = new_sym_var(sizeof(int) * 8);
  weight = new_sym_var(sizeof(int) * 8);
  qtty = new_sym_var(sizeof(int) * 8);
  *preco = price;
  *peso = weight;
  *qnt = qtty;
}

void q(char resto[], int *idp, int *qnt)
{
  int id;
  int quantidade;
  id = new_sym_var(sizeof(int) * 8);
  quantidade = new_sym_var(sizeof(int) * 8);
  *idp = id;
  *qnt = quantidade;
}

void A(char resto[], int *ide, int *idp, int *qnt)
{
  int id_prod;
  int id_enc;
  int qtty;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  qtty = new_sym_var(sizeof(int) * 8);
  *ide = id_enc;
  *idp = id_prod;
  *qnt = qtty;
}

void R(char resto[], int *ide, int *idp)
{
  int id_prod;
  int id_enc;
  id_enc = new_sym_var(sizeof(int) * 8);
  id_prod = new_sym_var(sizeof(int) * 8);
  *ide = id_enc;
  *idp = id_prod;
}

void C(char resto[], int *ide)
{
  int id_enc;
  id_enc = new_sym_var(sizeof(int) * 8);
  *ide = id_enc;
}

void p(char resto[], int *idp, int *preco)
{
  int id_prod;
  int price;
  id_prod = new_sym_var(sizeof(int) * 8);
  price = new_sym_var(sizeof(int) * 8);
  *idp = id_prod;
  *preco = price;
}

int main()
{
  int preco = 0;
  int peso = 0;
  int qnt = 0;
  int ID = 0;
  int idp = 0;
  int IDE = 0;
  int ide = 0;
  for (int palavra_index = 0; palavra_index < 10; palavra_index++)
  {
    palavra[palavra_index] = new_sym_var(sizeof(char) * 8);
  }

  palavra[10 - 1] = '\0';
  comando = new_sym_var(sizeof(char) * 8);
  for (int resto_index = 0; resto_index < 10; resto_index++)
  {
    resto[resto_index] = new_sym_var(sizeof(char) * 8);
  }

  resto[10 - 1] = '\0';
  while (comando != 'x')
  {
    if (comando == 'a')
    {
      a(resto, descricao, &preco, &peso, &qnt);
      strcpy(TABELA_DESCRICAO[ID], descricao);
      TABELA[ID][0] = ID;
      TABELA[ID][1] = preco;
      TABELA[ID][2] = peso;
      TABELA[ID][3] = qnt;
      printf("Novo produto %d.\n", ID);
      ++ID;
    }
    else
    {
      
    }

    if (comando == 'q')
    {
      int variavel = 0;
      q(resto, &idp, &qnt);
      if (TABELA[idp][2] == 0)
      {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
      }
      else
      {
        variavel = TABELA[idp][3] + qnt;
        TABELA[idp][3] = variavel;
      }

    }
    else
    {
      
    }

    if (comando == 'N')
    {
      ENCOMENDA[IDE][10000] = 1;
      printf("Nova encomenda %d.\n", IDE);
      ++IDE;
    }
    else
    {
      
    }

    if (comando == 'A')
    {
      int variavel;
      int soma = 0;
      A(resto, &ide, &idp, &qnt);
      soma = calcula(TABELA, ENCOMENDA, ide, idp, qnt);
      if (ENCOMENDA[ide][10000] == 0)
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      }
      else
      {
        if (TABELA[idp][2] == 0)
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
          if (TABELA[idp][3] < qnt)
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          }
          else
          {
            if (soma > 200)
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
            {
              variavel = ENCOMENDA[ide][idp] + qnt;
              TABELA[idp][3] = TABELA[idp][3] - qnt;
              ENCOMENDA[ide][idp] = variavel;
            }

          }

        }

      }

    }
    else
    {
      
    }

    if (comando == 'r')
    {
      int variavel = 0;
      q(resto, &idp, &qnt);
      if (TABELA[idp][1] == 0)
      {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        if (TABELA[idp][3] < qnt)
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qnt, idp);
        }
        else
        {
          variavel = TABELA[idp][3] - qnt;
          TABELA[idp][3] = variavel;
        }

      }

    }
    else
    {
      
    }

    if (comando == 'R')
    {
      R(resto, &ide, &idp);
      if (ENCOMENDA[ide][10000] == 0)
      {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
      }
      else
      {
        if (TABELA[idp][2] == 0)
        {
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
          TABELA[idp][3] = TABELA[idp][3] + ENCOMENDA[ide][idp];
          ENCOMENDA[ide][idp] = 0;
        }

      }

    }
    else
    {
      
    }

    if (comando == 'C')
    {
      int i;
      int soma = 0;
      C(resto, &ide);
      if (ENCOMENDA[ide][10000] == 0)
      {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        for (i = 0; i < 10000; i++)
        {
          soma += ENCOMENDA[ide][i] * TABELA[i][1];
        }

        printf("Custo da encomenda %d %d.\n", ide, soma);
      }

    }
    else
    {
      
    }

    if (comando == 'p')
    {
      p(resto, &idp, &preco);
      if (TABELA[idp][2] != 0)
      {
        TABELA[idp][1] = preco;
      }
      else
      {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
      }

    }
    else
    {
      
    }

    if (comando == 'E')
    {
      R(resto, &ide, &idp);
      if (ENCOMENDA[ide][10000] == 0)
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        if (TABELA[idp][2] == 0)
        {
          printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
        else
        {
          printf("%s %d.\n", TABELA_DESCRICAO[idp], ENCOMENDA[ide][idp]);
        }

      }

    }
    else
    {
      
    }

    if (comando == 'm')
    {
      int i;
      int qtty = 0;
      C(resto, &ide);
      idp = ide;
      ide = 0;
      if ((TABELA[idp][0] == 0) && (TABELA[idp][2] == 0))
      {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
      }
      else
      {
        for (i = 0; i < 500; i++)
        {
          if (ENCOMENDA[i][idp] > qtty)
          {
            qtty = ENCOMENDA[i][idp];
            ide = i;
          }
          else
          {
            
          }

        }

        if (qtty > 0)
        {
          printf("Maximo produto %d %d %d.\n", idp, ide, qtty);
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

    if (comando == 'l')
    {
      int i;
      int j = 0;
      int identificacao = 0;
      static int nova_lista[10000];
      for (i = 0; i < (ID + 1); i++)
      {
        if (TABELA[i][2])
        {
          nova_lista[j] = i;
          ++j;
        }
        else
        {
          
        }

      }

      mergeSort(nova_lista, 0, j - 1, identificacao);
      printf("Produtos\n");
      for (i = 0; i < ID; i++)
      {
        if (TABELA[nova_lista[i]][2] > 0)
        {
          printf("* %s %d %d\n", TABELA_DESCRICAO[nova_lista[i]], TABELA[nova_lista[i]][1], TABELA[nova_lista[i]][3]);
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

    if (comando == 'L')
    {
      int i;
      int j = 0;
      int last_id = -1;
      int identificacao = 1;
      static int nova_lista[10000];
      C(resto, &ide);
      if (ENCOMENDA[ide][10000] == 0)
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
      }
      else
      {
        for (i = 0; i < (ID + 1); i++)
        {
          if (ENCOMENDA[ide][i])
          {
            nova_lista[j] = i;
            ++j;
          }
          else
          {
            
          }

        }

        mergeSort(nova_lista, 0, j - 1, identificacao);
        printf("Encomenda %d\n", ide);
        for (i = 0; i < j; i++)
        {
          if ((ENCOMENDA[ide][nova_lista[i]] && (nova_lista[i] != last_id)) && TABELA[nova_lista[i]][1])
          {
            printf("* %s %d %d\n", TABELA_DESCRICAO[nova_lista[i]], TABELA[nova_lista[i]][1], ENCOMENDA[ide][nova_lista[i]]);
            last_id = nova_lista[i];
          }
          else
          {
            
          }

        }

      }

    }
    else
    {
      
    }

    for (int palavra_index = 0; palavra_index < 10; palavra_index++)
    {
      palavra[palavra_index] = new_sym_var(sizeof(char) * 8);
    }

    palavra[10 - 1] = '\0';
    comando = new_sym_var(sizeof(char) * 8);
    for (int resto_index = 0; resto_index < 10; resto_index++)
    {
      resto[resto_index] = new_sym_var(sizeof(char) * 8);
    }

    resto[10 - 1] = '\0';
  }

  return 0;
}

