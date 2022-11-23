#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 1024                                                           /* maximum name size */
#define MAX_INPUT 3082                                                          /* maximum input size: 3 names + 2 scores + */
                                                                                /* whitespaces + ":" + command */
#define TABLE 23                                                                /* hashtables size */

#define MAX_GAMES 9999                                                          /* arbitrary value for maximum number of games */

int NL = 0;                                                                     /* input counter */


/* new type: Team, with the essential elements to define it */
typedef struct _team{
    char *name;                                                                 /* name of team */
    int wins;                                                                   /* number of times time has won */
} *Team;


/* new type: *Link_team, nodes for teams, to store in the hashtable */
typedef struct node_team{
    Team t;
    struct node_team *next;
} *Link_team;


/* new type: Game, with the essential elements to define it */
typedef struct _game{
    char *name;                                                                 /* name of game */
    Team t1;                                                                    /* pointer to team 1 */
    Team t2;                                                                    /* pointer to team 2 */
    int score_t1;                                                               /* goals scored by team 1 */
    int score_t2;                                                               /* goals scored by team 2 */
} *Game;


/* new type: Link_game, nodes for games, to store in the hashtable */
typedef struct node_game{
    Game g;
    struct node_game *next;
} *Link_game;


/* new type: Instruction, auxilliary structure to store values when creating a game */
typedef struct{
	int hash_index;                                                             /* hash value of game name */
    char game[MAX_INPUT];                                                       /* game name */
    char team1[MAX_INPUT];                                                      /* team 1 name */
    char team2[MAX_INPUT];                                                      /* team 2 name */
    int score1;                                                                 /* goals scored by team 1 */
    int score2;                                                                 /* goals scored by team 2 */
	int input_index;                                                            /* stores index to next part of the instruction */
} Instruction;


/* new type: Winners, stores maximum number of wins achieved by the teams and pointers to every team who achieve it */
typedef struct _winners{
    int max_wins;                                                               /* current maximum number of wins */
    int how_many_teams;                                                         /* how many teams have maximum number of wins */
    struct node_team *teams;                                                    /* pointers to teams with maximum number of wins */
} Winners;


int hash(char input[MAX_INPUT]);

Link_team insert_team(Link_team head, char input[MAX_INPUT]);

Team add_new_team(char input[MAX_INPUT]);

void list_teams(Link_team head);

int does_team_exist(char input[MAX_NAME], Link_team head);

Link_team locate_team(char input[MAX_NAME], Link_team head);

Instruction get_name_hash(char input[MAX_INPUT], int i);

Winners create_game(char input[MAX_INPUT], Link_team *heads_teams,
    Link_game *heads_games, Game *list_games, Winners winners);

Instruction get_score(char input[MAX_INPUT], Instruction reader);

Link_game store_game(Link_game head, Game new_game, Game *list_games);

int does_game_exist(char input[MAX_NAME], Link_game head);

void list_games_order(Game *list_games);

Link_game locate_game(char input[MAX_NAME], Link_game head);

Link_game delete_game(char input[MAX_NAME], Link_game head, Game *list_games);

void rectify_score(char input[MAX_NAME], Link_game *heads_games, int i);

Winners are_they_winners(int wins, Instruction reader, Link_team *heads_teams,
    Winners winners);

void list_winners(Winners winners);

/* void list_winners_by_name(Winners winners);  INCOMPLETO */


/* main: reads instructions from the standard input and calls the appropriate auxiliary function to execute what's asked */
int main(){
    char input[MAX_INPUT];                                                      /* array for the instructions read */
    Link_team *heads_teams;                                                     /* hashtable for teams */
    Link_game *heads_games;                                                     /* hashtable for games */
    int i;                                                                      /* auxilliary variable */

    Link_team aux_team = NULL;
    Link_game aux_game = NULL;
    Game *list_games;                                                           /* stores games by order of entry */

    Winners winners;                                                            /* structure to store winners */
    winners.max_wins = 0;                                                       /* initializes wins at 0 */
    winners.how_many_teams = 0;                                                 /* initializes tems with maximum wins at 0 */
    winners.teams = NULL;                                                       /* initializes list with no teams */

    list_games = can_fail_malloc(MAX_GAMES*sizeof(Game));                                /* initializes table to store games by order of entry */
    for (i = 0; i < MAX_GAMES; i++)
        list_games[i] = NULL;

    heads_teams = can_fail_malloc(TABLE*sizeof(Link_team));                              /* initializes the hashtable for teams */
    for (i = 0; i < TABLE; i++)
        heads_teams[i] = NULL;

    heads_games = can_fail_malloc(TABLE*sizeof(Link_game));                              /* initializes the hashtable for games */
    for (i = 0; i < TABLE; i++)
        heads_games[i] = NULL;

    do{                                                                         /* cycle that awaits a new instruction */
        fgets(input, MAX_INPUT, stdin);
        NL++;
        strtok(input, "\n");                                                    /* removes trailing new_line */
        switch(input[0]){                                                       /* evaluates the first char of the instruction */

            case('a'):                                                          /* adds a new game */
                i = strlen(input);
                input[i] = '\n';                                                /* adds new_line necessary for reading */
                winners = create_game(input, heads_teams, heads_games,
                    list_games, winners);                                       /* if successful, a new game is created and stored */
                break;

            case('l'):                                                          /* lists games by order of entry */
                list_games_order(list_games);
                break;

            case('p'):                                                          /* searches for game by name and prints it if it exists */
                i = hash(input+2);
                if (does_game_exist(input+2, heads_games[i])){
                    aux_game = locate_game(input+2, heads_games[i]);
                    printf("%d %s %s %s %d %d\n", NL, aux_game->g->name,
                        aux_game->g->t1->name,aux_game->g->t2->name,
                        aux_game->g->score_t1, aux_game->g->score_t2);
                }
                else
                    printf("%d Jogo inexistente.\n", NL);                       /* the game was not found */
                break;

            case('r'):                                                          /* searches for game by name and deletes it */
                i = hash(input+2);
                if (does_game_exist(input+2, heads_games[i])){
                    heads_games[i] = delete_game(input+2, heads_games[i],
                        list_games);
                }
                else
                    printf("%d Jogo inexistente.\n", NL);                       /* the game was not found */
                break;

            case('s'):                                                          /* searches for game by name and corrects its score */
                rectify_score(input, heads_games, 2);
                break;

            case('A'):                                                          /* adds a new team */
                i = hash(input+2);
                heads_teams[i] = insert_team(heads_teams[i], input+2);
                break;

            case('K'):                                                          /* lists teams found in a given index of the hashtable */
                i = *(input+2) - '0';                                           /* (actually only works up to index 9) */
                list_teams(heads_teams[i]);
                break;

            case('P'):                                                          /* searches for team by name and prints it if it exists */
                i = hash(input+2);
                if (does_team_exist(input+2, heads_teams[i])){
                    aux_team = locate_team(input+2, heads_teams[i]);
                    printf("%d %s %d\n", NL, aux_team->t->name,
                        aux_team->t->wins);
                }
                else
                    printf("%d Equipa inexistente.\n", NL);                     /* the team was not found */
                break;

            case('w'):                                                          /* lists teams that have maximun number of wins */
                list_winners(winners);

                break;

            /* INCOMPLETO
            case('g'):
                if (winners.max_wins > 0){
                    printf("NL Melhores %d.\n", winners.max_wins);
                    list_winners_by_name(winners);
                }
                break;
            */
        }
    } while (input[0] != 'x');                                                  /* terminates the program */



    for (i = 0; i < MAX_GAMES; i++)
        free(list_games[i]);
    free(list_games);

    for (i = 0; i < TABLE; i++)
        free(heads_teams[i]);
    free(heads_teams);

    for (i = 0; i < TABLE; i++)
        free(heads_games[i]);
    free(heads_games);

    return 0;
}

                                                                                /* COMENTARIOS NAO REVISTOS A PARTIR DAQUI */
int hash(char input[MAX_INPUT]){
    int index = 0;
    int aux = 127;
    int i = 0;
    for (; input[i] != '\0'; i++)
        index = (aux*index + input[i]) % TABLE;
    return index;
}


Link_team insert_team(Link_team head, char input[MAX_INPUT]){                   /* INSERE NO INICIO DA LISTA */
    Link_team temp = can_fail_malloc(sizeof(struct node_team));

    if (does_team_exist(input, head)){
        printf("%d Equipa existente.\n", NL);
        return head;
    }
    temp->t = add_new_team(input);
    temp->next = head;
    return temp;
}


Team add_new_team(char input[MAX_INPUT]){                                       /* DEVOLVE PONTEIRO PARA NOVA TEAM */
    Team temp = can_fail_malloc(sizeof(struct _team));
    temp->name = can_fail_malloc(sizeof(char)*(strlen(input)+1));
    strcpy(temp->name, input);
    temp->wins = 0;
    return temp;
}


void list_teams(Link_team head){                                                /* DEVOLVE AS EQUIPAS NUMA DAS heads_teams */
	Link_team temp;
	for (temp = head; temp != NULL; temp = temp->next)
		printf("%s\n", temp->t->name);
}


int does_team_exist(char input[MAX_NAME], Link_team head){                      /* ENCONRA = TRUE; ELSE = FALSE */
	Link_team temp;
	for (temp = head; temp != NULL; temp = temp->next)
		if (!strcmp (input, temp->t->name))                                     /* NEGATIVO PQ STRCMP DA RETURN A 0 SE FOREM IGUAIS */
			return 1;
	return 0;
}


Link_team locate_team(char input[MAX_NAME], Link_team head){
    Link_team temp;
    for (temp = head; temp != NULL; temp = temp->next)
        if (!strcmp (input, temp->t->name))                                     /* NEGATIVO PQ STRCMP DA RETURN A 0 SE FOREM IGUAIS */
            return temp;
    temp = NULL;                                                                /* EM PRINCIPIO NUNCA EH CHAMADA SE DER FAIL, MAS PRECISA */
    return temp;                                                                /* DISTO PARA NAO DAR ERRO */
}


Instruction get_game_info(char input[MAX_INPUT], int i){
    int j, k;
    char *temp;
    Instruction reader;
    reader.input_index = i;
    reader.score1 = -1;                                                         /* PARA O GET_SCORE FUNCIONAR BEM */

    for (j = 0; input[i] != ':' && input[i] != '\n'; i++, j++)                  /* VE ONDE ACABA O NOME */
        ;

    temp = can_fail_malloc((j+1)*sizeof(char));                                          /* ALOCA O ESPACO NECESSARIO PARA O NOME */
    k = j;                                                                      /* CONTADOR DECRESCENTE PARA COPIAR DE SEGUIDA */

    for (j = 0; k > 0; j++, reader.input_index++, k--)                          /* COPIA NOME GAME */
        temp[j] = input[reader.input_index];

    temp[j] = '\0';                                                             /* CHAR PARA TERMINAR STRING */

    reader.hash_index = hash(temp);                                             /* GUARDA O HASH DO NOME DO JOGO */
    strcpy(reader.game, temp);                                                  /* GUARDA O NOME DO JOGO */
    reader.input_index = (i+1);                                                 /* ONDE CONTINUA A INSTRUCAO */
    i = reader.input_index;


    for (j = 0; input[i] != ':' && input[i] != '\n'; i++, j++)                  /* VE ONDE ACABA O NOME */
        ;

    temp = can_fail_realloc(temp, (j+1)*sizeof(char));                                   /* REALOCA O ESPACO NECESSARIO PARA O NOME */
    k = j;                                                                      /* CONTADOR DECRESCENTE PARA COPIAR DE SEGUIDA */

    for (j = 0; k > 0; j++, reader.input_index++, k--)                          /* COPIA NOME TEAM1 */
        temp[j] = input[reader.input_index];

    temp[j] = '\0';                                                             /* CHAR PARA TERMINAR STRING */

    strcpy(reader.team1, temp);                                                 /* GUARDA O NOME DA TEAM1 */
    reader.input_index = (i+1);                                                 /* ONDE CONTINUA A INSTRUCAO */
    i = reader.input_index;

    for (j = 0; input[i] != ':' && input[i] != '\n'; i++, j++)                  /* VE ONDE ACABA O NOME */
        ;

    temp = can_fail_realloc(temp, (j+1)*sizeof(char));                                   /* REALOCA O ESPACO NECESSARIO PARA O NOME */
    k = j;                                                                      /* CONTADOR DECRESCENTE PARA COPIAR DE SEGUIDA */

    for (j = 0; k > 0; j++, reader.input_index++, k--)                          /* COPIA NOME TEAM2 */
        temp[j] = input[reader.input_index];

    temp[j] = '\0';                                                             /* CHAR PARA TERMINAR STRING */

    strcpy(reader.team2, temp);                                                 /* GUARDA O NOME DA TEAM2 */
    reader.input_index = (i+1);                                                 /* ONDE CONTINUA A INSTRUCAO */
    i = reader.input_index;


    reader = get_score(input, reader);                                          /* GUARDA SCORE1 */

    reader = get_score(input, reader);                                          /* GUARDA SCORE2 */

    return reader;

}


Instruction get_score(char input[MAX_INPUT], Instruction reader){
    int i = reader.input_index;
    int n = 0;

    while(input[i] != ':' && input[i] != '\n'){                                 /* GUARDA O SCORE */
        n = n*10 + input[i] - '0';
        i++;
    }

    if (reader.score1 == -1){                                                   /* SE FALHA EH PQ SCORE1 JA FOI TRATADO */
        reader.score1 = n;
        reader.input_index = (i+1);                                             /* ONDE CONTINUA A INSTRUCAO */
    }

    else
        reader.score2 = n;

    return reader;
}


Winners create_game(char input[MAX_INPUT], Link_team *heads_teams,
    Link_game *heads_games, Game *list_games, Winners winners){
    Instruction reader;
    Game new_game = can_fail_malloc(sizeof(struct _game));

    reader.input_index = 2;
    reader = get_game_info(input, reader.input_index);                          /* GUARDA TODA A INFO SOBRE O GAME A INSERIR */

    if (does_game_exist(reader.game, heads_games[reader.hash_index])){          /* VERIFICA SE GAME JA FOI CRIADO */
        printf("%d Jogo existente.\n", NL);
        free(new_game);
        return winners;
    }

    if (!does_team_exist(reader.team1, heads_teams[hash(reader.team1)])){       /* VERIFICA SE TEAM1 JA FOI CRIADA */
        printf("%d Equipa inexistente.\n", NL);
        free(new_game);
        return winners;
    }

    if (!does_team_exist(reader.team2, heads_teams[hash(reader.team2)])){       /* VERIFICA SE TEAM2 JA FOI CRIADA */
        printf("%d Equipa inexistente.\n", NL);
        free(new_game);
        return winners;
    }

    new_game->name = can_fail_malloc(sizeof(char)*(strlen(reader.game)+1));
    strcpy(new_game->name, reader.game);                                        /* GUARDA O NOME DO JOGO */

    new_game->t1 = (locate_team(reader.team1,
        heads_teams[hash(reader.team1)]))->t;                                   /* GUARDA ENDERECO PARA TEAMS */
    new_game->t2 = (locate_team(reader.team2,
        heads_teams[hash(reader.team2)]))->t;

    new_game->score_t1 = reader.score1;                                         /* GUARDA SCORES */
    new_game->score_t2 = reader.score2;

    if (new_game->score_t1 > new_game->score_t2){                               /* ACTUALIZA WINS */
        new_game->t1->wins++;
        winners = are_they_winners(new_game->t1->wins, reader, heads_teams,
            winners);
    }

    else
        if (new_game->score_t2 > new_game->score_t1){
            new_game->t2->wins++;
            winners = are_they_winners(new_game->t2->wins, reader, heads_teams,
                winners);
        }

    heads_games[reader.hash_index] = store_game(heads_games[reader.hash_index],
        new_game, list_games);                                                  /* GUARDA O LINK DO JOGO NA HASHTABLE */

    return winners;
}


Link_game store_game(Link_game head, Game new_game, Game *list_games){
        Link_game temp = can_fail_malloc(sizeof(struct node_game));                      /* MEMORIA NECESSARIA PARA O NOVO JOGO */
        int i;

        temp->g = new_game;                                                     /* GUARDA O LINK DO JOGO NA HASHTABLE */
        temp->next = head;                                                      /* ACTUALIZA HEAD DA HASHTABLE */

        for (i = 0; list_games[i] != NULL; i++)
            ;

        list_games[i] = new_game;
        return temp;
}


int does_game_exist(char input[MAX_NAME], Link_game head){                      /* ENCONRA = TRUE; ELSE = FALSE */
	Link_game temp;
	for (temp = head; temp != NULL; temp = temp->next)
		if (!strcmp (input, temp->g->name))                                     /*   NEGATIVO PQ STRCMP DA RETURN A 0 SE FOREM IGUAIS  */
			return 1;
	return 0;
}


void list_games_order(Game *list_games){
    int i;
    for (i = 0; list_games[i] != NULL; i++)
        printf("%d %s %s %s %d %d\n", NL, list_games[i]->name,
            list_games[i]->t1->name, list_games[i]->t2->name,
            list_games[i]->score_t1, list_games[i]->score_t2);
}


Link_game locate_game(char input[MAX_NAME], Link_game head){

    Link_game temp;
    for (temp = head; temp != NULL; temp = temp->next)
        if (!strcmp (input, temp->g->name))                                     /* NEGATIVO PQ STRCMP DA RETURN A 0 SE FOREM IGUAIS */
            return temp;
    temp = NULL;                                                                /* EM PRINCIPIO NUNCA EH CHAMADA SE DER FAIL, MAS PRECISA */
    return temp;                                                                /* DISTO PARA NAO DAR ERRO */
}


Link_game delete_game(char input[MAX_NAME], Link_game head, Game *list_games){
    Link_game temp, prev;
    int i;

    for (temp = head, prev = NULL; temp != NULL; prev = temp,
        temp = temp->next){
        if(strcmp(temp->g->name, input) == 0){
            if(temp == head)
                head = temp->next;
            else
                prev->next = temp->next;

            for (i = 0; list_games[i] != NULL; i++)
                if(strcmp(list_games[i]->name, input) == 0){
                    for ( ; list_games[i] != NULL; i++)                         /* SUBSTITUI A PARTIR DO JOGO A APAGAR */
                        list_games[i] = list_games[i+1];
                    list_games[i] = NULL;                                       /* APAGA O ULTIMO */
                }

            if (temp->g->score_t1 > temp->g->score_t2)                          /* SE TEAM1 VENCEU */
                temp->g->t1->wins--;

            else
                if (temp->g->score_t1 < temp->g->score_t2)                      /* SE TEAM2 VENCEU */
                    temp->g->t2->wins--;

            free(temp->g->name);
            free(temp->g);
            free(temp);
        }
    }
    return head;
}


void rectify_score(char input[MAX_NAME], Link_game *heads_games, int i){
    int j, k, hash_temp, len;
    char *temp;
    Link_game temp_game;
    Instruction reader;
    reader.score1 = -1;                                                         /* PARA O GET_SCORE FUNCIONAR BEM */
    reader.score2 = 0;

    for (j = 0; input[i] != ':'; i++, j++)                                      /* VE ONDE ACABA O NOME */
        ;

    temp = can_fail_malloc((j+1)*sizeof(char));                                          /* ALOCA O ESPACO NECESSARIO PARA O NOME */
    k = j;                                                                      /* CONTADOR DECRESCENTE PARA COPIAR DE SEGUIDA */
    reader.input_index = i+1;

    for (i = 2, j = 0; k > 0; j++, i++, k--)                                    /* COPIA NOME GAME */
        temp[j] = input[i];

    temp[j] = '\0';

    hash_temp = hash(temp);

    temp_game = locate_game(temp, heads_games[hash_temp]);

    if (!does_game_exist(temp_game->g->name, heads_games[hash_temp])){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    reader = get_score(input, reader);                                          /* GUARDA SCORE1 */

    j = reader.input_index;

    len = strlen(input);

    while(input[j] != ':' && j < len){                                          /* SE USAR GET_SCORE PARA O SCORE2 DA ERRO */
        reader.score2 = reader.score2*10 + input[j] - '0';                      /* GUARDA SCORE2 */
        j++;
    }

    if (temp_game->g->score_t1 > temp_game->g->score_t2){                       /* SE ORIGINALMENTE TEAM1 VENCEU TEAM 2 */
        if (reader.score1 < reader.score2){                                     /* SE AGORA TEAM2 VENCE TEAM 1*/
                temp_game->g->t1->wins--;
                temp_game->g->t2->wins++;
        }
        else
            if (reader.score1 == reader.score2)
                temp_game->g->t1->wins--;
    }

    else{
        if (temp_game->g->score_t1 < temp_game->g->score_t2){                   /* SE ORIGINALMENTE TEAM2 VENCEU TEAM 1 */
            if (reader.score1 > reader.score2){                                 /* SE AGORA TEAM1 VENCE TEAM 2*/
                    temp_game->g->t1->wins++;
                    temp_game->g->t2->wins--;
                }
                else
                    if (reader.score1 == reader.score2)
                        temp_game->g->t2->wins--;
        }
        else                                                                    /* SE ORIGINALMENTE EMPATARAM */
            if (reader.score1 > reader.score2){                                 /* SE AGORA TEAM1 VENCE TEAM 2*/
                    temp_game->g->t1->wins++;
                }
                else
                    if (reader.score1 < reader.score2)                          /* SE AGORA TEAM2 VENCE TEAM 1*/
                        temp_game->g->t2->wins++;

    }
    temp_game->g->score_t1 = reader.score1;                                     /* GUARDA NOVOS SCORES */
    temp_game->g->score_t2 = reader.score2;
}


Winners are_they_winners(int wins, Instruction reader, Link_team *heads_teams,
    Winners winners){
    Link_team temp_head;

    if (wins == winners.max_wins){;                                             /* ADICIONA A WINNERS */
        temp_head = winners.teams;
        winners.teams = (locate_team(reader.team1,
            heads_teams[hash(reader.team1)]));
        winners.teams->next = temp_head;
        winners.how_many_teams++;
    }

    else
        if (wins > winners.max_wins){;                                          /* NOVO WINNER */
            free(winners.teams);
            winners.teams = (locate_team(reader.team1,
                heads_teams[hash(reader.team1)]));
            winners.teams->next = NULL;
            winners.max_wins = wins;
            winners.how_many_teams = 1;
        }
    return winners;
}


void list_winners(Winners winners){
    Link_team temp;
    for (temp = winners.teams; temp != NULL; temp = temp->next){
        printf("%s\n", temp->t->name);
    }
}


/* INCOMPLETO

void list_winners_by_name(Winners winners){

    Winners printed;

    Link_team temp, head, aux, temp_printed, temp2;

    int i;

    printed.teams = NULL;

    head = winners.teams;
    temp = head;

    for ( ; temp != NULL; temp = temp->next){

        for (temp2 = printed.teams; temp2 != NULL; temp2 = temp2->next){
            if(strcmp(temp->t->name, temp2->t->name) == 0){
                printf("%s AQUI4.\n", temp->t->name);
                break;
            }
        }
        printf("%s AQUI3.\n", temp->t->name);
        aux = temp->next;
        for(i = 0; aux != NULL; i++){
    	       if(temp->t->name[i] < aux->t->name[i])
                    aux = aux->next;
                else
                    if(temp->t->name[i] > aux->t->name[i]){
                        temp = aux;
                        aux = temp->next;
                        i = 0;
                    }
        }

        printf("NL * %s\n", temp->t->name);

        temp_printed = printed.teams;
        printed.teams = temp;
        printed.teams->next = temp_printed;
        temp = head;

    }
}

*/
