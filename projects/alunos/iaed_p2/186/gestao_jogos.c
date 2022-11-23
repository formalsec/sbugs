#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "gestao_jogos.h"


/* adiciona os dados de um novo jogo ao sistema */
void a_adicionaNovoJogo(lista_jogo * lst_jogo, Item ** hashtable_jogo, Item ** hashtable_equipa, int contador){
    
    char nome[MAX_STR], equipa1[MAX_STR], equipa2[MAX_STR];
    int score1, score2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&score1,&score2);
    
    /* verifica se o jogo ja existe no sistema*/
    if (procura_item(nome, hashtable_jogo)){ 
        printf("%d Jogo existente.\n", contador);
    }
    else{
        /* verifica se as equipas ja existem no sistema */
        if (!procura_item(equipa1, hashtable_equipa) || !procura_item(equipa2, hashtable_equipa)){
            printf("%d Equipa inexistente.\n", contador);
        }
        else{
            /* cria a estrutura associada ao jogo */
            Item * novo_jogo = cria_jogo(nome, equipa1, equipa2, score1, score2);

            /* insere o endereco do novo jogo na hashtable de jogos */
            insere_hashtable(novo_jogo, hashtable_jogo);

            /* aumenta o numero de vitorias associada 'a equipa vencedora*/
            adiciona_vitoria(hashtable_equipa, novo_jogo);
            
            /* insere endereco do novo jogo na fila de jogos, ordenado por ordem de introducao */
            if (lst_jogo->last){ /* ultimo jogo da lista aponta para o novo jogo caso a lista nao for vazia*/
                novo_jogo->prev = lst_jogo->last;
                lst_jogo->last->next = novo_jogo; 
            }     
            lst_jogo->last = novo_jogo; /* ponteiro para o ultimo jogo da lista aponta para o novo jogo */

            if (!lst_jogo->head){ /* se lista estiver vazia o ponteiro para o primeiro jogo aponta para o novo jogo*/
                lst_jogo->head = novo_jogo; 
            }
        }
    }
}   


/* adicina uma nova equipa ao sistema */
Item * A_adicionaNovaEquipa(Item * head_equipa, Item ** hashtable, int contador){

    char nome[MAX_STR];

    scanf(" %[^\n]", nome);

    /* verifica se a equipa ja esta no sistema */
    if (procura_item(nome, hashtable)){
        printf("%d Equipa existente.\n", contador);
        return head_equipa;
    }
    else{
        /* cria a estrutura associada 'a equipa */
        Item * nova_equipa = cria_equipa(nome);

        /* insere o endereco da nova equipa na hashtable de equipas */
        insere_hashtable(nova_equipa, hashtable);
        
        /* insere endereco do novo jogo na lista de equipas, ordenado por ordem lexicografica */
        if (!head_equipa){ /* caso a lista esteja vazia, a nova equipa e' o primeiro elemento da lista */
            return nova_equipa;
        }
        else { /* compara o nome da nova equipa com o nome da primeira equipa da lista */
            if (strcmp(nova_equipa->nome,head_equipa->nome)<0){
                nova_equipa->next = head_equipa;
                return nova_equipa;
            }
            else{
                /* precorre a lista e insere o endereco da equipa no lugar adequado */
                Item * anterior = head_equipa, *head = head_equipa;
                
                head_equipa = head_equipa->next;
                
                while(head_equipa && strcmp(nova_equipa->nome,head_equipa->nome)>0){
                    anterior = head_equipa;
                    head_equipa = head_equipa->next;
                }
                nova_equipa->next = head_equipa;
                anterior->next = nova_equipa;
                return head;
            }
        }
    }
}


/* lista todos os jogos existentes no sistema por ordem de introducao */
void l_listaTodosJogosPorOrdem(lista_jogo * lst_jogo, int contador){
    Item * j = lst_jogo->head; 

    /* como ja temos uma lista de jogos ordenado pela ordem pretendida, e' so percorrer esta lista */
    while(j){
        printf("%d %s %s %s %d %d\n", contador, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
        j = j->next;
    }
}


/* procura um jogo no sistema dado um nome e dispoe todas as informacoes relativas ao mesmo */
void p_procuraJogo(Item ** hashtable, int contador){
    Item * jogo;
    char nome[MAX_STR];

    scanf(" %[^\n]", nome);

    /* procura o jogo no sistema */
    jogo = procura_item(nome, hashtable);
    
    /* dispoe as informacoes do jogo caso este exista no sistema */
    if (jogo){
        printf("%d %s %s %s %d %d\n", contador, jogo->nome, jogo->equipa1, jogo->equipa2, jogo->score1, jogo->score2);
    }
    else{
        printf("%d Jogo inexistente.\n", contador);
    }
}


/* procura uma equipa no sistema dado um nome e dispoe todas as informacoes relativas 'a mesma */
void P_procuraEquipa(Item ** hashtable, int contador){
    char nome[MAX_STR];
    Item * equipa;

    scanf(" %[^\n]", nome);

    /* procura a equipa no sistema */
    equipa = procura_item(nome, hashtable);

    /* dispoe as informacoes da equipa caso esta exista no sistema */
    if (equipa){
        printf("%d %s %d\n", contador, nome, equipa->vitorias);
    }
    else{
        printf("%d Equipa inexistente.\n", contador);
    }
}


/* remove um jogo do sistema dado um nome */
void r_apagaJogo(lista_jogo * lst_jogo, Item ** hashtable_jogo, Item ** hashtable_equipa, int contador){
    char nome[MAX_STR];

    scanf(" %[^\n]", nome);

    /* procura o jogo no sistema e apaga caso este exista */
    if(!apaga_jogo(nome, hashtable_jogo, hashtable_equipa, lst_jogo)){
        printf("%d Jogo inexistente.\n", contador);
    }
}


/* altera a pontuacao de um jogo existente dado um nome e uma nova pontuacao */
void s_alteraPontuacao(Item ** hashtable_jogo, Item ** hashtable_equipa, int contador){
    Item * jogo;
    int score1, score2;
    char nome[MAX_STR];

    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);

    /* verifica se o jogo existe no sistema */
    if (!(jogo = procura_item(nome, hashtable_jogo))){
        printf("%d Jogo inexistente.\n", contador);
    }
    else{
        /* altera o numero de vitorias das equipas de acordo com a nova pontuaca0*/
        retira_vitoria(hashtable_equipa, jogo);
        /* altera a pontucao relativamente ao jogo */
        jogo->score1 = score1;
        jogo->score2 = score2;
        adiciona_vitoria(hashtable_equipa, jogo);
    }
}


/* lista as equipas existentes no sistema com o maior numero de vitorias por ordem lexicografica */
void g_encontraEquipasMaisVitorias(Item * head_equipa, int contador){
    Item *equipa = head_equipa;
    int maior_vitoria = 0;

    /* percorre a lista de equipas e procura o maior numero de vitorias */
    while(equipa){
        if (equipa->vitorias > maior_vitoria){
            maior_vitoria = equipa->vitorias;
        }
        equipa = equipa->next;
    }

    /* percorre a lista e dipoe as equipas com o numero de vitorias igual ao maior numero de vitorias */
    /* como ja temos uma lista ordenada por ordem lexicografica, e' so percorrer essa lista */
    if (head_equipa){
        printf("%d Melhores %d\n", contador, maior_vitoria);
    }

    while(head_equipa){
        if (head_equipa->vitorias == maior_vitoria){
            printf("%d * %s\n", contador, head_equipa->nome);
        }
        head_equipa = head_equipa->next;
    }
}