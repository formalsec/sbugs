#include "tabelaJogos.h"

int hash(char * nome){
    int h, a, m;
    h = 0; 
    a = 127; 
    m = 10000;
    for( ; *nome != '\0'; nome++){
        h = (a * h + *nome) % m;
    }   
    return h;
}

pTabela novaTabJogos(int m){
    int i;
    pTabela novaTabela = (pTabela) malloc (sizeof(struct entradasJogo));
    novaTabela->numJogos = 0;
    novaTabela->tamanho = m;
    novaTabela->entradaLista = (listaJogo *) malloc(sizeof (listaJogo) * m);
    for(i = 0; i < m; i++){
        (novaTabela->entradaLista)[i] = NULL;
    }
    return novaTabela;
}

void adicionarJogoTabela(pTabela tabelaJogos, pJogo jogo, int ordem, int numINP){
    if (jogo != NULL){
        int h;
        /*Entrada da tabela que aponta para uma lista onde o jogo se encontra*/
        h = hash(jogo->nome);
        tabelaJogos->entradaLista[h] = adicionarNovoJogo(jogo, (tabelaJogos->entradaLista + h), ordem, numINP);
    }   
}

pJogo procurarJogoTabela(pTabela tabelaJogos, char * nome){
    int h;
    pJogo jogo;
    /*Entrada da tabela que aponta para uma lista onde o jogo se encontra*/
    h = hash(nome);
    jogo = procurarJogoLista(tabelaJogos->entradaLista + h, nome);
    return jogo;
}

void apagarJogoTabela(pTabela tabelaJogos, char * nome, int numINP){
    int h;
    /*Entrada da tabela que aponta para uma lista onde o jogo se encontra*/
    h = hash(nome);
    apagarJogoLista(tabelaJogos->entradaLista + h, nome, numINP);    
}

void alteraPontuacao(pTabela tabelaJogos, char * nome, int pont1, int pont2, int numINP){
    pJogo jogo;
    jogo = procurarJogoTabela(tabelaJogos, nome);
    if (jogo == NULL){
        printf("%d Jogo inexistente.\n", numINP);
        return;
    }
    retiraVitoria(jogo);
    jogo->pont1 = pont1;
    jogo->pont2 = pont2;
    adicionaVitoria(jogo);
}

void listarJogos(pTabela tabelaJogos, int ordem, int numINP){
    int i, k;
    listaJogo * entradas;
    entradas = (listaJogo * ) malloc (sizeof(listaJogo) * tabelaJogos->tamanho);
    k = 0;
    /*O primeiro elemento da lista de cada entrada da tabela*/
    for (i = 0; i < tabelaJogos->tamanho; i++){
        entradas[i] = tabelaJogos->entradaLista[i];
    }
    while (k <= ordem){
        for (i = 0; i < tabelaJogos->tamanho; i++){
            /*Procura o elemento que foi inserido primeiro indicado pelo valor ordem*/
            if (entradas[i] != NULL && entradas[i]->ordem <= k){
                mostrarJogo(entradas[i]->ptJogo, numINP);
                entradas[i] = entradas[i]->proximo;
            }
        }
        k++;
    }  
    free(entradas);
}

void libertarTabela(pTabela tabelaJogos){
    int i;
    for (i = 0;  i < tabelaJogos->tamanho; i++){
        libertarListaJogos(tabelaJogos->entradaLista + i);
    }
    free(tabelaJogos->entradaLista);
    free(tabelaJogos);
}