#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "Projeto2.h"

int main(){
    int nl = 0; /*Variavel que determina o numero do input.*/
    char caracter;
    equipa_pont *tabela_hash_equipas;
    jogo_pont *tabela_hash_jogos;
    jogo_pont lista_jogos_inicio = NULL; /*inicio da lista de jogo por ordem de entrada.*/
    jogo_pont lista_jogos_fim = NULL; /*fim da lista de jogo por ordem de entrada.*/

    /*Inicializacao das tabelas de equipas e jogos, respetivamente.*/
    tabela_hash_equipas = inic_hash_equipa();
    tabela_hash_jogos = inic_hash_jogo();

    caracter = getchar();

    while (caracter != 'x'){
        switch(caracter){

            case 'A':
                nl++;
                adic_equipa(tabela_hash_equipas, nl);
                break;
            
            case 'a':
                nl++;
                adic_jogo(&lista_jogos_inicio, &lista_jogos_fim, tabela_hash_jogos, tabela_hash_equipas, nl);
                break;

            case 'l':
                nl++;
                jogos_introduzidos(lista_jogos_inicio, nl);
                break;

            case 'p':
                nl++;
                procura_jogo(tabela_hash_jogos, nl);
                break;

            case 'P':
                nl++;
                procura_equipa(tabela_hash_equipas, nl);
                break;

            case 's':
                nl++;
                altera_resultado(tabela_hash_jogos, tabela_hash_equipas, nl);
                break;

            case 'r':
                nl++;
                apaga_jogo(tabela_hash_jogos, tabela_hash_equipas, &lista_jogos_inicio, &lista_jogos_fim, nl);
                break;

            case 'g':
                nl++;
                mais_vencedoras(tabela_hash_equipas, nl);
                break;

        }
        caracter = getchar();
    }
    limpa(tabela_hash_equipas, tabela_hash_jogos);
    return 0;
}