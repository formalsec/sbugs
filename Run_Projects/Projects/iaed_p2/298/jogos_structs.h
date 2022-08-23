#ifndef JOGOS_STRUCTS_file
#define JOGOS_STRUCTS_file

/*estrutura JOGO define lista ligada de jogos em que cada jogo e definido pelo nome 
    do proprio jogo e nome de duas equipas (equipa1 e equipa2) e pelo score de 
    cada uma delas (score1 e score2) respetivemante*/
typedef struct jogo {
    char * nome;
    char * equipa1;
    char * equipa2;
    int score1, score2;
    struct jogo * next;
    struct jogo * prev;
} JOGO;

/*estrutura JOGO_LIST representa uma lista_de_jogos 
    (forma simplificada de representar uma lista ligada de jogos 
    indicando o primeiro (head) e ultimo (last) jogos (nos) dessa lista)*/
typedef struct jogos {
    JOGO * head;
    JOGO * last;
} JOGO_LIST;

/*estrutura JOGO_HASH define a representacao de cada jogo existente na hashtable_jogos*/
typedef struct jogo_hash {
    JOGO * jogo_ptr;
    struct jogo_hash * next;
} JOGO_HASH;

#endif