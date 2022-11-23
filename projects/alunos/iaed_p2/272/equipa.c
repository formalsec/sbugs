#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "equipa.h"
#include <stdio.h>
#include "hash.h"
#include <string.h>
#include <stdlib.h>

/* Funcao que adiciona uma equipa ao sistema das equipas */
void adiciona_equipa(struct Equipas*equipas,int comandos_total) {

    /* Chamada das variaveis que pretendemos usar */
    char nome[MAX_EQUIPA_NOME];
    int hash;
    struct Equipa *equipa;
    struct Equipa *nova_equipa;
    int nome_length;
    scanf(" %[^:\n]\n", nome);
    
    hash = hash_str(nome);
    /* Calculo da gaveta que pretendemos verificar */
    equipa = equipas->gavetas[hash % EQUIPA_GAVETAS];
    
    /* dentro da gaveta temos de verificar se essq equipa ja existia, ciclo while 
    para verificar todas as equipas na gaveta */
    while( equipa != NULL ) {

        /* No caso da equipa ja estar inserida na gaveta, printa o erro */
        if (strcmp(nome, equipa->nome) == 0) {
            printf("%d Equipa existente.\n", comandos_total);
            return;
        }

        /* No caso de se estar na ultima equipa da gaveta, faz break */
        if (equipa->next_equipa == NULL) {
            break;
        }
        /* Se a gaveta nao estiver vazia a equipa adicionada e colocada dentro dela */
        equipa = equipa->next_equipa;
    }
    
    /* Se fizer break, adicionar equipa no fim da gaveta */
    nome_length = strlen(nome); 
    /*  Alocamos a memoria para  nova equipa */
    nome_length = strlen(nome); 
    nova_equipa = can_fail_malloc(sizeof(struct Equipa)); 
    nome_length = strlen(nome); 
    /* Alocamos a memoria para o nome da equipa */
    nova_equipa -> nome = can_fail_malloc(sizeof(char) * (nome_length + 1)); 
    strcpy(nova_equipa->nome, nome);
    nova_equipa->wins = 0; /* Nova equipa comeca com 0 vitorias */
    /* Atualizamos o final da gaveta, sendo a nova equipa a ultima equipa e a proxima  
    equipa o NULL */
    nova_equipa->next_equipa = NULL; 
    
    /* Adicionamos memoria automaticamente para colocar a nova equipa no vetor 
    onde colocamos as equipas por ordem de entrada */
    equipas->ordem = can_fail_realloc(equipas->ordem, (equipas->nequipas + 1) * sizeof(struct Equipa));
    
    /* Nova equipa dentro do vetor*/
    equipas->ordem[ equipas->nequipas ] = nova_equipa;
    
    /* Aumentar o numero de equipas */
    equipas->nequipas += 1;

    /* Proxima equipa na gaveta e a nova equipa */
    if (equipa != NULL) {
        equipa->next_equipa = nova_equipa;
    }
    else {
        /* Colocar a nova equipa se a gaveta estiver vazia*/
        equipas->gavetas[hash % EQUIPA_GAVETAS] = nova_equipa;
    }
}

/* Funcao que recebe uma equipa e procura se essa equipa ja esta na base de dados, recebe uma equipa */
void procura_equipa(struct Equipas*equipas,int comandos_total){ 
    /* variaveis que pretendemos usar */
    char nome[MAX_EQUIPA_NOME];
    int hash;
    struct Equipa *equipa;
    /* Scanf do que nos e fornecido como informacao */
    scanf(" %[^:\n]", nome);
    /* Hash com o nome da equipa */
    hash = hash_str(nome);
    equipa = equipas->gavetas[hash % EQUIPA_GAVETAS];
    
    /* Ciclo while para verificarmos todos os elementos da gaveta */
    while ( equipa != NULL ) {
        /* Comparacao das strings, se a equipa estiver inserida, printamos o nome e as vitorias */
        if (strcmp(nome, equipa->nome) == 0) {
            printf("%d %s %d\n", comandos_total,
                equipa->nome,
                equipa->wins
            );
            return;
        }
        
        equipa = equipa->next_equipa;
    }
    /* Se a equipa nao existir, printamos o erro */
    
    printf("%d Equipa inexistente.\n", comandos_total);
}

/* Funcao auxiliar para o qsort */
int comparar_equipas(const void* equipa1, const void* equipa2) {
    /* equipa1 e `const struct Equipa**`, logo fazemos cast e dereferencianmos com o
       asterisco a esquerda, assim ficamos com um `const struct Equipa*`. Dai podemos
       aceder as wins. */
    if ( ( *(const struct Equipa**)equipa1 )->wins < ( *(const struct Equipa**)equipa2 )->wins ) {
        return 1;
    }
    if ( ( *(const struct Equipa**)equipa1 )->wins > ( *(const struct Equipa**)equipa2 )->wins ) {
        return -1;
    }
    
    return strcmp( ( *(const struct Equipa**)equipa1 )->nome, ( *(const struct Equipa**)equipa2 )->nome );
}

/* funcao que recebe as equipas e printa por ordem de quem tem mais wins, no caso de
terem o mesmo numero de wins, printa pela ordem lexicografica */
void melhores_equipas(struct Equipas*equipas,int comandos_total) {
    int wins;
    int n;
    /* Se o vetor das equipas estiver vazio*/
    if ( equipas->ordem == NULL ) {
        return;
    }
    
    /* No caso de nao ser vazio, faz sort das equipas pela ordem de vitorias e no caso de termos 
    equipas com o mesmo numero de vitorias, printa por ordem lexicografica */
    qsort(equipas->ordem, equipas->nequipas, sizeof(struct Equipa*), comparar_equipas);
    
    /* Acesso as vitorias da equipa que esta em primeiro no vetor de ordem de colocacao */
    wins = equipas->ordem[0]->wins;
    
    printf("%d Melhores %d\n", comandos_total, wins);
    
    /* Ciclo for que serve para verificar todas equipas dentro do vetor de ordem de colocacao
    na base de dados */
    for (n = 0; n < equipas->nequipas; n++) {
        /* Se a equipa que estivermos a ver tiver menos wins que o numero maximo de wins */
        if ( equipas->ordem[n]->wins < wins ) {
            return;
        }
        /* print das melhores equipas pela ordem pedida */
        printf("%d * %s\n", comandos_total, equipas->ordem[n]->nome);
    }
}
