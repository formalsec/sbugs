#include "_features.h"
#include "HashTable.h"
#include "lists.h"

#define TAM 1024

int main(){
    char command;
    char nome[TAM], equipa1[TAM], equipa2[TAM];
    int score1,score2;
    int contador=0;
    static list *ant; /*guarda o ultimo elemento da lista de jogos*/
    list *jogos;
   
    jogos = create("INI"); /*inicia a lista com o primeiro elemento
                            'INI' para ajudar no debug*/
    ant = jogos;
    
    /*inicializacao das hash tables*/
    Ginit();
    Tinit();

    do{
        scanf("%c",&command);
        /* chama as rotinas para o tratamento do comando  */
        switch(command){
            case 'a':
                contador++;
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&score1,&score2);
                ant = f_addgame(nome,equipa1,equipa2,score1,score2,contador,ant);
                break;
            case 'l':
                contador++;
                print_games(jogos, contador);
                break;
            case 'A':
                contador++;
                scanf(" %[^:\n]",equipa1);
                add_team(equipa1, contador);
                break;
            case 'p':
                contador++;
                scanf(" %[^:\n]",nome);
                show_game(nome, contador);
                break;
            case 'P':
                contador++;
                scanf(" %[^:\n]",equipa1);
                search_team(equipa1, contador);
                break;
            case 'r':
                contador++;
                scanf(" %[^:\n]",nome);
                if(strcmp(nome,ant->str)==0){
                    ant=ant->ant;
                }
                delete_game(nome, jogos, contador);
                break;
            case 's':{
                contador++;
                scanf(" %[^:\n]:%d:%d",nome,&score1,&score2);
                change_score(nome, score1, score2, contador);
                break;
            }
            case 'g':
                contador++;
                best_teams(contador);
                break;
        }
    }while(command!='x');
    
    Gfree_hash();
    Tfree_hash();
    free_list(jogos);


    return 0;
}
