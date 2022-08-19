/*File generated by PreProcessor.py*/


#include "equipas.h"
#include "jogos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
  char cmd;
  int NL = 0;
  hashtable_equipas *h_equipas = mk_hash_table_e();
  node_equipas *n_equipas = 0;
  hashtable_jogos *h_jogos = mk_hash_table_j();
  lista_jogos *jogos = mk_list();
  while ((cmd = getchar()) != 'x')
  {
    if (cmd == 'A')
    {
      {
        NL++;
        n_equipas = A(NL, n_equipas, h_equipas);
      }
    }
    else
    {
      if (cmd == 'P')
      {
        {
          NL++;
          P(NL, h_equipas);
        }
      }
      else
      {
        if (cmd == 'a')
        {
          {
            NL++;
            a(NL, jogos, h_jogos, h_equipas);
          }
        }
        else
        {
          if (cmd == 'l')
          {
            {
              NL++;
              l(NL, jogos);
            }
          }
          else
          {
            if (cmd == 'p')
            {
              {
                NL++;
                p(NL, h_jogos);
              }
            }
            else
            {
              if (cmd == 's')
              {
                {
                  NL++;
                  s(NL, h_jogos, h_equipas);
                }
              }
              else
              {
                if (cmd == 'r')
                {
                  {
                    NL++;
                    r(NL, jogos, h_jogos, h_equipas);
                  }
                }
                else
                {
                  if (cmd == 'g')
                  {
                    {
                      NL++;
                      g(NL, h_equipas);
                    }
                  }
                  else
                  {
                    continue;
                  }

                }

              }

            }

          }

        }

      }

    }

  }

  lib_espaco_equipas(n_equipas, h_equipas);
  free_list(jogos);
  lib_espaco_jogos(h_jogos);
  return 0;
}
