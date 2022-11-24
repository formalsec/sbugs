#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogos_linked.h"
#include "jogos_hash.h"
#include "equipas.h"
#include "cmds.h"
#include "aux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funcao que dado um jogo lista-o na forma:
    * nl nome-jogo nome-equipa1 nome-equipa2 score1 score2*/
void escreve_jogo(int * nl, JOGO * jogo)
{
    printf("%d %s %s %s %d %d\n", 
            *nl, jogo -> nome, jogo -> equipa1, 
            jogo -> equipa2, jogo -> score1, jogo -> score2);
}

/*Funcao que dado um nome remove da hashtable_jogos e da lista_de_jogos 
    o jogo referente a esse nome.*/
void remove_jogo(JOGO_HASH ** hashtable_jogos, JOGO_LIST * lista_de_jogos, char * nome)
{
    JOGO * jogo_eliminar = procura_jogo(hashtable_jogos, nome);

    remove_jogo_hash(hashtable_jogos, nome);
    remove_jogo_linked(lista_de_jogos, jogo_eliminar);
}

/*Funcao que liberta a memoria alocada pela hashtable_jogos e pela lista_de_jogos.*/
void destroy_jogos(JOGO_HASH ** hashtable_jogos, JOGO_LIST * lista_de_jogos)
{
    destroy_jogos_linked(lista_de_jogos);
    destroy_jogos_hash(hashtable_jogos);
}

/*Funcao que cria uma lista (lista_nomes) com os nomes das equipas existentes 
    em hashtable_equipas que contem um score igual a maior_score.*/
void cria_lista_nomes(char ** lista_nomes, EQUIPA ** hashtable_equipas, int maior_score)
{
    int i, len_str, indice = 0;
    EQUIPA * tmp = NULL;

    for(i = 0; i < TAM_HASH; i++)
    {
/*tmp representa a head da lista ligada atual referente a chave (i) da hashtable*/
        tmp = hashtable_equipas[i];

        while(tmp != NULL)
        {
            if (tmp -> score == maior_score)
            {
                len_str = strlen(tmp -> nome);
/*aloca memoria do tipo char necessaria para guardar a string referente ao nome da equipa*/
                lista_nomes[indice] = can_fail_malloc(sizeof(char) * (len_str + 1));
                strcpy(lista_nomes[indice], tmp -> nome);

                indice++;
            }
            tmp = tmp -> next;
        }
    }
}

/*Funcao de comparacao de strings que correspondem aos nomes das equipas existentes
    na lista_nomes. 
    *funcao utilizada na funcao qsort().*/
int compara_nomes(const void * equipa1, const void * equipa2)
{
    char const * nome1 = *(const char **)equipa1;
    char const * nome2 = *(const char **)equipa2;

    return strcmp(nome1, nome2);
}
