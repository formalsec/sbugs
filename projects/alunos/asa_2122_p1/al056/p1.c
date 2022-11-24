#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR 1

typedef struct sequence_el
{
    int id;
    struct sequence_el *next_el;
}SequenceEl;

typedef struct sequence
{
    int size;
    SequenceEl *first;
    SequenceEl *last;
}Sequence;

Sequence *createSequence(){
    Sequence *s = (Sequence *)can_fail_malloc(sizeof(Sequence));
    s->size = 0;
    s->first = NULL;
    s->last = NULL;
    return s;
}

SequenceEl *createSequenceEl(int id){
    SequenceEl *se = (SequenceEl *)can_fail_malloc(sizeof(SequenceEl));
    se->id = id;
    se->next_el = NULL;
    return se;
}

void freeSequence(Sequence *s){
    SequenceEl *aux1, *aux2;
    aux1 = s->first;
    while (aux1)
    {
        aux2 = aux1->next_el;
        free(aux1);
        aux1 = aux2;
    }
    free(s);
}

void addNumberToSequence(Sequence *s, int id){
    SequenceEl *se = createSequenceEl(id);
    s->size++;
    if (s->first == NULL)/*a sequencia esta vazia*/
    {
        s->first = se;
    }
    else
    {
        s->last->next_el = se;
    }
    s->last = se;
}

void problem1(Sequence *s){
    int i,  j;
    int *seq = can_fail_malloc(s->size * sizeof(int));
    SequenceEl *se = s->first;
    for ( i = 0; i < s->size; i++)/*copia a primeira sequencia para um vetor de inteiros*/
    {
        seq[i] = se->id;
        se = se->next_el;
    }
    int *len_seq = can_fail_malloc(s->size * sizeof(int));
    int *num_seq = can_fail_malloc(s->size * sizeof(int));
    for ( i = 0; i < s->size; i++)/*inicializa os vetores com o tamanha maximo da subsequencia e com o numero de subsequencias*/
    {
        len_seq[i] = 1;
        num_seq[i] = 1;
    }

    for ( i = 1; i < s->size; i++)/*analisa todo vetor a partir da segunda posicao*/
    {
        for ( j = 0; j < i; j++)/*analisa o vetor da primeira posicao ate a posicao i*/
        {
            if (seq[i] > seq[j])
            {

                if (len_seq[i] == len_seq[j] + 1)/*estamos no caso em que o tamanho maximo da subsequencia aumenta*/
                {
                    num_seq[i] = num_seq[i] + num_seq[j];
                }

                if (len_seq[i] < len_seq[j] + 1)/*estamos no caso em que o numero de subsequencias aumenta*/
                {
                    len_seq[i] = len_seq[i] + 1;
                    num_seq[i] = num_seq[j];
                }
            } 
        }
    }
    
    int lis = 0, n_lis = 0;
    for ( i = 0; i < s->size; i++)/*percorre os vetores para encontrar o numero maximo de subsequencias e o tamanho maximo das mesmas*/
    {
        if (len_seq[i] > lis)
        {
            lis = len_seq[i];
            n_lis = 0;
        }

        if (len_seq[i] == lis)
        {
            n_lis = n_lis + num_seq[i];
        }
    }

    printf("%d %d\n", lis, n_lis);    

    free(seq);
    free(len_seq);
    free(num_seq);
}

void problem2(Sequence *s1, Sequence *s2){
    int i,  j;
    int *seq1 = can_fail_malloc(s1->size * sizeof(int));
    SequenceEl *se = s1->first;
    for ( i = 0; i < s1->size; i++)/*copia a primeira sequencia para um vetor de inteiros*/
    {
        seq1[i] = se->id;
        se = se->next_el;
    }
    int *seq2 = can_fail_malloc(s2->size * sizeof(int));
    se = s2->first;
    for ( i = 0; i < s2->size; i++)/*copia a segunda sequencia para um vetor de inteiros*/
    {
        seq2[i] = se->id;
        se = se->next_el;
    }

    int *len_seq = can_fail_malloc(s2->size * sizeof(int));

    for ( i = 0; i < s2->size; i++)/*inicializa o vetor com o tamanha maximo da subsequencia comum entre as duas sequencias*/
    {
        len_seq[i] = 0;
    }

    int current_path = 0;

    for ( i = 0; i < s1->size; i++)/*analisa todos as posicoes do vetor da sequencia 1*/
    {
        
        for ( j = 0; j < s2->size; j++)/*analisa todas as posicoes da sequencia 2 por cada posicao da sequencia 1*/
        {
            if(seq1[i] > seq2[j])/*estamos no caso em que a posicao da primeira sequencia e superior ao da segunda*/
            {
                if (len_seq[j] > current_path)
                {
                    current_path = len_seq[j];/*aumentamos o caminho atual que contem o tamanho da subsequencia superior para a posicao i*/
                }
            }

            if (seq1[i] == seq2[j])/*estamos no caso em que encontramos um elemento em comum*/
            {
                if (len_seq[j] <= current_path)
                {
                    len_seq[j] = current_path + 1;/*aumentamos o tamanho maximo da  subsequencia na posicao encontrada*/
                }
            }
        }
        current_path = 0;/*reset ao valor do caminho sempre que passamos a posicao seguinte da primeira sequencia*/
    }
    
    int lcis = 0;

    for ( i = 0; i < s2->size; i++)/*percorremos o vetor e tiramos o valor da maior subsequencia crescente comum*/
    {
        if (len_seq[i] > lcis)
        {
            lcis = len_seq[i];
        }
    }
    
    printf("%d\n", lcis);

    free(seq1);
    free(seq2);
    free(len_seq);
}


int main()
{
    int num_sequences, tmp;
    char aux;
    Sequence *s1 = createSequence();
    if (scanf("%d", &num_sequences))/*le do stdout o numero de sequencias*/
    {
        while(scanf("%d", &tmp)){/*le a primeira sequencia*/
            addNumberToSequence(s1, tmp);
            if(scanf("%c", &aux)){
                if(aux == '\n'){
                    break;
                }
            }
        }
        if(num_sequences == 2)
        {
            Sequence *s2 = createSequence();
            while(scanf("%d", &tmp)){/*le a segunda a sequencia*/
                addNumberToSequence(s2, tmp);
                if(scanf("%c", &aux)){
                    if(aux == '\n'){
                        break;
                    }
                }
            }
            
            problem2(s1, s2);

            freeSequence(s1);
            freeSequence(s2);
        }
        else{

            problem1(s1);

            freeSequence(s1);
        }
    }
    return SUCCESS;
}