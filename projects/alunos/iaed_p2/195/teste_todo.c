#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "Listas_ligadas.h"
#include "Listas_ligadas2.h"
#include "FUNCOES_PROTOTIPO_AUX.h"
#include "FUNCOES_PROTOTIPO_MAIN.h"
#include "FUNCOES_AUX.h"
#include "FUNCOES_MAIN.h"
#define MAX_CHARS 1024

/*--------------------------------------------------------------------------------*/

/*
ident1: val[0]
linha: val[1]
ident2: val[2]
controlOrd: val[3]
max_vit: val2[0]
len_vit: val2[1]
*/

/*Na funcao principal e definido as variaveis usar (nome de um jogo,equipas e pontuacoes),
e usada uma array chamada valores que contem como referido em cima a posicao na lista de jogos
de um nodo, a linha do stdin e a posicao na lista de vitorias*/


/*
E definido c como o char de controlo, que enqunato o c e diferente de x e atribuido um respetivo
char a c, de modo, a executar os comandos pretendidos para o projeto e e chamado a funcao do 
respetivo comando e se incrementado o indice 1 de valores (a linha do stdin), apos a chamada de
cada comando. Sendo no final libertada, toda a memoria alocada para as listas ligadas usadas no
projeto.
*/

int main()
{
    char c;char nome[MAX_CHARS];char team1[MAX_CHARS];char team2[MAX_CHARS];
    int pont1,pont2; int valores[4] = {0,1,0,0};
    int val2[2] = {0,0};
    link_v head2 = NULL; link head = NULL; link_v yf;link jf;
    while ((c = getchar())!= 'x') {
    switch (c) 
    {
        case 'A':
        {
            scanf("%1023[^:\n]",nome);
            remove_esp(nome);
            A(nome,&head2,valores);
            valores[1]++;
            break;
        }
        case 'a':
        {
            scanf("%1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d",nome,team1,team2,&pont1,&pont2);
            remove_esp(nome);
            a(&head,nome,valores,&head2,team1,team2,pont1,pont2);
            valores[1]++;
            break;
        }
        case 'l':
        {
            print_lista_jog(head,valores);
            valores[1]++;
            break;
        }
        case 'p':
        {
            scanf("%1023[^:\n]",nome);
            remove_esp(nome);
            p(&head,nome,valores);
            valores[1]++;
            break;
        }
        case 'P':
        {
            scanf("%1023[^:\n]",nome);
            remove_esp(nome);
            P(&head2,nome,valores);
            valores[1]++;
            break;
        }
        case 'r':
        {
            scanf("%1023[^:\n]",nome);
            remove_esp(nome);
            r(nome,&head,&head2,valores);
            valores[1]++;
            break;
        }
        case 's':
        {
            scanf("%1023[^:\n]:%d:%d",nome,&pont1,&pont2);
            remove_esp(nome);
            s(&head,nome,pont1,pont2,&head2,valores);
            valores[1]++;
            break;
        }
        case 'g':
        {
            g(&head2,valores,val2);
            valores[1]++;
            break;
        }
    }
    }
    for(yf = head2; yf != NULL; yf = yf->next){
        delete_el_v(yf,yf->v.nome);
    }
    for(jf = head; jf != NULL; jf = jf->next){
        delete_el_jog(jf,jf->game.nome);
    }
    return 0;
}
