#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "projeto.h"

/* Le o nome da equipa a adicionar, verifica se ja existe alguma equipa com esse
nome, caso nao exista adiciona-a a hash table, calculando o indice em que lhe
corresponde atraves da funcao hash*/
void add_equipa(equipa *table_equipas, int linha){
    int i;
    /* Buffer utilizado para a string */
    char nome_equipa[MAXSTR];

    scanf(" %[^:\n]", nome_equipa);
    
    /* Funcao procura_equipa devolve NULL caso nao encontre equipa com o nome dado*/
    if(procura_equipa(table_equipas, nome_equipa)!=NULL){
        printf("%d Equipa existente.\n", linha);
        return;
    }

    i=hash(nome_equipa, HASH_TABLE_SIZE_EQUIPAS);

    table_equipas[i] = insere_equipa(&table_equipas[i], nome_equipa);

    return;
}

/* Funcao que devolve a equipa com o nome dado, caso nao encontre devolve NULL 
Calcula o indice em que a palavra se pode encontrar na hash table, apenas procurando
na lista correspondente a esse indice*/
equipa procura_equipa(equipa *table_equipas, char *nome_equipa){
    int i;
    i=hash(nome_equipa, HASH_TABLE_SIZE_EQUIPAS);

    return searchList(table_equipas[i], nome_equipa);
}

/* Percorre a lista dada ate encontrar a equipa procurada */
equipa searchList(equipa head, char *nome_equipa){  
    equipa aux;
    aux = head;  
    while (aux != NULL){  
        if (strcmp(aux->nome, nome_equipa)==0){
            return aux;  
        }  
        aux = aux->next;  
    }  
    return NULL;  
} 

/* Aloca memoria para uma nova equipa, atribuindo-lhe o nome dado e inicializando o 
numero de jogos ganhos a zero, insere ainda esta nova equipa no inicio da lista */
equipa insere_equipa(equipa *head, char *nome_equipa){
    equipa novo = (equipa)can_fail_malloc(sizeof(struct str_equipa));
    novo->nome = (char *) can_fail_malloc(sizeof(char)*(strlen(nome_equipa)+1));
    strcpy(novo->nome,nome_equipa);
    novo->jogos_ganhos = (int *) can_fail_malloc(sizeof(int));
    *novo->jogos_ganhos = 0;
    novo->next = *head;
    return novo;
}

/* Le o nome dado, verifica se existe alguma equipa com esse nome, caso exista
lista as informacoes correspondentes a essa equipa*/
void print_equipa(equipa *table_equipas, int linha){
    equipa equipa;
    char nome_buf[MAXSTR];

    scanf(" %[^:\n]", nome_buf);
    
    equipa=procura_equipa(table_equipas, nome_buf);
    if(equipa==NULL){
        printf("%d Equipa inexistente.\n", linha);
    }
    else{
        printf("%d %s %d\n", linha, equipa->nome, *equipa->jogos_ganhos);
    } 
}

/* Funcao que encontra as equipas que ganharam mais jogos, percorre a hash table
duas vezes. Numa primeira vez procura o valor maximo de jogos ganhos e contabiliza
tambem o numero de equipas com este numero de vitorias, cria um vetor com o
comprimento necessario, de seguida percorre uma segunda vez onde adiciona as equipas
que mais ganharam ao vetor criado, ordena ainda lexicograficamente esse vetor*/
void mais_vitorias(equipa *table_equipas, int linha){

    /* max corresponde ao valor maximo de jogos ganhos, num ao numero de
     equipas com esse numero de jogos ganhos */
    int i, max=0, num=0;
    equipa aux;

    /* Primeiro ciclo pela hash table, encontra valor maximo de jogos ganhos e
    numero de equipas com esse numero de jogos ganhos */
    for(i=0; i<HASH_TABLE_SIZE_EQUIPAS; i++){
        for(aux=table_equipas[i]; aux!=NULL; aux=aux->next){
            
            if ((*aux->jogos_ganhos)==max){
                num++;
            }
            else if((*aux->jogos_ganhos)>max){
                num=1;
                max=(*aux->jogos_ganhos);
            }
        }
    }
    /* Verifica se existem equipas adicionadas */
    if(num!=0){
        cria_e_ordena_vetor(table_equipas, max, num, linha);
    }
}

/* Aloca memoria para um vetor de strings do tamanho necessario, percorre a 
hash table uma segunda vez (como explicado na funcao mais_vitorias), adicionando
o nome das equipas que mais ganharam ao vetor */
void cria_e_ordena_vetor(equipa *table_equipas, int max, int num, int linha){
    char **vetor;
    int i, j=0;
    equipa aux;
    vetor = (char**)can_fail_malloc(sizeof(char*)*num);
    
    for(i=0; i<HASH_TABLE_SIZE_EQUIPAS; i++){
        for(aux=table_equipas[i]; aux!=NULL; aux=aux->next){
            if ((*aux->jogos_ganhos)==max){
                vetor[j]=aux->nome;
                j++;
            }
        }
    }
    
    /* Ordena o vetor de strings atraves da funcao built-in qsort */
    qsort(vetor, num, sizeof(char *), compara_strings);
    
    /* Print do vetor ja ordenado */
    printf("%d Melhores %d\n", linha, max);
    for(j=0;j<num;j++){
        printf("%d * %s\n",linha, vetor[j]);
    }

    /* Libertada a memoria alocada para o vetor */
    free(vetor);
}

/* Funcao que compara duas strings devolvendo a ordem entre estas */
int compara_strings(const void *a, const void *b) { 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
} 


