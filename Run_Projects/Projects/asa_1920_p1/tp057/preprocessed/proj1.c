/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main()
{
  int n = 0;
  int m = 0;
  int i = 0;
  int j = 0;
  int copia = 0;
  int deixa = 1;
  int totalCopias = 0;
  int totalDeixas = 0;
  bool final = true;
  int checkiffor = 0;
  n = new_sym_var(sizeof(int) * 8);
  m = new_sym_var(sizeof(int) * 8);
  int alunos[n];
  int rel[m * 2];
  for (i = 0; i < n; ++i)
  {
    alunos[i] = new_sym_var(sizeof(int) * 8);
  }

  for (j = 0; j < m; ++j, copia += 2, deixa += 2)
  {
    rel[copia] = new_sym_var(sizeof(int) * 8);
    rel[deixa] = new_sym_var(sizeof(int) * 8);
    if ((rel[copia] > n) || (rel[deixa] > n))
    {
      exit(0);
    }
    else
    {
      
    }

  }

  totalCopias = (m * 2) - 2;
  totalDeixas = (m * 2) - 1;
  copia -= 2;
  deixa -= 2;
  for (i = 0; i < m; ++i, copia -= 2, deixa -= 2)
  {
    if (alunos[rel[copia] - 1] < alunos[rel[deixa] - 1])
    {
      alunos[rel[copia] - 1] = alunos[rel[deixa] - 1];
      checkiffor += 1;
    }
    else
    {
      
    }

  }

  while (final == true)
  {
    if (checkiffor != 0)
    {
      checkiffor = 0;
      copia = totalCopias;
      deixa = totalDeixas;
      for (i = 0; i < m; ++i, copia -= 2, deixa -= 2)
      {
        if (alunos[rel[copia] - 1] < alunos[rel[deixa] - 1])
        {
          alunos[rel[copia] - 1] = alunos[rel[deixa] - 1];
          checkiffor += 1;
        }
        else
        {
          
        }

      }

    }
    else
    {
      final = false;
    }

  }

  for (i = 0; i < n; ++i)
  {
    printf("%d\n", alunos[i]);
  }

  return 0;
}
