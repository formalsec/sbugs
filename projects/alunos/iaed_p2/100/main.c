#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"

#define M 1049 /* Numero grande primo para o hashing */

int main() {
    unsigned long contador = 1; /* contador de inputs, incrementado apos cada input recebido */
    int i;
    char c;

    link t, t_aux;
    link_e x, x_aux;

    jogo_ptr j;
    equipa_ptr e;

    link *heads_jogos; /* ponteiro para a hastable de jogos */
    link_e *heads_equipas; /* ponteiro para a hastable de equipas */
    lst_ptr lista;  /* ponteiro para estrutura que contem a head e a tail de uma lista ligada de jogos */

    heads_jogos = (link*)can_fail_malloc(M*sizeof(link));
    heads_equipas = (link_e*)can_fail_malloc(M*sizeof(link_e));
    lista = (lst_ptr)can_fail_malloc(sizeof(list));

    lista->head = NULL; /* inicializacao da lista de jogos */
    lista->tail = NULL;

    hash_init_jogo(heads_jogos); /* inicializacao da hastable de jogos */
    hash_init_equipa(heads_equipas); /* inicializacao da hastable de equipas */

    while ((c = getchar()) != 'x') { /* enquanto a letra for diferente de x, o programa nao termina */
        switch (c){ /* corre a funcao correspondente ah letra lida no input e volta a ler uma nova letra */
            case 'a' :
                a(contador, heads_jogos, heads_equipas, lista);
                contador++;
                break;
            
            case 'l' :
                l(contador, lista);
                contador++;
                break;
            
            case 'p' :
                p(contador, heads_jogos);
                contador++;
                break; 
            
            case 'r' :
                r(contador, heads_jogos, heads_equipas, lista);
                contador++;
                break; 
            
            case 's' :
                s(contador, heads_jogos, heads_equipas);
                contador++;
                break; 
            
            case 'A' :
                A(contador, heads_equipas);
                contador++;
                break;
            
            case 'P' :
                P(contador, heads_equipas);
                contador++;
                break; 
            
            case 'g' :
                g(contador, heads_equipas);
                contador++;
                break; 
        }
    }

    /* FREES */

    for (i = 0; i < M; i++) { 
        for (t = heads_jogos[i]; t != NULL; t = t_aux) { /* Liberta cada lista ligada da hastable de jogos*/
            t_aux = t->next;
            j = t->j;
            free(j->nome);
            free(j->equipa1);
            free(j->equipa2);
            free(j);
            free(t);
        } 
        for (x = heads_equipas[i]; x != NULL; x = x_aux) { /* Liberta cada lista ligada da hastable de equipas*/
            x_aux = x->next;
            e = x->e;
            free(e->nome);
            free(e);
            free(x);
        } 
    }

    free(heads_jogos);
    free(heads_equipas);

    for (t = lista->head; t != NULL; t = t_aux) { /* Liberta os nos da lista ligada com todos os jogos */
            t_aux = t->next;
            free(t);  /* Basta libertar o noh porque os jogos ja foram libertados */
    }

    free(lista);

    return 0;
}
   