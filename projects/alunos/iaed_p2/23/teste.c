#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXNAME 1023
#define HASHSIZE 5

unsigned int hash(char *v, int M) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h;
}

typedef struct team{
    char name[MAXNAME];
    int wins;
    struct team* next;
}team;

typedef struct game{
    char name[MAXNAME];
    char team1[MAXNAME];
    char team2[MAXNAME];
    int score1;
    int score2;
    struct game* next;
}game;

static team * hash_table_team[HASHSIZE];

static team * team_head = NULL;

static game * hash_table_game[HASHSIZE];

static game * game_head = NULL;

/*inicializa a hash das equipas*/
void init_hash_table_team() {
    int i;
    for(i = 0; i < HASHSIZE; i++)
        hash_table_team[i] = NULL;
}

/*inicializa a hash table dos jogos*/
void init_hash_table_game() {
    int i;
    for(i = 0; i < HASHSIZE; i++)
        hash_table_game[i] = NULL;
}

/*reserva memoria para cada nova equipa*/
team *init_team() {
    team *p = (team*)can_fail_malloc(sizeof(team));
    return p;
}

/*reserva memoria para cada novo jogo*/
game *init_game() {
    game *p = (game*)can_fail_malloc(sizeof(game));
    return p;
}


/*insere equipa na hash*/
void insert_game(game *t, char *name, char* team1, char* team2, int *score1, int *score2) {
    int index = hash(name, HASHSIZE);
    game *end;
    game *t_list = init_game();
    strcpy(t->name, name);
    strcpy(t->team1, team1);
    strcpy(t->team2, team2);
    t->score1 = *score1;
    t->score2 = *score2;
    t->next = hash_table_game[index];
    hash_table_game[index] = t;
    strcpy(t_list->name, name);
    strcpy(t_list->team1, team1);
    strcpy(t_list->team2, team2);
    t_list->score1 = *score1;
    t_list->score2 = *score2;
    if(game_head== NULL) {
        t_list->next = game_head;
        game_head= t_list;
    }
    for(end = game_head; end->next != NULL; end = end->next)
        ;
    end->next = t_list;
    t_list->next = NULL;
}

/*insere jogo na hash e na lista*/
void insert_team(team *t, char *name) {
    int index = hash(name, HASHSIZE);
    team *end;
    team *t_list = init_team();
    strcpy(t->name, name);
    t->wins = 0;
    t->next = hash_table_team[index];
    hash_table_team[index] = t;
    strcpy(t_list->name, name);
    t_list->wins = 0;
    if(team_head== NULL) {
        t_list->next = team_head;
        team_head= t_list;
    }
    for(end = team_head;end->next != NULL; end = end->next)
        ;
    end->next = t_list;
    t_list->next = NULL;
}

/*encontra uma equipa na hash se ela existir pelo nome*/
team *team_search (char *name) {
    int index = hash(name, HASHSIZE);
    team*tmp = hash_table_team[index];
    while (tmp != NULL && strcmp(tmp->name, name) != 0)
        tmp = tmp->next;
    return tmp;
}

/*encontra um jogo na hash se ele existir pelo nome*/
game *game_search (char *name) {
    int index = hash(name, HASHSIZE);
    game*tmp = hash_table_game[index];
    while (tmp != NULL && strcmp(tmp->name, name) != 0)
        tmp = tmp->next;
    return tmp;
}

/*encontra uma quipa na lista se ela existir pelo nome*/
team *teamlist_search (char *name) {
    team*tmp = team_head;
    while (tmp != NULL && strcmp(tmp->name, name) != 0)
        tmp = tmp->next;
    return tmp;
}

/*encontra um jogo na lista se ele existir pelo nome*/
game *gamelist_search (char *name) {
    game*tmp = game_head;
    while (tmp != NULL && strcmp(tmp->name, name) != 0)
        tmp = tmp->next;
    return tmp;
}

/*apaga um jogo da hash table pelo nome*/
void game_delete_hash(char *name) {
    int index = hash(name, HASHSIZE);
    game *prev = NULL;
    game *tmp = hash_table_game[index];
    while (tmp != NULL && strcmp(tmp->name, name) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (prev == NULL) 
        hash_table_game[index] = tmp->next;
    else
        prev->next = tmp->next;
}

/*apaga um jogo da lista pelo nome*/
void game_delete_list(char *name) {
    game *prev = NULL;
    game *tmp = game_head;
    while (tmp != NULL && strcmp(tmp->name, name) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (prev == NULL) 
        game_head= tmp->next;
    else
        prev->next = tmp->next;
}



/*adiciona jogo na hash e na lista auto referenciada*/
void a(int *l) {
    char name[MAXNAME], team1[MAXNAME], team2[MAXNAME];
    int score1, score2;
    game *p = init_game();
    scanf("%[^:\n]", name);
    getchar();
    scanf("%[^:\n]", team1);
    getchar();
    scanf("%[^:\n]", team2);
    getchar();
    scanf("%d", &score1);
    getchar();
    scanf("%d", &score2);
    getchar();
    (*l)++;
    if(game_search(name)!=NULL){
        free(p);
        printf("%d Jogo existente.\n", *l);
    }
    else if(team_search(team1)==NULL || team_search(team2)==NULL) {
        free(p);
        printf("%d Equipa inexistente.\n", *l);
    }
    else {
        insert_game(p, name, team1, team2, &score1, &score2);
        if(score1 > score2) {
            team_search(game_search(name)->team1)->wins += 1;
            teamlist_search(game_search(name)->team1)->wins += 1;
        }
        else if(score2 > score1) {
            team_search(game_search(name)->team2)->wins += 1;
            teamlist_search(game_search(name)->team2)->wins += 1;
        }
    }
}

/*adiciona equipa na hash*/
void A(int *l) {
    char name[MAXNAME];
    team *p = init_team();
    scanf("%[^:\n]", name);
    getchar();
    (*l)++;
    if(team_search(name)==NULL) {
        insert_team(p, name);
    }
    else {
        printf("%d Equipa existente.\n", *l);
        free(p);
    }
}

/*lista os joogos introduzidos*/
void l(int *l) {
    game *temp = game_head;
    (*l)++;
    while(temp != NULL) {
        printf("%d %s %s %s %d %d\n", *l, temp->name, temp->team1, temp->team2, temp->score1, temp->score2);
        temp =  temp -> next;
    }
}
    
/*procura um jogo com o nome dado*/
void p(int *l) {
    char name[MAXNAME];
    game *temp;
    scanf("%[^:\n]", name);
    getchar();
    (*l)++;
    temp = game_search(name);
    if(temp != NULL)
        printf("%d %s %s %s %d %d\n", *l, temp->name, temp->team1, temp->team2, temp->score1, temp->score2);
    else
        printf("%d Jogo inexistente.\n", *l);
}

/*procura equipa na hash*/
void P(int *l) {
    char name[MAXNAME];
    team *tmp;
    scanf("%[^:\n]", name);
    getchar();
    (*l)++;
    tmp = team_search(name);
    if(tmp != NULL)
        printf("%d %s %d\n", *l, name, tmp->wins);
    else
        printf("%d Equipa inexistente.\n", *l);
    
}

/*remove um jogo da hash e da lista*/
void r(int *l) {
    char name[MAXNAME];
    scanf("%[^:\n]", name);
    getchar();
    if(game_search(name)==NULL){
        (*l)++;
        printf("%d Jogo inexistente.\n", *l);
    }
    else {
        int score1 = game_search(name)->score1;
        int score2 = game_search(name)->score2;
        if(score1 > score2) {
            team_search(game_search(name)->team1)->wins -= 1;
            teamlist_search(game_search(name)->team1)->wins -= 1;
        }
        else if(score2 > score1) {
            team_search(game_search(name)->team2)->wins -= 1;
            teamlist_search(game_search(name)->team2)->wins -= 1;
        }
        game_delete_hash(name);
        game_delete_list(name);
    }
}

/*altera resultado de um jogo*/
void s(int *l) {
    char name[MAXNAME];
    int score1, score2;
    game *tmp, *node;
    scanf("%[^:\n]", name);
    getchar();
    if(game_search(name) != NULL) {
        scanf("%d:%d", &score1, &score2);
        getchar();
        node = gamelist_search(name);
        tmp = game_search(name);
        tmp->score1 = score1;
        tmp->score2 = score2;
        node->score1 = score1;
        node->score2 = score2;
        if(score1 > score2) {
            team_search(game_search(name)->team1)->wins += 1;
            teamlist_search(game_search(name)->team1)->wins += 1;
        }
        else if(score2 > score1) {
            team_search(game_search(name)->team2)->wins += 1;
            teamlist_search(game_search(name)->team2)->wins += 1;
        }
    }
    else 
        printf("%d Jogo inexistente.\n", *l);
}

int main() {
    char cmd;
    int line = 0;
    init_hash_table_team();
    init_hash_table_game();
    while((cmd = getchar())) {
        getchar();
        switch(cmd) {
            case 'a':
                a(&line);
                break;
            case 'A': 
                A(&line);
                break;
            case 'l':
                l(&line);
                break;
            case 'p':
                p(&line);
                break;
            case 'P':
                P(&line);
                break;
            case 'r':
                r(&line);
                break;
            case 's':
                s(&line);
                break;
            case 'x':
                return 0;
        }
    }
    return 0;
}
                
