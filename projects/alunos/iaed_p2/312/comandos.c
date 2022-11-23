#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"

#define MAX_PAL 1024
#define M 1013
#define MAX_EQ 10000

/* adiciona_equipa_fim-->Esta funcao adiciona a equipa p ao fim da lista ligada das equipas.*/
acede_equipa_normal* adiciona_equipa_fim(equipas *p,acede_equipa_normal *a){
    if (a->head==NULL){
        no_equipa_normal *b=can_fail_malloc(sizeof(no_equipa_normal));
        b->p=p;
        b->next=NULL;
        a->head=b;
        a->last=b;
        return a;
    }
    else {
        no_equipa_normal *b=a->last;
        a->last = can_fail_malloc(sizeof(no_equipa_normal));
        a->last->p = p;
        a->last->next = NULL;
        b->next=a->last;
        return a;
    }
}

/*  cria_no_jogo_normal-->esta funcao recebe  um nome, duas equipas e dois resultados e cria um no de um jogo com essas variaveis.*/
jogo_normal* cria_no_jogo_normal(char *nome,equipas *equipa1,equipas *equipa2, int res1, int res2){
    jogo_normal *novo = can_fail_malloc(sizeof(jogo_normal));
    novo->nome=can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(novo->nome,nome);
    novo->equipa1=equipa1;
    novo->equipa2=equipa2;
    novo->resultado1=res1;
    novo->resultado2=res2;
    return novo;
}

/* adiciona_jogo_fim-->Esta funcao adiciona o jogo p ao fim da lista ligada dos jogos.*/
acede_jogo_normal* adiciona_jogo_fim(jogo_normal *p,acede_jogo_normal *a){
    if (a->head==NULL){
        no_jogo_normal *b=can_fail_malloc(sizeof(no_jogo_normal));
        b->p=p;
        b->next=NULL;
        a->head=b;
        a->last=b;
        return a;
    }
    else {
        no_jogo_normal *b=a->last;
        a->last = can_fail_malloc(sizeof(no_jogo_normal));
        a->last->p = p;
        a->last->next = NULL;
        b->next=a->last;
        return a;
    }
}

/*inicia_normais--> Esta funcao inicia a cabeca e o ultimo elemento das listas ligadas dos jogos e das equipas a NULL*/
void inicia_normais(acede_equipa_normal *a,acede_jogo_normal *b){
    a->head=NULL;
    a->last=NULL;
    b->head=NULL;
    b->last=NULL;
}

/* hash--> Funcao que calcula o indice em que um nome ficara guardado na hash table*/
int hash(char *v){
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h;
}

/* coloca_inicio_jogo--> Estas funcao adiciona o jogo p ao inicio da lista_ligada correspondente ao indice i da hash table(heads[i])*/
no_jogo* coloca_inicio_jogo(acede_jogos *lista,jogos *p){
    int i=hash(p->nome);
    no_jogo *c=lista->heads[i];
    lista->heads[i]=can_fail_malloc(sizeof(no_jogo));
    lista->heads[i]->p=p;
    lista->heads[i]->next = c;
    lista->heads[i]->previous = NULL;
    if (c!=NULL)
        c->previous=lista->heads[i];
    return lista->heads[i];
}

/* procura_jogo--> Esta funcao percorre a lista ligada que esta em lista->heads[i] ate encontrar o jogo com o nome igual ao nome recebido, se encontrar, 
                   devolve esse jogo, caso nao encontre devolve NULL*/
jogos* procura_jogo(acede_jogos *lista,char *nome){
    int i=hash(nome);
    no_jogo *a=lista->heads[i];
    if (lista->heads[i]==NULL)
        return NULL;
    while(a!=NULL){                         /*ciclo que percorre a lista ligada do indice i da hash table*/
        if (strcmp(a->p->nome,nome)==0){
            return a->p;
        }
        a=a->next;
    }
    return NULL;
}

/* remove_jogo--> Esta funcao remove um jogo da hash table, para isso vai calcular o seu i atraves da funcao hash e,apos aceder a lista->heads[i]
                  vai procurar esse jogo comparando o nome, quando o encontrar, da free a esse jogo.*/
no_jogo* remove_jogo(acede_jogos *lista,char *nome){
    int i=hash(nome);
    no_jogo *q=lista->heads[i],*c=lista->heads[i];
    for(;c;c=c->next){                               /*ciclo que percorre a lista ligada do indice i da hash table*/
        if(strcmp(c->p->nome,nome)==0){
            if(c->next==NULL && c->previous==NULL){         /*caso o primeiro elemento da lista ligada seja o unico dessa lista ligada*/
                free(c->p->nome);
                free(c->p);
                free(c);
                c=NULL;
                return c;
            }
            else if(c->previous==NULL){                     /*caso o elemento seja o primeiro da lista ligada mas nao o unico*/
                no_jogo *a=c->next;
                a->previous=NULL;
                free(c->p->nome);
                free(c->p);
                free(c);
                return a;
            }
            else{                                          /*caso o elemento esteja no meio de dois outros elementos ou seja o ultimo da lista ligada*/
                no_jogo *a=c->next,*b=c->previous;
                if (a!=NULL)
                    a->previous=b;
                b->next=a;
                free(c->p->nome);
                free(c->p);
                free(c);
                return q;
            }
        }
    }
    return 0;
}

/* inicializa_jogo--> Esta funcao inicializa a hash table do jogo, para isso, mete-se todos os seus lista_ligada_jogos->heads[i] a NULL*/
acede_jogos* inicializa_jogo(acede_jogos *lista_ligada_jogos){
    int i;
    for (i = 0; i < M; i++){
        lista_ligada_jogos->heads[i] = NULL;
    }
    return lista_ligada_jogos;
}

/* jogos_procura-->Funcao que chama a funcao que procura o jogo com o nome recebido*/
jogos* jogos_procura(char *nome,acede_jogos *lista_ligada_jogos){
    return procura_jogo(lista_ligada_jogos,nome);
}

/* jogos_insere-->Funcao que chama a funcao que insere o jogo no inicio da lista ligada do indice i da hash table, e atualiza a lista ligada
                  do indice i da sash table*/
void jogos_insere(jogos *p,acede_jogos *lista_ligada_jogos){
    int i=hash(p->nome);
    lista_ligada_jogos->heads[i]=coloca_inicio_jogo(lista_ligada_jogos, p);
}

/* jogos_apaga-->Funcao que chama a funcao que apaga um jogo, e atualiza a lista ligada do indice i da sash table*/
void jogos_apaga(char *nome,acede_jogos *lista_ligada_jogos){
    int i=hash(nome);
    lista_ligada_jogos->heads[i]=remove_jogo(lista_ligada_jogos, nome);
}

/* cria_no_jogo-->esta funcao recebe  um nome, duas equipas e dois resultados e cria um no de um jogo com essas variaveis.*/
jogos* cria_no_jogo(char *nome,equipas *equipa1,equipas *equipa2, int res1, int res2){
    jogos *novo = can_fail_malloc(sizeof(jogos));
    novo->nome=can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(novo->nome,nome);
    novo->equipa1=equipa1;
    novo->equipa2=equipa2;
    novo->resultado1=res1;
    novo->resultado2=res2;
    return novo;
}

/* coloca_inicio_equipa--> Esta funcao adiciona a equipa p ao inicio da lista_ligada correspondente ao indice i da hash table(heads[i])*/
no_equipa* coloca_inicio_equipa(lista_equipas *lista,equipas *p){
    int i=hash(p->nome);
    no_equipa *c = lista->heads[i];
    lista->heads[i]=can_fail_malloc(sizeof(no_equipa));
    lista->heads[i]->p=p;
    lista->heads[i]->next = c;
    return lista->heads[i];
}

/* procura_equipa--> Esta funcao percorre a lista ligada que esta em lista->heads[i] ate encontrar a equipa com o nome igual ao nome recebido, se encontrar, 
                     devolve essa equipa, caso nao encontre devolve NULL*/
equipas* procura_equipa(lista_equipas *lista,char *nome){
    int i=hash(nome);
    no_equipa *a=lista->heads[i];
    if (lista->heads[i]==NULL)
        return NULL;
    while(a!=NULL){                        /*ciclo que percorre a lista ligada do indice i da hash table*/
        if (strcmp(a->p->nome,nome)==0){
            return a->p;
        }
        a=a->next;
    }
    return NULL;
}

/* inicializa_equipa--> Esta funcao inicializa a hash table da equipa, para isso, mete-se todos os seus lista_ligada_jogos->heads[i] a NULL*/
lista_equipas* inicializa_equipa(lista_equipas *lista_ligada_equipas){
    int i;
    for (i = 0; i < M; i++) {               
        lista_ligada_equipas->heads[i] = NULL;
    }
    return lista_ligada_equipas;
}

/* equipa_procura-->Funcao que chama a funcao que procura a equipa com o nome recebido*/
equipas* equipa_procura(char *nome,lista_equipas *lista_ligada_equipas){
    equipas *b;
    b=procura_equipa(lista_ligada_equipas,nome);
    return b;
}

/* equipa_insere-->Funcao que chama a funcao que insere a equipa no inicio da lista ligada do indice i da hash table, e atualiza a lista ligada
                   do indice i da sash table*/
void equipa_insere(equipas *p,lista_equipas *lista_ligada_equipas){
    int i=hash(p->nome);
    lista_ligada_equipas->heads[i]=coloca_inicio_equipa(lista_ligada_equipas, p);
}

/* cria_no_equipa-->esta funcao recebe  um nome e cria um no de uma equipa com esse nome e o numero de vitorias a 0.*/
equipas* cria_no_equipa(char *nome){
    equipas *novo = can_fail_malloc(sizeof(equipas));
    novo->nome=can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    novo->vitorias = 0;
    strcpy(novo->nome,nome);
    return novo;
}

/* compara_s--> funcao auxiliar a merge que vai retornar 1 se as strings estiver desorgaganizadas alfabeticamente ,retorna 0 caso contrario*/
int compara_s(char a[],char b[]){
    if (strcmp(a,b)>0)
        return 1;
    else if (strcmp(a,b)<0)
        return 0;
    return 0;
}

/* funcao auxiliar a mergesort que vai ordenar os nomes alfabeticamente*/
void merge(equipas *a[1][MAX_EQ],int l,int m,int r){
    equipas *aux[1000];
    int i,j,k;
    for (i=m+1;i>l;i--)
        aux[i-1]=a[0][i-1];
    for (j=m;j<r;j++)
        aux[r+m-j]=a[0][j+1];
    for (k=l;k<=r;k++){
        if (compara_s(aux[i]->nome,aux[j]->nome))             /* condicao que vai comparar os nomes de aux[i] e aux[j],executa a
                                                                               condicao caso a descricao estas nao estejam por ordem alfabetica */
            a[0][k]=aux[j--];
        else
            a[0][k]=aux[i++];
    }
}

/* Algoritmo do merge sort para ordenar alfabeticamente a lista de nomes*/
void mergesort(equipas *a[1][MAX_EQ],int l,int r){
    int m=(r+l)/2;
    if (r<=l)
        return;
    mergesort(a,l,m);
    mergesort(a,m+1,r);
    merge(a,l,m,r);
}


/* func_a--> Esta funcao recebe os dados de um jogo e caso as equipas recebidas existam e nao haja nenhum jogo com este nome, vai ser criado um jogo com
              os dados recebidos,conforme o resultado desse jogo, pode-se ou nao somar mais uma vitoria a uma das equipas.*/
void func_a(int NL, lista_equipas *lista_ligada_equipas, acede_jogos *lista_ligada_jogos,acede_jogo_normal *jogos_normais){
    char nome[MAX_PAL];
    char equipa1[MAX_PAL];
    char equipa2[MAX_PAL];
    int res1;
    int res2;
    jogos *v;
    jogo_normal *q;
    equipas *b,*c;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&res1,&res2);
    if (jogos_procura(nome,lista_ligada_jogos)!=NULL)
        printf("%d Jogo existente.\n",NL);
    else if (equipa_procura(equipa1,lista_ligada_equipas)==NULL)
        printf("%d Equipa inexistente.\n",NL);
    else if (equipa_procura(equipa2,lista_ligada_equipas)==NULL)
        printf("%d Equipa inexistente.\n",NL);
    else{
        b=equipa_procura(equipa1,lista_ligada_equipas);
        c=equipa_procura(equipa2,lista_ligada_equipas);
        v=cria_no_jogo(nome,b,c,res1,res2);
        q=cria_no_jogo_normal(nome,b,c,res1,res2);
        jogos_insere(v,lista_ligada_jogos);  /*adiciona o jogo a hash table dos jogos(lista_ligada_normais)*/
        adiciona_jogo_fim(q,jogos_normais);  /*adiciona o jogo a lista ligada dos jogos(jogos_normais)*/
        if (res1>res2){
            b->vitorias+=1;
        }
        else if (res1<res2){
            c->vitorias+=1;
        }
    }
}

/* func_A--> Esta funcao recebe o nome de um jogo, e caso ainda nao exista nenhuma equipa com esse nome, cria uma nova equipa e adiciona essa equipa a hash
             table e a lista ligada das equipas.*/
void func_A(int NL, lista_equipas *lista_ligada_equipas,acede_equipa_normal *equipas_normais) {
    char a[MAX_PAL];
    equipas *v;
    scanf("  %[^\n]", a);
    if (equipa_procura(a, lista_ligada_equipas) != NULL) {
        printf("%d Equipa existente.\n", NL);
    }
    else {
        v = cria_no_equipa(a);
        equipa_insere(v, lista_ligada_equipas);  /*adiciona a equipa a hash table das equipas(lista_ligada_equipas)*/
        adiciona_equipa_fim(v, equipas_normais); /*adiciona a equipa a lista ligada das equipas(equipas_normais)*/
    }
}

/* func_l--> Esta funcao vai percorrer a lista ligada das equipas e listar os jogos por ordem de incersao, indicando o seu nome, o nome das
             equipas que jogaram e o resultado do jogo, verificando primeiro se estes jogos nao foram removidos.*/
void func_l(int NL,acede_jogo_normal *jogos_normais,acede_jogos *lista_ligada_jogos){
    jogos *b;
    char *lista[MAX_EQ];           /*lista onde se vao guardar os nomes que ja foram listados*/
    int contador=0,i;
    int estado=0;
    if (jogos_normais==NULL){
    }
    else{
        no_jogo_normal *a=jogos_normais->head;
        while(a!=NULL) {                          /*ciclo que percorre a lista ligada dos jogos(jogos_normais)*/
            for (i = contador - 1; i >= 0; i--) {    /* ciclo que vai percorrer a lista[10000] e vai comparar o nome da equipa que estamos a considerar 
                                                        atualmente com os da lista, caso esse nome esteja na lista mete o estado a 1 e o jogo desse nome
                                                        nao sera listado,caso contrario o estado permanece a 0*/
                if (strcmp(lista[i],a->p->nome)==0)
                    estado=1;
            }
            if(estado!=1) {
                if ((b = jogos_procura(a->p->nome, lista_ligada_jogos)) !=NULL) { /*verificar se o jogo em questao ainda pertence a hash table, ou seja, nao foi removido*/
                    printf("%d %s %s %s %d %d\n", NL, a->p->nome, a->p->equipa1->nome, a->p->equipa2->nome,
                           b->resultado1,
                           b->resultado2);
                    lista[contador] = a->p->nome; /* guardar o nome do jogo apos ele ser listado*/
                    contador += 1;
                }
            }
            a = a->next;
            estado=0;                  /*apos se passar para o proximo no temos que dar reset ao estado, ou seja, mete-lo a 0*/
        }
    }
}

/* func_p--> Esta funcao recebe um nome de um jogo, e apos verificar se esse jogo existe, lista esse jogo tal como na func_l. */
void func_p(int NL,acede_jogos *lista_ligada_jogos){
    char a[MAX_PAL];
    jogos *b;
    scanf(" %[^\n]", a);
    b=jogos_procura(a,lista_ligada_jogos);
    if(b==NULL){
        printf("%d Jogo inexistente.\n",NL);
    }
    else{
        printf("%d %s %s %s %d %d\n",NL,b->nome,b->equipa1->nome,b->equipa2->nome,b->resultado1,b->resultado2);
    }
}

/* func_r--> Esta funcao recebe um nome de um jogo e, apos verificar se esse jogo existe, remove esse jogo da hash table, subtraindo uma vitoria a equipa
             que tinha ganho o jogo em questao*/
void func_r(int NL,acede_jogos *lista_ligada_jogos){
    char a[MAX_PAL];
    jogos *b;
    scanf(" %[^\n]", a);
    b=jogos_procura(a,lista_ligada_jogos);
    if(b==NULL){
        printf("%d Jogo inexistente.\n",NL);
    }
    else{
        if(b->resultado1>b->resultado2){
            b->equipa1->vitorias-=1;
        }
        if(b->resultado1<b->resultado2){
            b->equipa2->vitorias-=1;
        }
        jogos_apaga(b->nome,lista_ligada_jogos);
    }
}

/* func_P--> Esta funcao recebe um nome de uma equipa e, apos verficar se exite alguma equipa com esse nome, lista essa equipa indicando o seu nome e o seu
             numero de vitorias.*/
void func_P(int NL,lista_equipas *lista_ligada_equipas){
    char a[MAX_PAL];
    equipas *b;
    scanf(" %[^\n]", a);
    b=equipa_procura(a,lista_ligada_equipas);
    if(b==NULL){
        printf("%d Equipa inexistente.\n",NL);
    }
    else{
        printf("%d %s %d\n",NL,b->nome,b->vitorias);
    }
}

/* func_s--> Esta funcao recebe um nome de um jogo e um resultado,e vrificando primeiro se exite algum jogo com esse nome, altera o resultado desse jogo na hash
             table para o resultado recebido, altera tambem o numero de vitorias das equipas conforme o novo resultado.*/
void func_s(int NL, acede_jogos *lista_ligada_jogos){
    char a[MAX_PAL];
    int b,c;
    jogos *jogo;
    scanf(" %[^:\n]:%d:%d",a,&b,&c);
    jogo=jogos_procura(a,lista_ligada_jogos);
    if (jogo==NULL){
        printf("%d Jogo inexistente.\n",NL);
    }
    else{
        if(b>c && jogo->resultado1<jogo->resultado2){
            jogo->equipa1->vitorias+=1;
            jogo->equipa2->vitorias-=1;
        }
        else if(b<c && jogo->resultado1>jogo->resultado2){
            jogo->equipa1->vitorias-=1;
            jogo->equipa2->vitorias+=1;
        }
        else if(b==c && jogo->resultado1>jogo->resultado2){
            jogo->equipa1->vitorias-=1;
        }
        else if(b==c && jogo->resultado1<jogo->resultado2){
            jogo->equipa2->vitorias-=1;
        }
        else if(b>c && jogo->resultado1==jogo->resultado2){
            jogo->equipa1->vitorias+=1;
        }
        else if(b<c && jogo->resultado1==jogo->resultado2){
            jogo->equipa2->vitorias+=1;
        }
        jogo->resultado1=b;
        jogo->resultado2=c;
    }
}
/* func_g--> Esta funcao vai listar as equipas com mais vitorias por ordem alfabetica*/
void func_g(int NL, acede_equipa_normal *equipas_normais){
    int i=0,c;
    int contador=0;
    equipas *lista_equipas_vitorias[1][MAX_EQ];
    no_equipa_normal *a=equipas_normais->head,*b=equipas_normais->head;
    if (equipas_normais->head==NULL){
    }
    else {
        while (a!=NULL) {    /*Ciclo que ve qual e o maior numero de vitorias de entre todas as equipas, percorrendo a lista ligada das equipas(equipas_normais).*/
            if (a->p->vitorias > i)
                i = a->p->vitorias;
            a = a->next;
        }
        while (b!=NULL) {       /*ciclo que passa as equipas com numero de vitorias igual ao definido do ciclo anterior para a tabela lista_equipas_vitorias
                                  percorrendo a lista ligada das equipas(equipas_normais).*/
            if (b->p->vitorias == i) {
                lista_equipas_vitorias[0][contador]=b->p;
                contador += 1;
            }
            b = b->next;
        }
        if (contador==1){
        }
        else
            mergesort(lista_equipas_vitorias,0, contador-1);           /*funcao de ordenacao*/
        printf("%d Melhores %d\n", NL, i);
        for (c=0; c < contador; c++) {                      /* ciclo que vai ate ao numero de equipas adicionadas a lista_equipas_vitorias para as poder listar*/
            printf("%d * %s\n", NL, lista_equipas_vitorias[0][c]->nome);
        }
    }
}

/* que_func--> funcao que apos ler a primeira letra do comando, verifica qual a funcao que tem que chamar em funcao do dessa primeira letra */
void que_func(int NL,char *letra,lista_equipas *lista_ligada_equipas,acede_jogos *lista_ligada_jogos,acede_jogo_normal *jogos_normais,
              acede_equipa_normal *equipas_normais){
    switch(*letra){
        case 'a':
            func_a(NL,lista_ligada_equipas,lista_ligada_jogos,jogos_normais);
            break;
        case 'A':
            func_A(NL,lista_ligada_equipas,equipas_normais);
            break;
        case 'l':
            func_l(NL,jogos_normais,lista_ligada_jogos);
            break;
        case 'p':
            func_p(NL,lista_ligada_jogos);
            break;
        case 'r':
            func_r(NL, lista_ligada_jogos);
            break;
        case 'P':
            func_P(NL, lista_ligada_equipas);
            break;
        case 's':
            func_s(NL,lista_ligada_jogos);
            break;
        case 'g':
            func_g(NL,equipas_normais);
            break;
    }
}

/* free_da_hash_jogo--> funcao que da free a hash table dos jogos*/
void free_da_hash_jogo(acede_jogos *lista_ligada_jogos){
    int i;
    no_jogo *aux1,*aux2;
    for(i=0;i<M;i++){    /*ciclo que percorre todos os indices possiveis da hash table ate M*/
        aux1=lista_ligada_jogos->heads[i];
        if (aux1==NULL)
            free(aux1);
        else{
            while(aux1){   /* ciclo while que percorre a lista_ligada de cada indice i da hash table*/
                if(aux1->next!=NULL)
                    aux2=aux1->next;
                else
                    aux2=NULL;
                free(aux1->p->nome);
                free(aux1->p);
                free(aux1);
                aux1=aux2;
            }
        }
    }
    free(lista_ligada_jogos);
}

/* free_da_hash_equipa--> funcao que da free a hash table das equipas*/
void free_da_hash_equipa(lista_equipas *lista_ligada_equipas){
    int i;
    no_equipa *aux1,*aux2;
    for(i=0;i<M;i++){ /*ciclo que percorre todos os indices possiveis da hash table ate M*/
        aux1=lista_ligada_equipas->heads[i];
        while(aux1){  /* ciclo while que percorre a lista_ligada de cada indice i da hash table*/
            if(aux1->next!=NULL)
                aux2=aux1->next;
            else
                aux2=NULL;
            free(aux1->p->nome);
            free(aux1->p);
            free(aux1);
            aux1=aux2;
        }
    }
    free(lista_ligada_equipas);
}

/* free_jogos_normais--> funcao que da free a lista ligada dos jogos*/
void free_jogos_normais(acede_jogo_normal *jogos_normais){
    no_jogo_normal *aux=jogos_normais->head,*aux2;
    while(aux){  /* ciclo while que percorre a lista_ligada(jogos_normais)*/
        if(aux->next!=NULL)
            aux2=aux->next;
        else
            aux2=NULL;
        free(aux->p->nome);
        free(aux->p);
        free(aux);
        aux=aux2;
    }
    free(jogos_normais);
}

/* free_equipas_normais--> funcao que da free a lista ligada das equipas*/
void free_equipas_normais(acede_equipa_normal *equipas_normais){
    no_equipa_normal *aux=equipas_normais->head,*aux2;
    while(aux){  /* ciclo while que percorre a lista_ligada(equipas_normais)*/
        if(aux->next!=NULL)
            aux2=aux->next;
        else
            aux2=NULL;
        free(aux);
        aux=aux2;
    }
    free(equipas_normais);
}