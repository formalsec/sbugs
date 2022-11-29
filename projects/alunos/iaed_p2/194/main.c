#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"
#include "equipa.h"

/* Ler n possiveis comando*/
int main() {
    /* tamanho equipa para inicializa hashTable | tamanho jogo para inicializa hashTable | tamanho dos comandos | tamanho da equipas ja adiciona |tamanho da jogos ja adiciona */
    int maxE = 19913, maxJ = 19913, nComandos = 1, nEquipas=0, nJogos=0;
    /* hashTable da equipa */
    pEquipa *tabE = NULL;
    /* hashTable do jogo */
    pJogo *tabJ = NULL;
    /* lista do jogo */
    DLinkedList listJ = NULL;
    
    char comando;
    
    tabE = EQUIPAinit(maxE,tabE);
    tabJ = JOGOinit(maxJ,tabJ);
    listJ = JOGOlist_init();
    do{
        comando = getchar();
        switch(comando) {
            case 'a':
                adicionaNovoJogo(tabJ,tabE,maxJ,maxE,nComandos,listJ);
                nJogos++;
                if(nJogos>maxJ/2){
                    maxJ = maxJ*2;
                    tabJ = JOGOexpand(tabJ,maxJ);
                }
                nComandos++;
                break;
            case 'A':
                adicionaNovaEquipa(tabE,maxE,nComandos);
                nEquipas++;
                if(nEquipas>maxE/2){
                    maxE = maxE*2;
                    tabE = EQUIPAexpand(tabE,maxE);
                }
                nComandos++;
                break;
            case 'l':
                listaJogosPelaOrdemIntroduzidos(listJ,nComandos);
                nComandos++;
                break; 
            case 'p':
                procuraUmJogo(tabJ,maxJ,nComandos);
                nComandos++;
                break;
            case 'P':
                procuraUmaEquipa(tabE,maxE,nComandos);
                nComandos++;
                break;
            case 'r':
                apagaUmJogo(tabJ,tabE,maxJ,maxE,listJ,nComandos);
                nJogos--;
                nComandos++;
                break;
            case 's':
                alteraScoreDeUmJogo(tabJ,tabE,maxJ,maxE,nComandos);
                nComandos++;
                break;
            case 'g':
                encontraAsEquipasVencedores(tabE,maxE,nComandos);
                nComandos++;
                break;  
        }
    /*Termina o programa*/
    } while(comando != 'x');

    sair(tabE,tabJ,listJ,maxE,maxJ);
    return 0;
}


