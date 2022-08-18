#include "matches.h"
#include "teams.h"
#include "aux.h"
#include <string.h>

/* devolve o indice da hash table atraves de uma string */
int hash(char *desc, int M) {
    int h, a = 31415, b = 27183;
    for (h = 0; *desc != '\0'; desc++, a = a*b % (M-1))
        h = (a*h + *desc) % M;
    return h;
}

/* altera as vitorias de duas equipas, com base no score antigo e no score novo */
void change_victories(node_team *n_team1, node_team *n_team2, int old_score[2], int new_score[2]){
    if (!((old_score[0] < old_score[1] && new_score[0] < new_score[1]) ||
          (old_score[0] > old_score[1] && new_score[0] > new_score[1]) ||
          (old_score[0] == old_score[1] && new_score[0] == new_score[1]))){
        if (old_score[0] > old_score[1] && new_score[0] == new_score[1])
            n_team1->victories = n_team1->victories - 1;
        else if (old_score[0] < old_score[1] && new_score[0] == new_score[1])
            n_team2->victories = n_team2->victories - 1;
        else if (old_score[0] > old_score[1]){
            n_team1->victories = n_team1->victories - 1;
            n_team2->victories = n_team2->victories + 1;
        }
        else if (old_score[0] < old_score[1]){
            n_team1->victories = n_team1->victories + 1;
            n_team2->victories = n_team2->victories - 1;
        }
        else if (old_score[0] == old_score[1]){
            if (new_score[0] < new_score[1])
                n_team2->victories = n_team2->victories + 1;
            else
                n_team1->victories = n_team1->victories + 1;
        }
    }
}

/* inicializa as hash tables e listas ligadas dos jogos e equipas */
void inicialize_lists(hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_teams * linked_teams, linked_list_matches * linked_matches){
    int i;
    for (i = 0; i < HASH_CAP_T; i++){  /* neste projeto, HASH_CAP_T e HASH_CAP_M teem o mesmo valor */
        hash_teams->nodes[i] = NULL;
        hash_matches->nodes[i] = NULL;
    }
    linked_teams->head = NULL;
    linked_teams->last = NULL;
    linked_matches->head = NULL;
    linked_matches->last = NULL;
}

/* destroi as hash tables e listas ligadas dos jogos e equipas */
void destroy(hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_teams *linked_teams, linked_list_matches *linked_matches){
    destroy_hash_teams(hash_teams);
    destroy_linked_teams(linked_teams);
    destroy_hash_matches(hash_matches);
    destroy_linked_matches(linked_matches);
}

/* devolve 1 se x for alfabeticamente menor que y e 0 caso contrario */
int less(char x[], char y[]){
    return strcmp(x,y) < 0 ? 1 : 0;
}

/* faz merge de dois vetores ordenados */
void merge(node_team *a[], node_team *aux[], int l, int m, int r){
    int i, j, k;
    for (i = m + 1; i > l; i --)
        aux[i - 1] = a[i - 1];
    for (j = m ; j < r; j++)
        aux[r + m - j] = a[j + 1];
    for (k = l; k <= r; k++){
        if (less(aux[j]->desc, aux[i]->desc))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/* algortimo merge sort */
void merge_sort(node_team *a[], node_team *aux[], int l, int r){
    int m = (r + l)/2;  /* m = ponto medio */
    if (r <= l)
        return;
    merge_sort(a, aux, l, m);
    merge_sort(a, aux, m + 1, r);
    merge(a, aux, l, m, r);
}



