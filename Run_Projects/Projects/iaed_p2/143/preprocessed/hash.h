#include <stdio.h>


/* estrutura das Equipas */
typedef struct Equipa{
    char *nome;
    int n_vitorias;
}*equipa; /* *equipa eh um ponteiro para a estrutura Equipas */


/* estrutura para a hash das Equipas */
typedef struct hash_Equipa{
    equipa *equipas;
    unsigned int tam_hash;
    unsigned int n_equipas;
}Hash_Equipa;


/* estrutura dos Jogos */
typedef struct Jogo{
    char *nome;
    equipa equipa1;
    int score_equipa1;
    equipa equipa2;
    int score_equipa2;
    int ordem_input;
}*jogo; /* *jogo eh um ponteiro para a estrutura Jogos */
   

/* estrutura para a hash dos Jogos */
typedef struct hash_Jogos{
    jogo *jogos;
    unsigned int tam_hash;
    unsigned int n_jogos;
    int numero_jogos;
}Hash_Jogos;



/* -------- prototipos funcoes -------- */


/* ----prototipos funcoes da hash table das equipas---- */


/*funcao recebe um nome de uma equipa e um int M (tamanho da hash) 
e que determina em que posicao da hash a equipa com esse nome fica */
int Equipa_hash(char *nome, int M);

/* funcao recebe um int m e um unsigned int *M(ambos tamanho da hash) e,
recebe tambem o ponteiro do tipo equipa para as equipas. retorna o ponteiro das 
equipas que esta na Hash_Equipa*/
equipa * Equipa_init(int m, unsigned int *M, equipa *Equipa);

/* funcao recebe um int M(tamanho da hash), um ponteiro do tipo equipa
para as equipas e uma equipa p que vai ser inserida na hash */
void Equipa_insert(int M, equipa *Equipa, equipa p);

/* funcao (do tipo equipa) recebe um int M(tamanho da hash), um Nome(nome da equipa) e
um ponteiro do tipo equipa para as equipas. a funcao procura a equipa e 
retorna-a se existir */
equipa Equipa_search(int M, char Nome[], equipa *Equipa);

/* funcao recebe um insigned int M(tamanho da hash) e um ponteiro do tipo 
equipa para as equipas. a funcao faz free de todas as equipas, inclusive todos os 
mallocs feitos em todas as outras funcoes relacionadas com as equipas */
void Equipa_FREE(unsigned int M, equipa *Equipa);


/* funcao recebe um unsigned int *M(tamanho da hash) e um ponteiro do tipo equipa
para as equipas. a funcao tem como objetivo expandir a hash das equipas */
equipa *Equipa_expand(unsigned int *M, equipa *Equipa);



/* ----prototipos funcoes da hash table dos jogos---- */


/*funcao que recebe um nome de um jogo e um inteiro N (tamanho da hash) 
e que determina em que posicao da hash a jogo com esse nome fica */
int Jogo_hash(char *nome, int N);

/* funcao recebe um int m e um unsigned int *N(ambos tamanho da hash) e,
recebe tambem o ponteiro do tipo jogo para os jogos. retorna o ponteiro dos 
jogos que esta na Hash_Jogos*/
jogo *Jogo_init(int m, unsigned int *N, jogo *Jogo);

/* funcao recebe um int N(tamanho da hash), um ponteiro do tipo jogo
para os jogos e um jogo p que vai ser inserido na hash */
void Jogo_insert(int N, jogo *Jogo, jogo p);

/* funcao (do tipo jogo) recebe um int N(tamanho da hash), um Nome(nome do jogo) e
um ponteiro do tipo jogo para os jogos. a funcao procura o jogo e 
retorna-o se existir */
jogo Jogo_search(int N, char Nome[], jogo *Jogo);

/* funcao recebe um unsigned int N(tamanho da hash), um Nome(nome do jogo) e 
um ponteiro do tipo jogo para os jogos. a funcao remove o jogo em questao da hash*/
void Jogo_delete(unsigned int N, char *Nome, jogo *Jogo);

/* funcao recebe um insigned int N(tamanho da hash) e um ponteiro do tipo 
jogo para os jogos. a funcao faz free de todas os jogos, inclusive todos os 
mallocs feitos em todas as outras funcoes relacionadas com os jogos */
void Jogo_FREE(unsigned int N, jogo *Jogo);

/* funcao recebe um unsigned int *M(tamanho da hash) e um ponteiro do tipo jogo
para os jogos. a funcao tem como objetivo expandir a hash dos jogos */
jogo *Jogo_expand(unsigned int *M, jogo *Jogo);