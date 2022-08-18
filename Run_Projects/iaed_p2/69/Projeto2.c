#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estruturas.h"
#include "hashtable.h"
#include "ordena_aux.h"
#define MAX 1024


void adiciona_novo_jogo(lista_jogos *heads_jg,lista_equipas *heads_eq,lista *lst,int count);
void adiciona_nova_equipa(lista_equipas *heads_eq,int count);

void procura_jogo(lista_jogos *heads_jg,int count);
void procura_equipa(lista_equipas *heads_eq,int count);

void apagar_jogo(lista_jogos *heads_jg,lista_equipas *heads_eq,lista *lst,int count);
void alterar_score(lista_jogos *heads_jg,lista_equipas *heads_eq,int count);
void lista_melhores(lista_equipas *heads_eq,int count);
int main(){
    char c;
    int count=1;
    /*a hastable dei como nome heads_jg porque e uma tabela
    de ponteiros que apontam para as cabecas das listas
    o mesmo aconte para as equipas*/
    lista_jogos *heads_jg=NULL;
    lista_equipas *heads_eq=NULL;
    /*lista que poem os jogos por ordem de entrada*/
    lista *lst=lista_por_ordem_inicializar();
    heads_jg=lst_inicializar_jg(heads_jg);
    heads_eq=lst_inicializar_eq(heads_eq);
    while((c=getchar())!='x'){
        switch(c){
            case 'a':
                adiciona_novo_jogo(heads_jg,heads_eq,lst,count);
                count++;
                break;
            case 'A':
                adiciona_nova_equipa(heads_eq,count);
                count++;
                break;
            case 'l':
                listar_jogos(lst,count);
                count++;
                break;
            
            case 'p':
                procura_jogo(heads_jg,count);
                count++;
                break;
            case 'P':
                procura_equipa(heads_eq,count);
                count++;
                break;
            case 'r':
                apagar_jogo(heads_jg,heads_eq,lst,count);
                count++;
                break;
            case 's':
                alterar_score(heads_jg,heads_eq,count);
                count++;
                break;
            case 'g':
                lista_melhores(heads_eq,count);
                count++;
                break;
        }
    }
    free_heads_jg(heads_jg);
    free_heads_eq(heads_eq);
    free_head(lst);
    return 0;
}
/*adiciona um novo jogo contendo o nome dele das equipas participantes
 e o resultada de cada uma*/
void adiciona_novo_jogo(lista_jogos *heads_jg,lista_equipas *heads_eq,lista *lst,int count){
    char *nome;
    char *eq1;
    char *eq2;
    int sc1,sc2;
    Jogo jogo;
    lista_equipas eq_1,eq_2;
    nome=malloc(MAX*sizeof(char));
    eq1=malloc(MAX*sizeof(char));
    eq2=malloc(MAX*sizeof(char));
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n",nome,eq1,eq2,&sc1,&sc2);
    eq_1=EQprocurar(heads_eq,eq1);
    eq_2=EQprocurar(heads_eq,eq2);
    if(JGprocurar(heads_jg,nome)!=NULL)
        printf("%d Jogo existente.\n",count);
    else if(eq_1==NULL || eq_2==NULL)
        printf("%d Equipa inexistente.\n",count);
    else{
        jogo=novo_jogo(nome,eq1,eq2,sc1,sc2);
        lista_por_ordem_add(lst,jogo);
        JGinserir(heads_jg,jogo);
        if(sc1>sc2)
            eq_1->equipa->vitorias+=1;
        else if(sc2>sc1)
            eq_2->equipa->vitorias+=1;
    }
    free(nome);
    free(eq1);
    free(eq2);
}
/*adiciona uma nova equipa contendo o nome dela e inicializa as vitorias a 0*/
void adiciona_nova_equipa(lista_equipas *heads_eq,int count){
    Equipa equipa;
    char *nome;
    nome=malloc(MAX*sizeof(char));
    scanf(" %[^:\n]:",nome);
    if(EQprocurar(heads_eq,nome)==NULL){
        equipa=nova_equipa(nome);
        EQinserir(heads_eq,equipa);
    }
    else printf("%d Equipa existente.\n",count);
    
    free(nome);
}

/*dando o nome do jogo verifica se ele existe e caso exista da as
 informacoes acerca dele*/
void procura_jogo(lista_jogos *heads_jg,int count){
    char *nome;
    lista_jogos jogo_procurado;
    nome=malloc(MAX*sizeof(char));
    scanf(" %[^:\n]:",nome);
    jogo_procurado=JGprocurar(heads_jg,nome);
    if(jogo_procurado==NULL)
        printf("%d Jogo inexistente.\n",count);
    else{
        printf("%d %s %s %s %d %d\n",count,jogo_procurado->jogo->nome_jogo,
            jogo_procurado->jogo->equipa1,jogo_procurado->jogo->equipa2,
            jogo_procurado->jogo->sc1,jogo_procurado->jogo->sc2);
    }
    free(nome);
}

/*dado o nome da equipa verifica se ela existe e caso exista da as
 informacoes acerca dela*/
void procura_equipa(lista_equipas *heads_eq,int count){
    char *nome;
    lista_equipas equipa_procurada;
    nome=malloc(MAX*sizeof(char));
    scanf(" %[^:\n]:",nome);
    equipa_procurada=EQprocurar(heads_eq,nome);
    if(equipa_procurada==NULL)
        printf("%d Equipa inexistente.\n",count);
    else{
        printf("%d %s %d\n",count,equipa_procurada->equipa->nome,
            equipa_procurada->equipa->vitorias);
    }
    free(nome);
}
/*dado o nome do jogo caso ele exista remove o podendo alterar o
 numero de vitorias das equipas*/
void apagar_jogo(lista_jogos *heads_jg,lista_equipas *heads_eq,lista *lst,int count){
    char *nome;
    lista_jogos jogo_el;
    lista_equipas equipa_procurada;
    nome=malloc(MAX*sizeof(char));
    scanf(" %[^:\n]:",nome);
    jogo_el=JGprocurar(heads_jg,nome);
    if(jogo_el==NULL)
        printf("%d Jogo inexistente.\n",count);
    else{
        if(jogo_el->jogo->sc1>jogo_el->jogo->sc2){
            equipa_procurada=EQprocurar(heads_eq, jogo_el->jogo->equipa1);
            equipa_procurada->equipa->vitorias-=1;
        }
        else if(jogo_el->jogo->sc1<jogo_el->jogo->sc2){
            equipa_procurada=EQprocurar(heads_eq, jogo_el->jogo->equipa2);
            equipa_procurada->equipa->vitorias-=1;
        }
        apagar_jogo_lista_por_ordem(lst,nome);
        Elimina_jogo(heads_jg,nome);
    }
    free(nome);
}
/*altera o score de um jogo podendo alterar o numero de vitorias das equipas*/
void alterar_score(lista_jogos *heads_jg,lista_equipas *heads_eq,int count){
    char *nome;
    int novo_sc1,novo_sc2;
    lista_jogos jogo_el;
    lista_equipas eq_procurada;
    nome=malloc(MAX*sizeof(char));
    scanf(" %[^:\n]:%d:%d",nome,&novo_sc1,&novo_sc2);
    jogo_el=JGprocurar(heads_jg,nome);
    if(jogo_el==NULL)
        printf("%d Jogo inexistente.\n",count);
    else{
        /*vamos retirar a vitoria para caso a vitoria se mantenha entao 
        depois voltamos a adicionar*/
        if(jogo_el->jogo->sc1>jogo_el->jogo->sc2){
            eq_procurada=EQprocurar(heads_eq, jogo_el->jogo->equipa1);
            eq_procurada->equipa->vitorias-=1;
        }
        else if(jogo_el->jogo->sc1<jogo_el->jogo->sc2){
            eq_procurada=EQprocurar(heads_eq, jogo_el->jogo->equipa2);
            eq_procurada->equipa->vitorias-=1;
        }
        jogo_el->jogo->sc1=novo_sc1;
        jogo_el->jogo->sc2=novo_sc2;
        if(novo_sc1>novo_sc2){
            eq_procurada=EQprocurar(heads_eq, jogo_el->jogo->equipa1);
            eq_procurada->equipa->vitorias+=1;
        }
        else if(novo_sc2>novo_sc1){
            eq_procurada=EQprocurar(heads_eq, jogo_el->jogo->equipa2);
            eq_procurada->equipa->vitorias+=1;
        }

    }
    free(nome);
}
/*lista as equipas que tem mais vitorias caso nao haja equipas 
entao nao retorna nada*/
void lista_melhores(lista_equipas *heads_eq,int count){
    int i=0,mais_vitorias=0,tamanho=0;
    lista_equipas aux;
    for(i=0;i<M;i++){
        aux=heads_eq[i];
        while(aux!=NULL){
            if(aux->equipa->vitorias>mais_vitorias){
                mais_vitorias=aux->equipa->vitorias;
                tamanho=1;
            }
            else if(aux->equipa->vitorias==mais_vitorias)
                tamanho++;
            aux=aux->next;
        }
    }
    if(tamanho>0)
        lista_melhores_aux(heads_eq, mais_vitorias, tamanho,count);


}