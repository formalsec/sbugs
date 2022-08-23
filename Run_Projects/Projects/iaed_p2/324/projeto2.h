#define SIZE 1023
#define HASHTABLE_SIZE 1021

/**************************************************************************************************/

/* Definir ESTRUTURAS:


ESTRUTURA DEFINIDA: 'vencedores'.
VARIAVEIS: Uma string do tamanho SIZE.
*/
typedef struct lista_v
{
    char vencedor[SIZE];
} vencedores;

/**************************************************************************************************/

/*
ESTRUTURA DEFINIDA: 'e_node'.
VARIAVEIS: Um ponteiro para uma string, um inteiro e um ponteiro para uma nova estrutura e_node.
*/
typedef struct equip
{
   char *nome;
   int vitorias;
   struct equip *next;
} e_node;

/**************************************************************************************************/

/*
ESTRUTURA DEFINIDA: 'jg_node'.
VARIAVEIS: Quatro ponteiros para strings, dois inteiro e dois ponteiros para novas estruturas jg_node.
*/
typedef struct jg_node
{
   char *value,*equipa1, *equipa2;
   int score1,score2;
   struct jg_node *next, *previous;
} jg_node;

/**************************************************************************************************/

/*
ESTRUTURA DEFINIDA: 'jogos'.
VARIAVEIS: Dois ponteiros para novas estruturas jg_node.
*/
typedef struct jg
{
   jg_node * head, *last;
} jogos;

/**************************************************************************************************/

/*
ESTRUTURA DEFINIDA: 'node'.
VARIAVEIS: Um ponteiro para uma nova estrutura jg_node, um ponteiro para uma string e um pornteiro 
            para uma nova estrutira node.
*/
typedef struct node
{
    jg_node * jogo;
    char *nome_jogo;
    struct node *next;
} node;

/**************************************************************************************************/

/*FUNCAO MAIN

Inicia quase todas as estruturas existentes no programa, onde serao guardadas os diversos 
dados. Possui um algoritmo de 'menu'. Apos ler o caracter inicial de cada linha, dependendo 
da letra do comando redireciona para diferentes funcoes/comandos.
*/

/**************************************************************************************************/

/*RESTANTES FUNCOES*/

/**************************************************************************************************/

/*
FUNCAO: 'get_location'.

OBJETIVO: Arranjar o indice da localizacao da string na hash.

DESCRICAO: Vai calcular atraves de contas especificas um numero entre 0 e o tamanho total da hash.
*/
int get_location(char *v);

/**************************************************************************************************/

/*
FUNCAO: 'mk_list_jg'.

OBJETIVO: Inicializar a lista ligada dos jogos.

DESCRICAO: Vai alocar memoria suficiente para a lista de jogos e inicializa a.
*/
jogos * mk_list_jg();

/**************************************************************************************************/

/*
FUNCAO: 'free_node_jg'.

OBJETIVO: Liberta a memoria alocada em nos argumentos do no do tipo jg_node.

DESCRICAO: Vai em libertar a memoria de cada argumento individualmente.
*/
void free_node_jg(jg_node * n);

/**************************************************************************************************/

/*
FUNCAO: 'free_list_jg'.

OBJETIVO: Liberta a memoria alocada em cada no da lista de jogos.

DESCRICAO: Vai a cada no da lista ligada, desconecta la e libertar a memoria alocada.
*/
void free_list_jg(jogos *l);

/**************************************************************************************************/

/*
FUNCAO: 'add_last_jg'.

OBJETIVO: Adicionar um novo no a lista de jogos.

DESCRICAO: Vai alocar memoria para novo no, copiar a nova informacao e ligar aos restantes elementos.
*/
jg_node *add_last_jg(jogos *l, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2);

/**************************************************************************************************/

/*
FUNCAO: 'insert_new_e_node'.

OBJETIVO: Adicionar um novo no a hash das equipas.

DESCRICAO: Vai alocar memoria para novo no, copiar a nova informacao e ligar aos restantes elementos.
*/
void insert_new_e_node(e_node** head, char *nome_equipa);

/**************************************************************************************************/

/*
FUNCAO: 'insert_into_equipas'.

OBJETIVO: Localizar a posicao para adicionar a nova string a hash.

DESCRICAO: Vai achar o indice da string na tabela hash e verificar onde colocar o novo no.
*/
void insert_into_equipas(e_node** hashtable, char *nome);

/**************************************************************************************************/

/*
FUNCAO: 'insert_new_node'.

OBJETIVO: Adicionar um novo no a hash dos jogos.

DESCRICAO: Vai alocar memoria para novo no, copiar a nova informacao e ligar aos restantes elementos.
*/
void insert_new_node(node** head,jg_node * jg);

/**************************************************************************************************/

/*
FUNCAO: 'insert_into_table'.

OBJETIVO: Localizar a posicao para adicionar a nova string a hash.

DESCRICAO: Vai achar o indice da string na tabela hash e verificar onde colocar o novo no.
*/
void insert_into_table(node** hashtable,jg_node *jg);

/**************************************************************************************************/

/*
FUNCAO: 'get_hashtables'.

OBJETIVO: Criar hash de jogos.

DESCRICAO: Vai alocar espaco para a nova hash e criar.
*/
node ** get_hashtables();

/**************************************************************************************************/

/*
FUNCAO: 'get_hashtable_equipas'.

OBJETIVO: Criar hash de equipas.

DESCRICAO: Vai alocar espaco para a nova hash e criar.
*/
e_node ** get_hashtable_equipa();

/**************************************************************************************************/

/*
FUNCAO: 'existe_equipa'.

OBJETIVO: Verificar a existencia da equipa na hash.

DESCRICAO: Vai achar a localizacao da string na hash e verificar se existe.
*/
int existe_equipa(e_node **hashtable, int location, char *texto);

/**************************************************************************************************/

/*
FUNCAO: 'a_comando'.

OBJETIVO: Adicionar um novo jogo a hash e a lista de jogos.

DESCRICAO: Chamada quando declarado o comando 'a', onde se vai verificar a existencia do jogo,
         posteriormente das equipas e adiciona os argumentos a lista e a hash.

ERROS: No caso de ja existir um jogo com esse nome no sistema e no caso de uma das equipas ou ambas 
      nao existirem no sistema.
*/
void a_comando(jogos *jg,node ** jg_hash,e_node **eqp_hash, int NL);

/**************************************************************************************************/

/*
FUNCAO: 'l_comando'.

OBJETIVO: Listar todos os jogos introduzidos.

DESCRICAO: Chamada quando declarado o comando 'l', onde se vai correr a lista de jogos e printa la.

ERROS: NENHUM.
*/
void l_comando(jogos *jg, int NL);

/**************************************************************************************************/

/*
FUNCAO: 'p_comando'.

OBJETIVO: Procurar um jogo com o nome dado.

DESCRICAO: Chamada quando declarado o comando 'p', onde se vai procurar na hash dos jogos a existencia
            do jogo.

ERROS: No caso de nao existir nenhum jogo com esse nome no sistema.
*/
void p_comando(node **hashtable, int NL);

/**************************************************************************************************/

/*
FUNCAO: 'remove_vitorias'.

OBJETIVO: Decrementar uma vitoria na equipa vencedora de um jogo.

DESCRICAO: Vai determinar o vencedor do jogo e decrementar um na variavel vitorias da hash.
*/
void remove_vitoria(node * aux,e_node ** equipas);

/**************************************************************************************************/

/*
FUNCAO: 'remove_jogo'.

OBJETIVO: Desconectar o no de um jogo da lista de jogos.

DESCRICAO: Vai encontrar o jogo e apagar as ligacoes desse jogo com os restantes jogos na lista de
            jogos e apagar a key que determina a localizacao do jogo na hash.
*/
void remove_jogo(jogos * jg,node *aux);

/**************************************************************************************************/

/*
FUNCAO: 'r_comando'.

OBJETIVO: Apagar um jogo dado um nome.

DESCRICAO: Chamada quando declarado o comando 'r', onde se vai procurar na hash dos jogos a existencia
            do jogo e eliminar o devido jogo da lista de jogos.

ERROS: No caso de nao existir nenhum jogo com esse nome no sistema.
*/
void r_comando(jogos * jg, node ** hashtable, e_node ** equipas, int NL);

/**************************************************************************************************/

/*
FUNCAO: 's_comando'.

OBJETIVO: Alterar o score de um jogo.

DESCRICAO: Chamada quando declarado o comando 's', onde se vai procurar na hash dos jogos a existencia
            do jogo e alterar os scores do jogo.

ERROS: No caso de nao existir nenhum jogo com esse nome no sistema.
*/
void s_comando(node ** hashtable,e_node ** equipas,int NL);

/**************************************************************************************************/

/*
FUNCAO: 'A_comando'.

OBJETIVO: Adicionar uma nova equipa.

DESCRICAO: Chamada quando declarado o comando 'A', onde se vai procurar na hash das equipas a existencia
            da equipa e adiciona la a hash caso nao exista.

ERROS: No caso de ja existir uma equipa com esse nome no sistema.
*/
void A_comando(e_node ** hashtable, int NL);

/**************************************************************************************************/

/*
FUNCAO: 'P_comando'.

OBJETIVO: Procurar uma equipa dado um nome.

DESCRICAO: Chamada quando declarado o comando 'P', onde se vai procurar na hash das equipas a existencia
            da equipa e mostrar o numero de vitorias.

ERROS: No caso de nao existir nenhuma equipa com esse nome no sistema.
*/
void P_comando(e_node ** hashtable, int NL);

/**************************************************************************************************/

/*
FUNCAO: 'copia_produto'.

OBJETIVO: Criar uma copia.

DESCRICAO: Vai copiar para a nova estrutura uma copia de uma string.
*/
vencedores copia_produto(vencedores l);

/**************************************************************************************************/

/*
FUNCAO: 'listar_vencedores'.

OBJETIVO: Criar uma lista dos vencedores.

DESCRICAO: Vai copiar para a lista os vencedores que estao na hash e printa los.
*/
void listar_vencedores(e_node ** equipas, int maior, int conta, int NL);

/**************************************************************************************************/

/*
FUNCAO: 'g_comando'.

OBJETIVO: Listar as equipas vencedoras.

DESCRICAO: Chamada quando declarado o comando 'g', onde se vai procurar na hash das equipas e procurar
            o maior numero de vitorias e listar todas as equipas com esse numero de vitorias, 
            por ordem alfabetica.

ERROS: NENHUM.
*/
void g_comando(e_node ** equipas, int NL);

/**************************************************************************************************/

/*
FUNCAO: 'free_equipas'.

OBJETIVO: Libertar a memoria da hash das equipas.

DESCRICAO: Vai a cada indice da hash e posteriormente a cada elemento e libertar a memoria alocada.
*/
void free_equipas(e_node ** equipas);

/**************************************************************************************************/

/*
FUNCAO: 'free_table'.

OBJETIVO: Libertar a memoria da hash dos jogos.

DESCRICAO: Vai a cada indice da hash e posteriormente a cada elemento e libertar a memoria alocada.
*/
void free_table(node ** table, jogos *lista_jogos);

/**************************************************************************************************/

/*
FUNCAO: 'free_all'.

OBJETIVO: Libertar a memoria de todas as estruturas criadas no programa.

DESCRICAO: Vai a cada estrutura individualmente e libertar memoria alocada.
*/
void free_all(jogos *lista_jogos, node ** table, e_node ** equipas);

/**************************************************************************************************/