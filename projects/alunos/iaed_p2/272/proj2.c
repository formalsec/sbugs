#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "equipa.h"
#include "jogo.h"
#include <stdlib.h>

/* Funcao main deste projeto */
int main() {
    /* Variaveis que pretendemos usar */
    int comandos_total = 1;
    struct Equipas equipas;
    struct Jogos jogos;
    int n;
    int correndo = 1;
    
    /* Inicializacao das variavies */
    for (n = 0; n < EQUIPA_GAVETAS; n++) {
        equipas.gavetas[n] = NULL;
    }
    equipas.ordem = NULL;
    equipas.nequipas = 0;
    for (n = 0; n < EQUIPA_GAVETAS; n++) {
        jogos.gavetas[n] = NULL;
    }
    jogos.njogos = 0;
    jogos.ordem = NULL;
    
    while (correndo) {

        /* Leitura do valor dado como input */
        int c = getchar();
        /* Switch case onde colocamos todas as funcoes que pretendemos usar */
        switch (c) {
        case 'a':
            adiciona_jogo(&jogos, &equipas, comandos_total);
            comandos_total++;
            break;
        
        case 'p':
            procura_jogo(&jogos, comandos_total);
            comandos_total++;
            break;
        
        case 'A':
            adiciona_equipa(&equipas, comandos_total);
            comandos_total++;
            break;
        
        case 'P':
            procura_equipa(&equipas, comandos_total);
            comandos_total++;
            break;
        
        case 'l':
            lista_jogos(&jogos, comandos_total);
            comandos_total++;
            break;
        
        case 'r':
            apaga_jogos(&jogos, comandos_total);
            comandos_total++;
            break;
        
        case 's':
            muda_jogos(&jogos, comandos_total);
            comandos_total++;
            break;
        
        case 'g':
            melhores_equipas(&equipas, comandos_total);
            comandos_total++;
            break;
        
        case 'x':
            correndo = 0;
            break;

        }
       
    }    

    /* Libertamos a memoria utilizada */
    for(n = 0; n < equipas.nequipas; n++) {
        free(equipas.ordem[n]->nome);
        free(equipas.ordem[n]);
    }
    free(equipas.ordem);
    for(n = 0; n < jogos.njogos; n++) {
        if (jogos.ordem[n]== NULL){
            continue;
        }
        free(jogos.ordem[n]->nome);
        free(jogos.ordem[n]);
    }
    free(jogos.ordem);
    
    return 0;
}
