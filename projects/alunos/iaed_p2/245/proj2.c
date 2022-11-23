#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include "auxiliares.h"     /* Header file que contem os defines relativos as funcoes auxiliares */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


/*  Funcao main
    Esta funcao seleciona os comandos a executar utilizando um switch case
    para todas as funcoes pedidas no enunciado. */
int main() {
    int NL = 0; 
    char n;
    char s[MAX], espaco; 
    Lista_equipas *lista_equipa = criar_lista(); 
    hashtable_equipas *ht_equipa = criar_equipas();
    hashtable_jogos *ht_jogos = criar_jogos();
    Lista_jogos *lista_jogo = criar_lista_j(); 

    while(1) {
        scanf("%c", &n);
        switch(n) {
            case 'a':
                NL += 1;
                scanf("%c", &espaco);
                fgets(s, MAX, stdin);
                a(NL, s, ht_jogos, ht_equipa, lista_jogo); 
                break;
            
            case 'l':
                NL += 1;
                l(NL, lista_jogo);
                break;
            
            case 'p':
                NL += 1;
                scanf("%c", &espaco);
                scanf("%[^:\n]", s);
                p(NL, s, ht_jogos);
                break;

            case 'r':
                NL += 1;
                scanf("%c", &espaco);
                scanf("%[^:\n]", s);
                r(NL, s, ht_jogos, ht_equipa, lista_jogo); 
                break;
            
            case 's':
                NL += 1;
                scanf("%c", &espaco);
                fgets(s, MAX, stdin);
                s_altera(NL, s, ht_jogos, ht_equipa, lista_jogo); 
                break;
                        
            case 'A':
                NL += 1;
                scanf("%c", &espaco);
                scanf("%[^:\n]", s);
                A(NL, s, ht_equipa, lista_equipa);
                break;
            
            case 'P':
                NL += 1;
                scanf("%c", &espaco);
                scanf("%[^:\n]", s);
                P(NL, s, ht_equipa);
                break;
          
            case 'g':
                NL += 1;
                g(NL, lista_equipa, ht_equipa);
                break; 
            
            case 'x':
            /*    libertar_jogos(ht_jogos); */
                liberta_lista(lista_jogo);
                libertar_equipas(ht_equipa); 
                liberta_lista_equipas(lista_equipa);
                return 0;
                break;
        }
    }
    return 0;
} 