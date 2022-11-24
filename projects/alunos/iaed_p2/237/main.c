#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "game.h"
#include "hash.h"
#include "structs.h"
#include "team.h"

int main() {
  orderedGames * init;
  orderedTeams * init2;
  char choice;
  int maxWins = 0;
  int cmd_count = 0;
  int game_count = 0;
  ht * hashtable = hash_init();
  ht * game_ht = hash_init();
  init = NULL;
  init2 = NULL;


  while ((choice = getchar()) != 'x' && choice != EOF) {
    switch (choice) {
      case 'a':
        cmd_count++;
        init = push(init, addGame(hashtable, game_ht, cmd_count, &game_count, &maxWins));
        break;
      case 'p':
        cmd_count++;
        getGame(game_ht, cmd_count);
        break;
      case 'l':
        cmd_count++;
        print(init, cmd_count);
        break;
      case 'A':
        cmd_count++;
        init2 = pushTeam(init2, addTeam(hashtable, cmd_count));
        break;
      case 'P':
        cmd_count++;
        getTeam(hashtable, cmd_count);
        break;
      case 's':
        cmd_count++;
        changeScore(game_ht, cmd_count);
        updateMaxWins(init2, &maxWins);
        break;
      case 'r':
        cmd_count++;
        init = removeGame(game_ht, cmd_count, init);
        updateMaxWins(init2, &maxWins);
        break;
      case 'g':
        cmd_count++;
        printTeams(init2, cmd_count, maxWins);
        break;
    }
  }
  destroy(init);
  destroyTeams(init2);
  destroyGame(game_ht);
  destroyTeam(hashtable);
  return 0;
}
