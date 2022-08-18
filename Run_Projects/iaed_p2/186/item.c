#include "item.h"


/* recebe os dados relativamento a um jogo e cria a estrutura associada ao mesmo */
Item * cria_jogo(char * nome, char * equipa1, char * equipa2, int score1, int score2){
    /* reserva espaco na memoria para a estrutura */
    Item * novo_jogo = (Item*) malloc(sizeof(Item));

    /* reserva espaco na memoria para o nome do jogo */
    novo_jogo->nome = (char*) malloc((strlen(nome)+1)*sizeof(char));
    strcpy(novo_jogo->nome, nome);

    /* reserva espaco na memoria para os nomes das equipas */
    novo_jogo->equipa1 = (char*) malloc((strlen(equipa1)+1)*sizeof(char));
    strcpy(novo_jogo->equipa1, equipa1);
    novo_jogo->equipa2 = (char*) malloc((strlen(equipa2)+1)*sizeof(char));
    strcpy(novo_jogo->equipa2, equipa2);

    /* atribui 'a estrutura as pontuacaoes associadas ao jogo */
    novo_jogo->score1 = score1;
    novo_jogo->score2 = score2;
    
    /* iniciaiza os ponteiros e os dados que nao sao relativos ao item jogo a zero e/ou NULL*/
    novo_jogo->next = NULL;
    novo_jogo->prev = NULL;
    novo_jogo->next_hash = NULL;
    novo_jogo->vitorias = 0;

    return novo_jogo;
}


/* recebe o nome de uma equipa e cria a estrutura associada 'a mesma */
Item * cria_equipa(char * nome){
    /* reserva espaco na memoria para a estrutura */
    Item * nova_equipa = (Item*) malloc(sizeof(Item));

    /* reserva espaco na memoria para o nome da equipa */
    nova_equipa->nome = (char*) malloc((strlen(nome)+1)*sizeof(char));
    strcpy(nova_equipa->nome, nome);

    /* iniciaiza os ponteiros, o numero de vitorias e os dados que nao sao relativos ao item equipa a zero e/ou NULL */
    nova_equipa->vitorias = 0;

    nova_equipa->equipa1 = NULL;
    nova_equipa->equipa2 = NULL;
    nova_equipa->score1 = 0;
    nova_equipa->score2 = 0;
    nova_equipa->next = NULL;
    nova_equipa->prev = NULL;
    nova_equipa->next_hash = NULL;

    return nova_equipa;
}


/* apaga na memoria todas as estruturas associadas aos jogos */
void apaga_jogos(lista_jogo * l){
    Item * aux;

    /* percorre a lista de jogos e apaga todos os jogos */
    while(l->head){
        aux = l->head->next;
        free(l->head->nome);
        free(l->head->equipa1);
        free(l->head->equipa2);
        free(l->head);
        l->head = aux;
    }
    free(l);
}


/* apaga na memoria todas as estruturas associadas 'as equipas */
void apaga_equipas(Item * head_equipa){
    Item * aux;

     /* percorre a lista de equipas e apaga todas as equipas */
    while(head_equipa){
        aux = head_equipa->next;
        free(head_equipa->nome);
        free(head_equipa);
        head_equipa = aux;
        
    }
}