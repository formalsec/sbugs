#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao principal do programa responsavel por iniciar ambas as hash tables e redirecionar para as funcoes
correspondentes dependendo do comando introduzido, funciona em loop e termina assim que for atribuido o comando x*/
int main(){
    int bol = 1,NL = 1,score1,score2, id = 0;
    char cmd,NOME[MAXNOME],EQUIPA1[MAXNOME],EQUIPA2[MAXNOME];
    equipa HTequipa[TABLE_SIZE]; /*hash table para as equipas*/
    jogo HTjogo[TABLE_SIZE]; /*hash table para os jogos*/
    init_HTE(HTequipa); /*inicializacao da hashtable de equipas*/
    init_HTJ(HTjogo); /*inicializacao da hash table de jogos*/
    while(bol){   /*corpo principal da funcao*/
        cmd = getchar(); /*obtencao do comando e atraves do switch redireciona para a funcao correspondente*/
        switch(cmd){
            case 'a':
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",NOME,EQUIPA1,EQUIPA2,&score1,&score2);
                /* se for possivel adicionar o jogo a funcao cmd_a() retorna 1 e incrementa o id dos jogos*/
                if(cmd_a(NOME, EQUIPA1, EQUIPA2, score1, score2, HTjogo, HTequipa, NL, id)) id++;
                NL++;
                break;
            case 'A':
                scanf(" %[^:\n]",NOME);
                cmd_A(NOME, HTequipa,NL);
                NL ++;
                break;
            case 'l':
                cmd_l(HTjogo, NL, id);
                NL++;
                break;
            case 'p':
                scanf(" %[^:\n]",NOME);
                cmd_p(NOME, HTjogo, NL);
                NL++;
                break;
            case 'P':
                scanf(" %[^:\n]",NOME);
                cmd_P(NOME, HTequipa, NL);
                NL++;
                break;
            case 'r':
                scanf(" %[^:\n]",NOME);
                cmd_r(NOME, HTjogo, HTequipa, NL);
                NL++;
                break;
            case 's':
                scanf(" %[^:\n]:%d:%d", NOME, &score1, &score2);
                cmd_s(NOME, HTjogo, score1, score2, HTequipa,NL);
                NL++;
                break;
            case 'g':
                cmd_g(HTequipa, NL);
                NL++;
                break;
            case 'x': /*termina o programa e liberta toda a memoria usada*/
                FreeHTjogo(HTjogo);
                FreeHTequipa(HTequipa);
                bol = 0;
                break;
        }
    }return 0;
}