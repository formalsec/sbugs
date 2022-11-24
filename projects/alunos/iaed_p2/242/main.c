#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "team_functions.h"
#include "game_functions.h"

int main(){
    int bol = 1;

    /*Variaveis onde ficam guardados os elementos do input*/
    char name[MAX_INPUT];
    char t1[MAX_INPUT];
    char t2[MAX_INPUT];
    int g_t1;
    int g_t2;

    int NL = 1;

    team* hash_table_team[TABLE_SIZE]; /*Hashtable das equipas*/
    game* hash_table_game[TABLE_SIZE]; /*Hashtable dos jogos*/
    team* max_teams; /*Cabeca da lista temporaria onde sao inseridas as equipas com numero maximo 
    de vitorias*/
    nodeGame* game_order; /*Cabeca da lista de ponteiros de todos os jogos inseridos*/
    

    init_hash_table_team(hash_table_team); /*Ambas as hashtables sao iniciadas*/
    init_hash_table_game(hash_table_game);

   
    game_order= NULL; /*Ambas as cabecas das listas sao iniciadas*/
    max_teams = NULL;


    while(bol){
        char cmd = getchar();
        switch(cmd){
            case 'a':
                getchar();
                scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, t1, t2, &g_t1, &g_t2);
                cmd_a(name, t1, t2, g_t1, g_t2, NL, hash_table_game, hash_table_team, &game_order);
                NL++;
                break; 
            case 'A':
                getchar();
                scanf("%[^:\n]", name);
                cmd_A(name, NL, hash_table_team);
                NL++;
                break;
            case 'p':
                getchar();
                scanf("%[^:\n]", name);
                cmd_p(name, NL, hash_table_game);
                NL++;
                break;
            case 'P':
                getchar();
                scanf("%[^:\n]", name);
                cmd_P(name, NL, hash_table_team);
                NL++;
                break;
            case 'l':
                reverse(&game_order);
                cmd_l(game_order, NL);
                reverse(&game_order);
                NL++;
                break;
            case 's':
                getchar();
                scanf("%[^:\n]:%d:%d", name, &g_t1, &g_t2);
                cmd_s(hash_table_team, hash_table_game, name, g_t1, g_t2, NL);
                NL++;
                break;
            case 'r':
                getchar();
                scanf("%[^:\n]", name);
                cmd_r(hash_table_team, hash_table_game, name, NL, &game_order);
                NL++;
                break;
            case 'g':
                getchar();
                cmd_g(&max_teams, NL, hash_table_team);
                NL++;
                break;
            case 'x':
                bol = 0;
                destroy_games(hash_table_game); /*Quando o programa e terminado liberta se toda 
                a memoria*/
                destroy_teams(hash_table_team);
                destroy_order(&game_order);
                break;
        }
    }
    return 0;
}
