#include "commands.h"
#include "hashGame.h"
#include "hashTeam.h"
#include "list.h"

/* Adds new game.
   Adds game to both hash table and the list. If the game is not a tie, the
   number of games won by the team which won is incremented.
   Errors: - If the game is already in the hash table.
           - If either of the teams is not in the teams' hash table. */
void command_a(char name[], char team1[], char team2[],
               int score1, int score2, int counter, LinkGame* games,
               LinkTeam* teams, LinkedList list){
   if(search_game(games, name) != NULL){
      printf("%d Jogo existente.\n", counter);
   }
   else if(search_team(teams, team1) == NULL ||
           search_team(teams, team2) == NULL){
      printf("%d Equipa inexistente.\n", counter);
   }
   else{
      ItemGame game = newItem_game(name, team1, team2, score1, score2);
      insert_game(games, game);
      append_list(list, game);
      if(score1 > score2){
         ItemTeam team = search_team(teams, team1);
         team->numGamesWon++;
      }
      else if(score1 < score2){
         ItemTeam team = search_team(teams, team2);
         team->numGamesWon++;
      }
   }
}

/* Adds new team.
   Adds team to the hash table.
   Errors: - If the team is already in the hash table. */
void command_A(char name[], int counter, LinkTeam* teams){
   if(search_team(teams, name) != NULL){
      printf("%d Equipa existente.\n", counter);
   }
   else{
      insert_team(teams, newItem_team(name));
   }
}

/* Displays every introduced game.
   Sweeps the list and displays every element. */
void command_l(int counter, LinkedList list){
   show_list(list, counter);
}

/* Searches for a given game.
   Errors: If the game is not in the hash table. */
void command_p(char name[], int counter, LinkGame* games){
   if(search_game(games, name) == NULL){
      printf("%d Jogo inexistente.\n", counter);
   }
   else{
      printf("%d ", counter);
      showItem_game(search_game(games, name));
   }
}

/* Searches for a given team.
   Errors: If the team is not in the hash table.*/
void command_P(char name[], int counter, LinkTeam* teams){
   if(search_team(teams, name) == NULL){
      printf("%d Equipa inexistente.\n", counter);
   }
   else{
      printf("%d ", counter);
      showItem_team(search_team(teams, name));
   }
}

/* Deletes given game. Deletes from both the hash table and list.
   If the game being deleted was not a tie, the winner's number of games won is
   decremented.
   Errors: If the game is not in the hash table.*/
void command_r(char name[], int counter, LinkGame* games, LinkTeam* teams,
               LinkedList list){
   if(search_game(games, name) == NULL){
      printf("%d Jogo inexistente.\n", counter);
   }
   else{
      if(search_game(games, name)->score1 > search_game(games, name)->score2){
         search_team(teams, search_game(games, name)->team1)->numGamesWon--;
      }
      else if(search_game(games, name)->score1 <
              search_game(games, name)->score2){
         search_team(teams, search_game(games, name)->team2)->numGamesWon--;
      }

      delete_game(games, name);
      remove_elem_list(list, name);
   }
}

/* Changes the score of a given game.
   Teams' number of games won needs to be adjusted according to previous score.
   Errors: If the game is not in the hash table.*/
void command_s(char name[], int score1, int score2, int counter,
               LinkGame* games, LinkTeam* teams, LinkedList list){
   int initWin = 0, finalWin = 0;

   if(search_game(games, name) == NULL){
      printf("%d Jogo inexistente.\n", counter);
   }
   else{

      if(search_game(games, name)->score1 > search_game(games, name)->score2){
         initWin = 1;
      }
      else if(search_game(games, name)->score1 <
              search_game(games, name)->score2){
         initWin = 2;
      }

      if(score1 > score2){
         finalWin = 1;
      }
      else if(score1 < score2){
         finalWin = 2;
      }

      if(initWin == 1 && finalWin == 2 &&
         search_team(teams, search_game(games, name)->team1)->numGamesWon>0){

         search_team(teams, search_game(games, name)->team1)->numGamesWon--;
         search_team(teams, search_game(games, name)->team2)->numGamesWon++;
      }
      else if(initWin == 1 && finalWin == 2){

         search_team(teams, search_game(games, name)->team2)->numGamesWon++;
      }
      else if(initWin == 2 && finalWin == 1 && search_team
              (teams, search_game(games, name)->team2)->numGamesWon > 0){

         search_team(teams, search_game(games, name)->team1)->numGamesWon++;
         search_team(teams, search_game(games, name)->team2)->numGamesWon--;
      }
      else if(initWin == 2 && finalWin == 1){

         search_team(teams, search_game(games, name)->team1)->numGamesWon++;
      }
      else if(initWin == 1 && finalWin == 0){
         search_team(teams, search_game(games, name)->team1)->numGamesWon--;
      }
      else if(initWin == 2 && finalWin == 0){
         search_team(teams, search_game(games, name)->team2)->numGamesWon--;
      }
      else if(initWin == 0 && finalWin == 1){
         search_team(teams, search_game(games, name)->team1)->numGamesWon++;
      }
      else if(initWin == 0 && finalWin == 2){
         search_team(teams, search_game(games, name)->team2)->numGamesWon++;
      }

      search_game(games, name)->score1 = score1;
      search_game(games, name)->score2 = score2;
      search_list(list, name)->score1 = score1;
      search_list(list, name)->score2 = score2;
   }
}

/* Auxiliar compare function for qsort in command_g. */
int cmpfunc(const void * a, const void * b){
   char** x, ** y;
   x = (char**) a;
   y = (char**) b;
   return strcmp(*x, *y);
}

/* Displays teams that won the most games by alphabetical order. */
void command_g(int counter, LinkTeam* teams){
   char* highTeams[CH];
   int i, size = 0, maxGamesWon = 0;
   LinkTeam head;

   for(i = 0; i < MH; i++){
      for(head = teams[i]; head != NULL; head = head->next){
         if(head->item->numGamesWon == maxGamesWon){
            highTeams[size] = head->item->name;
            size++;
         }
         else if(head->item->numGamesWon > maxGamesWon){
            maxGamesWon = head->item->numGamesWon;
            highTeams[0] = head->item->name;
            size = 1;
         }
      }
   }

   if(size == 0){
      return;
   }
   else{
      qsort(highTeams, size, sizeof(char*), cmpfunc);
      printf("%d Melhores %d\n", counter, maxGamesWon);
      for(i = 0; i < size; i++){
         printf("%d * %s\n", counter, highTeams[i]);
      }
   }
}
