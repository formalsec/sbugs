#ifndef Estruturas
#define Estruturas
#define MIL_VINTE_QUATRO 1024   /* Tamanho maximo do nome de uma equipa e jogo */
#define VALOR_HASH 10000         /* Numero utilizado na funcao de hash */

/* Estrutura de uma equipa */
typedef struct equipa {
    char *nome_equipa;
    int n_vitorias;
}Equipa;

/* Estrutura do no de uma equipa */
typedef struct no1{
    Equipa *eq;
    struct no1 *next;
}no_equipas;

/* Estrutura da hash table das equipas */
typedef struct {
    no_equipas *no[VALOR_HASH];
}lista_equipas;

/* Estrutura da lista ligada auxiliar com as equipas */
typedef struct no1_aux{
    no_equipas *head;
}lista_equipas_aux;

/* Estrutura de um jogo */
typedef struct jogo {
    char *nome_jogo;
    char *equipa1;
    char *equipa2;
    int resultado1;
    int resultado2;
}Jogo;

/* Estrutura de um jogo na lista ligada auxiliar */
typedef struct jogo_aux {
    char *nome_jogo;
    char *equipa1;
    char *equipa2;
    int resultado1;
    int resultado2;
}Jogo_aux;

/* Estrutura do no de um jogo */
typedef struct no2{
    Jogo *jog;
    struct no2 *next, *previous;
}no_jogos;

/* Estrutura do no de um jogo na lista ligada auxiliar */
typedef struct no2_aux{
    Jogo_aux *jog;
    struct no2_aux *next, *previous;
}no_jogos_aux;

/* Estrutura da hash table dos jogos */
typedef struct {
    no_jogos *no[VALOR_HASH];
}lista_jogos;

/* Estrutura da lista duplamente ligada auxiliar com os jogos */
typedef struct no2_aux1 {
    no_jogos_aux *head, *last;
}lista_jogos_aux;

/* Daqui para baixo estao listados todos os prototipos de funcoes que de alguma forma \
   recorrem as estruturas acima listadas para as alterar */

int hash(char *v);

void inicia_lista_equipas(lista_equipas * a);

void inicia_lista_equipas_aux(lista_equipas_aux *a);

void inicia_lista_jogos(lista_jogos *a);

void inicia_lista_jogos_aux(lista_jogos_aux *a);

Equipa* procura_equipa(char nome_equipa[], lista_equipas *a);

void insere_equipa(lista_equipas *a, Equipa *b);

void insere_equipa_aux(lista_equipas_aux *a, Equipa *b);

Jogo* procura_jogo(char nome_jogo[], lista_jogos *a);

void insere_jogo(lista_jogos *a, Jogo *b, lista_equipas *c);

void insere_jogo_aux(lista_jogos_aux *a, Jogo_aux *b);

void muda_n_vitorias (lista_equipas *a, lista_jogos *b, char nome_jogo[]);

no_jogos  * remove_jogo(char nome_jogo[], lista_jogos *a, lista_equipas *c);

void muda_resultado(int nl, char nome_jogo[], int res_equipa1, int res_equipa2, lista_jogos *a, lista_equipas *d);

void free_hash_equipas (lista_equipas *a);

void free_lista_equipas (lista_equipas_aux *a);

void free_hash_jogos (lista_jogos * a);

void free_lista_jogos (lista_jogos_aux *a);

void free_geral (lista_equipas *a, lista_equipas_aux *b, lista_jogos *c, lista_jogos_aux *d);

int aux_merge(no_equipas *a, no_equipas *b);

void merge(no_equipas **a, int l, int m, int r);

void mergesort(no_equipas **a,int l,int r);

#endif