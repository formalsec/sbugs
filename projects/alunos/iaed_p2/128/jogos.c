#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogos.h"

/* funcao que adiciona um jogo ao fim da lista dulamente ligada dos jogos*/
void adiciona_fim(limites_lista* lista,Jogo* jogo)
{
    /*aloca memoria para o no'*/
    link_lista n=can_fail_malloc(sizeof(struct lista_jogos));
    /*nao precisa de reservar memoria para o jogo pois este jogo 
    ja pertence a hashtable*/
    n->jogo=jogo;

    /*ponteiro para o elemento anterior aponta para o anterior ultimo
    elemento da lsita e o ponteiro para o seguinte e nulo*/
    n->next=NULL;
    n->prev=lista->last;

    /*se a lista ainda estiver vazia tanto a head como o last 
    passam a ser esse elemento*/
    if(lista->head==NULL)
    {
        lista->head=n;
        lista->last=n;
    }
    /*senao atualiza se a ultima posicao da lista*/
    else
    {
        lista->last->next=n;
        lista->last=n;
    }
}

/*funcao que cria uma lista duplamente ligada para jogos*/
limites_lista* nova_lista()
{
    /*reserva memoria e inicializa a head e last*/
    limites_lista* lista=can_fail_malloc(sizeof(limites_lista));
    lista->head=NULL;
    lista->last=NULL;
    return lista;
}

/*funcao que inicializa uma hashtable para jogos de tamanho m*/
link_jogo* inicializa_hash_jogo(int m)
{
    /*hashtable por encadeamento externo*/
    int i;
    
    /*ponteiros para as hash*/
    link_jogo * heads_jogos;
    /*reserva memoria para m indices da hashtable*/
    heads_jogos=(link_jogo*) can_fail_malloc(m*sizeof(link_jogo));
    /*inicializa-as*/
    for(i=0;i<m;i++)
        heads_jogos[i]=NULL;
    return heads_jogos;
}

/*funcao que cria um novo jogo*/
link_jogo novo_jogo(link* heads,char*buffer,char *equipa1,char *equipa2,int score1,int score2)
{
    int i;
    /*reserva a memoria necessaria para as caracteristicas do jogo necessarias*/
    link_jogo x=(link_jogo) can_fail_malloc(sizeof(struct no));
    x->jogo= can_fail_malloc(sizeof(struct jogo));
    x->jogo->nome=(char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));

    
    /*atribui os dados das equipas(ja previamente existentes)*/
    i= hash(equipa1,HEADS_JOGOS);
    x->jogo->equipa1=encontra_equipa(heads[i],equipa1);

    i= hash(equipa2,HEADS_JOGOS);
    x->jogo->equipa2=encontra_equipa(heads[i],equipa2);

    /*atribui os valores*/
    strcpy(x->jogo->nome,buffer);
    x->jogo->score1=score1;
    x->jogo->score2=score2;

    /*dependentemente se alguem venceu o jogo e' atribuida
    uma vitoria a essa equipa*/
    if(score1>score2)
        x->jogo->equipa1->jogos_ganhos+=1;
    else if(score2>score1)
        x->jogo->equipa2->jogos_ganhos+=1;
    
    x->next=NULL;
   
    return x;
}

/*funcao que insere o jogo no fim da lista duplamente ligada*/
link_jogo insere_jogo(limites_lista* lista,link* heads,link_jogo head,char*buffer,char *equipa1,char *equipa2,int score1,int score2)
{
    /*cria um novo elemento*/
    link_jogo x= novo_jogo(heads,buffer,equipa1,equipa2,score1,score2);
    x->next=head;
    /*adiciona ao fim da lista*/
    adiciona_fim(lista,x->jogo);
    return x;
}

/*funcao que insere o jogo na hashtable dos jogos*/
void insere_jogo_hash(limites_lista* lista,link* heads,link_jogo* heads_jogo,char *nome,char *equipa1,char *equipa2,int score1,int score2)
{
    /*chave da hashtable*/
    int i= hash(nome,HEADS_JOGOS);
    /*introduz o jogo na hash(no indice do jogo) e na lista*/
    heads_jogo[i]=insere_jogo(lista,heads,heads_jogo[i],nome,equipa1,equipa2,score1,score2);
    
}

/*funcao que determina se um jogo ja existe*/
int existe_jogo(link_jogo* heads_jogos,char *nome)
{
    link_jogo aux;
    /*chave da hashtable onde se encontra o jogo*/
    int i=hash(nome,HEADS_JOGOS);
    
    /*percorre todos os elementos da lista desse indice*/
    for(aux=heads_jogos[i];aux!=NULL;aux=aux->next)
    {
        /*se algum nome corresponder ao do jogo e' porque esse jogo ja existe*/
        if(eq(aux->jogo->nome,nome))
            return TRUE;
    }
    return FALSE;
}

/*funcao que encontra e devolve o jogo que corresponde ao nome introduzido*/
Jogo* encontra_jogo(link_jogo head,char* nome)
{
    link_jogo aux;
    /*percorre todos os jogos ate encontrar o pretendido e devolve-o*/
    for(aux=head;aux!=NULL;aux=aux->next)
    {
        if(eq(aux->jogo->nome,nome))
            return aux->jogo;
    }
    /*se nao encontrar devolve nulo*/
    return NULL;
    
}
/*funcao que procura um determinado jogo pelo seu nome*/
Jogo* procura_jogo(link_jogo*heads,char* nome)
{
    /*calcula-se a chave do jogo e devolve-se apos a sua procura*/
    int i= hash(nome,HEADS_JOGOS);
    return encontra_jogo(heads[i],nome);
}

/*funcao que destroi a lista duplamente ligada dos jogos*/
void destroi_lista_jogos(limites_lista* lista)
{
    link_lista head=lista->head;
    /*percorre todos os elementos da lista*/
    while(head!=NULL)
    {
        /*como ja foram libertas as equipas
        apenas se da free aos restantes elementos*/
        lista->head=lista->head->next;
        free(head->jogo->nome);
        free(head->jogo);
        free(head);
        head=lista->head;
    }
    /*destruir a lista*/
    lista->head=NULL;
    lista->last=NULL;
    free(lista);
}

/*funcao que destroi a hashtable dos jogos*/
void destroi_hash_jogos(link_jogo* heads_jogos,int M)
{
    int i;
    link_jogo head;
    /*percorre todos os indices da tabela*/
    for(i=0;i<M;i++)
    {
        head=heads_jogos[i];
        /*percorre todos os elementos de cada tabela*/
        while(head!=NULL)
        {
            /*liberta apenas os nos pois o resto ja foi libertado*/
            heads_jogos[i]=heads_jogos[i]->next;

            free(head);
            head=heads_jogos[i];
        }
        free(heads_jogos[i]);
        
    }
    free(head);
    free(heads_jogos);
}

/*funcao que apaga um jogo da hashtable*/
void apaga_jogo_hash(link_jogo*heads,char* nome)
{
    link_jogo aux,t;
    /*chave do jogo*/
    int i=hash(nome,HEADS_JOGOS);
    aux=heads[i];

    /*caso seja o primeiro elemento*/
    if(eq(aux->jogo->nome,nome))
    {
        /*guarda-se o no' onde se encontrava o jogo e a head passa a ser 
        o proximo elemento*/
        t=aux;
        heads[i]=aux->next;
        
        
    }
    else
    {
        /*percorre-se todos os elementos ate achar o anterior ao do jogo*/
        while(strcmp(aux->next->jogo->nome,nome)!=0)
        {
            aux=aux->next;
        }
        
        /*guarda-se o no' e faz-se a nova ligacao da lista*/
        t=aux->next;
        aux->next=t->next;
    }
    /*liberta-se o no da lista*/
    free(t);
    
        
    

}
/*funcao que apaga o jogo da lista duplamente ligada*/
void apaga_jogo_lista(limites_lista*lista,char*nome)
{
    link_lista t;
    link_lista aux=lista->head;
    /*se for o primeiro elemento*/
    if(eq(aux->jogo->nome,nome))
    {
        t=aux;
        /*se so tiver um elemento coloca-se a head e last com valor nulo*/
        if(lista->head==lista->last)
        {
            lista->head=NULL;
            lista->last=NULL;
        }
        else
        {
            /*senao a head passa a ser o elemento seguinte*/
            lista->head=aux->next;
            /*,mete-se o elemento anterior da head a apontar para o ultimo*/
            lista->head->prev=lista->last;
            /* e o seguinte ao ultimo como nulo*/
            lista->last->next=NULL;
            
        }
        
    }
    else
    {
        /*percorre-se os elementos ate encontrar o elemento pretendido*/
        while(strcmp(aux->jogo->nome,nome)!=0)
        {
            aux=aux->next;
        }
        t=aux;

        /*se nao for o ultimo elemento poe-se liga-se o elemento seguinte ao
        anterior ao do jogo*/
        if(aux->next!=NULL)
            aux->next->prev=t->prev;
        else
        {
            /*senao atualiza-se o last*/
            lista->last=aux->prev;
            
        }

        /*liga-se a lista novamente*/
        aux->prev->next=t->next;
        
        
    }
    /*liberta-se o no' onde se encontrava o jogo*/
    free(t);
    
    
    
}