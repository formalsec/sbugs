#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "main.h"

/* Inicia ambas as hash e a lista. Dependendo da letra escrita, executa uma 
determinada instrucao (os comandos possiveis estao listados em cada funcao) */
int main(){
    char comando;
    int linha = 1;
    linkeq *hash_equipas = HashEquipas_inic();
    item_hash_jg *hash_jogos = HashJogos_inic();
    lista lista_jogos = cria_lista_jogos();

    while ((comando = getchar()) != 'x'){
        switch(comando){
            case 'a':
                adiciona_jogo(hash_jogos, hash_equipas, lista_jogos, linha);
                linha++; /* sem erros */
                break;
            
            case 'A':
                adiciona_equipa(hash_equipas, linha);
                linha++; /* sem erros */
                break;
            
            case 'l':
                lista_todos_jogos(lista_jogos, linha);
                linha++; /* sem erros */
                break;
            
            case 'p':
                procura_jogo(hash_jogos,linha);
                linha++; /* sem erros */
                break;
            
            case 'P':
                procura_equipa(hash_equipas, linha);
                linha++; /* sem erros */
                break;

            case 'r':
                apaga_jogo(hash_jogos, hash_equipas, lista_jogos, linha);
                linha++; /* sem erros */
                break;

            case 's':
                altera_score(hash_jogos, hash_equipas, linha);
                linha++; /* sem erros*/
                break;

            case 'g':
                lista_melhores_equipas(hash_equipas, linha);
                linha++; /* sem erros */
                break;
            
            default:
                break;
        }
    }
    free_hashequipas(hash_equipas);
    free_listajogos(lista_jogos);
    free_hash_jogos(hash_jogos);

    return 0;

}

