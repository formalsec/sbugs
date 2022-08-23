#include "principal.h"
#include "codigoAux.h"
#include "jogo.h"
#include "listaJogo.h"
#include "hashtableJogo.h"
#include "equipa.h"
#include "listaEquipa.h"
#include "hashtableEquipa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    listaJogo**   headsJogos = NULL; 
    int           M_J = 1021;
    listaJogo*    listaDeJogos = NULL;

    listaEquipa** headsEquipas =  NULL; 
    int           M_E = 1021;
    listaEquipa*  listaDeEquipas = NULL;

    char comando[MAXCAR];
    int  NL = 1;          /* NL eh o numero da linha do comando lido */
    int* pNL = &NL;       /* pNL eh o endereco do numero da linha do comando lido */

    /* Inicializa a hash table de jogos e a lista ligada de jogos */
    headsJogos = criaHashTableJogo(M_J);
    listaDeJogos = criaListaJogo();

    /* Inicializa a hash table de equipas e a lista ligada de equipas */
    headsEquipas = criaHashTableEquipa(M_E);
    listaDeEquipas = criaListaEquipa();

    /* Enquanto nao chega ao fim do ficheiro obtem um comando, analisa-o e executa-o */
    while (scanf("%[^\n]\n", comando) && strcmp(comando, "x") != 0 && strcmp(comando, "X") != 0) {
        analisaComando(comando, headsJogos, headsEquipas, listaDeJogos, listaDeEquipas, M_J, M_E, pNL);
        
        /* Sempre que le um comando incremento o numero da linha do comando */
        *pNL += 1;
    }

    /* Liberta a memoria alocada para a hash table, para a lista ligada e para cada jogo */
    freeHashTableJogo(headsJogos, M_J);
    freeListaMaisJogos(listaDeJogos);

    /* Liberta a memoria alocada para a hash table, para a lista ligada e para cada equipa */
    freeHashTableEquipa(headsEquipas, M_E);
    freeListaMaisEquipas(listaDeEquipas);
    
    return 0;
}
