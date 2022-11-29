#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "main_f.h"

/* funcao main inicializa as hash tables e as listas ligadas e efetua os comandos do programa*/
int main(){
    int NL = 1;
    bloco_hash_equipa *table_e, *lista_e ;                               /* hash table equipas lista de todas as equipas */
    bloco_hash_jogo *table_j, *lista_j_ord_h, *lista_j_ord_t;            /* hash table jogos head e tail da lista de todos os jogos */
    lista_j_ord_h = can_fail_malloc(sizeof(bloco_hash_jogo));                     /* guarda memoria para a head da lista ligada */       
    lista_j_ord_t = can_fail_malloc(sizeof(bloco_hash_jogo));                     /* guarda memoria para a tail da lista ligada */
    lista_e = can_fail_malloc(sizeof(bloco_hash_equipa));                         /* guarda memoria para a lista das equipas */
    lista_j_ord_h[0] = NULL; lista_j_ord_t[0] = NULL; lista_e[0] = NULL; /* inicializa heads e tails a NULL para impedir q se percorra um node vazio */
    table_e = inicializa_hash_e() ; table_j = inicializa_hash_j();       /* inicializa todas as posicoes de ambas as hashs a NULL */
    while(1){      
        char c;  
        c=getchar();  
    switch(c){                                                           /* le o input e associa o ao comando a efetuar*/
        case 'A':
            A(table_e,lista_e,NL);
            NL++;
            break;
        case 'a':
            a(table_j,table_e,lista_j_ord_h,lista_j_ord_t,NL);
            NL++;
            break;
        case 'P':
            P(table_e,NL); 
            NL++;   
            break;
        case 'p':
            p(table_j,NL);
            NL++;
            break;
        case 's':
            s(table_j,table_e,NL);
            NL++;
            break;
        case 'r':
            r(table_j,lista_j_ord_h,lista_j_ord_t,NL);
            NL++;
            break;
        case 'l':
            l(lista_j_ord_h,NL);
            NL++;
            break;
        case 'g':
            g(lista_e,NL);
            NL++;
            break;
        case 'x':
            x(table_e,lista_e,table_j,lista_j_ord_h,lista_j_ord_t);
            return 0;
        }
    } 
    return 0;
}
