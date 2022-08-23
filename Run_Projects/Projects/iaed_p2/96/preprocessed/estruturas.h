#ifndef estruturas_h
#define estruturas_h
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#define Tamanho_hash 149

/* estrutura das equipas */
typedef struct {                 
    char *nome;          /* ponteiro para o nome para garantir efeciencia da memoria */
    int vitorias;
}equipa;

/* estrutura dos blocos da hash das equipas e das lista ligada */
typedef struct bloco_h_equipa{
    equipa *equipa;               
    struct bloco_h_equipa *next;
}*bloco_hash_equipa;


/* estrutura dos jogos com a mesma logica das equipas */
typedef struct {
    char *nome;    
    equipa *equipa1,*equipa2;        /* ponteiros para as equipas dos jogos tambem para eficiencia da memoria */
    int score1,score2;
}jogo;

/* estrutura dos blocos da hash dos jogos e das lista ligada */
typedef struct bloco_h_jogo{
    jogo *jogo;
    struct bloco_h_jogo *next;
}*bloco_hash_jogo;

/* funcao hash comum as duas hash tables */
unsigned int hash(char *nome);      

/* funcoes auxiliares da hash table das equipas */
bloco_hash_equipa *inicializa_hash_e();
void guarda_equipa_hash(bloco_hash_equipa *table_e,equipa *e);
equipa *procura_equipa_hash(bloco_hash_equipa *table_e,char *nome);


/* funcoes auxiliares da hash table dos jogos */
bloco_hash_jogo *inicializa_hash_j();
void guarda_jogo_hash(bloco_hash_jogo *table_j,jogo *j);
jogo *procura_jogo_hash(bloco_hash_jogo *table_j,char *nome);
void apaga_jogo_hash(bloco_hash_jogo *table_j, char *nome);

#endif