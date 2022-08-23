#ifndef _FUNCOES_PROTOTIPO_AUX_
#define _FUNCOES_PROTOTIPO_AUX_

/*Prototipo da funcao adiciona_eq*/
int adiciona_eq(char nome[],link_v* head,int valores[]);

int adiciona_jog(link *head,char nome[],char team1[],char team2[],int pont1,int pont2,link_v *head2
,int valores[]);

/*Prototipo da funcao altera_jog*/
int altera_jog(link head,char nome[],int pont1,int pont2,link_v head2);

/*Prototipo da funcao atribui_vit*/
void atribui_vit(char team1[],char team2[],int score1,int score2,link_v conj_vit);

/*Prototipo da funcao atribui_vit*/
void atribui_vit2(char team1[],char team2[],int score1_old,int score2_old,int score1,int score2,
link_v conj_vit);

/*Prototipo da funcao equipa_in*/
int equipa_in(link_v head, char nome[]);

/*Prototipo da funcao print_jog*/
int print_jog(link head, char nome[],int valores[]);

/*Prototipo da funcao print_vit*/
int print_vit(link_v head, char nome[],int valores[]);

/*Prototipo da funcao procura_vit_max*/
void procura_vit_max(link_v head,int val2[]);

/*Prototipo da funcao remove_esp*/
void remove_esp(char str[]);

/*Prototipo da funcao remove_jog*/
int remove_jog(link* head,char nome[],link_v* head2);

/*Prototipo da funcao MergeSort e dos suas funcoes auxiliares*/

void MergeSort(struct node_v** headRef);

struct node_v* SortedMerge(struct node_v* a, struct node_v* b);

void FrontBackSplit(struct node_v* source, 
                    struct node_v** frontRef, struct node_v** backRef);

#endif