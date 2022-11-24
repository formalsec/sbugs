#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"

#define MAX_PAL 1024
#define M 1013

/* Prototipos das funcoes utilizadas na main*/

void que_func(int NL,char *letra,lista_equipas *lista_ligada_equipas,acede_jogos *lista_ligada_jogos,acede_jogo_normal *jogos_normais,
              acede_equipa_normal *equipas_normais);

void free_da_hash_jogo(acede_jogos *lista_ligada_jogos);

void free_da_hash_equipa(lista_equipas *lista_ligada_equipas);

void free_jogos_normais(acede_jogo_normal *jogos_normais);

void free_equipas_normais(acede_equipa_normal *equipas_normais);


/* funcao main--> vai guardar a primeira letra do input numa variavel e chama a funcao que verifica
   que letra esta guardada em letra e depois fica a espera de um novo input para ler ate que este comece por x, onde para e termina o programa*/
int main(){
    int contador=0;                                 /*contador que incrimenta a cada passagem no ciclo while*/
    int *conta_linha=can_fail_malloc(sizeof(int));            /*contador das linhas*/
    char *letra=can_fail_malloc(sizeof(char));               /*variavel onde se guarda a primeira letra do input*/
    acede_jogo_normal *jogos_normais=can_fail_malloc(sizeof(acede_jogo_normal));       /*Jogos_normais-->ponteiro para a lista ligada dos jogos*/
    acede_equipa_normal *equipas_normais=can_fail_malloc(sizeof(acede_equipa_normal));  /*equipas_normais-->ponteiro para a lista ligada dos equipas*/
    acede_jogos *lista_ligada_jogos=can_fail_malloc(sizeof(acede_jogos));              /*lista_ligada_jogos--> ponteiro para a hash table dos jogos*/
    lista_equipas *lista_ligada_equipas=can_fail_malloc(sizeof(lista_equipas));        /*lista_ligada_equipas--> ponteiro para a hash table das equipas*/
    inicia_normais(equipas_normais,jogos_normais);
    lista_ligada_jogos=inicializa_jogo(lista_ligada_jogos);
    lista_ligada_equipas=inicializa_equipa(lista_ligada_equipas);
    *conta_linha=0;
    *letra=getchar();
    while (*letra!='x'){          /*ciclo que para quando a primeira letra do input for x*/
        contador+=1;
        if (contador%2!=0)
            *conta_linha+=1;
        que_func(*conta_linha,letra,lista_ligada_equipas,lista_ligada_jogos, jogos_normais,equipas_normais);
        *letra=getchar();
    }
    /*funcoes que dao free a toda a memoria que foi alocada*/
    free(conta_linha);
    free(letra);
    free_da_hash_jogo(lista_ligada_jogos);
    free_da_hash_equipa(lista_ligada_equipas);
    free_equipas_normais(equipas_normais);
    free_jogos_normais(jogos_normais);
    return 0;
}