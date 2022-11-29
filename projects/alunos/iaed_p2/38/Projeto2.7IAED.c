#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NOME 1024           /*Numero Maximo de caracteres no nome de um jogo ou equipa*/
#define MAX_INPUT 3085          /*Numero Maximo de caracteres no input geral dos comandos*/


float nl=1;                     /*contador do numero de comandos*/
int n_jogos=0;                  /*contador do numero de jogos*/
int n_equipas=0;                /*contador do numero de equipas*/

typedef struct Equipa{          
    int id;                     /*Indice da equipa no vetor global das equipas*/
    char *nome_equipa;          /*Nome da equipa*/
    int n_jogos_ganhos;         /*Numero de jogos ganhos pela equipa*/
} equipa;


typedef struct Jogo{
    char *nome;                 /*Nome do jogo*/
    equipa equipa1;             /*Primeira equipa participante*/
    equipa equipa2;             /*Segunda equipa participante*/
    int golos1;                 /*Golos marcados pela primeira equipa*/
    int golos2;                 /*Golos marcados pela segunda equipa*/
} jogo;


jogo *jogos;                    /*Tabela com todos os jogos do sistema*/
equipa *equipas;                /*Tabela com todas as equipas do sistema*/



/*aloca uma posicao de memoria na stack para um jogo e outra para uma equipa*/
void inicializa_sistema(){
    jogos=can_fail_malloc(sizeof(jogo));
    equipas=can_fail_malloc(sizeof(equipa));
}


/*liberta todas as posicoes de memoria alocadas dinamicamente ao longo do programa*/
void termina_sistema(){
    int i;

    for(i=0;i<n_jogos;i++)
        free(jogos[i].nome);
    free(jogos);

    for(i=0;i<n_equipas;i++)
        free(equipas[i].nome_equipa);
    free(equipas);
}


/*le o input do correspendente comando*/
void le_input(char *input){
    scanf(" %[^\n]",input);
}


/*verifica se o jogo com o nome recebido como argumento ja existe ou nao*/
int verifica_jogo(char *nome,int imprime){
    int i;

    for(i=0;i<n_jogos;i++){
        if(!(strcmp(jogos[i].nome,nome)))
            return i+1;            /*Retorna o indice+1 do jogo se existe*/
    }

    if(imprime)          /*Imprime mensagem de erro se o jogo nao existir e variavel imprime esteja a 1*/
        printf("%.0f Jogo inexistente.\n",nl);
    return 0;                      /*Retorna 0 se nao existe*/
}


/*verifica se o equipa com o nome recebido como argumento ja existe ou nao*/
int verifica_equipa(char *nome,int imprime){
    int i;

    for(i=0;i<n_equipas;i++){
        if(!(strcmp(equipas[i].nome_equipa,nome)))
            return i+1;             /*Retorna o indice+1 da equipa se existe*/
    }

    if(imprime)         /*Imprime mensagem de erro se a equipa nao existir e variavel imprime esteja a 1*/
        printf("%.0f Equipa inexistente.\n",nl);
    return 0;                       /*Retorna 0 se nao existe*/
}


/*adiciona um novo jogo ao sistema*/
void cria_jogo(){
    char input[MAX_INPUT],name[MAX_NOME],nome_equipa1[MAX_NOME],nome_equipa2[MAX_NOME];
    char *palavra;
    int score1,score2,i=0,j;
    
    le_input(input);

    palavra=strtok(input,":");
    while(palavra!=NULL){
        if(i==0)
            strcpy(name,palavra);
        else if(i==1)
            strcpy(nome_equipa1,palavra);
        else if(i==2)
            strcpy(nome_equipa2,palavra);
        else if(i==3)
            score1=atoi(palavra);
        else
            score2=atoi(palavra);
        palavra=strtok(NULL,":");
        i++;
    }
    
    i=verifica_equipa(nome_equipa1,0);
    j=verifica_equipa(nome_equipa2,0);
       
    if(verifica_jogo(name,0))
        printf("%.0f Jogo existente.\n",nl);
    else if(i && j){
        jogos=can_fail_realloc(jogos,sizeof(jogo)*(n_jogos+1));
        jogos[n_jogos].nome=can_fail_malloc(sizeof(char)*(strlen(name)+1));
        strcpy(jogos[n_jogos].nome,name);
        jogos[n_jogos].equipa1=equipas[i-1];
        jogos[n_jogos].equipa2=equipas[j-1];
        jogos[n_jogos].golos1=score1;
        jogos[n_jogos].golos2=score2;
        
        if(score1>score2)
            equipas[i-1].n_jogos_ganhos++;
        else if(score2>score1)
            equipas[j-1].n_jogos_ganhos++;

        n_jogos++;
    }
    else
        printf("%.0f Equipa inexistente.\n",nl);  
}


/*Imprime todos os jogos do sistema*/
void lista_jogos(){
    int i;

    for(i=0;i<n_jogos;i++)
        printf("%.0f %s %s %s %d %d\n",nl,jogos[i].nome,jogos[i].equipa1.nome_equipa,jogos[i].equipa2.nome_equipa,jogos[i].golos1,jogos[i].golos2);
}


/*Imprime um determinado jogo pertencente ao sistema*/
void lista_jogo(){
    int i;
    char name[MAX_NOME];
    
    le_input(name);
    
    i=verifica_jogo(name,1);
    if(i)
        printf("%.0f %s %s %s %d %d\n",nl,jogos[i-1].nome,jogos[i-1].equipa1.nome_equipa,jogos[i-1].equipa2.nome_equipa,jogos[i-1].golos1,jogos[i-1].golos2);
}


/*Apaga um determinado jogo do sistema*/
void apaga_jogo(){
    int i,j;
    char name[MAX_NOME];
    
    le_input(name);
    
    j=verifica_jogo(name,1);
    if(j){
        if(jogos[j-1].golos1>jogos[j-1].golos2)
            equipas[jogos[j-1].equipa1.id].n_jogos_ganhos--;
        else if(jogos[j-1].golos1<jogos[j-1].golos2)
            equipas[jogos[j-1].equipa2.id].n_jogos_ganhos--;

        for(i=j-1;i<n_jogos-1;i++)
            jogos[i]=jogos[i+1];
        
        n_jogos--; 
    }
}


/*Altera o resultado de um determinado jogo*/
void altera_resultado(){
    int i,score1,score2;
    char name[MAX_NOME],input[MAX_INPUT];
    char *palavra;

    le_input(input);
    palavra=strtok(input,":");
    strcpy(name,palavra);
    palavra=strtok(NULL,":");
    score1=atoi(palavra);
    palavra=strtok(NULL,":");
    score2=atoi(palavra);

    i=verifica_jogo(name,1);
    if(i){
        if((score1>=score2)&&(jogos[i-1].golos2>=jogos[i-1].golos1)){
            if(jogos[i-1].golos2>jogos[i-1].golos1)
                equipas[jogos[i-1].equipa2.id].n_jogos_ganhos--;
            if(score1>score2)
                equipas[jogos[i-1].equipa1.id].n_jogos_ganhos++;
        }
        else if((score2>=score1)&&(jogos[i-1].golos1>=jogos[i-1].golos2)){
            if(jogos[i-1].golos1>jogos[i-1].golos2)
                equipas[jogos[i-1].equipa1.id].n_jogos_ganhos--;
            if(score2>score1)
                equipas[jogos[i-1].equipa2.id].n_jogos_ganhos++;
        }
        
        jogos[i-1].golos1=score1;
        jogos[i-1].golos2=score2;
    }
}


/*Adiciona uma nova equipa ao sistema*/
void cria_equipa(){
    char team_name[MAX_NOME];

    le_input(team_name);

    if(verifica_equipa(team_name,0))
        printf("%.0f Equipa existente.\n",nl);
    else{
        equipas=can_fail_realloc(equipas,sizeof(equipa)*(n_equipas+1));

        equipas[n_equipas].id=n_equipas;
        equipas[n_equipas].nome_equipa=can_fail_malloc(sizeof(char)*(strlen(team_name)+1));
        strcpy(equipas[n_equipas].nome_equipa,team_name);
        equipas[n_equipas].n_jogos_ganhos=0;

        n_equipas++;
    }
}


/*Imprime uma determinada equipa pertencente ao sistema*/
void lista_equipa(){
    int i;
    char team_name[MAX_NOME];
    
    le_input(team_name);
    
    i=verifica_equipa(team_name,1);
    if(i)
        printf("%.0f %s %d\n",nl,equipas[i-1].nome_equipa,equipas[i-1].n_jogos_ganhos);
}


/*Imprime as equipas com o maior numero de jogos ganhos em ordem alfabetica*/
void lista_melhores_equipas(){
    int i,maior=0,cont=0,finish;
    equipa *melhores_equipas;
    equipa aux;

    for(i=0;i<n_equipas;i++){
        if(equipas[i].n_jogos_ganhos>maior)
            maior=equipas[i].n_jogos_ganhos;
    }

    melhores_equipas=can_fail_malloc(sizeof(equipa));
    for(i=0;i<n_equipas;i++){
        if(!i)
            printf("%.0f Melhores %d\n",nl,maior);
        if(equipas[i].n_jogos_ganhos==maior){
            cont++;
            melhores_equipas=can_fail_realloc(melhores_equipas,sizeof(equipa)*cont);
            melhores_equipas[cont-1]=equipas[i]; 
        }
    }

    while(1){
        finish=1;
        for(i=0;i<cont-1;i++){
            if(strcmp(melhores_equipas[i].nome_equipa,melhores_equipas[i+1].nome_equipa)>0){
                aux=melhores_equipas[i];
                melhores_equipas[i]=melhores_equipas[i+1];
                melhores_equipas[i+1]=aux;
                finish=0;
            }
        }
        if(finish)
            break;
    }

    for(i=0;i<cont;i++)
        printf("%.0f * %s\n",nl,melhores_equipas[i].nome_equipa);
    
    free(melhores_equipas);
}


/*Obtem o comando a ser executado e chama a funcao correspondente*/
int main(){
    char comando;

    inicializa_sistema();
    
    while((comando = getchar()) && comando!='x'){
        if(comando=='a')
            cria_jogo();
        else if(comando=='l')
            lista_jogos();
        else if(comando=='p')
            lista_jogo();
        else if(comando=='r')
            apaga_jogo();
        else if(comando=='s')
            altera_resultado();
        else if(comando=='A')
            cria_equipa();
        else if(comando=='P')
            lista_equipa();
        else if(comando=='g')
            lista_melhores_equipas();
        nl=nl+0.5;
    }

    termina_sistema();
    
    return 0;
}

