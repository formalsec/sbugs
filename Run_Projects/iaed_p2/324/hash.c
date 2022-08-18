#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


int get_location(char *v)
{
    int h = 0, a = 127;
    /*Ciclo que vai a cada caracter da string e da um valor do indice dessa string*/
    for (; *v != '\0'; v++)
        h = (a*h + *v) % HASHTABLE_SIZE;
    return h;
}

/**************************************************************************************************/

node ** get_hashtables()
{
    /*Aloca espaco para criar uma hash de jogos*/
    node ** hashtable = calloc(HASHTABLE_SIZE, sizeof(node*));
    return hashtable;
}

/**************************************************************************************************/

e_node ** get_hashtable_equipa()
{
    /*Aloca espaco para criar uma hash de equipas*/
    e_node ** hashtable = calloc(HASHTABLE_SIZE, sizeof(e_node*));
    return hashtable;
}
/**************************************************************************************************/