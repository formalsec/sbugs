#include "equipa.h" /* atraves deste include, acesso os ficheiros equipa.h e Jogo.h */
/* estrutura jogo representa um jogo composto pelo seu nome, os nomes das duas equipas e o score das mesmas */

struct jogo{
    char *Nome;
    char *Equipa_Casa;
    char *Equipa_Fora;
    int  Score_Equipa_Casa;
    int  Score_Equipa_Fora;
};
/* Jogo e um ponteiro paraa jogo */
typedef struct jogo* Jogo;


struct lista{
    Jogo jogo;
    struct lista* next;
};
typedef struct lista* Lista;

/* Prototipos das funcoes referentes aos jogos e a sua lista*/

Jogo novo_jogo(char *nome, char *equipa, char *equipa2, int score1, int score2);
Jogo procura(char *nome, Jogo* Hashtable, int tamanho_Hashtable);
int procura_indice(Jogo* Hashtable, char* nome, int tamanho_Hashtable);
Lista insere_lista(Lista lista, Jogo jogo);
Lista apaga_na_lista(Lista lista, char *nome);
int print_lista(Lista lista, int NL);
int free_jogos(Lista lista);



