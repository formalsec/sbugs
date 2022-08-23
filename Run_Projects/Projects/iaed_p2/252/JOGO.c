#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGO.h" 
#include "EQUIPA.h"

/*Funcao do comando 'l' que percorre a lista dos jogos e imprime os seus valores*/
void ListaJogos(game_list* l, int NL) 
{
    Jogo* temp = l->head;

    while (temp != NULL) 
    {
        printf("%d ", NL);
        printf("%s ",temp->nome);
        printf("%s ",temp->equipa1);
        printf("%s ",temp->equipa2);
        printf("%d ",temp->score1);
        printf("%d\n",temp->score2);

        temp = temp->next; /* segue para o proximo ate chegar a um valor NULL*/
    }
    return; 
 }

/*Funcao que utiliza a hashtable da lista dos jogos para encontrar um jogo a partir do seu nome*/
Jogo* FindGame(game_list* l, char buffer[DIM_STR]) 
{
    Jogo* toFind;
    int numHash = string_hash(buffer) % HASHSIZE;

    for (toFind = *(l->hashtable + numHash); toFind && strcmp(toFind->nome, buffer) != 0; toFind = toFind->collision);
    
    return toFind;
}

/*Funcao que serve para pesquisar um jogo e dar print aos seus valores*/
void SearchGame(game_list* l,int NL) 
{
    Jogo* toFind;
    char buffer[DIM_STR];
    scanf("%[^:\n]:",buffer);

    if ((toFind = FindGame(l, buffer))) /*caso em que encontra jogo*/
        {
            printf("%d ", NL);
            printf("%s ",toFind->nome);
            printf("%s ",toFind->equipa1);
            printf("%s ",toFind->equipa2);
            printf("%d ",toFind->score1);
            printf("%d\n",toFind->score2);
            return;
        }

    printf("%d Jogo inexistente.\n", NL); 

}

/* Funcao relativa ao comando 'r' que a partir de um nome de um jogo
 ela vai procurar esse jogo e remove-lo da lista de jogos */
game_list* apagaJogo(team_list* tl,game_list* l, int NL) 
{
    int numHash;
    char buffer[DIM_STR];
    Jogo* toDelete, *JogoColisao;

    toDelete = l->head;

    scanf("%[^:\n]:",buffer); /* le nome do jogo*/

    if ((toDelete = FindGame(l, buffer))) { /* procura jogo e mete em toDelete*/
        if(toDelete->score1 > toDelete->score2){ /* retira a vitoria ao vencedor desse jogo*/
            FindTeam(tl, toDelete->equipa1)->vitorias--;
        }   
        
        if(toDelete->score2 > toDelete->score1){
            FindTeam(tl, toDelete->equipa2)->vitorias--;
        }

        if (toDelete->next != NULL) {
            
            toDelete->next->previous = toDelete->previous;
        }

        if (toDelete->previous != NULL) {
        
            toDelete->previous->next = toDelete->next;
        } 

        if (toDelete == l->head) 
        {
            l->head = toDelete->next;
        }

        if (toDelete == l->last) 
        {
            l->last = toDelete->previous;
        }

        numHash = string_hash(buffer) % HASHSIZE;
        JogoColisao = *(l->hashtable + numHash);

        if (strcmp(JogoColisao->nome, buffer) == 0) 
        {
            *(l->hashtable + numHash) = JogoColisao->collision;
        } else 
        {
            for(;strcmp(JogoColisao->collision->nome, buffer) != 0;JogoColisao=JogoColisao->collision);
            
            JogoColisao->collision = JogoColisao->collision->collision;
        }

        free(toDelete->nome);
        free(toDelete->equipa1);
        free(toDelete->equipa2);
        
        free(toDelete);
        
        return l;
    }
    
    printf("%d Jogo inexistente.\n", NL);

    return l;
}


/* Funcao que inicializa comando 's' e le o nome do jogo.
 Retorna a lista de jogos com os scores do respetivo jogo atualizados.*/
game_list* comando_s(team_list* tl,game_list* l, int NL)
{
    char buffer[DIM_STR];
    scanf("%[^:\n]:",buffer);

    return ChangeScores(tl,l,buffer,NL);
}

/* Funcao que altera os scores de um jogo numa lista, a partir de scores lidos. */
game_list* ChangeScores(team_list* tl,game_list* l,char* buffer, int NL) 
{
    Jogo* toChange;
    int sc1,sc2;
    

    if ((toChange = FindGame(l, buffer))) /*procura jogo na lista*/
        {
            scanf("%d:%d",&sc1,&sc2); /* le os valores dos novos scores*/
            if(toChange->score1 > toChange->score2){  /* compara scores anteriores para gerir o numero de vitoria de cada uma das equipas*/
                 
                 if(sc2 > sc1){
                    FindTeam(tl, toChange->equipa1)->vitorias--;
                    FindTeam(tl, toChange->equipa2)->vitorias++;
                 }

                 if(sc1 == sc2){
                    FindTeam(tl, toChange->equipa1)->vitorias--;
                 }
            }

            if(toChange->score2 > toChange->score1){
                 
                 if(sc1 > sc2){
                    FindTeam(tl, toChange->equipa2)->vitorias--;
                    FindTeam(tl, toChange->equipa1)->vitorias++;
                 }

                 if(sc1 == sc2){
                    FindTeam(tl, toChange->equipa2)->vitorias--;
                 }
            }

            if(toChange->score2 == toChange->score1){
                 
                 if(sc1 > sc2){
                    FindTeam(tl, toChange->equipa1)->vitorias++;
                 }

                 if(sc2 > sc1){
                    FindTeam(tl, toChange->equipa2)->vitorias++;
                 }
            }

            toChange->score1 = sc1;
            toChange->score2 = sc2;

            return l;
        }

    printf("%d Jogo inexistente.\n", NL);

    return l;
}
