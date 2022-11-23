#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

/*Liberta a memoria da lista criada para o comando l*/
void freeList(link head){
    link aux1, aux2;
    if (!head) return;
	
	for (aux1 = head, aux2 = head->next; aux1; aux2 = aux1->next, aux1 = aux2){
        /*free(aux1->j);*/
        free(aux1);
    }

}

/*Cria e devolve um apontador para o novo jogo criado*/
link caseaAux(char name[1024],equipa team1,equipa team2,int num1,int num2){
    link temp = can_fail_malloc(sizeof(struct node));

    temp->j = novoJogo(name,team1,team2,num1,num2);
    return temp;

}

/*Altera o resultado de um jogo*/
int caseSAux(char auxString[1024],int auxNum1,int auxNum2,link *heads){
    jogo j;
    int out=0;


    j=Jsearch(heads,auxString);
/*Decrementa as vitorias na estrutura da equipa que tinha ganho o jogo*/
    if(j!=NULL){
        if(j->score1 > j->score2){
            j->equipa1->wins--;
        }
        else if(j->score1 < j->score2){
            j->equipa2->wins--;
        }

        j->score1=auxNum1;
        j->score2=auxNum2;
        out=1;
/*Incrementa as vitorias na estrutura da equipa que ganhou o jogo*/
        if(j->score1 > j->score2){
            j->equipa1->wins++;
        }
        else if(j->score1 < j->score2){
            j->equipa2->wins++;
        }

    }
    return out;
}


void processInput(){

  /*Variaveis auxliares*/
  int variavel=0,countOut=0,k,cond,auxNum1,auxNum2;
  char name[1024];
  char team[1024];
  char auxString[1024];
  link headList = NULL;
  link auxList = NULL;
  link tailList = NULL;

  equipa team1;
  equipa team2;

  link* head = Jinit(1001);
  Elink* top = Einit(1001);

  while(variavel<10){
    /*Variaveis auxiliares voltam ao valor inicial*/
    char token='\0';
    char s[1];
    strcpy(name,"\0");
    strcpy(team,"\0");
    strcpy(auxString,"\0");
    
    k=0;cond=0;auxNum1=0;auxNum2=0;
    /*obtem o comando*/
    scanf( "%s", s);
    token=s[0];
    /*countOut tem o numero da linha do input*/
    countOut++;


    switch (token) 
    {
        
        case 'a':
        /*Adiciona um jogo a base de dados*/
            scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",name,team,auxString,
            &auxNum1,&auxNum2);
        /*Verifica se ja existe um jogo como mesmo nome*/  
            if(Jsearch(head,name)){
                printf("%d Jogo existente.\n",countOut);
                break;
            }
        /*Verifica se ja existem as equipas a participar no jogo*/
            team1 = Esearch(top,team);
            if(!team1){
                printf("%d Equipa inexistente.\n",countOut);
                break;
            }
            team2 = Esearch(top,auxString);
            if(!team2){
                printf("%d Equipa inexistente.\n",countOut);
                break;
            }
        /*Se alguma das condicoes falhar, nenhum jogo se adiciona*/
            
        /*A lista que tem como cabeca HeadList servira para o comando l
            Caso nao exista uma head esta apontara para o jogo criado*/
            if(headList==NULL){
                headList = can_fail_malloc(sizeof(struct node));
                headList->j = novoJogo(name,team1,team2,auxNum1,auxNum2);
                Jinsert(head,headList->j);
                tailList = headList;
            }
        /*Caso exista uma HeadList, o jogo sera colocado na ultima posicao*/
            else{
                tailList->next = caseaAux(name,team1,team2,auxNum1,auxNum2);
                Jinsert(head,tailList->next->j);
                tailList=tailList->next;
            }
        /*A existencia de uma tail permite maior velocidade na colocacao de
            um novo jogo no fim da lista*/
            break;

        case 'l':
            if(headList==NULL){
                break;
            }
            /*Percorre todos os jogos e faz print do jogo
            No caso do jogo ter sido apagado mas a lista nao estar no fim,
                passa-se para a posicao seguinte da lista*/
            auxList=headList;
            while(auxList!=NULL){
                if((auxList->j->nome)!=NULL){
                    printf("%d ",countOut);
                    printJogo(auxList->j);
                }
                auxList=auxList->next;
            }
            break;
            
        case 'p':
        /*Procura um jogo na base de dados e da print do mesmo, caso ele exista*/
            scanf(" %[^:\n]",auxString);
            if(Jsearch(head,auxString)){
                printf("%d ",countOut);
                printJogo(Jsearch(head,auxString));
            }
            else{
                printf("%d Jogo inexistente.\n",countOut);
            }
            break;


        case 'r':
        /*Apaga um jogo da base de dados, caso ele exista*/
            scanf(" %[^:\n]",auxString);
            if(Jsearch(head,auxString)){
                Jdelete(head,auxString);
            }
            else{
                printf("%d Jogo inexistente.\n",countOut);
            }

            break;

        case 's':
        /*Altera, com recurso a uma funcao auxiliar o resultado de um jogo,
            caso ele exista*/
            scanf(" %[^:\n]:%d:%d",auxString,&auxNum1,&auxNum2);
            cond = caseSAux(auxString,auxNum1,auxNum2,head);
            if(cond==0){
                printf("%d Jogo inexistente.\n",countOut);
            }
   
            break;


        case 'A':
        /*Adiciona uma equipa a base de dados*/
            scanf(" %[^:\n]",auxString);
        /*Caso a equipa ja exista na base de dados,nao e adicionada*/
            if(Esearch(top,auxString)){
                printf("%d Equipa existente.\n",countOut);
            }
            else{
                Einsert(top, novaEquipa(auxString));
            }
            break;

        case 'P':
        /*Recebe o nome de uma equipa e da print da mesma, com o numero de jogos
            ganhos*/
            scanf(" %[^:\n]",auxString);
            if(Esearch(top,auxString)){
                k = getWins(top,auxString);
                printf("%d %s %d\n",countOut,auxString,k);
            }
            else{
                printf("%d Equipa inexistente.\n",countOut);
            }
            break;

        case 'g':
            /*Encontra as equipas com maior numero de vitorias*/
            getMostWins(top, countOut);
            break;

        case 'x': 

            /*Comando final, termina o programa*/
            variavel=100;
            break;
    }
    getchar();



  } 
  /*Libertam toda a memoria alocada no programa*/
  JdestroyHash(head);
  EdestroyHash(top);
  freeList(headList);
}






int main()
{
    /*Vai processar o input*/
    processInput();

    return 0;
}