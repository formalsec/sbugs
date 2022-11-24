#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"

/* nao recebe argumentos inicializa a 
hash table das equipas 
retorna a hash table criada*/
hash_table_equipa * cria_hash_table_equipa(){
    hash_table_equipa * rv = can_fail_malloc(sizeof(hash_table_equipa));
    rv->capacidade_equipa = CAP;
    rv->tb = can_fail_calloc(rv->capacidade_equipa, sizeof(hash_node_equipa)); /* poe tudo a zero */
    return rv; 
}

/* cria a hash funcao que recebe como argumentos 
um ponteiro para char e o inteiro e que cria um 
indice onde posso colocar informacao 
retorna o valor calculdo*/
int hash(char *v, int M) 
{                       /* tirado dos slides */
    int h = 0, a = 127;
    for (; *v != '\0'; v++){
        h = (a*h + *v) % M;
    }
    return h;
}

/* recebe como argumentos de funcao um ponteiros para a 
hash table e um ponteiro para char 
verifica se a palavra ja existe ou nao na hash table das equipas
e retorna um valor caso exista outro se nao
*/
int verificaExiste(hash_table_equipa* t, char * word){
    size_t h = hash(word, t->capacidade_equipa);
    hash_node_equipa * n;
    for(n=t->tb[h]; n != NULL; n = n->next){
        if (strcmp(n->equipa1, word) == 0){  /*  verifica se a pal dentro de cada no e ou nao igual a palavra dada */
            return 0;                    
        }
    }               
    return 1; 
}


/* funcao que recebe como argumento 
de funcao um ponteiro para char
calcula e retorna a memoria que e 
necessaria ser alocada para que determinada string caiba
 */
char *aloca_memoria(const char *s) {
    size_t len = strlen(s) + 1;
    void *new = can_fail_malloc(len);
    if (new == NULL){
        return NULL;
    }
    else{
        return (char *)memcpy(new, s, len);
    }
}

/* funcao que recebe como parametros um ponteiro 
para char e outro para a estrutura hash_node_euipa
faz a inicilizacaoo dos nos da hash_table_equipa
retorna o no inicial
*/
hash_node_equipa * constroiNo_equipa(char * nome_equipa, hash_node_equipa * inicio){
    hash_node_equipa * nn = can_fail_malloc(sizeof(hash_node_equipa));
   
    nn->equipa1 = aloca_memoria(nome_equipa);
    nn->vitorias = 0;
    nn->next = inicio;        /* por a cabeca antiga como o segundo elemento da lista ligada  */  
    inicio = nn;
    return inicio;
}

/* funcao que le uma palavra verifica
 se existe e adiciona na hashtable  */

void adiciona_equipa(hash_table_equipa * HashEquipa, int * Nr_linha){
    int n;
    char buffer[MAX];
    
    scanf("%[^:\n]", buffer);

    n = hash(buffer, HashEquipa->capacidade_equipa);
    
    if(verificaExiste(HashEquipa, buffer) == 0){        /*  verifica se as equipas estao na hash table */
       printf("%d Equipa existente.\n", *Nr_linha);
       *Nr_linha += 1; 
       return ;
    }
    
    HashEquipa->tb[n] = constroiNo_equipa(buffer, HashEquipa->tb[n]);
    *Nr_linha += 1;
}

/* funcao que le uma palavra verifica se existe
 e printa a quipa e o nr de vitorias  */
void procura_equipa(hash_table_equipa * eq, int * Nr_linha){
    char equipa[MAX]; 
    size_t h;
    hash_node_equipa * equipa_aux;
    scanf("%[^:\n]", equipa);
   
    h = hash(equipa, eq->capacidade_equipa);
    for (equipa_aux =  eq->tb[h]; equipa_aux; equipa_aux =  equipa_aux->next){
        if (strcmp(equipa, equipa_aux->equipa1) == 0){
            printf("%d %s %ld\n", *Nr_linha, equipa, equipa_aux->vitorias);
            *Nr_linha += 1;
            return;
        }
    } 
    printf("%d Equipa inexistente.\n", *Nr_linha);
    *Nr_linha += 1;
}

/* compara dois argumentos dados */
int compara_palavras(const void *a, const void *b){ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    
    return strcmp(*ia, *ib);
} 

/* printa nomes das equipa  */
void printa_melhores(char **vetor, size_t comp, int *Nr_linha, int maior) { 
    size_t i;
    if (comp != 0){
        printf("%d Melhores %d\n", *Nr_linha, maior);
    }
    for(i=0; i<comp; i++){
        printf("%d * %s\n", *Nr_linha, vetor[i]);  
    }
} 

/* funcao que encontra o maior e coloca dentro de um vetor 
todos os nomes de equipas com o maior nr de vitorias 
ordena e printa lexicograficamente 
*/
void maisGanhos(hash_table_equipa * eq, int *Nr_linha){ 
    size_t i, maior_aux = 0, maior = 0, cont = 0; int cont_aux = 0;
    char * vetor[MAX]; hash_node_equipa * equipa_aux;
    for (i = 0; i < eq->capacidade_equipa; i++) {
        for (equipa_aux = eq->tb[i]; equipa_aux; equipa_aux = equipa_aux->next) {
            if (equipa_aux->vitorias > maior_aux){ maior_aux = equipa_aux->vitorias; }
            cont_aux++;
        }
    }
    if (cont_aux == 0){ *Nr_linha += 1; return; }
    
    maior = maior_aux;
    for(i=0; i< eq->capacidade_equipa; i++){ 
        for (equipa_aux = eq->tb[i]; equipa_aux; equipa_aux = equipa_aux->next){
            if (equipa_aux->vitorias == maior){ 
                vetor[cont] = equipa_aux->equipa1; cont++; }
        }
    }
    qsort(vetor, cont, sizeof(char *), compara_palavras);
    printa_melhores(vetor, cont, Nr_linha, maior); *Nr_linha += 1;
} 

/* funcao que liberta toda a informacao reletiva a hash table das equipas */
void free_hash_table(hash_table_equipa * t) {
    hash_node_equipa * a;
    size_t i;
    for (i=0; i< t->capacidade_equipa; i++){
        while(t->tb[i]) {
            a = t->tb[i]->next;
            free(t->tb[i]->equipa1);
            free(t->tb[i]); /* free de todos os nos dessa tabela */
            t->tb[i] = a;
        }
    }  
    free(t->tb); /* free da tabela em si */
    free(t);     /*  free a estrutura que armazena a tabela */
} 