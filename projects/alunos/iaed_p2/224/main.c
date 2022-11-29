#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "comandos.h"


/* Le os valores de stdin e executa cada comando chamando a respetiva funcao */
int main(){
    int NL=0;   /*Numero da linha de input*/         
    
    char input[MAX_INPUT]="\0", input_separado[MAX_PARAM][MAX_STR] = {"\0"};

    Jogo *jogo = NULL;          /*Inicializacao de um jogo*/
    Equipa *equipa = NULL;      /*Inicializacao de uma equipa*/

    Lista *lista_jogos = CriaLista();       /*Criacao da lista de jogos*/
    Lista *lista_equipas = CriaLista();     /*Criacao da lista de equipas*/

    Node **hash_table_jogos = CriaHashTable();      /*Criacao da hash table de jogos*/
    Node **hash_table_equipas = CriaHashTable();    /*Criacao da hash table de equipas*/  

    while(1){

        if(fgets(input, MAX_INPUT-1 , stdin) != NULL){
            NL++;

            switch(SeparaInput(input, input_separado)){

                case 'a':
                    jogo = CriaJogo(input_separado);
                    AdicionaNovoJogo(NL, jogo, hash_table_jogos, hash_table_equipas, lista_jogos);
                    break;

                case 'l':
                    ListaJogosIntroduzidos(NL, lista_jogos);
                    break;

                case 'p':
                    ProcuraJogo(NL, input_separado, hash_table_jogos);
                    break;

                case 'r':
                    ApagaJogo(NL, input_separado, hash_table_jogos, hash_table_equipas, lista_jogos);
                    break;

                case 's':
                    AlteraScore(NL, input_separado, hash_table_jogos, hash_table_equipas);
                    break;

                case 'A':
                    equipa = CriaEquipa(input_separado);
                    AdicionaNovaEquipa(NL, equipa, hash_table_equipas, lista_equipas);
                    break;

                case 'P':
                    ProcuraEquipa(NL, input_separado, hash_table_equipas);
                    break;

                case 'g':
                    OrdenaEquipas(NL, lista_equipas);
                    break;

                case 'x':
                    LimpezaGeral(hash_table_jogos, lista_jogos, DestroiJogo);
                    LimpezaGeral(hash_table_equipas, lista_equipas, DestroiEquipa);
                    return 0;
                    break;
            }
    
        }

    }
    return 0;
}