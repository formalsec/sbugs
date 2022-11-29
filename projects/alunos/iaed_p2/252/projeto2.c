#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EQUIPA.h"
#include "JOGO.h"
#include "NOVO_JOGO.h"
#include "AUX.h"
#include "func_g.h"
#define DIM_STR 1024



int main(){
    char cmd;
    int NL = 0;
    int num_equipas = 0;
    char nome_equipa[DIM_STR];
    
    /*cria lista de jogos e de equipas*/
    team_list* lista_equipas;
    game_list* lista_jogos;

    /* inicializa listas*/
    lista_equipas = AlocaEquipas();
    lista_jogos = AlocaJogos();

	while(1){
        
		cmd = getchar(); /* obtem comando*/
		switch(cmd){
			case 'a':
                NL++;
                getchar();
                lista_jogos = comando_a(lista_jogos,lista_equipas, NL);

				break;
            
            case 'A':
                NL++;
                num_equipas++;
                getchar();
                scanf("%[^:\n]:",nome_equipa);
                if (FindTeam(lista_equipas, nome_equipa)) 
                {
                    printf("%d Equipa existente.\n", NL);
                    num_equipas--;
                    break;
                }
                lista_equipas = teamAdd(lista_equipas,nome_equipa);

                break;


            
            case 'l':
                NL++;
                getchar();
                ListaJogos(lista_jogos,NL);
                break;

            case 'p':
                NL++;
                getchar();
                
                SearchGame(lista_jogos, NL);
                break;
        
            case 'P':
                NL++;
                getchar();
                
                comando_P(lista_equipas, NL);
                break;
            
            case 'r':
                NL++;
                getchar();
                lista_jogos = apagaJogo(lista_equipas,lista_jogos, NL);
                break;
            
            case 's':
                NL++;
                getchar();
                comando_s(lista_equipas,lista_jogos, NL);
                break;
            
            case 'g':
                NL++;
                getchar();
                ordenaEquipas(lista_equipas,num_equipas,NL);
                break;
            
			case 'x':
                freeList(lista_equipas);
                freeGameList(lista_jogos);
				return 0;
        }

	}
	return 0;
}