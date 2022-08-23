#define Nome 1024 /*Tamanho maximo dos nomes das equipas e jogos. */
#define Hash_equipas 2131 /*Tamanho da Tabela_hash de equipas. */
#define Hash_jogos 5501 /*Tamanho da Tabela_hash de jogos. */

/*Estrutura de uma equipa.*/
typedef struct equipa{
    char *nome_equipa;
    int *vitorias;
    struct equipa *prox_equipa;
} *equipa_pont;

/*Estrutura de um jogo.*/
typedef struct jogo{
    char *nome_jogo;
    char *equipa1;
    char *equipa2;
    int *golos1;
    int *golos2;
    struct jogo *prox_jogo;
    struct jogo *prox_jogo_lista;
} *jogo_pont;

/*-----------------------Funcoes relacionadas com o ficheiro hashtable.c-----------------------*/

/*Esta funcao devolve a posicao de um elemento de uma tabela hash.*/
unsigned int hash(char *nome, int tamanho);

/*Esta funcao inicializa uma tabela hash de equipas.*/
equipa_pont* inic_hash_equipa();

/*Esta funcao inicializa uma tabela hash de jogos.*/
jogo_pont* inic_hash_jogo();

/*Esta funcao limpa todos os mallocs que tinham sido feitos para ambas as tabelas hash.*/
void limpa(equipa_pont *tabela_hash_equipas, jogo_pont *tabela_hash_jogos);

/*-------------------------Funcoes relacionadas com o ficheiro equipa.c-------------------------*/

/*Esta funcao adiciona uma equipa ao sistema.
 Esta funcao ira gerar um erro se a equipa ja existir no sistema.*/
void adic_equipa(equipa_pont *tabela_hash, int nl);

/*Esta funcao procura uma equipa no sistema.
  Esta funcao ira gerar um erro se a equipa nao existir no sistema.*/
void procura_equipa(equipa_pont *tabela_hash_equipas, int nl);

/*Esta funcao devolve o numero maximo de vitorias e quais a(s) equipa(s)
  que teem esse numero de vitorias no sistema.*/
void mais_vencedoras(equipa_pont *tabela_hash_equipas, int nl);

/*-------------------------Funcoes relacionadas com o ficheiro jogo.c-------------------------*/

/*Esta funcao adiciona um jogo ao sistema.
  Esta funcao ira gerar um erro se o nome do jogo ja existir no sistema 
  ou se uma das equipas nao existir no sistema.*/
void adic_jogo(jogo_pont *lista_jogos_inicio, jogo_pont *lista_jogos_fim, jogo_pont *tabela_hash_jogos, equipa_pont *tabela_hash_equipas, int nl);

/*Esta funcao devolve por ordem de entrada os jogos existentes.*/
void jogos_introduzidos(jogo_pont lista_jogos_inicio, int nl);

/*Esta funcao procura um jogo no sistema.
  Esta funcao ira gerar um erro se o nome do jogo nao existir no sistema.*/
void procura_jogo(jogo_pont *tabela_hash_jogos, int nl);

/*Esta funcao altera o resultado de um jogo do sistema.
  Esta funcao ira gerar um erro se nao existir nenhum jogo com o nome no sistema.*/
void altera_resultado(jogo_pont *tabela_hash_jogos, equipa_pont *tabela_hash_equipas, int nl);

/*Esta funcao remove um jogo do sistema.
  Esta funcao ira gerar um erro se nao existir nenhum jogo com o nome no sistema.*/
void apaga_jogo(jogo_pont *tabela_hash_jogos, equipa_pont *tabela_hash_equipas, jogo_pont *lista_jogos_inicio, jogo_pont *lista_jogos_fim, int nl);