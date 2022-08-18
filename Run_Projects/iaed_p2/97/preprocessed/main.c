/*File generated by PreProcessor.py*/


#include <stdio.h>
#include "proj2.h"


int main()
{
  char a1[1023 + 1];
  char a2[1023 + 1];
  char a3[1023 + 1];
  int s;
  int a4;
  int a5;
  int NL = 1;
  lista *jogos_ordem = cria_lista_jogos();
  lista **jogos = incializa_tabela_jogo();
  elem_eq **equipas = incializa_tabela_equipa();
  while ((s = getchar()) != EOF)
  {
    switch (s)
    {
      case 'a':
        for (int a1_index = 0; a1_index < (1023 + 1); a1_index++)
      {
        a1[a1_index] = new_sym_var(sizeof(char) * 8);
      }

        a1[(1023 + 1) - 1] = '\0';
        for (int a2_index = 0; a2_index < (1023 + 1); a2_index++)
      {
        a2[a2_index] = new_sym_var(sizeof(char) * 8);
      }

        a2[(1023 + 1) - 1] = '\0';
        for (int a3_index = 0; a3_index < (1023 + 1); a3_index++)
      {
        a3[a3_index] = new_sym_var(sizeof(char) * 8);
      }

        a3[(1023 + 1) - 1] = '\0';
        a4 = new_sym_var(sizeof(int) * 8);
        a5 = new_sym_var(sizeof(int) * 8);
        novo_jogo(jogos, &jogos_ordem, equipas, NL, a1, a2, a3, a4, a5);
        break;

      case 'A':
        for (int a1_index = 0; a1_index < (1023 + 1); a1_index++)
      {
        a1[a1_index] = new_sym_var(sizeof(char) * 8);
      }

        a1[(1023 + 1) - 1] = '\0';
        nova_equipa(equipas, NL, a1);
        break;

      case 'l':
        LDL_jogos(&jogos_ordem, NL);
        break;

      case 'p':
        for (int a1_index = 0; a1_index < (1023 + 1); a1_index++)
      {
        a1[a1_index] = new_sym_var(sizeof(char) * 8);
      }

        a1[(1023 + 1) - 1] = '\0';
        procura_jogo(jogos, NL, a1);
        break;

      case 'P':
        for (int a1_index = 0; a1_index < (1023 + 1); a1_index++)
      {
        a1[a1_index] = new_sym_var(sizeof(char) * 8);
      }

        a1[(1023 + 1) - 1] = '\0';
        procura_equipa(equipas, NL, a1);
        break;

      case 'r':
        for (int a1_index = 0; a1_index < (1023 + 1); a1_index++)
      {
        a1[a1_index] = new_sym_var(sizeof(char) * 8);
      }

        a1[(1023 + 1) - 1] = '\0';
        apaga_jogo(jogos, &jogos_ordem, equipas, NL, a1);
        break;

      case 's':
        for (int a1_index = 0; a1_index < (1023 + 1); a1_index++)
      {
        a1[a1_index] = new_sym_var(sizeof(char) * 8);
      }

        a1[(1023 + 1) - 1] = '\0';
        a4 = new_sym_var(sizeof(int) * 8);
        a5 = new_sym_var(sizeof(int) * 8);
        altera_sc_jogo(jogos, equipas, NL, a1, a4, a5);
        break;

      case 'g':
        equipas_maior_pontuacao(equipas, NL);
        break;

      case 'x':
        apaga_todos_dados(jogos, &jogos_ordem, equipas);
        return 0;

      default:
        break;

    }

    NL++;
    getchar();
  }

  return 0;
}

