#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JogoLincado.h"
#include "EquipaLincada.h"

#define MAXIMONOME 1024

/* Funcao que adiciona um jogo ao sistema. */
int casoa(int NL, htJ_t *htJ, htE_t *htE, lista_jogo *listaJogos, int indexJogos){
    char nome[MAXIMONOME], equipa1nome[MAXIMONOME], equipa2nome[MAXIMONOME];
    int pontuacao1, pontuacao2;
    Jogo *jogo;
    Equipa *equipa1;
    Equipa *equipa2;
    scanf("%[^:]:%[^:]:%[^:]:%d:%d", nome, equipa1nome, equipa2nome, &pontuacao1, &pontuacao2);
    equipa1 = obter_htE(htE, equipa1nome);
    equipa2 = obter_htE(htE, equipa2nome);
    if (obter_htJ(htJ, nome)){ printf("%d Jogo existente.\n", NL); }
    else if (!equipa1 || !equipa2){ printf("%d Equipa inexistente.\n", NL); }
    else{
        jogo = novoJogo(nome, equipa1, equipa2, pontuacao1, pontuacao2);
        /* Verificacao de qual equipa ganhou o jogo (ou se foi um empate). */
        if (pontuacao1 > pontuacao2) { equipa1 -> vitorias++; jogo -> vitoriosa = equipa1; }
        else if (pontuacao2 > pontuacao1) { equipa2 -> vitorias++; jogo -> vitoriosa = equipa2; }
        else { jogo -> vitoriosa = NULL; }
        /* Adiciona o jogo na hashtable e na lista lincada de jogos. */
        adicionar_ultimo_jogo(listaJogos, jogo);
        apropriar_htJ(htJ, nome, jogo);
        /* Retorna o index incrementado para adicionar ao numero de jogos no sistema. */
        return indexJogos + 1;
    }
    return indexJogos;
}

/* Funcao que adiciona uma equipa ao sistema. */
int casoA(int NL, htE_t *htE, lista_equipa *listaEquipas, int indexEquipas){
    Equipa *equipa;
    char nome[MAXIMONOME];
    scanf("%[^\n]", nome);
    if (obter_htE(htE, nome)) { printf("%d Equipa existente.\n", NL); }
    else{
        equipa = novaEquipa(nome);
        adicionar_ultimo_equipa(listaEquipas, equipa);
        apropriar_htE(htE, nome, equipa);
        return indexEquipas + 1;
    }
    return indexEquipas;
}

/* Funcao que lista todo os jogos introduzidos, por nome, equipas e seus respectivos pontos. */
void casol(int NL, lista_jogo* listaJogos){
    Jogo *jogo;
    no_jogo* no = listaJogos -> cabeca;
    /* Percorre a lista de jogos e imprimi cada jogo ate o no apontar para NULL. */
    while (no != NULL){
        jogo = no -> jogo;
        no = no -> prox;
        printf("%d %s %s %s %d %d\n", NL, jogo -> nome, jogo -> equipa1 -> nome, jogo -> equipa2 -> nome, jogo -> pontuacao[0], jogo -> pontuacao[1]);
    }
}

/* Funcao que procura um jogo com um nome dado. */
void casop(int NL, htJ_t *htJ){
    char nome[MAXIMONOME];
    Jogo *jogo;
    scanf("%[^\n]", nome);
    jogo = obter_htJ(htJ, nome);
    if (!jogo) { printf("%d Jogo inexistente.\n", NL); }
    else {
        printf("%d %s %s %s %d %d\n", NL, jogo -> nome, jogo -> equipa1 -> nome, jogo -> equipa2 -> nome, jogo -> pontuacao[0], jogo -> pontuacao[1]);
    }
}

/* Funcao que procura uma equipa com um nome dado. */
void casoP(int NL, htE_t *htE){
    char nome[MAXIMONOME];
    Equipa *equipa;
    scanf("%[^\n]", nome);
    equipa = obter_htE(htE, nome);
    if (!equipa) { printf("%d Equipa inexistente.\n", NL); }
    else {
        printf("%d %s %d\n", NL, equipa -> nome, equipa -> vitorias);
    }
}

/* Funcao que apaga um jogo da hashtable e lista lincada de jogos, dado u, nome. */
int casor(int NL, htJ_t *htJ, htE_t *htE, lista_jogo* listaJogos, int indexJogos){
    char nome[MAXIMONOME];
    Jogo *jogo;
    Equipa *vitoriosa;
    no_jogo *no = listaJogos -> cabeca;
    scanf("%[^\n]", nome);
    jogo = obter_htJ(htJ, nome);
    if (!jogo) { printf("%d Jogo inexistente.\n", NL); return indexJogos; }
    else {
        if (jogo -> vitoriosa != NULL) {
            vitoriosa = obter_htE(htE, jogo -> vitoriosa -> nome);
            vitoriosa -> vitorias--;
        }
        htJ_del(htJ, nome);
        /* Percorre a lista de jogos ate achar o jogo correspondente com a entrada. */
        while (strcmp(no->jogo->nome, jogo->nome) != 0) no = no->prox;
        remover_no_jogo(listaJogos, no);
        /* Retorna o index decrementado do sistema se o jogo eh removido. */
        return indexJogos - 1;
    }
}

/* Funcao que altera o placar de um jogo, dado seu nome. */
void casos(int NL, htJ_t *htJ, htE_t *htE){
    Jogo *jogo;
    Equipa *novaVitoriosa = NULL, *antiga, *nova;
    char nome[MAXIMONOME];
    int pontuacao1, pontuacao2;
    scanf("%[^:]:%d:%d\n", nome, &pontuacao1, &pontuacao2);
    jogo = obter_htJ(htJ, nome);
    if (!jogo) { printf("%d Jogo inexistente.\n", NL); }
    else {
        /* Pbtem a equipa vitoriosa depois da mudanca de pontuacao. */
        if (pontuacao1 > pontuacao2) { novaVitoriosa = jogo -> equipa1; }
        else if (pontuacao2 > pontuacao1) { novaVitoriosa = jogo -> equipa2; }
        else if (pontuacao1 == pontuacao2) { novaVitoriosa = NULL; }
        /* Muda a pontuacao do jogo no sistema. */
        jogo -> pontuacao[0] = pontuacao1;
        jogo -> pontuacao[1] = pontuacao2;
        /* Verifica houve uma mudanca no time vencedor do jogo. */
        if (novaVitoriosa != jogo -> vitoriosa) {
            /* Se nao for um empate, incrementa o numero de vitorias na nova equipa vencedora. */
            if (novaVitoriosa != NULL) {
                nova = obter_htE(htE, novaVitoriosa -> nome);
                nova -> vitorias++;
            }
            /* Se houvesse anteriormente um vencedor, diminui as suas vitorias. */
            if (jogo -> vitoriosa != NULL) {
                antiga = obter_htE(htE, jogo -> vitoriosa -> nome);
                antiga -> vitorias--;
            }
            jogo -> vitoriosa = novaVitoriosa;
        }
    }
}

/* Funcao que encontra as equipas que ganharam mais jogos e lista por ordem alfabetica. */
void casog(int NL, lista_equipa *listaEquipas, int indexEquipas) {
    int i = 0, j, indexVitorioso = 0, maiorVitorias = 0;
    char **melhores = malloc(sizeof(char*) * indexEquipas), *temp;
    Equipa *ponte;
    no_equipa *no;
    /* Verifica se tem esquipas no sistema. */
    if (indexEquipas > 0) {
        no = listaEquipas -> cabeca;
        /* Itera sobre as equipas para obter o maior numero de vitorias entre as equipas. */
        while (no != NULL){
            ponte = no -> equipa;
            if (ponte -> vitorias > maiorVitorias) maiorVitorias = ponte -> vitorias;
            else no = no -> prox;
        }
        no = listaEquipas -> cabeca;
        /* Loop que obtem as equipas com o maior numero de vitorias no sistema e adiciona a lista local. */
        while (no != NULL) {
            ponte = no -> equipa;
            if (ponte -> vitorias == maiorVitorias) { melhores[indexVitorioso++] = ponte -> nome; }
            no = no -> prox;
        }
        /* Algaritmo de ordenacao por selecao que organiza as equipas da lista local por ordem alfabetica. */
        for (i = 0; i < indexVitorioso - 1; i++) {
            for (j = i + 1; j < indexVitorioso; j++) {
                if (strcmp(melhores[i], melhores[j]) > 0) {
                    temp = melhores[i];
                    melhores[i] = melhores[j];
                    melhores[j] = temp;
                }
            }
        }
        printf("%d Melhores %d\n", NL, maiorVitorias);
        for (i = 0; i < indexVitorioso; i++){
            printf("%d * %s\n", NL, melhores[i]);
        }
        
    }
    free(melhores);
}


void liberar_hash_jogo(htJ_t* ht) {
    int i;
    entradaJ_t* tmp, * aux;
    for (i = 0; i < TAMANHO_TABELA; i++)
        for (tmp = ht -> entradas[i]; tmp != NULL; tmp = aux) {
            aux = tmp -> proxJ;
            free(tmp -> chaveJ);
            free(tmp);
        }
    free(ht->entradas);
    free(ht);
}

void liberar_hash_equipa(htE_t* ht) {
    int i;
    entradaE_t* tmp, * aux;
    for (i = 0; i < TAMANHO_TABELA; i++)
        for (tmp = ht -> entradas[i]; tmp != NULL; tmp = aux) {
            aux = tmp -> proxE;
            free(tmp -> chaveE);
            free(tmp);
        }
    free(ht->entradas);
    free(ht);
}


int main(){
    int NL = 0;
    /* Variaveis que acompanham o numero de jogos e equipas no sistema. */
    int indexJogos = 0, indexEquipas = 0;
    char caso = '\0';
    htJ_t *htJogos = criar_htJ();
    htE_t *htEquipas = criar_htE();
    lista_jogo* listaJogos = gerar_lista_jogo();
    lista_equipa* listaEquipas = gerar_lista_equipa();
    scanf("%c ", &caso);
    while (caso != 'x'){
        NL++;
        switch(caso){
            case 'a':
                indexJogos = casoa(NL, htJogos, htEquipas, listaJogos, indexJogos);
                break;
            
            case 'A':
                indexEquipas = casoA(NL, htEquipas, listaEquipas, indexEquipas);
                break;
            
            case 'l':
                casol(NL, listaJogos);
                break;
                
            case 'p':
                casop(NL, htJogos);
                break;
                
            case 'P':
                casoP(NL, htEquipas);
                break;
                
            case 'r':
                indexJogos = casor(NL, htJogos, htEquipas, listaJogos, indexJogos);
                break;
            
            case 's':
                casos(NL, htJogos, htEquipas);
                break;
            
            case 'g':
                casog(NL, listaEquipas, indexEquipas);
                break;
        }
    scanf("\n%c ", &caso);
    }
    /* Funcoes que liberam a memoria alocada pelas hashtables e listas lincadas. */
    liberar_lista_jogo(listaJogos, indexJogos);
    liberar_lista_equipa(listaEquipas);
    liberar_hash_jogo(htJogos);
    liberar_hash_equipa(htEquipas);
    return 0;
}
