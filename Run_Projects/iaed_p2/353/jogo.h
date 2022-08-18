#include "equipas.h"

/* estrutura do jogo, da hashtable com jogos e da linked list que guarda a ordem de insercao dos jogos */
typedef struct jogo{
    char* nome;             /* nome do jogo */
    char* equipa1;          /* nome da equipa 1 */
    char* equipa2;          /* nome da equipa 2 */
    int score1;             /* numero de golos da equipa 1 */
    int score2;             /* numero de golos da equipa 2 */
    struct jogo* next;
}link_jogo;

typedef struct{
    link_jogo **links;      /* ponteiro para um ponteiro */
}ht_jogo;

typedef struct linkedlist{  
    link_jogo *jogo;           
    struct linkedlist* next;
}ll_jogos;

/* declaracao de funcoes */
ht_jogo *ht_init(void);

link_jogo *ht_pair(ht_jogo *hashtable, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2);
link_jogo *st_search_jogo(ht_jogo *hashtable, const char *nome);

void ht_set(ht_jogo *hashtable, ll_jogos **ll_head, ht_equipas *hashtable_equipas, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2,int NL);
void ht_search(ht_jogo *hashtable, const char *nome, int NL);
void ht_dump(ht_jogo *hashtable);
void ht_del(ht_jogo *hashtable, const char *nome, int NL);
void ht_change(ht_jogo *hashtable, ht_equipas *hashtable_equipas, const char *nome, int score1, int score2, int NL);
void insertEndJogos(ll_jogos **head_ref, link_jogo *jogo);
void deleteNode(ll_jogos **head_ref, link_jogo *jogo);
void deleteList(ll_jogos **head);