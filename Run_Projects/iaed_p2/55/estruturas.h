#ifndef _ESTRUTURAS_
#define _ESTRUTURAS_


/* Estruturas dos nos */

typedef struct estr_jogo{
    struct estr_pt *pt_no_ponteiro;
    char** jogo;
    char** equipa1;
    char** equipa2;
    int* score1;
    int* score2;
    struct estr_jogo *proximo;/*, *anterior;*/
} no_jogo;

typedef struct estr_jogo* elo_jogo;


typedef struct estr_equipa{
    char** equipa;
    int* vitorias;
    struct estr_equipa *proximo;/*, *anterior;*/
} no_equipa;

typedef struct estr_equipa* elo_equipa;


typedef struct estr_pt{
    struct estr_jogo *ponteiro;
    struct estr_pt *proximo;/*, *anterior;*/
} no_ponteiro;
 
typedef struct estr_pt* elo_ponteiro;


/* Estruturas das Listas */

typedef struct{
    struct estr_jogo *inicio, *fim;
} lista;


typedef struct{
    struct estr_equipa *inicio, *fim;
} lista_equipa;


typedef struct{
    struct estr_pt *inicio, *fim;
} lista_ponteiro;



/* Cria/inicializa/retorna um no_equipa (struct estr_equipa). */
elo_equipa cria_no_equipa(char* equipa);

/* Cria/inicializa/retorna um no_jogo (struct estr_jogo). */
elo_jogo cria_no_jogo(char* jogo, char* equipa1, char* equipa2, int score1, int score2);

/* Cria/inicializa/retorna um no_ponteiro (struct estr_ptr). */
elo_ponteiro cria_no_ponteiro(elo_jogo pt_jogo);



/* Liberta toda a memoria associada a um no_equipa (struct estr_equipa) */
void liberta_no_equipa(elo_equipa no_libertar);

/* Liberta toda a memoria associada a um no_jogo (struct estr_jogo) */
void liberta_no_jogo(elo_jogo no_libertar);

/* Liberta toda a memoria associada a um no_ponteiro (struct estr_ptr) */
void liberta_no_ponteiro(elo_ponteiro no_libertar);



/* Duplica string */
char* duplica_string(char* cadeia_caracteres);


#endif