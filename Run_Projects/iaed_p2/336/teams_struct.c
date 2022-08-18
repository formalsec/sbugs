#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams_struct.h"

#define MAX_STR 1024
#define T_HASH 10000


/* Adiciona um novo elemento a pilha de equipas */
t_node* push_team(t_node *head, char *team){
    t_node *new_node = malloc(sizeof(t_node));
    new_node->next = head;
    new_node->team_name = malloc(sizeof(char) * (strlen(team) + 1));
    strcpy(new_node->team_name, team);
    new_node->wins = 0;
    return new_node;
}

/* Retira o elemento que e a cabeca da pilha */
t_node* pop_team(t_node *head){
    t_node *node = head->next;
    free(head->team_name);
    free(head);
    return node;
}

/* Elimina a pilha */
void destroy_pile(t_node *head){
    while(head){
        head = pop_team(head);
    }
}

/* Inicializa uma hash table de equipas */
link_t** init_hash_teams(){
    int i;
    link_t** hash_teams;
    hash_teams = malloc(sizeof(link_t) * T_HASH);
    for(i = 0; i < T_HASH; i++){
        hash_teams[i] = NULL;
    }
    return hash_teams;
}

/* Devolve a key para hash table segundo a string de input e o tamanho da tabela */
int hashU(char *v, int M){
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M - 1))
        h = (a*h + *v) % M;
    return h;
}


/* Numa certa key da hash table coloca um link na cabeca e liga-o ao antigo */
link_t* insert_beguin_hash_team(link_t *head, t_node *team){
    link_t *new_head = malloc(sizeof(link_t));
    new_head->link_team = team;
    new_head->next_link = head;
    return new_head;
}

/* Coloca uma equipa na hash table */
void insert_hash_team(link_t **List_links, t_node *Team){
    int key = hashU(Team->team_name, T_HASH);
    link_t *new_head = insert_beguin_hash_team(List_links[key], Team);
    List_links[key] = new_head; /* Ponteiro fica a apontar para a nova cabeca */
}

/* Retorna o ponteiro que aponta para o nome da equipa de input (retorna NULL se a equipa nao existir) */
t_node* search_team(link_t **List_links, char *name){
    int key = hashU(name, T_HASH);
    t_node *team = NULL;
    link_t *head = List_links[key];
    while(List_links[key]){
        if(!strcmp(List_links[key]->link_team->team_name, name)){
            team = List_links[key]->link_team;
            break;
        }
        else
            List_links[key] = List_links[key]->next_link;
    }
    List_links[key] = head; /* Reapontar para a cabeca original */
    return team;
}

/* Devolve 0 se dois elementos nao estiverem por ordem alfabetica (da esquerda para a direita) */
int less(t_node *team_one, t_node *team_two){
    int i, booleano = -1;
    for (i = 0; booleano == -1; i++){ /* verifica a letra de maior relevancia enquanto for igual nas duas descricoes */
        if (team_one->team_name[i] > team_two->team_name[i] || team_two->team_name[i] == '\0') {
            booleano = 0;
            break;
        }
        else if (team_one->team_name[i] < team_two->team_name[i] || team_one->team_name[i] == '\0'){
            booleano = 1;
            break;
        }
    }
    return booleano;
}

/* Junta duas particoes da array de forma ordenada */
void merge(t_node **array, int head, int midle, int last){
    int i, j, k;    /* i - iteravel que comeca no inicio da particao, j - iteravel que comeca no fim da particao, k - iteravel que percorre a array principal */
    t_node *aux[T_HASH]; /*  aux - array auxiliar que tem como conteudo os valores das particoes */
    for (i = midle + 1; i > head; i--)  /* primeira particao */
        aux[i - 1] = array[i - 1];
    for (j = midle; j < last; j++)      /* segunda particao por ordem invertida */
        aux[last + midle - j] = array[j + 1];
    for (k = head; k <= last; k ++){
        if (less(aux[j], aux[i]))
            array[k] = aux[j--];
        else
            array[k] = aux[i++];
    }
}

/* Funcao que ordena os elementos por ordem alfabetica */
void mergesort(t_node **array, int head, int last){
    int midle = (last + head)/2;               /* meio da array */
    if (last <= head)
        return;
    mergesort(array, head, midle);      /* particoes do lado direito */
    mergesort(array, midle + 1, last);  /* particoes do lado esquerdo */
    merge(array, head, midle, last);     /* juntar particoes de forma ordenada */
}


/* Ordena por ordem alfabetica o nome das equipas da pilha */
t_node* sort_teams_pile(t_node *head, int size){
    int i;
    t_node *teams_list[T_HASH];
    t_node *first_head = head, *sorted_pile = NULL;
    for(i = 0; i < size; i++){
        teams_list[i] = head;
        head = head->next;
    }
    mergesort(teams_list, 0, size - 1);
    for(i = size - 1; i >= 0; i--)
        sorted_pile = push_team(sorted_pile, teams_list[i]->team_name);
    destroy_pile(first_head);
    return sorted_pile;
}

/* Liberta a memoria toda alocada pela hash table */
void destroy_hash_teams(link_t **List_links){
    link_t *new_head;
    int i;
    for(i = 0; i < T_HASH; i++){
        while(List_links[i]){
            new_head = List_links[i]->next_link;
            free(List_links[i]);
            List_links[i] = new_head;
        }
    }
    free(List_links);
}