#define MAX_O 10

/* Constante que define o n maximo de caracteres num jogo ou numa equipa. */
#define MAX_CHARS 1023

/* Constantes que definem um potencial maximo n de jogos (MAX_G) e equipas (MAX_T). */
#define MAX_G 3500
#define MAX_T 3500

/* Estrutura associada ao objeto Jogo. */
typedef struct game {
    char name[MAX_CHARS + 1], team1[MAX_CHARS + 1], team2[MAX_CHARS + 1];
    int score1, score2;
} Game;

/* Estrutura associada ao objeto Equipa. */
typedef struct team {
    char name[MAX_CHARS + 1];
    int victories;
} Team;
