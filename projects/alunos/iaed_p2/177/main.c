#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "sistema.h"

int main(){
    /*lista onde sao guardados os jogos por ordem de insercao*/
    lista *lista_jogos=inicializa_lista();
    /*hash table onde sao guardados os jogos*/
    jogo jogos=NULL;
    /*hash table onde sao guardados os equipas e o
    numero de vitorias de cada equipa*/
    sistema equipas=NULL;
    int n_jogos_ganhos, score1, score2;
    int nl=0;
    char nome[DIM];
    char equipa1[DIM];
    char equipa2[DIM];
    char comando;
    jogos=inicializa_jogo(jogos, 31);
    equipas=inicializa_sistema(equipas, 31);
    while ((comando=getchar())!='x'){
        switch (comando){
            case 'a':
            nl+=1;
            scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
            if (pertence_jogo(jogos, nome)==1){
                printf("%d Jogo existente.\n", nl);
            }
            else if (pertence_equipa(equipas, equipa1)==0  ||  pertence_equipa(equipas, equipa2)==0){
                printf("%d Equipa inexistente.\n", nl);
            }
            else{
                jogos=insere_jogo(jogos, lista_jogos, nome, equipa1, equipa2, score1, score2);
                equipas=insere_vitoria(equipas, equipa1, equipa2, score1, score2);
            }
            break;

            case 'l':
            nl+=1;
            print(lista_jogos, nl);
            break;

            case 'p':
            nl+=1;
            scanf(" %[^:\n]", nome);
            if (pertence_jogo(jogos, nome)==0){
                printf("%d Jogo inexistente.\n", nl);
            }
            else{
                print_jogo(jogos, nome, nl);
            }
            break;

            case 'r':
            nl+=1;
            scanf(" %[^:\n]", nome);
            if (pertence_jogo(jogos, nome)==0){
                printf("%d Jogo inexistente.\n", nl);
            }
            else{
                equipas=elimina_vitoria(equipas, jogos, nome);
                jogos=elimina_jogo(jogos, nome);
            }
            break;

            case 's':
            nl+=1;
            scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
            if (pertence_jogo(jogos, nome)==0){
                printf("%d Jogo inexistente.\n", nl);
            }
            else{
                equipas=atualiza_vitoria(equipas, jogos, nome, score1, score2);
                jogos=altera_score(jogos, nome, score1, score2);
            }
            break;


            case 'A':
            nl+=1;
            scanf(" %[^:\n]", nome);
            if (pertence_equipa(equipas, nome)==1){
                printf("%d Equipa existente.\n", nl);
            }
            else{
                equipas=insere_equipa(equipas, nome, 0);
            }
            break;

            case 'P':
            nl+=1;
            scanf(" %[^:\n]", nome);
            if (pertence_equipa(equipas, nome)==0){
                printf("%d Equipa inexistente.\n", nl);
            }
            else{
                n_jogos_ganhos=jogos_ganhos(equipas, nome);
                printf("%d %s %d\n", nl, nome, n_jogos_ganhos);
            }
            break;

            case 'g':
            nl+=1;
            tabela(equipas, nl);

        }
    }
    equipas=destroi_sistema(equipas);
    jogos=destroi_jogo(jogos);
    free(lista_jogos);
    return 0;
}


