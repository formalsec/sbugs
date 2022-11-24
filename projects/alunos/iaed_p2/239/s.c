#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "projeto2.h"

/*
ARGUMENTOS: O nome do jogo do qual se quer alterar o score e os
novos scores que se pretende dar ao jogo.

OBJETIVO: Alterar score do jogo do nome inserido.
No caso de nao existir nenhum jogo com o nome dado, no sistema,
mostrar o erro "Jogo inexistente"
*/

void s(GAME* hashG[], int row)
{
  int index;
  int score1, score2;
  GAME* searcher_game;
  char name[MAX_STRING];
  getchar();
  scanf("%[^:]%d:%d", name,&score1,&score2);
  index = hash_function(name);
  searcher_game = hashG[index];

  while(strcmp(searcher_game->name,name) != 0)
  {
    if(searcher_game->link == NULL)
    {
      printf("%d Jogo inexistente.", row);

      return;
    }

    searcher_game = searcher_game->link;
  }

  if((searcher_game->score1 > searcher_game->score2) && (score2 > score1))
  {
    searcher_game->team1->score--;
    searcher_game->team2->score++;
  }

  else if((searcher_game->score2 > searcher_game->score1) && (score1 > score2))
  {
    searcher_game->team1->score++;
    searcher_game->team2->score--;
  }

  searcher_game->score1 = score1;
  searcher_game->score2 = score2;

  return;
}
