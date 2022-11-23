#ifndef EQUIPA_H
#define EQUIPA_H

#define TAMANHO_TABELA 2000

/* Criacao do tipo da Equipa. */
typedef struct {
    char *nome;
    int vitorias;
} Equipa;

/* Criacao do tipo da entrada da hashtable de equipas. */
typedef struct entradaE_t {
    char *chaveE;
    Equipa *equipa;
    struct entradaE_t *proxE;
} entradaE_t;

/* Criacao do tipo de hashtable. */
typedef struct {
    entradaE_t **entradas;
} htE_t;

/* Funcao que cria uma equipa. */
Equipa *novaEquipa(char* nome);
/* Funcao que libera a memoria alocada por uma equipa. */
void liberarEquipa(Equipa *equipa);
/* Funcao que cria uma entrada da hashtable. */
entradaE_t *criarEntrada_htE(char *chaveE, Equipa *equipa);
/* Funcao que cria uma hashtable. */
htE_t *criar_htE(void);
/* Funcao que cria a chave baseado em uma chave. */
int hashE(char *chaveE);
/* Funcao que apropria uma entrada a hashtable. */
void apropriar_htE(htE_t *hashtable, char *chaveE, Equipa *equipa);
/* Funcao que retorna uma equipe que eh compativel com uma chave chaveE. */
Equipa *obter_htE(htE_t *hashtable, char *chaveE);
/* Funcao que apaga uma equipa da hashtable. */
void htE_del(htE_t *hashtable, char *chaveE);

#endif
