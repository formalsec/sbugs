#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HighFunction.h"


int main(){
	int programa, nl = 0, golos_equipa1, golos_equipa2;
	char input, nome_equipa1[SIZE_CHAR], nome_equipa2[SIZE_CHAR], nome_jogo[SIZE_CHAR];
	TableJogos* table_jogos = STinitJogo();
    TableEquipas* table_equipas = STinitEquipa();
    linkEquipa equipas = NULL;
	linkJogo jogos = NULL;
    programa = 1;
	    while(programa == 1)
        {
            input = getchar();
            getchar();
            switch(input) 
            {
                case 'a':
                    nl++;
                    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, nome_equipa1, nome_equipa2, &golos_equipa1, &golos_equipa2);
                    addJogo(table_jogos, jogos, nome_jogo, nome_equipa1, nome_equipa2, golos_equipa1, golos_equipa2);
                    printf("%d", nl);
                    break;
                case 'A':
                    nl++;
                    scanf("%[^:\n]", nome_equipa1);
					addEquipa(table_equipas, equipas, nome_equipa1);
                    printf("%d", nl);
                    break;
                case 'l':
                    nl++;
                    printf("%d", nl);
                    break;
                case 'p':
                    nl++;
                    scanf("%[^:\n]", nome_jogo);
                    findJogo(table_jogos, jogos);
                    printf("%d", nl);
                    break;
                case 'P':
                    nl++;
                    scanf("%[^:\n]", nome_equipa1);
                    findEquipa(table_equipas, equipas);
                    printf("%d", nl);
                    break;
                case 'r':
                    nl++;
                    scanf("%[^:\n]", nome_jogo);
                    removeJogo(table_jogos, jogos);
                    printf("%d", nl);
                    break;
                case 's':
                    nl++;
                    scanf("%[^:\n]:%d:%d", nome_jogo, &golos_equipa1, &golos_equipa2);
                    changeScore(table_jogos, jogos, golos_equipa1, golos_equipa2);
                    printf("%d", nl);
                    break;
                case 'g':
                    nl++;
                    printf("%d", nl);
                    break;
                case 'x':
                    programa = 0;
            }
        }
	return 0;
}
