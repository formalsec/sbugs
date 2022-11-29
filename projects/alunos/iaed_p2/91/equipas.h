#ifndef EQUIPAS_H
#define EQUIPAS_H

typedef struct {
    char *nome;
    int score;
} Equipa;

typedef struct {
    Equipa **equipas;
    int tamanho, capacidade;
} TabelaEquipas;

/* Cria a tabela das equipas */
TabelaEquipas *inicia_tabela_equipas(int capacidade);
/* Insere uma equioa na tabela */
void inserir_equipa(TabelaEquipas *tabela, Equipa *equipa);
/* Procura uma equipa por nome */
Equipa *procura_equipa(TabelaEquipas *tabela, char *nome);
/* Liberta a memoria associada */
void free_tabela_equipas(TabelaEquipas *tabela);

/* Ordena alfabeticamente um vetor de strings */
void ordena_equipas(char **equipas, int left, int right);

#endif
