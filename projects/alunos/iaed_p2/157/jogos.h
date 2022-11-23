#include "equipas.h"


/* Estrutura jogo */
typedef struct jogo {
    /* Ponteiro para string que guarda o nome */
    char * nome;
    
    /* Ponteiros para as equipas que participam no jogo */
    pt_equipa equipa1;
    pt_equipa equipa2;

    /* Pontuacao de cada equipa */
    int score1, score2;
    
} * pt_jogo;


/* Nodes para jogos */
typedef struct node_jogo {
    /* Ponteiro para jogo */
    pt_jogo jogo;

    /* Ponteiro para proximo node */
    struct node_jogo * next;

} * link_jogo;


/* Estrutura nome */
typedef struct nome {
    /* Ponteiro para string que guarda o nome */
    char * nome;

    /* Ponteiro para proximo nome */
    struct nome * next;

} * pt_nome;


/* PROTOTIPOS */

/* Liberta espaco associado ao jogo e ao seu nome */
void free_jogo(pt_jogo a);

/* Devolve um ponteiro para um novo jogo com as caracteristicas indicadas */
pt_jogo novo_jogo(char * nome, char * equipa1, char * equipa2, int score1, int score2, link_equipa * equipas);

/* True caso o jogo exita no sistema, False caso contrario */
bool jogo_existe(char * nome, link_jogo * jogos);

/* Devolve um ponteiro para o jogo procurado, NULL caso nao encontre */
pt_jogo procura_jogo(char * nome, link_jogo * jogos);

/* Insere o jogo dado no respetivo lugar na tabela */
void insere_jogo_tabela(pt_jogo jogo, link_jogo * jogos);

/* Inicializa todas as entradas da tabela de jogos a NULL */
link_jogo * init_jogos(link_jogo * tabela);

/* Apaga o jogo da tabela, libertando o espaco respetivo */
void apaga_jogo_tabela(char * nome, link_jogo * jogos);

/* Apaga o nome da lista de nomes, devolve a cabeca da nova lista de nomes */
pt_nome apaga_nome_lista(pt_nome nomes_jogos, char * nome);

/* Liberta todo o espaco alocado pelas tabelas de jogos, equipas e lista de nomes */
void free_all(link_jogo * jogos, link_equipa * equipas, pt_nome nomes_jogos);

/* Coloca o nome na ultima posicao da lista e adiciona uma posicao nova a seguir, devolve a cabeca da lista */
pt_nome novo_nome(char * nome, pt_nome nomes_jogos);
