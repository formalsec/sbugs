#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* inclusao dos header files necessarios */
#include "comandos.h"
#include "structs.h"


/* funcao principal int main */
int main()
{
  /* hash table para os jogos */
  game_n *hash_table[TABLE_SIZE];
  /* hash table para as equipas */
  team_n *hash_teams[TABLE_SIZE];

  /* ponteiro para a lista de jogos */
  game_n *head = NULL;
  /* ponteiro para a lista de equipas */
  team_n *head_team = NULL;

  /* numero da linha do comando de input que originou um dado output */
  int nl = 1;
  
  char c;
  int maximo, n_maximos;

  /* inicializacao das hash tables */
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
      /* encontrar o numero maximo de vitorias */
      maximo = encontrar_maximo(head_team);
      /* encontrar o numero de equipas com o numero maximo de vitorias */
      n_maximos = encontrar_numero_maximos(head_team, maximo);
      g_equipas_vencedoras(head_team, nl, maximo, n_maximos);
      nl++;
      break;
    }
    c = getchar();
  }
  
  /* free necessarios */
  free_hash_table(hash_table);
  free_hash_teams(hash_teams);
  
  return 0;
}