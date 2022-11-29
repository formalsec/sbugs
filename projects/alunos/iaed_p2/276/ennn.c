#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 700
#define CAPACITY 10000

int NL = 0;
int n_jogos=0;

typedef struct {
    char name[MAX_NOME];
    char equipa1 [MAX_NOME];
    char equipa2 [MAX_NOME];
    int s1;
    int s2;
}jogo;

jogo lista[300];

typedef struct {
    char nome[MAX_NOME];
    int vitorias;
}equipa;

jogo *hash_table[CAPACITY];
equipa *hash_tableE[CAPACITY];

void init_table(){
    int i;
    for (i = 0;i<CAPACITY;i++)
    {
        hash_table[i] = NULL;
    }
}

void init_hashE(){
    int i ;
    for (i = 0 ; i < CAPACITY; i++)
    {
        hash_tableE[i] = NULL;
    }
}

size_t hash ( char *string){
    size_t tl = 5407;
    for (;*string;string++)
    {
        tl = (tl * 47) + (*string);
    }
    return (tl%CAPACITY);
}


int hash_table_insert (jogo *p){
    int index = hash(p->name);
    int i , tentar;
    if (p == NULL)
        return 0;
    for (i = 0; i < CAPACITY;i++)
    {
        tentar = (i+index) % CAPACITY;
        if (hash_table[tentar] ==  NULL)
        {
            hash_table[tentar] = p;
            return 1;
        }
    }
    return 0;
}

int hash_table_insertE (equipa *p){
    int index = hash(p->nome);
    int i , tentar;
    if (p == NULL)
        return 0;
    for (i = 0; i < CAPACITY;i++)
    {
        tentar = (i+index) % CAPACITY;
        if (hash_tableE[tentar] ==  NULL)
        {
            hash_tableE[tentar] = p;
            return 1;
        }
    }
    return 0;
}

 jogo *hash_table_lookup (char *name){
    int index = hash(name);
    int i,tentar;
    for (i=0; i <CAPACITY;i++)
    {
        tentar =(index + i) % CAPACITY;
        if (hash_table[tentar] == NULL){
            return NULL; /*NOT HERE */
        }
        if (hash_table[tentar] != NULL &&
            strncmp(hash_table[tentar] ->name,name, CAPACITY) == 0)
            {
                return hash_table[tentar];
            }
    }
    return NULL;
 }

 equipa *hash_table_lookupE (char *name){
    int index = hash(name);
    int i,tentar;
    for (i=0;i<CAPACITY;i++)
    {
        tentar = (index + i) % CAPACITY;
        if(hash_tableE[tentar] == NULL){
            return NULL; /*NOT HERE*/
        }
        if (hash_tableE[tentar] != NULL &&
            strncmp(hash_tableE[tentar]->nome,name,CAPACITY) == 0)
            {
                return hash_tableE[tentar];
            }
    }
    return NULL;
 }

 jogo *hash_table_delete(char *name){
    int index = hash(name);
    int i,tentar;
    for (i=0; i <CAPACITY;i++)
    {
        tentar =(index + i) % CAPACITY;
        if (hash_table[tentar] == NULL)
            return NULL;
        if (hash_table[tentar] != NULL &&
            strncmp(hash_table[tentar] ->name,name, CAPACITY) == 0)
            {
                jogo *tmp = hash_table[tentar];
                hash_table[tentar] = NULL;
                return tmp;
            }
    }
    return NULL;
 }

 void a(void) {
    jogo game;
    scanf("%[^\n:]:%[^\n:]:%[^\n:]:%d:%d",game.name,game.equipa1,game.equipa2,&game.s1,&game.s2);
    if (hash_table_lookup(game.name) != NULL)
    {
        printf("%d Jogo existente.\n",NL);
        return;
    }
    if ((hash_table_lookupE(game.equipa1) != NULL) && (hash_table_lookupE(game.equipa2)!= NULL))
    {
        hash_table_insert(&game);
        lista[n_jogos] = game;
        n_jogos++;
        if (game.s1 > game.s2)
            hash_table_lookupE(game.equipa1)->vitorias ++;
        if (game.s2 > game.s1)
            hash_table_lookupE(game.equipa2)->vitorias ++;
        return;
    }
    printf("%d Equipa inexistente.\n",NL);
}

void A(void) {
    equipa e;
    scanf("%[^\n:]:%d",e.nome,&e.vitorias);
    if (hash_table_lookupE(e.nome) != NULL)
    {
        printf("%d Equipa existente.\n",NL);
        return;
    }
    e.vitorias = 0;
    hash_table_insertE(&e);
}

void l(void){
    int i=0;
    if (n_jogos == 0)
        return;
    for (i=0; i<n_jogos;i++)
    {
        printf("%d %s %s %s %d %d\n" ,NL,lista[i].name,lista[i].equipa1,lista[i].equipa2,lista[i].s1,lista[i].s2);
    }
}

void p(void){
    jogo game;
    scanf("%[^\n:]",game.name);
    if (hash_table_lookup(game.name) == NULL)
    {
       printf("%d Jogo inexistente.\n",NL);
        return;
    }
    printf("%d %s %s %s %d %d\n",NL,game.name,game.equipa1,game.equipa2,game.s1,game.s2);
}

void r(void){
    jogo game;
    scanf("%[^\n:]",game.name);
    if (hash_table_lookup(game.name) == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }
    hash_table_delete(game.name);
    n_jogos --;
}

void s(void){
    jogo game;
    int s1,s2,i;
    scanf("%[^\n:]:%d:%d",game.name,&s1,&s2);
    if (hash_table_lookup(game.name) == NULL)
    {
        printf("%d Jogo inexistente.",NL);
        return;
    }
    for (i=0;i<n_jogos;i++)
    {
        if (strcmp(lista[i].name,game.name)==0)
        {
            game.s1 = s1;
            game.s2 = s2;
        }
    }
    hash_table_lookup(game.name)->s1 = s1;
    hash_table_lookup(game.name)->s2 = s2;
}

 void P(void){
    equipa team;
    scanf("%[^\n:]",team.nome);
    if (hash_table_lookupE(team.nome) == NULL)
    {
       printf("%d Equipa inexistente.\n",NL);
       return;
    }
    printf("%d %s %d\n",NL,team.nome,team.vitorias);
}


int main() {
    char b ='h' ;

    init_hashE();
    init_table();

    while (b != 'x')
        {
        scanf("%c", &b);

        switch (b)
        {
            case 'a':
                a();
                NL++;
                break;

            case 'l':
                l();
                NL++;
                break;

            case 'p':
                p();
                NL++;
                break;

            case 'r':
                r();
                NL++;
                break;

            case 's':
                s();
                NL++;
                break;

            case 'A':
                A();
                NL++;
                break;

            case 'P':
                P();
                NL++;
                break;

            case 'g':
                NL++;
                break;

            case 'x':
                return 0;
        }
    return 0;
    }
}
