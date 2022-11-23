#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash.h"

#include "linkedlist.h"

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

/*numero maximo de caracteres dos nomes*/  
#define MAX_CAR 1023

/* funcao que recebe duas hashtables uma lista e o numero da linha e adiciona o jogo a
   hashtable dos jogos e a lista caso nao haja erros*/
void adiciona_jogo(link1* hashtable1, link2* hashtable2, list* lista, int m){

    char nome[MAX_CAR], equipa1[MAX_CAR], equipa2[MAX_CAR];
    
    int score1, score2;     

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

    if (STsearchJ(nome, hashtable1, TAMHASH) != NULL){
        printf("%d Jogo existente.\n", m);
    }
    else if (STsearchE(equipa1, hashtable2, TAMHASH) == NULL || STsearchE(equipa2, hashtable2, TAMHASH) == NULL){
        printf("%d Equipa inexistente.\n", m);
    }
    else {
        STinsertJ(nome, equipa1, equipa2, score1, score2, hashtable1, TAMHASH);
        add_last(lista, nome);
        if (score1 > score2){
            link2 hashtable = STsearchE(equipa1, hashtable2, TAMHASH);
            ++hashtable->vitorias;
        }
        else if (score2 > score1){
            link2 hashtable = STsearchE(equipa2, hashtable2, TAMHASH);
            ++hashtable->vitorias;
        }
    }
}

/* funcao que recebe uma hashtable uma lista e o numero da linha e que da print aos jogos 
   pela ordem que foram introduzidos */
void lista_jogos(link1* hashtable, list* lista, int m){

    link1 x;  
    for (x = lista->head; x != NULL; x = x->next){
        link1 hash = STsearchJ(x->Jogo->nome, hashtable, TAMHASH);
        printf("%d %s %s %s %d %d\n", m, hash->Jogo->nome, hash->Jogo->equipa1, hash->Jogo->equipa2, hash->Jogo->score1, hash->Jogo->score2);
    }      
}

/* funcao que recebe uma hashtable e o numero da linha caso nao haja nenhum erro
   da print ao jogo com nome igual ao do input */
void procura_jogo(link1* hashtable, int m){

    char nome[MAX_CAR];

    scanf(" %[^:\n]", nome);

    if (STsearchJ(nome, hashtable, TAMHASH) == NULL){
        printf("%d Jogo inexistente.\n", m);
    }
    else {
        link1 hash = STsearchJ(nome, hashtable, TAMHASH);
        printf("%d %s %s %s %d %d\n", m, nome, hash->Jogo->equipa1, hash->Jogo->equipa2, hash->Jogo->score1, hash->Jogo->score2);
    }
}
/* funcao que recebe duas hashtables uma lista e o numero da linha caso nao haja
   nenhum erro apaga o jogo da hashtable dos jogos e da lista */
void apaga_jogo(link1* hashtable1, link2* hashtable2, list* lista, int m){

    char nome[MAX_CAR];

    scanf(" %[^:\n]", nome);

    if (STsearchJ(nome, hashtable1, TAMHASH) == NULL){
        printf("%d Jogo inexistente.\n", m);
    }
    else {
        link1 hash1 = STsearchJ(nome, hashtable1, TAMHASH);
        link2 hash2 = STsearchE(hash1->Jogo->equipa1, hashtable2, TAMHASH);
        link2 hash3 = STsearchE(hash1->Jogo->equipa2, hashtable2, TAMHASH);
        link1 node = search(lista, nome);
        if (hash1->Jogo->score1 > hash1->Jogo->score2){
            --hash2->vitorias; 
        }
        else if (hash1->Jogo->score1 < hash1->Jogo->score2){
            --hash3->vitorias;
        }
        rm_node(lista, node);
        STdelete(nome, hashtable1, TAMHASH); 
    }
}

/* funcao que recebe duas hashtables e o numero da linha caso nao haja
   nenhum erro altera os scores do jogo com o mesmo nome do input pelos novos scores */
void altera_score(link1* hashtable1, link2* hashtable2, int m){
    
    char nome[MAX_CAR];

    int score1, score2;

    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);

    if (STsearchJ(nome, hashtable1, TAMHASH) == NULL){
        printf("%d Jogo inexistente.\n", m);
    }
    else {
        link1 hash1 = STsearchJ(nome, hashtable1, TAMHASH);
        link2 hash2 = STsearchE(hash1->Jogo->equipa1, hashtable2, TAMHASH);
        link2 hash3 = STsearchE(hash1->Jogo->equipa2, hashtable2, TAMHASH);
        if (score1 > score2){
            if (hash1->Jogo->score1 < hash1->Jogo->score2){
                ++hash2->vitorias;
                --hash3->vitorias;
            }
            else if (hash1->Jogo->score1 == hash1->Jogo->score2){
                ++hash2->vitorias;
            }
        }      
        else if (score1 < score2){
            if (hash1->Jogo->score1 > hash1->Jogo->score2){
                --hash2->vitorias;
                ++hash3->vitorias;
            }
            else if(hash1->Jogo->score1 == hash1->Jogo->score2){
                ++hash3->vitorias;
            }
        }
        else if (score1 == score2){
            if (hash1->Jogo->score1 < hash1->Jogo->score2){
                --hash3->vitorias;
            }
            else if (hash1->Jogo->score1 > hash1->Jogo->score2){
                --hash2->vitorias;
            }    
        } 
        hash1->Jogo->score1 = score1;    
        hash1->Jogo->score2 = score2;
    }
}

/* funcao que recebe uma hashtable e o numero da linha caso nao haja erros 
   adiciona a hashtable das equipas a equipa com o nome do input */
void adiciona_equipa(link2* hashtable, int m){
    
    char nome[MAX_CAR]; 

    scanf(" %[^:\n]", nome);

    if (STsearchE(nome, hashtable, TAMHASH) != NULL){
        printf("%d Equipa existente.\n", m);       
    }
    else {
        STinsertE(nome, hashtable, TAMHASH);
    }
}

/* funcao que recebe uma hashtable e o numero da linha caso nao haja erros
   da print a equipa com o mesmo nome do input e o numero de vitorias */
void procura_equipa(link2* hashtable, int m){
     
    char nome[MAX_CAR];

    scanf(" %[^:\n]", nome);

    if (STsearchE(nome, hashtable, TAMHASH) == NULL){
        printf("%d Equipa inexistente.\n", m);
    }
    else {
        link2 hash = STsearchE(nome, hashtable, TAMHASH);
        printf("%d %s %d\n", m, nome, hash->vitorias);
    }
}

/* funcao auxiliar que serve para organizar por ordem lexicografica */
int ordena(const void * a, const void * b){

    node2 *x = *(node2 **)a;
    node2 *y = *(node2 **)b;
    return strcmp(x->equipa, y->equipa);
}

/* funcao que recebe uma hashtable e o numero da linha e da print as equipas
   por ordem lexicografica com maior numero de vitorias */
void lista_equipas(link2* hashtable, int m){

    int i, n = 0, max_vitorias = 0;
    link2 x;
    link2 a[TAMHASH];     

    for (i = 0; i < TAMHASH; i++){
        for (x = hashtable[i]; x != NULL; x = x->next){
            if (x->vitorias > max_vitorias){
                max_vitorias = x->vitorias;
            } 
        }
    }

    for (i = 0; i < TAMHASH; i++){
        for (x = hashtable[i]; x != NULL; x = x->next){
            if (x->vitorias == max_vitorias){
                a[n] = x;
                ++n;
            } 
        }
    }

    if (n != 0){
        qsort(a, n, sizeof(node2*), ordena);
        printf("%d Melhores %d\n", m, max_vitorias);
        for (i = 0; i < n; i++){
            printf("%d * %s\n", m, a[i]->equipa);
        }
    } 
}

/* funcao que recebe duas hashtables e uma lista e que liberta a memoria alocada */
void termina(link1* hashtable1, link2* hashtable2, list* lista){
    
    int i;
    link1 w, x; 
    link2 y, z;
    
    for (i = 0; i < TAMHASH; i++){
        x = hashtable1[i];
        while (x != NULL){
            w = x->next;
            free(x->Jogo->nome);
            free(x->Jogo->equipa1);
            free(x->Jogo->equipa2);
            free(x->Jogo);
            free(x);
            x = w;
        }
        y = hashtable2[i];   
        while (y != NULL){
            z = y->next;
            free(y->equipa);
            free(y);
            y = z;
        }
    }
    free_list(lista); 
    free(hashtable1);
    free(hashtable2);
}

/* funcao que inicializa as hashtables e a lista ligada e que realiza
   diversas funcoes dependendo do comando introduzido no input */
int main(){

    char c;

    int NL = 1;

    link2* hashequipa = STinitE(TAMHASH);

    link1* hashjogo = STinitJ(TAMHASH);

    list* lista =  mk_list();

    for (;;){

        switch (c = getchar()){

            case 'a':

                adiciona_jogo(hashjogo, hashequipa, lista, NL);
                ++NL;
                break;

            case 'l':

                lista_jogos(hashjogo, lista, NL);
                ++NL;
                break;

            case 'p':

                procura_jogo(hashjogo, NL);
                ++NL;
                break;

            case 'r':

                apaga_jogo(hashjogo, hashequipa, lista, NL);
                ++NL;
                break;

            case 's':

                altera_score(hashjogo, hashequipa, NL);
                ++NL;
                break;

            case 'A':

                adiciona_equipa(hashequipa, NL);
                ++NL;
                break;

            case 'P':

                procura_equipa(hashequipa, NL);
                ++NL;
                break;

            case 'g':

                lista_equipas(hashequipa, NL);
                ++NL;
                break;
            
            case 'x':

                termina(hashjogo, hashequipa, lista);
                return 0;
                break;
        }
    }
    return 0;
}