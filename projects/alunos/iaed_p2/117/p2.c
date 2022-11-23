#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INICIO 0
#define MAXIMO_CARACTERES 1024

typedef struct equipa{
    char *nome;
    int vitoria;
}Equipa;

typedef Equipa* link_equipa;

typedef struct jogo_node{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
    struct jogo_node *next;
}Jogo;

typedef Jogo* link_jogo;

static int N_equipa;

static int M_equipa ;

static link_equipa  *st_equipa;

int hashU(char *v, int M);

void Stinit_equipa(int m){
    int i; M_equipa = m , N_equipa = 0;
    st_equipa = (link_equipa*) can_fail_malloc (M_equipa*sizeof(link_equipa));
    for (i = 0; i < M_equipa; i++)
        st_equipa[i] = NULL;
}

void expand_equipa();

void STinsert_equipa(link_equipa p){
    int i = hashU(p->nome, M_equipa);
    while (st_equipa[i] != NULL) i = (i+1) % M_equipa;
    st_equipa[i] = p;
    if (N_equipa++>M_equipa/2)
    {
        expand_equipa();
    }
    
    
}

link_equipa STsearch_equipa(char* id){
    int i = hashU(id, M_equipa);
    while (st_equipa[i] != NULL)
        if (strcmp(st_equipa[i]->nome,id)==0)
            return st_equipa[i];
        else
            i = (i+1) % M_equipa;
    return NULL;
}

void expand_equipa() {
    int i;
    link_equipa *t = st_equipa;
    Stinit_equipa(M_equipa+M_equipa);
    for (i = 0; i < M_equipa/2; i++)
        if (t[i] != NULL)
            STinsert_equipa(t[i]);
    free(t);
}

link_equipa New_EQUIPA(char* buffer){
    link_equipa x = (link_equipa) can_fail_malloc(sizeof(Equipa));
    x->nome = (char*) can_fail_malloc (sizeof(char)*(strlen(buffer)+1));
    strcpy (x->nome, buffer);
    x->vitoria = 0;
    return x;
}

static int N_jogo ; /*numero  de elemento*/

static int M_jogo ; /*tamanho da minha tabela*/

static link_jogo *st;

int hashU(char *v, int M){
    int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a*b%(M-1))
        h = (a*h + *v) % M;
    return h;
}

void expand_jogo();

void Stinit_jogo(int m){
    int i; M_jogo = m, N_jogo = 0;
    st = (link_jogo*) can_fail_malloc (M_jogo*sizeof(link_jogo));
    for (i = 0; i < M_jogo; i++)
        st[i] = NULL;
    if (N_jogo++ > M_jogo/2)
        expand_jogo();
}

void STinsert_jogo(link_jogo p){
    int i = hashU(p->nome, M_jogo);
    while (st[i] != NULL) i = (i+1) % M_jogo;
    st[i] = p;
    if (N_jogo++>M_jogo/2)
    {
        expand_jogo();
    }
    
    
}

link_jogo STsearch_jogo(char* id){
    int i = hashU(id, M_jogo);
    while (st[i] != NULL)
        if (strcmp(st[i]->nome,id)==0)
            return st[i];
        else
            i = (i+1) % M_jogo;
    return NULL;
}

void STdelete_jogo(char* id){
    int j, i = hashU (id, M_jogo); link_jogo v;
    while (st[i] != NULL)
        if (strcmp(st[i]->nome,id)==0) break;
        else i = (i+1) % M_jogo;
    if (st[i] == NULL) return;
    st[i] = NULL;
    for (j = (i+1) % M_jogo; st[j] != NULL; j = (j+1)%M_jogo){
        v = st[j];
        st[j] = NULL;
        STinsert_jogo (v);
    }
    N_jogo--;
    
}

void expand_jogo() {
    int i;
    link_jogo *t = st;
    Stinit_jogo(M_jogo+M_jogo);
    for (i = 0; i < (M_jogo/2)-1; i++)
        if (t[i] != NULL)
            STinsert_jogo(t[i]);
    free(t);
}

link_jogo NEW_JOGO(char* designacao, char* team1, char* team2, int pontos1, int pontos2){
    link_jogo x = (link_jogo) can_fail_malloc(sizeof(Jogo));
    x->nome = (char*) can_fail_malloc (sizeof(char)*(strlen(designacao)+1));
    strcpy (x->nome, designacao);
    x->equipa1 = (char*) can_fail_malloc(sizeof(char)*(strlen(team1)+1));
    strcpy (x->equipa1, team1);
    x->equipa2 = (char*) can_fail_malloc(sizeof(char)*(strlen(team2)+1));
    strcpy (x->equipa2, team2);
    x->score1 = pontos1;
    x->score2 = pontos2;
    x->next = NULL;
    return x;

}

link_jogo insertEend_jogo(link_jogo head,link_jogo* fim, char* designacao, char* team1, char* team2, int pontos1, int pontos2){
    link_jogo t = NEW_JOGO(designacao,team1,team2,pontos1,pontos2);
    STinsert_jogo(t);
    if (head == NULL){
        *fim = t;
        return t;
    }
    (*fim)->next = t;
    *fim = t;
    return head;
}

void FREE_jogo(link_jogo t){
    free(t->nome);
    free(t->equipa1);
    free(t->equipa2);
    free(t);
}

link_jogo delete_jogo(link_jogo head, link_jogo *fim, char* text){
    link_jogo t, prev;
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next){
        if (strcmp(t->nome, text) == 0){
            if (t == head){
                if(t==(*fim))
                    *fim = NULL;
                head = t->next;
            }
            else{
                if (t==(*fim))
                    *fim = prev;
                prev->next = t->next;
            }
            FREE_jogo(t);
            break;
        }
               
    }
    return head;
}



void adiciona_um_novo_jogo(link_jogo *head_jogos, link_jogo *fim, int* nl);

void lista_os_jogos(link_jogo head, int* nl);

void procura_um_jogo( int* nl);

void apaga_um_jogo(link_jogo *head, link_jogo *fim, int* nl);

void altera_score(int* nl);

void adiciona_uma_equipa( int* nl);

void procura_uma_equipa( int* nl);

void mais_ganhos( int* nl);

int main(){
    int NL = 0;
    int *nl = &NL;
    char comando;
    link_jogo jogos = NULL;
    link_jogo *pt_jogos = &jogos;
    link_jogo fim = NULL;
    link_jogo *pt_fim = &fim;
    Stinit_jogo(293);
    Stinit_equipa(293);
    comando = getchar();
    while (comando != 'x')
    {
        switch (comando)
        {
        case 'a':
            comando = getchar();
            adiciona_um_novo_jogo(pt_jogos,pt_fim,nl);
            break;
        case 'l':
            comando = getchar();
            lista_os_jogos(jogos, nl);
            break;
        case 'p':
            comando = getchar();
            procura_um_jogo(nl);
            break;
        case 'r':
            comando = getchar();
            apaga_um_jogo(pt_jogos,pt_fim,nl);
            break;
        case 's':
            comando = getchar();
            altera_score(nl);
            break;
        case 'A':
            comando = getchar();
            adiciona_uma_equipa( nl);
            break;
        case 'P':
            comando = getchar();
            procura_uma_equipa(nl);
            break;
        case 'g':
            comando = getchar();
            mais_ganhos(nl);
            break;
        default:
            break;
        }
        comando = getchar();
    }
    return 0;

}

void adiciona_um_novo_jogo( link_jogo *head_jogos,link_jogo *fim, int *nl){
    char nome[MAXIMO_CARACTERES], equipa1[MAXIMO_CARACTERES], equipa2[MAXIMO_CARACTERES];
    int score1, score2;
    scanf ("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
    (*nl)++;
    if(STsearch_jogo(nome) != NULL){
        printf("%d Jogo existente.\n", *nl);
    }
    else if (STsearch_equipa(equipa1)==NULL||STsearch_equipa(equipa2)==NULL){
        printf("%d Equipa inexistente.\n", *nl);
    }
    else{
        if(score1>score2){
            link_equipa t = STsearch_equipa (equipa1);
            t->vitoria ++;
        }
        else if (score2>score1){
            link_equipa t = STsearch_equipa(equipa2);
            t->vitoria ++;
        }
        
        *head_jogos = insertEend_jogo(*head_jogos, fim, nome, equipa1, equipa2, score1, score2);
    }
    
}

void lista_os_jogos(link_jogo head, int *nl){
    link_jogo t;
    (*nl)++;
    if (head != NULL){
        for (t = head; t != NULL; t = t->next){
            printf("%d %s %s %s %d %d\n",(*nl), t->nome, t->equipa1, t->equipa2, t->score1 , t->score2);
        }
        
    }
}

void procura_um_jogo(int *nl){
    char nome[MAXIMO_CARACTERES];
    link_jogo t;
    (*nl)++;
    scanf("%[^:\n]",nome);
    t = STsearch_jogo(nome);
    if (t == NULL){
        printf("%d Jogo inexistente.\n",(*nl));
    }
    else{
        printf("%d %s %s %s %d %d\n",(*nl), t->nome, t->equipa1, t->equipa2, t->score1 , t->score2);
    }
    
    
}

void apaga_um_jogo(link_jogo *head, link_jogo *fim, int *nl){
    char nome[MAXIMO_CARACTERES];
    link_jogo t;
    (*nl)++;
    scanf ("%[^:\n]",nome);
    t = STsearch_jogo(nome);
    if (t == NULL)
        printf("%d Jogo inexistente.\n",(*nl));
    else{
        if (t->score1 > t->score2)
        {
            STsearch_equipa(t->equipa1)->vitoria--;
        }
        else if (t->score2 > t->score1)
        {
            STsearch_equipa(t->equipa2)->vitoria--;
        }
        STdelete_jogo(nome);
        *head=delete_jogo(*head,fim, nome);
    }
}

void altera_score(int *nl){
    char nome[MAXIMO_CARACTERES];
    int ponto1,ponto2;
    link_jogo t;
    scanf ("%[^:\n]:%d:%d",nome,&ponto1,&ponto2);
    t = STsearch_jogo(nome);
    (*nl)++;
    if (t == NULL)
        printf("%d Jogo inexistente.\n",(*nl));
    else{
        if(t->score1>t->score2){
            link_equipa x = STsearch_equipa (t->equipa1);
            x->vitoria --;
        }
        else if (t->score2>t->score1){
            link_equipa x = STsearch_equipa(t->equipa2);
            x->vitoria --;
        }
        if(ponto1>ponto2){
            link_equipa x = STsearch_equipa (t->equipa1);
            x->vitoria ++;
        }
        else if (ponto2>ponto1){
            link_equipa x = STsearch_equipa(t->equipa2);
            x->vitoria ++;
        }
        t->score1 = ponto1;
        t->score2 = ponto2;
    }    
}

void adiciona_uma_equipa(int *nl){
    char nome[MAXIMO_CARACTERES];
    scanf("%[^:\n]",nome);
    (*nl)++;
    if (STsearch_equipa(nome) != NULL)
        printf("%d Equipa existente.\n",(*nl));
    else{
        link_equipa t = New_EQUIPA(nome);
        STinsert_equipa(t);
    }
}

void procura_uma_equipa( int *nl){
    char nome[MAXIMO_CARACTERES];
    link_equipa t;
    (*nl)++;
    scanf("%[^:\n]",nome);
    t = STsearch_equipa(nome);
    if (t ==NULL)
        printf("%d Equipa inexistente.\n",(*nl));
    else
        printf("%d %s %d\n",(*nl),t->nome,t->vitoria);
    
}

int compareStr(const void *pa, const void *pb){
    char **a, **b;
    a = (char**)pa;
    b = (char**)pb;
    return strcmp(*a,*b);
}

void mais_ganhos( int *nl){
    int i, ng=-1, n_equipa=0;
    int aux = 0;
    char** array;
    (*nl)++;
    for(i=0 ; i<M_equipa; i++){
        if (st_equipa[i]!= NULL)
        {
            if (st_equipa[i]->vitoria > ng)
            {
                ng = st_equipa[i]->vitoria;
            }   
        }  
    }
    if (ng == -1) return;
    for(i=0 ; i<M_equipa; i++){
        if (st_equipa[i]!= NULL)
        {
            if (st_equipa[i]->vitoria == ng)
            {
                n_equipa++;
            }   
        }  
    }
    array = (char**) can_fail_malloc(sizeof(char*)*n_equipa);
    for (i=0; i<M_equipa; i++){
        if (st_equipa[i]!= NULL)
        {
            if (st_equipa[i]->vitoria == ng)
            {
                array[aux]= (char*)can_fail_malloc(sizeof(char)*(strlen(st_equipa[i]->nome)+1));
                strcpy(array[aux],st_equipa[i]->nome);
                aux++;
            }   
        }
    }
    qsort(array,n_equipa, sizeof(char*), compareStr );
    printf ("%d Melhores %d\n",(*nl),ng);
    for ( i = 0; i < n_equipa; i++)
    {
        printf ("%d * %s\n",(*nl),array[i]);
    }
    for(i=0; i<n_equipa; i++){
        free(array[i]);
    }
    free(array);
}
