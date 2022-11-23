#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "equipas.h"




/*funcao que calcula o indice da hashtable onde se encontra a string*/
int hash(char* n,int m)
{
    int i=0,a=127;
    for(;*n!='\0';n++)
    {
        i=(a*i+*n)%m;
    }
    
    return i;
}

/*funcao que cria um novo elemento equipa*/
link novo_el(char* buffer)
{
    /*reserva a memoria necessaria*/
    link x=(link) can_fail_malloc(sizeof(struct node));
    x->equipa= can_fail_malloc(sizeof(struct equipa));
    x->equipa->nome=(char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));

    /*atribui o nome da equipa e inicializa o n. de jogos ganhos a 0*/
    strcpy(x->equipa->nome,buffer);
    x->equipa->jogos_ganhos=0;
    x->next=NULL;
    
    return x;
}

/*funcao que insere uma equipa no inicio de uma lsita*/
link insere_el(link head,char *text)
{
    /*cria a equipa*/
    link x= novo_el(text);
    /*essa equipa passa a ser o primeiro elemento da lista*/
    x->next=head;
    return x;
}


/*funcao que inicializa uma hashtable para equipas de tamanho m*/
link* inicializa(int m)
{
    int i;
    int M=m;
    link* heads;
    /*reserva memoria para os m nos*/
    heads=(link*) can_fail_malloc(M*sizeof(link));
    /*inicializa*/
    for(i=0;i<M;i++)
        heads[i]=NULL;
    return heads;
}

/*funcao que insere uma equipa na sua lista da hashtable*/
void insere_na_lista(link*heads,char * nome)
{
    /*calcula a chave da equipa*/
    int i= hash(nome,HEADS_EQUIPAS);
    /*insere na lista da sua chave*/
    heads[i]=insere_el(heads[i],nome);
   
}

/*funcao que encontra e devolve a equipa que corresponde ao nome introduzido*/
Equipa* encontra_equipa(link head,char* nome)
{
    link aux;
    /*percorre todos os elementos da lista ate encontrar a equipa*/
    for(aux=head;aux!=NULL;aux=aux->next)
    {
        if(eq(aux->equipa->nome,nome))
            return aux->equipa;
    }
    /*se nao encontrar devolve nulo*/
    return NULL;
    
}

/*funcao que procura uma determinada equipa pelo seu nome*/
Equipa* procura_equipa(link*heads,char* nome)
{
    /*calcula-se a chave da equipa e devolve-se apos a sua procura*/
    int i= hash(nome,HEADS_EQUIPAS);
    return encontra_equipa(heads[i],nome);
}

/*funcao que determina se uma equipa ja existe*/
int existe_el(link*heads,char* nome)
{
    link aux;
    /*calcula a chave*/
    int i=hash(nome,HEADS_EQUIPAS);
    /*percorre os elementos da lista e se encontrar devolve TRUE*/
    for(aux=heads[i];aux!=NULL;aux=aux->next)
        if(eq(aux->equipa->nome,nome))
            return TRUE;
    return FALSE;
}

/*funcao que destroi a hashtable das equipas*/
void destroi_hash_equipa(link* heads,int M)
{
    int i;
    link head;
    /*ciclo para percorrer todas as listas da hashtable*/ 
    for(i=0;i<M;i++)
    {
        head=heads[i];
        /*ciclo para percorrer todos os elementos de uma lista*/
        while(head!=NULL)
        {
            /*liberta-se a memoria do nome da equipa e o proprio no*/
            heads[i]=heads[i]->next;
            free(head->equipa->nome);
            free(head->equipa);
            free(head);
            head=heads[i];
        }
        free(heads[i]);
        
    }
    free(head);
    free(heads);
}

