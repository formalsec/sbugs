#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj2_h.h"

int main(){
    list_j *ls_j = mk_list_j();		/*Criar lista duplamente ligada para os jogos*/
    list_e *ls_e = mk_list_e();		/*Criar lista duplamente ligada para as equipas*/
	
	/*Variaveis para a leitura dos inputs*/
	char command;
	char n[1024];
	char e1[1024];
	char e2[1024];
	int s1;
	int s2;
	
	int count=1;			/*Count=NL*/

	Init_hash_j(107);		/*Criar hashtable para os jogos*/
    Init_hash_e(107);		/*Criar hashtable para as equipas*/

	do{
		switch (command=getchar()){
			case 'a':{
				link_e eq1;
				link_e eq2;
				link_e venc;

				getchar();
				scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",n,e1,e2,&s1,&s2);

				eq1=lookup_e(e1);
				eq2=lookup_e(e2);

				if (lookup_j(n)==NULL){				/*Verificar se jogo ainda nao existe*/
					if (eq1!=NULL && eq2!=NULL){	/*Verificar se equipas existem*/
							insertEnd_j(ls_j,n,eq1,eq2,s1,s2);
							insert_h_j(ls_j->last);
							if (s1!=s2){
                                if (s1>s2)
                                    venc=eq1;
                                else if (s1<s2)
                                    venc=eq2;
                                venc->jogos_ganhos+=1;
                            }
                    }
					else
						printf("%d Equipa inexistente.\n", count);
				}
				else
					printf("%d Jogo existente.\n", count);
                break;
			}

			case 'A':{
				getchar();

				scanf("%[^:\n]",n);
                if (lookup_e(n)==NULL){		/*Verificar se equipa ainda nao existe*/
                    insertEnd_e(ls_e,n);
                    insert_h_e(ls_e->last);
                }
                else
                    printf("%d Equipa existente.\n", count);
				break;
			}
			case 'l':{
				link_j t;
                for(t = ls_j->head; t != NULL; t = t->next)
                    printf("%d %s %s %s %d %d\n",count,t->nome,t->equ1->nome,t->equ2->nome,t->sco1,t->sco2);
				break;
			}
			case 'p':{
                link_j t;
                getchar();
				scanf("%[^:\n]",n);

                t=lookup_j(n);	/*Procurar por jogo*/
                if (t!=NULL){
                    printf("%d %s %s %s %d %d\n",count,t->nome,t->equ1->nome,t->equ2->nome,t->sco1,t->sco2);
                }
                else
                    printf("%d Jogo inexistente.\n", count);
				break;
			}
			case 'P':{
				link_e t;
                getchar();
				scanf("%[^:\n]",n);

                t=lookup_e(n);	/*Procurar por equipa*/
                if (t!=NULL)
                    printf("%d %s %d\n", count,t->nome,t->jogos_ganhos);
                else
                    printf("%d Equipa inexistente.\n", count);
				break;
			}
			case 'r':{
                link_j j;
                getchar();
				scanf("%[^:\n]",n);
                j=lookup_j(n);

                if (j!=NULL){
                    s1=j->sco1;
                    s2=j->sco2;
                    if (s1!=s2){
                        if (s1>s2)
                            j->equ1->jogos_ganhos-=1;
                        else if (s1<s2)
                            j->equ2->jogos_ganhos-=1;
                    }

                    delete_h_j(j);
                    delete_j(ls_j,j);
                }
                else
                    printf("%d Jogo inexistente.\n", count);
				break;
			}
			case 's':{
				link_j t;
                getchar();
				scanf("%[^:\n]:%d:%d",n,&s1,&s2);

                t=lookup_j(n);
                if (t!=NULL){
                    if (t->sco1==t->sco2 && s1>s2)
                        t->equ1->jogos_ganhos++;
                    else if (t->sco1==t->sco2 && s1<s2)
                        t->equ2->jogos_ganhos++;


                    else if (t->sco1>t->sco2 && s1==s2)
                        t->equ1->jogos_ganhos--;
                    else if (t->sco1>t->sco2 && s1<s2){
                        t->equ1->jogos_ganhos--;
                        t->equ2->jogos_ganhos++;
                    }


                    else if (t->sco1<t->sco2 && s1==s2)
                        t->equ2->jogos_ganhos--;
                    else if (t->sco1<t->sco2 && s1>s2){
                        t->equ1->jogos_ganhos++;
                        t->equ2->jogos_ganhos--;
                    }

                    t->sco1=s1;
                    t->sco2=s2;
                }
                else
                    printf("%d Jogo inexistente.\n", count);
				break;
			}
			case 'g':{
                link_e t;
				list_e *ls_v = mk_list_e();			/*Lista duplamente ligada com as equipas */
				int i, i1, maior;					/*com maior numero de vitorias*/
				char **arr;

				i1=0;
				maior=get_higher_score(ls_e, ls_v);	/*Maior=maior numero de vitorias*/

				for(t = ls_v->head; t; t = t-> next)
                    i1++;

				arr=can_fail_malloc(sizeof(char*)*(i1+1));	/*Lista com strings com maior numero de vitorias*/

                for(i=0,t=ls_v->head;t;i++,t=t->next){
                    arr[i]=can_fail_malloc(sizeof(char)*(strlen(t->nome)+1));
					strcpy(arr[i],t->nome);
                }

                qsort(arr, i, sizeof(char *), cstring_cmp);

				for(i=0;i!=i1;i++){
                    if (i==0)
                        printf("%d Melhores %d\n",count, maior);
                    printf("%d * %s\n",count, arr[i]);
				}

				for(i=0;i!=i1;i++){
					free(arr[i]);
				}

                for(t = ls_v->head; t; t = ls_v->head)
                    delete_e(ls_v,t);

                free(ls_v);
                free(arr);
				break;
			}
			case 'x':{		/*Dar free em toda a memoria alocada*/

				link_j t;
				link_e t1;

				for(t = ls_j->head; t;t = ls_j->head){
					delete_h_j(t);
					delete_j(ls_j,t);
				}


				for(t1 = ls_e->head; t1; t1 = ls_e->head){
					delete_h_e(t1);
					delete_e(ls_e,t1);
				}
				free(ls_j);
				free(ls_e);
				free(head_h_e);
				free(head_h_j);
				break;
			}
		}
		getchar();
        count++;
	}while (command!='x');
	return 0;
}
