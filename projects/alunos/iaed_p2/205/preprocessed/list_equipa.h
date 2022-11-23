#ifndef LIST_EQUIPA_H
#define LIST_EQUIPA_H
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <string.h>
    #include "equipa.h"

    typedef struct node_equipa {
        struct Equipa *equipa;
        struct node_equipa *next;
    } NodeEquipa;

    typedef NodeEquipa *link_equipa;

    link_equipa list_equipa_init(Equipa* equipa);
    link_equipa list_equipa_insert_begin(link_equipa head, Equipa* equipa);
    link_equipa list_equipa_insert_end(link_equipa head, Equipa* equipa);
    link_equipa list_equipa_insert_sorted(link_equipa head, Equipa* equipa);
    link_equipa list_equipa_lookup(link_equipa head, Equipa* equipa);
    void list_equipa_print(link_equipa head,int nl);
    link_equipa list_equipa_delete(link_equipa head, Equipa* equipa);
 

#endif


