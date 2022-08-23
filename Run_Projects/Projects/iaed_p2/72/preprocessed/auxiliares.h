#ifndef AUXILIARES_H_INCLUDE
#define AUXILIARES_H_INCLUDE

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*tamanho maximo para strings incluindo \0*/
#define MAX_STR 1024

/*PROTOTIPOS*/
int get_string(char* arg);
int hash(char* s, int m);
int compara_strings(const void *ptr1, const void *ptr2);

#endif
