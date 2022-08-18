#include "hashEQ.h"
#include "hashJG.h"

#define MAXSTR 1023
#define M 1049


void addJogo(HLink_ head1,Link_* head2,HLink head3,int NL){
    int score1,score2;
    Jogo* jogo;
    char nome[MAXSTR],equipa1[MAXSTR],equipa2[MAXSTR];
    Equipa *equipa1_,*equipa2_;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

    if (procuraJgHash(head1,M,nome)!= NULL) {
        printf("%d Jogo existente.\n",NL);
        return;
    }
    else{

        equipa1_ = procuraEqHash(head3,M,equipa1);
        equipa2_ = procuraEqHash(head3,M,equipa2);

        if (equipa1_ == NULL || equipa2_ == NULL) {
            printf("%d Equipa inexistente.\n",NL);
            return;
        }

        jogo = criaJogo(nome,equipa1_,equipa2_,score1,score2);
        addHash_(head1,jogo,M);
        *head2 = addJgLista(*head2,jogo);
    }
}


void addEquipa(HLink head, int NL){
    char nome[MAXSTR];
    Equipa* equipa;
    scanf(" %[^:\n]", nome);

    if (procuraEqHash(head,M,nome) != NULL) {
        printf("%d Equipa existente.\n", NL);
    }

    equipa = criaEquipa(nome);
    addHash(head,equipa,M);
}

void listarJogos(Link_ listaJgs, int NL){
    Link_ aux = listaJgs;
    Jogo* jogo;
    while(aux!=NULL){
        jogo = obtemElem(aux);
        printf("%d %s %s %s %d %d\n",NL,jogo->nome,jogo->equipa1->nome,jogo->equipa2->nome,jogo->score1,jogo->score2);
        aux = aux->next;
    }
}


void procurarJogo(HLink_ head,int NL){
    Jogo* jogo;
    char nome[MAXSTR];
    scanf(" %[^:\n]", nome);
    jogo = procuraJgHash(head,M,nome);
    if (jogo == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    printf("%d %s %s %s %d %d\n",NL,jogo->nome,jogo->equipa1->nome,jogo->equipa2->nome,jogo->score1,jogo->score2);
}


void procurarEquipa(HLink head,int NL){
    Equipa* equipa;
    char nome[MAXSTR];
    scanf(" %[^:\n]", nome);
    equipa = procuraEqHash(head,M,nome);
    if (equipa == NULL) {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    printf("%d %s %d\n", NL, nome, equipa->jogosVencidos);
}

void apagarJogo(HLink_ head,Link_* listaJgs,int NL){
    char nome[MAXSTR];
    Jogo* jogo;
    scanf(" %[^:\n]", nome);
    jogo = procuraJgHash(head,M,nome);
    if (jogo == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    remHash_caso(head,nome,M);
    *listaJgs = apagaNode_(*listaJgs,jogo);
}


void alteraScores(HLink_ head,int NL){
    int score1_,score2_;
    char nome[MAXSTR];
    Jogo* jogo;
    scanf(" %[^:\n]:%d:%d", nome, &score1_, &score2_);
    jogo = procuraJgHash(head,M,nome);
    if (jogo == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    alteraScore(jogo,score1_,score2_);
}


int main(){
    HLink hashEq;
    HLink_ hashJg;
    Link_ listaJgs;

    int NL = 1;
    char fun;

    hashEq = inicializaHash(M);
    hashJg = inicializaHash_(M);
    listaJgs = inicializaLista_();

    
    while (1 > 0){
        scanf("%c", &fun);
        switch(fun){
            case 'a':
                addJogo(hashJg,&listaJgs,hashEq,NL);
                NL++;
            break;
            case 'A':
                addEquipa(hashEq,NL);
                NL++;
            break;
            case 'l':
                listarJogos(listaJgs,NL);
                NL++;
            break;
            case 'p':
                procurarJogo(hashJg,NL);
                NL++;
            break;
            case 'P':
                procurarEquipa(hashEq,NL);
                NL++;
            break;
            case'r':
                apagarJogo(hashJg,&listaJgs,NL);
                NL++;
            break;
            case 's':
                alteraScores(hashJg,NL);
                NL++;
            break;
            case 'x':
                limpaHash(hashEq,M);
                limpaHash_(hashJg,M);
                limpaLista_caso(listaJgs);
                return 0;

        }
    }
    
    return 0;
}