#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "constantes.h"
#include "tabelas_dispersao.h"
#include "comandos.h"
#include "listas.h"

/* Funcao de Dispersao */
int hash(char *v, int M){

    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}


/* Verifica se a tabela equipa eh vazia. */
int eh_vazia_tabela_equipa(const tabela_equipa* tabela, int M){
    
    int i = 0;
    for(i = 0; i < M; i++){
        if(tabela->cabecas_eq[i] != NULL){
            return 0;
        }
    }
    return 1;
}

/* Verifica se a tabela jogo eh vazia. */
int eh_vazia_tabela_jogo(const tabela_jogo* tabela, int MJ){
    
    int i = 0;
    for(i = 0; i < MJ; i++){
        if(tabela->cabecas_jg[i] != NULL){
            return 0;
        }
    }
    return 1;
}



/* Cria tabela de dispersao de equipas. */
tabela_equipa* cria_tabela_equipa(int M){

    int i = 0;
    /* Aloca memoria para struct tabela_equipa. */
    tabela_equipa* novaTabela = (tabela_equipa*) can_fail_malloc(sizeof(tabela_equipa));

    /* Aloca memoria para os M ponteiros de lista_equipa. */
    lista_equipa** cabecas = (lista_equipa**) can_fail_malloc(sizeof(lista_equipa*) * M);
    for (i = 0; i < M; i++){
        cabecas[i] = NULL;
    }
    novaTabela->cabecas_eq = &cabecas[0];
    return novaTabela;
}

/* Cria tabela de dispersao de jogos. */
tabela_jogo* cria_tabela_jogo(int MJ){

    int i = 0;
    /* Aloca memoria para struct tabela_jogo. */
    tabela_jogo* novaTabela = (tabela_jogo*) can_fail_malloc(sizeof(tabela_jogo));

    /* Aloca memoria para os MJ ponteiros de lista_equipa. */
    lista** cabecas = (lista**) can_fail_malloc(sizeof(lista*) * MJ);
    for (i = 0; i < MJ; i++){
        cabecas[i] = NULL;
    }
    novaTabela->cabecas_jg = &cabecas[0];
    return novaTabela;
}



/* Liberta toda a memoria associada a uma tabela_equipa (struct tabela_equipa) */
void liberta_tabela_equipa(tabela_equipa* tab_libertar, int M){
   
    int i = 0;
    /* Liberta toda a memoria associada as lista de equipas. */
    for (i = 0; i < M; i++){
        if(tab_libertar->cabecas_eq[i] != NULL){
            liberta_lista_equipa(tab_libertar->cabecas_eq[i]);
        }
    }
    free(tab_libertar->cabecas_eq);
    free(tab_libertar);
    return;
}

/* Liberta toda a memoria associada a uma tabela_jogo (struct tabela_jogo) */
void liberta_tabela_jogo(tabela_jogo* tab_libertar, int MJ){
   
    int i = 0;
    /* Liberta toda a memoria associada as lista de jogos. */
    for (i = 0; i < MJ; i++){
        if(tab_libertar->cabecas_jg[i] != NULL){
            liberta_lista_jogo(tab_libertar->cabecas_jg[i]);
        }
    }
    free(tab_libertar->cabecas_jg);
    free(tab_libertar);
    return;
}



/* Retorna ponteiro para lista_equipa inserida ou cria caso nao exista a lista. */
lista_equipa* insere_ou_cria_lista_equipa(tabela_equipa* tabela, char *equipa, int M){

    /* Seleciona indice do vetor cabecas_eq*/
    int indice = hash(equipa, M);
    if(tabela->cabecas_eq[indice] != NULL){
       return tabela->cabecas_eq[indice];
    }
    else{
        /* Cria nova lista de equipa vazia. */
        tabela->cabecas_eq[indice] = cria_lista_equipa();
        return tabela->cabecas_eq[indice];
    }
    puts("insere_lista_equipa: Erro\n");
}

/* Retorna ponteiro para lista_equipa pesquisada ou NULL caso nao exista a lista. */
lista_equipa* pesquisa_lista_equipa(tabela_equipa* tabela, char* equipa, int M){

    /* Seleciona indice do vetor cabecas_eq*/
    int indice = hash(equipa, M);
    return tabela->cabecas_eq[indice];
}

/* Retorna ponteiro para lista inserida ou cria caso nao exista a lista. */
lista* insere_ou_cria_lista_jogo(tabela_jogo* tabela, char *jogo, int MJ){

    /* Seleciona indice do vetor cabecas_eq*/
    int indice = hash(jogo, MJ);
    if(tabela->cabecas_jg[indice] != NULL){
       return tabela->cabecas_jg[indice];
    }
    else{
        /* Cria nova lista de equipa vazia. */
        tabela->cabecas_jg[indice] = cria_lista();
        return tabela->cabecas_jg[indice];
    }
    puts("insere_lista_equipa: Erro\n");
}

/* Retorna ponteiro para lista_equipa pesquisada ou NULL caso nao exista a lista. */
lista* pesquisa_lista_jogo(tabela_jogo* tabela, char* jogo, int MJ){

    /* Seleciona indice do vetor cabecas_eq*/
    int indice = hash(jogo, MJ);
    return tabela->cabecas_jg[indice];
}



/* Retorna quantidade de equipas com max_vitorias */
int retorna_contador_max_vitorias_tabela(const tabela_equipa* tabela, int M, \
                                            int max_vitorias){

    int i, contador_vitorias = 0;
    lista_equipa* lista;

    /* Verifica se a tabela equipa eh vazia. */
    if(!eh_vazia_tabela_equipa(tabela, M)){

        for(i = 0; i < M; i++){

            if(tabela->cabecas_eq[i] != NULL){

                lista = tabela->cabecas_eq[i];
                /* Verifica se a lista equipa eh vazia. */
                if(!eh_vazia_equipa(lista)){
                    /* Retorna quantidade de equipas com max_vitorias */
                    contador_vitorias += Retorna_contador_max_vitorias(lista, max_vitorias);
                }
            }
        }
    }
    return contador_vitorias;
}

/* Retorna o valor de max_vitorias */
int retorna_max_vitorias_tabela(const tabela_equipa* tabela, int M){

    int i, maximo = 0, maximo_vitorias = 0;
    lista_equipa* lista;

    /* Verifica se a tabela equipa eh vazia. */
    if(!eh_vazia_tabela_equipa(tabela, M)){

        for(i = 0; i < M; i++){

            if(tabela->cabecas_eq[i] != NULL){

                lista = tabela->cabecas_eq[i];
                /* Verifica se a lista equipa eh vazia. */
                if(!eh_vazia_equipa(lista)){
                    /* Retorna o valor de max_vitorias */
                    maximo = Retorna_max_vitorias(lista);
                    if(maximo > maximo_vitorias){
                        /* Atualiza o valor de max_vitorias se necessario. */
                        maximo_vitorias = maximo;
                    }
                }
            }
        }
    }
    return maximo_vitorias;
}

