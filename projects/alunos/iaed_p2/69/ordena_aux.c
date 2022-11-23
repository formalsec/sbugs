#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "ordena_aux.h"

/*sabendo quantas equipas existem com o maximo de vitorias entao vamos
 procura las e adicionar e ordena las por ordem alfabetica num array de
  ponteiros e de seguida dar print de cada uma*/
void lista_melhores_aux(lista_equipas *heads_eq,int mais_vitorias, int tamanho,int count){
    char **Equipas_mais_vit;
    int i,k=0,size;
    lista_equipas aux;
    Equipas_mais_vit=(char**)can_fail_malloc((tamanho)*sizeof(char*));
    for(i=0;i<M;i++){
        aux=heads_eq[i];
        while(aux!=NULL ){
            if(aux->equipa->vitorias==mais_vitorias){
                size=strlen(aux->equipa->nome)+1;
                Equipas_mais_vit[k]=can_fail_malloc(size);
                strcpy(Equipas_mais_vit[k],aux->equipa->nome);
                k++;
            }
            aux=aux->next;
        }
    }
    ordena(Equipas_mais_vit,k);
    printf("%d Melhores %d\n",count,mais_vitorias);
    for(i=0;i<k;i++){
        printf("%d * %s\n",count,Equipas_mais_vit[i]);
    }
    while(--i >= 0){
        free(Equipas_mais_vit[i]);
    }
    free(Equipas_mais_vit);
}

/*funcao que o qsort necessita para poder comparar as strings
 e assim trocar os ponteiros na tabela*/
int comparador(const void* a, const void* b) 
{ 
  
    return strcmp(*(char**)a,*(char**)b); 
} 
  
/*funcao que vai ordenar a tabela */
void ordena( char **arr, int n) 
{ 
    qsort(arr, n, sizeof(const char*), comparador); 
}