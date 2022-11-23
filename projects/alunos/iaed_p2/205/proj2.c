#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include "equipa.h"
#include "list_jogo.h"
#include "list_equipa.h"




/*
| __a__ | adiciona um novo jogo |
| __l__ | Lista todos os jogos pela ordem em que foram introduzidos |
| __A__ | adiciona uma nova equipa |
| __s__ | altera a pontuacao de um jogo |
| __r__ | apaga um jogo |
| __R__ | remove um produto de uma encomenda |
| __P__ | procura uma equipa |
| __p__ | procura um jogo |
| __g__ | Encontra as equipas que venceram mais jogos |
| __x__ | termina o programa |
*/

      


link_jogo jogos=NULL;
link_equipa equipas=NULL;
int nl=0;

 




/**
a - Adiciona um novo jogo.
Formato de entrada: a nome:equipa1:equipa2:score1:score2
Formato de saida: NADA (excepto erro).
Erros:
NL Jogo existente. no caso de ja existir um jogo com esse nome no sistema.
NL Equipa inexistente. no caso de uma das equipas ou ambas nao existirem no sistema.
*/
void adiciona_novo_jogo(){
    Jogo *jogo=can_fail_malloc(sizeof(Jogo));
    Equipa *equipa1=can_fail_malloc(sizeof(Equipa));
    Equipa *equipa2=can_fail_malloc(sizeof(Equipa));
    char *buffer_nome=can_fail_malloc(JOGO_MAX_SIZE_NAME);
    char *buffer_equipa1=can_fail_malloc(EQUIPA_MAX_SIZE_NAME);
    char *buffer_equipa2=can_fail_malloc(EQUIPA_MAX_SIZE_NAME);
    link_equipa link_equipa1;
    link_equipa link_equipa2;

    /*c=getchar(); consumir primeiro espaco do comando antes da descricao*/
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",buffer_nome, buffer_equipa1, buffer_equipa2,&jogo->score1, &jogo->score2);
    jogo->nome=can_fail_malloc(strlen(buffer_nome)+1);
    jogo->equipa1=can_fail_malloc(strlen(buffer_equipa1)+1);
    jogo->equipa2=can_fail_malloc(strlen(buffer_equipa2)+1);

    strcpy(jogo->nome, buffer_nome);
    strcpy(jogo->equipa1, buffer_equipa1);
    strcpy(jogo->equipa2, buffer_equipa2);

    free(buffer_nome);
    free(buffer_equipa1);
    free(buffer_equipa2);



/**
    printf("%s\n", jogo->nome);
    printf("%s\n", jogo->equipa1);
    printf("%s\n", jogo->equipa2);
    printf("%i\n", jogo->score1);
    printf("%i\n", jogo->score2);
    */
    


    equipa1->nome=jogo->equipa1;
    equipa2->nome=jogo->equipa2;

 
    /*printf("%s:%s:%s:%i:%i", nome, equipa1, equipa2, score1,score2);*/

    if(list_jogo_lookup(jogos, jogo)!= NULL){
        printf("%d Jogo existente.\n", nl);
        return;
    }

    link_equipa1=list_equipa_lookup(equipas, equipa1);
    if(link_equipa1==NULL){
        printf("%d Equipa inexistente.\n", nl);
        return;
    }

    link_equipa2=list_equipa_lookup(equipas, equipa2);
    if(link_equipa2==NULL){
        printf("%d Equipa inexistente.\n", nl);
        return;
    }


    jogos=list_jogo_insert_end(jogos, jogo);

    if(jogo->score1 > jogo->score2){
        link_equipa1->equipa->total_vitorias++;
    
    }
    else if(jogo->score2 > jogo->score1){
        link_equipa2->equipa->total_vitorias++;
    } 



}

/**
A - Adiciona uma nova equipa.
Formato de entrada: A nome
Formato de saida: NADA (excepto erro).
Erros:
NL Equipa existente. no caso de ja existir uma equipa com esse nome no sistema.
*/
void adiciona_nova_equipa(){
    Equipa *equipa=can_fail_malloc(sizeof(Equipa));
    char *buffer=can_fail_malloc(EQUIPA_MAX_SIZE_NAME);
    equipa->total_vitorias=0;

    scanf(" %[^:\n]",buffer);
    equipa->nome=can_fail_malloc(strlen(buffer)+1);
    strcpy(equipa->nome, buffer);
    free(buffer);
   
   if(list_equipa_lookup(equipas, equipa)!=NULL){
        printf("%d Equipa existente.\n", nl);
        return;
    }
   
    equipas=list_equipa_insert_end(equipas, equipa);
    

}




/**
l - Lista todos os jogos introduzidos.
Formato de entrada: l

Formato de saida: Uma linha por jogo no formato abaixo

NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
*/

void listar_jogos_ordem(){
    list_jogo_print(jogos,nl);

}






/**
P - Procura uma equipa dado um nome.
Formato de entrada: P nome
Formato de saida: NL nome numero-de-jogos-ganhos.
Erros:
NL Equipa inexistente. no caso de nao existir nenhuma equipa com esse nome no sistema.
*/
void procura_equipa(){
    Equipa *equipa=can_fail_malloc(sizeof(Equipa));
    char *buffer_nome=can_fail_malloc(EQUIPA_MAX_SIZE_NAME);
    link_equipa e;

    scanf(" %[^:\n]", buffer_nome);
    equipa->nome=can_fail_malloc(strlen(buffer_nome)+1);
    strcpy(equipa->nome, buffer_nome);
    free(buffer_nome);
    
    e=list_equipa_lookup(equipas, equipa);
    if(e==NULL){
        printf("%d Equipa inexistente.\n", nl);
        return;
    }
    printf("%d %s %d\n", nl, e->equipa->nome, e->equipa->total_vitorias);


}






/**
p - Procura um jogo com o nome dado.
Formato de entrada: p nome
Formato de saida: Igual ao formato de saida do comando l mas apenas com o jogo nome.
Erros:
NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
*/
void procura_jogo(){
    Jogo *jogo=can_fail_malloc(sizeof(Jogo));
    char *buffer_nome=can_fail_malloc(JOGO_MAX_SIZE_NAME);
    link_jogo link;

    scanf(" %[^:\n]",buffer_nome);
    jogo->nome=can_fail_malloc(strlen(buffer_nome)+1);
    strcpy(jogo->nome, buffer_nome);
    free(buffer_nome);
    

    link=list_jogo_lookup(jogos,jogo);
    if(link==NULL){
        printf("%d Jogo inexistente.\n", nl);
        return;
    }
    printf("%d %s %s %s %i %i\n", nl, link->jogo->nome, link->jogo->equipa1, link->jogo->equipa2, link->jogo->score1, link->jogo->score2);

}







/**
r - Apaga um jogo dado um nome.
Formato de entrada: r nome
Formato de saida: NADA (excepto erro).
Erros:
NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
*/
void apaga_jogo(){
    Jogo *jogo=can_fail_malloc(sizeof(Jogo));
    link_jogo j;
    link_equipa e;
    char *buffer_nome=can_fail_malloc(JOGO_MAX_SIZE_NAME);
    Equipa *equipa=can_fail_malloc(sizeof(Equipa));

    scanf(" %[^:\n]",buffer_nome);
    jogo->nome=can_fail_malloc(strlen(buffer_nome)+1);
    strcpy(jogo->nome, buffer_nome);
    free(buffer_nome);
    


    j=list_jogo_lookup(jogos, jogo);
    if(j==NULL){
        printf("%d Jogo inexistente.\n", nl);
        return;
    }
    if(j->jogo->score1 > j->jogo->score2){
        equipa->nome=j->jogo->equipa1;
        e=list_equipa_lookup(equipas,equipa);
        e->equipa->total_vitorias--;
    
    }
    else if(j->jogo->score2 > j->jogo->score1){
        equipa->nome=j->jogo->equipa2;
        e=list_equipa_lookup(equipas,equipa);
        e->equipa->total_vitorias--;
    }    

    jogos=list_jogo_delete(jogos, jogo);

   
}






/**
s - Altera o score de um jogo dado o nome.
Formato de entrada: s nome:score1:score2
Formato de saida: NADA (excepto erro).
Erros:
NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
*/
void altera_pontuacao(){
    Jogo *jogo=can_fail_malloc(sizeof(Jogo));
    char *buffer_nome=can_fail_malloc(JOGO_MAX_SIZE_NAME);
    link_jogo j;
    Equipa *equipa=can_fail_malloc(sizeof(Equipa));
    link_equipa e;
    
    scanf(" %[^:\n]:%d:%d",buffer_nome, &jogo->score1, &jogo->score2);
    jogo->nome=can_fail_malloc(strlen(buffer_nome)+1);
    strcpy(jogo->nome, buffer_nome);
    free(buffer_nome);
    
    j=list_jogo_lookup(jogos,jogo);

    if(j==NULL){
        printf("%d Jogo inexistente.\n",nl);
        return;
    }

    if(j->jogo->score1 > j->jogo->score2){
        equipa->nome=j->jogo->equipa1;
        e=list_equipa_lookup(equipas,equipa);
        e->equipa->total_vitorias--;
    
    }
    else if(j->jogo->score2 > j->jogo->score1){
        equipa->nome=j->jogo->equipa2;
        e=list_equipa_lookup(equipas,equipa);
        e->equipa->total_vitorias--;
    }    
    j->jogo->score1=jogo->score1;
    j->jogo->score2=jogo->score2;


    if(j->jogo->score1 > j->jogo->score2){
        equipa->nome=j->jogo->equipa1;
        e=list_equipa_lookup(equipas,equipa);
        e->equipa->total_vitorias++;
    
    }
    else if(j->jogo->score2 > j->jogo->score1){
        equipa->nome=j->jogo->equipa2;
        e=list_equipa_lookup(equipas,equipa);
        e->equipa->total_vitorias++;
    }    

}





/**
g - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa).
Formato de entrada: g
Formato de saida:
NL Melhores numero-de-jogos-ganhos
NL * nome-equipa1
NL * nome-equipa2
NL * nome-equipa3
...
Caso nao exista nenhuma equipa, o comando nao imprime nada (nem a palavra Melhores).
Erros: Nao aplicavel.
*/

void equipas_venceram_mais(){
    link_equipa vencedoras=NULL;
    link_equipa e=equipas;
    int max=0;

    while(e!= NULL){
        if(e->equipa->total_vitorias > max){
            /*printf("Max: %d; Total: %d\n",max, e->equipa->total_vitorias);*/
            vencedoras=NULL;
            max=e->equipa->total_vitorias;
        }

        if(e->equipa->total_vitorias==max){
            /*printf("insert: %s\n", e->equipa->nome);*/
            vencedoras=list_equipa_insert_sorted(vencedoras, e->equipa);
        }
        e=e->next;
    }
    if(vencedoras!=NULL){
        printf("%d Melhores %d\n", nl, max);
        list_equipa_print(vencedoras, nl);
    }

}




















void ler_comando(char comando){
    if (comando=='x'){
        EOF;
    }
    switch(comando){
        case 'a': {
            nl++;  
            adiciona_novo_jogo();
            break;   
        }
        
        case 'A':{
            nl++;
            adiciona_nova_equipa();
            break;
        }
        
        case 'l':{
            nl++;
            listar_jogos_ordem();
            break;
        }
        
        case 'p':{
            nl++;
            procura_jogo();
            break;
        }
        case 'P':{
            nl++;
            procura_equipa();
            break;
        }
        
        case 'r':{
            nl++;
            apaga_jogo();
            break;
        }
        
        case 's':{
            nl++;
            altera_pontuacao();
            break;
        }
        
        case 'g':{
            nl++;
            equipas_venceram_mais();
            break;
        }
        
        /*
        default:
            while(getchar()!=EOF);
        */    

    }


}      


int main(){
    char comando;
    comando=getchar();
    while(comando!='x'){
        ler_comando(comando);
        comando=getchar();
    }    

    return 0;
}    
