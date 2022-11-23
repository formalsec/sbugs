#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hashtable.h"


int hash(Key value, int m){return value%m;}

/*inicializa a lista que vai colocar os jogos por ordem de insercao*/
lista* lista_por_ordem_inicializar(){
    lista *nova_lista=can_fail_malloc(sizeof(lista));
    nova_lista->head=NULL;
    nova_lista->last=NULL;
    return nova_lista;
}




/*nesta lista os elementos sao inseridos no final*/
void lista_por_ordem_add(lista *l, Jogo jogo1){
    lista_jogos ultimo=can_fail_malloc(sizeof(struct str_jogos));
    ultimo->jogo=jogo1;
    ultimo->next=NULL;
    if(l->head==NULL){
        l->head=ultimo;
        l->last=ultimo;
    }
    else{
        l->last->next=ultimo;
        l->last=ultimo;
    }
}
/*quando um jogo e apagado tambem tem de ser apagado na lista ordenada*/
void apagar_jogo_lista_por_ordem(lista *l, char *nome){
    lista_jogos aux,prev;
    for(aux=l->head,prev=NULL;strcmp(aux->jogo->nome_jogo,nome)!=0;prev=aux,aux=aux->next)
    ;
            /*quando o jogo a remover e o unico*/
            if(aux==l->head && aux==l->last){
                l->head=aux->next;
                l->last=aux->next;

                free(aux);
            }
            /*quando o jogo a remover esta no inicio*/
            else if(aux==l->head){
                l->head=aux->next;
                free(aux);
            }
            /*quando o jogo a remover esta no final da lista*/
            else if(aux==l->last){
                l->last=prev;
                l->last->next=NULL;
                free(aux);
            }
            /*quando o jogo a remover esta entre duas estruturas que contem outros jogos*/
            else{
                prev->next=aux->next;
                free(aux);
            }
}
/*vai dar print das informacoes de cada jogo listando pela ordem de insercao*/
void listar_jogos(lista *l, int count){
    lista_jogos t;
    for(t=l->head;t!=NULL;t=t->next){
        printf("%d %s %s %s %d %d\n",count, t->jogo->nome_jogo,t->jogo->equipa1,
            t->jogo->equipa2,t->jogo->sc1,t->jogo->sc2);
    }
}
/*vai inicializar a hashtable dos jogos*/
lista_jogos* lst_inicializar_jg(lista_jogos *heads_jg) {
    int i;
    heads_jg = (lista_jogos*)can_fail_malloc(M*sizeof(lista_jogos));
    for (i = 0; i < M; i++){
        heads_jg[i] = NULL;
    }
    return heads_jg;
}
/*vai inicializar a hashtable das equipas*/
lista_equipas* lst_inicializar_eq(lista_equipas *heads_eq) {
    int i;
    heads_eq = (lista_equipas*)can_fail_malloc(M*sizeof(lista_equipas));
    for (i = 0; i < M; i++){
        heads_eq[i]=NULL;
    }
    return heads_eq;
}
/*funcao auxiliar da jginserir que adiciona o novo jogo a linked list*/
lista_jogos inserirInicio_da_Lista_JG(lista_jogos head_jg,Jogo jogo1){
    lista_jogos nova_head_jg;
    nova_head_jg=(lista_jogos)can_fail_malloc(sizeof(struct str_jogos));
    nova_head_jg->jogo=jogo1;
    nova_head_jg->next=head_jg;
    return nova_head_jg;
    
}
/*funcao auxiliar da eqinserir que adiciona a nova equipa a linked list*/
lista_equipas inserirInicio_da_Lista_EQ(lista_equipas head_eq,Equipa equipa){
    lista_equipas nova_head_eq;
    nova_head_eq=(lista_equipas)can_fail_malloc(sizeof(struct str_equipas));
    nova_head_eq->equipa=equipa;
    nova_head_eq->next=head_eq;
    return nova_head_eq;
    
}
/*insere o novo jogo na linked list e atualiza a hastable com
a nova cabeca da linked list*/
void JGinserir(lista_jogos *heads_jg, Jogo jogo){
    int i = hash(key(jogo), M);
    heads_jg[i] = inserirInicio_da_Lista_JG(heads_jg[i], jogo);
}
/*insere a nova equipa na linked list e atualiza a hastable com
a nova cabeca da linked list*/
void EQinserir(lista_equipas *heads_eq,Equipa equipa){
    int i = hash(key(equipa), M);
    heads_eq[i] = inserirInicio_da_Lista_EQ(heads_eq[i], equipa);
}
/*retorna a estrutura lista jogos que contem o jogo que se procura*/
lista_jogos procuraLista_jg(lista_jogos head_jg,char *nome_jogo2){
    lista_jogos t;
    for(t=head_jg;t!=NULL;t=t->next){
          if(strcmp(t->jogo->nome_jogo,nome_jogo2)==0)
            return t;
    }
    return NULL;
}

lista_jogos JGprocurar(lista_jogos *heads_jg, char *nome_jogo){
    int id=cria_id(nome_jogo);
    int i=hash(id,M);
    return procuraLista_jg(heads_jg[i],nome_jogo);
}

/*retorna a estrutura lista equipas que contem a equipa que se procura*/
lista_equipas procuraLista_eq(lista_equipas head_eq, char *nome_equipa){
    lista_equipas t;
    for(t=head_eq;t!=NULL;t=t->next){
        if(strcmp(t->equipa->nome,nome_equipa)==0)
            return t;
    }
    return NULL;
}


lista_equipas EQprocurar(lista_equipas *heads_eq, char *nome_equipa){
    int id=cria_id(nome_equipa);
    int i=hash(id,M);
    return procuraLista_eq(heads_eq[i],nome_equipa);
}
/*vai eliminar a estrutura que contem o jogo a eliminar da linked list 
associada a hashtable num determinado indice*/
lista_jogos Elimina_jogo_aux(lista_jogos head_jg, char *nome){
    lista_jogos anterior,aux;
    for(aux=head_jg,anterior=NULL;aux!=NULL;anterior=aux,aux=aux->next){
        if(strcmp(aux->jogo->nome_jogo,nome)==0){
            if(aux==head_jg){
                head_jg=aux->next;
            }
            else{
                anterior->next=aux->next;
                
            }
            free_jogo(aux->jogo);
            free(aux);
            return head_jg;
        }
    }  
    return head_jg;
}


void Elimina_jogo(lista_jogos *heads_jg, char *nome){
    int id=cria_id(nome);
    int i=hash(id,M);
    heads_jg[i] = Elimina_jogo_aux(heads_jg[i],nome);
}




/*-------------- dar free nas hashtbles e na linked list ordenada-----------------*/
void free_heads_jg(lista_jogos *heads_jg){
    int i;
    lista_jogos aux;
    for(i=0;i<M;i++){
        aux=heads_jg[i];
        while(heads_jg[i]!=NULL){
            aux=heads_jg[i]->next;
            free_jogo(heads_jg[i]->jogo);
            free(heads_jg[i]);
            heads_jg[i]=aux;
        }
        free(heads_jg[i]);
    }
    free(heads_jg);
}

void free_heads_eq(lista_equipas *heads_eq){
    int i;
    lista_equipas aux;
    for(i=0;i<M;i++){
        aux=heads_eq[i];
        while(heads_eq[i]!=NULL){
            aux=heads_eq[i]->next;
            free_equipa(heads_eq[i]->equipa);
            free(heads_eq[i]);
            heads_eq[i]=aux;
        }
        free(heads_eq[i]);
    }
    free(heads_eq);
}


void free_head(lista *l){
    lista_jogos aux;
    while(l->head!=NULL){
        aux=l->head->next;
        
        free(l->head);
        l->head=aux;
    }

    free(l);
}