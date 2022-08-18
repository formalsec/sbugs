#ifndef HASH_H
#define HASH_H


/* Estruturas */

typedef struct Jogo{
    char* nome;
    char* equipa_1;
    char* equipa_2;
    int pontuacao[2];
} *pJogo;

typedef struct Equipa{
    char *nome;
    int vitorias;
} *pEquipa;

                
typedef struct node_jogo{
    pJogo jogo;
    struct node_jogo *next;
} *link_jogo;

typedef struct node_equipa{
    pEquipa equipa;
    struct node_equipa *next;
} *link_equipa;

/* Estrutura para a Hashtable, em que cada indice 
vai ter uma lista para equipas e outra para jogos */
typedef struct Listas{
    link_jogo head_jogos;
    link_jogo tail_jogos;
    link_equipa head_equipas;
    link_equipa tail_equipas;
} *pListas;

/* Estrutura que vai possuir uma lista com todos 
os jogos por ordem de insercao e um vetor com 
todas as equipas tambem por ordem de insercao */
typedef struct Lst_Ord{
    link_jogo head_jogos;
    link_jogo tail_jogos;
    pEquipa* lista_equipas;
    int cont_equipas; /* indica o numero atual de equipas no sistema */
} *pLst_Ord;


/* Prototipos */


/* associa um numero a uma string para ser o indice da hashtable */
int hashU(char *v, int m);

/* aloca memoria dinamica para uma string */
char* str_dup(char* buffer);

/* inicializa a hashtable */
pListas* inicializa_listas(pListas* listas, int m);

/* inicializa a estrutura com os jogos e equipas ordenados por insercao */
pLst_Ord inicializa_lista_ordenada(pLst_Ord lista_ordenada);

/* insere uma equipa na hashtable */
void insere_equipa(pListas lista_equipas, link_equipa nova_equipa);

/* insere um jogo na hashtable */
void insere_jogo_hash(pListas lista_jogos, link_jogo novo_jogo);

/* insere um jogo na estrutura com listas e jogos ordenados */
void insere_jogo_lista_ordenada(pLst_Ord lista_jogos, link_jogo novo_jogo);

/* procura por uma equipa na hashtable */
link_equipa procura_equipa(pListas* listas, char* nome, int m);

/* procura por um jogo na hashtable */
link_jogo procura_jogo(pListas* listas, char* nome, int m);

/* elimina um jogo da hashtable */
void elimina_hash(pListas lista_jogos, char* nome);

/* elimina um jogo da lista com os jogos ordenados por insercao */
void elimina_lista_ordenada(pLst_Ord lista_jogos, char* nome);

/* adiciona uma equipa ao sistema */
void adiciona_equipa(int NL, pListas* listas, pLst_Ord lista_ordenada, int m);

/* adiciona um jogo ao sistema */
void adiciona_jogo(int NL, pListas* listas, pLst_Ord lista_ordenada, int m);

/* procura uma equipa no sistema e indica quantos jogos ganhou */
void consulta_equipa(int NL, pListas* listas, int m);

/* procura um jogo no sistema e indica as suas informacoes:
nome do jogo, equipas que jogaram, e pontuacao */
void consulta_jogo(int NL, pListas* listas, int m);

/* lista todos os jogos pela ordem de insercao 
no sistema, indicando as informacoes de cada um */
void jogos_ordenados(int NL, pLst_Ord lista_ordenada);

/* remove um jogo do sistema */
void remove_jogo (int NL, pListas* listas, pLst_Ord lista_ordenada, int m);

/* altera a pontuacao de um jogo, modificando o numero 
de vitorias das equipas envolvidas caso necessario */
void altera_pontuacao(int NL, pListas* listas, int m);

/* funcao de comparacao do qsort para ordenar as equipas
segundo o seu numero de vitorias, por ordem decrescente */
int compara_vitorias(const void* a, const void* b);

/* funcao de comparacao do qsort para ordenar as 
equipas segundo o seu nome, por ordem crescente */
int compara_nomes(const void* a, const void* b);

/* lista todas as equipas que estao empatadas em primeiro lugar
em termos de vitorias, listando-as por ordem lexicografica */
void ordena_equipas_vitorias(int NL, pLst_Ord lista_ordenada);

/* faz free de uma lista de equipas */
void free_equipas(link_equipa head_equipas);

/* faz free de uma lista de jogos */
void free_jogos(link_jogo head_jogos, int flag_struct);

/* faz free da hashtable */
void free_listas(pListas* listas, int m);

/* faz free da lista com os jogos e equipas ordenados */
void free_lista_ordenada(pLst_Ord lista_ordenada);


#endif