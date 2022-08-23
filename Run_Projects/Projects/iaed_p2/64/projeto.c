#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

int main(){
    /* Ponteiros utilizados para as hash tables e para a head e tail
    da lista dos jogos */
    jogo *hash_table_jogos = NULL, head=NULL, tail=NULL;
    equipa *hash_table_equipas = NULL;
    /* Char utilizado para designar o comando a ser executado */
    char comando;
    /* Inteiro utilizado para contabilizar o numero de linhas de input, de forma
    a facilitar o debug do projeto */
    int linha=0;

    /* Hash tables sao inicializadas como vazias */
    hash_table_equipas=inicia_hash_equipas(hash_table_equipas);
    hash_table_jogos=inicia_hash_jogos(hash_table_jogos);

    while((comando=getchar())!=EOF){
        switch(comando){
            case 'a':
                linha++;
                /* Funcao que adiciona um novo jogo */
                add_jogo(hash_table_equipas, hash_table_jogos, &head, &tail, linha);
                break;
                
            case 'A':
                linha++;
                /* Funcao que adiciona uma nova equipa */
                add_equipa(hash_table_equipas, linha);
                break;

            case 'l':
                linha++;
                /* Funcao que lista todos os jogos pela ordem que foram introduzidos */
                print(head, linha);
                break;

            case 'p':
                linha++;
                /* Funcao que procura um jogo dado o nome do mesmo */
                print_jogo(hash_table_jogos, linha);
                break;

            case 'P':
                linha++;
                /* Funcao que procura uma equipa dado o nome da mesma */
                print_equipa(hash_table_equipas, linha);
                break;

            case 'r':
                linha++;
                /* Funcao que apaga um jogo dado o nome do mesmo */
                remove_jogo(&head, &tail, hash_table_jogos, linha);
                break;
            
            case 's':
                linha++;
                /* Funcao que altera a pontuacao de um jogo */
                altera_score(hash_table_jogos, linha);
                break;

            case 'g':
                linha++;
                /* Funcao que encontra as equipas que venceram mais jogos */
                mais_vitorias(hash_table_equipas, linha);
                break;

            case 'x':
                /* Funcao que termina o programa */
                free_final(hash_table_equipas, hash_table_jogos);
                return 0;
        }
    }
    return 0;
}
