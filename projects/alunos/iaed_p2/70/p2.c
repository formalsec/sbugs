#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include"lista.h"
/*Numero maximo de caracteres no nomes das equipas
    e dos jogos*/
#define Max 1024
/* Numero utilizado para criar a hash tables dos 
    jogos e das equipas*/
#define M 29
/* lista_jogo: uma lista com a informacoes do jogos
    hash_game: uma hashtable com endereco dos jogos
    game: uma jogo
    equipas: hashtable com informacoes das equipas
    orde/ord1: tabela com as equipas com mais pontos
    equ/equ2: representa uma equipa
    jog: nome de uma jogo
    eq/eq2: nome de uma equipa
    nl: numero da linha
    sc1\sc2: score do jogos exceto na 'g' onde
        sc1 representa a pontuacao maxima e sc2
        o numero de equipas com essa pontuacao*/ 
int main(){
    l_jogo *lista_jogo;
    hash_jogo **hash_game;
    jogo *game;
    equipa **equipas,**orde,**ord1,*equ,*equ2;
    char jog[Max],eq1[Max],eq2[Max],c;
    int sc1,sc2,nl=1,m=M;
    lista_jogo=(l_jogo*) can_fail_malloc(sizeof(l_jogo));
    lista_jogo=cria_list_jogo(lista_jogo);
    hash_game = (hash_jogo**) can_fail_malloc((m *sizeof(hash_jogo)));
    hash_game = init(hash_game,m);
    equipas = (equipa**) can_fail_malloc((m *sizeof(equipa)));
    equipas = init_eq(equipas,m);
    c=getchar();
    while (c!='x')
    {
        switch (c)
        {
            /* Insere uma equipa*/
            case('a'):

                c=getchar();
                scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",jog,eq1,eq2,&sc1,&sc2);
                if (encontra_jogo(hash_game,jog,m)!=NULL)
                    printf("%d Jogo existente.\n",nl);
                else if ((equ=encontra_equipa(equipas,eq1,m))==NULL ||
                         ((equ2=encontra_equipa(equipas,eq2,m))==NULL))
                    printf("%d Equipa inexistente.\n",nl);
                else {
                    add_jogo(lista_jogo,jog,equ,equ2,sc1,sc2);
                    insere_jogo(hash_game,jog,lista_jogo->last,m);
                    if (sc1>sc2)
                        equ->i++;
                    else if (sc2>sc1)
                        equ2->i++;
                    
                }

                break;

            /* Lista todos os jogos pela ordem em que foram introduzidos.*/
             case('l'):
                print(lista_jogo,nl);
                break;

            /*Procura um jogo.*/
            case ('p'):
                c=getchar();
                scanf("%[^:\n]",jog);
                if((game=(encontra_jogo(hash_game,jog,m)))==NULL)
                    printf("%d Jogo inexistente.\n",nl);
                else
                     printf("%d %s %s %s %d %d\n",nl,game->n_jogo,
                            game->equipa1->nome,
                            game->equipa2->nome,game->sc1,game->sc2);

                break;
            
            /*Apaga um jogo.*/
            case ('r'):
                c=getchar();
                scanf("%[^:\n]",jog);
                remo_jog(hash_game,jog,lista_jogo,m,nl);
                break;
            
            /*Altera a pontuacao (_score_) de um jogo.*/
            case ('s'):
                c=getchar();
                scanf("%[^:\n]:%d:%d",jog,&sc1,&sc2);
                if((game=(encontra_jogo(hash_game,jog,m)))==NULL){
                    printf("%d Jogo inexistente.\n",nl);
                }
                else{
                    if (game->sc1 > game->sc2 && sc1<sc2){
                        game->equipa1->i--;
                        game->equipa2->i++;
                    }
                    else if (game->sc1 < game->sc2 && sc1>sc2)
                    {
                        game->equipa1->i++;
                        game->equipa2->i--;
                    }
                    else if (game->sc1 == game->sc2 && sc1>sc2){
                        game->equipa1->i++;
                    }
                    else if (game->sc1 == game->sc2 && sc1<sc2){
                        game->equipa2->i++;
                    }
                    else if (game->sc1 > game->sc2 && sc1==sc2){
                        game->equipa1->i--;
                    }
                    else if (game->sc1 < game->sc2 && sc1==sc2){
                        game->equipa2->i--;
                    }
                    game->sc1=sc1;
                    game->sc2=sc2;
                }
                break;

            /*Adiciona uma nova equipa.*/
            case('A'):
                c=getchar();
                scanf("%[^:\n]",eq1);
                if (encontra_equipa(equipas,eq1,m)==NULL)
                    insere_equipa(equipas,eq1,m);
                else
                    printf("%d Equipa existente.\n",nl);
                break;
            
            /*Procura uma equipa.*/
            case('P'):
                c=getchar();
                scanf("%[^:\n]",eq1);
                if ((equ=encontra_equipa(equipas,eq1,m))!=NULL)
                    printf("%d %s %d\n",nl,eq1,equ->i);
                else
                    printf("%d Equipa inexistente.\n",nl);
                
                break;
            
            /*Encontra as equipas que venceram mais jogos*/
            case('g'):
                sc2=0;
                sc1=0;
                sc1=encontr_melhor(equipas,m,sc1,&sc2);
                if (sc2!=0){
                    orde=(equipa**)can_fail_malloc(sc2*sizeof(equipa));
                    ord1=orde;
                    proc(equipas,orde,sc1,m,sc2);
                    ordena_lista(ord1,0,(sc2-1));
                    printf("%d Melhores %d\n",nl,sc1);
                    for (sc1=0;sc1<sc2;sc1++)
                        printf("%d * %s\n",nl,ord1[sc1]->nome);
                    free(ord1);
                        
                    }
                break;
        }

        c=getchar();
        c=getchar();
        nl++;
    }
    end(hash_game,m);
    end_q(equipas,m);
    free(lista_jogo);
    return 0;
}