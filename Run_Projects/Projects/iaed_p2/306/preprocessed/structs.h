#ifndef structs_h
#define structs_h

#define MAX_CARACTERES 1023    /*Maximo de caracteres de cada nome*/
#define MAX_HASH 6661          /*Tamanho de cada um das hashtables*/

/*struct das equipas*/
typedef struct equipa{
    char *nome;             /*Guarda o nome de uma equipa*/
    int vitorias;           /*Guarda as vitorias de uma equipa*/
    struct equipa *seguinte;    /*Pointer para a proxima equipa*/
}equipa ;

/*struct dos jogos*/
typedef struct jogo{
    char *nome, *equipa1, *equipa2;     /*Guarda o nome do jogo e as equipas, respetivamente*/
    int score1;                         /*Guarda o resultado da primeira equipa*/
    int score2;                         /*Guarda o resultado da segunda equipa*/
    struct jogo *seguinte;              /*Pointer para a proxima equipa*/
}jogo ;

/*struct dos nodes das listas de jogos*/
typedef struct node_j{  
    jogo *jogo;                         /*Guarda o jogo em si*/
    struct node_j *seguinte;            /*Aponta para o node seguinte*/
    struct node_j *anterior;            /*Aponta para o node anterior*/
}node_j;

/*struct dos nodes das listas de equipas*/
typedef struct node_e{
    equipa *equipa;                     /*Guarda a equipa em si*/
    struct node_e *seguinte;            /*Aponta para o node seguinte*/
    struct node_e *anterior;            /*Aponta para o node anterior*/
}node_e;

jogo *hash_jogos[MAX_HASH];           /*Hashtable para os jogos*/
equipa *hash_equipas[MAX_HASH];       /*Hashtable para as equipas*/
node_e *head_e;                       /*Head e para a lista das equipas*/
node_j *head_j,*tail_j;               /*Head e Tail* para a lista dos jogos*/

/*Foi acresentada uma tail na lista de jogos para obter
*    melhor eficiencia ao adicionar as equipas       */         

/* ---FIM DAS DEFINICOES---*/

#endif