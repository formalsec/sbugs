#ifndef PROJ2_H
#define PROJ2_H
/* Constantes*/
#define MAXNOME 1024  /* numero maximo de caracteres para os nomes de equipas e jogos incluindo '\0'*/
#define TABLE_SIZE 1097 /* tamanho das hash tables usadas no programa*/

/*Estrutura das equipas, contem o nome de cada equipa e o numero de jogos ganhos,
contem tambem um ponteiro para o jogo seguinte*/
typedef struct str_equipa{
    char *nome;
    int vitorias;
    struct str_equipa *nextE;
} *equipa; /* equipa e um ponteiro para a estrutura str_equipa*/

/*Estruturas dos jogos, contem o nome do jogo e de ambas as equipas participantes,
os scores de ambas as equipas e um id de jogo dado pela ordem que sao introduzidos*/
typedef struct str_jogo{
    char *nome, *eq1, *eq2;
    int sc1, sc2, id;
    struct str_jogo *nextJ;
} *jogo; /* jogo e um ponteiro para a estrutura str_jogo*/

/* Prototipos das funcoes usadas no programa*/
void FreeHTjogo(jogo * HTjogo);
void FreeJogo(jogo  aux);
void FreeHTequipa(equipa * HTequipa);
void FreeEquipa(equipa aux);
void FreeList (jogo head);
void FreeListE(equipa head);
void InsertJogo(char * nome, char * eq1, char * eq2, int sc1, int sc2, jogo * HTjogo, int id);
void InsertEquipa(char * nome, equipa * HTequipa);
void init_HTE(equipa * HTequipa);
void init_HTJ(jogo * HTjogo);
void cmd_A(char * nome, equipa * HTequipa, int NL);
void cmd_p(char * nome, jogo * HTjogo, int NL);
void cmd_P(char * nome, equipa * HTequipa, int NL);
void cmd_l(jogo * HTjogo, int NL, int id);
void cmd_g(equipa * HTequipa, int NL);
void cmd_r(char * nome, jogo * HTjogo, equipa * HTequipa, int NL);
void cmd_s(char * nome, jogo *HTjogo, int sc1, int sc2,equipa * HTequipa, int NL);
int cmd_a(char * nome, char * eq1, char * eq2, int sc1, int sc2, jogo * HTjogo, equipa * HTequipa, int NL, int id);
int Hash(char *v, int M);
equipa SearchEquipa(char * nome, equipa * HTequipa);
equipa ListaEquipas(equipa lista, char * nome, int vitorias);
jogo SearchJogo(char * nome, jogo * HTjogo);
jogo InsertEnd(jogo head, char * NOME,char * EQUIPA1,char * EQUIPA2, int score1, int score2);
jogo RemoveJogo(jogo head, char * nome);
jogo newjogo(char * nome, char * eq1, char * eq2, int sc1, int sc2, int id);
jogo AlteraScore(jogo head, char * nome, int sc1, int sc2, jogo * HTjogo);
#endif