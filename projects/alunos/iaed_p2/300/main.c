#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Equipas.h"
#include "Jogos.h"
#include "ListaLigada.h"

#define MAX 1024 /* Constante para definir o numero de carateres de cada input */

/*--------------------*/
/* FUNCOES PRINCIPAIS */
/*--------------------*/

void funcao_a(node **headsJ, pEquipa *heads, list *Lista, int nl, int m) /* Adiciona um novo jogo */
{
    char nome[MAX], equipa1[MAX], equipa2[MAX];
    int score1, score2;
    pEquipa Primeira, Segunda;
    node *a;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
    if (STsearchJ(headsJ, nome, m) != NULL) /* Se o node for NULL , entao e porque o jogo ja existe */
    {
        printf("%d Jogo existente.\n", nl);
    }
    else /* Se o node for NULL , entao e porque o jogo ainda nao existe */
    {
        if (STsearch(heads, equipa1, m) == NULL || STsearch(heads, equipa2, m) == NULL) /* Se a equipa1 ou a equipa2 for NULL , entao e porque ainda nao existem essas equipas*/
        {
            printf("%d Equipa inexistente.\n", nl);
        }
        else
        {
            if (score1 > score2) /* Se o score1 for maior que o score2 adiciona uma vitoria a equipa 1*/
            {
                Primeira = STsearch(heads, equipa1, m);
                Primeira->vitorias++;
            }
            else if (score1 < score2) /* Se o score2 for maior que o score1 adiciona uma vitoria a equipa 2*/
            {
                Segunda = STsearch(heads, equipa2, m);
                Segunda->vitorias++;
            }
            a = add_last(Lista, nome, equipa1, equipa2, score1, score2); /* Adiciona o jogo a lista e logo de seguida a hashtable */
            STinsertJ(headsJ, a, m);
        }
    }
}

void funcao_l(list *Lista, int nl) /* Lista todos os jogos pela ordem que foram introduzidos */
{
    printList(Lista->head, nl); /* Printa todos os jogos que foram criados com ajuda da funcao printList */
}

void funcao_p(node **headsJ, int nl, int m) /* Procura um jogo com o nome dado e printa caso o jogo existir*/
{
    char nome[MAX];
    node *Search;
    scanf(" %[^:\n]", nome);
    Search = STsearchJ(headsJ, nome, m);
    if (Search == NULL) /* Se o Jogo nao existir print que o jogo nao existe */
    {
        printf("%d Jogo inexistente.\n", nl);
    }
    else /* Se nao printa o nome do jogo, das equipas e o resultado do jogo */
    {
        printJogo(Search, nl);
    }
}

void funcao_r(node **headsJ, pEquipa *heads, int nl, list *Lista, int m) /* Apaga um jogo da estrutura de dados */
{
    char nome[MAX];
    node *Search, *node;
    pEquipa Primeira, Segunda;
    scanf(" %[^:\n]", nome);
    Search = STsearchJ(headsJ, nome, m);
    if (Search == NULL) /* Se o Jogo nao existir print que o jogo nao existe */
    {
        printf("%d Jogo inexistente.\n", nl);
    }
    else /* Se existir entao retira o jogo da lista, da hashtable e retira as vitorias as equipas que tinham ganho esse jogo */
    {
        Primeira = STsearch(heads, Search->jogo->equipa1, m);
        Segunda = STsearch(heads, Search->jogo->equipa2, m);
        if (Search->jogo->score1 > Search->jogo->score2) /* Se nesse jogo quem ganhou foi a equipa1 retira uma vitoria da equipa1 */
        {
            Primeira->vitorias--;
        }
        else if (Search->jogo->score1 < Search->jogo->score2) /* Se nesse jogo quem ganhou foi a equipa2 retira uma vitoria da equipa2 */
        {
            Segunda->vitorias--;
        }

        STdeleteJ(headsJ, nome, m); /* Remove o jogo da hashtable dos jogos*/
        node = Lista->head;
        while (node != NULL) /* Percorre a lista para encontrar o jogo e de seguida remove-lo*/
        {
            if (strcmp(node->jogo->nome, nome) == 0)
            {
                rm_node(Lista, node);
                break;
            }
            node = node->next;
        }
    }
}

void funcao_s(node **headsJ, pEquipa *heads, int nl, int m) /* Altera a pontuacao de um jogo*/
{
    char nome[MAX];
    int score1, score2;
    node *Search;
    pEquipa Primeira, Segunda;
    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
    if (STsearchJ(headsJ, nome, m) == NULL) /* Se o Jogo nao existir print que o jogo nao existe */
    {
        printf("%d Jogo inexistente.\n", nl);
    }
    else
    {
        Search = STsearchJ(headsJ, nome, m);
        Primeira = STsearch(heads, Search->jogo->equipa1, m);
        Segunda = STsearch(heads, Search->jogo->equipa2, m);
        if (Search->jogo->score1 > Search->jogo->score2) /* Estes ifs adicionam e retiram as vitorias de acordo com o input */
        {
            if (score1 > score2)
            {
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
            }
            else if (score2 > score1)
            {
                Primeira->vitorias--;
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
                Segunda->vitorias++;
            }
            else
            {
                Primeira->vitorias--;
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
            }
        }
        else if (Search->jogo->score1 < Search->jogo->score2)
        {
            if (score1 < score2)
            {
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
            }
            else if (score1 > score2)
            {
                Segunda->vitorias--;
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
                Primeira->vitorias++;
            }
            else
            {
                Segunda->vitorias--;
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
            }
        }
        else
        {
            if (score1 < score2)
            {
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
                Segunda->vitorias++;
            }
            else if (score1 > score2)
            {
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
                Primeira->vitorias++;
            }
            else
            {
                Search->jogo->score1 = score1;
                Search->jogo->score2 = score2;
            }
        }
    }
}

void funcao_A(pEquipa *heads, int nl, int m) /* Adiciona uma nova equipa */
{
    char nome[MAX];
    scanf(" %[^:\n]", nome);
    if (STsearch(heads, nome, m) != NULL) /* Se a equipa ja existir nao cria e printa que ja existe */
    {
        printf("%d Equipa existente.\n", nl);
    }
    else
    {
        STinsert(heads, nome, m); /* Se nao existir, cria uma nova equipa */
    }
}

void funcao_P(pEquipa *heads, int nl, int m) /* Procura por uma equipa */
{
    char nome[MAX];
    scanf(" %[^:\n]", nome);
    if (STsearch(heads, nome, m) == NULL) /* Se a equipa nao existir entao printa que nao existe */
    {
        printf("%d Equipa inexistente.\n", nl);
    }
    else
    {
        printEquipa(STsearch(heads, nome, m), nl); /* Se existir, prtinta o nome da equipa e o numero de vitorias */
    }
}

int Compare(const void *a, const void *b) /* Funcao de comparacao para usar no qsort */
{
    char *pa, *pb;
    pa = *(char **)a;
    pb = *(char **)b;
    return (strcmp(pa, pb));
}

void funcao_g(pEquipa *heads, int nl, int m) /* Encontra as equipas que venceram mais jogos */
{
    pEquipa aux;
    char **maiores = NULL;
    int i, maior = 0, equipas = 0, v = 0;
    for (i = 0; i < m; i++) /* De todas as equipas ve qual e que e o maior numero de vitorias */
    {
        aux = heads[i];
        while (aux != NULL)
        {
            if (aux->vitorias > maior)
            {
                maior = aux->vitorias;
            }
            aux = aux->next;
        }
    }
    for (i = 0; i < m; i++) /* Conta quantas equipas tiveram o mesmo numero de vitorias que o maior numero de vitorias*/
    {
        aux = heads[i];
        while (aux != NULL)
        {
            if (aux->vitorias == maior)
            {
                equipas++;
            }
            aux = aux->next;
        }
    }
    if (equipas == 0) /* Se nao houver nenhuma equipa entao nao printa nada*/
    {
        return;
    }
    maiores = can_fail_malloc(sizeof(char *) * equipas); /*Aloca memoria para criar uma lista de nomes*/
    for (i = 0; i < m; i++)
    {
        aux = heads[i];
        while (aux != NULL) /* Adiciona no array os nomes de todas as equipas que tem mais vitorias */
        {
            if (aux->vitorias == maior)
            {
                maiores[v] = aux->nome;
                v++;
            }
            aux = aux->next;
        }
    }
    qsort(maiores, v, sizeof(char *), Compare); /* Ordena o array por ordem lexicografica */
    printf("%d Melhores %d\n", nl, maior);
    for (i = 0; i < v; i++)
    {
        printf("%d * %s\n", nl, maiores[i]); /* Printa o array */
    }
    free(maiores);
}

void funcao_x(pEquipa *heads, node **headsJ, list *Lista, int m) /* Termina o programa, libertando toda a memoria usada*/
{
    int i;
    pEquipa destruir, tempE = NULL;
    node *destruirJ, *temp = NULL;
    for (i = 0; i < m; i++)
    {
        for (destruir = heads[i]; destruir != NULL;)
        {
            tempE = destruir->next;
            freeEquipa(destruir);
            destruir = tempE;
        }

        for (destruirJ = headsJ[i]; destruirJ != NULL;)
        {
            temp = destruirJ->next;
            free(destruirJ);
            destruirJ = temp;
        }
    }
    free(heads);
    free(headsJ);

    free_list(Lista);
}

int main()
{
    pEquipa *heads;
    node **headsJ;
    list *Lista;
    char comando;
    int nl = 1, m = 7349;
    Lista = mk_list();   /* Inicializa Lista */
    headsJ = STinitJ(m); /* Inicializa headsJ*/
    heads = STinit(m);   /* Inicializa heads */
    while (1)
    {                          /* Um ciclo infinito para pedir os comandos e continuar o programa sempre a funcionar, ate o comando ser x que acaba o programa */
        scanf("%c", &comando); /* Pede um comando e consoante esse comando vai para cada funcao */
        switch (comando)
        {
        case 'a':
            funcao_a(headsJ, heads, Lista, nl, m);
            nl++;
            break;
        case 'l':
            funcao_l(Lista, nl);
            nl++;
            break;
        case 'p':
            funcao_p(headsJ, nl, m);
            nl++;
            break;
        case 'r':
            funcao_r(headsJ, heads, nl, Lista, m);
            nl++;
            break;
        case 's':
            funcao_s(headsJ, heads, nl, m);
            nl++;
            break;
        case 'A':
            funcao_A(heads, nl, m);
            nl++;
            break;
        case 'P':
            funcao_P(heads, nl, m);
            nl++;
            break;
        case 'g':
            funcao_g(heads, nl, m);
            nl++;
            break;
        case 'x':
            funcao_x(heads, headsJ, Lista, m);
            return 0;
        }
    }
    return 0;
}