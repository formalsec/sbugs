#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shared.h"




/*000000000000000000000000000000000
00000000000000000000000000000000000

    asci

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*getting the int of a caracter*/
int asci(char caracter)
{
    return caracter;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    hash

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*hash function*/
int hash(char *name)
{
    unsigned i=0, soma=0, firm=13, code=0, size=strlen(name);
    /*for every caracter of the name*/
    for(; i<size; i++)
    {
        soma += asci(name[i]) * firm * i;
    }
    code = soma % 517;
    return code;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    strduplicate

00000000000000000000000000000000000    
000000000000000000000000000000000*/

char* strduplicate(char *txt)
{
    /*alocate a array with the exact size*/
    char *aux = (char*)malloc(sizeof(char)*(strlen(txt)+1));
    /*copy the exact text*/
    strcpy(aux, txt);
    return aux;
}