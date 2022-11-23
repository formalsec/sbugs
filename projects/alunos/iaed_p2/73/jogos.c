#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "jogos.h"

/* Funcao auxiliar para o calculo da hash do nome recebido */
int hash_function_jogos(char *string, int tamanho_max)
{
    int hash, a = 31415, b = 27183;

    for(hash = 0; *string != '\0'; string++, a = a*b % (tamanho_max - 1))
        hash = (a * hash + *string) % tamanho_max;
    return hash;
}


/* Funcao que inicializa a hashtable para os jogos, devolvendo a sua posicao */
hashtable_jogos* inicializa_jogos(int tamanho_maximo)
{
    int hash;
    hashtable_jogos *tabela_jogos;

    /* Criacao da estrutura que guarda o tamanho e o vetor de heads da tabela */
    tabela_jogos = (hashtable_jogos*) can_fail_malloc(sizeof(hashtable_jogos));

    tabela_jogos->tamanho_maximo = tamanho_maximo;

    tabela_jogos->vetor_hashes = 
    (link_hashtable_jogos*) can_fail_malloc(tamanho_maximo * sizeof(link_hashtable_jogos));

    /* Inicializacao do ponteiro das heads a null */
    for(hash = 0; hash < tamanho_maximo; hash++)
        tabela_jogos->vetor_hashes[hash].next = NULL;
 
    return tabela_jogos;
}


/* Funcao que inicializa a lista de jogos, e devolve a sua posicao */
lista_ord_jogos* inicializa_jogos_lista()
{
    lista_ord_jogos *lista_jogos;

    /* Aloca-se memoria para a estrutura que guarda os ponteiros da lista */
    lista_jogos = (lista_ord_jogos*) can_fail_malloc(sizeof(lista_ord_jogos));

    /* Inicializam-se os ponteiros a NULL */
    lista_jogos->head = NULL;
    lista_jogos->tail = NULL;

    return lista_jogos;
}


/* Funcao que introduz o jogo na correta posicao da hashtable e na lista */
void inserir_jogo(char* nome_jogo, link_equipa *equipa1, link_equipa *equipa2, 
int score1, int score2, hashtable_jogos *tabela_jogos, lista_ord_jogos *lista_jogos)
{
    char *novo_nome_jogo;
    int hash;
    jogo *novo_jogo;
    link_jogo *no_novo_jogo;

    /* Copia-se o nome dado para o jogo para uma string com apenas o tamanho da palavra */
    novo_nome_jogo = (char*) can_fail_malloc((strlen(nome_jogo) + 1) * sizeof(char));
    strcpy(novo_nome_jogo, nome_jogo);

    /* Colocam-se os atributos pretendidos na nova estrutura jogo */
    novo_jogo = (jogo*) can_fail_malloc(sizeof(jogo));

    novo_jogo->nome_jogo = novo_nome_jogo;
    novo_jogo->pequipa1 = equipa1;
    novo_jogo->pequipa2 = equipa2;
    novo_jogo->pontos1 = score1;
    novo_jogo->pontos2 = score2;

    /* Cria-se um novo no que contem a estrutura jogo */
    no_novo_jogo = (link_jogo*) can_fail_malloc(sizeof(link_jogo));
    no_novo_jogo->pointer_jogo = novo_jogo;

    /* Calcula-se a hash correspondente a este jogo */
    hash = hash_function_jogos(nome_jogo, tabela_jogos->tamanho_maximo);

    /* Insere-se o jogo na sua linha da hashtable */
    if(tabela_jogos->vetor_hashes[hash].next == NULL)
    {
        /* Caso ainda nao hajam elementos nessa linha da hashtable, o novo jogo e inserido diretamente */
        no_novo_jogo->jogo_next_hashtable = NULL;
        tabela_jogos->vetor_hashes[hash].next = no_novo_jogo;

    }
    else
    {
        /* Insere-se o elemento no inicio da respetiva linha da hashtable */
        no_novo_jogo->jogo_next_hashtable = tabela_jogos->vetor_hashes[hash].next;
        tabela_jogos->vetor_hashes[hash].next = no_novo_jogo;
    }

    /* Insere-se o jogo na lista */
    if(lista_jogos->head == NULL)
    {
        /* Caso ainda nao hajam elementos na lista, o novo jogo e simultaneamente o primeiro e ultimo elemento */
        lista_jogos->head = no_novo_jogo;
        lista_jogos->tail = no_novo_jogo;

        no_novo_jogo->jogo_anterior_lista = NULL;
        no_novo_jogo->jogo_next_lista = NULL;
    }
    else
    {
        /* Adiciona-se o novo jogo no fim da lista */
        lista_jogos->tail->jogo_next_lista = no_novo_jogo;

        no_novo_jogo->jogo_anterior_lista = lista_jogos->tail;
        no_novo_jogo->jogo_next_lista = NULL;

        lista_jogos->tail = no_novo_jogo;
    }
    
    /* Caso alguma equipa tenha ganho, incrementa-se o numero de vitorias */
    if(score1 > score2)
        equipa1->numero_vitorias++;
    else if(score1 < score2)
        equipa2->numero_vitorias++;
}


/* Funcao que lista todos os jogos introduzidos por ordem de insercao */
void listar_todos_jogos(int linha_input, lista_ord_jogos *lista_jogos)
{
    link_jogo *pjogo_atual;
    jogo *jogo_atual;

    pjogo_atual = lista_jogos->head;
    while(pjogo_atual != NULL)
    {
        /* Percorre-se toda a lista, imprimindo-se as caracteristicas de cada jogo */
        jogo_atual = pjogo_atual->pointer_jogo;
        printf("%d %s %s %s %d %d\n", linha_input, jogo_atual->nome_jogo, jogo_atual->pequipa1->nome_equipa,
        jogo_atual->pequipa2->nome_equipa, jogo_atual->pontos1, jogo_atual->pontos2);

        pjogo_atual = pjogo_atual->jogo_next_lista;
    }
}


/* Funcao que procura o jogo com o nome dado,e devolve o ponteiro da sua posicao */
link_jogo* procurar_jogo(char* nome_jogo, hashtable_jogos *tabela_jogos)
{
    int hash;
    link_jogo *link_atual;

    /* Obtem-se a hash correspondente ao nome recebido */
    hash = hash_function_jogos(nome_jogo, tabela_jogos->tamanho_maximo);

    /* Caso nao haja qualquer elemento na sua hash, entao este jogo nao existe */
    if(tabela_jogos->vetor_hashes[hash].next == NULL)
        return NULL;
    else
    {
        /* Obtem-se o primeiro no da lista */
        link_atual = tabela_jogos->vetor_hashes[hash].next; 

        while (link_atual != NULL)
        {
            /* Percorre-se toda a lista desta hash ate encontrarmos o jogo pretendido */
            if(!strcmp(link_atual->pointer_jogo->nome_jogo, nome_jogo))
                return link_atual;
            else
                link_atual = link_atual->jogo_next_hashtable;
        }
        /* Se chegamos ao fim da lista, entao e porque o jogo pretendido nao existe */
        return NULL;
    }
}


/* Funcao que pretende apagar o jogo recebido */
void apagar_jogo(char* nome_jogo, hashtable_jogos *tabela_jogos, lista_ord_jogos *lista_jogos)
{
    /* NOTA: Ao executarmos esta funcao, ja sabemos que o jogo que procuramos existe */
    int hash;
    link_jogo *jogo_anterior, *jogo_alvo, *jogo_next;

    /* Obtem-se a hash do jogo pretendido */
    hash = hash_function_jogos(nome_jogo, tabela_jogos->tamanho_maximo);

    /* O jogo pretendido ou esta na cabeca da sua hash, ou no resto da lista */
    if(strcmp(nome_jogo, tabela_jogos->vetor_hashes[hash].next->pointer_jogo->nome_jogo) == 0)
    {
        /* Guarda-se o jogo pretendido e o jogo seguinte passa a ser a head da lista daquela hash */
        jogo_alvo = tabela_jogos->vetor_hashes[hash].next;
        jogo_next = jogo_alvo->jogo_next_hashtable;
        tabela_jogos->vetor_hashes[hash].next = jogo_next;

    }
    /* Caso o jogo pretendido nao seja o primeiro na lista */
    else
    {
        jogo_anterior = tabela_jogos->vetor_hashes[hash].next;

        while (1)
        {
            /* Quando encontramos o jogo pretendido */
            if(strcmp(jogo_anterior->jogo_next_hashtable->pointer_jogo->nome_jogo, nome_jogo) == 0)
            {
                /* Retira-se o jogo do meio da lista */
                jogo_alvo = jogo_anterior->jogo_next_hashtable;
                jogo_next = jogo_alvo->jogo_next_hashtable;
                jogo_anterior->jogo_next_hashtable = jogo_next;

                break;
            }
            else
                jogo_anterior = jogo_anterior->jogo_next_hashtable;
        }  
    }

    /* Temos de atualizar a lista de jogos */
    /* Caso o jogo seja o unico na lista, da-se reset a lista */
    if(jogo_alvo->jogo_anterior_lista == NULL && jogo_alvo->jogo_next_lista == NULL)
    {
        lista_jogos->head = NULL;
        lista_jogos->tail = NULL;
    }
    /* Caso seja o primeiro jogo mas nao o unico */
    else if (jogo_alvo->jogo_anterior_lista == NULL)
    {
        jogo_next = jogo_alvo->jogo_next_lista;
        lista_jogos->head = jogo_next;
        jogo_next->jogo_anterior_lista = NULL;
    }
    /* Caso seja o ultimo mas nao o unico */
    else if (jogo_alvo->jogo_next_lista == NULL)
    {
        jogo_anterior = jogo_alvo->jogo_anterior_lista;
        lista_jogos->tail = jogo_anterior;
        jogo_anterior->jogo_next_lista = NULL;
    }
    /* Caso o jogo se encontre no meio da lista */
    else
    {
        jogo_next = jogo_alvo->jogo_next_lista;
        jogo_anterior = jogo_alvo->jogo_anterior_lista;

        jogo_anterior->jogo_next_lista = jogo_next;
        jogo_next->jogo_anterior_lista = jogo_anterior;
    }

    /* Antes de se remover o jogo, temos de descontar as vitorias de uma equipa, caso seja o caso */
    if(jogo_alvo->pointer_jogo->pontos1 > jogo_alvo->pointer_jogo->pontos2)
        jogo_alvo->pointer_jogo->pequipa1->numero_vitorias--;
    else if(jogo_alvo->pointer_jogo->pontos1 < jogo_alvo->pointer_jogo->pontos2)
        jogo_alvo->pointer_jogo->pequipa2->numero_vitorias--;

    /* Agora so falta libertar o espaco ocupado por este jogo */
    free(jogo_alvo->pointer_jogo->nome_jogo);
    free(jogo_alvo->pointer_jogo);
    free(jogo_alvo);
}


/* Funcao que altera o resultado do jogo pretendido */
void alterar_jogo(link_jogo *jogo, int score1, int score2)
{
    int score1temp, score2temp;

    /* Retira-se a vitoria, se existir, correspondente ao resultado anterior */
    score1temp = jogo->pointer_jogo->pontos1;
    score2temp = jogo->pointer_jogo->pontos2;

    if(score1temp > score2temp)
        jogo->pointer_jogo->pequipa1->numero_vitorias--;
    else if (score1temp < score2temp)
        jogo->pointer_jogo->pequipa2->numero_vitorias--;
    
    /* Atualiza-se o jogo, e adiciona-se uma vitoria a equipa vencedora, se for o caso */
    jogo->pointer_jogo->pontos1 = score1;
    jogo->pointer_jogo->pontos2 = score2;

    if(score1 > score2)
        jogo->pointer_jogo->pequipa1->numero_vitorias++;
    else if (score1 < score2)
        jogo->pointer_jogo->pequipa2->numero_vitorias++;
}


/* Funcao que vai libertar toda a memoria ocupada pela hashtable */
void destruir_jogos(hashtable_jogos *tabela_jogos)
{
    int hash;
    link_jogo *jogo_atual, *jogo_temporario;

    /* Percorrem-se todas as linhas da hashtable */
    for(hash = 0; hash < tabela_jogos->tamanho_maximo; hash++)
    {
        jogo_atual = tabela_jogos->vetor_hashes[hash].next;

        while(jogo_atual != NULL)
        {
            /* Percorre-se a lista inteira de cada linha, libertando-se a memoria 
            associada aos parametros de cada jogo, e as proprias estruturas do jogo */

            jogo_temporario = jogo_atual->jogo_next_hashtable;

            free(jogo_atual->pointer_jogo->nome_jogo);
            free(jogo_atual->pointer_jogo);
            free(jogo_atual);

            jogo_atual = jogo_temporario;
        }
    }

    /* Liberta-se finalmente o espaco do vetor de hashes, e a estrutura da tabela em si */ 
    free(tabela_jogos->vetor_hashes);
    free(tabela_jogos);
}


/* Funcao que vai libertar a memoria associada a lista de jogos */
void destruir_lista(lista_ord_jogos *lista_jogos)
{
    /* A este ponto ja todos os jogos foram apagados, 
    pelo que so e necessario apagar a estrutura da lista */
    free(lista_jogos);
}


