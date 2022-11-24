#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "Jogo.h"

#define TAMANHO_TABELA 2000

/* Funcao que cria um jogo. */
Jogo *novoJogo(char* nome, Equipa* equipa1, Equipa* equipa2, int pontos1, int pontos2) {
    Jogo *jogo  = can_fail_malloc(sizeof(Jogo));
    jogo -> nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(jogo -> nome, nome);
    jogo -> equipa1 = equipa1;
    jogo -> equipa2 = equipa2;
    jogo -> pontuacao[0] = pontos1;
    jogo -> pontuacao[1] = pontos2;
    return jogo;
}

/* Funcao que libera a memoria alocada por um jogo. */
void liberarJogo(Jogo *jogo){
    free(jogo -> nome);
    free(jogo);
}

/* Funcao que cria uma entrada da hashtable. */
entradaJ_t *par_htJ(char *chaveJ, Jogo *jogo) {
    /* Alocar a entrada. */
    entradaJ_t *entrada = can_fail_malloc(sizeof(entradaJ_t));
    entrada -> chaveJ = can_fail_malloc(sizeof(char)*strlen(chaveJ) + 1);
    entrada -> jogo = jogo;
    /* Copiar a chave. */
    strcpy(entrada -> chaveJ, chaveJ);
    /* O proximo comeca como NULL mas pode ser mudado posteriormente. */
    entrada -> proxJ = NULL;
    return entrada;
}

/* Funcao que cria uma hashtable. */
htJ_t *criar_htJ(void) {
    int i = 0;
    /* Alocar espaco para a tabela. */
    htJ_t *hashtable = can_fail_malloc(sizeof(htJ_t));
    /* Alocar espaco para ad entradas da tabela. */
    hashtable -> entradas = can_fail_malloc(sizeof(entradaJ_t) * TAMANHO_TABELA);
    /* Inicializar todas como NULL. */
    for (; i < TAMANHO_TABELA; ++i) hashtable -> entradas[i] = NULL;
    return hashtable;
}

/* Funcao que cria uma hash baseado em uma chave. */
int hashJ(char *chaveJ) {
    unsigned int valor_hash = 0;
    int i = 0;
    int tamanho_chave = strlen(chaveJ);
    /* Fazer varias repeticoes da multiplicacao. */
    for (; i < tamanho_chave; ++i) valor_hash = valor_hash * 23 + chaveJ[i];
    /* Ter certeza que o valor da hash eh maior que 0 e menor que o tamanho da tabela. */
    valor_hash %= TAMANHO_TABELA;
    return valor_hash;
}

/* Funcao que apropria uma entrada a hashtable. */
void apropriar_htJ(htJ_t *hashtable, char *chaveJ, Jogo *jogo) {
    int index = hashJ(chaveJ);
    entradaJ_t *ant;
    /* Explorar uma entrada. */
    entradaJ_t *entradaJ = hashtable -> entradas[index];
    /* Se estiver vazia, inserir imediatamente */
    if (entradaJ == NULL) {
        hashtable -> entradas[index] = par_htJ(chaveJ, jogo);
        return;
    }
    /* Iterar sobre cada entrada ate achar uma chave compativel ou ate o final. */
    while (entradaJ != NULL) {
        /* Verificar a chave. */
        if (strcmp(entradaJ -> chaveJ, chaveJ) == 0) {
            /* Se achado, substituir o valor. */
            entradaJ -> jogo = jogo;
            return;
        }
        ant = entradaJ;
        entradaJ = ant -> proxJ;
    }
    /* Se chegar ao final e nao ter nenhum item compstivel, adicionar novo. */
    ant -> proxJ = par_htJ(chaveJ, jogo);
}

/* Funcao que retorna um jogo que eh compativel com uma chave chaveJ. */
Jogo *obter_htJ(htJ_t *hashtable, char *chaveJ) {
    int index = hashJ(chaveJ);
    /* Tentar achar um index valido. */
    entradaJ_t *entradaJ = hashtable -> entradas[index];
    /* Se nao existir nada no index, nao ha entrada. */
    if (entradaJ == NULL) return NULL;
    /* Iterar sobre cada entrada */
    while (entradaJ != NULL) {
        /* Retornar valor se encontrado. */
        if (strcmp(entradaJ -> chaveJ, chaveJ) == 0) return entradaJ -> jogo;
        
        /* Ir para a proxima entrada. */
        entradaJ = entradaJ -> proxJ;
    }
    return NULL;
}

/* Funcao que apaga uma equipa da hashtable. */
void htJ_del(htJ_t *hashtable, char *chaveJ) {
    int index = hashJ(chaveJ), id = 0;
    entradaJ_t *ant;
    /* Tentar achar um jogo valido com o index. */
    entradaJ_t *entradaJ = hashtable -> entradas[index];
    if (entradaJ == NULL) {
        return;
    }
    /* Itera sobre cada entrada ate achar uma chave compativel ou chegar ao final da tabela. */
    while (entradaJ != NULL) {
        /* Verifica se a primeira entrada eh nula. */
        if (strcmp(entradaJ -> chaveJ, chaveJ) == 0) {
            /* Verifica se a primeira entrada eh nula. */
            if (entradaJ -> proxJ == NULL && id == 0) {
                hashtable -> entradas[index] = NULL;
            }
            /* Verifica se a entrada eh o primeiro item da hashtable. */
            if (entradaJ -> proxJ != NULL && id == 0) {
                hashtable -> entradas[index] = entradaJ -> proxJ;
            }
            /* Verifica se a entrada eh o ultimo item da hashtable. */
            if (entradaJ -> proxJ == NULL && id != 0) {
                ant -> proxJ = NULL;
            }
            /* Verifica se a entrada eh um item no meio da hashtable. */
            if (entradaJ -> proxJ != NULL && id != 0) {
                ant -> proxJ = entradaJ -> proxJ;
            }
            /* Libera a entrada que foi deletada. */
            free(entradaJ -> chaveJ);
            free(entradaJ);
            return;
        }
        ant = entradaJ;
        entradaJ = ant -> proxJ;
        ++id;
    }
}

