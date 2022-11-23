#ifndef HASH_H
#define HASH_H
#include "structs.h"
#include "LinkedList.h"
int hash(char *nome, int M);
void ht_creat_jogo(int tblsz, jogo *st);
void ht_creat_eq(int tblsz, equipa *eq);
void expand_jogo(int tblsz_jogo, jogo *st, int M);
void expand_equipa(int tblsz_equipa,equipa *eq, int N);
void insert_equipa(char *key,equipa value,int tblsz, equipa *eq,int N);
void expand_equipa(int tblsz_equipa, equipa *eq, int N);
void insert_jogo(char *key, jogo value,int tblsz, jogo *st, int M);
void expand_jogo(int tblsz_jogo, jogo *st, int M);
equipa search_equipa(char *key, int tblsz, equipa *eq);
jogo search_jogo(char *key, int tblsz, jogo *st);
void delete_jogo(char *key, int tblsz, jogo *st, int M);
int get_vitorias(char *key, int tblsz, equipa *eq);
char* quem_ganhou(char *key, int tblsz, jogo *st);
int quem_ganhou_int(char *key, int tblsz,jogo *st);
void altera_score(char *key, int tblsz, int score1, int score2, jogo *st);
void altera_vitorias(char*key,int tblsz,int vitorias, equipa *eq);
char* obtem_equipa1(char *key,int tblsz, jogo*st);
char* obtem_equipa2(char *key,int tblsz, jogo *st);
#endif