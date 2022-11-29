#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH 58

typedef struct team{
    char* team_name;
    int n_victories;
}* Teams;


typedef struct node{
    Teams T;
    struct node* next,* prev;
}* link;

typedef struct game{
    char* game_name;
    link teams[2];
    int score[2], ID;
}* Games;

typedef struct node_games{
    Games G;
    struct node_games* next,* prev;
}* link_games;


link* Init(int m){
    link* heads;
    int i;
    heads = can_fail_malloc(m*sizeof(link));
    for (i = 0; i < m; i++)   
        heads[i] = NULL;

    return heads;
}

link_games* Init_Games(int m){
    link_games* heads;
    int i;
    heads = can_fail_malloc(m*sizeof(link_games));
    for (i = 0; i < m; i++)   
        heads[i] = NULL;

    return heads;
}

int hash(char *new){
    char i = new[0];
    return (i - 'A');
}

link NEW_T(Teams new_team){
    link node = can_fail_malloc(sizeof(struct node));

    node->T = new_team;
    node->next = NULL;
    node->prev = NULL;
    node->T->n_victories = 0;

    return node;
}

link insert_midle(link node, Teams new_team){
    link new_node = NEW_T(new_team);

    new_node->prev = node->prev;
    node->prev->next = new_node;
    new_node->next = node;

    return new_node;
}

void print(link head){
    link t;

    for(t = head; t != NULL; t = t->next)
        printf("%s\n",t->T->team_name);
}


link* new_node(link* head, Teams new_team){
    link node;
    int m, flag = 0;
    
    m = hash (new_team->team_name);

    if (head[m] == NULL)
        head[m] = NEW_T(new_team);

    else{
        for (node = head[m]; node != NULL; node = node->next){
            if (strcmp(node->T->team_name, new_team->team_name) > 0){
                if (node->prev == NULL){
                    node = NEW_T(new_team);
                    node->next = head[m];
                    head[m]->prev = node;
                    head[m] = node;
                    flag = 1;
                    break;
                }
                else{
                    node->prev = insert_midle(node, new_team);
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0){
            for(node = head[m]; node->next != NULL; node = node->next){
            }
            node->next = NEW_T(new_team);
        }
    }

    return head;
}



link search(char* name, link* head){
    link node;
    int m;
    
    m = hash(name);
    
    if (head[m] != NULL){
        for(node = head[m]; node != NULL; node = node->next){
            if(strcmp(node->T->team_name, name) == 0){
                return node;
            }
        }
    }
    
    return NULL;
}

link_games search_game(char* name, link_games* head){
    link_games node;
    int m;

    m = hash(name);
    
    if (head[m] != NULL){
        for(node = head[m]; node != NULL; node = node->next){
            if(strcmp(node->G->game_name, name) == 0){
                return node;
            }
        }
    }
    
    return NULL;
}


void print_games(link_games head){
    link_games t;
    for(t = head; t != NULL; t = t->next)
        printf("%s\n",t->G->game_name);
}

link* add_team(int NL, link* heads){
    Teams new_team = can_fail_malloc(sizeof(struct team));
    char e_temp[1024];
    int flag = 0;
    
    scanf(" %[^:\n]", e_temp);

    new_team->n_victories = 0;
    new_team->team_name = can_fail_malloc((strlen(e_temp)+1)*sizeof(char));
    strcpy(new_team->team_name, e_temp);

    if (search(new_team->team_name, heads) != NULL){
        printf("%d Equipa existente.\n", NL);
        free(new_team->team_name);
        free(new_team);
        flag = 1;
    }

    if (flag == 0)
        heads = new_node(heads, new_team);

    return heads;
}

void free_node(link_games node){
    free(node->G->game_name);
    free(node->G);
    free(node);
}

link_games* delete_game(int NL, link_games* heads){
    char g_temp[1024];
    int m, flag = 0;
    link_games node;
    
    scanf(" %[^:\n]", g_temp);

    m = hash(g_temp);

    for(node = heads[m]; node != NULL; node = node->next){
        if(strcmp(node->G->game_name, g_temp) == 0) {
            if(node->prev == NULL){
                free_node(heads[m]);
                heads[m] = NULL;
            }
            else if(node->next == NULL){
                node->prev->next = NULL;
                free_node(node);
                break;
            }
            else{
                node->prev->next = node->next;
                node->next->prev = node->prev;
                free_node(node);
            }
            flag = 1;
        }
    }   


    if (flag == 0)
        printf("%d Jogo inexistente.\n", NL); 
    if (flag == 1)
        printf("%d Jogo existente.\n", NL);

    return heads;
}

void search_team(int NL, link* heads){
    char e_temp[1024];
    link node;

    scanf(" %[^:\n]", e_temp);

    if ((node = search(e_temp, heads)) == NULL)
        printf("%d Equipa inexistente.\n", NL);
    else
        printf("%d %s %d\n", NL, node->T->team_name, node->T->n_victories);
}

link_games NEW_G(Games new_game){
    link_games node = can_fail_malloc(sizeof(struct node_games));

    node->G = new_game;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

link_games insert_midle_games(link_games node, Games new_game){
    link_games new_node = NEW_G(new_game);

    new_node->prev = node->prev;
    node->prev->next = new_node;
    new_node->next = node;

    return new_node;
}

link_games* new_node_game(link_games* head, Games new_game){
    link_games node,last_node;
    int m, flag = 0;

    m = hash(new_game->game_name);

    if (head[m] == NULL){
        head[m] = NEW_G(new_game);
    }

    else{
       last_node = NULL;
        for (node = head[m]; node != NULL; node = node->next){
            last_node = node;
            if (strcmp(node->G->game_name, new_game->game_name)>0){
                if (node->prev == NULL){
                    node = NEW_G(new_game);
                    node->next = head[m];
                    head[m]->prev = node;
                    head[m] = node;
                    flag = 1;
                    break;
                }
                else{
                    node->prev = insert_midle_games(node, new_game);
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0){
           last_node->next = NEW_G(new_game);
           last_node->next->prev = last_node;
        }
            
    }
    return head;
}

void victories(Games new_game){

    if (new_game->score[0] > new_game->score[1])
        new_game->teams[0]->T->n_victories++;
    if (new_game->score[0] < new_game->score[1])
        new_game->teams[1]->T->n_victories++;
}

link_games* add_games(int NL, link_games* heads_games, link* heads_teams, int id){
    char e_temp1[1024], e_temp2[1024], g_temp[1024];
    int score1, score2, flag = 0;
    Games new;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", g_temp, e_temp1, e_temp2, &score1, &score2);
    
    if (search(e_temp1, heads_teams) != NULL){
        if (search(e_temp2, heads_teams) != NULL){
            flag = 1;
            if (search_game(g_temp, heads_games) == NULL){
                new = can_fail_malloc(sizeof (struct game));

                new->score[0] = score1;
                new->score[1] = score2;
                new->game_name = can_fail_malloc((strlen(g_temp)+1)*sizeof(char));
                strcpy(new->game_name, g_temp);

                new->teams[0] = search(e_temp1, heads_teams);
                new->teams[1] = search(e_temp2, heads_teams);
                new->ID = id;
                victories(new);

                heads_games = new_node_game(heads_games, new);

                flag = 2;
            }
        }
    }
    if (flag == 0)
        printf("%d Equipa inexistente.\n", NL);
    if (flag == 1)
        printf("%d Jogo existente.\n", NL);
    
    return heads_games;
}

void search_games(int NL, link_games* heads_games){
    char g_temp[1024];
    link_games node;

    scanf(" %[^:\n]", g_temp);

    if ((node = search_game(g_temp, heads_games)) == NULL)
        printf("%d Jogo inexistente.\n", NL);
    else
        printf("%d %s %s %s %d %d\n", NL, node->G->game_name, node->G->teams[0]->T->team_name, 
        node->G->teams[1]->T->team_name, node->G->score[0], node->G->score[1]);
}

link_games* change_score(int NL, link_games* heads_games){
    char g_temp[1024];
    int score1, score2;
    link_games game;

    scanf(" %[^:\n]:%d:%d", g_temp, &score1, &score2);

    game = search_game(g_temp, heads_games);
    
    if(game == NULL)
        printf("%d Jogo inexistente.\n", NL);
    else{
        if (game->G->score[0] - game->G->score[1] > 0 && score1 - score2 > 0){
            game->G->score[0] = score1;
            game->G->score[1] = score2;
        }
        if (game->G->score[0] - game->G->score[1] < 0 && score1 - score2 < 0){
            game->G->score[0] = score1;
            game->G->score[1] = score2;
        }
        if (game->G->score[0] - game->G->score[1] > 0 && score1 - score2 < 0){
            game->G->score[0] = score1;
            game->G->score[1] = score2;
            game->G->teams[0]->T->n_victories--;
            game->G->teams[1]->T->n_victories++;
        }
        if (game->G->score[0] - game->G->score[1] < 0 && score1 - score2 > 0){
            game->G->score[0] = score1;
            game->G->score[1] = score2;
            game->G->teams[0]->T->n_victories++;
            game->G->teams[1]->T->n_victories--;
        }
        else{
            game->G->score[0] = score1;
            game->G->score[1] = score2;
        }

    }
    return heads_games;
}

void list_teams(link* heads_teams){
    link node, temp, temp1, begin_node;
    Teams begin;
    int i, count = -1;

    begin = can_fail_malloc(sizeof(struct game));
    begin_node = NEW_T(begin);


    for (i = 0; i < MAX_HASH; i++){
        for (temp1 = heads_teams[i]; temp1 != NULL; temp1 = temp1->next){
            if (temp1->T->n_victories > count){
                count = temp1->T->n_victories;
                node = NEW_T(temp1->T);
                begin_node->next = node;
                node->prev = begin_node;
            }  
            else if (temp1->T->n_victories == count){
                for(temp = begin_node; temp->next != NULL; temp = temp->next){
                }
                node = NEW_T(temp1->T);
                node->prev = temp;
                temp->next = node;
            }
        }
    }
    print(begin_node->next);
    
    for(temp = begin_node; temp->next != NULL; temp = temp->next){
    }
    while (temp->prev != NULL){
        temp = temp->prev;
        free(temp->next);
    } 
    free(temp);

}


void list_games(int NL, link_games* heads){
    int i, j, max_array_size = 10, array_size = 0;
    link_games *array = can_fail_malloc(max_array_size * sizeof(link_games));
    link_games temp;

    for (i=0; i < MAX_HASH; i++){
        for (temp = heads[i]; temp != NULL ; temp = temp->next){
            if(array_size == max_array_size){
                max_array_size *= 2;
                array = can_fail_realloc(array, max_array_size * sizeof(link_games));
            }
            for(j = array_size; j > 0 && array[j - 1]->G->ID > temp->G->ID; j--)
                array[j] = array[j - 1];
            array[j] = temp;
            array_size++;
        }
    }

    for(i = 0; i < array_size; i++)
        printf("%d %s %s %s %d %d\n", NL, array[i]->G->game_name, 
        array[i]->G->teams[0]->T->team_name, array[i]->G->teams[1]->T->team_name, 
        array[i]->G->score[0], array[i]->G->score[1]);

  free(array);
}

void free_teams(link* heads){
    int i;
    link temp;

    for(i = 0; i < MAX_HASH; i++)
      while(heads[i] != NULL)
      {
        temp = heads[i]->next;
        free(heads[i]->T->team_name);
        free(heads[i]->T);
        free(heads[i]);
        heads[i] = temp;
      }
    free(heads);
}

void free_games(link_games* heads){
    int i;
    link_games temp;

    for(i = 0; i < MAX_HASH; i++)
      while(heads[i] != NULL)
      {
        temp = heads[i]->next;
        free(heads[i]->G->game_name);
        free(heads[i]->G);
        free(heads[i]);
        heads[i] = temp;
      }
    free(heads);
}

int main(){
    int NL = 0, id_jogo = -1; 
    char comando = '\0';
    link* heads_teams;
    link_games* heads_games;

    heads_teams = Init(MAX_HASH);
    heads_games = Init_Games(MAX_HASH);

    while(comando != 'x'){
        scanf("%c", &comando);
        switch(comando){
            case 'a':
                NL++;
                id_jogo++;
                heads_games = add_games(NL, heads_games, heads_teams, id_jogo);
                break;
            case 'A':
                NL++;
                heads_teams = add_team(NL, heads_teams);
                break;
            case 'l':
                NL++;
                list_games(NL, heads_games);
                break;
            case 'p':
                NL++;
                search_games(NL, heads_games);
                break;
            case 'P':
                NL++;
                search_team(NL, heads_teams);
                break;
            case 'r':
                NL++;
                heads_games = delete_game(NL, heads_games);
                break;
            case 's':
                NL++;
                heads_games = change_score(NL, heads_games);
                break;
            case 'g':
                NL++;
                list_teams(heads_teams);
                break;

        }
    }
    free_teams(heads_teams);
    free_games(heads_games);
    return 0;
}
