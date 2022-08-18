#include "abstract.h"     /* Contem as bibliotecas standard */
#include "commands.h"     /* Declaracao dos comandos */
#include "hash_equipas.h" /* Declaracao das funcoes da Hashtable equipas */
#include "hash_jogos.h"   /* Declaracao das funcoes da Hashtable jogos */
#include "lista_jogos.h"  /* Declaracao das funcoes da Lista jogos */

#define HASHJOGOS 80000   /* Tamanho da Hastable dos jogos */
#define HASHEQUIPAS 10000 /* Tamanho da Hastable das equipas */

int main()
{
    int M = HASHJOGOS;
    int m = HASHEQUIPAS;
    int *numeq = malloc(sizeof(int)); /* Aloca memoria para o numero de equipas no sistema */
    int NL = 0;
    char c;
    list *jogos = LS_jg_init();        /* Inicializa a Lista dos jogos */
    link_eq *heads_eq = HT_eq_init(m); /* Inicializa a Hashtable das equipas */
    link_jg *heads_jg = HT_jg_init(M); /* Inicializa a Hashtable dos jogos */
    *numeq = 0;
    for (;;) /* Ciclo do programa */
    {
        /* Invocacao das funcoes para os comandos individuais */
        scanf("%c", &c); /* Verifica a letra do comando respetivo */
        switch (c)
        {
        case 'a': cmd_a(heads_jg, heads_eq, jogos, M, m, ++NL); break;

        case 'l': cmd_l(jogos, heads_jg, M, ++NL); break;

        case 'p': cmd_p(heads_jg, M, ++NL); break;

        case 'r': cmd_r(heads_jg, jogos, M, ++NL); break;

        case 's': cmd_s(heads_jg, M, ++NL); break;

        case 'A': cmd_A(heads_eq, m, numeq, ++NL); break;

        case 'P': cmd_P(heads_eq, m, ++NL); break;

        case 'g': cmd_g(heads_eq, m, numeq, ++NL); break;

        case 'x':
            HT_eq_destroy(heads_eq, m); /* Destroi a Hashtable equipas */
            HT_jg_destroy(heads_jg, M); /* Destroi a Hashtable jogos */
            freeList(jogos);            /* Destroi a Lista jogos */
            free(numeq);                /* Liberta o numero de equipas no sistema */
            return 0;
            break; /* Condicao de termino */

        default: break;
        }
    }

    return 0;
}