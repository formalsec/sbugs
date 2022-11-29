#ifndef __ITEM__
#define __ITEM__

/* Tipo de dados de um jogo/equipa */
typedef struct {
    char *nome;/* Guarda o nome do jogo ou da equipa dependendo do caso */
    char *eq1;/* Caso seja jogo guarda o nome da equipa 1 caso contrario aponta para NULL*/
    char *eq2;/* Caso seja jogo guarda o nome da equipa 2 caso contrario aponta para NULL*/
    int scr[2];/* Guarda o resultado de um jogo ou caso seja uma equipa guarda o numero de vitorias no segundo indice */
}dados;         /* Sendo o primeiro -1 */

typedef dados* item;

/* Tipo de dados utilizado pela lista */
typedef struct {
    int n;
    int m;
    item* vetor;
} lista;

typedef char* Chave;

/* Tipo de dados que ira ser utilizado pelas tabelas de dispersao */
typedef struct{
    lista** itens;
    int m;
    int n;
}tabela;

/* valor pelo qual substituto a pontuacao/numero de vitorias num item apagado */
#define ITEM_APAGADO -1

/* Abstracoes para as estruturas de dados e para o algoritmo de ordenacao */
#define chave(a) (a->nome)
#define NULLitem (NULL)
#define eq(a,b) (!strcmp(a,b))
#define menor(a,b) (strcmp(a,b) < 0)
#define chaveLista(a,i) (a->vetor[i]->nome)
#define atribui(a,k,n) (a->vetor[k] = a->vetor[n])
#define equal(a,b) (!strcmp(chave(a),b) && a->scr[1] >= 0)

/* Prototipo da funcao de hashing */
int hash(char *str,int m);

/* Prototipo da funcao libItem que liberta o espaco ocupado por um item */
void libItem(dados *item);

#endif
