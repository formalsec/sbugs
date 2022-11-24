#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "hash.h"

/* Function Prototypes */
void do_a(Team*, Game*, int*, int);
void do_A(Team*, int*, int);
void do_l(Game*, int);
void do_p(Game*, int);
void do_P(Team*, int);
void do_r(Team*, Game*, int*, int);
void do_s(Team*, Game*, int);
void do_g(Team*, int);


void do_a(Team* hash_team_sys, Game* hash_game_sys,
int* game_count, int nl_count) {

      unsigned int t1_score, t2_score;
      char game_name[STRINGLIM];
      char t1_name[STRINGLIM];
      char t2_name[STRINGLIM];
      Team t1_dummy, t2_dummy;
      Game g_dummy;

      scanf("%*c%[^:]:%[^:]:%[^:]:%u:%u%*c",
      game_name, t1_name, t2_name, &t1_score, &t2_score);

      game_name[STRINGLIM - 1] = '\0';
      t1_name[STRINGLIM - 1] = '\0';
      t2_name[STRINGLIM - 1] = '\0';

      /* Ensure that no more than 9000 in 10000 elements are filled
      in the hash_game_sys */
      if (*game_count >= HASH_ELM_LIM) return;

      g_dummy = gameHashLookup(hash_game_sys, game_name);

      if (g_dummy) {

          printf("%d Jogo existente.\n", nl_count);
          return;
      }

      t1_dummy = teamHashLookup(hash_team_sys, t1_name);
      t2_dummy = teamHashLookup(hash_team_sys, t2_name);

      if (t1_dummy && t2_dummy) {

          if (strcmp(t1_dummy->name, t2_dummy->name)) {

              g_dummy =
              createGame(game_name, t1_name, t2_name,
              t1_score, t2_score, nl_count);
              insertGame(hash_game_sys, g_dummy);

              ++(*game_count);

              if (t1_score > t2_score)
                  ++t1_dummy->wins;
              else if (t1_score < t2_score)
                  ++t2_dummy->wins;
          }
      }
      else printf("%d Equipa inexistente.\n", nl_count);
}


void do_A(Team* hash_team_sys, int* team_count, int nl_count) {

    char name[STRINGLIM];
    Team t_dummy;

    scanf("%*c%[^\n]%*c", name);

    name[STRINGLIM - 1] = '\0';

    if (*team_count >= HASH_ELM_LIM) return;

    t_dummy = teamHashLookup(hash_team_sys, name);

    if (t_dummy) {

        printf("%d Equipa existente.\n", nl_count);
        return;
    }
    t_dummy = createTeam(name);
    insertTeam(hash_team_sys, t_dummy);

    ++(*team_count);
}


void do_l(Game* hash_game_sys, int nl_count) {

    int i, last_pos = 0;
    Game sorted_games[HASH_TABLE_LIM];

    for (i = 0; i < HASH_TABLE_LIM; i++) {

        if (hash_game_sys[i] && !ghost(hash_game_sys[i]))
        sorted_games[last_pos++] = hash_game_sys[i];
    }
    if (last_pos) {

        qsort(sorted_games, last_pos, sizeof(Game), gameCmpNLine);

        for (i = 0; i < last_pos; i++) {

            printf("%d %s %s %s %u %u\n",
            nl_count, sorted_games[i]->name,
            sorted_games[i]->team1,
            sorted_games[i]->team2,
            sorted_games[i]->t1_score,
            sorted_games[i]->t2_score);
        }
    }
}


void do_p(Game* hash_game_sys, int nl_count) {

    char name[STRINGLIM];
    Game g_dummy;

    scanf("%*c%[^\n]%*c", name);

    g_dummy = gameHashLookup(hash_game_sys, name);

    if (g_dummy) {

        printf("%d %s %s %s %u %u\n",
        nl_count, g_dummy->name,
        g_dummy->team1,
        g_dummy->team2,
        g_dummy->t1_score,
        g_dummy->t2_score);
    }
    else printf("%d Jogo inexistente.\n", nl_count);
}


void do_P(Team* hash_team_sys, int nl_count) {

    char name[STRINGLIM];
    Team t_dummy;

    scanf("%*c%[^\n]%*c", name);

    t_dummy = teamHashLookup(hash_team_sys, name);

    if (t_dummy) {

        printf("%d %s %u\n", nl_count,
        t_dummy->name,
        t_dummy->wins);
    }
    else printf("%d Equipa inexistente.\n", nl_count);
}


void do_r(Team* hash_team_sys, Game* hash_game_sys,
int* game_count, int nl_count) {

    char name[STRINGLIM];
    Team t1_dummy, t2_dummy;
    Game trashed_game;

    scanf("%*c%[^\n]%*c", name);

    trashed_game = gameHashLookup(hash_game_sys, name);

    if (trashed_game) {

        t1_dummy =
        teamHashLookup(hash_team_sys, trashed_game->team1);
        t2_dummy =
        teamHashLookup(hash_team_sys, trashed_game->team2);

        if (trashed_game->t1_score > trashed_game->t2_score)
            --t1_dummy->wins;
        else if (trashed_game->t1_score < trashed_game->t2_score)
            --t2_dummy->wins;

        trashed_game->removed_state = TRUE;

        --(*game_count);
    }
    else printf("%d Jogo inexistente.\n", nl_count);
}


void do_s(Team* hash_team_sys, Game* hash_game_sys, int nl_count) {

    char name[STRINGLIM];
    unsigned int new_t1_score, new_t2_score;
    unsigned int old_t1_score, old_t2_score;
    Team t1_dummy, t2_dummy;
    Game g_dummy;

    scanf("%*c%[^:]:%u:%u%*c", name, &new_t1_score, &new_t2_score);

    g_dummy = gameHashLookup(hash_game_sys, name);

    if (g_dummy) {

        old_t1_score = g_dummy->t1_score;
        old_t2_score = g_dummy->t2_score;

        g_dummy->t1_score = new_t1_score;
        g_dummy->t2_score = new_t2_score;

        t1_dummy = teamHashLookup(hash_team_sys, g_dummy->team1);
        t2_dummy = teamHashLookup(hash_team_sys, g_dummy->team2);

        if (old_t1_score < old_t2_score) {

            if (new_t1_score > new_t2_score) {

                ++t1_dummy->wins;
                --t2_dummy->wins;
            }
            else if (new_t1_score == new_t2_score)
                --t2_dummy->wins;
        }
        else if (old_t1_score == old_t2_score) {

            if (new_t1_score > new_t2_score) {
                ++t1_dummy->wins;
            }
            else if (new_t1_score < new_t2_score)
                ++t2_dummy->wins;
        }
        else {

            if (new_t1_score < new_t2_score) {

                --t1_dummy->wins;
                ++t2_dummy->wins;
            }
            else if (new_t1_score == new_t2_score)
                --t1_dummy->wins;
        }
    }
    else printf("%d Jogo inexistente.\n", nl_count);
}


void do_g(Team* hash_team_sys, int nl_count) {

    int i, last_pos = 0;
    unsigned int max_wins = 0;
    Team sorted_teams[STRINGLIM];

    max_wins = bestTeamsScoreLookup(hash_team_sys);

    for (i = 0; i < HASH_TABLE_LIM; i++ ) {

        if (hash_team_sys[i] && hash_team_sys[i]->wins == max_wins)
            sorted_teams[last_pos++] = hash_team_sys[i];
    }
    if (last_pos) {

        qsort(sorted_teams, last_pos, sizeof(Team), teamCmpABC);

        printf("%d Melhores %u\n", nl_count, max_wins);

        for (i = 0; i < last_pos; i++) {

            printf("%d * %s\n",
            nl_count, sorted_teams[i]->name);
        }
    }
}


int main() {

    int c;
    int nl_counter = 0;
    int game_sys_counter = 0;
    int team_sys_counter = 0;

    Team* hash_team_sys = (Team*)hashStartup();
    Game* hash_game_sys = (Game*)hashStartup();

    /* Exit condition */
    while ((c = getchar()) != 'x') {

        switch (c) {
            case 'a':
                do_a(hash_team_sys, hash_game_sys,
                &game_sys_counter, ++nl_counter);
                break;
            case 'A':
                do_A(hash_team_sys, &team_sys_counter,
                ++nl_counter);
                break;
            case 'l':
                do_l(hash_game_sys, ++nl_counter);
                break;
            case 'p':
                do_p(hash_game_sys, ++nl_counter);
                break;
            case 'P':
                do_P(hash_team_sys, ++nl_counter);
                break;
            case 'r':
                do_r(hash_team_sys, hash_game_sys,
                &game_sys_counter, ++nl_counter);
                break;
            case 's':
                do_s(hash_team_sys, hash_game_sys,
                ++nl_counter);
                break;
            case 'g':
                do_g(hash_team_sys, ++nl_counter);
                break;
        }
    }

    hashShutdown(hash_team_sys, hash_game_sys);

    return 0;
}
