#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2.h"

/*--------CONSTANTES---------*/
#define MAX_CARACTERES 1023


/*---------HASHTABLE---------*/

int hash(char v[MAX_CARACTERES], int M){
    int h = 0, a = 31415, b = 27183;

    for(h=0; *v != '\0'; v++, a = a*b % (M-1)){
        h = (a*h + *v) % M;
    }
    return h;
}

/*************hash das equipas**********/
void ini_hash_eq(link_equipa **eq, int M){
    int j;
    eq[0] = (link_equipa*)can_fail_malloc(M*sizeof(link_equipa));
    for (j = 0; j < M; j++){
        eq[0][j] = NULL;
    }
    return;
}

link_equipa nova_equipa(char nome[MAX_CARACTERES]){
    link_equipa aux = (link_equipa)can_fail_malloc(sizeof(struct node2));

    strcpy(aux-> eq.nome_equipa, nome);
    aux-> eq.numero_vit = 0;

    aux->seguinte = NULL;
    return aux;
}

void inserir_hash_eqp(link_equipa *eq, int M, char nome[MAX_CARACTERES]){
    /*insere elementos na hash das equipas*/
    link_equipa a;
    int i = hash(nome,M);
    if (eq[i] == NULL){
        eq[i] = nova_equipa(nome);
        return;
    }
        
    a = nova_equipa(nome);
    a->seguinte = eq[i];
    eq[i] = a;
        
}

link_equipa procura_hash_equipas(link_equipa *t_eq, char *nome, int M){
    /*procura a equipa pelo nome na minha hash de equipas*/
    int i = hash(nome, M);
    link_equipa aux=NULL;
    for (aux = t_eq[i]; aux!=NULL; aux = aux->seguinte){
        if (strcmp(aux->eq.nome_equipa, nome)==0){
            return aux;
        }
    }
    return NULL;
}

void apaga_node_eq(link_equipa nod){
    free(nod);
}

void apaga_hash_equipas(link_equipa *eq, int M){
    /*apaga todos os elementos da tabela*/
    int i;
    link_equipa auxiliar;
    link_equipa anterior;
    for (i = 0; i < M; i++){

        for (auxiliar=eq[i], anterior = NULL; auxiliar != NULL;){
            anterior = auxiliar;
            auxiliar = auxiliar->seguinte;
            apaga_node_eq(anterior);
        }
    }
}

/******************hash do jogo***********************/

void inserir_hash_jogo(link_jogo *tab, int M, char nome[MAX_CARACTERES], char equipa1[MAX_CARACTERES], char equipa2[MAX_CARACTERES], int score1, int score2){
    /*insere elementos na minha hash*/
    link_jogo aux;
    int i = hash(nome, M);
    
        if (tab[i] == NULL){
            tab[i] = novo_jogo(nome, equipa1, equipa2, score1, score2);
        }
        else {
            aux = novo_jogo(nome, equipa1, equipa2, score1, score2);
            aux->seguinte = tab[i];
            tab[i] = aux;
        }
}

link_jogo procura_hash(link_jogo *tab, char nome[MAX_CARACTERES], int M){
    /*procura um elemento na minha hash dos jogos, pelo nome do jogo*/
    int i = hash(nome, M);
    link_jogo aux;
    
    for (aux = tab[i]; aux!=NULL; aux = aux->seguinte){
        if (strcmp(aux->jogos.nome, nome)==0){
            return aux;
        }
    }
    return NULL;
}

void apaga_node(link_jogo nod){
    free(nod);
}

void apaga_hash(link_jogo *tab, int M){
    /*apaga todos os elementos da tabela*/
    int i;
    link_jogo auxiliar;
    link_jogo anterior;
    for (i = 0; i < M; i++){

        for (auxiliar=tab[i], anterior = NULL; auxiliar != NULL;){
            anterior = auxiliar;
            auxiliar = auxiliar->seguinte;
            apaga_node(anterior);
        }
    }
}

void remove_hash_el(link_jogo *tab, char *nome, int M){
    /*remove um elemento da hash do jogo */
    int i ;
    link_jogo auxiliar, anterior;

    for (i = 0; i < M; i++){
        for (auxiliar = tab[i], anterior = NULL; auxiliar != NULL;){
            if(strcmp(auxiliar->jogos.nome, nome)==0){
                if(auxiliar == tab[i]){
                    tab[i] = auxiliar->seguinte;
                    apaga_node(auxiliar);
                    break;
                }else{
                    anterior->seguinte = auxiliar->seguinte;
                    apaga_node(auxiliar);
                    break;
                }
            }
            anterior = auxiliar;
            auxiliar = auxiliar->seguinte;
        }
    } 
}

link_jogo novo_jogo(char nome[MAX_CARACTERES], char equipa1[MAX_CARACTERES], char equipa2[MAX_CARACTERES], int score1, int score2){
   /*cria um jogo*/
    link_jogo aux = (link_jogo)can_fail_malloc(sizeof(struct node1));

    strcpy(aux-> jogos.nome, nome);
    strcpy(aux-> jogos.equipa1.nome_equipa,equipa1);
    strcpy(aux-> jogos.equipa2.nome_equipa , equipa2);
    aux-> jogos.score1 = score1;
    aux-> jogos.score2 = score2;

    aux->seguinte = NULL;
    return aux;
}


/**************FUNCOES***************/
void adiciona_jogo(link_jogo *tab,link_equipa *tab_eq, int M, int M2,int NL){
    /*adiciona um jogo ao meu sistema*/
    char nome[MAX_CARACTERES];
    char equipa1[MAX_CARACTERES];
    char equipa2[MAX_CARACTERES];
    int score1;
    int score2;
    int h;

    scanf("%[^:]:%[^:]:%[^:]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
    if(procura_hash(tab,nome, M)==NULL){

        if((procura_hash_equipas(tab_eq,equipa1,M2)!=NULL) || (procura_hash_equipas(tab_eq,equipa2,M2)!=NULL)){
            inserir_hash_jogo(tab,M,nome,equipa1,equipa2,score1,score2);
            
            if(score1 > score2){
                h = hash(equipa1,M2);
                tab_eq[h]->eq.numero_vit = tab_eq[h]->eq.numero_vit + 1; /*atualiza o valor das vitorias*/
            }else {
                h = hash(equipa2,M2);
                tab_eq[h]->eq.numero_vit = tab_eq[h]->eq.numero_vit + 1;
            }

        }else{
            printf("%d Equipa inexistente.\n", NL);
        }
    }else{
        printf("%d Jogo existente.", NL);
    }
}

void imprime_jogo(link_jogo tab, int NL){
    /*imprime jogo*/
    printf("%d %s ",NL,tab->jogos.nome);
    printf("%s %s ",tab->jogos.equipa1.nome_equipa,tab->jogos.equipa2.nome_equipa);
    printf("%02d %02d.\n",tab->jogos.score1,tab->jogos.score2);
}

void lista_jogos(link_jogo *tab, int NL, int M){
    /*lista todos os jogos introduzidos*/
    link_jogo auxiliar;
    int i;
    for(i=0; i<M; i++){
        for(auxiliar = tab[i]; auxiliar!=NULL; auxiliar = auxiliar->seguinte){
            imprime_jogo(auxiliar, NL);
        }
    }
}

void procura_jogo(link_jogo *tab, int M, int NL){
    /*procura um jogo por nome*/
    char nome[MAX_CARACTERES];
    link_jogo tab1;

    scanf("%[^\n]",nome);
    
    if(procura_hash(tab,nome,M)!=0){
        tab1 = procura_hash(tab,nome,M);
        imprime_jogo(tab1,NL);
    }else {
        printf("%d Jogo inexistente.\n", NL);
    }
}

void remove_jogo(link_jogo *tab, int M, int NL){
    /*remove um elemento do jogo ao receber o nome do jogo*/
    char nome[MAX_CARACTERES];

    scanf("%[^\n]",nome);

    if (procura_hash(tab,nome,M)!=0){
        remove_hash_el(tab,nome,M);
    }else{
        printf("%d Jogo inexistente.\n", NL);
    }
}

void altera_score(link_jogo *tab, int M, int NL){
    /*altera scrore de um jogo dando o nome do mesmo*/
    char nome[MAX_CARACTERES];
    int score1, score2;
    int h;

    scanf("%[^:]:%d:%d",nome, &score1, &score2);
    if(procura_hash(tab, nome, M)!= 0){
        h = hash(nome,M);
        tab[h]->jogos.score1 = score1;
        tab[h]->jogos.score2 = score2;
    }else{
        printf("%d Jogo inexistente.\n", NL);
    }
}
/*
void printTab(link_equipa *tab, int M){
    int j;
    link_equipa aux;
    for(j=0;j<M;j++){
        for(aux = tab[j];aux != NULL; aux = aux->seguinte){
            printf("NL %s\n", aux->eq->nome_equipa);
        }
    }
}*/

void adiciona_equipa(link_equipa *tab_eq, int M, int NL){
    /*adiciona uma equipa ao meu sistema*/
    char nome[MAX_CARACTERES];

    scanf("%[^\n]",nome);

    if (procura_hash_equipas(tab_eq,nome,M)==NULL){
        inserir_hash_eqp(tab_eq,M,nome);
    }else{
        printf("%d Equipa existente.\n", NL);
    }
}


/*------------MAIN-----------*/
int main(){
    char comando;
    int i, NL=0;

    /*inicializacao dos ponteiros a NULL*/
    link_jogo *tab_jogo =NULL;
    link_equipa *tab_equipa=NULL;

    int M = 1033;/*M para a hash dos jogos*/
    int M2 = 1933;/*M para a hash dos equipas;*/
    
    /*inicia a hash dos jogos, mete todas as cabecas para NULL*/
    tab_jogo = (link_jogo*)can_fail_malloc(M*sizeof(link_jogo));
    for (i = 0; i < M; i++){
        tab_jogo[i] = NULL;
    }

    /*inicializacao da hash das equipas, mete tudo em NULL*/
    ini_hash_eq(&(tab_equipa),M2);

    
    /*comandos*/
    do{
        switch (comando = getchar()){
            case 'a':
                getchar();
                NL++;
                adiciona_jogo(tab_jogo,tab_equipa,M,M2,NL);
                break;
            case 'l':
                NL++;
                lista_jogos(tab_jogo,NL,M);
                break;
            case 'p':
                getchar();
                NL++;
                procura_jogo(tab_jogo,M,NL);
                break;
            case 'r':
                getchar();
                NL++;
                remove_jogo(tab_jogo,M,NL);
                break;
            case 's':
                getchar();
                NL++;
                altera_score(tab_jogo,M,NL);
                break;
            case 'A':
                getchar();
                NL++;
                adiciona_equipa(tab_equipa,M2,NL);
                break;
        }
    } while (comando != 'x');
            
    apaga_hash(tab_jogo,M);
    free(tab_jogo);
    apaga_hash_equipas(tab_equipa,M);
    free(tab_equipa);
    return 0;
}