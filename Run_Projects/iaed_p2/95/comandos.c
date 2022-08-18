#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "geral.h"
#include "structs.h"

#define MAX_NOME 1024

/*adiciona um novo jogo*/
void a(int cont,table_eq tab_eq,table_jogos tab_j,listagem lst) {
    char nome[MAX_NOME],equipa1[MAX_NOME],equipa2[MAX_NOME];
    int score1,score2;
    pJogo match;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&score1,&score2);
    if (SearchJogo(nome,tab_j)) {
        printf("%d Jogo existente.\n",cont);
        return;
    }
    if ((SearchEquipa(equipa1,tab_eq) == NULL) || 
    (SearchEquipa(equipa2,tab_eq) == NULL)) {
        printf("%d Equipa inexistente.\n",cont);
        return;
    }
    match = cria_jogo(nome,equipa1,equipa2,score1,score2,tab_eq);
    add_last(lst,match);
    InsertJogo(match,tab_j);
}

/*lista todos os jogos introduzidos*/
void l(int cont,listagem lst) 
{
    pJogo temp;
    temp = lst->head;
    while (temp != NULL) {
        printf("%d %s %s",cont,temp->nome,temp->equipa1);
        printf(" %s %d %d\n",temp->equipa2,temp->score1,temp->score2);
        temp = temp->next;
    }
}

/*procura um jogo dado um nome*/
void p(int cont,table_jogos tab_j) {
    char nome[MAX_NOME];
    pJogo match;
    scanf(" %[^:\n]",nome);
    if (SearchJogo(nome,tab_j) == NULL) {
        printf("%d Jogo inexistente.\n",cont);
        return;
    }
    match = SearchJogo(nome,tab_j);
    printf("%d %s %s ",cont,nome,match->equipa1);
    printf("%s %d %d\n",match->equipa2,match->score1,match->score2);
}

/*apaga um jogo dado um nome*/
void r(int cont,table_jogos tab_j,table_eq tab_eq,listagem lst) {
    char nome[MAX_NOME];
    scanf(" %[^:\n]",nome);
    if (SearchJogo(nome,tab_j) == NULL) {
        printf("%d Jogo inexistente.\n",cont);
        return;
    }
    if ((SearchJogo(nome,tab_j))->winner != NULL) {
        SearchEquipa((SearchJogo(nome,tab_j))->winner,tab_eq)->vitorias--;
    } 
    /*necessario remover tanto na hash de jogos bem como na lista*/
    delete_jogo_lst(lst,SearchJogo(nome,tab_j));
    DeleteJogoHash(nome,tab_j);
}

/*altera um score de um jogo dado um nome*/
void s(int cont,table_jogos tab_j,table_eq tab_eq) {
    char nome[MAX_NOME];
    char *old_winner = NULL;
    pJogo match;
    int score1,score2;
    scanf(" %[^:\n]:%d:%d",nome,&score1,&score2);
    if (SearchJogo(nome,tab_j) == NULL) {
        printf("%d Jogo inexistente.\n",cont);
        return;
    }
    match = SearchJogo(nome,tab_j);
    if (match->winner != NULL) {
        old_winner = malloc(sizeof(char)*strlen(match->winner)+1);
        strcpy(old_winner,match->winner);
    }
    Change_Score(match,score1,score2);
    Change_Wins(match,tab_eq,old_winner);
    /*old_winner eh apenas uma referencia para entender alteracoes
    pelo que sera sempre "liberto"*/
    free(old_winner);
}

/*adiciona uma nova equipa*/
void A(int cont,table_eq tab_eq) {
    char nome[MAX_NOME];
    Equipas equipa;
    scanf(" %[^:\n]",nome);
    if (SearchEquipa(nome, tab_eq)) {
        printf("%d Equipa existente.\n",cont);
        return;
    }
    equipa = cria_equipa(nome);

    InsertEquipa(equipa, tab_eq);
}

/*procura uma equipa dado um nome*/
void P(int cont,table_eq tab_eq) {
    char nome[MAX_NOME];
    int wins;
    scanf(" %[^:\n]",nome);
    if (SearchEquipa(nome,tab_eq) == NULL) {
        printf("%d Equipa inexistente.\n",cont);
        cont++;
        return;
    }
    wins = SearchEquipa(nome,tab_eq)->vitorias;
    printf("%d %s %d\n",cont,nome,wins);

}

/*funcao auxiliar ao qsort*/
int my_strcmp(const void *a, const void *b)
{
    char **v1, **v2;
    v1 = (char**) a;
    v2 = (char**) b;
    return strcmp(*v1,*v2);
}

/*encontra as equipas com mais vitorias e lista 
 por ordem lexicografica*/
void g(int cont,table_eq tab_eq) 
{
    /*max_wins guarda o numero maximo de vitorias de entre
    todos os jogos existentes*/
    /*nr_eq guarda quantas equipas tem esse numero (max_wins) de
    vitorias*/
    int i,j=0,max_wins=0,nr_eq=0;
    char **vetor;
    Node_eq temp = NULL;
    /*percorre a lista de cada indice da hash table de equipas*/
    for (i = 0; i < tab_eq->M ;i++) {
        temp = tab_eq->heads[i];
        while(temp != NULL) {
            /*caso encontre uma equipa com um numero maior de 
            vitorias ao registado em max_wins*/
            if (temp->equipa->vitorias == max_wins) {
                nr_eq++;
            }
            if (temp->equipa->vitorias > max_wins) {
                max_wins = temp->equipa->vitorias;
                /*reset ao nr de equipas*/
                nr_eq = 1;
            }
            temp = temp->next;
        }
    }
    if (nr_eq == 0) {
        return;
    }
    /*criacao de um vetor cujo tamanho eh nr_eq com o intuito
    de o preencher com o nome das equipas com maximo nr de vitorias*/
    vetor = (char**)malloc(sizeof(char*)*nr_eq);
    /*percorre novamente todos os indices da hash table ate 
    ter o vetor totalmente preenchido*/
    for (i = 0; i<tab_eq->M && j != nr_eq;i++) {
        temp = tab_eq->heads[i];
        while(temp != NULL) {
            if (temp->equipa->vitorias == max_wins) {
                vetor[j] = malloc(sizeof(char)*strlen(temp->equipa->nome)+1);
                strcpy(vetor[j],temp->equipa->nome);
                j++;
            }
            temp = temp->next;
        }
    }
    qsort(vetor, nr_eq, sizeof(char*), my_strcmp);

    printf("%d Melhores %d\n", cont, max_wins);
    for(i=0; i<nr_eq && vetor[i] != NULL; i++) {
        printf("%d * %s\n", cont, vetor[i]);
    }
    for(i=0; i<nr_eq; i++) {
        free(vetor[i]);
    }
    free(vetor);

}
