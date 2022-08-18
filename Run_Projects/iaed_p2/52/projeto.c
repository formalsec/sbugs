#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturasAlgoritmos.h"
#include "comandos.h"

int main(){
    /* c - Caracter para onde e lido a letra do comando
       m's - tamanho total das estruturas  (numero primo > 1000 escolhido ao acaso) */ 
    int c,m = 1163,NL = 1;
    /* Inicializacao das estruturas de dados que irao guardar os jogos e as equipas */
    tabela *jogos,*equipas;
    lista *jogosL,*equipasL;
    jogos = novaTabela(m);
    jogosL = novaLista(m);
    equipas = novaTabela(m);
    equipasL = novaLista(m);
    /* Leitura de comandos acaba com x ou com EOF */
    while((c = getchar()) != EOF && c != 'x'){
        switch(c){
            case('a'):
                a(jogos,equipas,NL,jogosL);
                NL++;
                break;
            case('A'):
                A(equipas,NL,equipasL);
                NL++;
                break;
            case('l'):
                l(jogosL,NL);
                NL++;
                break;
            case('p'):
                p(jogos,NL);
                NL++;
                break;
            case('P'):
                P(equipas,NL);
                NL++;
                break;
            case('r'):
                r(jogos,equipas,NL);
                NL++;
                break;
            case('s'):
                s(jogos,equipas,NL);
                NL++;
                break;
            case('g'):
                g(equipasL,NL);
                NL++;
                break;
        }
    } /*quando o programa acaba destruo todas as estruturas utilizadas*/
    destroiTabela(jogos);
    destroiTabela(equipas);
    libLista(jogosL);
    libLista(equipasL);
    return 0;
}
