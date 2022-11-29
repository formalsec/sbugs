#ifndef STRUCTS_H
#define STRUCTS_H

/* constantes globais ao longo do programa */
#define MAX_NAME 1023
#define TABLE_SIZE 10000

/* estrutura game_n que representa cada jogo */
typedef struct game
{
  char *nome;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
  /* ponteiro para colocar o jogo na hash_table */
  struct game *next;
  /* ponteiro para colocar o mesmo jogo na lista */
  struct game *lista;
} game_n;

/* estrutura team_n que representa cada equipa */
typedef struct team
{
  char *name;
  int wins;
  struct team *next;
  struct team *lista;
} team_n;

/* prototipo da funcao hash */
unsigned int hash_function(char *);

/* prototipos relacionados com a hash table para os jogos */
void iniciar_hash_table(game_n **);
void inserir_hash_table(game_n **, game_n *);
void free_hash_table(game_n **);

/* prototipos relacionados com a hash table para as equipas */
void iniciar_hash_teams(team_n **);
void inserir_hash_teams(team_n **, team_n *);
void free_hash_teams(team_n **);

/* linked list dos jogos */
game_n *inserir_na_head(game_n *, game_n *);

/* linked list das equipas */
team_n *inserir_na_head_teams(team_n *, team_n *);

/* funcoes de free de um no */
void free_jogo(game_n *);
void free_equipa(team_n *);

#endif