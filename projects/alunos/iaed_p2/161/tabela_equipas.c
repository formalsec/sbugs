#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "tabela_equipas.h"

/* cria uma tabela de equipas vazia e devolve o seu ponteiro ----------------------------------- */
pTabela_equipas inicializa_tabela_equipas(unsigned int max) 
{
    unsigned int i;

    /* aloca memoria para a tabela */
    pTabela_equipas tabela = (pTabela_equipas)can_fail_malloc(sizeof(struct tabela_equipas));

    tabela -> num_equipas = 0;
    tabela -> tamanho = max;

    /* aloca memoria para o vetor de equipas */
    tabela -> equipas = (pEquipa*)can_fail_malloc(max *sizeof(pEquipa));

    for (i = 0; i < tabela -> tamanho; i++) tabela -> equipas[i] = NULL;
    
    return tabela;
}


/* expande a tabela para o dobro do tamanho ---------------------------------------------------- */
void expande_tabela_equipas(pTabela_equipas tabela)
{
    unsigned int i;
    pTabela_equipas tabela_aux;
    
    /* cria tabela auxiliar com o dobro do tamanho*/
    tabela_aux = inicializa_tabela_equipas((tabela -> tamanho)*2);

    /* copia as equipas para a nova tabela */
    for (i = 0; i < tabela -> tamanho; i++)
        if (tabela -> equipas[i] != NULL)
            adiciona_equipa_tabela(tabela_aux, tabela -> equipas[i]);
    
    
    free(tabela -> equipas);

    /* muda o ponteiro das equipas e o tamanho da tabela original */
    tabela -> equipas = tabela_aux -> equipas;
    tabela -> tamanho = tabela_aux -> tamanho;

    
    free(tabela_aux);
    return;
}


/* adiciona uma equipa 'a tabela --------------------------------------------------------------- */
void adiciona_equipa_tabela(pTabela_equipas tabela, pEquipa equipa) 
{
    unsigned int i = gera_hash(obtem_nome_equipa(equipa), tabela -> tamanho);
    
    /* coloca a equipa no espaco atribuido pela hash, ou no proximo que estiver vazio */
    while (tabela -> equipas[i] != NULL) 
        i = (i+1) % tabela -> tamanho;
    
    tabela -> equipas[i] = equipa;

    /* se metade da tabela estiver ocupada, expande-a */ 
    if (tabela -> num_equipas++ > tabela -> tamanho/2)
        expande_tabela_equipas(tabela);
    
    return;
}


/* se a equipa existir devolve o seu ponteiro, senao, devolve NULL ----------------------------- */
pEquipa procura_equipa_tabela(pTabela_equipas tabela, char *nome_equipa)
{
    int i = gera_hash(nome_equipa, tabela -> tamanho);

    /* se a equipa nao estiver na posicao dada pela hash,
    percorre a tabela ate encontrar a equipa ou chegar a uma posicao vazia */
    while (tabela -> equipas[i] != NULL)

        if (strcmp(obtem_nome_equipa(tabela -> equipas[i]), nome_equipa) == 0)
            return tabela -> equipas[i]; /* devolve a equipa */
        else
            i = (i+1) % tabela -> tamanho;

    return NULL;
}


/* escreve o nome de cada equipa de um vetor de equipas ---------------------------------------- */
void print_vetor_equipas(char **vetor_equipas, unsigned int tamanho, unsigned int Num_Linha)
{
    unsigned int i;
    
    for (i = 0; i < tamanho; i++)
        printf("%u * %s\n", Num_Linha, vetor_equipas[i]);
    
    return;
    
}


/* compara o nome de duas equipas  ------------------------------------------------------------- */
int comparador(const void* equipa1, const void* equipa2)
{
    return strcmp(*(char**)equipa1, *(char**)equipa2);
} 


/* escreve as melhores equipas ----------------------------------------------------------------- */ 
void print_melhores_equipas(pTabela_equipas tabela, unsigned int Num_Linha)
{
    unsigned int i, j, num_equipas_percorridas, vitorias_equipa, maximo_vitorias;
    char **melhores_equipas_buffer; /* ponteiro para vetor de tamanho igual ao numero de equipas */
    char **melhores_equipas; /*ponteiro para vetor de tamanho igual ao numero de melhores equipas*/
        
    /* verifica se ha' equipas na tabela */
    if (tabela -> num_equipas == 0)
        return;


    /* aloca memoria para o vetor de melhores_equipas_buffer */
    melhores_equipas_buffer = (char**)can_fail_malloc(sizeof(char*)* tabela -> num_equipas);

    num_equipas_percorridas = 0;
    maximo_vitorias = 0;

    /* percorre a tabela de equipas ate todas as equipas tiverem sido percorridas */
    for(i = 0, j = 0; num_equipas_percorridas < tabela -> num_equipas; i++)
    {   
        
        if (tabela -> equipas[i] != NULL)
        {   
            num_equipas_percorridas++;

            /* se a equipa tiver mais vitorias que as anteriores,
             o index do vetor das melhores_equipas_buffer passa a 0 e a equipa eh adicionada*/
            if ((vitorias_equipa = obtem_vitorias_equipa(tabela -> equipas[i])) > maximo_vitorias)
                {
                maximo_vitorias = vitorias_equipa;
                j = 0;
                melhores_equipas_buffer[j++] = obtem_nome_equipa(tabela -> equipas[i]);
                }

            /* se a equipa tiver o mesmo numero de vitorias o seu nome eh adicionada ao vetor */
            else if (vitorias_equipa == maximo_vitorias)
                melhores_equipas_buffer[j++] = obtem_nome_equipa(tabela -> equipas[i]);
        }
        
    }

    
    
    /* se todas as equipas nao tiverem o mesmo numero de vitorias,
    aloca memoria para o vetor melhores_equipas e copia as melhores_equipas*/    
    if (j == tabela -> num_equipas)
        melhores_equipas = melhores_equipas_buffer;
    
    else
    {
        melhores_equipas = (char**)can_fail_malloc(sizeof(char*)*j);
        for(i = 0; i < j; i++)
            melhores_equipas[i] = melhores_equipas_buffer[i];
        
        free(melhores_equipas_buffer); 
    }
    
    /* ordena o vetor das equipas */   
    qsort(melhores_equipas, (int)j, sizeof(char*), comparador);
    
    
    printf("%u Melhores %u\n", Num_Linha, maximo_vitorias);
    print_vetor_equipas(melhores_equipas, j, Num_Linha);
    
    free(melhores_equipas); 
    return;
}

/* liberta a memoria da tabela e das equipas --------------------------------------------------- */
void destroi_tabela_equipas(pTabela_equipas tabela)
{
    unsigned int i;
    
    /* percorre a tabela e liberta a memoria alocada 'as equipas */
    for (i = 0; i < tabela -> tamanho; i++)
        if(tabela -> equipas[i] != NULL)
            free_equipa(tabela -> equipas[i]);
            
    
    free(tabela -> equipas);
    free(tabela);

    return;
}
