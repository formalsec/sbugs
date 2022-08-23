#include "EquipasEJogos.h"

Equipa* criaEquipa(char* nome){
    Equipa* equipa;
    equipa = (Equipa*)malloc(sizeof(Equipa));
    equipa->jogosVencidos = 0;
    equipa->nome = (char*)malloc(sizeof(char)*strlen(nome)+1);
    strcpy(equipa->nome,nome);
    return equipa;
}

Jogo* criaJogo(char* nome,Equipa* equipa1,Equipa* equipa2,int score1,int score2){
    Jogo* jogo;
    jogo = (Jogo*)malloc(sizeof(Jogo));
    jogo->score1 = score1;
    jogo->score2 = score2;
    jogo->nome = (char*)malloc(sizeof(char)*strlen(nome)+1);
    strcpy(jogo->nome,nome);
    jogo->equipa1 = equipa1;
    jogo->equipa2 = equipa2;
    if (score1>score2) {
        addJogosV(equipa1);
    }
    if (score1<score2) {
        addJogosV(equipa2);
    }
    
    
    return jogo;
}

void addJogosV(Equipa* equipa){
    equipa->jogosVencidos +=1;
}

void remJogosV(Equipa* equipa){
    equipa->jogosVencidos -=1;
}

void alteraScore(Jogo* jogo,int score1_,int score2_){
    int comp1,comp2;
    comp1 = jogo->score1 - jogo->score2;
    comp2 = score1_ - score2_;
    
    if (comp1 > 0 && comp2 < 0) {
        jogo->equipa1->jogosVencidos--;
        jogo->equipa2->jogosVencidos++;
    }
    
    if (comp1 < 0 && comp2 > 0) {
        jogo->equipa1->jogosVencidos++;
        jogo->equipa2->jogosVencidos--;
    }
    
    if (comp1 == 0 && comp2 > 0) {
        jogo->equipa1->jogosVencidos++;
    }

    if (comp1 == 0 && comp2 < 0) {
        jogo->equipa2->jogosVencidos++;
    }
    
    if (comp1 > 0 && comp2 == 0) {
        jogo->equipa1->jogosVencidos--;
    }
    
    if (comp1 < 0 && comp2 == 0) {
        jogo->equipa2->jogosVencidos--;
    }
    
    jogo->score1 = score1_;
    jogo->score2 = score2_;
}

void freeEq(Equipa* equipa){
    free(equipa->nome);
    free(equipa);
}

void freeJg(Jogo* jogo){
    free(jogo->nome);
    free(jogo);
}