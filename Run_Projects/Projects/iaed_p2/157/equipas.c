#include "equipas.h"

pt_equipa nova_equipa (char * nome)
{
    pt_equipa equipa_nova;

    int comp = strlen(nome) + 1; /* '/0' */ 

    /* Aloca espaco para a nova equipa */
    equipa_nova = (pt_equipa) malloc(sizeof(struct equipa));

    /* Aloca espaco para o nome da equipa e atribui-lo */
    equipa_nova->nome = (char*) malloc(comp * sizeof(char));
    strcpy(equipa_nova->nome, nome);

    /* Inicializa o numero de vitorias a zero */
    equipa_nova->vitorias = 0;

    return equipa_nova;
}


pt_equipa procura_equipa (char * nome, link_equipa * equipas)
{
    /* Encontra o indice da equipa na tabela */
    int indice = hash_equipa(nome);
    
    link_equipa tmp;

    /* Ponteiro temporario aponta para primeiro elemento do indice */
    tmp = equipas[indice];

    /* Percorre os elementos desse indice ate ao fim ou ate encontrar a equipa pretendida */
    while (tmp != NULL && strcmp(tmp->equipa->nome, nome) != 0)
        tmp = tmp->next;

    /* Devolve ponteiro para equipa caso encontre, NULL caso contrario */
    if (tmp == NULL)
        return NULL;
    else
        return tmp->equipa;
}


bool equipa_existe (char * nome, link_equipa * equipas)
{
    /* Caso o procura equipa devolva NULL, a equipa nao existe no sistema */
    return (procura_equipa(nome, equipas) != NULL);
}


void free_equipa (pt_equipa equipa)
{
    /* Liberta o espaco alocado para a equipa e para o seu nome */
    free(equipa->nome);
    free(equipa);
}


link_equipa * init_equipas (link_equipa * tabela)
{
    int i;
    
    for (i = 0; i < (TAB_SIZE/2); i++)
        tabela[i] = NULL;

    return tabela;
}


void insere_equipa_tabela (pt_equipa equipa, link_equipa * equipas)
{
    /* Encontra o indice da equipa na tabela */
    int indice = hash_equipa(equipa->nome);

    /* Aloca espaco para o novo elemento da tabela */
    link_equipa new = (link_equipa) malloc(sizeof(struct node_equipa));

    /* Adiciona a equipa ao inicio da lista ligada do seu indice */
    new->equipa = equipa;
    new->next = equipas[indice];
    equipas[indice] = new;
}


int compara (const void * a, const void * b)
{
    return strcmp((const char*)a, (const char*)b);
}


int max_vitorias(link_equipa * equipas)
{
    /* Inicializa o numero de vitorias a zero */
    int i, max = 0;
   
    /* Ponteiro auxiliar que vai percorrer cada indice da tabela */
    link_equipa aux;
    
    /* Percorre todos os elementos da tabela, guardando o maior numero de vitorias encontrado */
    for (i = 0; i < (TAB_SIZE/2); i++) {
        aux = equipas[i];
        
        /* Caso o indice contenha elementos */
        while (aux != NULL) {
            if (aux->equipa->vitorias > max)
                max = aux->equipa->vitorias;
            
            aux = aux->next;
        }         
    }
    
    return max;
}
