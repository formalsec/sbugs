#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "projeto.h"

/* Funcao hash que utiliza strings como criterio de comparacao. Recalcula a sua
base a cada iteracao, o que evita anomalias com chaves irregulares */
int hash(char *c, int size){
    int indice, a = 31415, b = 27183;
    for (indice = 0; strcmp(c,"\0")!=0; c++, a = a*b % (size-1)){
        indice = (a*indice + *c) % size;
    }
    return indice;
}

/* Funcao que inicia a tabela hash utilizada para a estrutura jogo, aloca memoria
de acordo com o tamanho da tabela e define todos os seus indices a NULL */
jogo * inicia_hash_jogos(jogo *table_jogos){
    int i;
    table_jogos = (jogo *)can_fail_malloc(HASH_TABLE_SIZE_JOGOS*sizeof(struct str_jogo));
    for (i = 0; i < HASH_TABLE_SIZE_JOGOS; i++){
        table_jogos[i] = NULL;
    }
    return table_jogos;
}

/* Funcao que inicia a tabela hash utilizada para a estrutura equipa, aloca memoria 
de acordo com o tamanho da tabela e define todos os seus indices a NULL */
equipa * inicia_hash_equipas(equipa *table_equipas) {
    int i;
    table_equipas = (equipa *)can_fail_malloc(HASH_TABLE_SIZE_EQUIPAS*sizeof(struct str_equipa));
    for (i = 0; i < HASH_TABLE_SIZE_EQUIPAS; i++){
        table_equipas[i] = NULL;
    }
    return table_equipas;
}

/* Funcao utilizada no final de todos os comandos, percorre todas as listas (utilizadas
devido ao encadeamento externo), presentes nas duas hashtables, libertando toda a memoria
alocada para estas tabelas */
void free_final(equipa *table_equipas, jogo *table_jogos){
    int i;
    jogo aux_jogo;
    equipa aux_equipa;

    /* Ciclo utilizado para percorrer as listas da hash table dos jogos */
    for(i=0; i<HASH_TABLE_SIZE_JOGOS; i++){
        for(; table_jogos[i]!=NULL; table_jogos[i]=aux_jogo){
            /* Ponteiro auxiliar para nao se perder o proximo jogo na lista */
            aux_jogo=table_jogos[i]->next;
            /* Frees a todos os ponteiros caracteristicos da estrutura jogo */
            free(table_jogos[i]->nome);
            free(table_jogos[i]->score1);
            free(table_jogos[i]->score2);
            free(table_jogos[i]);
        }
    }
    /* Free da hash table dos jogos em si */
    free(table_jogos);

    /* Ciclo utilizado para percorrer as listas da hash table das equipas */
    for(i=0; i<HASH_TABLE_SIZE_EQUIPAS; i++){
        for(; table_equipas[i]!=NULL; table_equipas[i]=aux_equipa){
            /* Ponteiro auxiliar para nao se perder a proxima equipa na lista */
            aux_equipa=table_equipas[i]->next;
            /* Frees a todos os ponteiros caracteristicos da estrutura equipa */
            free(table_equipas[i]->nome);
            free(table_equipas[i]->jogos_ganhos);
            free(table_equipas[i]);
        }
    }
    /* Free da hash table das equipas em si */
    free(table_equipas);
}
