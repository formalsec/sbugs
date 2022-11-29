#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "lista_char.h"

/*funcao usada para comparar strings*/
int comparar_nome(const void*nome1,const void*nome2)
{
    return strcmp(*((char**)nome1),*((char**)nome2));
}

/*funcao que insere uma equipa numa lista ligada*/
link insere_el_char(link head,Equipa*equipa)
{
    /*reserva memoria*/
    link x=(link)can_fail_malloc(sizeof(struct node));
    x->equipa=equipa;
    x->next=head;
    return x;
}

/*funcao que destroi uma lista simplesmente ligada*/
link destroi(link head)
{
    link aux,t;
    /*percorre todos os elementos e liberta-se os nos*/
    for(aux=head;aux!=NULL;aux=t)
    {
        t=aux->next;
        free(aux);
        
    }
    /*nao se apaga a head para a lista ser utilizada novamente*/
    return aux;
}