/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


int nAlunos;
int nAmizades;
typedef struct Aluno
{
  int indice_aluno;
  int nota;
  int b_visited;
  int n_de_amigos;
  struct Aluno *anterior;
  struct Aluno **amigos;
} aluno;
aluno *alunos;
aluno *proximo;
void escreveNotas()
{
  int i;
  for (i = 0; i < nAlunos; i++)
  {
    printf("%d\n", alunos[i].nota);
  }

}

void DFS_Alg(int indice)
{
  int i;
  int j;
  alunos[indice].b_visited = 1;
  for (i = 0; i < alunos[indice].n_de_amigos; i++)
  {
    if (alunos[indice].amigos[i] != 0)
    {
      if (alunos[indice].amigos[i]->b_visited == 0)
      {
        proximo = alunos[indice].amigos[i];
        alunos[indice].amigos[i] = 0;
        break;
      }
      else
      {
        if (alunos[indice].amigos[i]->nota > alunos[indice].nota)
        {
          alunos[indice].nota = alunos[indice].amigos[i]->nota;
        }
        else
        {
          
        }

        alunos[indice].amigos[i] = 0;
      }

    }
    else
    {
      
    }

  }

  if (i == alunos[indice].n_de_amigos)
  {
    if (alunos[indice].anterior == 0)
    {
      for (j = 0; j < nAlunos; j++)
      {
        if ((alunos[j].b_visited == 0) && (alunos[j].amigos[0] != 0))
        {
          break;
        }
        else
        {
          
        }

      }

      if (j == nAlunos)
      {
        escreveNotas();
        return;
      }
      else
      {
        alunos[j].anterior = 0;
        DFS_Alg(alunos[j].indice_aluno - 1);
      }

    }
    else
    {
      if (alunos[indice].nota > alunos[indice].anterior->nota)
      {
        alunos[indice].anterior->nota = alunos[indice].nota;
      }
      else
      {
        
      }

      DFS_Alg(alunos[indice].anterior->indice_aluno - 1);
    }

  }
  else
  {
    proximo->anterior = &alunos[indice];
    DFS_Alg(proximo->indice_aluno - 1);
  }

}

int main()
{
  int i = 0;
  int j = 0;
  int k = 0;
  int h = 0;
  int Prev_Student;
  int student = -1;
  int friend;
  nAlunos = new_sym_var(sizeof(int) * 8);
  nAmizades = new_sym_var(sizeof(int) * 8);
  alunos = (aluno *) malloc((sizeof(aluno)) * nAlunos);
  proximo = malloc(sizeof(aluno));
  while (h < nAlunos)
  {
    alunos[h].indice_aluno = 0;
    alunos[h].nota = 0;
    alunos[h].amigos = (aluno **) malloc(sizeof(aluno *));
    alunos[h].amigos[0] = 0;
    alunos[h].n_de_amigos = 0;
    alunos[h].anterior = malloc(sizeof(aluno));
    alunos[h].b_visited = 0;
    h++;
  }

  alunos[0].anterior = 0;
  while (i < nAlunos)
  {
    alunos[i].nota = new_sym_var(sizeof(int) * 8);
    alunos[i].indice_aluno = i + 1;
    i++;
  }

  while (j < nAmizades)
  {
    Prev_Student = student;
    student = new_sym_var(sizeof(int) * 8);
    friend = new_sym_var(sizeof(int) * 8);
    student--;
    friend--;
    if (Prev_Student == student)
    {
      k++;
    }
    else
    {
      k = 0;
    }

    alunos[student].amigos = (aluno **) realloc(alunos[student].amigos, (sizeof(aluno *)) * (k + 1));
    alunos[student].amigos[k] = &alunos[friend];
    alunos[student].n_de_amigos++;
    j++;
  }

  DFS_Alg(0);
  return 0;
}

