#ifndef P2_H
#define P2_H

/* Header file que contem as estruturas utilizadas no projeto e os comandos */

/* Estrutura Equipa:
    Contem alguns dos ponteiros necessarios para a implementacao de uma
    lista duplamente ligada, next e prev. Contem tambem os dados utilizados
    na lista de equipas: nome e numero de vitorias. */
typedef struct Equipa {
    char *nome;
    int vitorias;
    struct Equipa *next, *prev;  
} Equipa;


/* Estrutura Lista de Equipas:
    Contem os ponteiros necessarios para a implementacao de uma lista
    duplamente ligada, head e last, constituida pelas equipas do sistema. */
typedef struct Lista_equipas {
    Equipa *head, *last;
} Lista_equipas;


/* Estrutura Hashtable das Equipas:
    Contem o ponteiro que diz respeito as entradas da hash: as equipas. */
typedef struct hastable_equipas {
    Equipa **entradas;
} hashtable_equipas;


/* Estrutura Jogo:
    Contem os ponteiros necessarios a implementacao de uma lista duplamente
    ligada, next e prev. Tambem contem os dados relativos a um jogo:
    nome, equipa 1 e equipa 2 e o resultado. */
typedef struct Jogo {
    char *nome;
    Equipa *equipa1, *equipa2;
    int score1, score2;
    struct Jogo *next, *prev;
} Jogo;


/* Estrutura Lista de Jogos:
    Contem os ponteiros necessarios a implementacao de uma lista
    duplamente ligada, head e last, constituida pelos jogos do sistema. */
typedef struct Lista_jogos {
    Jogo *head, *last;
} Lista_jogos;


/* Estrutura hashtable dos jogos:
   Contem o ponteiro que diz respeito as entradas da hashtable dos jogos:
   a estrutura dos jogos. */
typedef struct hashtable_jogos {
    Jogo **entradas;
} hashtable_jogos;


/* Funcoes relativas aos comandos das equipas */
Lista_equipas *A(int NL, char s[], hashtable_equipas *ht_equipa, Lista_equipas *lista_equipa);

void P(int NL, char s[], hashtable_equipas *ht_equipa);

void g(int NL, Lista_equipas *lista_equipa, hashtable_equipas *ht_equipa);


/* Funcoes relativas aos comandos dos jogos */
Lista_jogos *a(int NL, char s[], hashtable_jogos *ht_jogos, hashtable_equipas *ht_equipa, Lista_jogos *lista_jogo);

void p(int NL, char s[], hashtable_jogos *ht_jogo);

void l(int NL, Lista_jogos *lista_jogo);

Lista_jogos *r(int NL, char s[], hashtable_jogos *ht_jogos, hashtable_equipas *ht_equipa, Lista_jogos *lista_jogo);

Lista_jogos *s_altera(int NL, char s[], hashtable_jogos *ht_jogos, hashtable_equipas *ht_equipa, Lista_jogos *lista_jogo);

#endif

