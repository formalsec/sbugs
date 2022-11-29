#ifndef OPRERATIONSOVERTABLE_H
#define OPRERATIONSOVERTABLE_H
#define MAX_TABEL 1051


typedef struct jogo
{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
}*game;

/* Estrutura que vai definir cada jogo */

typedef struct item
{
    game j;
    struct item *next;

}*campeonato;
/* Estrutura da hashtable dos jogos */

typedef struct copas
{
    char *text;
    char *Pequipa;
    char *Sequipa;
    int Pscore;
    int Sscore;
    struct copas *next; 
}copa;

/* Estrutura da lista de jogos por ordem de insercao */

typedef struct Junta
{
    campeonato *hashtable;
    copa *lista;
}Junta;

/* Uma megaestrutura que serve como ponteiro para a hashtable e para a lisgta de jogos */ 

int hash(char *v, int M);
campeonato *init_array(campeonato *heads, int M);
campeonato *insert_hash(campeonato *heads, game j, int M);
campeonato insertBeginList(campeonato head, game j);
campeonato NEW_NODE(game jogo);
campeonato search_hash(campeonato *heads, char *name);
campeonato searchList(campeonato head, char *name);
copa *InsereEnd(copa *lista, game head);
copa *NOVA_COPA(game head);
campeonato *removeEl(campeonato *heads, char *text, int M);
campeonato removeHashEl(campeonato head, char *text);
copa *RLista(copa *j, char *text);
copa *Search_Copas(copa *head, char *nome);
char *strdup(const char *src);
campeonato libertahashtable(campeonato jogo);
copa *libertalista(copa *lista);

#endif