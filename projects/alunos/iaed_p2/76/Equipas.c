#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Equipas.h"
#include "Misc.h"

/* Inicializa uma nova equipa com nome fornecido na funcao adiciona_equipa. */
equipa* cria_equipa(char* nome)
{
    equipa* nova_equipa = (equipa*) can_fail_malloc(sizeof(equipa));
    nova_equipa -> nome = (char*) can_fail_malloc(strlen(nome)+1);
    strcpy(nova_equipa -> nome, nome);
    nova_equipa -> vitorias = 0;
    return nova_equipa;
}

/* FUNCOES SOBRE HASH TABLES DE EQUIPAS: Esta hash table recorre a resolucao
 * linear de conflitos entre keys com o mesmo valor (linear probing). */

/* Insere uma equipa na hash table. Se o numero de equipas ultrapassar metade da hash
 * table, ela e realocada para uma nova tabela com o dobro da dimensao inicial. */
equipa** insere_equipa_h(equipa** h_equipas, equipa* nova_equipa, int* cont_equipas, int* tam_h_equipas)
{
    int i = hash(nova_equipa -> nome, *tam_h_equipas);
    while (h_equipas[i])
        i = (i+1) % (*tam_h_equipas);
    h_equipas[i] = nova_equipa;
    if (*cont_equipas > *tam_h_equipas/2) /* Verifica se e necessaria realocacao. */
        h_equipas = expande_h_equipas(h_equipas, cont_equipas, tam_h_equipas);
    return h_equipas;
}

/* Duplica uma hash table de equipas e efetua o respetivo rehashing dos seus elementos. */
equipa** expande_h_equipas(equipa** h_equipas, int* cont_equipas, int* tam_h_equipas)
{
    int j, novo_tam_h_equipas = 2*(*tam_h_equipas);
    equipa** aux = (equipa**) can_fail_calloc (novo_tam_h_equipas, sizeof(equipa*));
    for (j = 0; j < *tam_h_equipas; j++)
        if (h_equipas[j])
            insere_equipa_h(aux, h_equipas[j], cont_equipas, &novo_tam_h_equipas);
    free(h_equipas);
    *tam_h_equipas = novo_tam_h_equipas;
    return aux; 
}

/* Procura uma equipa na hash table, dado um nome.
 * Se ela existir, um ponteiro para essa equipa e devolvido pela funcao. */
equipa* procura_equipa_h(char* nome, equipa** h_equipas, int tam_h_equipas)
{
    int i;
    i = hash(nome, tam_h_equipas);
    while (h_equipas[i])
    {
        if (!strcmp(h_equipas[i] -> nome, nome))
            return h_equipas[i];
        i = (i+1) % tam_h_equipas;
    }
    return NULL;
}

/* Remove todas as equipas da hash table (incluindo os seus
 * nomes) previamente alocados, e destroi a propria tabela. */
void destroi_h_equipas(equipa** h_equipas, int tam_h_equipas)
{
    int i;
    for (i = 0; i < tam_h_equipas; i++)
        if (h_equipas[i])
        {
            free(h_equipas[i] -> nome);
            free(h_equipas[i]);
        }
    free(h_equipas);
}
