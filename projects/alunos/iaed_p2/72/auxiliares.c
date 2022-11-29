#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "auxiliares.h"

/*
  get_string: (char*) -> int
  Le uma string da stdin ate encontrar o carater ':' ou '\n' ou exceder o
  limite de carateres lidos STR_MAX; Retorna o numero de carateres lidos
*/
int get_string(char* arg){
    char c;
    int i = 0;

    c = getchar();
    while(c != ':' && c != '\n' && i < MAX_STR - 1){
        arg[i++] = c;
        c = getchar();
    }

    /*Limpa a stdin ate encontrar ':', '\n' ou EOF*/
    while(c != ':' && c != '\n')
        c = getchar();

    /*Termina a string com null byte*/
    arg[i++] = '\0';

    return i;
}

/*
  hash: (char*,int) -> int
  Faz hash de uma string que consiste num inteiro entre 0 e m
*/
int hash(char* s, int m){
    int i = 0;
    unsigned int sum = 0;

    /*Implementacao da funcao de hash de Jenkins*/
    while(s[i] != '\0'){
      sum += s[i++];
      sum += sum << 10;
      sum ^= sum >> 6;
    }

    sum += sum << 3;
    sum ^= sum >> 11;
    sum += sum << 15;
    
    return sum % m;
}

/*
  compara_strings: (const void *, count void *) -> int
  Funcao para ser usada com o qsort para ordenar char**
*/
int compara_strings(const void *ptr1, const void *ptr2) { 
    /*converte const void* para strings*/
    const char **str1 = (const char **)ptr1;
    const char **str2 = (const char **)ptr2;

    /*compara as strings*/
    return strcmp(*str1, *str2);
} 
