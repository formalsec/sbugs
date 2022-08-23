#include "hashtable.h"
#include "item.h"
#include "gestao_jogos.h"


int main(){
    int comando, contador = 0;
    /* reserva espaco na memoria para a lista de jogos */
    lista_jogo * lst_jogo = (lista_jogo*) malloc(sizeof(lista_jogo));
    /* inicializa a cabeca para a lista de equipas e reserva memoria para a hashtable de jogos e para a hashtable de equipas */
    Item * head_equipa = NULL, * hashtable_jogo[TAMANHO_TAB], * hashtable_equipa[TAMANHO_TAB];

    /* inicializa as posicoes das hashtables com valor NULL */
    init_hashtable(hashtable_jogo);
    init_hashtable(hashtable_equipa);

    lst_jogo->head = NULL;
    lst_jogo->last = NULL;

    /* deteta o comando inserido pelo utilizador, termina o programa caso input seja o caracter 'x' */
    while((comando = getchar()) != 'x'){
        if (comando != '\n'){
            contador++; /* conta o numero de linhas do input*/

            switch(comando){
                case 'a':
                    a_adicionaNovoJogo(lst_jogo, hashtable_jogo, hashtable_equipa, contador);
                    break;
                
                case 'A':
                    head_equipa = A_adicionaNovaEquipa(head_equipa, hashtable_equipa, contador);
                    break;

                case 'l':
                    l_listaTodosJogosPorOrdem(lst_jogo, contador);
                    break;
                
                case 'p':
                    p_procuraJogo(hashtable_jogo, contador);
                    break;

                case 'P':
                    P_procuraEquipa(hashtable_equipa, contador);
                    break;

                case 'r':
                    r_apagaJogo(lst_jogo, hashtable_jogo, hashtable_equipa, contador);
                    break;
                
                case 's':
                    s_alteraPontuacao(hashtable_jogo, hashtable_equipa, contador);
                    break;

                case 'g':
                    g_encontraEquipasMaisVitorias(head_equipa, contador);
                    break;
                
                default:
                    printf("Input invalido\n");
                    break;
            }
        }
    }    

    /* liberta na memoria os dados associados aos jogos e 'as equipas*/
    apaga_equipas(head_equipa);
    apaga_jogos(lst_jogo);
    
    return 0;
}

