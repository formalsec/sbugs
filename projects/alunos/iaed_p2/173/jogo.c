#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogo.h"
 
/* 
Aloca memoria para um jogo e inicializa
*/
Jogo* cria_jogo(char nome[],Equipa* e1,Equipa* e2,int s1, int s2,int id){
    Jogo *jogo = (Jogo*) can_fail_malloc(sizeof(Jogo));
    jogo->nome = strdup_nome(nome);
    jogo->e1 = e1;
    jogo->e2 = e2;
    jogo->s1 = s1;
    jogo->s2 = s2;
    jogo->id = id;
    return jogo;
}

/*
Retorna o id de um jogo
*/
int get_id_jogo(Jogo *jogo){
    if (jogo == NULL){
        return 0;
    }
    return jogo->id;
}

/* 
Liberta a memoria alocada para um jogo
*/
void free_jogo(Jogo *jogo){
    free(jogo->nome);
    free(jogo);
}

/* 
Altera o score de um jogo
*/
void alt_score_jogo(Jogo *jogo,int s1,int s2){
    jogo->s1 = s1;
    jogo->s2 = s2;
}

/* 
Retorna o nome de um jogo
*/
char* get_nome_jogo(Jogo *jogo){
    return jogo->nome;
}

/* 
Retorna a primeira equipa de um jogo
*/
Equipa* get_equipa1_jogo(Jogo *jogo){
    return jogo->e1;
}

/* 
Retorna a segunda equipa de um jogo
*/
Equipa* get_equipa2_jogo(Jogo *jogo){
    return jogo->e2;
}

/* 
Retorna o score da primeira equipa de um jogo
*/
int get_score1_jogo(Jogo *jogo){
    return jogo->s1;
}

/* 
Retorna o score da segunda equipa de um jogo
*/
int get_score2_jogo(Jogo *jogo){
    return jogo->s2;
}