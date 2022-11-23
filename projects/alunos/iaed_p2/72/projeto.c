#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "funcoes.h"
#include <stdio.h>

/*FUNCAO MAIN*/

/*
  main: () -> int
  Primeira funcao a ser executada, trata de reconhecer o comando presente na input
*/
int main(){
    /*Variavel que conteem o comando a ser executado e o numero de linhas*/
    char op;
    unsigned int NL = 1;

    /*Variaveis que conteem as estruturas usadas para guardar os jogos e as equipas*/
    Jogos jogos;
    Equipas equipas;

    /*Inicializa estruturas de jogos e equipas*/
    jogos = init_jogos();
    equipas = init_equipas();

    /*Le carateres da stdin ate encontrar o caso terminal
      ou um comando a executar*/
    while((op = getchar()) != 'x'){
        switch(op){
            case('a'):
                /*elimina o ' ' entre o comando e o conteudo do comando*/
                getchar(); 
                NL = a(NL, jogos, equipas);
                break;
            case('A'):
                getchar();
                NL = A(NL, equipas);
                break;
            case('l'):
                getchar();
                NL = l(NL, jogos);
                break;
            case('p'):
                getchar();
                NL = p(NL, jogos);
                break;
            case('P'):
                getchar();
                NL = P(NL, equipas);
                break;
            case('r'):
                getchar();
                NL = r(NL, jogos);
                break;
            case('s'):
                getchar();
                NL = s(NL, jogos);
                break;
            case('g'):
                getchar();
                NL = g(NL, equipas);
                break;   
        }
    }

    /*destroi todos os jogos e equipas e as estruturas*/
    destroi_jogos(jogos);
    destroi_equipas(equipas);

    return 0;
}
