#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int M = 59;
struct jogo **tabela;
struct jogo **hashjogos;
struct equipa **hashequipa;
int n = 0;
int linha = 0;
struct jogo
{
  char *nomeJogo;
  char *nomeEquipa1;
  char *nomeEquipa2;
  int r1;
  int r2;
  struct jogo *anterior;
  struct jogo *posterior;
};
struct equipa
{
  int n_vitorias;
  char *nomeequipa;
  struct equipa *anterior;
  struct equipa *posterior;
};
int hash(char *v)
{
  int h;
  int a = 314;
  int b = 271;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

void StInitEquipa()
{
  int i;
  hashequipa = malloc(M * (sizeof(struct equipa)));
  for (i = 0; i < M; i++)
  {
    hashequipa[i] = 0;
  }

}

void StInitJogo()
{
  int i;
  hashjogos = malloc(M * (sizeof(struct jogo)));
  for (i = 0; i < M; i++)
  {
    hashjogos[i] = 0;
  }

}

struct equipa *cria_equipa(char *nomeequipa)
{
  struct equipa *equipaAuxiliar = malloc(sizeof(struct equipa));
  equipaAuxiliar->nomeequipa = malloc(((sizeof(char)) * strlen(nomeequipa)) + 1);
  equipaAuxiliar->n_vitorias = 0;
  strcpy(equipaAuxiliar->nomeequipa, nomeequipa);
  return equipaAuxiliar;
}

struct jogo *cria_jogo(char *nomeJogo, char *nomeEquipa1, char *nomeEquipa2, int r1, int r2)
{
  struct jogo *jogoAuxiliar = malloc(sizeof(struct jogo));
  jogoAuxiliar->nomeJogo = malloc(((sizeof(char)) * strlen(nomeJogo)) + 1);
  strcpy(jogoAuxiliar->nomeJogo, nomeJogo);
  jogoAuxiliar->nomeEquipa1 = malloc(((sizeof(char)) * strlen(nomeEquipa1)) + 1);
  strcpy(jogoAuxiliar->nomeEquipa1, nomeEquipa1);
  jogoAuxiliar->nomeEquipa2 = malloc(((sizeof(char)) * strlen(nomeEquipa2)) + 1);
  strcpy(jogoAuxiliar->nomeEquipa2, nomeEquipa2);
  jogoAuxiliar->r1 = r1;
  jogoAuxiliar->r2 = r2;
  return jogoAuxiliar;
}

void equipa_ganhou(char *nomeequipa)
{
  struct equipa *equipaAuxiliar;
  if (hashequipa[hash(nomeequipa)] != 0)
  {
    for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
    {
      if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0)
      {
        equipaAuxiliar->n_vitorias += 1;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

}

void equipa_perdeu(char *nomeequipa)
{
  struct equipa *equipaAuxiliar;
  if (hashequipa[hash(nomeequipa)] != 0)
  {
    for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
    {
      if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0)
      {
        equipaAuxiliar->n_vitorias -= 1;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

}

void funcao_a()
{
  struct jogo *jogoAuxiliar;
  struct equipa *equipaAuxiliar;
  char *nomeJogo = malloc((sizeof(char)) * 1023);
  char *nomeequipa1 = malloc((sizeof(char)) * 1023);
  char *nomeequipa2 = malloc((sizeof(char)) * 1023);
  int r1;
  int r2;
  int j;
  linha++;
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  for (int nomeequipa1_index = 0; nomeequipa1_index < 10; nomeequipa1_index++)
  {
    nomeequipa1[nomeequipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeequipa1[10 - 1] = '\0';
  for (int nomeequipa2_index = 0; nomeequipa2_index < 10; nomeequipa2_index++)
  {
    nomeequipa2[nomeequipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeequipa2[10 - 1] = '\0';
  r1 = new_sym_var(sizeof(int) * 8);
  r2 = new_sym_var(sizeof(int) * 8);
  if (hashjogos[hash(nomeJogo)] != 0)
  {
    for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != 0; jogoAuxiliar = jogoAuxiliar->posterior)
    {
      if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0)
      {
        printf("%d Jogo existente.\n", linha);
        return;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  j = 0;
  if (hashequipa[hash(nomeequipa1)] != 0)
  {
    for (equipaAuxiliar = hashequipa[hash(nomeequipa1)]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
    {
      if (strcmp(nomeequipa1, equipaAuxiliar->nomeequipa) == 0)
      {
        j = 1;
      }
      else
      {
        
      }

    }

    if (j == 0)
    {
      printf("%d Equipa inexistente.\n", linha);
      return;
    }
    else
    {
      
    }

  }
  else
  {
    printf("%d Equipa inexistente.\n", linha);
    return;
  }

  j = 0;
  if (hashequipa[hash(nomeequipa2)] != 0)
  {
    for (equipaAuxiliar = hashequipa[hash(nomeequipa2)]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
    {
      if (strcmp(nomeequipa2, equipaAuxiliar->nomeequipa) == 0)
      {
        j = 1;
      }
      else
      {
        
      }

    }

    if (j == 0)
    {
      printf("%d Equipa inexistente.\n", linha);
    }
    else
    {
      
    }

  }
  else
  {
    printf("%d Equipa inexistente.\n", linha);
    return;
  }

  jogoAuxiliar = cria_jogo(nomeJogo, nomeequipa1, nomeequipa2, r1, r2);
  tabela[n] = jogoAuxiliar;
  n++;
  if (r1 > r2)
  {
    equipa_ganhou(nomeequipa1);
  }
  else
  {
    if (r1 < r2)
    {
      equipa_ganhou(nomeequipa2);
    }
    else
    {
      
    }

  }

  if (hashjogos[hash(nomeJogo)] == 0)
  {
    jogoAuxiliar->anterior = 0;
    jogoAuxiliar->posterior = 0;
    hashjogos[hash(nomeJogo)] = jogoAuxiliar;
  }
  else
  {
    jogoAuxiliar->posterior = hashjogos[hash(nomeJogo)];
    hashjogos[hash(nomeJogo)]->anterior = jogoAuxiliar;
    jogoAuxiliar->anterior = 0;
    hashjogos[hash(nomeJogo)] = jogoAuxiliar;
  }

}

void funcao_A()
{
  struct equipa *equipaAuxiliar;
  char *nomeequipa = malloc((sizeof(char)) * 1023);
  linha++;
  for (int nomeequipa_index = 0; nomeequipa_index < 10; nomeequipa_index++)
  {
    nomeequipa[nomeequipa_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeequipa[10 - 1] = '\0';
  if (hashequipa[hash(nomeequipa)] != 0)
  {
    for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
    {
      if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0)
      {
        printf("%d Equipa existente.\n", linha);
        return;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  equipaAuxiliar = cria_equipa(nomeequipa);
  if (hashequipa[hash(nomeequipa)] == 0)
  {
    equipaAuxiliar->anterior = 0;
    equipaAuxiliar->posterior = 0;
    hashequipa[hash(nomeequipa)] = equipaAuxiliar;
  }
  else
  {
    equipaAuxiliar->posterior = hashequipa[hash(nomeequipa)];
    hashequipa[hash(nomeequipa)]->anterior = equipaAuxiliar;
    equipaAuxiliar->anterior = 0;
    hashequipa[hash(nomeequipa)] = equipaAuxiliar;
  }

}

void funcao_l()
{
  int i;
  linha++;
  for (i = 0; i < n; i++)
  {
    if (tabela[i] != 0)
    {
      printf("%d %s %s %s %d %d\n", linha, tabela[i]->nomeJogo, tabela[i]->nomeEquipa1, tabela[i]->nomeEquipa2, tabela[i]->r1, tabela[i]->r2);
    }
    else
    {
      
    }

  }

}

void funcao_p()
{
  struct jogo *jogoAuxiliar;
  char *nomeJogo = malloc((sizeof(char)) * 1023);
  linha++;
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  if (hashjogos[hash(nomeJogo)] != 0)
  {
    for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != 0; jogoAuxiliar = jogoAuxiliar->posterior)
    {
      if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0)
      {
        printf("%d %s %s %s %d %d\n", linha, jogoAuxiliar->nomeJogo, jogoAuxiliar->nomeEquipa1, jogoAuxiliar->nomeEquipa2, jogoAuxiliar->r1, jogoAuxiliar->r2);
        return;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  printf("%d Jogo inexistente.\n", linha);
}

void funcao_P()
{
  struct equipa *equipaAuxiliar;
  char *nomeequipa = malloc((sizeof(char)) * 1023);
  linha++;
  for (int nomeequipa_index = 0; nomeequipa_index < 10; nomeequipa_index++)
  {
    nomeequipa[nomeequipa_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeequipa[10 - 1] = '\0';
  if (hashequipa[hash(nomeequipa)] != 0)
  {
    for (equipaAuxiliar = hashequipa[hash(nomeequipa)]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
    {
      if (strcmp(nomeequipa, equipaAuxiliar->nomeequipa) == 0)
      {
        printf("%d %s %d\n", linha, nomeequipa, equipaAuxiliar->n_vitorias);
        return;
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("%d Equipa inexistente.\n", linha);
  }

}

void funcao_r()
{
  struct jogo *jogoAuxiliar;
  struct jogo *jogoAuxiliar1;
  char *nomeJogo = malloc((sizeof(char)) * 1023);
  int i;
  linha++;
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  if (hashjogos[hash(nomeJogo)] != 0)
  {
    for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != 0; jogoAuxiliar = jogoAuxiliar->posterior)
    {
      if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0)
      {
        for (i = 0; i < n; i++)
        {
          if (strcmp(tabela[i]->nomeJogo, nomeJogo) == 0)
          {
            tabela[i] = 0;
          }
          else
          {
            
          }

        }

        if (jogoAuxiliar->r1 > jogoAuxiliar->r2)
        {
          equipa_perdeu(jogoAuxiliar->nomeEquipa1);
        }
        else
        {
          if (jogoAuxiliar->r1 < jogoAuxiliar->r2)
          {
            equipa_perdeu(jogoAuxiliar->nomeEquipa2);
          }
          else
          {
            
          }

        }

        if (jogoAuxiliar->anterior == 0)
        {
          if (jogoAuxiliar->posterior == 0)
          {
            hashjogos[hash(nomeJogo)] = 0;
            return;
          }
          else
          {
            
          }

          jogoAuxiliar1 = jogoAuxiliar->posterior;
          jogoAuxiliar1->anterior = 0;
          hashjogos[hash(nomeJogo)] = jogoAuxiliar1;
          return;
        }
        else
        {
          jogoAuxiliar1 = jogoAuxiliar->anterior;
          jogoAuxiliar1->posterior = jogoAuxiliar->posterior;
          jogoAuxiliar = jogoAuxiliar->posterior;
          jogoAuxiliar->anterior = jogoAuxiliar1;
          return;
        }

      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", linha);
  }

}

void funcao_s()
{
  struct jogo *jogoAuxiliar;
  char *nomeJogo = malloc((sizeof(char)) * 1023);
  int r1;
  int r2;
  linha++;
  for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
  {
    nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nomeJogo[10 - 1] = '\0';
  r1 = new_sym_var(sizeof(int) * 8);
  r2 = new_sym_var(sizeof(int) * 8);
  if (hashjogos[hash(nomeJogo)] != 0)
  {
    for (jogoAuxiliar = hashjogos[hash(nomeJogo)]; jogoAuxiliar != 0; jogoAuxiliar = jogoAuxiliar->posterior)
    {
      if (strcmp(nomeJogo, jogoAuxiliar->nomeJogo) == 0)
      {
        if (jogoAuxiliar->r1 > jogoAuxiliar->r2)
        {
          if (r1 < r2)
          {
            equipa_ganhou(jogoAuxiliar->nomeEquipa2);
            equipa_perdeu(jogoAuxiliar->nomeEquipa1);
          }
          else
          {
            if (r1 == r2)
            {
              equipa_perdeu(jogoAuxiliar->nomeEquipa1);
            }
            else
            {
              
            }

          }

        }
        else
        {
          if (jogoAuxiliar->r1 < jogoAuxiliar->r2)
          {
            if (r1 > r2)
            {
              equipa_ganhou(jogoAuxiliar->nomeEquipa1);
              equipa_perdeu(jogoAuxiliar->nomeEquipa2);
            }
            else
            {
              if (r1 == r2)
              {
                equipa_perdeu(jogoAuxiliar->nomeEquipa2);
              }
              else
              {
                
              }

            }

          }
          else
          {
            if (r1 > r2)
            {
              equipa_ganhou(jogoAuxiliar->nomeEquipa1);
            }
            else
            {
              if (r1 < r2)
              {
                equipa_ganhou(jogoAuxiliar->nomeEquipa2);
              }
              else
              {
                
              }

            }

          }

        }

        jogoAuxiliar->r1 = r1;
        jogoAuxiliar->r2 = r2;
      }
      else
      {
        
      }

    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", linha);
  }

}

void funcao_g()
{
  int maximo;
  int i;
  int j;
  int k;
  struct equipa *equipaAuxiliar;
  char *nomeAuxiliar;
  char **nomes = malloc((sizeof(char *)) * 200);
  for (j = 0; j < 200; j++)
  {
    nomes[j] = malloc((sizeof(char)) * 1023);
  }

  linha++;
  maximo = -1;
  j = 0;
  for (i = 0; i < M; i++)
  {
    if (hashequipa[i] != 0)
    {
      for (equipaAuxiliar = hashequipa[i]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
      {
        if (equipaAuxiliar->n_vitorias > maximo)
        {
          maximo = equipaAuxiliar->n_vitorias;
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

  }

  if (maximo == (-1))
  {
    for (j = 0; j < 200; j++)
    {
      free(nomes[j]);
    }

    free(nomes);
    return;
  }
  else
  {
    
  }

  for (i = 0; i < M; i++)
  {
    if (hashequipa[i] != 0)
    {
      for (equipaAuxiliar = hashequipa[i]; equipaAuxiliar != 0; equipaAuxiliar = equipaAuxiliar->posterior)
      {
        if (equipaAuxiliar->n_vitorias == maximo)
        {
          strcpy(nomes[j], equipaAuxiliar->nomeequipa);
          j++;
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

  }

  for (i = 0; i < j; i++)
  {
    for (k = 0; k < j; k++)
    {
      if (strcmp(nomes[k], nomes[i]) > 0)
      {
        nomeAuxiliar = nomes[i];
        nomes[i] = nomes[k];
        nomes[k] = nomeAuxiliar;
      }
      else
      {
        
      }

    }

  }

  printf("%d Melhores %d\n", linha, maximo);
  for (i = 0; i < j; i++)
  {
    printf("%d * %s\n", linha, nomes[i]);
  }

  for (j = 0; j < 200; j++)
  {
    free(nomes[j]);
  }

  free(nomes);
  return;
}

void funcao_x()
{
  int i;
  struct equipa *equipaAuxiliar;
  struct equipa *equipaAuxiliar1;
  struct jogo *jogoAuxiliar;
  struct jogo *jogoAuxiliar1;
  for (i = 0; i < M; i++)
  {
    if (hashequipa[i] != 0)
    {
      equipaAuxiliar = hashequipa[i];
      while (equipaAuxiliar != 0)
      {
        equipaAuxiliar1 = equipaAuxiliar->posterior;
        free(equipaAuxiliar->nomeequipa);
        free(equipaAuxiliar);
        equipaAuxiliar = equipaAuxiliar1;
      }

    }
    else
    {
      
    }

  }

  for (i = 0; i < M; i++)
  {
    if (hashjogos[i] != 0)
    {
      jogoAuxiliar = hashjogos[i];
      while (jogoAuxiliar != 0)
      {
        jogoAuxiliar1 = jogoAuxiliar->posterior;
        free(jogoAuxiliar->nomeJogo);
        free(jogoAuxiliar->nomeEquipa1);
        free(jogoAuxiliar->nomeEquipa2);
        free(jogoAuxiliar);
        jogoAuxiliar = jogoAuxiliar1;
      }

    }
    else
    {
      
    }

  }

  free(hashjogos);
  free(hashequipa);
}

int main()
{
  char comando;
  int i;
  StInitJogo();
  StInitEquipa();
  tabela = malloc((sizeof(struct jogo *)) * 300);
  for (i = 0; i < 300; i++)
  {
    tabela[i] = 0;
  }

  while (1)
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        funcao_a();
        break;

      case 'A':
        funcao_A();
        break;

      case 'l':
        funcao_l();
        break;

      case 'p':
        funcao_p();
        break;

      case 'P':
        funcao_P();
        break;

      case 'r':
        funcao_r();
        break;

      case 's':
        funcao_s();
        break;

      case 'g':
        funcao_g();
        break;

      case 'x':
        funcao_x();
        return 0;
        break;

    }

  }

  return 0;
}

