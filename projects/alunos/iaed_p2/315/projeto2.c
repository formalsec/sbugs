#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "jogos.h"
#include "comuns.h"

/**********/
/*comandos*/
/**********/

void a(int Nl,hash_table_jogos table_jogo,lista_jogos *jogos,hash_table_team table_equipas){

    /*Esta funcao adiciona um novo jogo ao sistema. Da erro se o jogo ja existir
    ou se uma das equipas nao existir.*/

    char nome[MAX_STRING],equipa1[MAX_STRING],equipa2[MAX_STRING];
    char *nome1,*equipa11,*equipa22;
    int score[2],h;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&score[0],&score[1]);
    nome1 = reduce_string(nome);
    equipa11 = reduce_string(equipa1);
    equipa22 = reduce_string(equipa2);
    if(hash_search_jogos(table_jogo,nome1))
        printf("%d Jogo existente.\n",Nl);
    else if(!(hash_search_equipas(table_equipas,equipa11) && hash_search_equipas(table_equipas,equipa22)))
        printf("%d Equipa inexistente.\n",Nl);
    else{
        int r1;
        jogo new_jogo = cria_jogo(nome1,equipa11,equipa22,score);
        hash_insert_jogos(table_jogo,nome1);
        h = hash(nome1,table_jogo->cap);
        insert_end_list_jogos(jogos,new_jogo);
        table_jogo->table[h]->no_j = jogos->last;
        r1 = score[0]-score[1];
        if(r1>0){
            no team = hash_search_equipas(table_equipas,equipa11);
            team->no_e->vitorias +=1;
        }else if(r1<0){
            no team = hash_search_equipas(table_equipas,equipa22);
            team->no_e->vitorias +=1;
        }
    }
    free(nome1);
    free(equipa11);
    free(equipa22);
}

void A(int Nl,hash_table_team table_equipas,lista *equipas){

    /*Esta funcao adiciona uma equipa ao sistema.
    Da erro no caso de a equipa ja existir.*/

    char nome[MAX_STRING];
    char *equipa;
    scanf(" %[^:\n]",nome);
    equipa = reduce_string(nome);
    if(!(hash_search_equipas(table_equipas,equipa))){
        equipas->head = insert_equipa(equipas->head,equipa);
        hash_insert_equipas(table_equipas,equipa,equipas);
    }
    else
        printf("%d Equipa existente.\n",Nl);
    free(equipa);
}

void l(int Nl,lista_jogos *jogos){

    /*Esta funcao lista todos os jogos do sistema na forma:
    NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
    sendo NL o numero da linha do comando de input que chamou a funcao.*/

    no_jogo aux;
    for(aux = jogos->head;aux != NULL;aux = aux->next)
        printf("%d %s %s %s %d %d\n",Nl,aux->game.nome,aux->game.equipa1,aux->game.equipa2,aux->game.score0,aux->game.score1);
}


void p(int Nl,hash_table_jogos table_jogos){

    /*Esta funcao procura um jogo dado um nome e lista-o na forma:
    NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
    sendo NL o numero da linha do comando de input que chamou a funcao.
    Da erro no caso do jogo nao existir.*/

    char nome[MAX_STRING];
    char *nome1;
    node_jogo aux;
    scanf(" %[^:\n]",nome);
    nome1 = reduce_string(nome);
    aux = hash_search_jogos(table_jogos,nome1);
    free(nome1);
    if(aux == NULL)
        printf("%d Jogo inexistente.\n",Nl);
    else
       printf("%d %s %s %s %d %d\n",Nl,aux->no_j->game.nome,aux->no_j->game.equipa1,aux->no_j->game.equipa2,aux->no_j->game.score0,aux->no_j->game.score1); 
}


void P(int Nl,hash_table_team table_equipas){

    /*Esta funcao procura uma equipa dado um nome e lista a na forma:
    NL nome-equipa numero-de-jogos-ganhos
    Da erro no caso da equipa nao existir.*/

    char nome[MAX_STRING];
    char *equipa;
    no aux;
    scanf(" %[^:\n]",nome);
    equipa = reduce_string(nome);
    aux = hash_search_equipas(table_equipas,equipa);
    free(equipa);
    if(aux == NULL)
        printf("%d Equipa inexistente.\n",Nl);
    else
        printf("%d %s %d\n",Nl,aux->no_e->nome_equipa,aux->no_e->vitorias);
}

void r(int Nl,hash_table_jogos table_jogos,lista_jogos* jogos,hash_table_team table_equipas){

    /*Esta funcao remove um jogo do sistema.
    Da erro no caso de o jogo para ser removido nao
    existir.*/

    char nome[MAX_STRING];
    char *nome1;
    node_jogo aux;
    no_jogo aux1;
    int r;
    scanf(" %[^:\n]",nome);
    nome1 = reduce_string(nome);
    aux = hash_search_jogos(table_jogos,nome1);
    if(aux == NULL)
        printf("%d Jogo inexistente.\n",Nl );
    else{
        r = aux->no_j->game.score0 - aux->no_j->game.score1;
        if(r>0){
            no team = hash_search_equipas(table_equipas,aux->no_j->game.equipa1);
            team->no_e->vitorias -=1;
        }else if(r<0){
            no team = hash_search_equipas(table_equipas,aux->no_j->game.equipa2);
            team->no_e->vitorias -=1;
        }
        if(strcmp(jogos->last->game.nome,aux->no_j->game.nome) == 0){
            jogos->last = jogos->last->prev;
        }
        remove_jogos(table_jogos,aux);
        if(jogos->head->game.nome == NULL){
            if(jogos->head->next != NULL){
    		  aux1 = jogos->head->next;
    		  free(jogos->head);
    		  jogos->head = aux1;
              aux1->prev = NULL;
            }else{
                free(jogos->head);
                jogos->head = NULL;
            }
    	}
        
    }
   
    free(nome1);
}


void s(int Nl,hash_table_jogos table_jogos,hash_table_team hash_equipa){

    /*Esta funcao altera o score de um jogo dado o nome.
    Da erro no caso de o jogo nao existir.*/

    char nome[MAX_STRING];
    char *nome1;
    int score[2];
    node_jogo aux;
    scanf(" %[^:\n]:%d:%d",nome,&score[0],&score[1]);
    nome1 = reduce_string(nome);
    aux = hash_search_jogos(table_jogos,nome1);
    if(aux == NULL)
        printf("%d Jogo inexistente.\n",Nl);
    else{
        int r1,r2;
        r1 = aux->no_j->game.score0 - aux->no_j->game.score1;
        r2 = score[0] - score[1];
        if(r1>0 && r2<0){
            no team,team1;
            team = hash_search_equipas(hash_equipa,aux->no_j->game.equipa1);
            team->no_e->vitorias -=1;
            team1 = hash_search_equipas(hash_equipa,aux->no_j->game.equipa2);
            team1->no_e->vitorias +=1;
        }else if(r1<0 && r2>0){
            no team,team1;
            team = hash_search_equipas(hash_equipa,aux->no_j->game.equipa1);
            team->no_e->vitorias +=1;
            team1 = hash_search_equipas(hash_equipa,aux->no_j->game.equipa2);
            team1->no_e->vitorias -=1;
        }else if(r1==0 && r2>0){
            no team;
            team = hash_search_equipas(hash_equipa,aux->no_j->game.equipa1);
            team->no_e->vitorias +=1;
        }else if(r1==0 && r2<0){
            no team;
            team = hash_search_equipas(hash_equipa,aux->no_j->game.equipa2);
            team->no_e->vitorias +=1;
        }else if(r1>0 && r2==0){
            no team;
            team = hash_search_equipas(hash_equipa,aux->no_j->game.equipa1);
            team->no_e->vitorias -=1;
        }else if(r1<0 && r2==0){
            no team;
            team = hash_search_equipas(hash_equipa,aux->no_j->game.equipa2);
            team->no_e->vitorias -=1;
        }
        aux->no_j->game.score0 = score[0];
        aux->no_j->game.score1 = score[1];
    }
    free(nome1);

}

void g(int Nl,lista *equipas){

    /*Esta funcao encontra as equipas que ganharam mais jogos e 
    lista por ordem lexicografica (do nome da equipa) no formato:
    NL Melhores numero-de-jogos-ganhos
    NL * nome-equipa1
    NL * nome-equipa2
    NL * nome-equipa3
    ...
    Sendo Nl o numero da linha onde foi chamado o comando.*/

    if(equipas->head != NULL){
        node_equipa lista;
        node_equipa aux;
        node_equipa aux1;
        int maior = 0;
        lista = NULL;
        for(aux = equipas->head;aux != NULL;aux = aux->next){
            if(aux->vitorias > maior){
                maior = aux->vitorias;
                libertar_lista_teams(lista);
                lista = NULL;   
                lista = insert_equipa(lista,aux->nome_equipa);
            }else if(aux->vitorias == maior){
                char*equipa = aux->nome_equipa;
                lista = adicionar_ordem_alfabetica(lista,equipa); 
            }
        }
        printf("%d Melhores %d\n",Nl,maior);
        for(aux1 = lista;aux1 != NULL;aux1 = aux1->next)
            printf("%d * %s\n",Nl,aux1->nome_equipa);
        libertar_lista_teams(lista);
    }
}


/*******************/
/*corpo do programa*/
/*******************/

int main(){
    /**equipas -> lista com todas as equipas do sistema.
    *jogos   -> lista com todos os jogos, sendo a cabeca da lista o jogo mais antigo
                e o ultimo elemento o mais recente.
    table_equipas -> hash table que contem as equipas.
    table_jogos -> hash table que contem os jogos.
    comando -> caracter correspondente ao comando inserido.
    NL -> numero inteiro que corresponde a linha de input.*/
    lista *equipas;
    lista_jogos *jogos;
    hash_table_team table_equipas;
    hash_table_jogos table_jogos;
    char comando;
    int NL = 1;
    table_equipas = can_fail_malloc(sizeof(struct stru_hash_equipa));
    init_hash_table_equipas(table_equipas,SIZE_HASH_EQUIPAS);
    table_jogos = init_hash_table_jogos(SIZE_HASH);
    equipas = can_fail_malloc(sizeof(lista));
    jogos = can_fail_malloc(sizeof(lista_jogos));
    equipas->head = NULL;
    jogos->head = NULL;
    comando = getchar();
    while(comando != 'x'){
        switch (comando){
            case 'a':
                a(NL,table_jogos,jogos,table_equipas);
                NL++;
                break;
            case 'A':
                A(NL,table_equipas,equipas);
                NL++;
                break;
            case 'l':
                l(NL,jogos);
                NL++;
                break;
            case 'p':
                p(NL,table_jogos);
                NL++;
                break;
            case 'P':
                P(NL,table_equipas);
                NL++;
                break;
            case 'r':
                r(NL,table_jogos,jogos,table_equipas);
                NL++;
                break;
            case 's':
                s(NL,table_jogos,table_equipas);
                NL++;
                break;
            case 'g':
                g(NL,equipas);
                NL++;
                break;
            }
        
        comando = getchar();
    }
    libertar_hash_equipas(table_equipas);
    free(equipas);
    libertar_hash_jogos(table_jogos);
    free(jogos->head);
    free(jogos);
    return 0;
}
