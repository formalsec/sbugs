#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_equipa.h"

int M;
equipa **head_hash_e;
jogo **head_hash_j;

/*Funcao auxiliar que serve para comparar strings*/
int string_cmp(const void *a, const void *b)
{
 const char **ia = (const char **)a;
 const char **ib = (const char **)b;
 return strcmp(*ia, *ib);
}

/*Funcao que recebe duas listas de equipas (uma principal e outra temporaria) e
 * devolve o maior numero de vitorias*/
int maior_aux(lista_e *principal, lista_e *temp){
    int maior=0;
    equipa*d;
    equipa*d1;
    for(d = principal->head; d; d = d->next){
        if (d->vitorias>maior){
            for(d1 = temp->head; d1; d1 = temp->head)
                rm_equipa(temp,d1);
            maior=d->vitorias;
        }
        if (d->vitorias==maior){
            add_last_equipa(temp,d->nome);
        }
    }
    return maior;
}

int main(){
    int y=0;
    int o,k=0;
    jogo*n;
    char d;
    char t[1023];
    char s[1023];
    char r[1023];
    lista_e*ls=mk_lista_e();                                                                            /*Inicializa a lista das equipas.*/
    lista_j*lk=mk_lista_j();                                                                            /*Inicializa a lista dos jogos.*/
    M=50077;
    init_hash_equipa(M);                                                                                /*Inicializa a hash table das equipas.*/
    init_hash_jogo(M);                                                                                  /*Inicializa a hash table dos jogos.*/
    do
    {
        switch (d=getchar())
        {

        /*Adiciona um novo jogo*/
        case 'a':
            getchar();
            y++;
            scanf("%[^:]:%[^:]:%[^:]:%d:%d",t,s,r,&k,&o);
            if(lookup_j(t)==NULL){
                if((lookup_e(s)!=NULL)&&(lookup_e(r)!=NULL)){
                    add_last_jogo(lk,t,(lookup_e(s)),(lookup_e(r)),k,o);                                /*Adiciona o jogo a lista dos jogos.*/
                    hash_jogo_insert(lk->last);                                                         /*Adiciona o jogo a hash table dos jogos.*/
                    if(k>o){
                        (lookup_e(s))->vitorias+=1;                                                     /*Altera o numero de vitorias dependendo do resultado do jogo*/
                        break;
                    }
                    if(k<o){
                        (lookup_e(r))->vitorias+=1;
                         break;
                    }
            }else
                printf("%d Equipa inexistente.\n",y);
            }else
                printf("%d Jogo existente.\n",y);
            break;

        /*Adiciona uma nova equipa*/
        case 'A':
            getchar();
            y++;
            scanf("%[^:\n]",s);
            if(lookup_e(s)!=NULL)
                printf("%d Equipa existente.\n",y);
            else{
                add_last_equipa(ls,s);                                                      /*Adiciona o jogo a lista das equipas.*/
                hash_equipa_insert(ls->last);                                               /*Adiciona o jogo a hash table das equipas.*/
            }
            break;

        /*Procura uma equipa*/
        case 'P':
            getchar();
            y++;
            scanf("%[^:\n]",r);
            if(lookup_e(r)==NULL)                                                            /*Verifica se a equipa existe.*/
                printf("%d Equipa inexistente.\n",y);
            else
                printf("%d %s %d\n",y,(lookup_e(r))->nome,(lookup_e(r))->vitorias);
            break;

        /*Procura um jogo*/
        case 'p':
            getchar();
            y++;
            scanf("%[^:\n]",t);
            if(lookup_j(t)==NULL)                                                           /*Verifica se o jogo existe.*/
                printf("%d Jogo inexistente.\n",y);
            else
                printf("%d %s %s %s %d %d\n",y,(lookup_j(t))->nome,(lookup_j(t))->e1->nome,(lookup_j(t))->e2->nome,(lookup_j(t))->resultado1,(lookup_j(t))->resultado2);
            break;

        /*Lista todos os jogos por ordem de insercao*/
        case 'l':
            y++;
            for(n=lk->head;n;n=n->next){                                                                                        /*Percorre a lista dos jogos.*/
                if(lookup_j(n->nome)!=NULL)
                    printf("%d %s %s %s %d %d\n",y,n->nome,n->e1->nome,n->e2->nome,n->resultado1,n->resultado2);                /*Print pela ordem de insercao.*/
            }
            break;

        /*Altera o resultado de um jogo*/
        case 's':{
            jogo* a;
            getchar();
            y++;
            scanf("%[^:]:%d:%d",t,&k,&o);
            a=lookup_j(t);
            if(a!=NULL){                                                                          /*Procura o jogo inserido.*/
                if(k>o &&(a->resultado1)<(a->resultado2)){                                        /*Analise de todos os casos possiveis, modificando assim o numero de vitorias.*/
                    a->e1->vitorias+=1;
                    a->e2->vitorias-=1;
                }
                else if(k>o &&(a->resultado1)==(a->resultado2)){
                    a->e1->vitorias+=1;
                }
                else if(k==o &&(a->resultado1)>(a->resultado2)){
                    a->e1->vitorias-=1;
                }
                else if(k==o &&(a->resultado1)<(a->resultado2)){
                    a->e2->vitorias-=1;
                }
                else if(k<o &&(a->resultado1)>(a->resultado2)){
                    a->e1->vitorias-=1;
                    a->e2->vitorias+=1;
                }
                else if(k<o &&(a->resultado1)==(a->resultado2)){
                    a->e2->vitorias+=1;
                }
                a->resultado1=k;                                                        /*Atribuicao do novo resultado*/
                a->resultado2=o;
            }
            else
                printf("%d Jogo inexistente.\n",y);
            break;
        }

        /*Remove um jogo*/
        case 'r':{
            jogo*a;
            getchar();
            y++;
            scanf("%[^:\n]",t);
            a=lookup_j(t);                                                              /*Procura o jogo inserido.*/
            if(a!=NULL){
                if(a->resultado1>a->resultado2){
                    a->e1->vitorias-=1;
                }
                else if(a->resultado1<a->resultado2){
                    a->e2->vitorias-=1;
                }
                hash_delete_j(t);                                                       /*Apagamos o jogo da hash table dos jogos.*/
                rm_jogo(lk,a);                                                          /*Apagamos o jogo da lista dos jogos.*/
            }else
                printf("%d Jogo inexistente.\n",y);
            break;
        }

        /*Encontra as equipas que venceram mais jogos. Se existir mais que uma, lista por ordem alfabetica*/
        case 'g':{
            int i, count, maior;
            char **temp;                                                                /*Criacao de um array temporario.*/
            equipa*t;
            lista_e*ls_temp = mk_lista_e();                                             /*Inicializa-se uma lista de equipas temporaria.*/
            maior=maior_aux(ls,ls_temp);
            y++;
            count=0;

                for(t = ls_temp->head; t; t = t-> next)                                 /*Quando o loop acabar, o count ira ser igual ao numero de equipas existentes.*/
                    count++;

                temp=can_fail_malloc(sizeof(char*)*(count+1));                                   /* O array temporario ira assim ter o tamanho "ideal".*/

                for(i=0,t=ls_temp->head;t;i++,t=t->next){
                    temp[i]=can_fail_malloc(sizeof(char)*(strlen(t->nome)+1));
                    strcpy(temp[i],t->nome);
                }

                qsort(temp, i, sizeof(char *), string_cmp);                             /*Ordena-se os elementos do array por ordem alfabetica.*/

                for(i=0;i!=count;i++){
                    if (i==0)
                        printf("%d Melhores %d\n",y, maior);                            /*Print dos elementos do array temporario ja ordenados.*/
                    printf("%d * %s\n",y, temp[i]);
                }

                for(i=0;i!=count;i++){                                                  /*Free de cada elemento do array temporario.*/
                    free(temp[i]);
                }

                for(t = ls_temp->head; t; t = ls_temp->head)                            /*Removemos todas as equipas da lista temporaria.*/
                    rm_equipa(ls_temp,t);

                free(ls_temp);                                                          /*Free da lista temporaria.*/
                free(temp);                                                             /*Free do array temporario.*/
                break;
            }
        }

    /*Termina o loop.*/
    }while (d!='x');
    free(head_hash_e);              /*Free da hash table das equipas.*/
    free(head_hash_j);              /*Free da hash table dos jogos.*/
    free_list_equipa(ls);           /*Free da lista das equipas.*/
    free_list_jogo(lk);             /*Free da lista dos jogos.*/
    return 0;
}
