#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include"lista.h"


int main()
{
  l_jogo *lista_jogo;
  hash_jogo **hash_game;
  jogo *game;
  equipa **equipas;
  equipa **orde;
  equipa **ord1;
  equipa *equ;
  equipa *equ2;
  char jog[1024];
  char eq1[1024];
  char eq2[1024];
  char c;
  int sc1;
  int sc2;
  int nl = 1;
  int m = 29;
  lista_jogo = (l_jogo *) malloc(sizeof(l_jogo));
  lista_jogo = cria_list_jogo(lista_jogo);
  hash_game = (hash_jogo **) malloc(m * (sizeof(hash_jogo)));
  hash_game = init(hash_game, m);
  equipas = (equipa **) malloc(m * (sizeof(equipa)));
  equipas = init_eq(equipas, m);
  c = getchar();
  while (c != 'x')
  {
    switch (c)
    {
      case 'a':
        c = getchar();
        for (int jog_index = 0; jog_index < 10; jog_index++)
      {
        jog[jog_index] = new_sym_var(sizeof(char) * 8);
      }

        jog[10 - 1] = '\0';
        for (int eq1_index = 0; eq1_index < 10; eq1_index++)
      {
        eq1[eq1_index] = new_sym_var(sizeof(char) * 8);
      }

        eq1[10 - 1] = '\0';
        for (int eq2_index = 0; eq2_index < 10; eq2_index++)
      {
        eq2[eq2_index] = new_sym_var(sizeof(char) * 8);
      }

        eq2[10 - 1] = '\0';
        sc1 = new_sym_var(sizeof(int) * 8);
        sc2 = new_sym_var(sizeof(int) * 8);
        if (encontra_jogo(hash_game, jog, m) != 0)
      {
        printf("%d Jogo existente.\n", nl);
      }
      else
      {
        if (((equ = encontra_equipa(equipas, eq1, m)) == 0) || ((equ2 = encontra_equipa(equipas, eq2, m)) == 0))
        {
          printf("%d Equipa inexistente.\n", nl);
        }
        else
        {
          add_jogo(lista_jogo, jog, equ, equ2, sc1, sc2);
          insere_jogo(hash_game, jog, lista_jogo->last, m);
          if (sc1 > sc2)
          {
            equ->i++;
          }
          else
          {
            if (sc2 > sc1)
            {
              equ2->i++;
            }
            else
            {
              
            }

          }

        }

      }

        break;

      case 'l':
        print(lista_jogo, nl);
        break;

      case 'p':
        c = getchar();
        for (int jog_index = 0; jog_index < 10; jog_index++)
      {
        jog[jog_index] = new_sym_var(sizeof(char) * 8);
      }

        jog[10 - 1] = '\0';
        if ((game = encontra_jogo(hash_game, jog, m)) == 0)
      {
        printf("%d Jogo inexistente.\n", nl);
      }
      else
      {
        printf("%d %s %s %s %d %d\n", nl, game->n_jogo, game->equipa1->nome, game->equipa2->nome, game->sc1, game->sc2);
      }

        break;

      case 'r':
        c = getchar();
        for (int jog_index = 0; jog_index < 10; jog_index++)
      {
        jog[jog_index] = new_sym_var(sizeof(char) * 8);
      }

        jog[10 - 1] = '\0';
        remo_jog(hash_game, jog, lista_jogo, m, nl);
        break;

      case 's':
        c = getchar();
        for (int jog_index = 0; jog_index < 10; jog_index++)
      {
        jog[jog_index] = new_sym_var(sizeof(char) * 8);
      }

        jog[10 - 1] = '\0';
        sc1 = new_sym_var(sizeof(int) * 8);
        sc2 = new_sym_var(sizeof(int) * 8);
        if ((game = encontra_jogo(hash_game, jog, m)) == 0)
      {
        printf("%d Jogo inexistente.\n", nl);
      }
      else
      {
        if ((game->sc1 > game->sc2) && (sc1 < sc2))
        {
          game->equipa1->i--;
          game->equipa2->i++;
        }
        else
        {
          if ((game->sc1 < game->sc2) && (sc1 > sc2))
          {
            game->equipa1->i++;
            game->equipa2->i--;
          }
          else
          {
            if ((game->sc1 == game->sc2) && (sc1 > sc2))
            {
              game->equipa1->i++;
            }
            else
            {
              if ((game->sc1 == game->sc2) && (sc1 < sc2))
              {
                game->equipa2->i++;
              }
              else
              {
                if ((game->sc1 > game->sc2) && (sc1 == sc2))
                {
                  game->equipa1->i--;
                }
                else
                {
                  if ((game->sc1 < game->sc2) && (sc1 == sc2))
                  {
                    game->equipa2->i--;
                  }
                  else
                  {
                    
                  }

                }

              }

            }

          }

        }

        game->sc1 = sc1;
        game->sc2 = sc2;
      }

        break;

      case 'A':
        c = getchar();
        for (int eq1_index = 0; eq1_index < 10; eq1_index++)
      {
        eq1[eq1_index] = new_sym_var(sizeof(char) * 8);
      }

        eq1[10 - 1] = '\0';
        if (encontra_equipa(equipas, eq1, m) == 0)
      {
        insere_equipa(equipas, eq1, m);
      }
      else
      {
        printf("%d Equipa existente.\n", nl);
      }

        break;

      case 'P':
        c = getchar();
        for (int eq1_index = 0; eq1_index < 10; eq1_index++)
      {
        eq1[eq1_index] = new_sym_var(sizeof(char) * 8);
      }

        eq1[10 - 1] = '\0';
        if ((equ = encontra_equipa(equipas, eq1, m)) != 0)
      {
        printf("%d %s %d\n", nl, eq1, equ->i);
      }
      else
      {
        printf("%d Equipa inexistente.\n", nl);
      }

        break;

      case 'g':
        sc2 = 0;
        sc1 = 0;
        sc1 = encontr_melhor(equipas, m, sc1, &sc2);
        if (sc2 != 0)
      {
        orde = (equipa **) malloc(sc2 * (sizeof(equipa)));
        ord1 = orde;
        proc(equipas, orde, sc1, m, sc2);
        ordena_lista(ord1, 0, sc2 - 1);
        printf("%d Melhores %d\n", nl, sc1);
        for (sc1 = 0; sc1 < sc2; sc1++)
          printf("%d * %s\n", nl, ord1[sc1]->nome);

        free(ord1);
      }
      else
      {
        
      }

        break;

    }

    c = getchar();
    c = getchar();
    nl++;
  }

  end(hash_game, m);
  end_q(equipas, m);
  free(lista_jogo);
  return 0;
}

