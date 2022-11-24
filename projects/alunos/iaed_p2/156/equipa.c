#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Projeto2.h"

/*Esta funcao adiciona uma equipa ao sistema.
 Esta funcao ira gerar um erro se a equipa ja existir no sistema.*/
void adic_equipa(equipa_pont *tabela_hash, int nl) {
    int indice;
    char buffer[Nome];
    equipa_pont equipa_adici, i;

    scanf(" %[^:\n]", buffer);

    indice = hash(buffer, Hash_equipas);

    /*Verifica se o nome da equipa ja existe.*/
    for (i = tabela_hash[indice]; i != NULL; i = i->prox_equipa){
        if (strcmp(i->nome_equipa, buffer) == 0){
            printf("%d Equipa existente.\n", nl);
            return;
        }
    }

    equipa_adici = (equipa_pont)can_fail_malloc(sizeof(struct equipa));

    equipa_adici->nome_equipa = (char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(equipa_adici->nome_equipa, buffer);

    equipa_adici -> vitorias = (int*)can_fail_malloc(sizeof(int));
    *equipa_adici -> vitorias = 0;

    equipa_adici -> prox_equipa = tabela_hash[indice];
    tabela_hash[indice] = equipa_adici;
    /*Adiciona a equipa no indice da tabela certo.*/
}

/*Esta funcao procura uma equipa no sistema.
  Esta funcao ira gerar um erro se a equipa nao existir no sistema.*/
void procura_equipa(equipa_pont *tabela_hash_equipas, int nl){
    char nome[Nome];
    int indice;
    equipa_pont i;
    
    scanf(" %[^:\n]", nome);

    indice = hash(nome, Hash_equipas);

    /*Verifica se a equipa existe no sistema e se existir retorna o nome e as vitorias.*/
    for(i = tabela_hash_equipas[indice]; i != NULL; i = i -> prox_equipa){
        if (strcmp(nome, i -> nome_equipa) == 0){
            printf("%d %s %d\n", nl, i -> nome_equipa, *i -> vitorias);
            return;
        }
    }
    printf("%d Equipa inexistente.\n", nl);
}

/*Esta funcao e auxiliar ao qsort e serve para ordenar as equipas pelos nomes.*/
int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

/*Esta funcao serve para descobrir o numero maximo de vitorias e atualiza a variavel tamanho
  para ficar com o numero de equipas que teem esse numero de vitorias.*/
int descobre_max_vit(equipa_pont *tabela_hash_equipas, int* tamanho){
    int indice, max_vitorias = 0;
    equipa_pont e;

    for (indice = 0; indice < Hash_equipas; indice++){
        for (e = tabela_hash_equipas[indice]; e != NULL; e = e -> prox_equipa){
            if (*e -> vitorias > max_vitorias){ 
                /*Se a equipa tiver mais vitorias que as anteriores atualiza o numero maximo de 
                vitorias e comeca a contar o numero de equipas que tem esse numero de vitorias.*/
                max_vitorias = *e -> vitorias;
                (*tamanho) = 1;
            }
            else if (*e -> vitorias == max_vitorias){
                (*tamanho)++;
            }
        }
    }
    return max_vitorias;
}

/*Esta funcao devolve o numero maximo de vitorias e quais a(s) equipa(s)
  que teem esse numero de vitorias no sistema.*/
void mais_vencedoras(equipa_pont *tabela_hash_equipas, int nl){
    int indice, max_vitorias = 0, indice_array = 0, tamanho = 0;
    equipa_pont e;
    char **array;

    max_vitorias = descobre_max_vit(tabela_hash_equipas, &tamanho);

    if (tamanho == 0){
        return;
    }

    array = (char**)can_fail_malloc(sizeof(char*)* tamanho);

    /*Coloca em cada indice do array as equipas que tem o numero maximo de vitorias.*/
    for (indice = 0; indice < Hash_equipas; indice++){
        for (e = tabela_hash_equipas[indice]; e != NULL; e = e -> prox_equipa){
            if (*e -> vitorias == max_vitorias){
                array[indice_array] = e -> nome_equipa;
                indice_array++;
            }
        }
    }
    
    /*Ordena o array.*/
    qsort(array, tamanho, sizeof(char *), cstring_cmp);

    printf("%d Melhores %d\n", nl, max_vitorias);
    for (indice = 0; indice < indice_array; indice++){
        printf("%d * %s\n", nl, array[indice]);
    }
    
    free(array);
}