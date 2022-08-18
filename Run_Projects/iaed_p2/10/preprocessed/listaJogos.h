#ifndef _TABJOGO_
#define _TABJOGO_
#include "jogo.h"

typedef struct noJogo{
    pJogo ptJogo;
    struct noJogo * proximo;
    int ordem;
} * listaJogo;


/*cria um elemento da lista dos jogos*/
listaJogo novoJogoLista(pJogo novoJogo, int ordem);

/*adiciona um jogo a lista dos jogos*/
listaJogo adicionarNovoJogo(pJogo novoJogo, listaJogo * listaJogos, int ordem, int numINP);

/*procura um jogo numa lista de jogos*/
pJogo procurarJogoLista(listaJogo * listaJogos, char * nome);

/*apaga um jogo numa lista de jogos*/
void apagarJogoLista(listaJogo * listaJogos, char * nome, int numINP);

/*faz free a todos os elementos de uma lista de jogos*/
void libertarListaJogos(listaJogo * listaJogos);


#endif