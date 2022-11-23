#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "commands.h"
/* Maximum number of characters of a read string*/
#define MC 1024

/* Applies command that matches read character. */
int main(){
   char character = getchar(), name[MC], team1[MC], team2[MC];
   int score1, score2, counter = 0;
   /* Initializes games' hash table. */
   LinkGame* games = HASHinit_game(1009);
   /* Initializes teams' hash table. */
   LinkTeam* teams = HASHinit_team(1009);
   /* Initializes list. */
   LinkedList list = init_list();

   while(character != 'x'){
      counter++;
      switch(character){
         case 'a':
         scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d ", name, team1,
               team2, &score1, &score2);
         command_a(name, team1, team2, score1, score2, counter,
                   games, teams, list);
         break;

         case 'A':
         scanf(" %[^:\n] ", name);
         command_A(name, counter, teams);
         break;

         case 'l':
         scanf(" ");
         command_l(counter, list);
         break;

         case 'p':
         scanf(" %[^:\n] ", name);
         command_p(name, counter, games);
         break;

         case 'P':
         scanf(" %[^:\n] ", name);
         command_P(name, counter, teams);
         break;

         case 'r':
         scanf(" %[^:\n] ", name);
         command_r(name, counter, games, teams, list);
         break;

         case 's':
         scanf(" %[^:\n]:%d:%d ", name, &score1, &score2);
         command_s(name, score1, score2, counter, games, teams, list);
         break;

         case 'g':
         scanf(" ");
         command_g(counter, teams);
         break;

         case 'x':
         break;
      }
      character = getchar();
   }
   /* Destroys games' hash table. */
   destroy_hash_game(games);
   /* Destroys games' hash table. */
   destroy_hash_team(teams);
   /* Destroys list. */
   destroy_list(list);

   return 0;
}
