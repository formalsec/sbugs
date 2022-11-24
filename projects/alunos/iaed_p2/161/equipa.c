#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"


/* cria um equipa e devolve um ponteiro para a equipa ------------------------------------------ */
pEquipa cria_equipa(char *nome)
{   
    /* aloca memoria para a estrutura equipa */
    pEquipa nova_equipa = (pEquipa) can_fail_malloc(sizeof(struct equipa));
   
    /* aloca memoria para o nome da equipa e copia-o */
    nova_equipa -> nome = (char*) can_fail_malloc(sizeof(char)*(1 + strlen(nome)));
    strcpy(nova_equipa -> nome, nome);
   
    
    nova_equipa -> num_vitorias = 0;
   
    return nova_equipa;
}


/* devolve o nome da equipa -------------------------------------------------------------------- */
char* obtem_nome_equipa(pEquipa equipa)
{
    return equipa -> nome;
}


/* devolve o numero de vitorias da equipa ------------------------------------------------------ */
int obtem_vitorias_equipa(pEquipa equipa)
{
    return equipa -> num_vitorias;
}


/* altera o numero de vitorias da equipa ------------------------------------------------------- */
void altera_vitorias_equipa(pEquipa equipa, int alteracao)
{
    equipa -> num_vitorias += alteracao;

    return;
}


/* escreve o nome e numero de vitorias da equipa ----------------------------------------------- */
void print_equipa(pEquipa equipa, unsigned int Num_Linha)
{
    printf("%u %s %u\n", Num_Linha, equipa -> nome, equipa ->num_vitorias);

    return;
}


/* liberta a memoria alocada para a equipa ----------------------------------------------------- */
void free_equipa(pEquipa equipa)
{

    free(equipa -> nome); /* liberta a memoria alocada para o nome */
    
    free(equipa); /* liberta a memoria alocada para a estrutura */

    return;
}


