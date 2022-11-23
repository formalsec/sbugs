#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"
#include "lista.h"
#include "hash_table_equipa.h"
#include "hash_table_jogo.h"

int main(void)
{
    /*Hash table para guardar ponteiros para jogos*/
    jogo *hash_table_jogo[HASH_SIZE];
    /*Hash table para guardar ponteiros para equipas*/
    equipa *hash_table_equipa[HASH_SIZE];
    /*Cabeca da lista para guardar jogos pela ordem de introducao*/
    node *head;

    equipa * aux_equipa;
    jogo * aux_jogo;
    node * aux_node;
    char Comando = LeCaracterInicial();

    int contador;
    contador = 1;

    /*Inicializacao das tabelas e lista*/
    init_hash_table_equipa(hash_table_equipa);
    init_hash_table_jogo(hash_table_jogo);
    head = NULL;

    while (Comando != 'x')
    {
        switch (Comando)
        {
        case 'a':
            aux_jogo = Comando_a(contador, hash_table_equipa, hash_table_jogo);
            if (aux_jogo != NULL) /*se o jogo existir*/
            {
                hash_table_jogo_insert(aux_jogo, hash_table_jogo);
                aux_node = lista_insert(aux_jogo, head);
                head = aux_node;
            }
            contador++;
            break;
        
        case 'A':
            aux_equipa = Comando_A(contador, hash_table_equipa);
            if (aux_equipa != NULL) /*se a equipa existir*/
            {
                aux_equipa->vitorias = 0;
                hash_table_equipa_insert(aux_equipa, hash_table_equipa);
            }
            contador++;
            break;

        case 'l':
            contador = Comando_l(contador, head);
            contador++;
            break;

        case 'p':
            Comando_p(contador, hash_table_jogo);
            contador++;
            break;

        case 'P':
            Comando_P(contador, hash_table_equipa);
            contador++;
            break;

        case 'r':
            aux_jogo = Comando_r(contador, hash_table_jogo, hash_table_equipa);
            if (aux_jogo != NULL)
            {
                hash_table_jogo_delete(aux_jogo->nome_jogo, hash_table_jogo);
                aux_node = lista_delete(aux_jogo->nome_jogo, head);
                head = aux_node;
            }
            contador++;
            break;

        case 's':
            aux_node = Comando_s(contador, hash_table_jogo, hash_table_equipa, head);
            head = aux_node;
            contador++;
            break;

        case 'g':
            contador = Comando_g(contador, hash_table_equipa);
            contador++;
            break;

        default:
            break;
        }
        Comando = LeCaracterInicial();
    }
    
    /*frees dos ponteiros criados*/
    free_equipas(hash_table_equipa);
    free_jogos(hash_table_jogo);
    free_listas(head);
    return 0;
}

