#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

char * cria_pchar(char str[]) {

    char * n = (char *) can_fail_malloc (sizeof(char) * (strlen(str) + 1));

    strcpy(n, str);

    return n;

}

Item cria_item(char * n, char * e1, char * e2, int s1, int s2) {
    
    Item item = (Item) can_fail_malloc (sizeof(struct item));

    item -> nome = n;
    item -> e1 = e1;
    item -> e2 = e2;
    item -> s1 = s1;
    item -> s2 = s2;
    item -> vitorias = 0;

    return item;

} 

void free_item(Item item) {

    free(item -> nome);
    free(item -> e1);
    free(item -> e2);
    free(item);

}

void imprime_jogo(Item j, int NL) {

    printf("%d %s %s %s %d %d\n", NL, j -> nome, j -> e1, j -> e2, j -> s1, j -> s2);

}

Item vencedor(char * e1, char * e2, int s1, int s2, Hashtable hasht) {

    if (s1 < s2)
        return procura_hash(e2, hasht);
    
    else if (s1 > s2) 
        return procura_hash(e1, hasht);

    else
        return NULL;

}

int compara(const void * a, const void * b) { 

    char **v1, **v2;
    v1 = (char **) a;
    v2 = (char **) b;
    return strcmp(*v1, *v2);

}
