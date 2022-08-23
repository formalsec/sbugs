#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"
#include "matches.h"
#include "aux.h"

/* Adiciona uma nova equipa se a equipa ainda nao existir */
void cmd_A(int * NL, hash_table_teams *hash_teams, linked_list_teams * linked_teams){
    char d[MAX_CHARS_T];
    scanf(" %[^:\n]", d);
    if (search_team(hash_teams, d) == NULL) {
        node_team *n = add_linked_list_team(linked_teams, d, 0);
        add_hash_table_team(hash_teams, n);
    }
    else
        printf("%d Equipa existente.\n", *NL);
}

/* Procura uma equipa e faz printa da sua descricao e vitorias */
void cmd_P(int * NL, hash_table_teams *hash_teams){
    char d[MAX_CHARS_M];
    ptr_team * ptr_n_team;
    node_team * n_team;
    scanf(" %[^:\n]", d);
    ptr_n_team = search_team(hash_teams, d);
    n_team = ptr_n_team? ptr_n_team->node : NULL; /* so se consegue obter o node de ptr_n_team se a equipa existir */
    if (n_team)
        printf("%d %s %d\n", *NL, n_team->desc, n_team->victories);
    else
        printf("%d Equipa inexistente.\n", *NL);
}

/* Adiciona um novo jogo se o jogo ainda na existe e as equipas existem*/
void cmd_a(int * NL, hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_matches * linked_matches){
    char name[MAX_CHARS_M], team1[MAX_CHARS_T], team2[MAX_CHARS_T];
    int score[2];
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score[0], &score[1]);
    if (search_match(hash_matches, name) != NULL)
        printf("%d Jogo existente.\n", *NL);
    else {
        ptr_team * ptr_n_team1 = search_team(hash_teams, team1);
        node_team *n_team1 = ptr_n_team1 ? ptr_n_team1->node : NULL;
        ptr_team * ptr_n_team2 = search_team(hash_teams, team2);
        node_team *n_team2 = ptr_n_team2 ? ptr_n_team2->node : NULL;
        if (n_team1 == NULL || n_team2 == NULL)
            printf("%d Equipa inexistente.\n", *NL);
        else{
            node_match * n;
            if (score[0] > score[1])
                n_team1->victories++;
            else if (score[1] > score[0])
                n_team2->victories++;
            n = add_linked_list_match(linked_matches, name, n_team1, n_team2, score);
            add_hash_table_match(hash_matches, n);
        }
    }
}

/* Procura um jogo atraves da descricao e faz print da sua descricao, equipas e score */
void cmd_p(int * NL, hash_table_matches *hash_matches){
    char d[MAX_CHARS_M];
    ptr_match * ptr_n_match;
    node_match * n_match;
    scanf(" %[^:\n]", d);
    ptr_n_match = search_match(hash_matches, d);
    n_match = ptr_n_match ? ptr_n_match->node : NULL;
    if (n_match)
        printf("%d %s %s %s %d %d\n", *NL, n_match->desc, n_match->team1->desc, n_match->team2->desc, n_match->score[0], n_match->score[1]);
    else
        printf("%d Jogo inexistente.\n", *NL);
}

/* Lista todos os jogos pela ordem em que foram introduzidos */
void cmd_l(int * NL, linked_list_matches * linked_matches){
    node_match *head = linked_matches->head;
    while(head){
        printf("%d %s %s %s %d %d\n", *NL, head->desc, head->team1->desc, head->team2->desc, head->score[0], head->score[1]);
        head = head->next;
    }
}

/* Procura um jogo atraves da descricao e apaga-o, se existir */
void cmd_r(int *NL, hash_table_matches *hash_matches, linked_list_matches *linked_matches){
    char d[MAX_CHARS_M];
    ptr_match *ptr_n;
    scanf(" %[^:\n]", d);
    ptr_n = search_match(hash_matches, d);
    if (ptr_n) {
        int old_score[2];
        int new_score[2] = {0, 0}; /* cria-se um novo score a 0,0 para se poder usar a funcao change_victories */
        node_match *n = remove_match_hash_table(hash_matches, ptr_n);
        old_score[0] = n->score[0];
        old_score[1] = n->score[1];
        change_victories(n->team1, n->team2, old_score, new_score);
        remove_match(linked_matches, n);
    }
    else
        printf("%d Jogo inexistente.\n", *NL);

}

/* Altera o score de um jogo e faz as alteracoes necessarias as vitorias das equipas dos jogo */
void cmd_s(int *NL, hash_table_matches * hash_matches){
    char name[MAX_CHARS_M];
    int new_score[2];
    ptr_match *ptr_n_match;
    scanf(" %[^:\n]:%d:%d", name, &new_score[0], &new_score[1]);
    ptr_n_match = search_match(hash_matches, name);
    if (ptr_n_match){
        int old_score[2];
        node_team *team1, *team2;
        old_score[0] = ptr_n_match->node->score[0];
        old_score[1] = ptr_n_match->node->score[1];
        team1 = ptr_n_match->node->team1;
        team2 = ptr_n_match->node->team2;
        change_victories(team1, team2, old_score, new_score);
        ptr_n_match->node->score[0] = new_score[0];
        ptr_n_match->node->score[1] = new_score[1];
    }
    else
        printf("%d Jogo inexistente.\n", *NL);
}

/* Encontra as equipas que venceram mais jogos e ordena-as por ordem alfabetica da descricao */
void cmd_g(int *NL, linked_list_teams *linked_teams){
    if (linked_teams->head){
        int cap = 100;
        int i = 0, last_index;
        int v = search_most_vict_teams(linked_teams);
        node_team **list_vic = malloc(sizeof(node_team) * cap);
        node_team **aux_l_v;
        node_team *n = linked_teams->head;
        while (n){
            if (n->victories == v){
                if (i == cap) {
                    list_vic = realloc(list_vic, sizeof(node_team) * cap * 2);
                    cap*=2;
                }
                list_vic[i++] = n;
            }
            n = n->next;
        }
        last_index = i - 1;
        aux_l_v = malloc(sizeof(node_team) * (last_index + 1));
        merge_sort(list_vic, aux_l_v, 0, last_index);
        printf("%d Melhores %d\n", *NL, v);
        for (i = 0; i <= last_index; i++){
            printf("%d * %s\n",*NL, list_vic[i]->desc);
        }
        free(list_vic);
        free(aux_l_v);
    }
}

/* Chama as diferentes funcoes para os diferentes comandos */
void call_cmds(char c, int *NL, hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_teams * linked_teams, linked_list_matches * linked_matches){
    switch (c) {
        case 'A':
            cmd_A(NL, hash_teams, linked_teams);
            break;
        case 'P':
            cmd_P(NL, hash_teams);
            break;
        case 'a':
            cmd_a(NL, hash_teams, hash_matches, linked_matches);
            break;
        case 'p':
            cmd_p(NL, hash_matches);
            break;
        case 'l':
            cmd_l(NL,linked_matches);
            break;
        case 'r':
            cmd_r(NL, hash_matches, linked_matches);
            break;
        case 's':
            cmd_s(NL, hash_matches);
            break;
        case 'g':
            cmd_g(NL, linked_teams);
        default:
            break;

    }
    *NL = *NL + 1;
}

/* Inicializa as estruturas, e vai estar a espera de novos comandos ate terminar o programa */
int main(){
    char c;
    int *NL = malloc(sizeof(int));
    hash_table_matches *hash_matches = malloc(sizeof(hash_table_teams));
    hash_table_teams *l_teams = malloc(sizeof(hash_table_matches));
    linked_list_matches * linked_matches = malloc(sizeof(linked_list_matches));
    linked_list_teams * list_t = malloc(sizeof(linked_list_teams));
    inicialize_lists(l_teams, hash_matches, list_t, linked_matches);
    *NL = 1;
    scanf("%c", &c);
    while (c != 'x'){
        call_cmds(c, NL, l_teams, hash_matches, list_t, linked_matches);
        scanf("\n%c", &c);
    }
    free(NL);
    destroy(l_teams, hash_matches, list_t, linked_matches);
    return 0;
}


