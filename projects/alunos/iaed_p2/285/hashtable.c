#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hashtable.h" /* atraves deste include, acesso os ficheiros Jogo.h, equipas.h e hashtable.h */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Funcao hash que retorna um indice para uma hashtable*/
unsigned hash(char *nome, int tamanho_Hashtable){
    unsigned indice = 0, a = 127 ;
    for(; *nome != '\0'; nome ++){
        indice = (a * indice + *nome) % tamanho_Hashtable;
    }
    return indice;
}
/* Funcao que procura o indice da hashtable onde se encontra um jogo com o nome dado como argumento. Caso nao haja um jogo na
hashtable com o nome dado, retorna NAO_ENCONTRA. */
int procura_indice(Jogo* Hashtable, char* nome, int tamanho_Hashtable){
    int indice;
    indice = hash(nome, tamanho_Hashtable);
    while (Hashtable[indice] != NULL){
        if (strcmp(Hashtable[indice] -> Nome, nome) == 0){
            return indice;
        }
        else{
            indice = (indice + 1) % tamanho_Hashtable;
        }
    }
    return NAO_ENCONTRA;
}

/* Funcao que inicializa a hashtable dos jogos alocando espaco para todos os seus jogos 
e atribuindo-lhes NULL (Retorna a hashtable). */
Jogo* inicializa(int tamanho_hashtable){
    Jogo *HashTable;
    int indice;
    HashTable = can_fail_malloc(tamanho_hashtable * sizeof(Jogo));
    for(indice = 0; indice < tamanho_hashtable; indice++){
      HashTable[indice] = NULL;
    }
    return HashTable;
}


/* Funcao que retorna a hashtable que recebe inserindo um jogo num espaco vazio */
Jogo* insere(Jogo jogo, Jogo* Hashtable, int Tamanho_HashTable){
    int indice = hash(jogo -> Nome, Tamanho_HashTable);
    while (Hashtable[indice] != NULL){
        indice = (indice + 1) % Tamanho_HashTable;
    }
    Hashtable[indice] = jogo;
    return Hashtable;
    }

/* Funcao que retorna a hashtable que recebe libertando o espaco alocado para um jogo eliminando assim
o jogo da hashtable. Caso nao encontre o jogo, retorna a hashtable dada sem alteracoes */
Jogo* apaga_jogo(Jogo* HashTable, char* nome, int tamanho_Hashtable){
    int indice;
    int indice2;
    Jogo jogo;
    indice = procura_indice(HashTable, nome, tamanho_Hashtable);
    free(HashTable[indice] -> Nome); 
    free(HashTable[indice] -> Equipa_Casa);
    free(HashTable[indice] -> Equipa_Fora);
    free(HashTable[indice]);
    HashTable[indice] = NULL;
    for (indice2 = (indice + 1) % tamanho_Hashtable; HashTable[indice2] != NULL; indice2 = (indice2 + 1) % tamanho_Hashtable){
        jogo = HashTable[indice2];
        HashTable[indice2] = NULL;
        insere(jogo, HashTable, tamanho_Hashtable);
    }

            return HashTable;
}
/* Funcao que retorna a hashtable que recebe alterando o score de um jogo. Caso nao encontre o jogo
com o nome dado, retorna a hashtable que recebeu sem alteracoes */
Jogo* altera_score(char* nome, Jogo* Hashtable, int tamanho_Hashtable){
    int indice, novo_score_equipa_casa, novo_score_equipa_fora;
    scanf(":%d:%d" , &novo_score_equipa_casa, &novo_score_equipa_fora);
    indice = procura_indice(Hashtable, nome, tamanho_Hashtable);
            Hashtable[indice] -> Score_Equipa_Casa = novo_score_equipa_casa;
            Hashtable[indice] -> Score_Equipa_Fora = novo_score_equipa_fora;
            return Hashtable;
}

/* Funcao que inicializa a hashtable das equipas alocando espaco para todas as suas equipas 
e atribuindo-lhes NULL (Retorna a hashtable). */
Equipa* inicializa_equipas(int tamanho_Hashtable){
    Equipa *Hashtable;
    int i;
    Hashtable = can_fail_malloc( tamanho_Hashtable * sizeof(Equipa));
    for(i = 0; i < tamanho_Hashtable; i++){
      Hashtable[i] = NULL;
    }
    return Hashtable;
}

/* Funcao que retorna a hashtable que recebe inserindo uma equipa num espaco vazio */
Equipa* insere_equipa(Equipa equipa, Equipa *Hashtable, int Tamanho_HashTable){
    int Indice = hash(equipa -> Nome, Tamanho_HashTable);
    while (Hashtable[Indice] != NULL){
        Indice = (Indice + 1) % Tamanho_HashTable;
    }
    Hashtable[Indice] = equipa;
    return Hashtable;
}

/* Funcao que retorna a hashtable que recebe incrementando o numero de vitorias da equipa que tiver ganho o jogo. Em caso de empate, devolve a hashtable original */
Equipa* atribui_vitoria(Equipa * Hashtable, char *equipa1, char *equipa2, int score1, int score2, int tamanho_Hashtable){
    int Indice;
    if (score1 > score2){
        Indice = procura_indice_equipas(Hashtable, equipa1, tamanho_Hashtable);
        Hashtable[Indice] -> Vitorias ++;
        return Hashtable;
    }
    if (score2 > score1){
        Indice = procura_indice_equipas(Hashtable, equipa2, tamanho_Hashtable);
        Hashtable[Indice] -> Vitorias ++;
        return Hashtable;
    }
    return Hashtable;
}

/* Funcao que retorna a hashtable que recebe decrementando o numero de vitorias da equipa que tiver perdido o jogo. Em caso de empate, devolve a hashtable original */
Equipa* retira_vitoria(Equipa * Hashtable, char *equipa1, char *equipa2, int score1, int score2, int tamanho_Hashtable){
    int Indice;
    if (score1 > score2){
        Indice = procura_indice_equipas(Hashtable, equipa1, tamanho_Hashtable);
        Hashtable[Indice] -> Vitorias --;
        return Hashtable;
    }
    if (score2 > score1){
        Indice = procura_indice_equipas(Hashtable, equipa2, tamanho_Hashtable);
        Hashtable[Indice] -> Vitorias --;
        return Hashtable;
    }
    return Hashtable;
}
