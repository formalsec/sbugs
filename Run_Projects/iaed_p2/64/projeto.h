#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximo de caracteres numa string. */
#define MAXSTR 1024
/* Tamanho da hash table das equipas. */
#define HASH_TABLE_SIZE_EQUIPAS 593
/* Tamanho da hash table dos jogos. */
#define HASH_TABLE_SIZE_JOGOS 997


/* Estrutura que representa uma equipa. Esta tem 3 ponteiros, 1 que aponta para a 
proxima equipa, 1 que aponta para o nome da equipa e 1 para o numero de jogos ganhos*/
typedef struct str_equipa{
    struct str_equipa * next;
    char *nome;
    int *jogos_ganhos;
} * equipa;

/* Estrutura que representa um jogo. Esta tem 7 ponteiros, 1 que aponta para o proximo
jogo na hash_table (next), 1 que aponta para o proximo jogo na lista (next_lista), 1 
para o nome do jogo, 2 para os nomes das equipas e 2 para os scores destas equipas*/
typedef struct str_jogo{
    struct str_jogo * next;
    struct str_jogo * next_lista;
    char *nome;
    equipa equipa1, equipa2;
    int *score1, *score2;
} * jogo;

/* Funcoes utilizadas no ficheiro jogos.c, associadas a manipulacao da estrutura jogo*/

/* Le o nome do jogo e das equipas a adicionar, assim como os scores das duas 
equipas, verifica se o jogo e inexistente e se as equipas existentes, caso se 
verifiquem as condicoes adiciona o jogo a hash table e a lista ligada */
void add_jogo(equipa *table_equipas, jogo *table_jogos, jogo *head, jogo *tail, int linha);

/* Adiciona jogo a hash table, calculando o indice da tabela correspondente
ao nome do jogo dado atraves da funcao hash*/ 
void add_jogo_hash(jogo *table_jogos, equipa *table_equipas, char *nome, char *equipa1, char *equipa2, int score1, int score2);

/* Aloca memoria para o jogo, para o nome do jogo e para os scores do jogo, cria
o jogo dado o que recebe como input e insere-o no inicio da lista */
jogo insere_jogo(jogo *head, equipa *table_equipas, char *nome, char *equipa1, char *equipa2, int score1, int score2);

/* Apos ter adicionado o jogo a hash table, encontra-o e adiciona-o 
no final da lista ligada, utilizando a tail para tal */
void add_jogo_lista(jogo *head, jogo *tail, jogo *table_jogos, char *nome);

/* Funcao que devolve o jogo com o nome dado, caso nao encontre devolve NULL 
Calcula o indice em que o jogo se pode encontrar na hash table, apenas procurando
na lista correspondente a esse indice*/
jogo procura_jogo(jogo *table_jogos, char *nome);

/* Percorre toda a lista ate encontrar o jogo com o nome dado */
jogo searchList_jogo(jogo head, char *nome);

/* Percorre a lista ligada dos jogos, imprimindo toda a informacao associada aos mesmos */
void print(jogo head, int linha);

/* Le o nome dado, verifica se existe algum jogo com esse nome, caso exista
lista as informacoes correspondentes a esse jogo*/
void print_jogo(jogo *table_jogos, int linha);

/* Altera o score de um jogo, atualizando portanto o numero de jogos ganhos
das equipas desse jogo, caso seja necessario */
void altera_score(jogo *table_jogos, int linha);

/* Le nome do jogo a remover, verifica se o jogo existe, caso exista remove-o
da lista primeiro, e de seguida remove-o da hash table */
void remove_jogo(jogo *head, jogo *tail, jogo *table_jogos, int linha);

/* Percorre a lista da hash table em que se encontra o jogo ate encontrar o jogo
com o nome dado, quando o encontra remove-o da lista e liberta a memoria alocada 
inicialmente para este */
jogo remove_jogo_hash(jogo head, char *nome_jogo);


/*Funcoes utilizadas no ficheiro equipas.c, associadas a manipulacao da estrutura equipa */

/* Le o nome da equipa a adicionar, verifica se ja existe alguma equipa com esse
nome, caso nao exista adiciona-a a hash table, calculando o indice em que lhe
corresponde atraves da funcao hash*/
void add_equipa(equipa *table_equipas, int linha);

/* Funcao que devolve a equipa com o nome dado, caso nao encontre devolve NULL 
Calcula o indice em que a palavra se pode encontrar na hash table, apenas procurando
na lista correspondente a esse indice*/
equipa procura_equipa(equipa *table_equipas, char *nome);

/* Percorre a lista dada ate encontrar a equipa procurada */
equipa searchList(equipa head, char *nome);

/* Aloca memoria para uma nova equipa, atribuindo-lhe o nome dado e inicializando o 
numero de jogos ganhos a zero, insere ainda esta nova equipa no inicio da lista */
equipa  insere_equipa(equipa *head, char *nome);

/* Le o nome dado, verifica se existe alguma equipa com esse nome, caso exista
lista as informacoes correspondentes a essa equipa*/
void print_equipa(equipa *table_equipas, int linha);

/* Funcao que encontra as equipas que ganharam mais jogos, percorre a hash table
duas vezes. Numa primeira vez procura o valor maximo de jogos ganhos e contabiliza
tambem o numero de equipas com este numero de vitorias, cria um vetor com o
comprimento necessario, de seguida percorre uma segunda vez onde adiciona as equipas
que mais ganharam ao vetor criado, ordena ainda lexicograficamente esse vetor*/
void mais_vitorias(equipa * table_equipas, int linha);

/* Aloca memoria para um vetor de strings do tamanho necessario, percorre a 
hash table uma segunda vez (como explicado na funcao mais_vitorias), adicionando
o nome das equipas que mais ganharam ao vetor */
void cria_e_ordena_vetor(equipa *table_equipas, int max, int num, int linha);

/* Funcao que compara duas strings devolvendo a ordem entre estas */
int compara_strings(const void *a, const void *b);


/*Funcoes utilizadas no ficheiro hashtables.c, associadas a manipulacao das hash tables */

/* Funcao hash que utiliza strings como criterio de comparacao. Recalcula a sua
base a cada iteracao, o que evita anomalias com chaves irregulares */
int hash(char *v, int size);

/* Funcao que inicia a tabela hash utilizada para a estrutura jogo, aloca memoria
de acordo com o tamanho da tabela e define todos os seus indices a NULL */
equipa * inicia_hash_equipas(equipa *table_equipas);

/* Funcao que inicia a tabela hash utilizada para a estrutura equipa, aloca memoria 
de acordo com o tamanho da tabela e define todos os seus indices a NULL */
jogo * inicia_hash_jogos(jogo *table_jogos);

/* Funcao utilizada no final de todos os comandos, percorre todas as listas (utilizadas
devido ao encadeamento externo), presentes nas duas hashtables, libertando toda a memoria
alocada para estas tabelas */
void free_final(equipa *table_equipas, jogo *table_jogos);
