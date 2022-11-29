#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "proj2_aux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Aloca espaco de memoria para uma lista_jogos_equipas
e inicializa todos os seus ponteiros a NULL. Retorna a lista.*/
Lista_jogos_equipas* cria_lista(){
    int i;
    Lista_jogos_equipas *lje = (Lista_jogos_equipas *)can_fail_malloc(sizeof(Lista_jogos_equipas));
    lje->primeira_equipa = NULL;
    lje->ultima_equipa = NULL;
    lje->primeiro_jogo = NULL;
    lje->ultimo_jogo = NULL;
    for ( i = 0; i < TAMANHO_TABELA; i++){
        lje->tab_equipa[i]= can_fail_malloc(sizeof(Tabela_equipas));
        lje->tab_equipa[i]->primeira_equipa = NULL;
        lje->tab_equipa[i]->ultima_equipa = NULL;
    }
    for ( i = 0; i < TAMANHO_TABELA; i++){
        lje->tab_jogo[i]= can_fail_malloc(sizeof(Tabela_jogos));
        lje->tab_jogo[i]->primeiro_jogo = NULL;
        lje->tab_jogo[i]->ultimo_jogo = NULL;
    }
    return lje;
}

/*Aloca espaco de memoria para uma tabela_equipas e inicializa
todos os seus ponteiros a NULL. Retorna a lista.*/
Tabela_equipas* cria_lista_equipas(){
    Tabela_equipas *tabela= (Tabela_equipas *)can_fail_malloc(sizeof(Tabela_equipas));
    tabela->primeira_equipa= NULL;
    tabela->ultima_equipa= NULL;
    return tabela;
}

/*Funcao de dispersao para strings. Retorna o inteiro com
a posicao da tabela onde se vai adicionar a/o equipa/jogo.*/
int hash(char *b){
    int h=0, a=127;
    for(; *b != '\0'; b++){
        h=(a*h + *b) % TAMANHO_TABELA;
    }
    return h;
}

/*Funcao auxiliar ao comando A. Aloca espaco em memoria para uma equipa e
inicializa com o nome dado, 0 vitorias e ponteiros a NULL. Retorna a equipa.*/
Equipa* adiciona_equipa(char *atr1){
    Equipa *nova_equipa = (Equipa*) can_fail_malloc(sizeof(Equipa));
    nova_equipa->nome = (char*) can_fail_malloc(sizeof(char)*(strlen(atr1)+1));
    strcpy(nova_equipa->nome, atr1);
    nova_equipa->vitorias = 0;
    nova_equipa->equipa_seguinte = NULL;
    nova_equipa->prox_tabela = NULL;
    nova_equipa->prox_vit_max = NULL;
    nova_equipa->anterior_vit_max = NULL;
    return nova_equipa;
}

/*Funcao auxiliar ao comando P. Procura uma equipa na tabela de dispersao,
dado um nome. Retorna a equipa, caso exista. Caso contrario, retorna NULL.*/
Equipa* procura_nome_equipa(Lista_jogos_equipas *lje, char *atr1){
    Equipa *equipa;
    int posicao= hash(atr1);
    equipa= lje->tab_equipa[posicao]->primeira_equipa;
    while(equipa != NULL){
        if(strcmp(equipa->nome, atr1) == 0){
            return equipa;
        }
        equipa= equipa->prox_tabela;
    }
    return NULL;
}

/*Funcao auxiliar ao comando a. Aloca espaco em memoria para um jogo e inicializa os atributos
com os dados passados como argumento e os ponteiros a NULL. Retorna o jogo.*/
Jogo* adiciona_jogo(char *atr1, Equipa *equipa_1, Equipa *equipa_2, char *atr2, char *atr3){
    Jogo *novo_jogo= (Jogo*) can_fail_malloc(sizeof(Jogo));
    novo_jogo->nome= (char*) can_fail_malloc(sizeof(char)*(strlen(atr1)+1));
    strcpy(novo_jogo->nome, atr1);
    novo_jogo->equipa1= equipa_1;
    novo_jogo->equipa2= equipa_2;
    novo_jogo->score1= atoi(atr2);
    novo_jogo->score2= atoi(atr3);
    novo_jogo->jogo_seguinte= NULL;
    novo_jogo->jogo_anterior= NULL;
    novo_jogo->prox_tabela= NULL;
    novo_jogo->anterior_tabela= NULL;
    return novo_jogo;
}

/*Funcao auxiliar ao comando p. Procura umjogo na tabela de dispersao,
dado um nome. Retorna o jogo, caso exista. Caso contrario, retorna NULL.*/
Jogo* procura_nome_jogo(Lista_jogos_equipas *lje, char *atr1){
    Jogo *jogo;
    int posicao= hash(atr1);
    jogo = lje->tab_jogo[posicao]->primeiro_jogo;
    while(jogo != NULL){
        if(strcmp(jogo->nome, atr1) == 0){
            return jogo;
        }
        jogo= jogo->prox_tabela;
    }
    return NULL;
}

/*Funcao auxiliar ao comando g. Procura o numero maximo de vitorias, percorrendo toda
a lista de equipas. Retorna o inteiro encontrado.*/
int procura_max_vitorias(Lista_jogos_equipas *lje){
    Equipa *equipa;
    int max_vitorias= 0;
    equipa= lje->primeira_equipa;
    while(equipa != NULL){
        if(equipa->vitorias > max_vitorias){
            max_vitorias= equipa->vitorias;
        }
        equipa= equipa->equipa_seguinte;
    }
    return max_vitorias;
}

/*Funcao auxiliar ao comando g. Cria uma lista de equipas e adiciona-lhe todas as equipas
do sistema que tenham tantas vitorias quanto o numero maximo de vitorias. Retorna a lista.*/
Tabela_equipas* procura_equipa_vitorias(Lista_jogos_equipas *lje, int num_max_vitorias){
    Tabela_equipas *max_vitorias;
    Equipa *equipa;
    equipa= lje->primeira_equipa;
    max_vitorias = cria_lista_equipas();
    while(equipa != NULL){
        if(equipa->vitorias == num_max_vitorias){
            if(max_vitorias->primeira_equipa == NULL){
                max_vitorias->primeira_equipa= equipa;
            }
            else{
                max_vitorias->ultima_equipa->prox_vit_max= equipa;
                equipa->anterior_vit_max = max_vitorias->ultima_equipa;
            }
            max_vitorias->ultima_equipa= equipa;
        }
        equipa= equipa->equipa_seguinte;
    }
    return max_vitorias;
}

/*Funcao auxiliar ao comando g. Ordena a lista de equipas recebida como parametro 
e imprime a lista. Liberta a lista quando acaba de imprimir.*/
void ordena_equipa_vitorias(Tabela_equipas *max_vitorias, int NL, int num_max_vitorias){
    Equipa *equipa_1, *equipa_2, *equipa_menor;
    if(max_vitorias->primeira_equipa == NULL){  /*Se a lista estiver vazia, nao imprime*/
        free(max_vitorias);                     /*nada, liberta a memoria da lista e retorna.*/
        return;
    }
    equipa_1= max_vitorias->primeira_equipa;
    printf("%d Melhores %d\n", NL, num_max_vitorias);
    while(equipa_1 != NULL){
        if(equipa_1->prox_vit_max == NULL){          /*Se so existir uma equipa na lista, imprime*/
            printf("%d * %s\n", NL, equipa_1->nome); /*essa equipa, liberta a memoria e retorna.*/
            max_vitorias->primeira_equipa= NULL;
            max_vitorias->ultima_equipa= NULL;
            free(max_vitorias);
            return;
        }
        else{
            equipa_2= equipa_1->prox_vit_max;
            while(equipa_2 != NULL){
                if(strcmp(equipa_1->nome,equipa_2->nome) > 0){
                    equipa_menor= equipa_2;
                }
                else if(strcmp(equipa_1->nome,equipa_2->nome)<0){
                    equipa_menor= equipa_1;
                }
                equipa_2= equipa_2->prox_vit_max;
                equipa_1= equipa_menor;
            }
            printf("%d * %s\n", NL, equipa_menor->nome);
            /*Depois de imprimir a menor equipa, altera os ponteiros necessarios
            por forma a nao comparar novamente com esta equipa.*/
            if(equipa_menor == max_vitorias->primeira_equipa){  
                max_vitorias->primeira_equipa=max_vitorias->primeira_equipa->prox_vit_max;
            }
            if(equipa_menor->anterior_vit_max == NULL){
                if(equipa_menor->prox_vit_max == NULL){
                    max_vitorias->primeira_equipa= NULL;
                    max_vitorias->ultima_equipa= NULL;
                }
                else{
                    equipa_menor->prox_vit_max->anterior_vit_max= NULL;
                }
            }
            else if(equipa_menor->prox_vit_max == NULL){
                equipa_menor->anterior_vit_max->prox_vit_max= NULL;
                max_vitorias->ultima_equipa= max_vitorias->ultima_equipa->anterior_vit_max;
            }
            else{
                equipa_menor->anterior_vit_max->prox_vit_max= equipa_menor->prox_vit_max;
                equipa_menor->prox_vit_max->anterior_vit_max = equipa_menor->anterior_vit_max;
            }
            equipa_1= max_vitorias->primeira_equipa;
        }
    }
    free(max_vitorias);
}

/*Funcao auxiliar ao comando x. Liberta toda a memoria alocada no sistema.*/
void free_lista(Lista_jogos_equipas *lje){
    Equipa *equipa1, *equipa2;
    Jogo *jogo1, *jogo2;
    int i;
    equipa1= lje->primeira_equipa;
    while(equipa1 != NULL){
        equipa2 = equipa1;
        free(equipa2->nome);
        equipa1= equipa1->equipa_seguinte;
        free(equipa2);
    }
    jogo1= lje->primeiro_jogo;
    while(jogo1 != NULL){
        jogo2= jogo1;
        free(jogo2->nome);
        jogo1= jogo1->jogo_seguinte;
        free(jogo2);
    }
    for(i=0; i<TAMANHO_TABELA; i++){
        free(lje->tab_equipa[i]);
        free(lje->tab_jogo[i]);
    }
    free(lje);
}