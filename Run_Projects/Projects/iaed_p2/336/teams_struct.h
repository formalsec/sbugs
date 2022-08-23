#ifndef TEAMS_STRUCT
#define TEAMS_STRUCT

/* A lista de equipas esta organizada numa pilha */
typedef struct stru_team_node{
		struct stru_team_node *next;
		char *team_name;
		int wins;	
} t_node;

/* Hash table ira conter ponteiros para cada nome de equipa */
typedef struct link_team{
	t_node *link_team;
	struct link_team *next_link; /* Para o mesmo hash, links simplesmente ligados */
} link_t;

/* Adiciona um novo elemento a pilha de equipas */
t_node* push_team(t_node *head, char *team);

/* Retira o elemento que e a cabeca da pilha */
t_node* pop_team(t_node *head);

/* Elimina a pilha */
void destroy_pile(t_node *head);

/* Inicializa uma hash table de quipas */
link_t** init_hash_teams();

/* Devolve a key para hash table segundo a string de input e o tamanho da tabela */
int hashU(char *v, int M);

/* Numa certa key da hash table coloca um link na cabeca e liga-o ao antigo */
link_t* insert_beguin_hash_team(link_t *head, t_node *team);

/* Coloca uma equipa na hash table */
void insert_hash_team(link_t **List_links, t_node *Team);

/* Retorna o ponteiro que aponta para o nome da equipa de input (retorna NULL se a equipa nao existir) */
t_node* search_team(link_t **List_links, char *name);

/* Devolve 0 se dois elementos nao estiverem por ordem alfabetica (da esquerda para a direita) */
int less(t_node *team_one, t_node *team_two);

/* Junta duas particoes da array de forma ordenada */
void merge(t_node **array, int ini, int meio, int ult);

/* Funcao que ordena os elementos por ordem alfabetica */
void mergesort(t_node **array, int ini, int ult);

/* Ordena por ordem alfabetica o nome das equipas da pilha */
t_node* sort_teams_pile(t_node *head, int size);

/* Liberta a memoria toda alocada pela hash table */
void destroy_hash_teams(link_t **List_links);

#endif