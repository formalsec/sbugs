#include "library.h"

int main()
{   
    int NL = 1;
    char c = '\0';
    /* tamanho das hastables */
    int j = 983, e = 1021;
    
    ptr_jogo* h_jogo = NULL,*head_jogo = NULL, *tail_jogo = NULL;
    ptr_equipa* h_equipa = NULL, *head_equipa = NULL, *tail_equipa = NULL;

    /* inicializacao das tabelas */
    h_equipa = Init_hash_equipa(e,h_equipa);
    head_equipa = Init_hash_equipa(1,head_equipa);
    tail_equipa = Init_hash_equipa(1,tail_equipa);

    h_jogo = Init_hash_jogo(j,h_jogo);
    head_jogo = Init_hash_jogo(1,head_jogo);
    tail_jogo = Init_hash_jogo(1,tail_jogo);
    
    while (c != 'x')
    {   
        c = getchar();
        
        switch(c)
        {   
        case 'a':
            novo_jogo(NL, h_jogo, h_equipa, j, e, head_jogo, tail_jogo, head_equipa, tail_equipa);
            NL += 1;
            break;
        case 'A':
            nova_equipa(NL, h_equipa, e, head_equipa, tail_equipa);
            NL += 1;
            break;
        case 'l':
            lista_jogos(NL, head_jogo);
            NL +=1;
            break;
        case 'p':
            procura_jogo(NL, h_jogo, j);
            NL += 1;
            break;
        case 'P':
            procura_equipa(NL, h_equipa, e);
            NL += 1;
            break;
        case 'r':
            r_jogo(NL, h_jogo, head_jogo, tail_jogo, j,head_equipa,tail_equipa);
            NL += 1;
            break;
        case 's':
            altera_score(NL,h_jogo,j,head_equipa,tail_equipa);
            NL += 1;
            break;
        case 'g':
            melhores_equipas(NL,head_equipa);
            NL += 1;
            break;
        }
    }
/* Free das hashtables e das heads e tails das filas */
    free(head_equipa);
    free(tail_equipa);
    free(head_jogo);
    free(tail_jogo);

    free_hash_equipa(e,h_equipa);
    free_hash_jogo(j,h_jogo);
    return 0;  
}