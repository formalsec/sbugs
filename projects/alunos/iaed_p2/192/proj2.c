#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* SISTEMA DE GESTAO DE BASE DADOS DE JOGOS AMIGAVEIS*/

typedef struct stru_node_equipa{
      struct stru_node_equipa *next;
      char *nome;
      int vitorias;
    }*node_equipa;

typedef struct stru_node_jogo{
      struct stru_node_jogo *next;
      char *name;
      node_equipa equipa1,equipa2;
      int golos_casa;
      int golos_fora;
    }*node_jogo;

typedef struct node_queue{
  node_jogo jogo;
  struct node_queue *prev;
  struct node_queue *next;
}*Q;

typedef struct stru_list{
  Q head,tail;
}*list;

void init_teamhash(int m,node_equipa *equipas){
  int j;
  for(j=0;j<m;j++)
    equipas[j]=NULL;
}
 void init_gamehash(int n,node_jogo *jogos){
  int j;
  for(j=0;j<n;j++)
    jogos[j]=NULL;
}
Q init_node_queue(){
  node_jogo aux;
  Q q,auxiliar;
  auxiliar=(Q)can_fail_malloc(sizeof(struct node_queue));
  q=auxiliar;

  aux=(node_jogo)can_fail_malloc(sizeof(struct stru_node_jogo));
  q->jogo=aux;

  auxiliar=(Q)can_fail_malloc(sizeof(struct node_queue));
  q->prev=auxiliar;
  free(auxiliar);

  auxiliar=(Q)can_fail_malloc(sizeof(struct node_queue));
  q->next=auxiliar;
  free(auxiliar);
  q->prev=NULL;
  q->next=NULL;
  return q;
}
list init_list(){
  Q auxiliar;
  list q;
  q=(list)can_fail_malloc(sizeof(struct stru_list));
  auxiliar=(Q)can_fail_malloc(sizeof(struct node_queue));
  q->head=auxiliar;
  free(auxiliar);
  auxiliar=(Q)can_fail_malloc(sizeof(struct node_queue));
  q->tail=auxiliar;
  free(auxiliar);
  q->head=q->tail=NULL;
  return q;
}
int hash_str(char *v,int M){
  int h,a=31415,b=27183;
  for(h=0;*v!='\0';v++,a=a*b%(M-1))
    h=(a*h + *v)%M;
  return h;
  }
node_equipa insere_equipa(node_equipa equipas,char *nome){
  node_equipa team;
  team=(node_equipa)can_fail_malloc(sizeof(struct stru_node_equipa));
  team->nome = can_fail_malloc(strlen(nome)+1);
  team->vitorias=0;
  strcpy(team->nome,nome);
  team->next=equipas;
  return team;
}

int search_game(node_jogo head,char* nome_do_jogo){
  node_jogo x;
  for(x=head;x!=NULL;x=x->next){
    if (strcmp(x->name,nome_do_jogo)==0){
      return 1;
      break;
    }
  }
  return 0;
}
int search_team(node_equipa head_equipa,char* team){
  node_equipa x;
  for(x=head_equipa;x!=NULL;x=x->next){
    if (strcmp(x->nome,team)==0){
      return 1;
      break;
    }
  }
  return 0;
}
void insert(int input,node_equipa *equipas,int m){
  int i;
  char nome[1024];
  scanf(" %[^:\n]",nome);
  i=hash_str(nome,m);
  if (search_team(equipas[i],nome)==1){
    printf("%d Equipa existente.\n",input);
  }
  else{
  equipas[i]=insere_equipa(equipas[i],nome);
}
}
Q novo_no(char* nome_do_jogo,int m,char* team1,char* team2,int golos_casa,int golos_fora,node_equipa *equipas,Q next){
  int i=hash_str(team1,m),j=hash_str(team2,m);
  Q new,aux_next,aux_prev;
  node_equipa h,aux;
  new=(Q)can_fail_malloc(sizeof(struct node_queue));
  aux_next=(Q)can_fail_malloc(sizeof(struct node_queue));
  new->next=aux_next;
  free(aux_next);
  aux_prev=(Q)can_fail_malloc(sizeof(struct node_queue));
  new->prev=aux_prev;
  free(aux_prev);
  new->jogo=(node_jogo)can_fail_malloc(sizeof(struct stru_node_jogo));
  new->jogo->name=(char*)can_fail_malloc(strlen(nome_do_jogo)+1);
  strcpy(new->jogo->name,nome_do_jogo);
  for(h=equipas[i];h!=NULL;h=h->next){
    if (strcmp(h->nome,team1)==0) {
      aux=(node_equipa)can_fail_malloc(sizeof(struct stru_node_equipa));
      new->jogo->equipa1=aux;
      free(aux);
      new->jogo->equipa1=h;
      break;
    }
  }
  for(h=equipas[j];h!=NULL;h=h->next){
    if (strcmp(h->nome,team2)==0){
      aux=(node_equipa)can_fail_malloc(sizeof(struct stru_node_equipa));
      new->jogo->equipa2=aux;
      free(aux);
      new->jogo->equipa2=h;
      break;
    }
  }
  new->jogo->golos_casa=golos_casa;
  new->jogo->golos_fora=golos_fora;
  new->prev=next;
  new->next=NULL;
  return new;
}

node_jogo insere_jogo(char* nome_do_jogo,int m,int n,char* team1,char* team2,int golos_casa,int golos_fora,node_jogo *jogos,node_equipa *equipas,list l){
  int i=hash_str(team1,m),j=hash_str(team2,m),k=hash_str(nome_do_jogo,n);
  int winner;
  node_jogo novo_jogo;
  node_equipa h,aux;
  if (golos_casa>golos_fora){
     winner=1;
  }
  else if (golos_casa<golos_fora){
     winner=2;
  }
  else if(golos_casa==golos_fora){
    winner=0;
  }
  novo_jogo=(node_jogo)can_fail_malloc(sizeof(struct stru_node_jogo));
  novo_jogo->name=(char*)can_fail_malloc(strlen(nome_do_jogo)+1);
  novo_jogo->golos_casa=golos_casa;
  novo_jogo->golos_fora=golos_fora;
  strcpy(novo_jogo->name,nome_do_jogo);
  for(h=equipas[i];h!=NULL;h=h->next){
    if (strcmp(h->nome,team1)==0) {
        aux=(node_equipa)can_fail_malloc(sizeof(struct stru_node_equipa));
        novo_jogo->equipa1=aux;
        novo_jogo->equipa1=h;
        free(aux);
      break;
    }
  }
  for(h=equipas[j];h!=NULL;h=h->next){
    if (strcmp(h->nome,team2)==0){
      aux=(node_equipa)can_fail_malloc(sizeof(struct stru_node_equipa));
      novo_jogo->equipa2=aux;
      novo_jogo->equipa2=h;
      free(aux);
      break;
    }
  }
  for(h=equipas[i];h!=NULL;h=h->next){
    if((strcmp(h->nome,team1)==0)&&(winner==1)){
      h->vitorias++;
    }
  }
  for(h=equipas[j];h!=NULL;h=h->next){
    if((strcmp(h->nome,team2)==0)&&(winner==2)){
      h->vitorias++;
    }
  }
  novo_jogo->next=jogos[k];
  if (!l->head) {
    l->head=l->tail=novo_no(nome_do_jogo,m,team1,team2,golos_casa,golos_fora,equipas,l->head);
    return novo_jogo;
  }
  else {
  l->tail->next=novo_no(nome_do_jogo,m,team1,team2,golos_casa,golos_fora,equipas,l->tail);
  l->tail=l->tail->next;
  return novo_jogo;
}
return 0;
}

void adiciona_jogo(int inp,int m,int n,node_jogo *jogos,node_equipa *equipas, list l){
  int i,j,k,a,b;
  char nome[1024],e1[1024],e2[1024];
  scanf(" %[^:]:%[^:\n]:%[^:\n]:%d:%d",nome,e1,e2,&a,&b);
  i=hash_str(e1,m);
  j=hash_str(e2,m);
  k=hash_str(nome,n);
  if(search_game(jogos[k],nome)==1) {
    printf("%d Jogo existente.\n",inp);
  }
  else if ((search_team(equipas[i],e1)==0)){
    printf("%d Equipa inexistente.\n",inp);
  }
  else if (search_team(equipas[j],e2)==0){
    printf("%d Equipa inexistente.\n",inp);
  }
  else{
  jogos[k]=insere_jogo(nome,m,n,e1,e2,a,b,jogos,equipas,l);
}
}
void print_ordenada(int inp,list l){
  Q x;
  for(x=l->head;x!=NULL;x=x->next){
    printf("%d %s %s %s %d %d\n",inp,x->jogo->name,x->jogo->equipa1->nome,x->jogo->equipa2->nome,x->jogo->golos_casa,x->jogo->golos_fora);
}
}

int check_game(int inp,node_jogo *jogos,int n){
  int i;
  node_jogo x;
  char nome[1024];
  scanf("%s",nome);
  i=hash_str(nome,n);
  for(x=jogos[i];x!=NULL;x=x->next){
    if (strcmp(x->name,nome)==0){
      printf("%d %s %s %s %d %d\n",inp,x->name,x->equipa1->nome,x->equipa2->nome,x->golos_casa,x->golos_fora);
      return 0;
    }
  }
  printf("%d Jogo inexistente.\n",inp);
  return 0;
}
int delete_game(int inp,node_jogo *jogos,node_equipa *equipas,int m,int n,list l){
  node_jogo aux,temp,prev;
  Q x,aux_queue;
  node_equipa equipa_com_menos_vitoria;
  char *vencedor,nome[1024];
  int i,j,existe=0,tie=0;
  scanf("%s",nome);
  i=hash_str(nome,n);
  aux=jogos[i];
  if(aux!=NULL){
    for(temp=jogos[i],prev=NULL;(temp!=NULL);prev=temp,temp=temp->next){
      if (strcmp(temp->name,nome)==0){
        if (temp==jogos[i]){
          if (temp->golos_casa > temp->golos_fora){                                 /* a string vencedor serve para mais tarde dentro da funcao descobrir */
            vencedor=(char*)can_fail_malloc(sizeof(char)*(strlen(temp->equipa1->nome)+1));   /* em que equipa vai ser decrementada a vitoria caso o jogo que e para ser eliminado tinha vencedor*/
            existe=1;
            strcpy(vencedor,temp->equipa1->nome);
            jogos[i]=temp->next;
            free(temp->name);
            free(temp);
            break;
          }
          else if (temp->golos_fora>temp->golos_casa){
            existe=1;
            vencedor=(char*)can_fail_malloc(sizeof(char)*(strlen(temp->equipa2->nome)+1));
            strcpy(vencedor,temp->equipa2->nome);
            jogos[i]=temp->next;
            free(temp->name);
            free(temp);
            break;
          }
            else if(temp->golos_fora==temp->golos_casa){                            /* a  variavel tie serve para nos dizer q e um empate e a funcao pode simplesmente acabar e retornar 0*/
              tie=1;
            jogos[i]=temp->next;
            free(temp->name);
            free(temp);
            break;
          }
          }
        else
        {
          if (temp->golos_casa > temp->golos_fora){                                   /*  a variavel existe serve para saber se as equipas existem na base de dados*/
            existe=1;
            vencedor=(char*)can_fail_malloc(sizeof(char)*(strlen(temp->equipa1->nome)+1));
            strcpy(vencedor,temp->equipa1->nome);
            prev->next=temp->next;
            free(temp->name);
            free(temp);
            break;
          }
          else if (temp->golos_fora > temp->golos_casa){
            existe=1;
            vencedor=(char*)can_fail_malloc(sizeof(char)*(strlen(temp->equipa2->nome)+1));
            strcpy(vencedor,temp->equipa2->nome);
            prev->next=temp->next;
            free(temp->name);
            free(temp);
            break;
          }
          else if (temp->golos_fora==temp->golos_casa){
            tie=1;
            prev->next=temp->next;
            free(temp->name);
            free(temp);
            break;
          }
  }
}
}

for(x=l->head;x!=NULL;x=x->next){
  if (strcmp(x->jogo->name,nome)==0){
    if (x==l->head){
      l->head=x->next;
      free(x->jogo->name);
      free(x);
      break;
    }
    else if(x->next!=NULL)
    {
      aux_queue=x;
      x->next->prev = x->prev;
      x->prev->next=x->next;
      free(aux_queue->jogo->name);
      free(aux_queue);
      break;
    }
    else if (x->prev!=NULL){
      x->prev->next=x->next;
      free(x->jogo->name);
      free(x);
      break;
    }
  }
}
  if (existe==1) {
    j=hash_str(vencedor,m);
  for(equipa_com_menos_vitoria=equipas[j];equipa_com_menos_vitoria!=NULL;equipa_com_menos_vitoria=equipa_com_menos_vitoria->next){
    if(strcmp(equipa_com_menos_vitoria->nome,vencedor)==0){ /*  aqui esta o uso da string vencedor*/
    equipa_com_menos_vitoria->vitorias--;
    free(vencedor);
    return 0;
  }
}
}
  else if(tie==1){
    return 0;
  }
  else if (search_game(jogos[i],nome)==0){
 printf("%d Jogo inexistente.\n",inp);
  return 0;
}
}
 else{
  printf("%d Jogo inexistente.\n",inp);
}
return 0;
}

int change_game(int inp,node_jogo *jogos,int n,list l){
  char nome[1024];
  int a,b,i,winner;
  node_jogo x;
  Q t;
  scanf(" %[^:]:%d:%d",nome,&a,&b);
  i=hash_str(nome,n);
  if (a>b){
    winner=1;
  }
  else if (a<b)
  {
    winner=2;
  }
  else if(a==b)
  {
    winner=0;
  }
  if (search_game(jogos[i],nome)==1){
  for(x=jogos[i];(x!=NULL);x=x->next){
    if ((strcmp(x->name,nome)==0)&&(winner==1)&&(x->golos_casa<x->golos_fora)){
      x->equipa1->vitorias++;
      x->equipa2->vitorias--;
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
    else if((winner==2)&&(x->golos_casa>x->golos_fora)&&(strcmp(x->name,nome)==0)){
      x->equipa1->vitorias--;
      x->equipa2->vitorias++;
      x->golos_casa=a;
      x->golos_fora=b;
      break;
  }
    else if((winner==1)&&(x->golos_casa>x->golos_fora)&&(strcmp(x->name,nome)==0)){
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
    else if((winner==2)&&(x->golos_casa<x->golos_fora)&&(strcmp(x->name,nome)==0)){
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
    else if ((strcmp(x->name,nome)==0)&&(winner==0)&&(x->golos_casa<x->golos_fora)){
      x->equipa2->vitorias--;
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
    else if ((strcmp(x->name,nome)==0)&&(winner==0)&&(x->golos_casa>x->golos_fora)){
      x->equipa1->vitorias--;
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
    else if ((strcmp(x->name,nome)==0)&&(winner==1)&&(x->golos_casa==x->golos_fora)){
      x->equipa1->vitorias++;
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
    else if ((strcmp(x->name,nome)==0)&&(winner==2)&&(x->golos_casa==x->golos_fora)){
      x->equipa2->vitorias++;
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
    else if ((strcmp(x->name,nome)==0)&&(winner==0)&&(x->golos_casa==x->golos_fora)){
      x->golos_casa=a;
      x->golos_fora=b;
      break;
    }
}
  for(t=l->head;(t!=NULL);t=t->next){
    if (strcmp(t->jogo->name,nome)==0){
    t->jogo->golos_casa=a;
    t->jogo->golos_fora=b;
  }
}
}
  else {
    printf("%d Jogo inexistente.\n",inp);
  }
  return 0;
}
int check_team(int inp,node_equipa *equipas,int m){
  char nome[1024];
  int i;
  node_equipa x;
  scanf(" %[^:\n]",nome);
  i=hash_str(nome,m);
  for(x=equipas[i];x!=NULL;x=x->next){
    if (strcmp(x->nome,nome)==0){
      printf("%d %s %d\n",inp,x->nome,x->vitorias);
      return 0;
    }
  }
  printf("%d Equipa inexistente.\n",inp);
  return 0;
}
int cmpstr(const void* a, const void* b){
    const struct stru_node_equipa *elemento1=*(struct stru_node_equipa **)a,*elemento2=*(struct stru_node_equipa **)b;
    int rtn;
    rtn=strcmp (elemento1->nome, elemento2->nome);
    return rtn;
}
void sort_teams(int inp,node_equipa *equipas){
  int i,j,n=1161,maximo=0;
  int capacity=5,existe;
  int used=0;
  node_equipa x;
    for(j=0;j<n;j++){
      for(x=equipas[j];x!=NULL;x=x->next){    /*  dentro deste ciclo for  averiguamos qual o maior numero de vitorias de uma equipa */
        if (x->vitorias>=maximo)
        {
          maximo=x->vitorias;
          }
        existe=1;                              /* a variavel existe volta a ter o mesmo significado como foi anteriormente explicado*/
        }
      }
    if (existe==1){
    node_equipa *array=can_fail_malloc(sizeof(struct stru_node_equipa)*capacity); /*  e criado um vetor de estruturas  de equipas dinamico */
    for(j=0;j<n;j++){
      for(x=equipas[j];x!=NULL;x=x->next){
        if((used>=capacity)&&(x->vitorias==maximo))                      /* a variavel use diz nos se o vetor esta sobrelotado*/
        {
          capacity*=2;
          array=(node_equipa*)can_fail_realloc(array,sizeof(struct stru_node_equipa)*capacity);   /* esta aqui a realocacao dinamica do vetor de estruturas fazendo jus a sua caracteristica  */
          array[used]=(node_equipa)can_fail_malloc(sizeof(struct stru_node_equipa));
          array[used]->nome=(char*)can_fail_malloc(strlen(x->nome)+1);
          strcpy(array[used]->nome,x->nome);
          used++;
        }
        else if (x->vitorias==maximo){
        array[used]=(node_equipa)can_fail_malloc(sizeof(struct stru_node_equipa));
        array[used]->nome=(char*)can_fail_malloc(strlen(x->nome)+1);
        strcpy(array[used]->nome,x->nome);
        used++;
      }
    }
  }
    qsort(array,used,sizeof(struct equipa_a*),cmpstr);
    printf("%d Melhores %d\n",inp,maximo);
    for(i=0;i<used;i++){
      printf("%d * %s\n",inp,array[i]->nome);
      free(array[i]->nome);
      free(array[i]);
    }
    free(array);
  }
}

void free_game(node_jogo *jogos,int n){
  node_jogo x,temp;
  int i;
  for(i=0;i<n;i++){
    x=jogos[i];
      while(x!=NULL){
      temp=x->next;
      free(x->name);
      free(x);
      x=temp;
  }
}
}
void free_team(node_equipa *equipas,int n){
  node_equipa x,temp;
  int i;
  for(i=0;i<n;i++){
    x=equipas[i];
    while(x!=NULL){
      temp=x->next;
      free(x->nome);
      free(x);
      x=temp;
  }
  }
}
 void remove_queue(list l){
  while(l->head!=NULL)
  {
    Q temp=l->head;
    l->head=temp->next;
    free(temp->jogo->name);
    free(temp->jogo);
    free(temp);
  }
    free(l);
 }






int main(){
  int c,inp=1;
  node_equipa *equipas;
  node_jogo *jogos;
  list l;
  int m=1161,n=1161;
  equipas=(node_equipa*)can_fail_malloc(m*sizeof(struct stru_node_equipa));
  jogos=(node_jogo*)can_fail_malloc(n*sizeof(struct stru_node_jogo));
  l=init_list(); /* guarda se na variavel l do tipo lista a lista que e passada como argumento na maioria das funcoes*/
  init_teamhash(m,equipas);
  init_gamehash(n,jogos);
  while (((c=getchar())!=EOF)&&(c!='x')) {
    switch(c){
      case 'a':{
        adiciona_jogo(inp,m,n,jogos,equipas,l);
        inp++;                                                /* dentro  do switch e incrementado o valor do inp para efeitos de debug e aconselhado pelo corpo docente*/
        break;
      }
      case 'A':
      {
        insert(inp,equipas,m);
        inp++;
        break;
      }
      case 'l':
      {
        print_ordenada(inp,l);
        inp++;
        break;
      }
      case 'p':
      {
        check_game(inp,jogos,n);
        inp++;
        break;
      }
      case 'r':
      {
        delete_game(inp,jogos,equipas,m,n,l);
        inp++;
        break;
      }
      case 's':
      {
        change_game(inp,jogos,n,l);
        inp++;
        break;
      }
      case 'P':
      {
        check_team(inp,equipas,n);
        inp++;
        break;
      }
      case 'g':
      {
        sort_teams(inp,equipas);
        inp++;
        break;
      }
  }
}
    remove_queue(l);
    free_game(jogos,n);
    free(jogos);
    free_team(equipas,n);
    free(equipas);
    return 0;
}
