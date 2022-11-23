#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "equipa.h"
#include "jogo.h"
#include "listas.h"
#include "hashtables.h"
#include "comandos.h"

/* Le o primeiro caracter de cada linha e chama a funcao correspondente ao comando a executar */
int main() {
    char c;
    int nl = 0;
    lstEquipas lista_equipas = criar_lst_equipas();
    lstJogos lista_jogos = criar_lst_jogos();
    hashEquipas hash_equipas = criar_hash_equipas();
    hashJogos hash_jogos = criar_hash_jogos();

    /* Quando c == 'x' o programa termina */
    while((c = getchar()) != 'x') {
        switch (c) {
            case 'a':
                nl++;
                novo_jogo(lista_jogos, hash_jogos, hash_equipas, nl);
                break;
            case 'A':
                nl++;
                nova_equipa(lista_equipas, hash_equipas, nl);
                break;
            case 'l':
                nl++;
                listar_jogos(lista_jogos, nl);
                break;
            case 'p':
                nl++;
                procurar_jogo(hash_jogos, nl);
                break;
            case 'P':
                nl++;
                procurar_equipa(hash_equipas, nl);
                break;
            case 'r':
                nl++;
                apagar_jogo(lista_jogos, hash_jogos, nl);
                break;
            case 's':
                nl++;
                alterar_pontuacao(hash_jogos, nl);
                break;
            case 'g':
                nl++;
                mais_vitorias(lista_equipas, nl);
        }
    }
    
    /* No final liberta toda a memoria associada 'as listas, 'as hashtables, 'as equipas e aos jogos */
    terminar_prog(lista_jogos, lista_equipas, hash_jogos, hash_equipas);

    return 0;
}