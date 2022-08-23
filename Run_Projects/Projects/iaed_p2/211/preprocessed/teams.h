#ifndef IAED_P2_FINAL_TEAMS_H
#define IAED_P2_FINAL_TEAMS_H

#define HASH_CAP_T 1000
#define MAX_CHARS_T 1024

/* Estrutura de no de equipa */
typedef struct stru_node_team {
    struct stru_node_team *next;
    char *desc;
    int victories;
} node_team;

/* Estrutura de lista ligada das equipas*/
typedef struct l_team {
    struct stru_node_team *head, * last;
} linked_list_teams;

/* Estrutura de no da hash table das equipas*/
typedef struct hash_node_team{
    struct stru_node_team *node;
    struct hash_node_team *next;
} ptr_team;

/* Estrutura de hash table das equipas */
typedef struct hash_teams{
    struct hash_node_team *nodes[HASH_CAP_T];
} hash_table_teams;

/* cria um no de uma equipa, adiciona-o a lista ligada de equipas e devolve esse no */
node_team * add_linked_list_team(linked_list_teams * linked_teams, char desc[], int victories);

/* cria um ptr_team que aponta para o no n, e coloca-o na hash table das equipas */
void add_hash_table_team(hash_table_teams * hash_teams, node_team * n);

/* procura um ptr_team que aponta para o no com a descricao d e devolve esse ptr_team */
ptr_team * search_team(hash_table_teams * hash_teams, char d[]);

/* procura o maior numero de vitorias das equipas e devolve esse valor */
int search_most_vict_teams(linked_list_teams * linked_teams);

/* destroi a hash table das equipas, fazendo free do seu conteudo */
void destroy_hash_teams(hash_table_teams *hash_teams);

/* destroi a lista ligada das equipas, fazendo free do seu conteudo */
void destroy_linked_teams(linked_list_teams *linked_teams);

#endif

