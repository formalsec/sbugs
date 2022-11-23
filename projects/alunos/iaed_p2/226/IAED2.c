#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define hash(A,B) (A%B)
#define MAXNAME 1023
#define HASHTABLESIZE 619
#define MAXINPUT 3080
#define SCORE 2


typedef struct Game {
    char *name, *team_one, *team_two;
    int score[SCORE];
    struct Game *next;
} game;

typedef struct node_t {
    game *game;
    struct node_t *next;
} Node;

typedef struct Team{
    char *team_name;
    int wins;
    struct Team *next;
} team;

int teams_counter = 0, command_count = 0;
static team *teams[HASHTABLESIZE] = {0};
static game *hashtable[HASHTABLESIZE] = {0};
static Node *head = NULL;
static Node *tail = NULL;
static team *team_head = NULL;
static team *team_tail = NULL;

/* funcao que inicializa tanto a hashtable dos jogos como a das equipas */
void initializeHashTables() {
    int i;
    for (i = 0; i < HASHTABLESIZE; i++) {
        hashtable[i] = NULL;
        teams[i] = NULL;
    }
}

/* funcao que isere na lista das equipas a equipa fornecida */
void insertTeamList(team *t){
    team *temp;

    temp = t;
    temp->next = NULL;

    if(team_head == NULL){
        team_head = temp;
        team_tail = temp;
    }
    else {
        team_tail->next = temp;
        team_tail = temp;
    }
}

/* funcao que isere na lista dos jogos o jogo fornecido */
void insertList(game *g){
    Node *temp = (Node*)can_fail_malloc(sizeof(Node));

    temp->game = g;
    temp->next = NULL;

    if(head == NULL){
        head = temp;
        tail = temp;
    }
    else {
        tail->next = temp;
        tail = temp;
    }
}

/* funcao que insere na hash das equipas a equipa pretendida */
void insertHashTeam(team *t, unsigned long key){
    team *temp;

    if (!teams[key]) {
        teams[key] = t;
    } else {
        for(temp = teams[key]; temp->next != NULL; temp = temp->next);
        temp->next = t;
    }
}

/* funcao que insere na hash dos jogos o jogo pretendido */
void insertHashName(game *g, unsigned long key) {
    game *temp;

    if (!hashtable[key]) {
        hashtable[key] = g;
    } else {
        for(temp = hashtable[key]; temp->next != NULL; temp = temp->next);
        temp->next = g;
    }
}

/* funcao usada no comando "a" que consiste em ler e organizar o input */
game *read_game() {
    game *inputPtr;
    char name[MAXINPUT], team_one[MAXINPUT], team_two[MAXINPUT];
    int score_one, score_two;

    /* passa o input para variaveis */
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team_one, team_two, &score_one, &score_two);

    /* aloca a memoria de cada parametro de um jogo */
    inputPtr = (game*) can_fail_malloc(sizeof(game));
    inputPtr->name = can_fail_malloc(sizeof(char)*(strlen(name)+1));
    inputPtr->team_one = can_fail_malloc(sizeof(char)*(strlen(team_one)+1));
    inputPtr->team_two = can_fail_malloc(sizeof(char)*(strlen(team_two)+1));
    inputPtr->score[0] = score_one;
    inputPtr->score[1] = score_two;

    strcpy(inputPtr->name, name);
    strcpy(inputPtr->team_one, team_one);
    strcpy(inputPtr->team_two, team_two);

    return inputPtr;
}

/* funcao que retorna uma key que corresponde ao lugar do nome fornecido na hashtable */
unsigned long getKey(char name[MAXNAME]) {
    unsigned int i;
    unsigned long car, string = 0;

    for (i = 0; i < strlen(name); i++) {
        car = name[i];
        string += car*i;
    }
    return hash(string, HASHTABLESIZE);
}

/* funcao que elimina da hash um determinado jogo */
void deleteHash(char *name, char *team_one, char *team_two, unsigned long key) {
    game *t, *prev;

    for (t = hashtable[key], prev = NULL; t != NULL; prev = t, t = t->next) {
        if (strcmp(t->name, name) == 0
            && strcmp(t->team_one, team_one) == 0
            && strcmp(t->team_two, team_two) == 0) {

            if(t == hashtable[key])
                hashtable[key] = t->next;
            else
                prev->next = t->next;
        }
    }
}


void deleteList(char *name, char *team_one, char *team_two) {
    Node *t, *prev;

    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (strcmp(t->game->name, name) == 0
        && strcmp(t->game->team_one, team_one) == 0
        && strcmp(t->game->team_two, team_two) == 0) {

            if(t == head)
                head = t->next;
            else if (t == tail) {
                tail = prev;
                prev->next = t->next;
            }
            else
                prev->next = t->next;
        }
    }
}

/* funcao que retorna 1 se a equipa recebida ja esxistir na hash e 0 caso contrario */ 
int team_error(char name[MAXNAME], unsigned long key){
    team *node;
    for(node = teams[key]; node != NULL; node = node->next)
        if (strcmp(node->team_name, name) == 0)
            return 1;

    return 0;
}

/* funcao que retorna 1 se o jogo ja existir na hash dos jogos e 0 caso contrario */
int game_error(char name[MAXNAME], unsigned long key) {
    game *node;
    for(node = hashtable[key]; node != NULL; node = node->next)
        if (strcmp(node->name, name) == 0)
            return 1;

    return 0;
}

/* funcao que consoante o resultado do jogo aumenta o numero de vitorias a equipa que venceu o encontro */
void increment_win(game *g, unsigned long key1, unsigned long key2){
    team *node;

    if(g->score[0] > g->score[1]){
        for (node = teams[key1]; node != NULL; node = node->next)
            if (strcmp(node->team_name, g->team_one) == 0) {
                node->wins++;
                return;
            }
    } else if(g->score[0] < g->score[1]){
        for (node = teams[key2]; node != NULL; node = node->next)
            if (strcmp(node->team_name, g->team_two) == 0) {
                node->wins++;
                return;
            }
    }
}

void command_a() {
    game *inputPtr;
    unsigned long key;

    inputPtr = read_game();
    inputPtr->next = NULL;

    key = getKey(inputPtr->name);
    if (game_error(inputPtr->name, key) != 0) {
        printf("%d Jogo existente.\n", command_count);
    } else if (team_error(inputPtr->team_one, getKey(inputPtr->team_one)) == 0
            || team_error(inputPtr->team_two, getKey(inputPtr->team_two)) == 0){
        printf("%d Equipa inexistente.\n", command_count);
    } else {
        insertHashName(inputPtr, key);
        insertList(inputPtr);
        increment_win(inputPtr, getKey(inputPtr->team_one), getKey(inputPtr->team_two));
    }
}

void command_p(){
    game *node;
    unsigned long key;
    char name[MAXNAME];

    /* passa o input para variaveis */
    scanf("%s", name);
    key = getKey(name);

    for (node = hashtable[key]; node != NULL; node = node->next)
        if (strcmp(node->name, name) == 0) {
            printf("%d %s %s %s %d %d\n", command_count, node->name, node->team_one,
                    node->team_two, node->score[0], node->score[1]);
            return;
        }
    printf("%d Jogo inexistente.\n", command_count);
}

void command_r() {
    game *t;
    unsigned long key;
    char name[MAXNAME];

    /* passa o input para variaveis */
    scanf("%s", name);
    key = getKey(name);

    for (t = hashtable[key]; t != NULL; t = t->next) {
        if (strcmp(t->name, name) == 0) {
            deleteList(t->name, t->team_one, t->team_two);
            deleteHash(t->name, t->team_one, t->team_two, key);
            return;
        }
    }
    printf("%d Jogo inexistente.\n", command_count);
}

void command_s() {
    game *node;
    unsigned long key;
    char name[MAXINPUT];
    int score_one = 0, score_two = 0;

    /* passa o input para variaveis */
    scanf("%[^:\n]:%d:%d", name, &score_one, &score_two);

    key = getKey(name);

    for (node = hashtable[key]; node != NULL; node = node->next)
        if (strcmp(node->name, name) == 0) {
            node->score[0] = score_one;
            node->score[1] = score_two;
            return;
        }
    printf("%d Jogo inexistente.\n", command_count);
}

void command_l() {
    Node *node = head;
    for (; node != NULL; node = node->next){
        printf("%d %s %s %s %d %d\n", command_count, node->game->name, node->game->team_one,
                node->game->team_two, node->game->score[0], node->game->score[1]);
    }
}

void command_A(){
    team *inputPtr = can_fail_malloc(sizeof(team));
    unsigned long key;
    char name[MAXNAME];

    /* passa o input para variaveis */
    scanf("%s", name);

    key = getKey(name);

    inputPtr->team_name = can_fail_malloc(sizeof(char)*(strlen(name) + 1));
    strcpy(inputPtr->team_name, name);
    inputPtr->next = NULL;

    if (team_error(inputPtr->team_name, key) != 0){
        printf("%d Equipa existente.\n",command_count);
    } else{
        insertHashTeam(inputPtr, key);
        insertTeamList(inputPtr);
        teams_counter++;
    }
}

void command_P(){
    team *node = NULL;
    unsigned long key;
    char name[MAXNAME] = {0};

    /* passa o input para variaveis */
    scanf("%s", name);
    key = getKey(name);

    for (node = teams[key]; node != NULL; node = node->next)
        if (strcmp(node->team_name, name) == 0) {
            printf("%d %s %d\n", command_count, node->team_name, node->wins);
            return;
        }
    printf("%d Equipa inexistente.\n", command_count);
}

void command_g(){
    team *node = team_head;
    int max_wins = 0, count = 0;
    char **max_wins_teams, temp[MAXNAME] = {0};
    int i, j;

    if(teams_counter == 0) return;

    max_wins_teams = can_fail_malloc(teams_counter * sizeof(char*));
    for (i = 0; i < teams_counter; i++)
        max_wins_teams[i] = can_fail_malloc((MAXNAME+1));

    for (; node != NULL; node = node->next) {
        if (node->wins > max_wins)
            max_wins = node->wins;
        teams_counter++;
    }

    for (node = team_head, i = 0; node != NULL; node = node->next, i++)
        if (node->wins == max_wins) {
            strcpy(max_wins_teams[i], node->team_name);
            count++;
        }

    for (i = 0; i < count; ++i) {
        for (j = i + 1; j < count; ++j) {
            if (strcmp(max_wins_teams[i], max_wins_teams[j]) > 0) {
                strcpy(temp, max_wins_teams[i]);
                strcpy(max_wins_teams[i], max_wins_teams[j]);
                strcpy(max_wins_teams[j], temp);
            }
        }
    }

    printf("%d Melhores %d\n", command_count, max_wins);
    for (i = 0; i < count; ++i)
        printf("%d * %s\n", command_count, max_wins_teams[i]);

    /*for (i = 0; i < teams_counter; i++)
       if(max_wins_teams[i])
            free(max_wins_teams[i]);
    free(max_wins_teams);*/
}

/* funcao que desaloca toda a memoria alocada nas listas */
void freeList() {
    Node *temp;
    team *temp_t;

    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp->game->name);
        free(temp->game->team_one);
        free(temp->game->team_two);
        free(temp->game);
        free(temp);
    }
   while (team_head != NULL){
        temp_t = team_head;
        team_head = team_head->next;
        free(temp_t->team_name);
        free(temp_t);
    }
}

/* funcao que desaloca a memoria alocada em ambas as hashtables */
void freeHash() {
    game *temp;
    team *temp_t;
    int i;
    for (i = 0; i < HASHTABLESIZE; i++){
        while (hashtable[i] != NULL) {
            temp = hashtable[i];
            hashtable[i] = hashtable[i]->next;
            if(temp->name)
                free(temp->name);
            if(temp->team_two)
                free(temp->team_two);
            if(temp->team_one)
                free(temp->team_one);
            free(temp);
        }
       while (teams[i] != NULL) {
            temp_t = teams[i];
            teams[i] = teams[i]->next;
            if(temp_t->team_name)
                free(temp_t->team_name);
            free(temp_t);
        }
    }

}

/* Comando que inicializa as varias funcoes */
int main() {
    initializeHashTables();
    for (;;) {
        switch (getchar()) {
            case 'a':
                getchar();
                command_count++;
                command_a();
                break;
            case 'l':
                getchar();
                command_count++;
                command_l();
                break;
            case 'p':
                getchar();
                command_count++;
                command_p();
                break;
            case 'r':
                getchar();
                command_count++;
                command_r();
                break;
            case 's':
                getchar();
                command_count++;
                command_s();
                break;
            case 'A':
                getchar();
                command_count++;
                command_A();
                break;
            case 'P':
                getchar();
                command_count++;
                command_P();
                break;
            case 'g':
                getchar();
                command_count++;
                command_g();
                break;
            case 'x':
                freeList();
                /*freeHash();*/
                return 0;
            default:
                break;
        }
    }
}


