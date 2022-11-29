#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "estruturas.h"


/* Cria/inicializa/retorna um no_equipa (struct estr_equipa). */
elo_equipa cria_no_equipa(char* equipa){

    elo_equipa novo_no = (elo_equipa) can_fail_malloc(sizeof(no_equipa));
    int* pt_vitorias = (int*) can_fail_malloc(sizeof(int));
    char** cc = (char**) can_fail_malloc(sizeof(char*) * 1);
    cc[0] = duplica_string(equipa);

    *pt_vitorias = 0;

    if (novo_no == NULL)         /* Verifica alocacao de memoria. */
        puts("cria_no_equipa: Erro. can_fail_malloc retornou NULL\n");

    novo_no->equipa = &cc[0];
    novo_no->vitorias = pt_vitorias; 
    novo_no->proximo = NULL;

    return novo_no;
}   

/* Cria/inicializa/retorna um no_jogo (struct estr_jogo). */
elo_jogo cria_no_jogo(char* jogo, char* equipa1, char* equipa2, int score1, int score2){

    elo_jogo novo_no = (elo_jogo) can_fail_malloc(sizeof(no_jogo));
    int* pt_score1 = (int*) can_fail_malloc(sizeof(int));
    int* pt_score2 = (int*) can_fail_malloc(sizeof(int));

    char** cc = (char**) can_fail_malloc(sizeof(char*) * 3);
    cc[0] = duplica_string(jogo);
    cc[1] = duplica_string(equipa1);
    cc[2] = duplica_string(equipa2);

    *pt_score1 = score1;
    *pt_score2 = score2;

    if (novo_no == NULL)         /* Verifica alocacao de memoria. */
        puts("cria_no_jogo: Erro. can_fail_malloc retornou NULL\n");

    novo_no->jogo = &cc[0];
    novo_no->equipa1 = &cc[1];
    novo_no->equipa2 = &cc[2];
    novo_no->score1 = pt_score1; 
    novo_no->score2 = pt_score2;
    novo_no->pt_no_ponteiro = NULL;
    novo_no->proximo = NULL;

    return novo_no;
}   

/* Cria/inicializa/retorna um no_ponteiro (struct estr_ptr). */
elo_ponteiro cria_no_ponteiro(elo_jogo pt_jogo){

    elo_ponteiro novo_no = (elo_ponteiro) can_fail_malloc(sizeof(no_ponteiro));
    if (novo_no == NULL)         /* Verifica alocacao de memoria. */
        puts("cria_no_ponteiro: Erro. can_fail_malloc retornou NULL\n");

    novo_no->ponteiro = pt_jogo;
    /*
    novo_no->anterior = NULL;
    */
    novo_no->proximo = NULL;

    return novo_no;
}  



/* Liberta toda a memoria associada a um no_equipa (struct estr_equipa) */
void liberta_no_equipa(elo_equipa no_libertar){
   
    free(*(no_libertar->equipa));
    free(no_libertar->equipa);
    free(no_libertar->vitorias);
    free(no_libertar);
    return;
}

/* Liberta toda a memoria associada a um no_jogo (struct estr_jogo) */
void liberta_no_jogo(elo_jogo no_libertar){
   
    free(*(no_libertar->jogo));
    free(*(no_libertar->equipa1));
    free(*(no_libertar->equipa2));
    free(no_libertar->jogo);
    free(no_libertar->score1);
    free(no_libertar->score2);
    free(no_libertar);
    return;
}

/* Liberta toda a memoria associada a um no_ponteiro (struct estr_ptr) */
void liberta_no_ponteiro(elo_ponteiro no_libertar){

    free(no_libertar);
    return;
}



/* Duplica string */
char* duplica_string(char* cadeia_caracteres){

    int tamanho = strlen(cadeia_caracteres) + 1;
    char* cc = (char*) can_fail_malloc(sizeof(char) * tamanho);

    if (cc == NULL){
        puts("duplica_string: Erro. can_fail_malloc retornou NULL\n");
        return NULL;
    }
    /*  return memcpy(cc, cadeia_caracteres, tamanho);  */
    strcpy(cc, cadeia_caracteres);
    return cc; 
}

