#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include "auxiliares.h"     /* Header file que contem os defines relativos as funcoes auxiliares */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


int main()
{
  int NL = 0;
  char n;
  char s[3100];
  char espaco;
  Lista_equipas *lista_equipa = criar_lista();
  hashtable_equipas *ht_equipa = criar_equipas();
  hashtable_jogos *ht_jogos = criar_jogos();
  Lista_jogos *lista_jogo = criar_lista_j();
  while (1)
  {
    n = new_sym_var(sizeof(char) * 8);
    switch (n)
    {
      case 'a':
        NL += 1;
        espaco = new_sym_var(sizeof(char) * 8);
        fgets(s, 3100, stdin);
        a(NL, s, ht_jogos, ht_equipa, lista_jogo);
        break;

      case 'l':
        NL += 1;
        l(NL, lista_jogo);
        break;

      case 'p':
        NL += 1;
        espaco = new_sym_var(sizeof(char) * 8);
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        p(NL, s, ht_jogos);
        break;

      case 'r':
        NL += 1;
        espaco = new_sym_var(sizeof(char) * 8);
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        r(NL, s, ht_jogos, ht_equipa, lista_jogo);
        break;

      case 's':
        NL += 1;
        espaco = new_sym_var(sizeof(char) * 8);
        fgets(s, 3100, stdin);
        s_altera(NL, s, ht_jogos, ht_equipa, lista_jogo);
        break;

      case 'A':
        NL += 1;
        espaco = new_sym_var(sizeof(char) * 8);
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        A(NL, s, ht_equipa, lista_equipa);
        break;

      case 'P':
        NL += 1;
        espaco = new_sym_var(sizeof(char) * 8);
        for (int s_index = 0; s_index < 10; s_index++)
      {
        s[s_index] = new_sym_var(sizeof(char) * 8);
      }

        s[10 - 1] = '\0';
        P(NL, s, ht_equipa);
        break;

      case 'g':
        NL += 1;
        g(NL, lista_equipa, ht_equipa);
        break;

      case 'x':
        liberta_lista(lista_jogo);
        libertar_equipas(ht_equipa);
        liberta_lista_equipas(lista_equipa);
        return 0;
        break;

    }

  }

  return 0;
}

