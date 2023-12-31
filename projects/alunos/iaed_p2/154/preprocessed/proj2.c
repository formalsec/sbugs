#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "comandos.h"
#include "structs.h"


int main()
{
  game_n *hash_table[10000];
  team_n *hash_teams[10000];
  game_n *head = 0;
  team_n *head_team = 0;
  int nl = 1;
  char c;
  int maximo;
  int n_maximos;
  iniciar_hash_table(hash_table);
  iniciar_hash_teams(hash_teams);
  c = getchar();
  while (c != 'x')
  {
    switch (c)
    {
      case 'a':
        head = a_adiciona_jogo(hash_table, hash_teams, head, nl);
        nl++;
        break;

      case 'A':
        head_team = A_adiciona_equipa(hash_teams, head_team, nl);
        nl++;
        break;

      case 'l':
        l_lista_jogos(head, nl);
        nl++;
        break;

      case 'p':
        p_procura_jogo(hash_table, nl);
        nl++;
        break;

      case 'P':
        P_procura_equipa(hash_teams, nl);
        nl++;
        break;

      case 'r':
        head = r_apaga_jogo(hash_table, hash_teams, head, nl);
        nl++;
        break;

      case 's':
        s_altera_score(hash_table, hash_teams, nl);
        nl++;
        break;

      case 'g':
        maximo = encontrar_maximo(head_team);
        n_maximos = encontrar_numero_maximos(head_team, maximo);
        g_equipas_vencedoras(head_team, nl, maximo, n_maximos);
        nl++;
        break;

    }

    c = getchar();
  }

  free_hash_table(hash_table);
  free_hash_teams(hash_teams);
  return 0;
}

