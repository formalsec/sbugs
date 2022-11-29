#ifndef HEADS_H
#define HEADS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jogo
{
    char *nome;               /*Nome do jogo*/
    char *e1, *e2;            /*Nome das equipas*/
    int score1, score2;       /*Resultado da partida, pontos da equipa 1 e da equipa 2 respetivamente*/
    struct jogo *next, *prev; /*Ligacao a outro jogo, efeitos de criacao da lista ligada*/

} jogo;

typedef struct equipa
{
    char *nome;                 /*Nome da equipa*/
    int jogos_ganhos;           /*NUmero total de jogos ganhos da equipa*/
    struct equipa *next, *prev; /*Ligacao a outra equipa, efeitos de criacao da lista ligada*/
} equipa;

typedef struct HT_jogos
{
    jogo *p;               /*A hashtable apenas liga ao endereco da lista ligada, nao ocupando duas vezes o mesmo espaco*/
    struct HT_jogos *next; /*Liga ao proximo, para efeitos de criar o encadeamento externo na hashtable*/
    struct HT_jogos *prev;
} * HT_jogos;

typedef struct HT_equipas
{
    equipa *equipa;          /*A hashtable apenas liga ao endereco da lista ligada, nao ocupando duas vezes o mesmo espaco*/
    struct HT_equipas *next; /*Liga ao proximo, para efeitos de criar o encadeamento externo na hashtable*/
    struct HT_equipas *prev;
} * HT_equipas;

typedef struct
{
    jogo *head, *last; /*Estrutura para a criacao da lista ligada, permite adicionar elementos ao fim da lista, sem ter de a percorrer continuamente*/
} list_jogos;

typedef struct
{
    equipa *head, *last; /*Estrutura para a criacao da lista ligada, permite adicionar elementos ao fim da lista, sem ter de a percorrer continuamente*/
} list_equipas;

#endif

/*Heads HashtableJogos*/
HT_jogos *makeHTJ(int HT_tam);
void addHTJ(jogo *jogo, HT_jogos *heads, int HT_tam);
void remHTJ(char *nome, HT_jogos *heads, int HT_tam);
jogo *searchJogo(char *nome, HT_jogos *heads, int HT_tam);
void freeHTJ(HT_jogos *HT, int HT_tam);

/*Heads HashtableEquipas*/
HT_equipas *makeHTE(int HT_tam);
void addHTE(equipa *equipa, HT_equipas *heads, int HT_tam);
void remHTE(char *nome, HT_equipas *heads, int HT_tam);
equipa *searchEquipa(char *nome, HT_equipas *heads, int HT_tam);
void freeHTE(HT_equipas *HT, int HT_tam);

/*Heads HashtableGeral*/
int hashU(char *v, int HT_tam);
int compare_strings(char *first, char *second);

/*Listas Ligadas gerias*/
list_jogos *mk_list();
list_equipas *mk_list_eq();
void free_jogo(jogo *n);
void free_equipa(equipa *n);
void rm_jogo(list_jogos *jogos, jogo *n);
void free_list_jogos(list_jogos *jogos);
void free_list_equipas(list_equipas *teams);

/*Heads jogos*/
void add_jovo(int NL, list_jogos *jogos, HT_jogos *HT_jogos, HT_equipas *HT_equipas, int HT_tam);
void apaga_jogo(int NL, list_jogos *jogos, HT_jogos *HT_jogos, HT_equipas *HT_equipas, int HT_tam);
void lista_jogos(int NL, list_jogos *jogos);
void procura_jogo(int NL, HT_jogos *HT, int HT_tam);
void altera_score(int NL, HT_jogos *HT_jogos, HT_equipas *HT_equipas, int HT_tam);

/*Heads equipas*/
void add_equipa(int NL, list_equipas *teams, HT_equipas *HT_equipas, int HT_tam);
void procura_equipa(int NL, HT_equipas *HT_equipas, int HT_tam);
void encontra_equipas(int NL, list_equipas *teams);