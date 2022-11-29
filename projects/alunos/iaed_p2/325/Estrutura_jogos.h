#ifndef Estrutura_H
#define Estrutura_H

#include "Hash_equipas.h"

/* Lista duplamente ligada de jogos que guarda o nome do jogo, o nome das duas equipas e os golos
 * marcados de cada uma das equipas. */
typedef struct stru_jogo {
    char *nome;
    Equipas_hash equipa1, equipa2;
    int score1, score2;
    struct stru_jogo *next, *previous;
} jogo;

typedef struct {
    struct stru_jogo *head, *last;
} Jogos;

/* Funcao que inicializa a lista dos jogos. */
Jogos *init_Jogos();

/* Funcao que adiciona um novo logo a lista de jogos alocando memoria. */
jogo *adiciona_jogo(Jogos *j, char *n, Equipas_hash e1, Equipas_hash e2, int s1, int s2);

/* Funcao que elimina um certo jogo da lista de jogos, libertando a memoria deste. */
void delete_jogoP(Jogos *j, jogo *del);

/* Funcao que elimina todos os jogos da lista de jogos libertando toda a memoria que esta continha.
 */
void free_Jogos(Jogos *j);

#endif
