#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"


/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|. COMANDOS  .|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/

/* ESTA FUNCAO CRIA UMA NOVA EQUIPA E ADICONA-A A HASHTABLE DAS EQUIPAS */
void novaEquipa(ht_equipas *hashtable, int NL){
    
    char nome_equipa[STRING_SIZE];

    scanf(" %[^\n]",nome_equipa);
    ht_set_equipas(hashtable, nome_equipa, NL);
}

/* ESTA FUNCAO PROCURA NA HASHTABLE DAS EQUIPAS O NOME DA EQUIPA E IMPRIME CASO HAJA */
void procuraEquipa(ht_equipas *hashtable, int NL){

    char nome_equipa[STRING_SIZE];

    scanf(" %[^\n]",nome_equipa);
    ht_search_equipas(hashtable, nome_equipa, NL);
}

/* ESTA FUNCAO CRIA UM NOVO JOGO ADICIONANDO-O A HASHTABLE DOS JOGOS */
void novoJogo(ht_jogo *hashtable, ll_jogos **ll_head, ht_equipas *hashtable_equipas, int NL){
   
    char nome_jogo[STRING_SIZE], equipa1[STRING_SIZE], equipa2[STRING_SIZE];
    int score1, score2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome_jogo,equipa1,equipa2,&score1,&score2);
    ht_set(hashtable, ll_head, hashtable_equipas, nome_jogo, equipa1, equipa2, score1, score2, NL); 
}

/* ESTA FUNCAO PROCURA UM JOGO PELO NOME E SE ENCONTRAR IMPREME-LO */
void procuraJogo(ht_jogo *hashtable, int NL){
    
    char nome_jogo[STRING_SIZE];

    scanf(" %[^\n]",nome_jogo);
    ht_search(hashtable, nome_jogo,NL);
}

/* ESTA FUNCAO APAGA UM JOGO E ATUALIZA O RESULTADO DECREMENTANDO CASO VITORIA */
void apagaJogo(ht_jogo *hashtable, ll_jogos **ll_head, ht_equipas *hashtable_equipas, int NL){
    
    char nome_jogo[STRING_SIZE];
    link_jogo *jogo;
    link_equipa *equipa;

    scanf(" %[^\n]",nome_jogo);

    jogo = st_search_jogo(hashtable, nome_jogo);
    if(jogo != NULL){
        /* atualiza o resultado consoante o resultado quando eliminamos
        a equipa vencedora temos de dimuir o nr de vitorias */
        if(jogo->score1 > jogo->score2){
            equipa = st_search(hashtable_equipas, jogo->equipa1);
            equipa->nr_vitorias--;
        }
        /* quando eliminamos a equipa vencedora temos de dimuir o nr de vitorias */
        if(jogo->score1 < jogo->score2){
            equipa = st_search(hashtable_equipas, jogo->equipa2);
            equipa->nr_vitorias--;
        }
    }
    /* retira do lista ligada dos jogos */
    deleteNode(ll_head, jogo);
    /* retira da hashtable dos jogos */
    ht_del(hashtable, nome_jogo, NL);
    
}

/* ESTA FUNCAO ALTERA O SCORE DE UM JOGO */
void alteraScore(ht_jogo *hashtable, ht_equipas *hashtable_equipas, int NL){

    char nome_jogo[STRING_SIZE];
    int score1,score2;

    scanf(" %[^:\n]:%d:%d",nome_jogo,&score1,&score2);
    ht_change(hashtable, hashtable_equipas, nome_jogo, score1, score2, NL);
}

/* ESTA FUNCAO IMPRIME UMA TABELA COM AS PONTUACOES */
void tabScoresEquipas(ht_equipas *hashtable_equipas, int NL){

    link_equipa *x, *y;
    int i, j, e, contador = 0;
    char *vetor[2000];
    unsigned int mais_vitorias = 0;

    /* percorre todas as posicoes da tabela e guarda o nr de vitorias mais alto */
    for(i = 0; i < TAM_TABELA; i++){

        x = hashtable_equipas->entries[i];

        while(x != NULL){
            contador++;                             /* contador do nr de elementos na hashtable */
            if(x->nr_vitorias > mais_vitorias)
                mais_vitorias = x->nr_vitorias;
            x = x->next;
        }
    }
    /* se nao houver equipas sai */
    if(contador == 0)
        return;
        
    /* percorre todas as posicoes da hashtable que tem o nr de vitorias mais alto e guarda num vetor */
    for(i = 0, e = 0; i < TAM_TABELA; i++){

        y = hashtable_equipas->entries[i];
        
        while(y != NULL){
            
            if(y->nr_vitorias == mais_vitorias){ 
                vetor[e] = y->nome;
                e++;
            }
            y = y->next;
        }
    }

    /* ordena por ordem alfabetica */
    qsort(vetor,e,sizeof(char*),compara_nomes);

    /* imprime a tabela dos resultados */
    printf("%d Melhores %d\n",NL,mais_vitorias);
    for(j = 0; j < e; j++){
        printf("%d * %s\n",NL,vetor[j]);
    }
}

/* ESTA FUNCAO COMPARA DOIS NOMES E EH USADA NO QSORT PARA ORDENAR ALFABETICAMENTE */
int compara_nomes(const void *a, const void *b){

    char **nomeA = (char**)a;
    char **nomeB = (char**)b;

    return strcmp(*nomeA,*nomeB);
}

/* ESTA FUNCAO LISTA OS JOGOS PELA ORDEM DE ENTRADA */
void listaJogos(ll_jogos *ll_head, int NL){
    
    /* percorre todos os jogos inseridos na linked list */
    while (ll_head != NULL){ 

        printf("%d %s %s %s %d %d\n",NL,ll_head->jogo->nome,ll_head->jogo->equipa1,ll_head->jogo->equipa2,ll_head->jogo->score1,ll_head->jogo->score2);
        ll_head = ll_head->next; 
    }
}

/* ESTA FUNCAO LIBERTA TODA A MEMORIA ALOCADA PARA A HASHTABLE DOS JOGOS */
void free_hashtable(ht_jogo *hashtable){

    int i = 0;
    link_jogo *x, *y;

    for(; i < TAM_TABELA; i++){

        x = hashtable->links[i];
        while(x != NULL){

            y = x;
            x = x->next;
            free(y->equipa1);
            free(y->equipa2);
            free(y->nome);
            free(y);
        }
    }
    free(hashtable->links);
    free(hashtable);
}

/* ESTA FUNCAO LIBERTA TODA A MEMORIA ALOCADA PARA A HASHTABLE DOS EQUIPAS */
void free_hashtable_equipas(ht_equipas *hashtable_equipas){

    int i = 0;
    link_equipa *x, *y;

    for(; i < TAM_TABELA; i++){

        x = hashtable_equipas->entries[i];
        while(x != NULL){

            y = x;
            x = x->next;
            free(y->nome);
            free(y);
        }
    }
    free(hashtable_equipas->entries);
    free(hashtable_equipas);
}