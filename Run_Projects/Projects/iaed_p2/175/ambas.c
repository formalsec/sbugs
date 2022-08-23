#include "library.h"

/* devolve o indice da hashtable */
int hash(char*nome, int M) {
    int h = 0, a = 12737; 
    for (; *nome != '\0'; nome++) 
        h = (a*h + *nome) % M; 
    return h;
}

/* reserva memoria para o nome e devolve o endereco de memoria */
char* copia_string(char *nome) {
    char *ptr_n;
    int len_nome;
    len_nome = strlen(nome) + 1;
    ptr_n = (char*) malloc(len_nome * sizeof(char));
    strcpy(ptr_n,nome);
    return ptr_n;
}