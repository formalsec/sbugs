#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "processos.h"
#include "jogo.h"
#include "equipa.h"



void adicionaNovoJogo(pJogo *tabJ, pEquipa *tabE, int maxJ, int maxE, int nComandos, DLinkedList list) {
    pJogo jogo;
    pJogo novoJogo = (pJogo)can_fail_malloc(sizeof(struct Jogo));
    pEquipa equipa1, equipa2;
    qlink novoJ;
    int score1, score2;
    char nome[1024],nomeEq1[1024],nomeEq2[1024];
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,nomeEq1,nomeEq2,&score1,&score2);
    
    jogo = JOGOsearch(nome,tabJ,maxJ);
    equipa1 = EQUIPAseach(nomeEq1,tabE,maxE);
    equipa2 = EQUIPAseach(nomeEq2,tabE,maxE);
    if(jogo != NULL) {
        printf("%d Jogo existente.\n", nComandos);
    } else if(equipa1==NULL||equipa2==NULL) {
        printf("%d Equipa inexistente.\n", nComandos);
    } else {
        novoJogo->nome = strdup(nome);
        novoJogo->equipa1 = strdup(nomeEq1);
        novoJogo->equipa2 = strdup(nomeEq2);
        novoJogo->score1 = score1;
        novoJogo->score2 = score2;
        novoJogo->novoJogo = NULL;
        novoJ = JOGOappend(list,novoJogo);
        novoJogo->novoJogo = novoJ;
        JOGOinsert(novoJogo,tabJ,maxJ);
        
        if(score1>score2){
            equipa1->contVencidos++;
        } else if(score1<score2){
            equipa2->contVencidos++;
        }
    }
}

void adicionaNovaEquipa(pEquipa *tab, int max, int nComandos) {
     pEquipa equipa;
    char nome[1024];
    scanf(" %[^:\n]",nome);

    equipa = EQUIPAseach(nome, tab, max);
    if(equipa!=NULL){
        printf("%d Equipa existente.\n", nComandos);   
    } else {
        EQUIPAinsert(nome,0,tab,max);
    }
}

void listaJogosPelaOrdemIntroduzidos(DLinkedList list, int nComandos) {
    JOGOlist(nComandos,list);
}


void procuraUmJogo(pJogo *tabJ, int max, int nComandos){
    pJogo jogo;
    char nome[1024];
    scanf(" %[^:\n]",nome);

    jogo = JOGOsearch(nome,tabJ,max);
    if( jogo == NULL) {
        printf("%d Jogo inexistente.\n", nComandos);
    } else {
        printf("%d %s %s %s %d %d\n",nComandos,nome,jogo->equipa1,jogo->equipa2,jogo->score1,jogo->score2);
    }

}

void procuraUmaEquipa(pEquipa *tab, int max, int nComandos) {
    pEquipa equipa;
    char nome[1024];
    scanf(" %[^:\n]",nome);

    equipa = EQUIPAseach(nome, tab, max);
    if( equipa == NULL) {
        printf("%d Equipa inexistente.\n", nComandos);
    } else {
        printf("%d %s %d\n",nComandos,nome,equipa->contVencidos);
    }
}

void apagaUmJogo(pJogo *tabJ, pEquipa *tabE, int maxJ, int maxE, DLinkedList list, int nComandos) {
    pJogo jogo;
    char nome[1024];
    scanf(" %[^:\n]",nome);

    jogo = JOGOsearch(nome,tabJ,maxJ);
    if(jogo==NULL) {
        printf("%d Jogo inexistente.\n", nComandos);
    } else {
        if((jogo->score1)>(jogo->score2)) {
            EQUIPAseach(jogo->equipa1, tabE, maxE)->contVencidos--;
        } else if((jogo->score1)<(jogo->score2)){
            EQUIPAseach(jogo->equipa2, tabE, maxE)->contVencidos--;
        }
        JOGOQdelete(jogo->novoJogo, list);
        JOGOdelete(nome, tabJ, maxJ);
    }
}

void alteraScoreDeUmJogo(pJogo *tabJ, pEquipa *tabE, int maxJ, int maxE, int nComandos){
    pJogo jogo;
    pEquipa equipa1, equipa2;
    int score1, score2;
    char nome[1024];
    scanf(" %[^:\n]:%d:%d",nome,&score1,&score2);

    jogo = JOGOsearch(nome, tabJ, maxJ);
    if(jogo==NULL) {
        printf("%d Jogo inexistente.\n", nComandos);    
    }else{
        equipa1 = EQUIPAseach(jogo->equipa1, tabE, maxE);
        equipa2 = EQUIPAseach(jogo->equipa2, tabE, maxE);
        if(jogo->score1>jogo->score2&&score1<score2) {
            equipa1->contVencidos--;
            equipa2->contVencidos++;
        } else if(jogo->score1<jogo->score2&&score1>score2) {
            equipa1->contVencidos++;
            equipa2->contVencidos--;
        } else if(jogo->score1==jogo->score2&&score1>score2) {
            equipa1->contVencidos++;
        } else if(jogo->score1==jogo->score2&&score1<score2) {
            equipa2->contVencidos++;
        }else if(jogo->score1>jogo->score2&&score1==score2) {
            equipa1->contVencidos--;
        }else if(jogo->score1<jogo->score2&&score1==score2) {
            equipa2->contVencidos--;
        }
        jogo->novoJogo->jogo->score1 = score1;
        jogo->novoJogo->jogo->score1 = score2;
        jogo->score1 = score1;
        jogo->score2 = score2;
    } 
}


void encontraAsEquipasVencedores(pEquipa *tab, int max, int nComandos) {
    int ganhos = EQUIPAmaxWin(tab,max);
    EQUIPAlist(nComandos,ganhos,tab,max); 
}

void sair(pEquipa *tabE, pJogo *tabJ, DLinkedList listJ, int maxE, int maxJ){
    destoryList(listJ);
    destroyHashJogo(tabJ,maxJ);
    destroyHashEquipa(tabE,maxE);
}

void destoryList(DLinkedList list){
    qlink current, aux;
	if (list == NULL) return;
	if (list->load != 0)
		for (current = list->head, aux = list->head->next; current != NULL; aux = current->next, free(current), current = aux){}
	free(list);
}

void destroyHashJogo(pJogo *tabJ, int maxJ){
    int i;
    for(i=0;i<maxJ;i++){
        free(tabJ[i]);
    }
    free(tabJ);
}

void destroyHashEquipa(pEquipa *tabE, int maxE){
    int i;
    for(i=0;i<maxE;i++){
        free(tabE[i]);
    }
    free(tabE);
}





