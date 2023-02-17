#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <wasp.h>
typedef struct match *match;
struct match
{
  int i;
  int j;
};
int readSeq(int **P)
{
  int n = 0;
  int a = 4;
  int c;
  *P = malloc(a * (sizeof(int)));
  c = ' ';
  while (((-1) != c) && ('\n' != c))
  {
    (*P)[n] = __WASP_symb_int("i");
    scanf("%d", &(*P)[n]);
    c = getchar();
    n++;
    if (a == (n + 1))
    {
      a *= 2;
      *P = realloc(*P, a * (sizeof(int)));
    }
  }

  (*P)[n] = 2147483647;
  n++;
  return n;
}

struct stackItem
{
  int v;
  int c;
};
typedef struct stack *stack;
struct stack
{
  int t;
  int a;
  struct stackItem *S;
};
stack newS()
{
  stack I = (void *) 0;
  I = malloc(sizeof(struct stack));
  I->a = 4;
  I->t = 0;
  I->S = malloc((sizeof(struct stackItem)) * I->a);
  I->S[0].v = 2147483647;
  I->S[0].c = 0;
  return I;
}

void freeS(stack I)
{
  free(I->S);
  I->S = (void *) 0;
  free(I);
}

struct stackItem *top(stack I)
{
  return &I->S[I->t];
}

void pump(stack I)
{
  I->t++;
  if (I->a == I->t)
  {
    I->a *= 2;
    I->S = realloc(I->S, (sizeof(struct stackItem)) * I->a);
  }
}

int topBSearch(stack *A, int n, int v)
{
  int m;
  int a = 0;
  int b = n;
  while ((1 + a) < b)
  {
    m = b + a;
    m /= 2;
    if (top(A[m])->v > v)
      b = m;
    else
      a = m;
  }

  if (top(A[a])->v < v)
    a++;
  return a;
}

int stackBSearch(stack S, int v)
{
  int m;
  int a = 0;
  int b = 1 + S->t;
  while ((1 + a) < b)
  {
    m = b + a;
    m /= 2;
    if (S->S[m].v < v)
      b = m;
    else
      a = m;
  }

  return S->S[a].c;
}

int main()
{
  stack *A;
  int *D;
  int *DC;
  int c;
  int n;
  int *X;
  int i;
  int j;
  int *Y;
  int k;
  int a;
  match M;
  int m;
  c = __WASP_symb_int("c");
  getchar();
  n = readSeq(&X);
  switch (c)
  {
    case 1:
      n--;
      A = (stack *) calloc(n + 1, sizeof(stack));
      A[0] = newS();
      pump(A[0]);
      top(A[0])->v = -2147483648;
      top(A[0])->c = 1;
      j = 1;
      for (i = 0; i < n; i++)
    {
      k = topBSearch(A, j, X[i]);
      if (j == k)
      {
        A[j] = newS();
        j++;
      }
      int count = top(A[k])->c;
      pump(A[k]);
      top(A[k])->v = X[i];
      top(A[k])->c = count;
      top(A[k])->c += top(A[k - 1])->c;
      top(A[k])->c -= stackBSearch(A[k - 1], X[i]);
    }

      j--;
      printf("%d ", j);
      printf("%d\n", top(A[j])->c);
      for (i = 0; i <= j; i++)
      freeS(A[i]);

      free(A);
      break;

    case 2:
      k = readSeq(&Y);
      a = 4;
      M = malloc(a * (sizeof(struct match)));
      m = 0;
      for (i = 0; i < n; i++)
    {
      for (j = 0; j < k; j++)
      {
        if (X[i] == Y[j])
        {
          M[m].i = i;
          M[m].j = j;
          m++;
          if (a == m)
          {
            a *= 2;
            M = realloc(M, a * (sizeof(struct match)));
          }
        }
      }

    }

      free(Y);
      D = malloc(m * (sizeof(int)));
      DC = malloc(m * (sizeof(int)));
      for (i = 0; i < m; i++)
    {
      D[i] = 1;
      DC[i] = 1;
      for (j = 0; j < i; j++)
      {
        if (((M[j].j < M[i].j) && (X[M[j].i] < X[M[i].i])) && (D[i] < (D[j] + 1)))
        {
          D[i] = D[j] + 1;
          DC[i] = 0;
        }
      }

      for (j = 0; j < i; j++)
      {
        if (((M[j].j < M[i].j) && (X[M[j].i] < X[M[i].i])) && (D[i] == (D[j] + 1)))
        {
          DC[i] += DC[j];
        }
      }

    }

      printf("%d\n", D[m - 1] - 1);
      free(D);
      free(DC);
      free(M);
      break;

  }

  free(X);
  return 0;
}
