#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"

/* Funcao que le o caracter inicial do input */
char LeCaracterInicial()
{
    char CaracterInicial;
    scanf("%c", &CaracterInicial);
    return CaracterInicial; 
}

/*hash function que recebe o nome de um jogo ou o nome de uma equipa */        
unsigned int hash_function(char *nome)
{
    int tamanho, i;
    unsigned int hash = 0;
    tamanho = strlen(nome); /*comprimento do nome dado*/
    for (i = 0; i < tamanho; i++) /*o ciclo torna o hash value mais aleatorio*/
    {
        hash = hash + (nome[i] ^ 3);
        hash = hash + (nome[i] * nome[i]);
        hash = (hash * nome[i]) % HASH_SIZE;
    }
    return hash;
}

/* Funcoes para fazer os frees necessarios*/
void free_jogos(jogo *hash[HASH_SIZE])
{
    int i;
    jogo *aux_1, *aux_2;
    for (i = 0; i < HASH_SIZE; i++)
    {
        if (hash[i] != NULL)
        {
            for (aux_1 = hash[i]; aux_1 != NULL; aux_1 = aux_2)
            {
                aux_2 = aux_1->next;
                free(aux_1->equipa_1);
                free(aux_1->equipa_2);
                free(aux_1->nome_jogo);
                free(aux_1);
            }
        }
    }
}

void free_equipas(equipa *hash[HASH_SIZE])
{
    int i;
    equipa *aux_1, *aux_2;
    for (i = 0; i < HASH_SIZE; i++)
    {
        if (hash[i] != NULL)
        {
            for (aux_1 = hash[i]; aux_1 != NULL; aux_1 = aux_2)
            {
                aux_2 = aux_1->next;
                free(aux_1->nome_equipa);
                free(aux_1);
            }
        }
    }
}

void free_listas(node *head)
{
    node *aux_1, *aux_2;
    aux_1 = head;
    while (aux_1 != NULL)
    {
        aux_2 = aux_1->next;
        free(aux_1);
        aux_1 = aux_2;
    }
    free(aux_1);
}

/* Funcao que cria o novo jogo que verifica os argumentos e que retorna o jogo*/
jogo * Comando_a(int contador, equipa *hash_1[HASH_SIZE], jogo *hash_2[HASH_SIZE])
{
    char string_nome[MAX_STRING];
    char string_nome_1[MAX_STRING]; /*vetores auxiliares*/
    char string_nome_2[MAX_STRING];

    equipa *aux_1, *aux_2;
    jogo *novo_jogo, *jogo_aux;
    novo_jogo = (jogo*) can_fail_malloc(sizeof(jogo)); /*aloca espaco para o novo jogo*/

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", 
    string_nome, string_nome_1, string_nome_2, 
    &novo_jogo->score_1, &novo_jogo->score_2);

    /* Alocacao do espaco necessario para as strings*/
    novo_jogo->nome_jogo = (char*) can_fail_malloc((strlen(string_nome)+1) * sizeof(char));
    novo_jogo->equipa_1 = (char*) can_fail_malloc((strlen(string_nome_1)+1) * sizeof(char));
    novo_jogo->equipa_2 = (char*) can_fail_malloc((strlen(string_nome_2)+1) * sizeof(char));

    strcpy(novo_jogo->nome_jogo, string_nome);
    strcpy(novo_jogo->equipa_1, string_nome_1);
    strcpy(novo_jogo->equipa_2, string_nome_2);

    jogo_aux = hash_table_jogo_lookup(novo_jogo->nome_jogo, hash_2);
    aux_1 = hash_table_equipa_lookup(novo_jogo->equipa_1, hash_1);
    aux_2 = hash_table_equipa_lookup(novo_jogo->equipa_2, hash_1);
    /* No caso de ja existir um jogo com este nome */
    if (jogo_aux != NULL && strcmp(jogo_aux->nome_jogo, novo_jogo->nome_jogo) == 0)
    {
        printf("%d Jogo existente.\n", contador);
        free(novo_jogo->equipa_1);
        free(novo_jogo->equipa_2);
        free(novo_jogo->nome_jogo);
        free(novo_jogo);
        return NULL;
    }
    /* No caso de uma ou duas equipas nao existirem */ 
    if (aux_1 == NULL || aux_2 == NULL)
    {
        printf("%d Equipa inexistente.\n", contador);
        free(novo_jogo->equipa_1);
        free(novo_jogo->equipa_2);
        free(novo_jogo->nome_jogo);
        free(novo_jogo);
        return NULL;
    }
    else
    {
        /* Se a primeira equipa ganhou*/
        if (novo_jogo->score_1 > novo_jogo->score_2)
        {
            aux_1->vitorias++; 
        }
        /* Se a segunda equipa ganhou*/
        if (novo_jogo->score_1 < novo_jogo->score_2)
        {
            aux_2->vitorias++;
        }
        return novo_jogo;
    }
}

/* Funcao que cria uma equipa, verifica os argumentos e que retorna a equipa*/
equipa * Comando_A(int contador, equipa *hash[HASH_SIZE])
{
    char string_nome_equipa[MAX_STRING];
    equipa *nova_equipa, *equipa_aux;
    nova_equipa = (equipa*) can_fail_malloc(sizeof(equipa));
    
    scanf(" %[^\n]", string_nome_equipa);
    nova_equipa->nome_equipa = (char*) can_fail_malloc((strlen(string_nome_equipa)+1) 
    * sizeof(char)); /* aloca o espaco para o nome da equipa */
    strcpy(nova_equipa->nome_equipa, string_nome_equipa);

    equipa_aux = hash_table_equipa_lookup(nova_equipa->nome_equipa, hash);
    /* Se a equipa ja existir */
    if (equipa_aux != NULL && 
    strcmp(equipa_aux->nome_equipa, nova_equipa->nome_equipa) == 0)
    {
        printf("%d Equipa existente.\n", contador);
        free(nova_equipa->nome_equipa);
        free(nova_equipa);
        return NULL;
    }
    else
    {
        return nova_equipa;
    }
}

/* Funcao que excuta o comando l */
int Comando_l(int contador, node *head)
{
    node *aux_1;
    jogo *aux_3;
    int aux_2;
    aux_2 = contador;
    if (head != NULL) /*so faz printfs se existirem jogos */
    {
        for (aux_1 = head; aux_1 != NULL; aux_1 = aux_1->next)
        {
            aux_3 = aux_1->jogo;
            printf("%d %s %s %s %d %d\n", aux_2, aux_3->nome_jogo,
            aux_3->equipa_1, aux_3->equipa_2, aux_3->score_1, aux_3->score_2);
        }
    }
    return aux_2;
}

/* Funcao que executa o comando p*/
void Comando_p(int contador, jogo *hash[HASH_SIZE])
{
    char nome[MAX_STRING];
    jogo *aux;
    scanf(" %[^:\n]", nome);
    aux = hash_table_jogo_lookup(nome, hash);
    /* se o jogo nao existir */
    if (aux == NULL)
    {
        printf("%d Jogo inexistente.\n", contador);
    }
    else
    {
        printf("%d %s %s %s %d %d\n",contador, aux->nome_jogo, aux->equipa_1, 
        aux->equipa_2, aux->score_1, aux->score_2);
    }
}

/* Funcao que executa o comando P*/
void Comando_P(int contador, equipa *hash[HASH_SIZE])
{
    char nome[MAX_STRING];
    equipa *aux;
    scanf(" %[^\n]", nome);
    aux = hash_table_equipa_lookup(nome, hash);
    /* se a equipa nao existir */
    if (aux == NULL)
    {
        printf("%d Equipa inexistente.\n", contador);
    }
    else
    {
        printf("%d %s %d\n",contador, aux->nome_equipa, aux->vitorias);
    }
}

/* Funcao que elimina um jogo do sistema*/
jogo * Comando_r(int contador, jogo *hash_1[HASH_SIZE], equipa *hash_2[HASH_SIZE])
{
    char nome[MAX_STRING];
    jogo *aux_1;
    equipa *equipa_aux;
    scanf(" %[^:\n]", nome);
    aux_1 = hash_table_jogo_lookup(nome, hash_1);
    /* se o jogo nao existir */
    if (aux_1 == NULL)
    {
        printf("%d Jogo inexistente.\n", contador);
        return NULL;
    }
    else
    {
        /* se a equipa_1 ganhou */
        if (aux_1->score_1 > aux_1->score_2)
        {
            equipa_aux = hash_table_equipa_lookup(aux_1->equipa_1, hash_2);
            equipa_aux->vitorias--;
        }
        /* se a equipa_2 ganhou */
        if (aux_1->score_1 < aux_1->score_2)
        {
            equipa_aux = hash_table_equipa_lookup(aux_1->equipa_2, hash_2);
            equipa_aux->vitorias--;
        }
        return aux_1;
    }
}

/* Funcao que altera o score de um jogo */
node * Comando_s(int contador, jogo *hash_1[HASH_SIZE], equipa *hash_2[HASH_SIZE], node *head)
{
    char nome[MAX_STRING];
    int score_1, score_2, score_orig_1, score_orig_2;
    jogo *aux_1;
    node *aux_2;
    equipa *equipa_1, *equipa_2;
    scanf(" %[^:\n]:%d:%d", nome, &score_1, &score_2);
    aux_1 = hash_table_jogo_lookup(nome, hash_1);
    /* se o jogo nao existir */
    if (aux_1 == NULL)
    {
        printf("%d Jogo inexistente.\n", contador);
    }
    else
    {
        /*guarda os scores originais para comparar com os novos*/
        score_orig_1 = aux_1->score_1;
        score_orig_2 = aux_1->score_2;
        /*altera os scores na hash table de jogos*/
        aux_1->score_1 = score_1;
        aux_1->score_2 = score_2;
        aux_2 = lista_lookup(nome, head);
        /*altera os scores na lista*/
        aux_2->jogo->score_1 = score_1;
        aux_2->jogo->score_2 = score_2;
        /*procura as equipas em questao na hash table de equipas*/
        equipa_1 = hash_table_equipa_lookup(aux_1->equipa_1, hash_2);
        equipa_2 = hash_table_equipa_lookup(aux_1->equipa_2, hash_2);
        /*se a equipa_1 inicialmente tinha ganho */
        if (score_orig_1 > score_orig_2)
        {
            /*se no novo score ha empate */
            if (score_1 == score_2)
            {
                equipa_1->vitorias--;
            }
            /*se no novo score a equipa_1 perdeu*/
            else if (score_1 < score_2)
            {
                equipa_1->vitorias--;
                equipa_2->vitorias++;
            }
        }
        /*se a equipa_1 inicialmente perdeu */
        else if (score_orig_1 < score_orig_2)
        {
            /*se no novo score ha empate */
            if (score_1 == score_2)
            {
                equipa_2->vitorias--;
            }
            /*se no novo score a equipa_2 perdeu*/
            if (score_1 > score_2)
            {
                equipa_2->vitorias--;
                equipa_1->vitorias++;
            }
        }
        /*no caso de originalmente ter havido um empate*/
        else
        {
            /*se no novo score a equipa_1 perdeu*/
            if (score_1 < score_2)
            {
                equipa_2->vitorias++;
            }
            /*se no novo score a equipa_2 perdeu*/
            if (score_1 > score_2)
            {
                equipa_1->vitorias++;
            }
        }
    }
    return head;
}

/* Funcao auxiliar para comparar strings*/
int Compara_strings(const void *string_1,const void *string_2)
{
    const char *p_string_1, *p_string_2;
    p_string_1 = *(const char**)string_1;
    p_string_2 = *(const char**)string_2;
    return strcmp(p_string_1, p_string_2);
}

/* Funcao que executa o comando g*/
int Comando_g(int contador, equipa *hash[HASH_SIZE])
{
    int max_vitorias, index_matriz, existe, cont, i, j, k;
    char *vetor_strings[MAX_STRING];
    equipa *aux_1, *aux_2, *aux_3, *aux_4;
    max_vitorias = 0;
    index_matriz = 0;
    cont = contador;
    existe = 0;
    /*ciclos para percorrer a hash table de equipas*/
    for (i = 0; i < HASH_SIZE; i++)
    {
        aux_1 = hash[i];
        for (aux_2 = aux_1; aux_2 != NULL; aux_2 = aux_2->next)
        {
            if (aux_2->vitorias >= max_vitorias)
            {
                max_vitorias = aux_2->vitorias;
                existe = 1; /*se alguma equipa tiver pelo menos 1 vitoria*/
            } 
        }
    }
    if (existe == 1)
    {
        /* percorre a hash table em procura das equipas com max vitorias*/
        for (k = 0; k < HASH_SIZE; k++)
        {
            aux_3 = hash[k];
            for (aux_4 = aux_3; aux_4 != NULL; aux_4 = aux_4->next)
            {
                if (aux_4->vitorias == max_vitorias)
                {
                    /*guarda os nomes das equipas num vetor*/
                    vetor_strings[index_matriz] = aux_4->nome_equipa;
                    index_matriz++;
                } 
            }
        }
        /*faz sort do vetor com as strings por ordem alfabetica*/
        qsort(vetor_strings, index_matriz, sizeof(char *), Compara_strings);
        printf("%d Melhores %d\n", cont, max_vitorias);
        for (j = 0; j < index_matriz; j++)
        {
            printf("%d * %s\n", cont, vetor_strings[j]);
        } 
    }    
    return cont;
}