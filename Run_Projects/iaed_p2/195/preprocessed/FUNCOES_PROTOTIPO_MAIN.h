#ifndef _FUNCOES_PROTOTIPO_MAIN_
#define _FUNCOES_PROTOTIPO_MAIN_

/*Funcao prototipo da funcao a (representa o comando a)*/

void a(link* head,char nome[],int valores[],link_v* head2, char team1[],char team2[],
int pont1,int pont2);

/*Funcao prototipo da funcao p (representa o comando p)*/

void p(link* head,char nome[],int valores[]);

/*Funcao prototipo da funcao r (representa o comando r)*/

void r(char nome[],link* head,link_v* head2,int valores[]);

/*Funcao prototipo da funcao s (representa o comando s)*/

void s(link* head,char nome[],int pont1,int pont2,link_v* head2,int valores[]);

/*Funcao prototipo da funcao A (representa o comando A)*/

void A(char nome[],struct node_v** head2,int valores[]);

/*Funcao prototipo da funcao P (representa o comando P)*/

void P(link_v* head2,char nome[],int valores[]);

/*Funcao prototipo da funcao g (representa o comando g)*/

void g(link_v* head2,int valores[],int val2[]);

#endif