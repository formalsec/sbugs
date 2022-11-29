#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "futebol.h"
/*numero maximo de caracteres de nome de jogo ou equipa*/
#define MAX 1024
/*tamanho da hashtable*/
#define M 1049

int main(){

    int comando, sc1, sc2, NL;
    char nome[MAX], eq1[MAX], eq2[MAX];

    /*pointer para a hashtable das equipas*/
    hashtable* hequipas;

    /*pointer para a hashtable dos jogos*/
    hashtable* hjogos;

    /*pointer para a lista dos jogos*/
    list* ljogos;

    /*contador para o numero da linha do comando executado*/
    NL=0;

    /*inicializar as hashtables das equipas e jogos, e inicializar a lista de jogos*/
    hequipas = criahash(M);
    hjogos = criahash(M);
    ljogos = crialista();


    while ((comando = getchar())!='x') {

        switch(comando) {

            case 'a':

                NL++;
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, eq1, eq2, &sc1, &sc2);
                adiciona_jogo(nome, eq1, eq2, sc1, sc2, hequipas, hjogos, ljogos,NL);

                break;

            case 'l':
                NL++;
                lista_jogos(ljogos,NL);
                break;

            case 'p':
                NL++;
                scanf(" %[^:\n]", nome);
                procura_jogo(hjogos, nome, NL);
                break;
            
            case 'r':
                NL++;
                scanf(" %[^:\n]", nome);
                apaga_jogo(hjogos, ljogos, nome, NL);
                break;

            case 's':
                NL++;
                scanf(" %[^:\n]:%d:%d",nome, &sc1, &sc2);
                altera_score(hjogos, nome, sc1, sc2, NL);
                break;

            case 'A':
                NL++;
                scanf(" %[^:\n]", nome);
                adiciona_equipa(nome, hequipas, NL);
                break;

            case 'P':
                NL++;
                scanf(" %[^:\n]", nome);
                procura_equipa(hequipas, nome, NL);
                break;
            
            case 'g':
                NL++;
                mais_vitorias(hequipas, M, NL);
                break;

            default:
                printf("ERRO: comando desconhecido.\n");

        }

        /*le \n introduzido pelo utilizador*/
        getchar();                                          

    }

    /*free das hashtables das equipas e jogos, free da lista de jogos e free dos jogos e equipas em si*/
    freelista(ljogos,0,free);
    freehash(hequipas, M, 1, freeequipa);
    freehash(hjogos, M, 1, freejogo);

    return 0;

}




