#ifndef JOGOS_H
#define JOGOS_H

/* Jogo em hash */
typedef struct match {
    char *nome;            /* String nao vazia com max = STRMAX */
    char *Equipas[2];      /* 2 Strings nao vazias com max = STRMAX */
    unsigned int score[1]; /* Par de numeros inteiros nao negativo */
    struct match *next, *prev;
} Jogo;

typedef struct match_list {
    struct match *head, *last;
} Jogos;

typedef struct team {
    char *nome;            /* String nao vazia com max = STRMAX */
    unsigned int jganhos;  /* Numero total de jogos ganhos */
    struct team *next;
} Equipa;

typedef struct team_list {
    struct team *head, *last;
} Equipas;


/* Organizacao interna das chaves */
typedef char* Chave;
#define chave(a) (a->nome)


/* Funcao de hashing */
int hash(Chave value, int M);

/* Funcao que cria uma lista de jogos */
Jogos* init_jogos();

/* Funcao que cria uma lista de equipas */
Equipas* init_equipas();

/* Funcao que cria um jogo */
Jogo* novo_jogo();

/* Funcao que cria uma equipa */
Equipa* nova_equipa();

/* Funcao que remove um jogo da lista de jogos e da memoria */
Jogos* remove_jogo(Jogos *Lst, char* text);

/* Funcao que encontra o maior numero de vitorias */
unsigned int encontra_max(Equipas *Lst);

/* Funcao que encontra as equipas com o maior numero de vitorias
e coloca os seus nomes em Nomes */
int encontra_melhores(Equipas*Lst,unsigned int Max,char**Nomes);

/* Funcao que ordena dois nomes lexicograficamente */
int compare(const void *a, const void *b);

/* Funcao que liberta a memoria associada a um jogo */
void elimina_jogo(Jogo *J);

/* Funcao que liberta a memoria associada a uma equipa */
void elimina_equipa(Equipa *E);

#endif