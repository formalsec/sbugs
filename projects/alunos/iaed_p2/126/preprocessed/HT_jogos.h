#ifndef HTJOGOS_H
#define HTJOGOS_H

/* Estrutura do no' de uma lista ligada que guarda ponteiros para jogos */
typedef struct node_jg {
    Jogo jogo; /* Ponteiro para a estrutura jogo */
    struct node_jg *prox; /* ponteiro para o proximo no' */
} *link_jg;

/* Estrutura de uma hashtable que guarda ponteiros para jogos */
typedef link_jg* HT_jg; /* Tabela com ponteiros para nos de listas ligadas com jogos */


/*------------------------| Prototipos das funcoes |--------------------------------------*/

HT_jg HTjg_inicializa(int max);
Jogo HTjg_procura(HT_jg jogos, char* nome, int max);
link_jg novo_node_jg(Jogo jogo, link_jg prox);
void HTjg_adiciona(HT_jg jogos, char* nome, Jogo jogo, int max);
void HTjg_apaga(HT_jg jogos, char* nome, Jogo jogo, int max);
link_jg apaga_jg_lista(link_jg head, Jogo jogo);
void HTjg_termina(HT_jg jogos, int max);


#endif