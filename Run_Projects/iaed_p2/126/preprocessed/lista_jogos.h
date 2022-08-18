#ifndef LISTAJOGOS_H
#define LISTAJOGOS_H

/* Estrutura de uma lista que guarda ponteiros jogos por ordem de introducao */
typedef struct lista {
    link_jg head; /* Ponteiro para o primeiro no' da lista */
    link_jg tail; /* Ponteiro para o ultimo no' da lista */
} *Lista_jg;


/*------------------------| Prototipos das funcoes |--------------------------------------*/

Lista_jg LSTjg_inicializa();
void LSTjg_adiciona(Lista_jg lista, Jogo jg);
void LSTjg_escreve(int NL, Lista_jg lista);
void LSTjg_apaga(Lista_jg lista, Jogo jogo);
void LSTjg_termina(Lista_jg lista);

#endif