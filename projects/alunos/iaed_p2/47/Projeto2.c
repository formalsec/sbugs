#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashGame.h"
#include "hashTeam.h"
#include "doublelinked.h"
#define MAXNOME 1024




void add_Game(gamelink *headgame,teamlink *headteam,GameLinkedList list,int NL);   /*comando a*/
void add_Team(teamlink *head, int NL, int *teamcounter);                            /*comando A*/
void print_Game(gamelink *head,int NL);                                             /*comando p*/
void delete_Game(gamelink *head,int NL,GameLinkedList list);                        /*comando r*/
void print_Team(teamlink *head, int NL);                                            /*comando P*/
void edit_Score(gamelink *headgame,int NL);                                         /*comando s*/
void print_Games(GameLinkedList list, int NL);                                      /*comando l*/
void best_Teams(teamlink *head,int NL,int *teamcounter);                            /*comando g*/
int compare(TEAM i,TEAM j);                                                         /*funcao auxiliar que compara os nomes de 2 equipas usando strcmp*/






/*main*/ 
int main(){
    int NL=1;                                       /*identificador do input*/
    int teamcounter=0;                              /*contador de equipas presentes no sistema*/
    gamelink *headgame= HASHinit_game(N);           /*inicializa a Hashtable com N entradas*/
    teamlink *headteam= HASHinit_team(M);           /*inicializa a Hashtable com M entradas*/
    GameLinkedList listGames=list_init();           /*inicializa a Lista duplamente ligada */
    char comando = ' ';    /*variavel que ira definir o comando a ser executado*/
    while (comando != 'x') 
    {
        scanf("%c",&comando);    /*le o comando introduzido*/
        switch (comando)
        {
        case 'a':
            add_Game(headgame,headteam,listGames,NL);
            break;
        
        case 'A':
            add_Team(headteam,NL,&teamcounter);
            break;
        
        case 'r':
            delete_Game(headgame,NL,listGames);
            break;
        case 'p':
            print_Game(headgame,NL);
            break;
           
        case 'P':
            print_Team(headteam,NL);          
            break;
        case 's':
            edit_Score(headgame,NL);
            break;
       case 'l':
            print_Games(listGames,NL);
            break;  
        case 'g':
            best_Teams(headteam,NL,&teamcounter);
            break;
        case 'x':                                   /*Elimina as Estruturas criadas para o sistema,libertando memoria*/
            destroy_hash_game(headgame);  
            destroy_hash_team(headteam);
            destroy_list(listGames);
            break;
        }
        NL++; /*incrementa a linha de input*/
    }
    return 0; 
}    

void add_Game(gamelink *headgame,teamlink *headteam,GameLinkedList list,int NL){ /*comando a*/
    char name[MAXNOME],team1[MAXNOME],team2[MAXNOME];
    int away,home;
    GAME i;
    TEAM A,B,w;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",name,team1,team2,&home,&away);
    getchar();
    A = search_team(headteam,team1);
    B = search_team(headteam,team2);
    i = search_game(headgame,name);
    
    if (i) printf("%d Jogo existente.\n",NL);           
    else if (!A || !B) printf("%d Equipa inexistente.\n",NL);
    else
    {
        i=newGame(name,A,B,home,away);
        insert_game(headgame,i);
        append(list,i);
        w=winner(i);
        if(w) w->wongames++;
    }

}   
void add_Team(teamlink *head,int NL,int *teamcounter){ /*comando A*/
    char name[MAXNOME]; 
    TEAM i;
    scanf(" %[^:\n]",name);
    getchar();
    i=search_team(head,name);
    if (i!=NULL) printf("%d Equipa existente.\n",NL);
    else
    {
        insert_team(head,newTeam(name)); 
        (*teamcounter)++;
    }
    
    
    
}
void print_Game(gamelink *head,int NL){ /*comando p*/
    char name[MAXNOME];
    GAME i;
    scanf(" %[^:\n]",name);
    getchar();
    i = search_game(head,name);
    if (i==NULL) printf("%d Jogo inexistente.\n",NL);
    else
    {
        printf("%d ",NL);
        seeGame(i);
    }
    
}
void print_Team(teamlink *head,int NL){ /*comando P*/
    char name[MAXNOME];
    TEAM i;
    scanf(" %[^:\n]",name);
    getchar();
    i=search_team(head,name);
    if (!i) printf("%d Equipa inexistente.\n",NL);
    else
    {
        printf("%d ",NL);
        seeTeam(i);
        printf(" %d\n",i->wongames);
    }

}
void delete_Game(gamelink *head,int NL,GameLinkedList list){ /*comando r*/
    char name[MAXNOME];
    GAME i;
    TEAM t;
    scanf(" %[^:\n]",name);
    getchar();
    i=search_game(head,name);
    if (!i) printf("%d Jogo inexistente.\n",NL);
    else 
    {
        t=winner(i);
        if (t) t->wongames--;
        remove_Game_list(list,name);
        delete_game(head,name);
        
    }
}

void edit_Score(gamelink *headgame,int NL){       /*comando s*/
    char name[MAXNOME];
    int home,away;
    GAME i;
    TEAM old,new;
    scanf(" %[^:\n]:%d:%d",name,&home,&away);
    getchar();
    i=search_game(headgame,name);
    if(!i)
    {
        printf("%d Jogo inexistente.\n",NL);
        return;
    }
    old=winner(i);
    i->scoreHome=home;
    i->scoreAway=away;
    new=winner(i);
    if(old) old->wongames--;
    if(new) new->wongames++;
}

void print_Games(GameLinkedList list,int NL){ /*comando l*/
    Link current;
    getchar();
    
    for (current=list->head; current != NULL; current = current->next)
    {
        printf("%d ",NL);
        seeGame(current->Game);
    }
}

int cmp_TEAM(const void *v, const void *w) /*funcao auxiliar que compara o nome de duas equipas*/
{ 
    const TEAM t1 = *(const TEAM*)v;
    const TEAM t2 = *(const TEAM*)w;
    return strcmp((t1)->Teamname , (t2)->Teamname);
}


void best_Teams(teamlink *head,int NL,int *teamcounter){ /*comando g*/
    TEAM  *TEAMARRAY;
    int max=-1,n=0,nmax=0,index=0,i;
    teamlink aux;

    getchar();
    if ((*teamcounter) == 0) return;
    
    for (i = 0; i < N && n < (*teamcounter); i++)           /*obtem o numero de jogos ganhos maximo no sistema*/
    {
        for(aux=head[i];aux;aux=aux->next)
        {
            
            if (max < aux->TEAM->wongames)
                {
                    max=aux->TEAM->wongames;
                }
            n++;
            
        }
    }

    for ( i = 0; i < N ; i++)                                   /*obtem o numero de equipas com esse numero de jogos ganhos*/
    {
        for(aux=head[i];aux;aux=aux->next)
        {
            if (aux->TEAM->wongames == max)
            {
                nmax++;
            }
        }
        
        
    }
    TEAMARRAY=can_fail_malloc(sizeof(TEAM)*nmax);                    /*aloca memoria para um vetor de equipas onde serao introduzidas as equipas com o maior numero de jogos ganhos*/
    for ( i = 0; i < N; i++)
    {
         for(aux=head[i];aux;aux=aux->next)
        {
            if (aux->TEAM->wongames == max)
            {
                TEAMARRAY[index]=aux->TEAM;                     /*insere nesse vetor as equipas com mais vitorias*/
                index++;
            }
            
        }
        
    }
    qsort(TEAMARRAY,nmax,sizeof(TEAM),cmp_TEAM);                    /*sort vetor*/
    printf("%d Melhores %d\n",NL,max);
    for ( i = 0; i < nmax; i++)
    {
        printf("%d * ",NL);                                 /*escreve no terminal as equipas presentes em TEAMARRAY*/
        seeTeam(TEAMARRAY[i]);
        printf("\n");
    }
    free(TEAMARRAY);                            /*liberta a memoria alocada para o vetor*/

    
    
    
    
    
    

}

