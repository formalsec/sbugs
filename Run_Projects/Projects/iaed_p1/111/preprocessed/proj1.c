/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>


struct __produto__
{
  char DES[64];
  int PR;
  int PESO;
  int STCK;
  int VALIDO;
};
struct __encomenda__
{
  int QTD[10000];
  int PESO;
};
struct __produto__ P[10000];
struct __encomenda__ E[500];
int P_ID = 0;
int E_ID = 0;
char C;
int IDE;
int IDP;
int QTD;
int PR;
int ID;
int A;
int B;
int i;
int N;
int M;
int TOTAL;
int OCORR_MAX;
int OCORR_MAXN;
void ordena(int OR[10000], int l, int r);
int menor_descricao(int CH, int l, int r, struct __produto__ PR[10000]);
int main()
{
  int O[10000];
  while ((C = getchar()) != EOF)
  {
    switch (C)
    {
      case 'a':
        if (P_ID < 10000)
      {
        for (int P_index = 0; P_index < 10; P_index++)
        {
          P[P_ID].DES[P_index] = new_sym_var(sizeof(char) * 8);
        }

        P[P_ID].DES[10 - 1] = '\0';
        P[P_ID].PR = new_sym_var(sizeof(int) * 8);
        P[P_ID].PESO = new_sym_var(sizeof(int) * 8);
        P[P_ID].STCK = new_sym_var(sizeof(int) * 8);
        P[P_ID].VALIDO = 0;
        printf("Novo produto %d.\n", P_ID++);
      }
      else
      {
        
      }

        continue;

      case 'q':
        IDP = new_sym_var(sizeof(int) * 8);
        QTD = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDP) && (IDP < P_ID))
      {
        P[IDP].STCK += QTD;
      }
      else
      {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", IDP);
      }

        continue;

      case 'N':
        if (E_ID < 500)
      {
        printf("Nova encomenda %d.\n", E_ID);
        ++E_ID;
        for (N = 0; N < 10000; ++N)
        {
          E[E_ID].QTD[N] = 0;
        }

        E[E_ID].PESO = 0;
      }
      else
      {
        
      }

        continue;

      case 'A':
        IDE = new_sym_var(sizeof(int) * 8);
        IDP = new_sym_var(sizeof(int) * 8);
        QTD = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDE) && (IDE < E_ID))
      {
        if ((0 <= IDP) && (IDP < P_ID))
        {
          if ((P[IDP].STCK - QTD) >= 0)
          {
            if ((E[IDE].PESO + (P[IDP].PESO * QTD)) <= 200)
            {
              E[IDE].QTD[IDP] += QTD;
              E[IDE].PESO += P[IDP].PESO * QTD;
              P[IDP].STCK = P[IDP].STCK - QTD;
            }
            else
            {
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", IDP, IDE);
            }

          }
          else
          {
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", IDP, IDE);
          }

        }
        else
        {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", IDP, IDE);
        }

      }
      else
      {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", IDP, IDE);
      }

        continue;

      case 'r':
        IDP = new_sym_var(sizeof(int) * 8);
        QTD = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDP) && (IDP < P_ID))
      {
        if ((P[IDP].STCK - QTD) >= 0)
        {
          P[IDP].STCK = P[IDP].STCK - QTD;
        }
        else
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", QTD, IDP);
        }

      }
      else
      {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", IDP);
      }

        continue;

      case 'R':
        IDE = new_sym_var(sizeof(int) * 8);
        IDP = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDE) && (IDE < E_ID))
      {
        if ((0 <= IDP) && (IDP < P_ID))
        {
          E[IDE].PESO = E[IDE].PESO - (P[IDP].PESO * E[IDE].QTD[IDP]);
          P[IDP].STCK += E[IDE].QTD[IDP];
          E[IDE].QTD[IDP] = 0;
        }
        else
        {
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", IDP, IDE);
        }

      }
      else
      {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", IDP, IDE);
      }

        continue;

      case 'C':
        TOTAL = 0;
        IDE = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDE) && (IDE < E_ID))
      {
        for (N = 0; N < P_ID; ++N)
        {
          TOTAL += E[IDE].QTD[N] * P[N].PR;
        }

        printf("Custo da encomenda %d %d.\n", IDE, TOTAL);
      }
      else
      {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", IDE);
      }

        continue;

      case 'p':
        IDP = new_sym_var(sizeof(int) * 8);
        PR = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDP) && (IDP < P_ID))
      {
        P[IDP].PR = PR;
      }
      else
      {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", IDP);
      }

        continue;

      case 'E':
        IDE = new_sym_var(sizeof(int) * 8);
        IDP = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDE) && (IDE < E_ID))
      {
        if ((0 <= IDP) && (IDP < P_ID))
        {
          printf("%s %d.\n", P[IDP].DES, E[IDE].QTD[IDP]);
        }
        else
        {
          printf("Impossivel listar produto %d. Produto inexistente.\n", IDP);
        }

      }
      else
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", IDE);
      }

        continue;

      case 'm':
        OCORR_MAX = -1;
        OCORR_MAXN = 0;
        IDP = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDP) && (IDP < P_ID))
      {
        for (N = 0; N <= E_ID; ++N)
        {
          if (E[N].QTD[IDP] > OCORR_MAX)
          {
            OCORR_MAX = E[N].QTD[IDP];
            OCORR_MAXN = N;
          }
          else
          {
            
          }

        }

        if ((E_ID != 0) && (OCORR_MAX > 0))
        {
          printf("Maximo produto %d %d %d.\n", IDP, OCORR_MAXN, OCORR_MAX);
        }
        else
        {
          
        }

      }
      else
      {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", IDP);
      }

        continue;

      case 'l':
        for (N = 0; N < P_ID; ++N)
      {
        O[N] = P[N].PR;
      }

        printf("Produtos\n");
        ordena(O, 0, N - 1);
        for (N = 0; N < P_ID; ++N)
      {
        for (M = 0; M < P_ID; ++M)
        {
          if ((O[N] == P[M].PR) && (P[M].VALIDO == 0))
          {
            printf("* %s %d %d\n", P[M].DES, P[M].PR, P[M].STCK);
            P[M].VALIDO = 1;
          }
          else
          {
            
          }

        }

      }

        for (N = 0; N < P_ID; ++N)
      {
        P[N].VALIDO = 0;
      }

        continue;

      case 'L':
        A = 0;
        B = 0;
        IDE = new_sym_var(sizeof(int) * 8);
        if ((0 <= IDE) && (IDE < E_ID))
      {
        for (N = 0; N < P_ID; ++N)
        {
          if (E[IDE].QTD[N] > 0)
          {
            O[A++] = P[N].DES[0];
          }
          else
          {
            
          }

        }

        printf("Encomenda %d\n", IDE);
        ordena(O, 0, A - 1);
        for (N = 0; N < A; ++N)
        {
          for (M = 0; M < A; ++M)
          {
            if ((O[N] == P[M].DES[0]) && (P[M].VALIDO == 0))
            {
              if (((O[N] == O[N + 1]) && (N < (A - 1))) || ((O[N] == O[N - 1]) && (N > 1)))
              {
                ID = menor_descricao(O[N], B, A, P);
                printf("* %s %d %d\n", P[ID].DES, P[ID].PR, E[IDE].QTD[ID]);
                P[ID].VALIDO = 1;
                ++B;
              }
              else
              {
                printf("* %s %d %d\n", P[M].DES, P[M].PR, E[IDE].QTD[M]);
                P[M].VALIDO = 1;
                B = 0;
              }

            }
            else
            {
              
            }

          }

        }

        for (N = 0; N < P_ID; ++N)
        {
          P[N].VALIDO = 0;
        }

      }
      else
      {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", IDE);
      }

        continue;

      case 'x':
        break;

    }

  }

  return 0;
}

void ordena(int OR[10000], int l, int r)
{
  int i;
  int j;
  for (i = l + 1; i <= r; ++i)
  {
    int v = OR[i];
    j = i - 1;
    while ((j >= l) && (OR[j] > v))
    {
      OR[j + 1] = OR[j];
      j--;
    }

    OR[j + 1] = v;
  }

}

int menor_descricao(int CH, int l, int r, struct __produto__ PR[10000])
{
  char V[10000][64];
  int Vi[10000];
  char A[64];
  int a = 0;
  int b = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  int nenhuma_troca = 1;
  for (i = 0; i < r; ++i)
  {
    if (PR[i].DES[0] == CH)
    {
      strcpy(V[b], PR[i].DES);
      Vi[b++] = i;
    }
    else
    {
      
    }

  }

  nenhuma_troca = 0;
  for (i = 0; i < (b - 1); ++i)
  {
    k = 1;
    if ((strlen(V[i]) < strlen(V[i + 1])) && (i < (64 - 1)))
    {
      k = (int) strlen(V[i]);
    }
    else
    {
      k = (int) strlen(V[i + 1]);
    }

    for (j = 1; j < k; ++j)
    {
      if (V[i][j] > V[i + 1][j])
      {
        strcpy(A, V[i]);
        strcpy(V[i], V[i + 1]);
        strcpy(V[i + 1], A);
        a = Vi[i];
        Vi[i] = Vi[i + 1];
        Vi[i + 1] = a;
        nenhuma_troca = 1;
      }
      else
      {
        
      }

    }

    if (nenhuma_troca == 0)
    {
      if ((((int) strlen(V[i + 1])) == k) && (((int) strlen(V[i])) != k))
      {
        strcpy(A, V[i]);
        strcpy(V[i], V[i + 1]);
        strcpy(V[i + 1], A);
        a = Vi[i];
        Vi[i] = Vi[i + 1];
        Vi[i + 1] = a;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  return Vi[l];
}

