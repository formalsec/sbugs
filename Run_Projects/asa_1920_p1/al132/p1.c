/*
Joao Silva n92491
Joao Simoes n92499
*/

#include <stdio.h>
#include <stdlib.h>

#define White 0
#define Gray 1
#define Black 2

void inicializarTabela();
void adicionaArco(int u, int v);
void visitaTabela();
void visita(int u);
int adjacenciaDiferente(int u);
int lastCheck();

typedef struct vertice{
    int nota;
    int cor;
    int nAdjacencias;
    int* adjacencias;
    int adjacenciaAtual;
}vertice;

vertice* tabela;
int nAlunos;

int main(){

    int nRelacoes,retorno;
    
    retorno = scanf("%d,%d",&nAlunos,&nRelacoes);
    if(retorno != 2)
        exit(EXIT_FAILURE);

    inicializarTabela();

    int nota,i;
    for(i = 1;i <= nAlunos;i++){
        retorno = scanf("%d",&nota);
        if(retorno != 1)
            exit(EXIT_FAILURE);
        tabela[i].nota = nota;
    }

    int j,Pessoa1,Pessoa2;
    for(j = 0;j < nRelacoes;j++){
        retorno = scanf("%d %d",&Pessoa1,&Pessoa2);
        if(retorno != 2)
            exit(EXIT_FAILURE);
        adicionaArco(Pessoa1,Pessoa2);
    }

    visitaTabela();
    while(lastCheck());
    
    for(i = 1;i <= nAlunos;i++){
        printf("%d\n",tabela[i].nota);
    }
    
    return 0;
}

void inicializarTabela(){
    int i;
    tabela = malloc(sizeof(vertice)*(nAlunos+1));
    for(i = 1;i <= nAlunos;i++){
        tabela[i].nota = 0;
        tabela[i].cor = White;
        tabela[i].nAdjacencias = 0;
        tabela[i].adjacencias = malloc(sizeof(int));
        tabela[i].adjacenciaAtual = 0;
    }
}

void adicionaArco(int u, int v){
    if(tabela[u].nAdjacencias < 1){
        tabela[u].adjacencias[0] = v;
        tabela[u].nAdjacencias++;
    }
    else{
        tabela[u].adjacencias = realloc(tabela[u].adjacencias,sizeof(int)*(tabela[u].nAdjacencias+1));
        tabela[u].nAdjacencias++;
        tabela[u].adjacencias[tabela[u].nAdjacencias-1] = v;
    }    
}

void visitaTabela(){
    int i;
    for(i = 1;i <= nAlunos;i++){
        visita(i);
    }
}

void visita(int u){
    tabela[u].cor = Gray;
    int i;
    for(i = tabela[u].adjacenciaAtual;i < tabela[u].nAdjacencias;i++){
        if(tabela[tabela[u].adjacencias[i]].cor == White){
            visita(tabela[u].adjacencias[i]);
        }
        if(tabela[tabela[u].adjacencias[i]].cor == Gray){ 
            if(adjacenciaDiferente(tabela[u].adjacencias[i]) != 0){
                tabela[tabela[u].adjacencias[i]].adjacenciaAtual++;
                visita(tabela[u].adjacencias[i]);
            }
        }
        if((tabela[u].nota < tabela[tabela[u].adjacencias[i]].nota)){
            tabela[u].nota = tabela[tabela[u].adjacencias[i]].nota;
        }
    }
    tabela[u].cor = Black;
}

int adjacenciaDiferente(int u){
    int i;
    for(i = 0;i < tabela[u].nAdjacencias;i++){
        if(tabela[tabela[u].adjacencias[i]].cor == White){
            return 1;
        }
    }
    return 0;
}

int lastCheck(){
    int i,j;
    for(i = 1;i <= nAlunos;i++){
        for(j = 0;j < tabela[i].nAdjacencias;j++){
            if((tabela[i].nota < tabela[tabela[i].adjacencias[j]].nota)){
                tabela[i].nota = tabela[tabela[i].adjacencias[j]].nota;
                return 1;
            }
        }
    }
    return 0;
}