#ifndef jogo_h
#define jogo_h

#include "equipa.h"

typedef struct ligadadupla{
    char *  nome_jogo;
    char * equipa1;
    char * equipa2;
    int pontos1;
    int pontos2;
    struct ligadadupla * anterior;
    struct ligadadupla * proximo;
} NoListaJogos;

typedef struct jogo{
    NoListaJogos * inicio, * fim;
} inicioFimJogos;

typedef struct s_hash_node{
    struct s_hash_node * proximoNo;
    NoListaJogos * informacoes_jogo;
} hash_node;

typedef struct{
    hash_node ** tb_jogo;
    size_t capacidade;
} hash_table;

hash_table * cria_hash_table();

hash_node * cria_no(hash_node * inicio);

int verificaExiste_jogo(hash_table * hashJogo,  char * jogo);

int verificaEquipaDentro_aux_1(hash_table_equipa* t, char * equipa1, size_t h);

int verificaEquipaDentro_aux_2(hash_table_equipa* t, char * equipa2, size_t h);

void aumentaGanhos(hash_table_equipa * hashEquipa, hash_node_equipa * equipaAux, size_t h_eq, char * equipa);

void adiciona_jogo(hash_table * hash_jogo, int * Nr_linha, hash_table_equipa * hashEquipa, inicioFimJogos * Lista_jogos);

void print_info_jogo(int * Nr_linha, hash_node *cp);

void procura_jogo(hash_table * t, int *Nr_linha);

void tiraVitorias(hash_table_equipa *eq, hash_node_equipa *equipa_aux, char * equipa, size_t h_eq);

void acrescenta_vitorias(hash_table_equipa *eq, hash_node_equipa *equipa_aux,  char *equipa, size_t h_eq);

void altera_score(hash_table * t, int * Nr_linha, hash_table_equipa * eq);

void remove_no(inicioFimJogos * lista, hash_node * jogo_aux);

void removeDaHash(hash_node * temp, hash_node * ant, hash_table * t, char * nome_jogo, size_t h);

void remove_jogo_aux(hash_table * t, hash_table_equipa * eq, inicioFimJogos * lista, char * nome_jogo);

void remove_jogo(hash_table * t, hash_table_equipa * eq, inicioFimJogos * lista,  int * Nr_linha);

void lista_todos(inicioFimJogos * inicioFim, int * Nr_linha);

void free_hash_table_jogo(hash_table * t);                  
             
void liberta_dupla(inicioFimJogos * lista);


#endif