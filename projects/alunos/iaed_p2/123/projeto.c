#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int hash(char *nome){ /*obter valor indice*/
    int i;
    int tamanho = strlen(nome);
    unsigned int hash_valor = 0;
    for (i=0; i<tamanho; i++){
        hash_valor += nome[i];
        hash_valor = hash_valor * nome[i] % 1000;
    }
    return hash_valor;
}

/*hashtable equipas*/
typedef struct Equipa{  /*hashtable vai guardar uma equipa*/
    char *nome;              /*e a chave*/                     
    int vitorias;            /*vitorias da equipa*/
    struct Equipa *next;     /*aponta para a proxima entrada*/
}Equipa; 

typedef struct {    /*hashtable*/                                         
     Equipa **entradas;
}hash_tabela;

hash_tabela *hash_criar(int hash_tamanho){
    int i;
    /*alocar tabela*/
    hash_tabela *hashtabela = can_fail_malloc(sizeof(hash_tabela));
    /*alocar entradas da tabela*/
    hashtabela->entradas = can_fail_malloc(sizeof(Equipa*) * hash_tamanho);
    /*colocar entradas a NULL*/
    for(i=0; i< hash_tamanho; i++){
        hashtabela->entradas[i] = NULL;
    }
    return hashtabela;
}

Equipa* procuraequipa(hash_tabela *hashtabela, char *nome){
    unsigned int indice = hash(nome);
    Equipa *entrada = hashtabela->entradas[indice];
    while (entrada != NULL){
        if(strcmp((entrada->nome), nome) == 0){
            return entrada;
        }
        entrada = entrada->next;
    }
    return entrada;
}

void hash_adicionarequipa(hash_tabela *hashtabela, char *nome, int linha){
    unsigned int indice = hash(nome);
    Equipa *entrada;
    if(procuraequipa(hashtabela, nome) != NULL){printf("%d Equipa existente.\n", linha);}
    else{
        entrada = can_fail_malloc(sizeof(Equipa));
        entrada->nome = (char* ) can_fail_malloc(sizeof(char) * (strlen(nome) +1));
        strcpy(entrada->nome, nome);
        entrada->vitorias = 0; /*comeca a 0*/
        entrada->next = hashtabela->entradas[indice]; 
        hashtabela->entradas[indice] = entrada;
    }
}


/*hashtable jogos*/
typedef struct Jogo{  /*hashtable vai guardar uma jogo*/
    char *nome;              /*nome do jogo e a chave*/
    char *equipa1;           /*nome equipas*/
    char *equipa2;                     
    int score1;              /*golos cada equipa*/
    int score2;            
    struct Jogo *prox;     /*aponta para a proxima entrada*/
}Jogo; 

typedef struct {    /*hashtable*/                                           
     Jogo **entradasj;
}hash_tabela_jogo;

int contador_vetor = 0;
Jogo vetor[10000];

hash_tabela_jogo *hash_criarj(int hash_tamanho){
    int i = 0;
    /*alocar tabela*/
    hash_tabela_jogo *hashtabela = can_fail_malloc(sizeof(hash_tabela_jogo));
    /*alocar entradas da tabela*/
    hashtabela->entradasj = can_fail_malloc(sizeof(Jogo*) * hash_tamanho);
    /*colocar entradas a NULL*/
    for(i=0; i< hash_tamanho; i++){
        hashtabela->entradasj[i] = NULL;
    }
    return hashtabela;
}
void adicionavitoria(hash_tabela *hashtabelaequipas, char *equipa){
    unsigned int indice = hash(equipa);
    Equipa *entrada = hashtabelaequipas->entradas[indice];
    entrada->vitorias += 1;
}

void retiravitoria(hash_tabela *hashtabelaequipas, char *equipa){
    unsigned int indice = hash(equipa);
    Equipa *entrada = hashtabelaequipas->entradas[indice];
    entrada->vitorias -= 1;
}

Jogo* procurajogo(hash_tabela_jogo* hashtabela, char* nome){
    unsigned int indice = hash(nome);
    Jogo* entrada = hashtabela->entradasj[indice];
    while(entrada != NULL){
        if(strcmp(entrada->nome, nome) == 0){
            return entrada;
        }
        entrada = entrada->prox;
    }
    return entrada;
}

void hash_adicionarjogo(hash_tabela_jogo *hashtabela, hash_tabela *hashtabelaequipas, char *nome, char *equipa1, char *equipa2, int score1, int score2, int linha){
    unsigned int indice = hash(nome);                    
    Jogo *entrada;
    if (procurajogo(hashtabela, nome) != NULL){printf("%d Jogo existente.\n", linha);}
    else{
        if (procuraequipa(hashtabelaequipas, equipa1) == NULL || procuraequipa(hashtabelaequipas, equipa2) == NULL){ /*procuraequipa_aux devolve inteiro igual a 0 caso a equipa nao exista */
        printf("%d Equipa inexistente.\n", linha);
            }
        else{
            entrada = can_fail_malloc(sizeof(Jogo));
            entrada->nome = (char* ) can_fail_malloc(sizeof(char) * (strlen(nome) +1));
            entrada->equipa1 = (char* ) can_fail_malloc(sizeof(char) * (strlen(equipa1) +1));
            entrada->equipa2 = (char* ) can_fail_malloc(sizeof(char) * (strlen(equipa2) +1));
            strcpy(entrada->nome, nome);
            strcpy(entrada->equipa1, equipa1);
            strcpy(entrada->equipa2, equipa2);
            entrada->score1 = score1;
            entrada->score2 = score2;
            if (score1 > score2){adicionavitoria(hashtabelaequipas, equipa1);}
            else if(score2 > score1){adicionavitoria(hashtabelaequipas, equipa2);}
            entrada->prox = hashtabela->entradasj[indice];
            hashtabela->entradasj[indice] = entrada;
            vetor[contador_vetor] = *entrada;
            contador_vetor ++;
        }
    }
}
void lista_jogos(int linha){
    int i = 0;
    for (i=0; i<contador_vetor; i++){
        printf("%d %s %s %s %d %d\n", linha, vetor[i].nome, vetor[i].equipa1, vetor[i].equipa2, vetor[i].score1, vetor[i].score2);
    }
}
void apagajogo(hash_tabela_jogo* hashtabelaj, hash_tabela* hashtabelaequipas, char* nome){
    unsigned int indice = hash(nome);
    Jogo* J = hashtabelaj->entradasj[indice];
    Jogo* anterior = NULL;
    while (J != NULL){
        if(strcmp(J->nome, nome) == 0){
            if(anterior != NULL){
                anterior->prox = J->prox;
            }
            else{
                hashtabelaj->entradasj[indice] = J->prox;
            }
            if(J->score1 > J->score2){retiravitoria(hashtabelaequipas, J->equipa1);}
            else if (J->score2 > J->score1){retiravitoria(hashtabelaequipas, J->equipa2);}
            free(J->nome);
            free(J->equipa1);
            free(J->equipa2);
        }
        anterior = J;
        J = J->prox;
    }
}
void alterascore(hash_tabela_jogo* hashtabelaj, hash_tabela* hashtabelaequipas, char* nome, int score1, int score2){
    Jogo* J = procurajogo(hashtabelaj, nome);
    if ((J->score1 > J->score2) && score2>score1){
        retiravitoria(hashtabelaequipas, J->equipa1);
        adicionavitoria(hashtabelaequipas, J->equipa2);
    }
    if ((J->score1 > J->score2) && score2 == score1){
        retiravitoria(hashtabelaequipas, J->equipa1);
    }
    else if ((J->score1 == J->score2) && score2>score1){
        adicionavitoria(hashtabelaequipas, J->equipa2);
    }
    else if ((J->score1 == J->score2) && score1>score2){
        adicionavitoria(hashtabelaequipas, J->equipa1);
    }
    else if ((J->score1 < J->score2) && score1>score2){
        retiravitoria(hashtabelaequipas, J->equipa2);
        adicionavitoria(hashtabelaequipas, J->equipa1);
    }
    else if ((J->score1 < J->score2) && score1==score2){
        retiravitoria(hashtabelaequipas, J->equipa2);
    }
    J->score1 = score1;
    J->score2 = score2;
}

/*void printhashtable(hash_tabela_jogo* hashtabela){
    printf("Start\n");
    for(int i = 0; i<1000; i++){
        Jogo* J = hashtabela->entradasj[i];
        while (J!= NULL){
        printf("%s %s %s %d %d-", J->nome, J->equipa1, J->equipa2, J->score1, J->score2);
        J = J->prox;
        }
    }
    printf("End\n");
}*/

int main(){
    hash_tabela *hashtabela = hash_criar(1000);        /*inicialicao das hashtabelas*/
    hash_tabela_jogo *hashtabelaj = hash_criarj(1000);
    int flag = 1;
    int linha = 0;
    int score1;
    int score2;
    char *nome = (char* ) can_fail_malloc(sizeof(char)* 1024);
    char *equipa1 = (char* ) can_fail_malloc(sizeof(char)* 1024);
    char *equipa2 = (char* ) can_fail_malloc(sizeof(char)* 1024);
    Equipa* E;
    Jogo* J;
    do{
        switch(getchar()){
            case('a'):
                linha ++;
                scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
                hash_adicionarjogo(hashtabelaj, hashtabela, nome, equipa1, equipa2, score1, score2, linha);
                break;
            case('A'):
                linha ++;
                scanf("%s", nome);
                hash_adicionarequipa(hashtabela, nome, linha);
                break;
            case('l'):
                linha ++;
                lista_jogos(linha);
                break;
            case('p'):
                linha ++;
                scanf("%s", nome);
                J = procurajogo(hashtabelaj, nome);
                if (J == NULL) {printf("%d Jogo inexistente.\n", linha);}
                else{
                    printf("%d %s %s %s %d %d\n", linha, J->nome, J->equipa1, J->equipa2, J->score1, J->score2);
                }              
                break;
            case('P'):
                linha ++;
                scanf("%s", nome);
                E = procuraequipa(hashtabela, nome);
                if (E == NULL) {printf("%d Equipa inexistente.\n", linha);}
                else{printf("%d %s %d\n", linha, E->nome, E->vitorias);}
                procuraequipa(hashtabela, nome);
                break;
             case('r'):
                linha ++;
                scanf("%s", nome);
                if (procurajogo(hashtabelaj, nome) == NULL) {printf("%d Jogo inexistente.\n", linha);}
                else{
                    apagajogo(hashtabelaj, hashtabela, nome);
                }          
                break;
            case('s'):
                linha ++;
                scanf(" %[^:]:%d:%d", nome, &score1, &score2);
                if (procurajogo(hashtabelaj, nome) == NULL) {printf("%d Jogo inexistente.\n", linha);}
                else{alterascore(hashtabelaj, hashtabela, nome, score1, score2);}
                break;
            case('g'):
                linha ++;           
                break;
            case('x'):
                linha = 0;
                flag = 0;
                /*printhashtable(hashtabelaj);*/
                break;
        }
    }while(flag == 1);
    free(nome);
    free(hashtabela);
    free(hashtabelaj);
    free(equipa1);
    free(equipa2);
    return 0;
}