#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "game.h"
#include "team.h"
#include "default.h"


int main(){
    char buffer[1024]; /*usado para obter nomes*/
    char t1[1024],t2[1024],s1[100],s2[100]; /*usado para obter as caracteristicas dos jogos t-team  s-score*/
    game_list game_list_aux, primeiro_jogo;
    game_link game_link_aux, game_link_aux2;    /*variaveis auxiliares*/
    link *teams;
    game_link *games;   
    game_list games_sorted;     /* lista de equipas, jogos e ponteiros para jogos ordenados*/
    int i, contador = 0;    /*i-var aux, contador - para contar o nr do comando*/
    char comando;           
    teams = can_fail_malloc(M*sizeof(link));
    games = can_fail_malloc(M*sizeof(game_link));
    games_sorted = can_fail_malloc(sizeof(struct game_pointers)); 
    primeiro_jogo = games_sorted;   
    games_sorted->game = NULL;
    for (i = 0; i < M; i++){
        teams[i] = NULL;        /* inicialisa as variaveis auxiliares*/
        games[i] = NULL;        /*nao foi posto fora do main devido a um erro*/
    }                           
    comando = getchar();        /*obtem comando*/
    while(comando != 'x'){
        switch(comando){
            case 'A':{  /*adiciona equipa*/
                contador++;
                scanf(" %[^\n]", buffer);       /*obtem o nome da equipa*/
                if(existing_team(teams, buffer)){   /*se existir*/
                    printf("%d Equipa existente.\n", contador);
                    break;
                }
                add_team(teams,buffer); /*se nao existir*/
                break;
            }
            case 'P':{ /*procura equipa*/
                i = 0;
                contador++;
                scanf(" %[^\n]", buffer);   /*obtem o nome*/
                i = find(teams, buffer, contador);          /* ve se existe a equipa e se existir escreve tudo menos o nr de vitorias*/
                if(i == 1){break;}      /*se nao existir para*/
                game_list_aux = games_sorted;
                while(game_list_aux->game != NULL){ /*se existir conta as vitorias*/
                    if(!strcmp(game_list_aux->game->team1, buffer)){ /*ve se a equipa 1 e a desejada*/
                        if(game_list_aux->game->score1 > game_list_aux->game->score2){/*ve se o seu score foi maior que o do oponente*/
                            i++;
                        }}
                    if(!strcmp(game_list_aux->game->team2, buffer)){    /*faz o mesmo com a equipa 2*/
                        if(game_list_aux->game->score2 > game_list_aux->game->score1){
                            i++;
                        }}
                    game_list_aux = game_list_aux->next;    /*passa ao proximo jogo*/
                }
                printf("%d\n", i);
                break;
            }
            case 'a':{  /*adiciona jogo*/
                contador++;
                scanf(" %[^:]", buffer);
                getchar();
                scanf("%[^:]", t1);
                getchar();
                scanf("%[^:]", t2);
                getchar();
                scanf("%[^:]", s1);
                getchar();
                scanf("%s", s2);  /*obtem as informacoes necessarias*/
                getchar();
                if(existing_game(games, buffer)){   /*verifica se o jogo existe no sistema*/
                    printf("%d Jogo existente.\n", contador);
                    break;
                }
                if(!(existing_team(teams,t1) && existing_team(teams,t2))){  /*verifica se as equipas existem no sistema*/
                    printf("%d Equipa inexistente.\n", contador);
                    break;
                }
                add_game(games ,buffer ,t1 ,t2 ,s1 ,s2, &games_sorted);/* adiciona o jogo ao sistema*/
                
                /*printf("%s\n",(games_sorted)->game->name);*/ 
                /*linha de codigo que representa os jogos no sistema(usada com uma hashtable menor)*/
                break;
            }
            case 'l':{  /*lista jogos*/
                contador++;
                game_list_aux = primeiro_jogo;          /*pega no termo antes do primeiro jogo*/
                while(game_list_aux->prev != NULL){     /* enquanto exitirem mais jogos*/
                    game_list_aux = game_list_aux->prev;    /* pegamos no proximo e escrevemos o que e pedido*/
                    printf("%d %s %s %s %d %d\n",contador ,game_list_aux->game->name, game_list_aux->game->team1,game_list_aux->game->team2, game_list_aux->game->score1, game_list_aux->game->score2);
                }
                break;
            }
            case 'p':{
                contador++;
                scanf(" %[^\n]", buffer);   /*obtem o nome do jogo*/
                if(!existing_game(games, buffer)){ /*verifica se o jogo existe*/
                    printf("%d Jogo inexistente.\n",contador);
                    break;
                }
                game_link_aux = get_game(games,buffer); /*pega no jogo e escreve o pedido*/
                printf("%d %s %s %s %d %d\n",contador ,game_link_aux->name, game_link_aux->team1,game_link_aux->team2, game_link_aux->score1, game_link_aux->score2);
                break;
            }
            case 's':{
                contador++;
                scanf(" %[^:]", buffer);
                getchar();
                scanf(" %[^:]", s1);
                getchar();
                scanf(" %s", s2);   /*obtem o nome do jogo e os scores novos*/
                if(!existing_game(games, buffer)){  /*verifica se os jogos existem*/
                    printf("%d Jogo inexistente.\n",contador);
                    break;
                }
                game_link_aux = get_game(games,buffer); /*obtem o jogo e muda os scores do jogo para a conversao em int das strings*/
                game_link_aux->score1 = atoi(s1);   
                game_link_aux->score2 = atoi(s2);
                break;  
            }
            case 'r':{
                contador++;
                scanf(" %[^\n]", buffer);   /*obtem o nome do jogo*/
                if(!existing_game(games, buffer)){  /*verifica se existe*/
                    printf("%d Jogo inexistente.\n",contador);
                    break;
                }
                game_list_aux = games_sorted;   
                while(strcmp(game_list_aux->game->name, buffer)){   /*obtem o jogo na lista ordenada*/
                    game_list_aux = game_list_aux->next;
                }

                game_link_aux = games[hashU(buffer)]; 
                if(game_link_aux->next == NULL){        /*verifica se o unico jogo da lista e o que queremos eliminar*/
                    game_link_aux = game_link_aux->next;
                    free_game_node(games[hashU(buffer)]);
                    games[hashU(buffer)] = game_link_aux;   /*se for elimina assim*/
                }
                else{           /*se nao for procuramos assim: */
                    if(!strcmp(game_link_aux->name,buffer)){    /*se for o  primeiro*/
                        games[hashU(buffer)] = game_link_aux->next;
                        free_game_node(game_link_aux);      /*eliminamos o primeiro e dizemos que o segundo elemento passa a ser o primeiro*/
                    }
                    else{   /*se nao for o primeiro vamos procurar o elemento antes do que pretendemos eliminar*/
                    while(strcmp(game_link_aux->next->name, buffer)){
                        game_link_aux = game_link_aux->next;
                    }
                    game_link_aux2 = game_link_aux->next;   /*ligamos o anterior ao a seguir ao elemento eliminado*/
                    game_link_aux->next = game_link_aux->next->next;
                    free_game_node(game_link_aux2);     /*eliminamos o elemento*/
                    }
                }
                if(game_list_aux->prev == NULL){    /*se o elemento foi o ultimo a ser adicionado a lista ordenada*/
                    games_sorted = games_sorted->next;  
                    games_sorted->prev = NULL;      /*dizemos que o segundo termo passa a ser o primeiro e que o anterior a esse e NULL*/
                    free(game_list_aux);        /*damos free ao termo*/
                }
                else{       /*se nao for ligamos o anterior ao seguinte ao que pretendemos eliminar*/
                    game_list_aux->prev->next = game_list_aux->next;
                    game_list_aux->next->prev = game_list_aux->prev;
                    free(game_list_aux);        /*libertamos o termo*/

                }
                break;
            }

        }
        comando = getchar();    /*obtemos o proximo comando*/
    }
    free_list(teams);
    free_game_list(games);
    free(games);
    free_ord(games_sorted);
    free(teams);        /*libertamos as listas usadas*/
    return 0;
}