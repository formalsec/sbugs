#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "equipas.h"


/* Funcao auxiliar que calcula a hash da equipa recebida */
int hash_function_equipas(char *string, int tamanho_max)
{
    int hash, a = 31415, b = 27183;

    for(hash = 0; *string != '\0'; string++, a = a*b % (tamanho_max - 1))
        hash = (a * hash + *string) % tamanho_max;
    return hash;
}


/* Funcao auxiliar de comparacao para o qsort */
int qsort_funcao_comparacao(const void *a, const void *b)
{
    /* Reconvertem-se os ponteiros recebidos para o seu tipo correto */
    link_equipa **equipaA = (link_equipa**) a;
    link_equipa **equipaB = (link_equipa**) b;

    return strcmp((*equipaA)->nome_equipa, (*equipaB)->nome_equipa);
}


/* Funcao que inicializa a hashtable das equipas, e devolve a sua posicao */
hashtable_equipas* inicializa_equipas(int tamanho_maximo)
{
    int i;
    hashtable_equipas *tabela_equipas;

    /* Aloca-se espaco em memoria para a struct que define a hashtable */
    tabela_equipas = (hashtable_equipas*) can_fail_malloc (sizeof(hashtable_equipas));

    /* Atribui-se o tamanho a hashtable e reserva-se esse numero de linhas */
    tabela_equipas->tamanho_maximo = tamanho_maximo;

    tabela_equipas->vetor_hashes = 
    (link_hashtable_equipas*) can_fail_malloc(tamanho_maximo * sizeof(link_hashtable_equipas));

    /* Inicializam-se os ponteiros de cada hash */
    for(i = 0; i < tamanho_maximo; i++)
        tabela_equipas->vetor_hashes[i].next = NULL; 

    return tabela_equipas;
}


/* Funcao que adiciona a equipa pretendida na posicao correta da hashtable */
void adicionar_equipa(char *nome_equipa, hashtable_equipas *equipas)
{
    /* NOTA: Ao executarmos esta funcao temos a certeza que 
    a equipa ainda nao foi adicionada */

    int hash;
    link_equipa *nova_equipa, *equipa_seguinte;
    
    /* Aloca-se o espaco necessario para a nova equipa e atribuisse-lhe o seu nome */
    nova_equipa = (link_equipa*) can_fail_malloc (sizeof(link_equipa));

    nova_equipa->numero_vitorias = 0;

    nova_equipa->nome_equipa = (char*) can_fail_malloc((strlen(nome_equipa) + 1) * sizeof(char));
    strcpy(nova_equipa->nome_equipa, nome_equipa);
    nova_equipa->next = NULL;

    /* Obtem-se a hash correspondente a esta equipa */
    hash = hash_function_equipas(nome_equipa, equipas->tamanho_maximo);

    /* Caso ainda nao hajam elementos nessa linha da tabela, e so adicionar */
    if (equipas->vetor_hashes[hash].next == NULL)
        equipas->vetor_hashes[hash].next = nova_equipa;

    /* Caso ja existam elementos, adiciona-se na primeira posicao 
    e reconecta-se o resto da lista */
    else
    {
        equipa_seguinte = equipas->vetor_hashes[hash].next;
        equipas->vetor_hashes[hash].next = nova_equipa;
        nova_equipa->next = equipa_seguinte;
    }
}


/* Funcao que procura por uma dada equipa, e devolve a sua posicao se existir */
link_equipa* procurar_equipa (char *nome_equipa, hashtable_equipas *equipas)
{
    int hash;
    link_equipa *link_atual;

    /* Obtem-se a hash correspondente a esta equipa */
    hash = hash_function_equipas(nome_equipa, equipas->tamanho_maximo);

    /* Caso a correspondente linha da hashtable nao tenha elementos, 
    entao a equipa pretendida nao existe */
    if (equipas->vetor_hashes[hash].next == NULL)
        return NULL;
    
    else
    {
        /* Caso contrario percorre-se a lista ate se encontrar a equipa */
        link_atual = equipas->vetor_hashes[hash].next;
        while (link_atual != NULL)
        {
            if (!strcmp(link_atual->nome_equipa, nome_equipa))
                return link_atual;
            else
                link_atual = link_atual->next;
        }

        /* Se chegamos ao fim da lista, entao a equipa pretendida nao existe */
        return NULL;
    }
}


/* Funcao que lista todas as equipas com o maior numero de vitorias */
void listar_melhores_equipas(hashtable_equipas *equipas, int linha_input)
{
    /* NOTA: Esta funcao so corre com a certeza de que 
    existe pelo menos uma equipa no sistema */

    int hash, maior_nmr_vitorias = 0, numero_equipas = 0, indice = 0;
    link_equipa *equipa_atual;
    link_equipa **array_equipas_vitoriosas;

    /* Percorrem-se todos os elementos de todas as linhas da hashtable, 
    para encontrarmos o numero de equipas com o maior numero de vitorias, 
    e este numero de vitorias */
    for(hash = 0; hash < equipas->tamanho_maximo; hash++)
    {
        equipa_atual = equipas->vetor_hashes[hash].next;

        while(equipa_atual != NULL)
        {
            if(equipa_atual->numero_vitorias == maior_nmr_vitorias)
                numero_equipas++;
            else if(equipa_atual->numero_vitorias > maior_nmr_vitorias)
            {
                maior_nmr_vitorias = equipa_atual->numero_vitorias;
                numero_equipas = 1;
            }
            equipa_atual = equipa_atual->next;
        }
    }

    /* A este ponto, ja sabemos o numero de equipas a listar, criando-se um vetor para sabermos quais sao */
    array_equipas_vitoriosas = (link_equipa**) can_fail_malloc(numero_equipas * sizeof(link_equipa*));

    /* Vamos adicionar as equipas pretendidas ao vetor, percorrendo mais uma vez a hashtable */
    while (indice < numero_equipas)
    {
       for(hash = 0; hash < equipas->tamanho_maximo; hash++)
       {
            equipa_atual = equipas->vetor_hashes[hash].next;

            while(equipa_atual != NULL)
            {
                if(equipa_atual->numero_vitorias == maior_nmr_vitorias)
                {
                    array_equipas_vitoriosas[indice] = equipa_atual;
                    indice++;
                }
                equipa_atual = equipa_atual->next;
            }
       }
    }

    /* Agora que temos todas as equipas que pretendemos listar, temos de as ordenar */
    qsort(array_equipas_vitoriosas, numero_equipas, sizeof(link_equipa*), qsort_funcao_comparacao);

    /* So nos falta imprimir as equipas */
    printf("%d Melhores %d\n", linha_input, maior_nmr_vitorias);

    for(indice = 0; indice < numero_equipas; indice++)
        printf("%d * %s\n", linha_input, array_equipas_vitoriosas[indice]->nome_equipa);

    /* Liberta-se o espaco que ocupamos para o array de ordenacao */
    free(array_equipas_vitoriosas);
}


/* Funcao que liberta todo o espaco associado as equipas */
void destruir_equipas(hashtable_equipas *equipas)
{
    int hash;
    link_equipa *head, *temp;

    /* Percorrem-se todas as linhas da hashtable. Para cada linha,
    eliminamos todos os elementos da lista */
    for (hash = 0; hash < equipas->tamanho_maximo; hash++)
    {
        head = equipas->vetor_hashes[hash].next; /* Cabeca da lista de cada hash */

        while(head != NULL)
        {
            temp = head->next;
            free(head->nome_equipa);
            free(head);
            head = temp;
        }
    }
    /* Finalmente, liberta-se o espaco associado ao vetor de hashes e a propria hashtable */
    free(equipas->vetor_hashes);
    free(equipas);
}
