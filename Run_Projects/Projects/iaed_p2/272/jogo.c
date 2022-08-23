#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>

/* Funcao que adiciona um jogo a base de dados */
void adiciona_jogo(struct Jogos*jogos, struct Equipas*equipas, int comandos_total) {
    /* Variaveis que pretendemos utilizar */
    /* Nomes dos jogos e das equipas */
    char nome[MAX_JOGO_NOME];
    char equipa1_nome[MAX_EQUIPA_NOME];
    char equipa2_nome[MAX_EQUIPA_NOME];
    /* Golos de caga uma das equipas */
    int golos1, golos2;

    /* Hash table para um jogo */
    int hash_nome, hash_equipa1, hash_equipa2;
    /* Ponteiros para o jogo e o proximo jogo */
    struct Jogo *jogo;
    struct Jogo *novo_jogo;
    struct Equipa *equipa1;
    struct Equipa *equipa2;
    int nome_length;
    
    /* Scanf das variaveis dadas */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1_nome, equipa2_nome, &golos1, &golos2);
    
    /* Nome do jogo */
    hash_nome = hash_str(nome);

    /* Gaveta onde o jogo esta inserido na hash table de jogos */
    jogo = jogos->gavetas[hash_nome % JOGO_GAVETAS];
    
    /* Ciclo while ate chegarmos ao fim da gaveta */
    while ( jogo != NULL ) {
        /* Se ao compararmos as strings elas forem iguais, o jogo ja existe na gaveta */
        if (strcmp(nome, jogo->nome) == 0) {
            printf("%d Jogo existente.\n", comandos_total);
            return;
        }
        /* Se o proximo jogo for NULL, fazemos break */
        if (jogo->next_jogo == NULL) {
            break;
        }
        /* Atualizamos os dados dentro da gaveta, o next jogo passa a ser o jogo dado */
        jogo = jogo->next_jogo;
    }
    
    /* Proximo segmento serve para comparar as equipas dentro do jogo */
    hash_equipa1 = hash_str(equipa1_nome);
    /* Gaveta que pretendemos verificar  */
    equipa1 = equipas->gavetas[hash_equipa1 % EQUIPA_GAVETAS];
    
    /* Ciclo while para ver todas as equipas dentro da gaveta */
    while ( equipa1 != NULL ) {
        /* Se a equipa ja estivr inserida na gaveta, fazemos break */
        if (strcmp(equipa1_nome, equipa1->nome) == 0) {
            break;
        }
        /* Se a gaveta equipa nao estiver vazia, adicionamos a equipa ao fim da gaveta*/
        equipa1 = equipa1->next_equipa;
    }
    /* Mesma coisa que o segmento anterior, mas para a segunda equipa dentro do jogo */
    hash_equipa2 = hash_str(equipa2_nome);
    
    equipa2 = equipas->gavetas[hash_equipa2 % EQUIPA_GAVETAS];
    while ( equipa2 != NULL ) {
        if (strcmp(equipa2_nome, equipa2->nome) == 0) {
            break;
        }
        equipa2 = equipa2->next_equipa;
    }
    
    /* No caso das equipas nao existirem, printa erro */
    if (equipa1 == NULL || equipa2 == NULL) {
        printf("%d Equipa inexistente.\n", comandos_total);
        return;
    }
    
    /* Se a primeira equipa tiver mais golos, gannhou o jogo, atualizamos as wins */
    if ( golos1 > golos2 ) {
        equipa1->wins++;
    }
    /* Mesma coisa mas para a equipa 2 */
    if ( golos1 < golos2 ) {
        equipa2->wins++;
    }
    
    /* Adicionamos o jogo a gaveta onde estamos colocados */
    /* Alocamos memoria para o novo jogo */
    novo_jogo = malloc(sizeof(struct Jogo));
    nome_length = strlen(nome);
    /* Alocamos memoria para o nome do jogo */
    novo_jogo->nome = malloc(sizeof(char) * (nome_length + 1));
   /* Copiamos o nome do novo jogo */
    strcpy(novo_jogo->nome, nome);
    /* Criamos as variaveis do jogo */ 
    novo_jogo->equipa1 = equipa1;
    novo_jogo->equipa2 = equipa2;
    novo_jogo->golos1  = golos1;
    novo_jogo->golos2  = golos2;
    /* Adicionamos o jogo ao fim da gaveta, pelo que o proximo jogo e NULL */
    novo_jogo->next_jogo = NULL;
    
    /* Realloc serve para reallocar memoria automaticamente ao vetor de forma
    a podermos colocar mais jogos */
    jogos->ordem = realloc(jogos->ordem, (jogos->njogos + 1) * sizeof(struct Jogo));
    
    /* Inserimos o novo jogo no vetor de ponteiros para a ordem de entrada dos 
    jogos na base de dados */
    jogos->ordem[ jogos->njogos ] = novo_jogo;
    
    /* Incrementamos 1 ao numero de jogos totais */
    jogos->njogos += 1;
    
    /* Proximo jogo na gaveta e o novo jogo */
    if (jogo != NULL) {
        jogo->next_jogo = novo_jogo;
    }
    /* No caso da gaveta estar vazia, coloca-se o novo jogo */
    else {
        jogos->gavetas[hash_nome % JOGO_GAVETAS] = novo_jogo;
    }
}

/* Funcao que recebe um jogo e procura na base de dados se esse jogo ja existe */
void procura_jogo(struct Jogos* jogos, int comandos_total) {
    /* Variaveis que pretendemos usar */
    char nome[MAX_JOGO_NOME];
    int hash;
    struct Jogo *jogo;
    scanf(" %[^:\n]", nome);
    hash = hash_str(nome);
    /* Calculo da gaveta que vamos verificar  */
    jogo = jogos->gavetas[hash % JOGO_GAVETAS];
    
    /* Similar a processos anteriores, ciclo while para passar por todos os jogos na gaveta */
    while ( jogo != NULL ) {
        /* Comparamos se o nome do jogo dado e igual ao nome do jogo na gaveta*/
        if (strcmp(nome, jogo->nome) == 0) {
            /* Se passar o teste, encontramos o jogo, printamo-lo */
            printf("%d %s %s %s %d %d\n", comandos_total,
                jogo->nome,
                jogo->equipa1->nome,
                jogo->equipa2->nome,
                jogo->golos1,
                jogo->golos2
            );
            return;
        }
        /* Se a gaveta for NULL */
        jogo = jogo->next_jogo;
    }
    
    /* NO caso do jogo nao existir, printamos o erro */
    printf("%d Jogo inexistente.\n", comandos_total);
}

/* Funcao que pretende listar todos os jogos por ordem de introducao na base
de dados */
void lista_jogos(struct Jogos*jogos, int comandos_total) {
    /* Variaveis que pretendemos usar */
    int n;
    /* Ciclo for para passarmos por todos os jogos no vetor de ponteiros de 
    ordem de insercao na base de dados, no caso do vetor ser vazio, nao printa
    nada */
    for (n = 0; n < jogos->njogos; n++) {
        /* Print dos jogos por ordem de insercao */
        printf("%d %s %s %s %d %d\n", comandos_total,
            jogos->ordem[n]->nome,
            jogos->ordem[n]->equipa1->nome,
            jogos->ordem[n]->equipa2->nome,
            jogos->ordem[n]->golos1,
            jogos->ordem[n]->golos2
        );
    }
}

/* Funcao que pretende apagar um jogo da base de dados do sistema */
void apaga_jogos(struct Jogos*jogos, int comandos_total) {
    /* Variaveis que pretendemos usar */
    char nome[MAX_JOGO_NOME];
    int hash;
    int n, i;
    struct Jogo *jogo;
    struct Jogo *ultimo_jogo = NULL;
    /* Scanf das variaveis dadas */
    scanf(" %[^:\n]", nome);
    hash = hash_str(nome);
    /* Calculo da gaveta que vamos verificar */
    jogo = jogos->gavetas[hash % JOGO_GAVETAS];
    
    /* Similar aos anteriores, ciclo while para passar por todos os jogos da gaveta */
    while ( jogo != NULL ) {
        /* Comparamos as strings do nome do jogo */
        if (strcmp(nome, jogo->nome) == 0) {
            /* Se a primeira equipa tiver ganho o jogo temos de retirar uma vitoria a equipa 1 */
            if ( jogo->golos1 > jogo->golos2 ) {
                jogo->equipa1->wins -= 1;
            }
            /* Mesma coisa mas para a equipa 2 */
            if ( jogo->golos1 < jogo->golos2 ) {
                jogo->equipa2->wins -= 1;
            }
            
            /* este segmento serve para atualizar o vetor de ponteiros da ordem de entrada na 
            base dados, ciclo for para passar por todos os jogos no vetor */
            for (n = 0; n < jogos->njogos; n++) {
                /* Vemos se o jogo esta inserido no vetor */
                if ( jogo == jogos->ordem[n] ) {
                    /* Atualizamos o vetor ordem, os jogos inseridos depois do apagado andam uma casa
                    para tras */
                    for (i = n + 1; i < jogos->njogos; i++) {
                        jogos->ordem[i-1] = jogos->ordem[i];
                    }
                    /* Decrementamos um ao numero de jogos total */
                    jogos->njogos -= 1;
                    break;
                }
            }
            
            /* Se o ultimo jogo na gaveta for NULL, atualizamos os valores */
            if (ultimo_jogo == NULL) {
                jogos->gavetas[hash % JOGO_GAVETAS] = jogo->next_jogo;
            } else {
                ultimo_jogo->next_jogo = jogo->next_jogo;
            }
            
            /* Libertamos a memoria do jogo que apagamos */
            free(jogo->nome);
            free(jogo);
            return;
        }
        
        /* O ultimo jogo passa a ser so um jogo */
        ultimo_jogo = jogo;
        jogo = jogo->next_jogo;
    }
    /* No caso do jogo nao estiver inserido na gaveta, printamos o erro */
    printf("%d Jogo inexistente.\n", comandos_total);
}
/* Funcao que pretende alterar o resultado de um jogo */
void muda_jogos(struct Jogos*jogos, int comandos_total) {
    /* Variaveis que pretendemos utilizar para a funcao */
    char nome[MAX_JOGO_NOME];
    int hash;
    struct Jogo *jogo;
    int golos1, golos2;
    /* Scanf das variaveis dadas */
    scanf(" %[^:\n]:%d:%d", nome, &golos1, &golos2);
    hash = hash_str(nome);
    /* Calculo da gaveta que vamos verificar */
    jogo = jogos->gavetas[hash % JOGO_GAVETAS];
    
    /* Mesmo processo, passamos por todas os jogos dentro da gaveta */
    while ( jogo != NULL ) {
        /* comparamos o nome do jogo */
        if (strcmp(nome, jogo->nome) == 0) {
            /* Se a primeira equipa estiver a ganhar, alteramos as wins dessa equipa*/
            if ( golos1 > golos2 ) {
                jogo->equipa1->wins += 1;
            }
            /* Mesmo processo mas para a segunda equipa */ 
            if ( golos1 < golos2 ) {
                jogo->equipa2->wins += 1;
            }
            
            /* A equipa1 esta a ganhar mas ao fazer delete deste jogo ou aleramos o score do mesmo
             a equipa1 ja nao ganhou este jogo, derementamos as suas wins*/
            if ( jogo->golos1 > jogo->golos2 ) {
                jogo->equipa1->wins -= 1;
            }
            /* Mesmo processo mas para a segunda equipa */
            if ( jogo->golos1 < jogo->golos2 ) {
                jogo->equipa2->wins -= 1;
            }
            
            jogo->golos1 = golos1;
            jogo->golos2 = golos2;
            
            return;
        }
        
        jogo = jogo->next_jogo;
    }
    /* No caso do jogo nao existir, nao o podemos alterar, printa o erro */
    printf("%d Jogo inexistente.\n", comandos_total);
}
