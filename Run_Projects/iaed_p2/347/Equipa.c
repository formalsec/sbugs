#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Equipa.h"

/* Funcao que cria uma equipa. */
Equipa *novaEquipa(char* nome) {
    Equipa *equipa;
    equipa = malloc(sizeof(Equipa));
    equipa -> nome = malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(equipa -> nome, nome);
    equipa -> vitorias = 0;
    return equipa;
}

/* Funcao que libera a memoria alocada por uma equipa. */
void liberarEquipa(Equipa *equipa){
    free(equipa -> nome);
    free(equipa);
}

/* Funcao que cria uma entrada da hashtable. */
entradaE_t *criarEntrada_htE(char *chaveE, Equipa *equipa) {
    /* Alocar a entrada. */
    entradaE_t *entrada = malloc(sizeof(entradaE_t));
    entrada -> chaveE = malloc(strlen(chaveE) + 1);
    entrada -> equipa = equipa;
    /* Copiar a chave. */
    strcpy(entrada -> chaveE, chaveE);
    /* O proximo comeca como NULL mas pode ser mudado posteriormente. */
    entrada -> proxE = NULL;
    return entrada;
}

/* Funcao que cria uma hashtable. */
htE_t *criar_htE(void) {
    int i = 0;
    /* Alocar espaco para a tabela. */
    htE_t *hashtable = malloc(sizeof(htE_t));
    /* Alocar espaco para ad entradas da tabela. */
    hashtable -> entradas = malloc(sizeof(entradaE_t) * TAMANHO_TABELA);
    /* Inicializar todas como NULL. */
    for (; i < TAMANHO_TABELA; ++i) hashtable -> entradas[i] = NULL;
    return hashtable;
}

/* Funcao que cria uma hash baseado em uma chave. */
int hashE(char *chaveE) {
    unsigned int valor_hash = 0;
    int i = 0;
    int tamanho_chave = strlen(chaveE);
    /* Fazer varias repeticoes da multiplicacao. */
    for (; i < tamanho_chave; ++i) valor_hash = valor_hash * 23 + chaveE[i];
    /* Ter certeza que o valor da hash eh maior que 0 e menor que o tamanho da tabela. */
    valor_hash %= TAMANHO_TABELA;
    return valor_hash;
}

/* Funcao que apropria uma entrada a hashtable. */
void apropriar_htE(htE_t *hashtable, char *chaveE, Equipa *equipa) {
    int index = hashE(chaveE);
    entradaE_t *ant;
    /* Explorar uma entrada. */
    entradaE_t *entradaE = hashtable -> entradas[index];
    /* Se estiver vazia, inserir imediatamente */
    if (entradaE == NULL) {
        hashtable -> entradas[index] = criarEntrada_htE(chaveE, equipa);
        return;
    }
    /* Iterar sobre cada entrada ate achar uma chave compativel ou ate o final. */
    while (entradaE != NULL) {
        /* Verificar a chave. */
        if (strcmp(entradaE -> chaveE, chaveE) == 0) {
            /* Se achado, substituir o valor. */
            entradaE -> equipa = equipa;
            return;
        }
        ant = entradaE;
        entradaE = ant -> proxE;
    }
    /* Se chegar ao final e nao ter nenhum item compstivel, adicionar novo. */
    ant -> proxE = criarEntrada_htE(chaveE, equipa);
}

/* Funcao que retorna uma equipe que eh compativel com uma chave chaveE. */
Equipa *obter_htE(htE_t *hashtable, char *chaveE) {
    int index = hashE(chaveE);
    /* Tentar achar um indice valido. */
    entradaE_t *entradaE = hashtable -> entradas[index];
    /* Se nao existir nada no index, nao ha entrada. */
    if (entradaE == NULL) return NULL;
    /* Iterar sobre cada entrada */
    while (entradaE != NULL) {
        /* retornar valor se encontrado. */
        if (strcmp(entradaE -> chaveE, chaveE) == 0) return entradaE -> equipa;
        /* Ir para a proxima entrada. */
        entradaE = entradaE -> proxE;
    }
    return NULL;
}

/* Funcao que apaga uma equipa da hashtable. */
void htE_del(htE_t *hashtable, char *chaveE) {
    int index = hashE(chaveE), id = 0;
    entradaE_t *ant;
    /* Tentar achar um jogo valido com o index. */
    entradaE_t *entradaE = hashtable -> entradas[index];
    if (entradaE == NULL) {
        return;
    }
    /* Itera sobre cada entrada ate achar uma chave compativel ou chegar ao final da tabela. */
    while (entradaE != NULL) {
        /* Verifica a chave. */
        if (strcmp(entradaE -> chaveE, chaveE) == 0) {
            /* Verifica se a primeira entrada eh nula. */
            if (entradaE -> proxE == NULL && id == 0) {
                hashtable -> entradas[index] = NULL;
            }
            /* Verifica se a entrada eh o primeiro item da hashtable. */
            if (entradaE -> proxE != NULL && id == 0) {
                hashtable -> entradas[index] = entradaE -> proxE;
            }
            /* Verifica se a entrada eh o ultimo item da hashtable. */
            if (entradaE -> proxE == NULL && id != 0) {
                ant -> proxE = NULL;
            }
            /* Verifica se a entrada eh um item no meio da hashtable. */
            if (entradaE -> proxE != NULL && id != 0) {
                ant -> proxE = entradaE -> proxE;
            }
            /* Libera a entrada que foi deletada. */
            free(entradaE -> chaveE);
            free(entradaE);
            return;
        }
        ant = entradaE;
        entradaE = ant -> proxE;
        ++id;
    }
}
