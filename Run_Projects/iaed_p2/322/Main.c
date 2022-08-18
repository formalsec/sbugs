#include "main.h"

/* Read first part of the command from user and send it to the parsing function */
int main(){
    int command, counter = 1;
    Hash_Array *game_hash, *team_hash;
    Node_ptr top_game_list;

    game_hash = hashtable_init(ARRAY_SIZE);
    team_hash = hashtable_init(ARRAY_SIZE);
    top_game_list = init();


    while(1){
        /* printf("waiting for next command\n"); */
        command = getchar();
        top_game_list = parse_instructions(command,counter++, game_hash, team_hash, top_game_list);
    }
    return 0;
}

/* Receives a command and parses said command, calling the respective
fucntion and takes care any potential "junk" from the input stream */
Node_ptr parse_instructions(int command, int counter, Hash_Array *game_hash, Hash_Array *team_hash,  Node_ptr top_game_list){
    int junk_flag = 0;  /* Flag active when function receives arguments */
    Node_ptr aux;
    getchar(); /* Junk */
    switch(command){
    case 65:
        junk_flag = comando_A(counter,team_hash);
        break;
    case 80:
        junk_flag = comando_P(counter,team_hash);
        break;
    case 97:
        aux = comando_a(counter,game_hash,team_hash,top_game_list);
        if(aux != NULL){
            top_game_list = aux;
        }
        junk_flag = 1;
        break;
    case 103:
        junk_flag = comando_g(counter, team_hash);
        break;
    case 108:
        junk_flag = comando_l(counter, game_hash, top_game_list);
        break;
    case 112:
        junk_flag = comando_p(counter, game_hash);
        break;
    case 114:
        top_game_list = comando_r(counter, game_hash, team_hash, top_game_list);
        junk_flag = 1;
        break;
    case 115:
        junk_flag = comando_s(counter, game_hash, team_hash);
        break;
    case 120:
        exit_program(team_hash, game_hash, top_game_list);
    
    default:
        break;
    }

    if (junk_flag){
        getchar();
    }

    return top_game_list;
}

/* Exits the program, and frees all the variables */
void exit_program(Hash_Array *team_hash, Hash_Array *game_hash, Node_ptr top_game_list){
    hashtable_free_all(team_hash);
    hashtable_free_all(game_hash);
    clear_all(top_game_list);

    exit(0);


}







