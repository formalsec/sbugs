#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"
#include "jogo.h"

int main(){
    char comando;
    int * Nr_linha = can_fail_malloc(sizeof(int));
    inicioFimJogos * inicio_fim = can_fail_malloc(sizeof(inicioFimJogos));
    hash_table_equipa * hashTableEquipas = cria_hash_table_equipa();
    hash_table * hashTableJogos = cria_hash_table();
    inicio_fim->inicio = NULL; inicio_fim->fim = NULL; *Nr_linha = 1;

    while (1){ comando = getchar();
        switch(comando){
            case 'A' : 
                getchar(); 
                adiciona_equipa(hashTableEquipas, Nr_linha); 
                break;
            case 'a' :
                getchar();
                adiciona_jogo(hashTableJogos, Nr_linha, hashTableEquipas, inicio_fim);
                break;
            case 'l' :
                lista_todos(inicio_fim, Nr_linha); 
                break; 
            case 'p' :
                getchar();
                procura_jogo(hashTableJogos, Nr_linha);
                break;
            case 's' :
                getchar();
                altera_score(hashTableJogos, Nr_linha, hashTableEquipas);
                break;
            case 'P' :
                getchar();
                procura_equipa(hashTableEquipas, Nr_linha);
                break;
            case 'g' :
                getchar();
                maisGanhos(hashTableEquipas, Nr_linha); 
                break;
            case 'r' :
                getchar();
                remove_jogo(hashTableJogos, hashTableEquipas, inicio_fim, Nr_linha);
                break;  
            case 'x' :
                free(Nr_linha);
                free_hash_table(hashTableEquipas);
                free_hash_table_jogo(hashTableJogos);
                liberta_dupla(inicio_fim);
                return 0;
        } 
    }
    return 0;   
}





