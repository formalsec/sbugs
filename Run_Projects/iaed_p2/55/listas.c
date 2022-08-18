#include "listas.h"
#include "estruturas.h"


/* Cria nova lista de equipa vazia. */
lista_equipa* cria_lista_equipa(){
    /* Aloca memoria para struct estr_equipa. */
    lista_equipa* novaLista = (lista_equipa*) malloc(sizeof(lista_equipa));
    if (novaLista == NULL)      /* Verifica alocacao de memoria. */
        puts("cria_lista: Error. malloc returned NULL\n");
    novaLista->inicio = NULL;   /* Inicializa inicio. */
    novaLista->fim = NULL;      /* Inicializa fim. */
    return novaLista;           /* Retorna ponteiro para a lista criada. */
}

/* Cria nova lista vazia. */
lista* cria_lista(){
    /* Aloca memoria para struct estr_jogo. */
    lista* novaLista = (lista*) malloc(sizeof(lista));
    if (novaLista == NULL)      /* Verifica alocacao de memoria. */
        puts("cria_lista: Error. malloc returned NULL\n");
    novaLista->inicio = NULL;   /* Inicializa inicio. */
    novaLista->fim = NULL;      /* Inicializa fim. */

    return novaLista;           /* Retorna ponteiro para a lista criada. */
}

/* Cria nova lista ponteiros vazia. */
lista_ponteiro* cria_lista_ponteiros(){
    /* Aloca memoria para struct estr_ptr. */
    lista_ponteiro* novaLista = (lista_ponteiro*) malloc(sizeof(lista_ponteiro));
    if (novaLista == NULL)      /* Verifica alocacao de memoria. */
        puts("cria_lista: Error. malloc returned NULL\n");
    novaLista->inicio = NULL;   /* Inicializa inicio. */
    novaLista->fim = NULL;      /* Inicializa fim. */

    return novaLista;           /* Retorna ponteiro para a lista criada. */
}



/* Verifica se a lista equipa eh vazia. */
int eh_vazia_equipa(const lista_equipa* l){
    return (l->inicio == NULL && l->fim == NULL);
}

/* Verifica se a lista eh vazia. */
int eh_vazia(const lista* l){
    return (l->inicio == NULL && l->fim == NULL);
}

/* Verifica se a lista ponteiros eh vazia. */
int eh_vazia_ponteiros(const lista_ponteiro* l){
    return (l->inicio == NULL && l->fim == NULL);
}



/* Adiciona um no_equipa (struct estr_equipa) como o ultimo elemento da lista. */
void adiciona_equipa_fim(lista_equipa* l, elo_equipa novo_no){

    /* Adiciona em lista vazia. */
    if(l->inicio == NULL && l->fim == NULL){
        if(DEBUG)
            puts("Lista vazia");
        l->inicio = novo_no;
        l->fim = novo_no;
        /*
        novo_no->anterior = NULL;
        */
        novo_no->proximo = NULL;
    }
    /* Adiciona em lista nao vazia. */
    else{
        if(DEBUG)
            puts("Lista com elemento");
            /*
        novo_no->anterior = l->fim;
        */
        novo_no->proximo = NULL;
        l->fim->proximo = novo_no;
        l->fim = novo_no;
    }
    return;
}   

/* Adiciona um no_jogo (struct estr_jogo) como o ultimo elemento da lista. */
void adiciona_fim(lista* l, elo_jogo novo_no){

    if(l->inicio == NULL && l->fim == NULL){
        if(DEBUG)
            puts("Lista vazia");
        l->inicio = novo_no;
        l->fim = novo_no;
        /*
        novo_no->anterior = NULL;
        */
        novo_no->proximo = NULL;
    }
    else{
        if(DEBUG)
            puts("Lista com elemento");
            /*
        novo_no->anterior = l->fim;
        */
        l->fim->proximo = novo_no;
        l->fim = novo_no;
        novo_no->proximo = NULL;
    }
    return;
}   

/* Adiciona no ponteiro (struct estr_ptr) como o ultimo elemento da lista. */
void adiciona_fim_ponteiro(lista_ponteiro* l, elo_ponteiro novo_no){

    if(l->inicio == NULL && l->fim == NULL){
        if(DEBUG)
            puts("Lista vazia");
        l->inicio = novo_no;
        l->fim = novo_no;
        /*
        novo_no->anterior = NULL;
        */
        novo_no->proximo = NULL;
    }
    else{
        if(DEBUG)
            puts("Lista com elemento");
            /*
        novo_no->anterior = l->fim;
        */
        l->fim->proximo = novo_no;
        l->fim = novo_no;
        novo_no->proximo = NULL;
    }
    return;
}   

/* Adiciona um no_jogo (struct estr_jogo) como o primeiro elemento da lista. */
void adiciona_inicio(lista* l, elo_jogo novo_no){

    if(l->inicio == NULL && l->fim == NULL){
        if(DEBUG)
            puts("Lista vazia");
        l->inicio = novo_no;
        l->fim = novo_no;
        /*
        novo_no->anterior = NULL;
        */
        novo_no->proximo = NULL;
    }
    else{
        if(DEBUG)
            puts("Lista com elemento");
        novo_no->proximo = l->inicio;
        /*
        l->inicio->anterior = novo_no;
        */
        l->inicio = novo_no;
        /*
        novo_no->anterior = NULL;
        */
    }
    return;
}



/* Remove um no_equipa (struct estr_equipa). */
void remove_no_equipa(lista_equipa* l, elo_equipa no){

    elo_equipa no_velho = no;

    /* eh_vazia verifica se inicio e fim da lista sao NULL. */
    if(!eh_vazia_equipa(l)){
        /* Verifica se ha somente um no_jogo na lista. */
        if(l->inicio == l->fim){
            liberta_no_equipa(no);
            l->inicio = NULL;
            l->fim = NULL;
        }
        /* Remove o primeito no-jogo da lista. */
        else if(l->inicio == no){
            if(DEBUG)
            printf("Remove primeiro da lista\n");
            l->inicio = no->proximo;
            /*
            no->proximo->anterior = NULL;
            */
            liberta_no_equipa(no_velho);
        }
        /* Remove o ultimo no-jogo da lista. */
        else if(l->fim == no){
            if(DEBUG)
            printf("Remove ultimo da lista\n");
            /*
            l->fim = no->anterior;
            no->anterior->proximo = NULL;
            */
            liberta_no_equipa(no_velho);
        }
        /* Lista com mais de 2 no_jogo. */
        else{
            /*
            no->anterior->proximo = no->proximo;
            no->proximo->anterior = no->anterior;
            */
            liberta_no_equipa(no_velho);
        }
        return;
    }
    return;
}

/* Remove um no_jogo (struct estr_jogo). */
void remove_no_jogo(lista* l, elo_jogo no){

    char* jogo = *(no->jogo);
    elo_jogo no_velho = no;

    elo_jogo seguidor = NULL;
    elo_jogo t = l->inicio;

    /* eh_vazia verifica se inicio e fim da lista sao NULL. */
    if(!eh_vazia(l)){
        /* Verifica se ha somente um no_jogo na lista. */
        if(l->inicio == l->fim){
            liberta_no_jogo(no);
            l->inicio = NULL;
            l->fim = NULL;
            return;
        }
        /* Remove o primeito no-jogo da lista. */
        if(l->inicio == no){
            if(DEBUG)
                printf("Remove primeiro da lista\n");
            l->inicio = no->proximo;
            liberta_no_jogo(no_velho);
            return;
        }

        for(t = l->inicio, seguidor = NULL; t != NULL; \
                seguidor = t, t = t->proximo) {

            if(strcmp(*(t->jogo), jogo) == 0) {
                if(t == l->inicio)
                    l->inicio = t->proximo;
                else if(t == l->fim){
                    l->fim = seguidor;
                    seguidor->proximo = NULL;
                }
                else
                    seguidor->proximo = t->proximo;
            
                liberta_no_jogo(t);
                return;
            }
        }
        return;
    }
    puts("remove_no_jogo: Erro -> argumento eh lista vazia\n");
    return;
}

/* Remove um no_ponteiro (struct estr_ptr). */
void remove_no_ponteiro(lista_ponteiro* l, elo_ponteiro no){

    char* jogo = *(no->ponteiro->jogo);
    elo_ponteiro no_velho = no;

    elo_ponteiro seguidor = NULL;
    elo_ponteiro t = l->inicio;

    /* eh_vazia verifica se inicio e fim da lista sao NULL. */
    if(!eh_vazia_ponteiros(l)){
        /* Verifica se ha somente um no_jogo na lista. */
        if(l->inicio == l->fim){
            liberta_no_ponteiro(no);
            l->inicio = NULL;
            l->fim = NULL;
            return;
        }
        /* Remove o primeito no-jogo da lista. */
        if(l->inicio == no){
            if(DEBUG)
                printf("Remove primeiro da lista\n");
            l->inicio = no->proximo;
            liberta_no_ponteiro(no_velho);
            return;
        }

        for(t = l->inicio, seguidor = NULL; t != NULL; \
                seguidor = t, t = t->proximo) {

            if(strcmp(*(t->ponteiro->jogo), jogo) == 0) {

                if(t == l->inicio)
                    l->inicio = t->proximo;
                else if(t == l->fim){
                    l->fim = seguidor;
                    seguidor->proximo = NULL;
                }
                else
                    seguidor->proximo = t->proximo;

                liberta_no_ponteiro(t);
                return;
            }
        }
        return;
    }
    puts("remove_no_ponteiro: Erro -> argumento eh lista vazia\n");
    return;
}

/* Retorna o valor de max_vitorias */
int Retorna_max_vitorias(const lista_equipa* le){

    int max_vitorias = 0;
    elo_equipa inicio = le->inicio;

    if(!eh_vazia_equipa(le)){
        
    /* Verifica o maior valor de vitorias e guarda em max_vitorias. */
        while (inicio != NULL){
            if(*(inicio->vitorias) > max_vitorias){
                max_vitorias = *(inicio->vitorias);
            }
            inicio = inicio->proximo;
        }
        return max_vitorias;
    }
    return 0;
}

/* Retorna quantidade de equipas com max_vitorias */
int Retorna_contador_max_vitorias(const lista_equipa* le, int max_vitorias){

    int contador_vitorias = 0;
    elo_equipa inicio = le->inicio;

    if(!eh_vazia_equipa(le)){
        
    /* Incrementa contador quando numero de vitorias igual a max_vitorias. */
        while (inicio != NULL){
            if(*(inicio->vitorias) == max_vitorias){
                contador_vitorias++;
            }
            if(*(inicio->vitorias) > max_vitorias){
                printf("Erro RRRRetorna_max_vitorias: vitorias > max_vitorias\n");
            }
            inicio = inicio->proximo;
        }
        return contador_vitorias;
    }
    return 0;
}



/* Procura um no_equipa (struct estr_equipa). */
elo_equipa procura_no_equipa(const lista_equipa* le, char* equipa){

    elo_equipa inicio = le->inicio;

    if(!eh_vazia_equipa(le)){
        while (inicio != NULL){
            if((strcmp(*(inicio->equipa), equipa)) == 0){
                return inicio;
            }
            inicio = inicio->proximo;
        }
        return NULL;
    }
    return NULL;
}

/* Procura um no_jogo (struct estr_jogo). */
elo_jogo procura_no_jogo(const lista* l, char* jogo){

    elo_jogo inicio = l->inicio;

    if(!eh_vazia(l)){
        while (inicio != NULL){
            if((strcmp(*(inicio->jogo), jogo)) == 0){
                return inicio;
            }
            inicio = inicio->proximo;
        }
        return NULL;
    }
    return NULL;
}



/* Altera o numero de vitorias das Equipas. Jogo com empates. */
void altera_vitorias_empate(int s1, int s2, int s1v, int s2v, \
                             elo_equipa no1, elo_equipa n2){

    int score1 = s1, score2 = s2, score_velho1 = s1v, score_velho2 = s2v;
    elo_equipa No_equipa1 = no1, No_equipa2 = n2;

    /* Havia empate, agora equipa1 venceu. */
    if((score_velho1 == score_velho2) && (score1 > score2)){
        *(No_equipa1->vitorias) += 1;
        return;
    }       
    /* Havia empate, agora equipa2 venceu. */
    if((score_velho1 == score_velho2) && (score1 < score2)){
        *(No_equipa2->vitorias) += 1;
        return;
    }
}

/* Altera o numero de vitorias das Equipas. Jogo como vitorias Equipa1. */
void altera_vitorias_equipa1(int s1, int s2, int s1v, int s2v, \
                              elo_equipa no1, elo_equipa n2){

    int score1 = s1, score2 = s2, score_velho1 = s1v, score_velho2 = s2v;
    elo_equipa No_equipa1 = no1, No_equipa2 = n2;

    /* Equipa1 havia vencido, agora empatou. */
    if((score_velho1 > score_velho2) && (score1 == score2)){
        *(No_equipa1->vitorias) -= 1; 
        return;
    }
    /* Equipa1 havia vencido, agora equipa2 venceu. */
    if((score_velho1 > score_velho2) && (score1 < score2)){
        *(No_equipa1->vitorias) -= 1; 
        *(No_equipa2->vitorias) += 1; 
        return;
    }
    return;
}

/* Altera o numero de vitorias das Equipas. Jogo como vitorias Equipa2. */
void altera_vitorias_equipa2(int s1, int s2, int s1v, int s2v, \
                                elo_equipa no1, elo_equipa n2){

    int score1 = s1, score2 = s2, score_velho1 = s1v, score_velho2 = s2v;
    elo_equipa No_equipa1 = no1, No_equipa2 = n2;

    /* Equipa2 havia vencido, agora empatou. */
    if((score_velho1 < score_velho2) && (score1 == score2)){
        *(No_equipa2->vitorias) -= 1;
        return;
    }
    /* Equipa2 havia vencido, agora equipa1 venceu. */
    if((score_velho1 < score_velho2) && (score1 > score2)){
        *(No_equipa1->vitorias) += 1; 
        *(No_equipa2->vitorias) -= 1; 
        return;
    }
}

/* Altera score de um no_jogo (struct estr_jogo). */
void altera_score(int score1, int score2, elo_jogo no){
    *(no->score1) = score1;
    *(no->score2) = score2;
    return;
}



/* Liberta toda a memoria associada a lista de equipas. */
void liberta_lista_equipa(lista_equipa* l){

    lista_equipa* lista_velha = l;
    elo_equipa inicio = l->inicio;
    elo_equipa no_velho;

    while(inicio != NULL){
        no_velho = inicio;
        inicio = inicio->proximo;
        liberta_no_equipa(no_velho);
    }
    free(lista_velha);
    return;
}

/* Liberta toda a memoria associada a lista de jogos. */
void liberta_lista_jogo(lista* l){

    lista* lista_velha = l;
    elo_jogo inicio = l->inicio;
    elo_jogo no_velho;

    while(inicio != NULL){
        no_velho = inicio;
        inicio = inicio->proximo;
        liberta_no_jogo(no_velho);
    }
    free(lista_velha);
    return;
}

/* Liberta toda a memoria associada a lista de jogos. */
void liberta_lista_ponteiro(lista_ponteiro* l){

    lista_ponteiro* lista_velha = l;
    elo_ponteiro inicio = l->inicio;
    elo_ponteiro no_velho;

    while(inicio != NULL){
        no_velho = inicio;
        inicio = inicio->proximo;
        liberta_no_ponteiro(no_velho);
    }
    free(lista_velha);
    return;
}