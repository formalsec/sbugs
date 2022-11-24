#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "tipos.h"

/******************************************************************************
 * Funcoes:
******************************************************************************/

/********************************** Game *************************************/

/* new_game: Funcao que cria um novo jogo, e devolve um ponteiro para o mesmo. 
 nome: parametro que representa o nome do jogo.
 equipa1, equipa2: parametros que representam os nomes das equipas do jogo.
 score1, score2: parametros que representam as pontuacoes finais das equipas. */
Game* new_game(char *nome, char *equipa1, char *equipa2, int score1, int score2) {
    Game *jogo;

    jogo = (Game *) can_fail_malloc(sizeof(Game));
    jogo->name = (char *) can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(jogo->name, nome);
    jogo->team1 = (char *) can_fail_malloc(sizeof(char) * (strlen(equipa1) + 1));
    strcpy(jogo->team1, equipa1);
    jogo->team2 = (char *) can_fail_malloc(sizeof(char) * (strlen(equipa2) + 1));
    strcpy(jogo->team2, equipa2);
    jogo->score_team1 = score1;
    jogo->score_team2 = score2;

    return jogo;
}

/* change_score: Funcao que altera a pontuacao de um jogo existente. 
 jogo: parametro que representa o ponteiro para o jogo.
 score1, score2: parametros que representam as novas pontuacoes. */
void change_score(Game *jogo, int score1, int score2) {
    jogo->score_team1 = score1;
    jogo->score_team2 = score2;
}

/* key_game: Funcao que acede e devolve a chave que identifica o jogo numa 
tabela de dispersao.
 item: parametro que representa o ponteiro para o no da lista com o jogo. */
char* key_game(void *item) {
    Node_list *no = (Node_list *) item;
    Game *jogo = item_list(no);

    return jogo->name;
}

/* print_game_list: Funcao que imprime todos os elementos de um jogo numa lista. 
 item: parametro que representa o ponteiro para o jogo. */
void print_game_list(void *item) {
    Game *jogo = (Game *) item;

    printf("%s %s %s %d %d\n", jogo->name, jogo->team1, jogo->team2,
     jogo->score_team1, jogo->score_team2);
}

/* print_game: Funcao que imprime todos os elementos de um jogo. 
 jogo: parametro que representa o ponteiro para o jogo. */
void print_game(Game *jogo) {
    printf("%s %s %s %d %d\n", jogo->name, jogo->team1, jogo->team2,
     jogo->score_team1, jogo->score_team2);
}

/* free_game: Funcao que liberta toda a memoria associada a um jogo. 
 item: parametro que representa o ponteiro para o jogo. */
void free_game(void *item) {
    Game *jogo = (Game *) item;
    
    free(jogo->name);
    free(jogo->team1);
    free(jogo->team2);
    free(jogo);
}

/********************************** Team *************************************/

/* new_team: Funcao que cria uma nova equipa, e devolve o ponteiro para a mesma. 
 nome: parametro que representa o nome da equipa. */
Team* new_team(char *nome) {
    Team *equipa;

    equipa = (Team *) can_fail_malloc(sizeof(Team));
    equipa->name = (char *) can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(equipa->name, nome);
    equipa->wins = 0;

    return equipa;
}

/* add_win: Funcao que adiciona uma vitoria 'a equipa. 
 equipa: parametro que representa o ponteiro para a equipa. */
void add_win(Team *equipa) {
    equipa->wins += 1;
}

/* remove_win: Funcao que subtrai uma vitoria 'a equipa. 
 equipa: parametro que representa o ponteiro para a equipa. */
void remove_win(Team *equipa) {
    equipa->wins -= 1;
}

/* key_team_bt: Funcao que acede e devolve a chave que identifica a equipa numa 
arvore binaria.
 item: parametro que representa o ponteiro para a equipa. */
int key_team_bt(void *item) {
    Team *equipa = (Team *) item;

    return equipa->wins;
}

/* key_team_lp: Funcao que acede e devolve a chave que identifica a equipa numa 
tabela de dispersao.
 item: parametro que representa o ponteiro para a equipa. */
char* key_team_lp(void *item) {
    Team *equipa = (Team *) item;

    return equipa->name;
}

/* print_team_bt: Funcao que imprime o nome de uma equipa. 
 equipa: parametro que representa o ponteiro para a equipa. */
void print_team_bt(Team *equipa) {
    printf("* %s\n", equipa->name);
}

/* print_team_lp: Funcao que imprime o nome e o numero de vitorias de uma equipa. 
 item: parametro que representa o ponteiro para a equipa. */
void print_team_lp(void *item) {
    Team *equipa = (Team *) item; 

    printf("%s %d\n", equipa->name, equipa->wins);
}

/* free_team: Funcao que liberta toda a memoria associada a uma equipa. 
 item: parametro que representa o ponteiro para a equipa. */
void free_team(void *item) {
    Team *equipa = (Team *) item; 

    free(equipa->name);
    free(equipa);
}

/************* Tabela de dispersao por procura linear (Geral) ****************/

/* hash: Funcao que gera e distribui indices para uma tabela de dispersao, e 
devolve esse mesmo indice
 chave: parametro que representa a chave do elemento.
 tamanho: parametro que representa o tamanho da tabela de dispersao. */
long hash(void *chave, long tamanho) {
    long indice, a = 31415, b = 27183;
    char *nome = (char *) chave;

    for (indice = 0; *nome != '\0'; nome++, a = a * b % (tamanho - 1)) {
        indice = (a * indice + *nome) % tamanho;
    }

    return indice;
}
