#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj2_h.h"

int hash_s(char *v, int M){		/*Criar chave para a hashtable*/
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h;
}

int get_higher_score(list_e *ls_e, list_e *ls_v){	/*Retornar o maior numero de jogos ganhos*/
	int maior=0;									/*e editar ls_v para conter esses jogos*/
	link_e t,t1;
	for(t = ls_e->head; t; t = t->next){
		if (t->jogos_ganhos>maior){
            for(t1 = ls_v->head; t1; t1 = ls_v->head)
                delete_e(ls_v,t1);
			maior=t->jogos_ganhos;
		}
		if (t->jogos_ganhos==maior){
            insertEnd_e(ls_v,t->nome);
		}
	}
	return maior;
}

int cstring_cmp(const void *a, const void *b){		/*Funcao auxiliar para o qsort()*/
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}
