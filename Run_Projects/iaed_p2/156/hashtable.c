#include <stdlib.h>
#include "Projeto2.h"

/*Esta funcao devolve a posicao de um elemento de uma tabela hash.*/
unsigned int hash(char *nome, int tamanho) {

    int indice, a = 31415, b = 27183;

    for (indice = 0; *nome != '\0'; nome++, a = a*b % (tamanho-1)){
        indice = (a*indice + *nome) % tamanho;
    }
    return indice;
}

/*Esta funcao inicializa uma tabela hash de equipas.*/
equipa_pont* inic_hash_equipa() {
    
    equipa_pont *tabela_hash;
    int i;

    tabela_hash = (equipa_pont*)malloc(Hash_equipas*sizeof(equipa_pont));
    /*Guarda o tabela hash com o malloc.*/

    for (i = 0; i < Hash_equipas; i++){
        tabela_hash[i] = NULL;
        /*Mete todas as entradas a nulo.*/
    }
    return tabela_hash;
}

/*Esta funcao inicializa uma tabela hash de jogos.*/
jogo_pont* inic_hash_jogo() {
    jogo_pont *tabela_hash;
    int i;

    tabela_hash = (jogo_pont*)malloc(Hash_jogos*sizeof(jogo_pont));
    /*Guarda o tabela hash com o malloc.*/

    for (i = 0; i < Hash_jogos; i++){
        tabela_hash[i] = NULL;
        /*Mete todas as entradas a nulo.*/
    }
    return tabela_hash;
}

/*Esta funcao limpa todos os mallocs que tinham sido feitos para ambas as tabelas hash.*/
void limpa(equipa_pont *tabela_hash_equipas, jogo_pont *tabela_hash_jogos){
    int indice;
    equipa_pont e, aux1;
    jogo_pont i, aux2;

    /*Obtem cada elemento de cada lista de cada indice da tabela hash de equipas e faz free.*/
    for (indice = 0; indice < Hash_equipas; indice++){
        for (e = tabela_hash_equipas[indice]; e != NULL; e = aux1){
            aux1 = e -> prox_equipa;
            free(e -> nome_equipa);
            free(e -> vitorias);
            free(e);
        }
    }
    free(tabela_hash_equipas); 

    /*Obtem cada elemento de cada lista de cada indice da tabela hash de jogos e faz free.*/
    for (indice = 0; indice < Hash_jogos; indice++){
        for (i = tabela_hash_jogos[indice]; i != NULL; i = aux2){
            aux2 = i -> prox_jogo;
            free(i -> nome_jogo);
            free(i -> golos1);
            free(i -> golos2);
            free(i);
        }
    }
    free(tabela_hash_jogos);
}