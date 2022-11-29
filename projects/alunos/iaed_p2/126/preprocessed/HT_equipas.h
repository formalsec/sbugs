#ifndef HTEQUIPAS_H
#define HTEQUIPAS_H

/* Estrutura do no' de uma lista ligada que guarda ponteiros para equipas */
typedef struct node_eq {
    Equipa equipa; /* Ponteiro para a estrutura equipa */
    struct node_eq *prox; /* ponteiro para o proximo no' */
} *link_eq;

/* Estrutura de uma hashtable que guarda ponteiros para equipas */
typedef link_eq* HT_eq; /* Tabela com ponteiros para nos de listas ligadas com equipas */


/*------------------------| Prototipos das funcoes |--------------------------------------*/

HT_eq HTeq_inicializa(int max);
Equipa HTeq_procura(HT_eq equipas, char* nome, int max);
int hash(char *c, int max);
void HTeq_adiciona(HT_eq equipas, char* nome, int max);
void maximo_vitorias(HT_eq equipas, int* max_num, int max_eq);
void melhores_equipas(HT_eq equipas, Equipa *melhores, int max_v, int max_eq);
void HTeq_termina(HT_eq equipas, int max);


#endif