#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOME 1023

typedef struct equipas {
    char equipa_nome[MAXNOME];
    int nr_vitorias;
}Equipas;

typedef struct {
    char nome[MAXNOME];
    Equipas *equipa_A;
    Equipas *equipa_B;
    int score1;
    int score2;    
}Jogo;

typedef struct no{
    Jogo jogo;
    struct no *proximo;
}*link;

typedef struct no_equipas{
    Equipas equipas;
    struct no_equipas *proximo;
}*link_equipas;


link_equipas cria_equipa(char *nome, int nv){
    link_equipas nova_no_equipa;
    nova_no_equipa = (link_equipas)can_fail_malloc(sizeof(struct no_equipas));
    strcpy(nova_no_equipa->equipas.equipa_nome , nome);
    nova_no_equipa->equipas.nr_vitorias = nv;
    nova_no_equipa->proximo = NULL;
    return nova_no_equipa;
}

/*funcao que insere no inicio da lista*/
link_equipas insertAtBegining(link_equipas head_list,link_equipas new_node){
    if (head_list == NULL)
        return new_node;
    else{
        new_node->proximo = head_list;
        head_list = new_node;
        return new_node;
    }
}

void delete_list (link_equipas *head_list){
    link_equipas k, anterior;
    for(k = *(head_list), anterior = NULL; k != NULL;){
            anterior = k;
            k = k->proximo;
            free(anterior);
        }

}

int hash(char *nome, int M){
    int h, a = 31415, b = 27183;
    for(h = 0; *nome != '\0'; nome++, a = a*b % (M - 1)){
        h = (a*h + *nome) % M;
    }
        
    return h;
}

link *Init_hash(link * heads, int M){
    int i;
    heads = (link*)can_fail_malloc(M*sizeof(link));
    for (i = 0; i<M; i++){
        heads[i] = NULL;            /*iniciliaza as heads todas a NULL*/
    } 
    return heads;
}

Equipas *NewEquipes(char* equipa_nome){
    Equipas *e = (Equipas *)can_fail_malloc(sizeof(Equipas));
    strcpy(e->equipa_nome,equipa_nome);
    e->nr_vitorias = 0;
    return e;
}

link NewNode(char* nome, char* equipa1, char* equipa2, int score1, int score2){
   
    link novo= (link) can_fail_malloc(sizeof(struct no));

    novo->jogo.equipa_A = NewEquipes(equipa1);
    novo->jogo.equipa_B = NewEquipes(equipa2);
    novo->jogo.score1 = score1;
    novo->jogo.score2 = score2;
    
    strcpy(novo->jogo.nome, nome);
    novo->proximo = NULL;
    return novo;


}

link *insere_hash(link *heads,int M, char *nome, char *equipa1, char *equipa2, int score1, int score2){ 
    link j;
    int chave = hash(nome, M);
    if(heads[chave] == NULL){
        heads[chave]= NewNode(nome,equipa1, equipa2,score1, score2);
    }
    else{
        j = NewNode(nome,equipa1, equipa2,score1, score2);
        j->proximo = heads[chave];
        heads[chave] = j;
    }
    return heads;
}
/*funcao que verifica se o jogo existe*/
link verifica_jogo(link *heads, int M, char *nome){
    int chave = hash(nome, M);
    link y;

    for (y = heads[chave]; y != NULL; y = y-> proximo){
        if(strcmp(y->jogo.nome, nome) == 0){
            return y;     /*se existir retorna a link de onde esta o jogo*/
        }
    }
    return 0;  
}

void apaga_no(link no){
    free(no->jogo.equipa_A);   
    free(no->jogo.equipa_B);
    free(no);
}

link *destroy_hash(link *heads, int M){
    int i = 0;
    link aux = NULL, anterior = NULL;
    for(i = 0; i<M; i++){
        for(aux = heads[i], anterior = NULL; aux != NULL;){
            anterior = aux;
            aux = aux->proximo;
            apaga_no(anterior);
        }
    }
    return heads;
}

void printjogo(link no){
    int NL = 0;
    printf("%d %s %s %s %d %d\n", NL, no->jogo.nome,no->jogo.equipa_A->equipa_nome,no->jogo.equipa_B->equipa_nome, no->jogo.score1, no->jogo.score2);
}

int prinflista(link head){
  link aux;
  for(aux = head; aux != NULL; aux = aux->proximo){
    printjogo(aux);
  }
  return 0;
}


int verifica_equipa(link_equipas listaDeEquipas, char * nome){
    link_equipas k;
    for(k = listaDeEquipas; k != NULL; k = k->proximo){
        if(strcmp(k->equipas.equipa_nome, nome)==0){

            return 1;
        }
    }
    return 0;
}

link *adiciona_jogo(int NL, link *heads,int M, char *nome, char *equipa1, char *equipa2, int score1, int score2, link_equipas listaDeEquipas, int *pflag){
    
    if(verifica_jogo(heads,M,nome) == 0){   /* primeiro ve se o jogo existe */
        if((verifica_equipa(listaDeEquipas,equipa1)== 0) && (verifica_equipa(listaDeEquipas,equipa2)== 0)){   /* depois ve as equipas */
            /* se ambos forem == 0 quer dizer que nao existe, sendo assim podemos adicionar a hash */
            heads = insere_hash(heads,M,nome,equipa1,equipa2,score1,score2);
            
            *(pflag)= 1;   /* esta flag serve para verificar se adicionamos o jogo a hastable heads (e usada como ponteiro para a funcao a alterar mesmo)*/
            return heads;
        }
        else 
            printf("%d Equipa existente.\n", NL);
    }
    else
        printf("%d Jogo existente.\n", NL);     
    
    *(pflag)= 0; /* volta a por a 0 porque nao adicionamos o jogo */
    return heads;
}

link_equipas adiciona_equipa(link_equipas listaDeEquipas,char *nome, int NL){
    
    if(verifica_equipa(listaDeEquipas, nome)==1){
        printf("%d Equipa existente.\n", NL);
        return listaDeEquipas;
    }
    return insertAtBegining(listaDeEquipas,cria_equipa(nome,0));
}

void printEverything(link *heads, int M){
    int i;
    for(i=0; i<M; i++){    /* percorre os indices da hastable ( esta a andar de head em head )*/
        prinflista(heads[i]);
    }
}

void comando_p(link *heads,int M,char *nome,int NL){
    link k = verifica_jogo(heads,M,nome);
    if(verifica_jogo(heads,M,nome) == 0){   /* se o jogo apenas faz aquele print e sai */
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    printjogo(k);
}

link *comando_r(link *heads, int M, char * nome, int NL){
    int chave = hash(nome, M);                      /* este remove apenas tira o jogo da hastable */
    link h, anterior;

    for(h = heads[chave], anterior = NULL; h != NULL; ){
        if(strcmp(h->jogo.nome, nome) == 0){
            if(h == heads[chave])
                heads[chave] = h->proximo;
            else
                anterior->proximo = h->proximo;
            
            apaga_no(h);
            return heads;
        }
        anterior = h;
        h = h->proximo;
    }

    printf("%d Jogo inexistente.\n", NL);
    return heads;

}

int main(){
    char comando,nome[MAXNOME];
    char equipa1[MAXNOME], equipa2[MAXNOME];
    int score1 = 0,score2 = 0;
    int flag=0;
    int *pflag=&(flag);
    link *heads = NULL;
    int M = 1013;
    int NL = 0;
    
    link_equipas listaDeEquipas = NULL;               /*as equipas estao guardadas numa lista*/

    heads = Init_hash(heads, 1013);                     /*inicializa a hash*/

    while((comando = getchar()) != 'x'){
        switch(comando){
            case 'a':
                NL++;
                getchar();
                scanf("%[^:\n]:",nome);
                scanf("%[^:\n]:",equipa1);
                scanf("%[^:\n]:",equipa2);
                scanf("%d:%d", &score1, &score2);
                
                heads = adiciona_jogo(NL,heads, M, nome, equipa1, equipa2, score1, score2, listaDeEquipas, pflag);
                if(flag==1){   /* se for 1 quer dizer que o jogo foi adicionado e que sedo assim podemos adicionar as equipas a lista */
                    listaDeEquipas = adiciona_equipa(listaDeEquipas,equipa1,NL);
                    listaDeEquipas = adiciona_equipa(listaDeEquipas,equipa2, NL);
                }
            
                break;
            case 'l':
                NL ++;
                printEverything(heads,M);
                break;

            case 'A':
                NL ++;
                getchar();
                scanf("%[^:\n]",nome);
                listaDeEquipas = adiciona_equipa(listaDeEquipas,nome,NL);
                
                
                break;

            case 'p':
                NL++;
                getchar();
                scanf("%[^:\n]",nome);
                comando_p(heads, M, nome,NL);
                
                break;

            case 'r':
                NL++;
                getchar();
                scanf("%[^:\n]",nome);
                heads = comando_r(heads,M,nome,NL);
                

        }
    }

    delete_list(&(listaDeEquipas));
    destroy_hash(heads,M);
    free(heads);
    return 0;
}   