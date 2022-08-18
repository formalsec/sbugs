#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

int  main() {

    char c;
    int NL = 0; /* Variavel que indica numero da linha de comando */

    struct node * head = NULL; /* Cria lista para jogos */
    
    Hashtable hash_e, hash_j; /* Cria hashtables para equipas e jogos */

    hash_e = cria_hash(21001);
    hash_j = cria_hash(21001);

    while ((c = getchar())!= 'x') {
        switch (c) {
            case 'a':
                NL++;
                __a__(NL, hash_j, hash_e, &head);
                break;

            case 'A':
                NL++;
                __A__(NL, hash_e);
                break;

            case 'l':
                NL++;
                __l__(NL, head);
                break;

            case 'p':
                NL++;
                __p__(NL, hash_j);
                break;

            case 'P':
                NL++;
                __P__(NL, hash_e);
                break;

            case 'r':
                NL++;
                __r__(NL, hash_j, hash_e, &head);
                break;
            
            case 's':
                NL++;
                __s__(NL, hash_j, hash_e);
                break;
            
            case 'g':
                NL++;
                __g__(NL, hash_e);
                break;
                
        }
    }

    liberta_hash(hash_e); 
    liberta_hash(hash_j);
    liberta_lista(head);

    return 0;

}
