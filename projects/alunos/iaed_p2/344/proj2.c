#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int select_letter();
void add_team();
void formats_input();
void lookup_team();
void add_game();
void print_table();
char new_str[3100];

typedef struct team {
char*name;
unsigned long int nwinner;
}*pTeam;

typedef struct game{
    char*name2;
    char*hteam;
    char*ateam;
    unsigned long int hscore;
    unsigned long int ascore;
}*pGame;

pTeam search2(char* name2);
static int M;
static pTeam *st;
static pGame *st1;
pTeam team3; 

int hash1(char *v, int M)
{
int h = 0, a = 127;
for (; *v != '\0'; v++)
h = (a*h + *v) % M;
return h;
}

void Stinit(int m) {
int i; M=m;
st = (pTeam*)can_fail_malloc(M*sizeof(pTeam));
for (i = 0; i < M; i++)
st[i] = NULL; /* inicializo tudo a NULL */
}

void STinsert(char*name, unsigned long int twinner) {
int i = hash1(name, M);
while (st[i]!=NULL) i = (i+1) % M;
st[i] = can_fail_malloc(sizeof(struct team));
st[i]->nwinner=twinner;
st[i]->name = name;
}


void Stinit2(int m) {
int i; M=m;
st1 = (pGame*)can_fail_malloc(M*sizeof(pGame));
for (i = 0; i < M; i++)
st1[i] = NULL; /* inicializo tudo a NULL */
}

void STinsert2(char*name2, char*hteam, char*ateam, unsigned long int hscore, unsigned long int ascore) {
int i = hash1(name2, M);
while (st[i]!=NULL) i = (i+1) % M;
st1[i] = can_fail_malloc(sizeof(struct game));
st1[i]->hscore=hscore;
st1[i]->ascore=ascore;
st1[i]->name2 = name2;
st1[i]->hteam = hteam;
st1[i]->ateam = ateam;
}

int main(){

    Stinit(10);
    Stinit2(10);
    while(select_letter());


    return 0;
}

/* Selects the command for each letter given */
int select_letter(){
    char command;

    command = getchar();
    switch (command){
        case 'A': add_team(); return 1;

        case 'P': lookup_team(); return 1;

        case 'a': add_game(); return 1;

        case 'l': print_table(); return 1;

        case 'x': return 0;  /* Ends the program */

        default: return 1;
    }
}

void add_team(){
    char team2[1024];
    formats_input();
    sscanf(new_str, "%s", team2);
    if(search2(team2) == NULL)
    
        STinsert(team2, 0);
    else
        printf("NL Equipa existente.\n");
}

void formats_input(){
    int i2=0, c;
    while ((c = getchar()) != '\n')
    {
        if (c == ':'){
            c = ' ';
            new_str[i2] = c;
            i2++;
        }
        else
        {
            new_str[i2] = c;
            i2++;
        }
    }
   new_str[i2] = '\0';     
}

pTeam search2(char* name2)
{
int i = hash1(name2, M);
while (st[i] != NULL)
    if (strcmp(st[i]->name, name2)==0){
        return st[i];
    }

    else{
        i = (i+1) % M;
    }
return NULL;

}

void lookup_team()
{
    char team2[1024];
    formats_input();
    sscanf(new_str, "%s", team2);
    team3 = search2(team2);
    if(team3 == NULL){
    
        printf("NL Equipa inexistente.\n");
    }
    else{
        printf("NL %s %lu\n", team3->name, team3->nwinner);
    }
}

void add_game(){
    char gamename[1024];
    char hname[1024];
    char aname[1024];
    long unsigned int hscore1;
    long unsigned int ascore1;

    formats_input();
    sscanf(new_str, "%s%s%s%lu%lu", gamename, hname, aname, &hscore1, &ascore1);
    STinsert2(gamename, hname, aname, hscore1, ascore1);
}

void print_table(){
    int i;
    for(i=0; i< 10; i++){
        if(st1[i] == NULL){
        
        }
        else{
            printf("NL %s %s %s %lu %lu\n", st1[i]->name2, st1[i]->hteam, st1[i]->ateam, st1[i]->hscore, st1[i]->ascore);
        }
    }
}