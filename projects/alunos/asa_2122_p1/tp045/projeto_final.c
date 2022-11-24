#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define BLOCK (1);

#define max(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct Seq
{
    int *array;
    int size;

} Seq;

void print_sequence(Seq *a);
Seq *read_sequence(void);
int *list(int arr[], int n);
int lcs(Seq *a, Seq *b);
void free_sequence(Seq *a);

int main()
{
    Seq *a, *b;
    char command;
    int lcs_result;

    int *resposta;

    int i;

    int *arrayOne = NULL;
    int val;
    int s = 0;

    if ((scanf("%c\n", &command)) != 1)
    {
        return -1;
    }

    if (command == '1')
    {
        while (scanf("%d", &val) != EOF)
        {
            arrayOne = (int *)can_fail_realloc(arrayOne, sizeof(int) * (s + 1));
            arrayOne[s] = val;
            s++;
        }
        resposta = list(arrayOne, s);
        printf("%d %d\n", resposta[0], resposta[1]);

        free(arrayOne);
    }

    if (command == '2')
    {
        a = read_sequence();
        b = read_sequence();

        int **table = (int **)can_fail_malloc((a->size + 1) * sizeof(int *));

        for (i = 0; i < a->size; i++)
        {
            table[i] = (int *)can_fail_malloc((b->size + 1) * sizeof(int));
        }

        lcs_result = lcs(a, b);

        printf("%d\n", lcs_result);

        for (i = 0; i < a->size; i++)
        {
            free(table[i]);
        }

        free(table);

        free_sequence(a);
        free_sequence(b);
    }

    return 0;
}

Seq *read_sequence(void)
{

    Seq *a;
    int i, space, counter, counter2, ans, temp;
    char c = ' ';

    ans = 1;
    counter2 = 0;

    space = BLOCK;
    counter = 0;

    a = (Seq *)can_fail_malloc(sizeof(Seq));

    a->array = (int *)can_fail_malloc(space * sizeof(int));

    a->size = 0;

    
    for (i = 0; c != '\n' && c != EOF; i++)
    {
        if (counter == space)
        {
            space += BLOCK;
            a->array = (int *)can_fail_realloc(a->array, space * sizeof(int));
        }

        if ((scanf("%d", &temp)) != 1)
        {
            break;
        }

        if (temp == ans)
        {
            counter2++;

            if (counter2 == 3)
            {
                counter2 = 0;
                i--;
            }

            continue;
        }
        else
        {
            a->array[i] = temp;
            ans = a->array[i];
        }

        counter += 1;
        a->size += 1;
        c = getchar();
    }

    return a;
}

void print_sequence(Seq *a)
{
    int i;

    for (i = 0; i < a->size; i++)
    {
        printf("%d ", a->array[i]);
    }
    puts(" ");
    printf("size:%d\n", a->size);
}

void free_sequence(Seq *a)
{
    free(a->array);
    free(a);
}

int *lis(Seq *a)
{
    int i, j, max, counter;
    int table[a->size];
    int static result[2];

    i = 0;
    j = 0;
    max = 0;
    counter = 0;

    result[0] = 0;
    result[1] = 0;

    for (i = 0; i < a->size; i++)
    {
        table[i] = 1;
    }

    for (i = 2; i < a->size; i++)
    {
        for (j = 1; j < i; j++)
        {
            if (a->array[i] > a->array[j] && table[i] < table[j] + 1)
            {

                table[i] = table[i] + 1;

                if (table[i] > max)
                {
                    max = table[i];
                    counter = 1;
                }

                if (table[i] == max)
                {
                    counter++;
                }
            }
        }
    }

    result[0] = max;
    result[1] = counter;

    return result;
}

int lcs(Seq *a, Seq *b)
{

    int i, j;
    int result;
    int tabela[b->size];
    int current = 0;

    if (a->size == 0 || b->size == 0) {
        return 0;
    }

    for (j = 0; j<b->size;j++){
        tabela[j]= 0;
    }
    for (i = 0; i<a->size;i++){
        current = 0;
        for (j = 0; j<b->size;j++){
            if(a->array[i] == b->array[j]){
                if (current +1 > tabela[j]){
                    tabela[j] = current +1;
                }
            }
            if (a->array[i] > b->array[j]){
                if (tabela[j] > current){
                    current = tabela [j];
                }
            }
        }
    }

    result = 0;
    for (i = 0; i<b->size;i++){
        if (tabela[i]>result){
            result = tabela[i];
        }
    }
    return result;

}

/* receives array and size of array */
int *list(int arr[], int n)
{
    int aux[n];
    int j;
    int i;
    /*int k;*/
    int tamanho_maximo = 1;
    int c = 0;
    int cp[n];
    /*int h;
     int *resposta1 = can_fail_malloc ((sizeof(int))* n); */
    static int resposta[2];
    aux[0] = 1;
    cp[0] = 1;
    for (i = 1; i < n; i++)
    {
        aux[i] = 1;
        cp[i] = 1;
        for (j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && aux[i] < aux[j] + 1)
            {
                aux[i] = aux[j] + 1;
                cp[i] = cp[j];
                if (tamanho_maximo < aux[i])
                {
                    tamanho_maximo = aux[i];
                }
            }
            else if (aux[i] == aux[j] + 1)
            {
                cp[i] += cp[j];
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (aux[i] == tamanho_maximo)
        {
            c += cp[i];
        }
    }

    resposta[0] = tamanho_maximo;
    resposta[1] = c;

    /*
    for (h = 0; h<n; h++){
        printf("%d | %d | %d\n", aux[h], arr[h], cp[h]);
    }
    printf("__________________________________\n");
    */

    return resposta;
}