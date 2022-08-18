#include "estruturas.h"

NodeJ *insertEnd_lista_tabelaJ(NodeJ *cabeca, NodeJ *x)
{
    NodeJ *t = cabeca;
    x->next_tabela = NULL;
    if (cabeca == NULL) return x;
    while (t->next_tabela != NULL)
        t = t->next_tabela;
    t->next_tabela = x;
    return cabeca;
}

void freeJ(NodeJ *x)
{
    free(x->nome);
    free(x->casa);
    free(x->fora);
    free(x);
}

void free_lista_tabelaJ(NodeJ *cabeca)
{
    NodeJ *t;
    while(cabeca != NULL)
    {
        t = cabeca;
        cabeca = cabeca->next_tabela;
        freeJ(t);
    }
}

NodeJ *remove_lista_tabelaJ(NodeJ *cabeca, char *nomenclatura)
{
    NodeJ *tant, *t;
    t = cabeca;
    if(cabeca == NULL)
        return cabeca;
    if (strcmp(t->nome, nomenclatura) == 0)
    {
        t = cabeca->next_tabela;
        freeJ(cabeca);
        return t;
    }
    while(t->next_tabela != NULL)
    {
        tant = t;
        t = t->next_tabela;
        if(strcmp(t->nome, nomenclatura) == 0)
        {
            tant->next_tabela = t->next_tabela;
            freeJ(t);
            return cabeca;
        }
    }
    return cabeca;
}

void print_lista_tabelaJ(int cont, NodeJ *cabeca)
{
    NodeJ *t;
    t = cabeca;
    while(t != NULL)
    {
        printf("%d %s %s %s %d %d\n",cont, t->nome, t->casa, t->fora, t->resCasa, t->resFora);
        t = t->next_tabela;
    }
}

NodeJ *encontra_lista_tabelaJ(NodeJ *cabeca, char *nomenclatura)
{
    NodeJ *t = cabeca;
    if(t == NULL)
        return NULL;
    if(strcmp(t->nome,nomenclatura) == 0)
        return t;
    while(t->next_tabela != NULL)
    {
        t = t->next_tabela;
        if(strcmp(t->nome, nomenclatura) == 0)
            return t;
    }
    return NULL;
}

/*___________________________________________________________________________________________________________________*/

/* funcao hash que devolve o inidice da tabela a que corresponde a string dada */
unsigned int hash(const char *key)
{
    unsigned int soma = 0, i, key_size = strlen(key);

    for(i = 0; i < key_size; i++)
    {
        soma += key[i];
        soma = soma * 13 * key[i];        
    }
    soma = soma % TAM_HASH;
    return soma;
}

/*-------------------------------------------------------------------------------------------------------------------*/

void freeE(NodeE *x)
{
    free(x->nome);
    free(x);
}

void free_listaE(NodeE *cabeca)
{
    NodeE *t;
    while(cabeca != NULL)
    {
        t = cabeca;
        cabeca = cabeca->next;
        freeE(t);
    }
}

NodeE *insertEnd_listaE(NodeE *cabeca, char *nome, int wins)
{
    NodeE *t = cabeca;
    NodeE *x = malloc(sizeof(NodeE));
    x->nome = malloc(sizeof(char)*strlen(nome)+1);
    strcpy(x->nome, nome);
    x->vitorias = wins;
    x->next = NULL;
    if (cabeca == NULL) return x;
    while (t->next != NULL)
        t = t->next;
    t->next = x;
    return cabeca;
}

NodeE *remove_listaE(NodeE *cabeca, char *nomenclatura)
{
    NodeE *tant, *t;
    t = cabeca;
    if (strcmp(t->nome,nomenclatura) == 0)
    {
        t = cabeca->next;
        freeE(cabeca);
        return t;
    }
    while(t->next != NULL)
    {
        tant = t;
        t = t->next;
        if(strcmp(t->nome, nomenclatura)==0)
        {
            tant->next = t->next;
            freeE(t);
            return cabeca;
        }
    }
    return cabeca;
}

void print_equipa(int cont, NodeE *equipa)
{
    printf("%d %s %d\n", cont, equipa->nome, equipa->vitorias);
}

NodeE *encontra_listaE(NodeE *cabeca, char *nomenclatura)
{
    NodeE *t = cabeca;
    if(t == NULL)
        return NULL;
    else if(strcmp(t->nome,nomenclatura) == 0)
        return t;
    else 
    {
        while(t->next != NULL)
        {
            t = t->next;
            if(strcmp(t->nome, nomenclatura) == 0)
                return t;
        }
        return NULL;
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

NodeE **init_hash_tableE()
{
    NodeE **hash_table;
    hash_table = calloc(TAM_HASH, sizeof(NodeE*));
    /*inicializa a tabela vazia*/
    return hash_table;
}

void hash_table_insertE(NodeE **hash_table, char *nome, int vitorias)
{
    int index = hash(nome);
    hash_table[index] = insertEnd_listaE(hash_table[index], nome, vitorias);
}

void hash_table_removeE(NodeE **hash_table, char *nome)
{
    int index = hash(nome);
    hash_table[index] = remove_listaE(hash_table[index], nome);
}

void free_tabelaE(NodeE **tabela)
{
    int i;
    for (i = 0; i < TAM_HASH; i++)
        free_listaE(tabela[i]);
    free(tabela);
}

NodeE *encontra_tabelaE(NodeE **tabela, char *nome)
{
    int index = hash(nome);
    return encontra_listaE(tabela[index], nome);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

void hash_table_insertJ(NodeJ **hash_table, NodeJ *jogo)
{
    int index = hash(jogo->nome);
    hash_table[index] = insertEnd_lista_tabelaJ(hash_table[index], jogo);
}

void hash_table_removeJ(NodeJ **hash_table, char *nome)
{
    int index = hash(nome);
    hash_table[index] = remove_lista_tabelaJ(hash_table[index], nome);
}

void free_listaJ(NodeJ *cabeca)
{
    NodeJ *t;
    while(cabeca != NULL)
    {
        t = cabeca;
        cabeca = cabeca->next_lista;
        freeJ(t);
    }
}

NodeJ *insertEnd_listaJ(NodeJ *cabeca, NodeJ **cauda, NodeJ **tabela, char *nome, char *casa, char *fora, int resCasa, int resFora)
{
    NodeJ *x = malloc(sizeof(NodeJ));
    x->nome = malloc(sizeof(char)*strlen(nome)+1);
    strcpy(x->nome, nome);
    x->casa = malloc(sizeof(char)*strlen(casa)+1);
    strcpy(x->casa, casa);
    x->fora = malloc(sizeof(char)*strlen(fora)+1);
    strcpy(x->fora, fora);
    x->resCasa = resCasa;
    x->resFora = resFora;
    x->next_lista = NULL;
    hash_table_insertJ(tabela, x);
    if(cabeca == NULL)
    {
        x->prev_lista = NULL;
        *cauda = x;
        cabeca = x;
        return cabeca;
    }
    (*cauda)->next_lista = x;
    x->prev_lista = *cauda;
    *cauda = x;
    return cabeca;
}

NodeJ *apagaNodeJ(NodeJ *cabeca, NodeJ **cauda, NodeJ *del)
{
    if(cabeca == (*cauda))
    {
        cabeca = NULL;
        (*cauda) = NULL;
    }
    else if(cabeca == del)
        cabeca = del->next_lista;
    else if((*cauda) == del)
    {
        (*cauda) = del->prev_lista; 
        (*cauda)->next_lista = NULL;
    }
    else 
    {
        del->next_lista->prev_lista = del->prev_lista;
        del->prev_lista->next_lista = del->next_lista;
    }
    return cabeca;
}


NodeJ *remove_listaJ(NodeJ *cabeca, NodeJ **cauda, NodeJ **tabela, char *nomenclatura)
{
    NodeJ *jogo;
    jogo = encontra_tabelaJ(tabela, nomenclatura);
    cabeca = apagaNodeJ(cabeca, cauda, jogo);
    hash_table_removeJ(tabela, jogo->nome);
    return cabeca;
}

void print_listaJ(int cont, NodeJ *cabeca)
{
    NodeJ *t;
    t = cabeca;
    while(t != NULL)
    {
        printf("%d %s %s %s %d %d\n",cont, t->nome, t->casa, t->fora, t->resCasa, t->resFora);
        t = t->next_lista;
    }
}

void print_jogo(int cont, NodeJ *jogo)
{
    printf("%d %s %s %s %d %d\n", cont, jogo->nome, jogo->casa, jogo->fora, jogo->resCasa, jogo->resFora);
}

NodeJ *encontra_listaJ(NodeJ *cabeca, char *nomenclatura)
{
    NodeJ *t = cabeca;
    if(t == NULL)
        return NULL;
    if(strcmp(t->nome,nomenclatura) == 0)
        return t;
    while(t->next_lista != NULL)
    {
        t = t->next_lista;
        if(strcmp(t->nome, nomenclatura) == 0)
            return t;
    }
    return NULL;
}

NodeJ **init_hash_tableJ()
{
    NodeJ **hash_table;
    hash_table = calloc(TAM_HASH, sizeof(NodeJ*));
    /*inicializa a tabela vazia*/
    return hash_table;
}

void print_tableJ(int cont, NodeJ **hash_table)
{
    unsigned int i;
    for(i = 0; i < TAM_HASH; i++)
    {
        if(hash_table[i] == NULL)
            printf("\t\t%i\t---\n", i);
        else
        {
            printf("\t\t%i\t", i);
            print_listaJ(cont, hash_table[i]);
        }
    }
}

void free_tabelaJ(NodeJ **tabela)
{
    int i;
    for (i = 0; i < TAM_HASH; i++)
        free_lista_tabelaJ(tabela[i]);
    free(tabela);
}

NodeJ *encontra_tabelaJ(NodeJ **tabela, char *nome)
{
    int index = hash(nome);
    return encontra_lista_tabelaJ(tabela[index], nome);
}