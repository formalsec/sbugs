#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGO.h" 
#include "EQUIPA.h"
#include "NOVO_JOGO.h"

/* Funcao que inicializa o comando 'a' e le o nome do jogo,da equipa 1 e da equipa 2.
 Retorna a lista de jogos atualizada.*/
game_list* comando_a(game_list* l, team_list* tl, int NL)
{
    char nome_jogo[DIM_STR],equipa1[DIM_STR],equipa2[DIM_STR];
    scanf("%[^:\n]:",nome_jogo);
    scanf("%[^:\n]:",equipa1);
    scanf("%[^:\n]:",equipa2);

    return gameAdd(nome_jogo,equipa1,equipa2,l,tl,NL);

}

/* Funcao que serve para procurar casos em que nao sera possivel adicionar novo Jogo*/ 
int gameErrors(char *nome_jogo,char *equipa1,char *equipa2,game_list* l, team_list* tl, int NL)
{
    if (FindGame(l, nome_jogo)){
        printf("%d Jogo existente.\n", NL);
        
        return -1;
    }

    if (!FindTeam(tl, equipa1)){
        printf("%d Equipa inexistente.\n", NL);
        
        return -1;
    }    

    if (!FindTeam(tl, equipa2)){
        printf("%d Equipa inexistente.\n", NL);
        
        return -1;
    }

    return 0;
}

/* Funcao que vai criar novo jogo*/
game_list* gameAdd(char *nome_jogo,char *equipa1,char *equipa2,game_list* l, team_list* tl, int NL) 
{   
    
    int sc1,sc2;
    Jogo* novo_jogo = (Jogo *) can_fail_malloc(sizeof(Jogo));
    
    if (gameErrors(nome_jogo,equipa1,equipa2,l,tl,NL) == -1){
        free(novo_jogo);
        return l;
    }
    
    /*guarda nome do jogo*/
    novo_jogo->nome = (char *) can_fail_malloc((strlen(nome_jogo) + 1)  * sizeof(char));
    strcpy(novo_jogo->nome, nome_jogo);

    /*guarda nome da equipa1*/
    novo_jogo->equipa1 = (char *) can_fail_malloc((strlen(equipa1) + 1)  * sizeof(char));
    strcpy(novo_jogo->equipa1, equipa1);
    

    /*guarda nome da equipa2*/
    novo_jogo->equipa2 = (char *) can_fail_malloc((strlen(equipa2) + 1)  * sizeof(char));
    strcpy(novo_jogo->equipa2, equipa2);
    
    /*guarda valores dos scores*/
    scanf("%d:%d",&sc1,&sc2);
    novo_jogo->score1 = sc1;
    novo_jogo->score2 = sc2;
    
    /* adiciona vitoria a equipa que venceu o jogo*/
    if (sc1 > sc2){
        FindTeam(tl, equipa1)->vitorias++;
    }

    if (sc2 > sc1){
        FindTeam(tl, equipa2)->vitorias++;
    }
    
    HashJogo(l,novo_jogo);
    
    return l;
}