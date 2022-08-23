#ifndef LIST_JOGO_H
#define LIST_JOGO_H
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <string.h>
    #include "jogo.h"

    typedef struct node_jogo{
        struct Jogo *jogo;
        struct node_jogo *next;
    } NodeJogo;

    typedef NodeJogo *link_jogo;

    link_jogo list_jogo_init(Jogo* jogo);
    link_jogo list_jogo_insert_begin(link_jogo head, Jogo* jogo);
    link_jogo list_jogo_insert_end(link_jogo head, Jogo* jogo);
    link_jogo list_jogo_lookup(link_jogo head, Jogo* jogo);
    void list_jogo_print(link_jogo head,int nl);
    link_jogo list_jogo_delete(link_jogo head, Jogo* jogo);
 

#endif


