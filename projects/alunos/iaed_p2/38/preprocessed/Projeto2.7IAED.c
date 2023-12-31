#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


float nl = 1;
int n_jogos = 0;
int n_equipas = 0;
typedef struct Equipa
{
  int id;
  char *nome_equipa;
  int n_jogos_ganhos;
} equipa;
typedef struct Jogo
{
  char *nome;
  equipa equipa1;
  equipa equipa2;
  int golos1;
  int golos2;
} jogo;
jogo *jogos;
equipa *equipas;
void inicializa_sistema()
{
  jogos = malloc(sizeof(jogo));
  equipas = malloc(sizeof(equipa));
}

void termina_sistema()
{
  int i;
  for (i = 0; i < n_jogos; i++)
    free(jogos[i].nome);

  free(jogos);
  for (i = 0; i < n_equipas; i++)
    free(equipas[i].nome_equipa);

  free(equipas);
}

void le_input(char *input)
{
  for (int input_index = 0; input_index < 10; input_index++)
  {
    input[input_index] = new_sym_var(sizeof(char) * 8);
  }

  input[10 - 1] = '\0';
}

int verifica_jogo(char *nome, int imprime)
{
  int i;
  for (i = 0; i < n_jogos; i++)
  {
    if (!strcmp(jogos[i].nome, nome))
    {
      return i + 1;
    }
    else
    {
      
    }

  }

  if (imprime)
  {
    printf("%.0f Jogo inexistente.\n", nl);
  }
  else
  {
    
  }

  return 0;
}

int verifica_equipa(char *nome, int imprime)
{
  int i;
  for (i = 0; i < n_equipas; i++)
  {
    if (!strcmp(equipas[i].nome_equipa, nome))
    {
      return i + 1;
    }
    else
    {
      
    }

  }

  if (imprime)
  {
    printf("%.0f Equipa inexistente.\n", nl);
  }
  else
  {
    
  }

  return 0;
}

void cria_jogo()
{
  char input[3085];
  char name[1024];
  char nome_equipa1[1024];
  char nome_equipa2[1024];
  char *palavra;
  int score1;
  int score2;
  int i = 0;
  int j;
  le_input(input);
  palavra = strtok(input, ":");
  while (palavra != 0)
  {
    if (i == 0)
    {
      strcpy(name, palavra);
    }
    else
    {
      if (i == 1)
      {
        strcpy(nome_equipa1, palavra);
      }
      else
      {
        if (i == 2)
        {
          strcpy(nome_equipa2, palavra);
        }
        else
        {
          if (i == 3)
          {
            score1 = atoi(palavra);
          }
          else
          {
            score2 = atoi(palavra);
          }

        }

      }

    }

    palavra = strtok(0, ":");
    i++;
  }

  i = verifica_equipa(nome_equipa1, 0);
  j = verifica_equipa(nome_equipa2, 0);
  if (verifica_jogo(name, 0))
  {
    printf("%.0f Jogo existente.\n", nl);
  }
  else
  {
    if (i && j)
    {
      jogos = realloc(jogos, (sizeof(jogo)) * (n_jogos + 1));
      jogos[n_jogos].nome = malloc((sizeof(char)) * (strlen(name) + 1));
      strcpy(jogos[n_jogos].nome, name);
      jogos[n_jogos].equipa1 = equipas[i - 1];
      jogos[n_jogos].equipa2 = equipas[j - 1];
      jogos[n_jogos].golos1 = score1;
      jogos[n_jogos].golos2 = score2;
      if (score1 > score2)
      {
        equipas[i - 1].n_jogos_ganhos++;
      }
      else
      {
        if (score2 > score1)
        {
          equipas[j - 1].n_jogos_ganhos++;
        }
        else
        {
          
        }

      }

      n_jogos++;
    }
    else
    {
      printf("%.0f Equipa inexistente.\n", nl);
    }

  }

}

void lista_jogos()
{
  int i;
  for (i = 0; i < n_jogos; i++)
    printf("%.0f %s %s %s %d %d\n", nl, jogos[i].nome, jogos[i].equipa1.nome_equipa, jogos[i].equipa2.nome_equipa, jogos[i].golos1, jogos[i].golos2);

}

void lista_jogo()
{
  int i;
  char name[1024];
  le_input(name);
  i = verifica_jogo(name, 1);
  if (i)
  {
    printf("%.0f %s %s %s %d %d\n", nl, jogos[i - 1].nome, jogos[i - 1].equipa1.nome_equipa, jogos[i - 1].equipa2.nome_equipa, jogos[i - 1].golos1, jogos[i - 1].golos2);
  }
  else
  {
    
  }

}

void apaga_jogo()
{
  int i;
  int j;
  char name[1024];
  le_input(name);
  j = verifica_jogo(name, 1);
  if (j)
  {
    if (jogos[j - 1].golos1 > jogos[j - 1].golos2)
    {
      equipas[jogos[j - 1].equipa1.id].n_jogos_ganhos--;
    }
    else
    {
      if (jogos[j - 1].golos1 < jogos[j - 1].golos2)
      {
        equipas[jogos[j - 1].equipa2.id].n_jogos_ganhos--;
      }
      else
      {
        
      }

    }

    for (i = j - 1; i < (n_jogos - 1); i++)
      jogos[i] = jogos[i + 1];

    n_jogos--;
  }
  else
  {
    
  }

}

void altera_resultado()
{
  int i;
  int score1;
  int score2;
  char name[1024];
  char input[3085];
  char *palavra;
  le_input(input);
  palavra = strtok(input, ":");
  strcpy(name, palavra);
  palavra = strtok(0, ":");
  score1 = atoi(palavra);
  palavra = strtok(0, ":");
  score2 = atoi(palavra);
  i = verifica_jogo(name, 1);
  if (i)
  {
    if ((score1 >= score2) && (jogos[i - 1].golos2 >= jogos[i - 1].golos1))
    {
      if (jogos[i - 1].golos2 > jogos[i - 1].golos1)
      {
        equipas[jogos[i - 1].equipa2.id].n_jogos_ganhos--;
      }
      else
      {
        
      }

      if (score1 > score2)
      {
        equipas[jogos[i - 1].equipa1.id].n_jogos_ganhos++;
      }
      else
      {
        
      }

    }
    else
    {
      if ((score2 >= score1) && (jogos[i - 1].golos1 >= jogos[i - 1].golos2))
      {
        if (jogos[i - 1].golos1 > jogos[i - 1].golos2)
        {
          equipas[jogos[i - 1].equipa1.id].n_jogos_ganhos--;
        }
        else
        {
          
        }

        if (score2 > score1)
        {
          equipas[jogos[i - 1].equipa2.id].n_jogos_ganhos++;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

    jogos[i - 1].golos1 = score1;
    jogos[i - 1].golos2 = score2;
  }
  else
  {
    
  }

}

void cria_equipa()
{
  char team_name[1024];
  le_input(team_name);
  if (verifica_equipa(team_name, 0))
  {
    printf("%.0f Equipa existente.\n", nl);
  }
  else
  {
    equipas = realloc(equipas, (sizeof(equipa)) * (n_equipas + 1));
    equipas[n_equipas].id = n_equipas;
    equipas[n_equipas].nome_equipa = malloc((sizeof(char)) * (strlen(team_name) + 1));
    strcpy(equipas[n_equipas].nome_equipa, team_name);
    equipas[n_equipas].n_jogos_ganhos = 0;
    n_equipas++;
  }

}

void lista_equipa()
{
  int i;
  char team_name[1024];
  le_input(team_name);
  i = verifica_equipa(team_name, 1);
  if (i)
  {
    printf("%.0f %s %d\n", nl, equipas[i - 1].nome_equipa, equipas[i - 1].n_jogos_ganhos);
  }
  else
  {
    
  }

}

void lista_melhores_equipas()
{
  int i;
  int maior = 0;
  int cont = 0;
  int finish;
  equipa *melhores_equipas;
  equipa aux;
  for (i = 0; i < n_equipas; i++)
  {
    if (equipas[i].n_jogos_ganhos > maior)
    {
      maior = equipas[i].n_jogos_ganhos;
    }
    else
    {
      
    }

  }

  melhores_equipas = malloc(sizeof(equipa));
  for (i = 0; i < n_equipas; i++)
  {
    if (!i)
    {
      printf("%.0f Melhores %d\n", nl, maior);
    }
    else
    {
      
    }

    if (equipas[i].n_jogos_ganhos == maior)
    {
      cont++;
      melhores_equipas = realloc(melhores_equipas, (sizeof(equipa)) * cont);
      melhores_equipas[cont - 1] = equipas[i];
    }
    else
    {
      
    }

  }

  while (1)
  {
    finish = 1;
    for (i = 0; i < (cont - 1); i++)
    {
      if (strcmp(melhores_equipas[i].nome_equipa, melhores_equipas[i + 1].nome_equipa) > 0)
      {
        aux = melhores_equipas[i];
        melhores_equipas[i] = melhores_equipas[i + 1];
        melhores_equipas[i + 1] = aux;
        finish = 0;
      }
      else
      {
        
      }

    }

    if (finish)
    {
      break;
    }
    else
    {
      
    }

  }

  for (i = 0; i < cont; i++)
    printf("%.0f * %s\n", nl, melhores_equipas[i].nome_equipa);

  free(melhores_equipas);
}

int main()
{
  char comando;
  inicializa_sistema();
  while ((comando = getchar()) && (comando != 'x'))
  {
    if (comando == 'a')
    {
      cria_jogo();
    }
    else
    {
      if (comando == 'l')
      {
        lista_jogos();
      }
      else
      {
        if (comando == 'p')
        {
          lista_jogo();
        }
        else
        {
          if (comando == 'r')
          {
            apaga_jogo();
          }
          else
          {
            if (comando == 's')
            {
              altera_resultado();
            }
            else
            {
              if (comando == 'A')
              {
                cria_equipa();
              }
              else
              {
                if (comando == 'P')
                {
                  lista_equipa();
                }
                else
                {
                  if (comando == 'g')
                  {
                    lista_melhores_equipas();
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

    nl = nl + 0.5;
  }

  termina_sistema();
  return 0;
}

