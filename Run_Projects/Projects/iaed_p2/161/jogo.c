#include "jogo.h"


/* cria um jogo e devolve o ponteiro para o jogo ----------------------------------------------- */
pJogo cria_jogo(char *nome, char *equipa1, char *equipa2,unsigned int score[2])
{
    /* aloca memoria para a estrutura jogo */
    pJogo jogo = (pJogo)malloc(sizeof(struct jogo));
    

    /* aloca memoria para os nomes das equipas e do jogo, e copia-os */
    jogo -> nome = (char*)malloc(sizeof(char)*(1 + strlen(nome)));
    strcpy(jogo -> nome, nome);

    jogo -> equipa1 = (char*)malloc(sizeof(char)*(1 + strlen(equipa1)));
    strcpy(jogo -> equipa1, equipa1);

    jogo -> equipa2 = (char*)malloc(sizeof(char)*(1 + strlen(equipa2)));
    strcpy(jogo -> equipa2, equipa2);


    jogo -> score[0] = score[0];
    jogo -> score[1] = score[1];
    
    return jogo;
}



/* devolve o nome de um jogo ------------------------------------------------------------------- */
char* obtem_nome_jogo(pJogo jogo)
{
    return jogo -> nome;
}


/* altera o score de um jogo ------------------------------------------------------------------- */
void altera_score_jogo(pJogo jogo, unsigned int score[2])
{
    jogo -> score[0] = score[0];

    jogo -> score[1] = score[1];

    return;
}


/* devolve o nome da equipa vencedora do jogo, se for empate devolve NULL ---------------------- */
char* obtem_vencedor_jogo(pJogo jogo)
{
    if (jogo -> score[0] > jogo -> score[1])
        return jogo -> equipa1;
    
    if (jogo -> score[0] < jogo -> score[1])
        return jogo -> equipa2;
    
    return NULL;
}


/* escreve o score, o nome das equipas, e o nome de um jogo ------------------------------------ */
void print_jogo(pJogo jogo, unsigned int Num_Linha)
{
    printf("%u %s %s %s %u %u\n", Num_Linha, jogo -> nome, jogo -> equipa1,
                            jogo -> equipa2, jogo -> score[0], jogo -> score[1]);

    return;
}


/* liberta a memoria alocada a um jogo */
void free_jogo(pJogo jogo)
{
    free(jogo -> nome); /* liberta a memoria alocada ao nome do jogo */
    
    free(jogo -> equipa1); /* liberta a memoria alocada ao nome da equipa 1*/
    
    free(jogo -> equipa2); /* liberta a memoria alocada ao nome da equipa 2*/
    
    free(jogo); /* liberta a memoria alocada 'a estrutura jogo*/

    return;
}