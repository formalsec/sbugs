#ifndef _LISTA_CHAR_
#define _LISTA_CHAR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"


int comparar_nome(const void*nome1,const void*nome2);
link insere_el_char(link head,Equipa *equipa);
link destroi(link head);

#endif

