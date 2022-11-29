#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Funcoes_da_Main.h"

#define Valor_inicial 0
#define Primo_MAX  7727

/*Criacao de um sistema de gestao de uma base de dados de jogos de futebol amigaveis */

int main(){
    /* Inicializam das variaveis */
    char letrainicial; int contador = Valor_inicial; 
    int max_equipas = Primo_MAX; int n_equipas = Valor_inicial;p_equipa *tab_e;
    int max_jogos = Primo_MAX; int n_jogos = Valor_inicial;p_jogo *tab_j;
    link head; link tail; 
    head = NULL; tail = NULL;
    /* Inicializam das HashTables Equipa e Jogo */
    Equipainit(&max_equipas,max_equipas,&tab_e);
    Jogoinit(&max_jogos,max_jogos,&tab_j);
    while(Primo_MAX== Primo_MAX){
        letrainicial = getchar();
        if(letrainicial == 'A'){
            A(++contador,&max_equipas,&n_equipas,&tab_e);
        }
        if(letrainicial == 'P'){
            P(++contador,&max_equipas,&tab_e);
        }            
        if(letrainicial == 'a'){
            a(++contador,&max_jogos,&max_equipas,&n_jogos,&tab_j,&tab_e,&head,&tail);
        }
        if(letrainicial == 'p'){
            p(++contador,&max_jogos,&tab_j);
        }   
        if(letrainicial == 's'){
            s(++contador,&max_jogos,&tab_j);
        }
        if(letrainicial == 'l'){
            l(++contador,head);
        }
        if(letrainicial == 'r'){
            r(++contador,&max_jogos,&n_jogos,&tab_j,&head,&tail);
        }
        if(letrainicial =='g')
            g(++contador,n_equipas,max_equipas,tab_e);
        if(letrainicial == 'x'){
            liberta(max_equipas,tab_e,tab_j,head);
            break;
        }
    }
    
    
    return 0;
}
