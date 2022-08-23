#include <stdio.h>
#include "hashtable_team.h"
#include "hashtable_game.h"

#define MAX_INPUT 3080

int NL = 1;

int main(){
    ht_team *ht_team = ht_create_hteam();
    ht_game *ht_game = ht_create_hgame();
    GAME* linkedlist = NULL;

    while(1) {
        unsigned int j = 0;
        char command = '\0';
        char input[MAX_INPUT] = "\0";
        scanf("%c", &command);
        switch (command) {
            case 'a': {
                linkedlist = addGame(NL, ht_game, ht_team, linkedlist);
                NL++;
                break;
            }
            case 'A': {
                TEAM *team = NULL;
                scanf(" %[^:\n]", input);
                team = getTeam(input);
                ht_set_team(NL, ht_team, team);
                NL++;
                break;
            }
            case 'l': {
                GAME *paux = NULL;
                if (linkedlist == NULL) {
                    NL++;
                    break;
                }
                paux = linkedlist;
                while (paux != NULL) {
                    printf("%d %s %s %s %d %d\n", NL, paux->name, paux->team1->name, paux->team2->name,
                           paux->score[0], paux->score[1]);
                    if (paux->pnext != NULL) {
                        paux = paux->pnext;
                    }
                    else{
                        break;
                    }
                }
                NL++;
                break;
            }
            case 'p': {
                GAME *game = NULL;
                scanf(" %[^:\n]", input);
                game = ht_get_game(ht_game, input);
                if (game != NULL) {
                    printf("%d %s %s %s %d %d\n", NL, game->name, game->team1->name, game->team2->name,
                           game->score[0], game->score[1]);
                } else {
                    printf("%d Jogo inexistente.\n", NL);
                }
                NL++;
                break;
            }
            case 'P': {
                TEAM *team = NULL;
                scanf(" %[^:\n]", input);
                team = ht_get_team(ht_team, input);
                if (team != NULL) {
                    printf("%d %s %d\n", NL, team->name, team->gameswon);
                }
                else{
                    printf("%d Equipa inexistente.\n", NL);
                }
                NL++;
                break;
            }
            case 'r': {
                GAME *game = NULL;
                scanf(" %[^:\n]", input);
                game = ht_get_game(ht_game, input);
                if (game != NULL) {
                    linkedlist = ht_remove_game(ht_game, ht_team , game, linkedlist);
                } else {
                    printf("%d Jogo inexistente.\n", NL);
                }
                NL++;
                break;
            }
            case 's': {
                GAME *auxgame = NULL;
                char name[1024] = "\0";
                int score1 = 0, score2 = 0;
                scanf(" %[^:\n]:%d:%d", name, &score1, &score2);
                auxgame = ht_get_game(ht_game, name);
                if (auxgame == NULL) {
                    printf("%d Jogo inexistente.\n", NL);
                    NL++;
                    break;
                } else {
                    if (auxgame->score[0] > auxgame->score[1]) {
                        j = 1;
                    } else if (auxgame->score[1] > auxgame->score[0]) {
                        j = 2;
                    }
                    else{
                        j = 3;
                    }
                }
                auxgame->score[0] = score1;
                auxgame->score[1] = score2;
                if (auxgame->score[1] > auxgame->score[0] && j == 1){
                    TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
                    TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
                    team->gameswon++;
                    auxteam->gameswon--;
                }
                else if (auxgame->score[1] == auxgame->score[0] && j == 1){
                    TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
                    auxteam->gameswon--;
                }
                else if(auxgame->score[1] > auxgame->score[0] && j == 3){
                    TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
                    team->gameswon++;
                }
                else if (auxgame->score[0] > auxgame->score[1] && j == 3){
                    TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
                    auxteam->gameswon++;
                }
                else if (auxgame->score[0] > auxgame->score[1] && j == 2) {
                    TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
                    TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
                    auxteam->gameswon++;
                    team->gameswon--;
                }
                else if (auxgame->score[0] == auxgame->score[1] && j == 2) {
                    TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
                    team->gameswon--;
                }
                NL++;
                break;
            }
            case 'g': {
                find_max(ht_team, NL);
                NL++;
                break;
            }
            case 'x': {
                ht_dump_game(ht_game);
                ht_dump_team(ht_team);
                free(ht_game->entries);
                free(ht_team->entries);
                free(ht_game);
                free(ht_team);
                return 0;
            }
            default:
                break;
        }
    }
}