#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_jogos.h"
#include "hash_equipas.h"


void insertion(char *a[], int left, int right)
{
  int i;
  int j;
  for (i = left + 1; i < right; i++)
  {
    char *v = a[i];
    j = i - 1;
    while ((j >= left) && (strcmp(v, a[j]) < 0))
    {
      a[j + 1] = a[j];
      j--;
    }

    a[j + 1] = v;
  }

}

int main()
{
  char x;
  int linha = 0;
  link_jogo lista_jogos = 0;
  link_equipa lista_equipas = 0;
  link_jogo *tabela_jogos;
  link_equipa *tabela_equipas;
  tabela_jogos = init_jogo(1069);
  tabela_equipas = init_equipa(1069);
  x = getchar();
  while (x != 'x')
  {
    if (x == 'a')
    {
      link_jogo jogo;
      int score1;
      int score2;
      char buf[1024];
      char buf1[1024];
      char buf2[1024];
      char *equipa1;
      char *equipa2;
      char *nome;
      linha++;
      for (int buf_index = 0; buf_index < 10; buf_index++)
      {
        buf[buf_index] = new_sym_var(sizeof(char) * 8);
      }

      buf[10 - 1] = '\0';
      for (int buf1_index = 0; buf1_index < 10; buf1_index++)
      {
        buf1[buf1_index] = new_sym_var(sizeof(char) * 8);
      }

      buf1[10 - 1] = '\0';
      for (int buf2_index = 0; buf2_index < 10; buf2_index++)
      {
        buf2[buf2_index] = new_sym_var(sizeof(char) * 8);
      }

      buf2[10 - 1] = '\0';
      score1 = new_sym_var(sizeof(int) * 8);
      score2 = new_sym_var(sizeof(int) * 8);
      nome = (char *) malloc((strlen(buf) + 1) * (sizeof(char)));
      strcpy(nome, buf);
      equipa1 = (char *) malloc((strlen(buf1) + 1) * (sizeof(char)));
      strcpy(equipa1, buf1);
      equipa2 = (char *) malloc((strlen(buf2) + 1) * (sizeof(char)));
      strcpy(equipa2, buf2);
      if (procura_jogo(nome, tabela_jogos) != 0)
      {
        printf("%d Jogo existente.\n", linha);
      }
      else
      {
        if (procura_equipa(equipa1, tabela_equipas) == 0)
        {
          printf("%d Equipa inexistente.\n", linha);
        }
        else
        {
          if (procura_equipa(equipa2, tabela_equipas) == 0)
          {
            printf("%d Equipa inexistente.\n", linha);
          }
          else
          {
            jogo = novo_jogo(nome, equipa1, equipa2, score1, score2);
            tabela_jogos = insere_jogo(jogo, tabela_jogos);
            lista_jogos = insere_jogo_2(jogo, lista_jogos);
            if (score1 > score2)
            {
              atribui_vitoria(equipa1, tabela_equipas);
              lista_equipas = atribui_vitoria_2(equipa1, lista_equipas);
            }
            else
            {
              if (score1 < score2)
              {
                atribui_vitoria(equipa2, tabela_equipas);
                lista_equipas = atribui_vitoria_2(equipa2, lista_equipas);
              }
              else
              {
                
              }

            }

          }

        }

      }

      free(nome);
      free(equipa1);
      free(equipa2);
    }
    else
    {
      if (x == 'A')
      {
        char *nome;
        char buffer[1024];
        link_equipa new_equipa;
        linha++;
        for (int buffer_index = 0; buffer_index < 10; buffer_index++)
        {
          buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
        }

        buffer[10 - 1] = '\0';
        nome = (char *) malloc((strlen(buffer) + 1) * (sizeof(char)));
        strcpy(nome, buffer);
        if (procura_equipa(nome, tabela_equipas) != 0)
        {
          printf("%d Equipa existente.\n", linha);
        }
        else
        {
          new_equipa = nova_equipa(nome);
          tabela_equipas = insere_equipa(new_equipa, tabela_equipas);
          lista_equipas = insere_equipa_2(new_equipa, lista_equipas);
        }

        free(nome);
      }
      else
      {
        if (x == 'l')
        {
          linha++;
          print_jogos(lista_jogos, linha);
        }
        else
        {
          if (x == 'p')
          {
            link_jogo x;
            char *nome;
            char buffer[1024];
            linha++;
            for (int buffer_index = 0; buffer_index < 10; buffer_index++)
            {
              buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
            }

            buffer[10 - 1] = '\0';
            nome = (char *) malloc((strlen(buffer) + 1) * (sizeof(char)));
            strcpy(nome, buffer);
            x = procura_jogo(nome, tabela_jogos);
            if (x == 0)
            {
              printf("%d Jogo inexistente.\n", linha);
            }
            else
            {
              printf("%d %s %s %s %d %d\n", linha, x->jogo->nome, x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);
            }

            free(nome);
          }
          else
          {
            if (x == 'P')
            {
              link_equipa equipa;
              char buffer[1024];
              char *nome;
              linha++;
              for (int buffer_index = 0; buffer_index < 10; buffer_index++)
              {
                buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
              }

              buffer[10 - 1] = '\0';
              nome = (char *) malloc((strlen(buffer) + 1) * (sizeof(char)));
              strcpy(nome, buffer);
              equipa = procura_equipa(nome, tabela_equipas);
              if (equipa == 0)
              {
                printf("%d Equipa inexistente.\n", linha);
              }
              else
              {
                printf("%d %s %d\n", linha, equipa->equipa->nome, equipa->equipa->vitorias);
              }

              free(nome);
            }
            else
            {
              if (x == 'r')
              {
                link_jogo jogo;
                char buffer[1024];
                char *nome;
                linha++;
                for (int buffer_index = 0; buffer_index < 10; buffer_index++)
                {
                  buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
                }

                buffer[10 - 1] = '\0';
                nome = (char *) malloc((strlen(buffer) + 1) * (sizeof(char)));
                strcpy(nome, buffer);
                jogo = procura_jogo(nome, tabela_jogos);
                if (jogo == 0)
                {
                  printf("%d Jogo inexistente.\n", linha);
                }
                else
                {
                  if (jogo->jogo->score1 > jogo->jogo->score2)
                  {
                    remove_vitoria(jogo->jogo->equipa1, tabela_equipas);
                    lista_equipas = remove_vitoria_2(jogo->jogo->equipa1, lista_equipas);
                  }
                  else
                  {
                    if (jogo->jogo->score1 < jogo->jogo->score2)
                    {
                      remove_vitoria(jogo->jogo->equipa2, tabela_equipas);
                      lista_equipas = remove_vitoria_2(jogo->jogo->equipa2, lista_equipas);
                    }
                    else
                    {
                      
                    }

                  }

                  tabela_jogos = apaga_jogo(nome, tabela_jogos);
                  lista_jogos = apaga_jogo_2(nome, lista_jogos);
                }

                free(nome);
              }
              else
              {
                if (x == 's')
                {
                  link_jogo jogo;
                  char *nome;
                  int score1;
                  int score2;
                  int old_score1 = 0;
                  int old_score2 = 0;
                  char buffer[1024];
                  linha++;
                  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
                  {
                    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
                  }

                  buffer[10 - 1] = '\0';
                  score1 = new_sym_var(sizeof(int) * 8);
                  score2 = new_sym_var(sizeof(int) * 8);
                  nome = (char *) malloc((strlen(buffer) + 1) * (sizeof(char)));
                  strcpy(nome, buffer);
                  jogo = procura_jogo(nome, tabela_jogos);
                  if (jogo == 0)
                  {
                    printf("%d Jogo inexistente.\n", linha);
                  }
                  else
                  {
                    old_score1 = jogo->jogo->score1;
                    old_score2 = jogo->jogo->score2;
                    altera_jogo(jogo, score1, score2);
                    lista_jogos = altera_jogo_2(nome, score1, score2, lista_jogos);
                    if (old_score1 == old_score2)
                    {
                      if (score1 > score2)
                      {
                        atribui_vitoria(jogo->jogo->equipa1, tabela_equipas);
                        lista_equipas = atribui_vitoria_2(jogo->jogo->equipa1, lista_equipas);
                      }
                      else
                      {
                        if (score1 < score2)
                        {
                          atribui_vitoria(jogo->jogo->equipa2, tabela_equipas);
                          lista_equipas = atribui_vitoria_2(jogo->jogo->equipa2, lista_equipas);
                        }
                        else
                        {
                          
                        }

                      }

                    }
                    else
                    {
                      if (old_score1 > old_score2)
                      {
                        if (score1 < score2)
                        {
                          remove_vitoria(jogo->jogo->equipa1, tabela_equipas);
                          lista_equipas = remove_vitoria_2(jogo->jogo->equipa1, lista_equipas);
                          atribui_vitoria(jogo->jogo->equipa2, tabela_equipas);
                          lista_equipas = atribui_vitoria_2(jogo->jogo->equipa2, lista_equipas);
                        }
                        else
                        {
                          
                        }

                        if (score1 == score2)
                        {
                          remove_vitoria(jogo->jogo->equipa1, tabela_equipas);
                          lista_equipas = remove_vitoria_2(jogo->jogo->equipa1, lista_equipas);
                        }
                        else
                        {
                          
                        }

                      }
                      else
                      {
                        if (old_score1 < old_score2)
                        {
                          if (score1 > score2)
                          {
                            remove_vitoria(jogo->jogo->equipa2, tabela_equipas);
                            lista_equipas = remove_vitoria_2(jogo->jogo->equipa2, lista_equipas);
                            atribui_vitoria(jogo->jogo->equipa1, tabela_equipas);
                            lista_equipas = atribui_vitoria_2(jogo->jogo->equipa1, lista_equipas);
                          }
                          else
                          {
                            
                          }

                          if (score1 == score2)
                          {
                            remove_vitoria(jogo->jogo->equipa2, tabela_equipas);
                            lista_equipas = remove_vitoria_2(jogo->jogo->equipa2, lista_equipas);
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

                  }

                }
                else
                {
                  if (x == 'g')
                  {
                    int max = 0;
                    int i = 0;
                    int j;
                    link_equipa t;
                    link_equipa x;
                    char *lista_melhores[1000];
                    linha++;
                    for (t = lista_equipas; t != 0; t = t->next)
                    {
                      if (t->equipa->vitorias >= max)
                      {
                        max = t->equipa->vitorias;
                      }
                      else
                      {
                        
                      }

                    }

                    for (x = lista_equipas; x != 0; x = x->next)
                    {
                      if (x->equipa->vitorias == max)
                      {
                        lista_melhores[i] = (char *) malloc((sizeof(char)) * (strlen(x->equipa->nome) + 1));
                        strcpy(lista_melhores[i], x->equipa->nome);
                        i++;
                      }
                      else
                      {
                        
                      }

                    }

                    insertion(lista_melhores, 0, i);
                    if (lista_equipas != 0)
                    {
                      printf("%d Melhores %d\n", linha, max);
                    }
                    else
                    {
                      
                    }

                    for (j = 0; j <= (i - 1); j++)
                    {
                      printf("%d * %s\n", linha, lista_melhores[j]);
                    }

                    for (j = 0; j < i; j++)
                    {
                      free(lista_melhores[j]);
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

    x = getchar();
  }

  tabela_jogos = liberta_jogos(tabela_jogos);
  lista_jogos = remove_lista(lista_jogos);
  tabela_equipas = liberta_equipas(tabela_equipas);
  lista_equipas = remove_lista_2(lista_equipas);
  free(tabela_jogos);
  free(tabela_equipas);
  return 0;
}

