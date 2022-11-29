#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estruturas.h"
#include <string.h>

/*id criado apartir da soma de todos os numeros
correspondentes aos caracteres da palavra*/
int cria_id(char *nome){
    int tamanho,id=0,i=0;
    tamanho=strlen(nome);
    for(i=0;i<=tamanho;i++)
        id+=nome[i];
    return id;
}

Jogo novo_jogo(char* nome1,char* equipa_1,char* equipa_2, int score1,int score2){
    int tamanho;
    Jogo novo;
    novo=(Jogo)can_fail_malloc(sizeof(struct str_jogo));
    tamanho=(strlen(nome1))+1;
    novo->nome_jogo=(char*)can_fail_malloc(sizeof(char)*tamanho);
    strcpy(novo->nome_jogo,nome1);
    tamanho=strlen(equipa_1)+1;
    novo->equipa1=(char*)can_fail_malloc(sizeof(char)*tamanho);
    strcpy(novo->equipa1,equipa_1);
    novo->equipa2=(char*)can_fail_malloc((sizeof(char)*((strlen(equipa_2))+1)));
    strcpy(novo->equipa2,equipa_2);
    novo->sc1=score1;
    novo->sc2=score2;
    novo->id=cria_id(nome1);
    return novo;
}

Equipa nova_equipa(char *nome_equipa){
    Equipa nova;
    nova=(Equipa)can_fail_malloc(sizeof(struct str_equipa));
    nova->nome=(char*)can_fail_malloc((sizeof(char)*((strlen(nome_equipa))+1)));
    strcpy(nova->nome,nome_equipa);
    nova->vitorias=0;
    nova->id=cria_id(nome_equipa);
    return nova;
}

void free_jogo(Jogo a){
    free(a->nome_jogo);
    free(a->equipa1);
    free(a->equipa2);
    free(a);
}

void free_equipa(Equipa a){
    free(a->nome);
    free(a);
}