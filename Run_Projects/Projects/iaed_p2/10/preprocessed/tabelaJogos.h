#ifndef _LISTAJOGOS_
#define _LISTAJOGOS_
#include "listaJogos.h"

typedef struct entradasJogo{
    listaJogo * entradaLista;
    int tamanho;
    int numJogos;
} * pTabela;


/*funcao que retorna um valor entre 0 e m para uma string*/
int hash(char * nome);

/*cria uma tabela de jogos*/
pTabela novaTabJogos(int m);


/*adiciona um jogo a tabela de jogos*/
void adicionarJogoTabela(pTabela tabelaJogos, pJogo jogo, int ordem, int numINP);

/*procura um jogo na tabela de jogos*/
pJogo procurarJogoTabela(pTabela tabelaJogos, char * nome);

/*apaga um jogo da tabela de jogos*/
void apagarJogoTabela(pTabela tabelaJogos, char * nome, int numINP);

/*altera a pontuacao de um jogo*/
void alteraPontuacao(pTabela tabelaJogos, char * nome, int pont1, int pont2, int numINP);

/*lista as equipas por ordem de insercao*/
void listarJogos(pTabela tabelaJogos, int ordem, int numINP);

/*faz free a todos os elementos da tabela*/
void libertarTabela(pTabela tabelaJogos);

#endif

