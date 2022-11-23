#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "hash_equipa.h"
#include "hash_jogo.h"
#include "lista_jogos.h"

#define MAX_HASHTABLE 367 /* tamanho das hashtables */


/* funcao de dispersao */
int hash(char *key,int M){
    int h,a=31415,b=27183; 

    /* calcula a media ponderada dos caracteres */
    for (h=0; *key != '\0'; key++){
        h = (a*h + *key) % M;
        /* recalcula a base a cada iteracao */
        a = a*b % (M-1);
    }

    return h;
}


/* retira a vitoria de um jogo ah equipa vencedora */
void retira_vitoria(int M, pJogo jogo, linkE * equipas){
    int i;
    pEquipa equipa;

    /* verifica se a equipa 1 foi a vencedora */
    if (jogo->score1 > jogo->score2){

        /* procura a equipa 1 na hashtable */
        i=hash(jogo->equipa1,M);
        equipa = SearchEquipa(jogo->equipa1,equipas[i]);

        /* decrementa o numero de vitorias da equipa 1 */
        --equipa->vitorias;
    }
    
    /* caso contrario, verifica se a equipa 2 foi a vencedora */
    else if (jogo->score1 < jogo->score2){

        /* procura a equipa na hashtable */
        i=hash(jogo->equipa2,M);
        equipa=SearchEquipa(jogo->equipa2,equipas[i]);

        /* decrementa o numero de vitorias da equipa 2 */
        --equipa->vitorias;
    }
}


/* atribui a vitoria de um jogo ah equipa vencedora */
void atribui_vitoria(int M, pJogo jogo, linkE * equipas){
    int i;
    pEquipa equipa;

    /* verifica se a equipa 1 foi a vencedora */
    if (jogo->score1 > jogo->score2){

        /* procura a equipa 1 na hashtable */
        i=hash(jogo->equipa1,M);
        equipa = SearchEquipa(jogo->equipa1,equipas[i]);

        /* incrementa as vitorias da equipa 1 */
        ++equipa->vitorias;
    }

    /* caso contrario, verifica se a equipa 2 foi a vencedora */
    else if (jogo->score1 < jogo->score2){

        /* procura a equipa 2 na hashtable */
        i=hash(jogo->equipa2,M);
        equipa=SearchEquipa(jogo->equipa2,equipas[i]);
        
        /* incrementa as vitorias da equipa 2 */
        ++equipa->vitorias;
    }
}



/* Adiciona um novo jogo */
int comando_a(int nl, int M,linkJ *jogos,linkE *equipas,lista * jogosCron){
    char nome[1024],equipa1[1024],equipa2[1024];
    int s1,s2,i;
    pJogo j;

    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&s1,&s2);

    i=hash(nome,M); /* indice do jogo na hashtable */

    /* erro caso o jogo ja existir no sistema*/
    if (SearchJogo(nome,jogos[i])!=NULL)
        printf("%d Jogo existente.\n",nl);

    /* erro caso alguma equipa nao existir no sistema*/
    else if (SearchEquipa(equipa1,equipas[hash(equipa1,M)])==NULL || 
    SearchEquipa(equipa2,equipas[hash(equipa2,M)])==NULL)
        printf("%d Equipa inexistente.\n",nl);
    
    else{  

        /* cria o jogo */
        j = newJogo(nome,equipa1,equipa2,s1,s2);

        /* insere o jogo na hashtable dos jogos */
        jogos[i]=InsertJogo(j,jogos[i]);

        /* adiciona a vitoria a equipa vencedora */
        atribui_vitoria(M,j,equipas);

        /* insere o jogo na lista de jogos */
        jogosCron=InsertEndLista(j,jogosCron);
    }

    /* aumenta o nl antes de o retornar */
    return ++nl;
}



/* Adiciona uma nova equipa */
int comando_A(int nl,int M,linkE *equipas){
    char nome[1024];
    int i;

    scanf("%[^:\n]",nome);

    i = hash(nome,M); /* indice da equipa na hashtable */

    /* erro caso a equipa ja existir no sistema */
    if (SearchEquipa(nome,equipas[i])!=NULL)
        printf("%d Equipa existente.\n",nl);

    else 
        /* insere a equipa na hashtable das equipas */
        equipas[i]=InsertEquipa(nome,equipas[i]); 

    /* aumenta o nl antes de o retornar */  
    return ++nl;
}



/* Lista todos os jogos introduzidos */
int comando_l(lista* jogosCron, int nl){
    /* imprime a lista de jogos por ordem cronologica*/
    printLista(jogosCron,nl);

    /* aumenta o nl antes de o retornar*/
    return ++nl;
}



/* Procura um jogo com um nome dado */
int comando_p(int nl, int M,linkJ* jogos){
    char nome[1024];
    int i;
    linkJ j;

    scanf("%[^:\n]",nome);
    
    /* procura o jogo na hashtable */
    i = hash(nome,M);
    j = SearchJogo(nome,jogos[i]);
 
    printf("%d ",nl); /* imprime o numero da linha */
    
    /* erro caso o jogo nao existir no sistema */
    if (j==NULL) 
        printf("Jogo inexistente.\n");

    else
        /* imprime o jogo */
        printJogo(j->jogo);   

    /* aumenta o nl antes de o retornar */  
    return ++nl;
    
}



/* Procura uma equipa dado um nome */
int comando_P(int nl,int M,linkE* equipas){
    char nome[1024];
    int i;
    pEquipa e;

    scanf("%[^:\n]",nome);

    /* procura a equipa */
    i = hash(nome,M);
    e = SearchEquipa(nome,equipas[i]);

    /* imprime o numero da linha */
    printf("%d ",nl);

    /* erro caso a equipa nao existir no sistema */
    if (e==NULL)  
        printf("Equipa inexistente.\n");

    else
        /* imprime a equipa */
        printEquipa(e);

    /* aumenta o nl antes de o retornar */
    return ++nl;
}



/* Apagra um jogo dado um nome */
int comando_r(int nl,int M,linkJ * jogos,lista* jogosCron, linkE*equipas){
    char nome[1024];
    int i;
    linkJ j;

    scanf("%[^:\n]",nome);

    /* procura o jogo na hashtable dos jogos */
    i = hash(nome,M);
    j = SearchJogo(nome,jogos[i]);

    /* erro caso o jogo nao existir no sistema */
    if (j==NULL)
        printf("%d Jogo inexistente.\n",nl);
    
    else {
        /* retira a vitoria do jogo a equipa vencedora */
        retira_vitoria(M,j->jogo,equipas);

        /* apaga o jogo da lista por ordem cronologica */
        jogosCron = DeleteLista(nome,jogosCron);

        /* apaga o jogo da hashtable dos jogos */
        jogos[i]=DeleteJogo(j,jogos[i]);
    }

    /* aumenta o nl antes de o retornar */
    return ++nl;
}



/* Altera o score de um jogo dado o nome */
int comando_s(int nl,int M,linkJ*jogos,linkE*equipas){
    char nome[1024];
    int i,s1,s2;
    linkJ j;

    scanf("%[^:\n]:%d:%d",nome,&s1,&s2);

    /* procura o jogo */
    i = hash(nome,M);
    j = SearchJogo(nome,jogos[i]);

    /* erro caso o jogo nao existir no sistema */
    if (j==NULL)
        printf("%d Jogo inexistente.\n",nl);

    else {
        /* retira a vitoria anterior as equipas */
        retira_vitoria(M,j->jogo,equipas);

        /* altera o score do jogo */
        j->jogo->score1=s1;
        j->jogo->score2=s2;

        /* adiciona a nova vitoria a equipa vencedora */
        atribui_vitoria(M,j->jogo,equipas);
    }

    /* aumenta o nl antes de o retornar */
    return ++nl;
}



/* funcao de comparacao (utilizada no qsort)*/
int cmp_func(const void *p1,const void *p2){
    /* ordena as listas de caracteres por ordem lexicografica */
    return strcmp(* (char * const *) p1, * (char * const *) p2);
}


/* Encontra as equipas que ganharam mais jogos */
int comando_g(int nl,int M,linkE*equipas){
    int i,j=0;
    int maior=0; /* maior numero de vitorias */
    int n=0; /* numero de equipas com o maior numero de vitorias*/
    linkE x;
    char ** lista; /* lista dos nomes das equipas com maior numero de vitorias*/
    
    /* percorre todas as equipas na hashtable */
    for (i=0;i<M;i++){
        for (x=equipas[i];x!=NULL;x=x->next){

            /* verifica se a equipa tem mais vitorias do que 'maior' */
            if (x->equipa->vitorias > maior){
                maior = x->equipa->vitorias; /* atualiza 'maior' */
                n=1; /* atualiza n */
            }

            /* verifica se a equipa tem tantas vitorias como 'maior'*/
            else if (x->equipa->vitorias == maior)
                n++; /* incrementa n */
        }
    }

    /* verifica que ha pelo menos uma equipa no sistema */
    if (n!=0){

        /* aloca espaco para a lista */
        lista = (char**)can_fail_malloc(n*sizeof(char*));
        
        /* percorre todas as equipas da hashtable */
        for (i=0;i<M;i++) 
            for (x=equipas[i];x!=NULL;x=x->next)
                /* verifica se a equipa tem tantas vitorias como 'maior' */
                if (x->equipa->vitorias == maior)
                    /* acrecenta o nome da equipa a lista*/
                    lista[j++]=x->equipa->nome;

        /* ordena a lista por ordem lexicografica */
        qsort(lista,n,sizeof(char*),cmp_func);

        /* imprime as equipas */
        printf("%d Melhores %d\n",nl,maior);
        for (i=0;i<n;i++)
            printf("%d * %s\n",nl,lista[i]);

        /* liberta a lista */
        free(lista);    
    }
    return ++nl;
}



int main(){
    int nl=1; /* numero linha */
    int M=MAX_HASHTABLE; /*tamanho das hashtables */
    char c; /* comando dado pelo utilizador */

    /* inicializa a hashtable das equipas */
    linkE *equipas = InitEquipa(M); 
    /* incializa a hashtable dos jogos */
    linkJ *jogos = InitJogo(M); 
    /* inicializa a lista de jogos por ordenados por ordem de introducao */ 
    lista* jogosCron = InitLista(); 

    while ((c=getchar())!='x'){  /* repete o ciclo ate receber o comando x */
        switch(c){
            case 'a':
                getchar(); /* le o espaco introduzido pelo utilizador depois da letra do comando*/
                nl =comando_a(nl,M,jogos,equipas,jogosCron);
                break;
            case 'A':
                getchar();
                nl=comando_A(nl,M,equipas);
                break;
            case 'l':
                nl=comando_l(jogosCron,nl);
                break;
            case 'p':
                getchar();
                nl = comando_p(nl,M,jogos);
                break;
            case 'P':
                getchar();
                nl = comando_P(nl,M,equipas);
                break;
            case 'r':
                getchar();
                nl=comando_r(nl,M,jogos,jogosCron,equipas);
                break;
            case 's':
                getchar();
                nl=comando_s(nl,M,jogos,equipas);
                break;
            case 'g':
                nl = comando_g(nl,M,equipas);
                break;    
        }
    }

    /* liberta a hashtable das equipas */
    FreeHashEquipa(M,equipas);
    free(equipas);

    /* liberta a hashtable dos jogos */
    FreeHashJogo(M,jogos);
    free(jogos);

    /* liberta a lista dos jogos */
    freeLista(jogosCron);
    free(jogosCron);

    return 0;
}