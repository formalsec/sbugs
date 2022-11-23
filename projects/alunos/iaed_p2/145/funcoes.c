#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

void __a__(int NL, Hashtable hash_j, Hashtable hash_e, link * head) {

    char n_s[MAXNOME], e1_s[MAXNOME], e2_s[MAXNOME], * n, * e1, * e2;
    int s1, s2;
    Item j, v;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", n_s, e1_s, e2_s, &s1, &s2);
    n = cria_pchar(n_s);
    e1 = cria_pchar(e1_s);
    e2 = cria_pchar(e2_s);

    j = cria_item(n, e1, e2, s1, s2);

    /* Verifica se o jogo e valido */
    if (procura_hash(n, hash_j) != NULL) { 
        printf("%d Jogo existente.\n", NL);
        free_item(j);
        return;
    }

    /* Verifica se as equipas sao validas */
    if (procura_hash(e1, hash_e) == NULL || procura_hash(e2, hash_e) == NULL ) { 
        printf("%d Equipa inexistente.\n", NL);
        free_item(j);
        return;
    }

    insere_hash(j, hash_j); /* Adiciona Item jogo a tabela */
    insere_lista(j, head); /* Adicona Item jogo a lista */

    /* Atualiza dados de vitorias */
    if ((v = vencedor(e1, e2, s1, s2, hash_e)) != NULL)
        v -> vitorias++;

}


void __A__(int NL, Hashtable hasht) {

    char n_s[MAXNOME], * n;
    Item e;

    scanf(" %[^:\n]", n_s);
    n = cria_pchar(n_s);
     
    /* Verifica se a equipa e valida */
    if (procura_hash(n, hasht) != NULL) {
        printf("%d Equipa existente.\n", NL);
        free(n);
        return;
    }

    e = cria_item(n, NULL, NULL, 0, 0);
    insere_hash(e, hasht); /* Adiciona Item equipa a tabela */

}


void __l__(int NL, link head) {

    if (head != NULL) /* Verifica se a lista nao esta vazia */
        imprime_lista(NL, head);

}


void __p__(int NL, Hashtable hasht) {

    char n[MAXNOME];
    Item j;
    scanf(" %[^:\n]", n);

    j = procura_hash(n, hasht);
    
    if (j == NULL) { /* Verifica se o jogo existe */
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    imprime_jogo(j, NL);

}


void __P__(int NL, Hashtable hasht) {

    char n[MAXNOME];
    Item e;
    scanf(" %[^:\n]", n);

    e = procura_hash(n, hasht);

    if (e == NULL) { /* Verifica se a equipa existe */
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    printf("%d %s %d\n", NL, n, e -> vitorias);

}


void __r__(int NL, Hashtable hash_j, Hashtable hash_e, link * head) {

    char n[MAXNOME];
    Item j, v;
    scanf(" %[^:\n]", n);

    j = apaga_hash(n, hash_j); /* Obtem Item jogo e, se exisitir, remove-o  da tabela */

    if (j == NULL) { /* Verifica se o jogo existe */
        printf("%d Jogo inexistente.\n", NL);
        return ;
    }

    apaga_lista(j, head); /* Retira o Item jogo da lista */

    /* Atualiza dados de vitorias */
    v = vencedor(j -> e1, j -> e2, j -> s1, j -> s2, hash_e);
    if (v != NULL)
        v -> vitorias--;

    free_item(j); /* Liberta memoria alocada pelo item */

}


void __s__(int NL, Hashtable hash_j, Hashtable hash_e) {

    char n[MAXNOME];
    int s1, s2;
    Item j, aux, v;

    scanf(" %[^:\n]:%d:%d", n, &s1, &s2);

    j = procura_hash(n, hash_j);

    scanf(":%d:%d", &s1, &s2); /* Le restante imput */

    if (j == NULL) { /* Verifica se o jogo existe */
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    aux = vencedor(j -> e1, j -> e2, j -> s1, j -> s2, hash_e); /* Vencedor do jogo anterior */

    /* Altera scores */
    j -> s1 = s1;
    j -> s2 = s2;

    v = vencedor(j -> e1, j -> e2, j -> s1, j -> s2, hash_e); /* Novo vencedor */

    /* Altera vencedores */
    if (aux == v) /* Verifica se vencedor e o mesmo */
        return;

    if (aux == NULL) { /* Verifica se havia um empate */
        v -> vitorias++;
        return;
    }

    if (v == NULL) { /* Verifica se passou a haver um empate */
        aux -> vitorias--;
        return;
    }
    
    v -> vitorias++; /* O vencedor trocou */
    aux -> vitorias--;

}


void __g__(int NL, Hashtable hasht) {

    Item * endereco = hasht -> endereco;
    int M = hasht -> M, i, j = 0;
    int V = 0; /* Maior numero de vitorias */
    int equipas = 0; /* Quantas equipas tem o maior numero de vitorias */
    char ** lista; /* Lista de strings a ser ordenada */

    if (hasht -> N == 0) /* Verifica se existem equipas */
        return;

    for (i = 0; i < M; i++) /* Percorre a tabela para determinar V e equipas */
        if (endereco[i] != NULL) {
            if (endereco[i] -> vitorias == V) 
                equipas++; 
            if (endereco[i] -> vitorias > V) {
                V = endereco[i] -> vitorias;
                equipas = 1;
            }
        }
        
    lista = (char **) can_fail_malloc (sizeof(char *) * equipas); 

    for (i = 0; i < M; i++) /* Percorre a tabela e adiciona equipas a lista de strings */
        if (endereco[i] != NULL) {
            if (endereco[i] -> vitorias == V) {
                lista[j] = endereco[i] -> nome;
                j++;
            }
        }

    qsort(lista, equipas, sizeof(char *), compara); /* Ordena lista de strings */

    /* Imprime lista de strings */
    printf("%d Melhores %d\n", NL, V);

    for (i = 0; i < equipas; i++)
        printf("%d * %s\n", NL, lista[i]);

    free(lista); /* Liberta memoria alocada para a lista */

}
