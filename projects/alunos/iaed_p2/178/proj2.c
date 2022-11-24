#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1024



typedef struct team {
    char team_name[MAX_CHAR];
    int wins;
} *pointer_team;

typedef struct node_team {
    pointer_team t;
    struct node_team *next_team;
} *link_team;

link_team *heads_team;



typedef struct game {
    char game_name[MAX_CHAR];
    char team1_name[MAX_CHAR];
    char team2_name[MAX_CHAR];
    char winner[MAX_CHAR];
    int score1;
    int score2;
} *pointer_game;

typedef struct node_game {
    pointer_game g;
    struct node_game *next_game;
} *link_game;

link_game *heads_game;



/*funcao que recebe um nome e retorna um indice na hash table*/

int hash (char *v, int dim) {

    int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a * b % (dim - 1))

        h = (a*h + *v) % dim;

    return h;
}



/*funcao que inicializa a hash table das equipas*/

void init_hash_teams (int dim) {

    int index;
    heads_team = (link_team*) can_fail_malloc(dim * sizeof(link_team));

    for (index = 0; index < dim ; index++) {

        heads_team[index] = NULL;

    }
}



/*funcao que inicializa a hash table dos jogos*/

void init_hash_games (int dim) {

    int index;
    heads_game = (link_game*) can_fail_malloc(dim * sizeof(link_game));

    for (index = 0; index < dim ; index++) {

        heads_game[index] = NULL;

    }
}



/*funcao que insere uma equipa no inicio de uma lista de equipas*/

link_team insert_beggin_list_team (link_team head, char* name) {

    link_team aux = (link_team) can_fail_malloc(sizeof(struct node_team));
    aux->t = (pointer_team) can_fail_malloc(sizeof(struct team));
    strcpy(aux->t->team_name, name);
    aux->t->wins = 0;
    aux->next_team = head;

    return aux;
}



/*funcao que recebe um nome de uma equipa e verifica se ela se encontra numa 
    dada lista de equipas da hash*/

link_team search_team (link_team head, char* name) {

    link_team aux;

    for (aux = head; aux != NULL; aux = aux->next_team) {

        if (strcmp(aux->t->team_name, name) == 0) {

            return aux;

        }
    } 

    return NULL;

}



/*funcao que adiciona uma nova equipa*/

void add_team (int line, int dim) {

    int index;
    char name[MAX_CHAR];
    scanf(" %[^:\n]", name);
    index = hash(name, dim);

    if (search_team(heads_team[index], name) == NULL) { 

        /*se a equipa nao estiver nesse espaco, adiciona se ah hash table de 
            equipas*/

        heads_team[index] = insert_beggin_list_team(heads_team[index], name);

    } 

    else {

        printf("%d Equipa existente.\n", line);

    }
}



/*funcao que procura uma equipa dado um nome*/

void look_for_team (int line, int dim) {

    int index;
    char name[MAX_CHAR];
    scanf(" %[^:\n]", name);
    index = hash(name, dim);

    if (search_team(heads_team[index], name) != NULL) {

        /*caso a equipa se encontre na hash table de equipas*/

        printf("%d %s %d\n", line, heads_team[index]->t->team_name, 
                             heads_team[index]->t->wins);

    }

    else {

        printf("%d Equipa inexistente.\n", line);

    }

}



/*funcao que insere um jogo no inicio de uma hash list de jogos*/

link_game insert_beggin_list_game (link_game head, char* name_of_game, 
                                  char* team1_name, char* team2_name, 
                                  int goals1, int goals2, char* winner) {

    link_game aux = (link_game) can_fail_malloc(sizeof(struct node_game));
    aux->g = (pointer_game) can_fail_malloc(sizeof(struct game));
    strcpy(aux->g->game_name, name_of_game);
    strcpy(aux->g->team1_name, team1_name);
    strcpy(aux->g->team2_name, team2_name);
    strcpy(aux->g->winner, winner);
    aux->g->score1 = goals1;
    aux->g->score2 = goals2;
    aux->next_game = head;

    return aux;
}



/*funcao que recebe um nome de um jogo e verifica se se encontra numa dada lista 
    de jogos da hash*/

link_game search_game (link_game head, char* name) {

    link_game aux;

    for (aux = head; aux != NULL; aux = aux->next_game) {

        if (strcmp(aux->g->game_name, name) == 0) {

            return aux;

        }
    } 

    return NULL;

}



/*funcao que recebe um jogo e uma dada lista de jogos da hash table de jogos e 
    apaga o jogo dado da lista*/

link_game delete_game (link_game head, char *name) {

    link_game aux, prev;

    for (aux = head, prev = NULL; aux != NULL; prev = aux, aux = aux->next_game) {

        if (strcmp(aux->g->game_name, name) == 0) {

            if (aux == head) {

                head = aux->next_game;

            }

            else {

                prev->next_game = aux->next_game;

            }
            
            free(aux->next_game);
            free(aux);

            break;
        }
    }

    return head;

}



/*funcao que adiciona um novo jogo*/

void add_game (int line, int vector_position, int dim, int *games_index) {

    int index_game, index_team1, index_team2, score1, score2;

    char game_name[MAX_CHAR], team1_name[MAX_CHAR], team2_name[MAX_CHAR], 
         tie[MAX_CHAR];

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", game_name, team1_name, team2_name, 
                                            &score1, &score2);

    index_game = hash(game_name, dim);
    index_team1 = hash(team1_name, dim);
    index_team2 = hash(team2_name, dim);

    if (search_game(heads_game[index_game], game_name) == NULL) { 

        /*se o jogo nao estiver nesse espaco, adiciona se ah hash table de jogos*/

        if (search_team(heads_team[index_team1], team1_name) != NULL && 
            search_team(heads_team[index_team2], team2_name) != NULL) {
            
            /*procurar se existe algum vencedor do jogo*/
            
            if (score1 > score2) { 

                heads_game[index_game] = insert_beggin_list_game(heads_game[index_game],
                                                                 game_name, 
                                                                 team1_name, 
                                                                 team2_name, 
                                                                 score1, 
                                                                 score2, 
                                                                 team1_name);


                heads_team[index_team1]->t->wins++;
                
            }
            else if (score1 == score2) {

                strcpy(tie, "tie");

                heads_game[index_game] = insert_beggin_list_game(heads_game[index_game], 
                                                                 game_name, 
                                                                 team1_name, 
                                                                 team2_name, 
                                                                 score1, 
                                                                 score2, 
                                                                 tie);
                
            }
            else {

                heads_game[index_game] = insert_beggin_list_game(heads_game[index_game], 
                                                                 game_name, 
                                                                 team1_name, 
                                                                 team2_name, 
                                                                 score1, 
                                                                 score2, 
                                                                 team2_name);

                heads_team[index_team2]->t->wins++;
                
            }

            games_index[vector_position] = index_game;

        }
        
        else {

            printf("%d Equipa inexistente.\n", line);

        }

    }

    else {

        printf("%d Jogo existente.\n", line);

    }
}



/*funcao que procura um jogo com o nome dado*/

void look_for_game (int line, int dim) {

    int index;
    char name[MAX_CHAR];
    scanf(" %[^:\n]", name);
    index = hash(name, dim);

    if (search_game(heads_game[index], name) != NULL) { 

        /*caso o jogo se encontre na hash table de jogos*/

        printf("%d %s %s %s %d %d\n", line, name, 
                                      heads_game[index]->g->team1_name, 
                                      heads_game[index]->g->team2_name, 
                                      heads_game[index]->g->score1, 
                                      heads_game[index]->g->score2);

    }

    else {

        printf("%d Jogo inexistente.\n", line);

    }
}



/*funcao que recebe um indice e altera o conteudo em games_index na 
    posicao dada pelo indice recebido*/

void change_vector_content (int index, int vector_counter, int* games_index) {

    int i;

    for (i = 0; i<= vector_counter; i++) {

        if (games_index[i] == index) { 

            /*caso o jogo a analisar seja o mesmo que se pretende remover*/

            games_index[i] = -1;

            break;

        }
    }
}



/*funcao que apaga um jogo dado um nome*/

void remove_game (int line, int vector_counter, int dim, int* games_index) {

    int index, index_team1, index_team2;
    char game_name[MAX_CHAR];
    scanf(" %[^:\n]", game_name);
    index = hash(game_name, dim);

    if (search_game(heads_game[index], game_name) != NULL) {

        /*procurar o vencedor do jogo que sera removido*/ 

        if (strcmp(heads_game[index]->g->winner, 
                   heads_game[index]->g->team1_name) == 0) {

            index_team1 = hash(heads_game[index]->g->team1_name, dim);
            heads_team[index_team1]->t->wins--; 
               
        }

        else if (strcmp(heads_game[index]->g->winner, 
                        heads_game[index]->g->team2_name) == 0) {

            index_team2 = hash(heads_game[index]->g->team2_name, dim);
            heads_team[index_team2]->t->wins--;

        }

        delete_game(heads_game[index], game_name);

        change_vector_content(index, vector_counter, games_index); 

    }

    else {

        printf("%d Jogo inexistente.\n", line);

    }
}



/* funcao que altera o resultado de um jogo dado o nome*/

void change_score (int line, int dim) {

    int index, goals1, goals2, index_winner, index_loser, index_old_winner;
    char game_name[MAX_CHAR];
    scanf(" %[^:\n]:%d:%d", game_name, &goals1, &goals2);
    index = hash(game_name, dim);

    if (search_game(heads_game[index], game_name) != NULL) {

        heads_game[index]->g->score1 = goals1;
        heads_game[index]->g->score2 = goals2;

        if (goals1 > goals2) {

            /*caso a team1 seja a vencedora do jogo*/

            if (strcmp(heads_game[index]->g->winner, 
                       heads_game[index]->g->team1_name) != 0 

                &&  

                strcmp(heads_game[index]->g->winner, "tie") != 0) {

                /*caso a team2 seja a vencedora antes da mudanca de resultado*/

                strcpy(heads_game[index]->g->winner, 
                       heads_game[index]->g->team1_name);

                index_winner = hash(heads_game[index]->g->team1_name, dim);
                index_loser = hash(heads_game[index]->g->team2_name, dim);
                heads_team[index_winner]->t->wins++;
                heads_team[index_loser]->t->wins--;

            }

            else if (strcmp(heads_game[index]->g->winner, "tie") == 0) {

                /*caso nao houvesse nenhum vencedor antes da mudanca de 
                    resultado*/

                strcpy(heads_game[index]->g->winner, heads_game[index]->g->team1_name);
                index_winner = hash(heads_game[index]->g->team1_name, dim);
                heads_team[index_winner]->t->wins++;

            }
        }

        else if (goals2 > goals1) {

            /*caso a team2 seja a vencedora do jogo*/

            if (strcmp(heads_game[index]->g->winner, 
                       heads_game[index]->g->team2_name) != 0 

                && 

                strcmp(heads_game[index]->g->winner, "tie") != 0) {

                /*caso a team1 seja a vencedora antes da mudanca de resultado*/

                strcpy(heads_game[index]->g->winner, heads_game[index]->g->team2_name);
                index_winner = hash(heads_game[index]->g->team2_name, dim);
                index_loser = hash(heads_game[index]->g->team1_name, dim);
                heads_team[index_winner]->t->wins++;
                heads_team[index_loser]->t->wins--;

            }

            else if (strcmp(heads_game[index]->g->winner, "tie") == 0) {

                /*caso nao houvesse nenhum vencedor antes da mudanca de resultado*/

                strcpy(heads_game[index]->g->winner, heads_game[index]->g->team2_name);
                index_winner = hash(heads_game[index]->g->team2_name, dim);
                heads_team[index_winner]->t->wins++;

            }
        }

        else {

            if (strcmp(heads_game[index]->g->winner, 
                       heads_game[index]->g->team1_name) != 0 
            
                && 
                
                strcmp(heads_game[index]->g->winner, "tie") != 0) {

                /*caso a team2 seja a vencedora antes da mudanca de resultado*/

                strcpy(heads_game[index]->g->winner, "tie");
                index_old_winner = hash(heads_game[index]->g->team2_name, dim);
                heads_team[index_old_winner]->t->wins--;

            }

            else if (strcmp(heads_game[index]->g->winner, 
                            heads_game[index]->g->team2_name) != 0 
            
                    && 
                    
                    strcmp(heads_game[index]->g->winner, "tie") != 0) {

                /*caso a team1 seja a vencedora antes da mudanca de resultado*/

                strcpy(heads_game[index]->g->winner, "tie");
                index_old_winner = hash(heads_game[index]->g->team1_name, dim);
                heads_team[index_old_winner]->t->wins--;

            }
        }
    }

    else {

        printf("%d Jogo inexistente.\n", line);

    }
}



/*funcao que lista todos os jogos introduzidos*/

void print_games (int line, int max_index, int* games_index) {

    int i;

    for (i = 0; i<= max_index ; i++) {

        if (games_index[i] != -1 && heads_game[games_index[i]] != NULL) { 

            printf("%d %s %s %s %d %d\n", 
                line, 
                heads_game[games_index[i]]->g->game_name, 
                heads_game[games_index[i]]->g->team1_name, 
                heads_game[games_index[i]]->g->team2_name, 
                heads_game[games_index[i]]->g->score1, 
                heads_game[games_index[i]]->g->score2);
        
        }    

    }
}



/*funcao que encontra as equipas que ganharam mais jogos e lista por ordem          
lexicografica*/

void print_teams (int line, int max_teams) {

    if (max_teams > 0) {

        printf("%d Melhores", line);

    }

}





int main () {

    int car, line = 1, index_game = 0, i, index_team = 0, dim = 10007, 
        size_games = 10000;

    int* games_index = (int*)  can_fail_malloc(size_games * sizeof(int));

    int *aux = games_index;
    
    init_hash_teams(dim);

    init_hash_games(dim);

    while((car = getchar()) != 'x') {

        switch(car) {

            case 'A':

                add_team(line, dim);
                line++;
                index_team++;

                break;

            case 'P':

                look_for_team(line, dim);
                line++;

                break;

            case 'a':

                add_game(line, index_game, dim, games_index);
                line++;
                size_games++;
                index_game++;

                break;

            case 'p':

                look_for_game(line, dim);
                line++;

                break;

            case 's':

                change_score(line, dim);
                line++;

                break;

            case 'r':

                remove_game(line, index_game, dim, games_index);
                line++;

                break;

            case 'l':

                print_games(line, index_game, games_index);
                line++;

                break;

            case 'g':

                print_teams(line, index_team);
                line++;

                break;
        }
    }

    for (i = 0; i < dim; i++) {

        free(heads_team[i]);
        free(heads_game[i]);

    }

    free(heads_game);
    free(heads_team);
    free(aux);
    
    return 0;
}
