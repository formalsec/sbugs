/*File generated by PreProcessor.py*/


#include "commands.h"
#include <stdio.h>


char reader;
char var_nome[1024];
char var_eq1[1024];
char var_eq2[1024];
unsigned int var_s1;
unsigned int var_s2;
int main()
{
  while (reader != EOF)
  {
    reader = getchar();
    if (reader == 'a')
    {
      {
        for (int var_nome_index = 0; var_nome_index < 10; var_nome_index++)
        {
          var_nome[var_nome_index] = new_sym_var(sizeof(char) * 8);
        }

        var_nome[10 - 1] = '\0';
        for (int var_eq1_index = 0; var_eq1_index < 10; var_eq1_index++)
        {
          var_eq1[var_eq1_index] = new_sym_var(sizeof(char) * 8);
        }

        var_eq1[10 - 1] = '\0';
        for (int var_eq2_index = 0; var_eq2_index < 10; var_eq2_index++)
        {
          var_eq2[var_eq2_index] = new_sym_var(sizeof(char) * 8);
        }

        var_eq2[10 - 1] = '\0';
        var_s1 = new_sym_var(sizeof(unsigned int) * 8);
        var_s2 = new_sym_var(sizeof(unsigned int) * 8);
        adiciona_novo_jogo(var_nome, var_eq1, var_eq2, var_s1, var_s2);
      }
    }
    else
    {
      if (reader == 'A')
      {
        {
          for (int var_nome_index = 0; var_nome_index < 10; var_nome_index++)
          {
            var_nome[var_nome_index] = new_sym_var(sizeof(char) * 8);
          }

          var_nome[10 - 1] = '\0';
          adiciona_nova_equipa(var_nome);
        }
      }
      else
      {
        if (reader == 'l')
        {
          {
            lista_jogos();
          }
        }
        else
        {
          if (reader == 'p')
          {
            {
              for (int var_nome_index = 0; var_nome_index < 10; var_nome_index++)
              {
                var_nome[var_nome_index] = new_sym_var(sizeof(char) * 8);
              }

              var_nome[10 - 1] = '\0';
              procura_jogo(var_nome);
            }
          }
          else
          {
            if (reader == 'P')
            {
              {
                for (int var_nome_index = 0; var_nome_index < 10; var_nome_index++)
                {
                  var_nome[var_nome_index] = new_sym_var(sizeof(char) * 8);
                }

                var_nome[10 - 1] = '\0';
                procura_equipa(var_nome);
              }
            }
            else
            {
              if (reader == 'r')
              {
                {
                  for (int var_nome_index = 0; var_nome_index < 10; var_nome_index++)
                  {
                    var_nome[var_nome_index] = new_sym_var(sizeof(char) * 8);
                  }

                  var_nome[10 - 1] = '\0';
                  apaga_jogo(var_nome);
                }
              }
              else
              {
                if (reader == 's')
                {
                  {
                    for (int var_nome_index = 0; var_nome_index < 10; var_nome_index++)
                    {
                      var_nome[var_nome_index] = new_sym_var(sizeof(char) * 8);
                    }

                    var_nome[10 - 1] = '\0';
                    var_s1 = new_sym_var(sizeof(unsigned int) * 8);
                    var_s2 = new_sym_var(sizeof(unsigned int) * 8);
                    altera_score(var_nome, var_s1, var_s2);
                  }
                }
                else
                {
                  if (reader == 'g')
                  {
                    {
                      lista_vencedores();
                    }
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

  liberta_memoria();
  return 0;
}

