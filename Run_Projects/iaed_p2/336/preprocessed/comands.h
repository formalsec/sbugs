#ifndef COMANDS
#define COMANDS
/* Estrutura da base de dados */
typedef struct data_base {
	l_game *game_list;          /* Lista de jogos */
	game_link **hash_games;     /* Hash table de jogos */
	t_node *teams_pile;			/* Pilha de equipas */
	link_t **hash_teams;		/* Hash table de equipas */
	int NL;                     /* Numero da linha do comando de input */
} d_b;

/* Inicializa a base de dados */
d_b* init_data_base();

/* Liberta memoria alocada para a base de dados */
void destroy_data(d_b *data_base);

/* Adiciona um novo jogo */
void add_new_game(d_b *data_base);

/* Imprime todos os jogos pela ordem que foram introduzidos na base de dados */
void list_games(d_b *data_base);

/* Procura e printa o nome do jogo */
void search_name_game(d_b *data_base);

/* Remove um jogo da base de dados (tanto da hash table como da lista de jogos)*/
void remove_game(d_b *data_base);

/* Muda o resultado de um jogo */
void score_change(d_b *data_base);

/* Adiciona uma nova equipa a base de dados */
void add_new_team(d_b *data_base);

/* Printa o nome da equipa e o seu numero de vitorias */
void search_name_team(d_b *data_base);

/* Printa as equipas com maior numero de vitorias por ordem alfabetica */
void best_teams(d_b *data_base);

/* Chama uma funcao segundo o comando de input */
void comand_list(char comand, d_b *data_base);

#endif