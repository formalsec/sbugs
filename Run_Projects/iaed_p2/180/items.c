#include "items.h"

/* liberta memoria da equipa introduzido */
void liberta_mem_equipa(linkEquipa equipa) {
    free(equipa->nome);
    free(equipa);
}

/* liberta memoria do jogo introduzido */
void liberta_mem_jogo(linkJogo jogo) {
    free(jogo->nome);
    free(jogo->eq1);
    free(jogo->eq2);
    free(jogo);
}

/* procura equipa na lista */
linkEquipa procura_equipa_item (linkEquipa head_equipas, char* nome) {
    linkEquipa i;
    /* procura equipa com mesmo nome */
    for (i = head_equipas; i != NULL; i = i->next)
        if (strcmp(i->nome,nome) == 0)
            return i;
    return NULL;
}

/* cria e aloca espaco para nova equipa */
linkEquipa nova_equipa (char *nome) {
    /* aloca espaco e inicializa uma nova equipa */
    linkEquipa nv_eq = (linkEquipa)malloc(sizeof(struct nodeEquipa));
    nv_eq->nome = (char*)malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(nv_eq->nome, nome);
    nv_eq->vitorias = 0;
    nv_eq->next = NULL;
    return nv_eq;
}

/* coloca equipa na lista */
linkEquipa coloca_equipa (linkEquipa head_equipas, char *nome) {
    /* cria nova equipa e insere na lista */
    linkEquipa nv_eq = nova_equipa(nome);
    nv_eq->next = head_equipas;
    return nv_eq;
}

/* procura jogo na lista */
linkJogo procura_jogo_item (linkJogo head_jogos, char* nome) {
    /* procura jogo com mesmo nome */
    linkJogo i;
    for (i = head_jogos; i != NULL; i = i->next)
        if (strcmp(i->nome,nome) == 0)
            return i;
    return NULL;
}

/* cria e aloca espaco para novo jogo */
linkJogo novo_jogo (char *nome, char *eq1, char *eq2, int s1, int s2) {
    /* aloca espaco e inicializa um novo jogo */
    linkJogo nv_jg = (linkJogo)malloc(sizeof(struct nodeJogo));
    nv_jg->nome = (char*)malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(nv_jg->nome, nome);
    nv_jg->eq1 = (char*)malloc(sizeof(char)*(strlen(eq1)+1));
    strcpy(nv_jg->eq1, eq1);
    nv_jg->eq2 = (char*)malloc(sizeof(char)*(strlen(eq2)+1));
    strcpy(nv_jg->eq2, eq2);
    nv_jg->s1 = s1;
    nv_jg->s2 = s2;
    return nv_jg;
}

/* coloca jogo na lista */
linkJogo coloca_jogo (linkJogo head_jogos, char *nome,
                      char *eq1, char *eq2, int s1, int s2) {
    /* cria novo jogo e insere na lista */
    linkJogo nv_jg = novo_jogo (nome,eq1,eq2,s1,s2);
    nv_jg->next = head_jogos;
    return nv_jg;
}   

/* remove jogo da lista */
linkJogo remove_jogo (linkJogo head_jogos, char *nome) {
    /* remove jogo com nome dado da lista */
    linkJogo i, ant;
    for(i = head_jogos, ant = NULL; i != NULL; ant = i, i = i->next) {
        if(strcmp(i->nome, nome) == 0) {            
            if(i == head_jogos)
                head_jogos = i->next;
            else
                ant->next = i->next;
            liberta_mem_jogo(i);
            break;
        }
    }
    return head_jogos;
}