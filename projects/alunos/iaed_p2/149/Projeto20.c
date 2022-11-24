#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "funcoes.h"


int main(){
    /*Inicia as variaveis todas, as hash tables e linked lsits*/
    hash_table_equipa * hash_table_equipa_p;
    hash_table_jogo * hash_table_jogo_p;
    char command;
    lista Equipa_lista;
    lista* Equipa_lista_pointer;
    lista2 Jogos_lista;
    lista2* Jogos_lista_pointer;
    int NL, indicador;
    Jogos_lista_pointer = &Jogos_lista;
    Equipa_lista_pointer = &Equipa_lista;
    Equipa_lista_pointer->head = NULL;
    Equipa_lista_pointer->last = NULL;
    Jogos_lista_pointer->head = NULL;
    Jogos_lista_pointer->last = NULL;
    NL = 1,indicador = 0;
    hash_table_equipa_p = init_hash_Equipa(TABLE_SIZE);
    hash_table_jogo_p = init_hash_jogos(TABLE_SIZE);
    while (indicador ==0) {
        command = getchar(); /*primeira letra e lida e comparada com as letras do comandos existentes*/
        switch (command){
            case 'A':
                executa_A(hash_table_equipa_p,Equipa_lista_pointer,NL);
                NL = NL +1;
                break;
            case 'P':
                executa_P(hash_table_equipa_p,NL);
                NL = NL +1;
                break;
            case 'a':
                executa_a(hash_table_equipa_p,hash_table_jogo_p,Jogos_lista_pointer,NL);
                NL = NL +1;
                break;
            case 'p':
                executa_p(hash_table_jogo_p,NL);
                NL = NL +1;
                break;
            case 'l':
                executa_l(Jogos_lista_pointer,NL);
                NL = NL +1;
                break;
            case 's':
                executa_s(hash_table_jogo_p,NL);
                NL = NL +1;
                break;
            case 'r':
                executa_r(hash_table_jogo_p,Jogos_lista_pointer,NL);
                NL = NL +1;
                break;
            case 'g':
                executa_g(Equipa_lista_pointer,NL);
                NL = NL +1;
                break;
            case 'x':
                liberta_espacos(Equipa_lista_pointer,Jogos_lista_pointer,hash_table_equipa_p,hash_table_jogo_p);
                indicador = 1;
                break;
        }
    }
    return EXIT_SUCCESS;
    
}