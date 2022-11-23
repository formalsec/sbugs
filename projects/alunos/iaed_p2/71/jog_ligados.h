#ifndef JOG_LIGADOS_H
#define JOG_LIGADOS_H

#include "structs.h"

/* Inicializa a lista ligada com links de jogos*/
Lista_Jogos init_lista_jogos();

/* Acrescenta um novo link com o jogo dado no fim da fila */
void acrescenta_jogo(Lista_Jogos lista, Jogo jogo);

/* Remove um link com o jogo dado da lista ligada */
void rem_aux1(Lista_Jogos lista, Jogo jogo);

/* Da free() a lista ligada e aos seus elementos */
void destroi_jog_ligados(Lista_Jogos lista);

#endif