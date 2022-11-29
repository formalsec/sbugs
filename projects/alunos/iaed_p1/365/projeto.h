#define MAXPROD 10000
#define MAXENC 500
#define MAXDESCR 63
#define MAXENCPROD 200

/***************************************************************************************/

/* Definir ESTRUTURAS:


ESTRUTURA DEFINIDA: 'product'.
VARIAVEIS: Quatro do tipo inteiro e uma string (conjunto de no maximo MAXDESCR caracteres.)
*/
typedef struct{
    int preco, peso, qtd, idp;
    char descricao[MAXDESCR];
} product;

/***************************************************************************************/

/*
ESTRUTURA DEFINIDA: 'pedido'.
VARIAVEIS: Duas do tipo inteiro.
*/
typedef struct
{
    int idp, qntd;
} pedido;

/***************************************************************************************/

/*
ESTRUTURA DEFINIDA: 'encomendas'.
VARIAVEIS: Tres do tipo inteiro e uma estrutura do tipo 'pedido', com MAXENCPROD indices.
*/
typedef struct
{ 
    int ide, peso_total, num_pedidos;
    pedido pedidos[MAXENCPROD];
} encomendas;

/***************************************************************************************/

/*FUNCAO MAIN

Inicia quase todas as estruturas existentes no programa, onde serao guardadas os diversos 
dados. Possui um algoritmo de 'menu'. Apos ler o caracter inicial de cada linha, dependendo 
da letra do comando redireciona para diferentes funcoes.
*/

/***************************************************************************************/


/* Definir FUNCOES AUXILIARES da MAIN


FUNCAO: 'a_comando'.

OBJETIVO: adicionar um novo produto ao sistema.

DESCRICAO: Chamada quando declarado o comando 'a', onde se 'cria' um indice do produto e 
se le os respetivos dados do standard input, guardando os na estrutura 'prod' criada na 
funcao main.

ERROS: NENHUM.
*/
void a_comando(product prod[], int idp);

/***************************************************************************************/

/*
FUNCAO: 'q_comando'.

OBJETIVO: adicionar stock a um produto existente no sistema.

DESCRICAO: Chamada quando declarado o comando 'q', onde se cria duas variaveis locais
para guardar os valores lidos dos standard input. Posteriormente e verificado se na 
estrutura 'prod' se o produto selecionado existe.

ERROS: Caso nao exista o produto selecionado escreve uma mensagem de erro no output.
*/
void q_comando(product prod[]);

/***************************************************************************************/

/*
FUNCAO: 'N_comando'.

OBJETIVO: Criar uma nova encomenda.

DESCRICAO: Chamada quando declarado o comando 'N', onde se 'cria' um indice da encomenda, 
guardando os na estrutura 'new_encm', criada na funcao main.

ERROS: NENHUM.
*/
void N_comando(encomendas new_encm[], int num_encomendas);

/***************************************************************************************/

/*
FUNCAO: 'A_comando'.

OBJETIVO: adicionar um produto a uma encomenda. Se o produto ja existir na encomenda, 
adicionar a nova quantidade a quantidade existente

DESCRICAO: Chamada quando declarado o comando 'N', onde se le os dados obtidos pelo 
standart input sendo guardados em variaveis locais, para verificacao das normas pedidas.


ERROS: No caso de nao existir nenhuma encomenda criada com esse identificador, no caso
de nao existir nenhum produto criado com esse identificador, no caso de nao existir 
stock suficiente desse produto para satisfazer a encomenda e  no caso de a adicao 
desse produto exceder o peso maximo permitido por encomenda escreve uma mensagem de erro.
*/
void A_comando(encomendas new_encm[], product prod[]);

/***************************************************************************************/

/*
FUNCAO: 'r_comando'.

OBJETIVO: Remover stock a um produto existente.

DESCRICAO: Chamada quando declarado o comando 'r', onde se cria duas variaveis locais 
para guardar os valores lidos pelo input.

ERROS: No caso de nao existir nenhum produto criado com esse identificador e no caso de 
nao existir nenhum produto criado com esse identificador escreve uma mensagem de erro.
*/
void r_comando(product prod[]);

/***************************************************************************************/

/*
FUNCAO: 'R_comando'.

OBJETIVO: Remover um produto de uma encomenda.

DESCRICAO: Chamada quando declarado o comando 'R', onde se cria duas variaveis locais
para guardar os valores lidos pelo input. 

ERROS: No caso de nao existir nenhuma encomenda criada com esse identificador e no caso 
de nao existir nenhum produto criado com esse identificador escreve uma mensagem de erro.
*/
void R_comando(product prod[], encomendas new_encm[]);

/***************************************************************************************/

/*
FUNCAO: 'C_comando'.

OBJETIVO: Calcular o custo de uma encomenda.

DESCRICAO: Chamada quando declarado o comando 'C', onde se cria uma variavel local
para guardar o valor lido pelo input e calcular o custo de cada produto da encomenda
e fazer o total.

ERROS: No caso de nao existir nenhuma encomenda criada com esse identificador escreve
uma mensagem de erro.
*/
void C_comando(product prod[], encomendas new_encm[], int idp);

/***************************************************************************************/

/*
FUNCAO: 'p_comando'.

OBJETIVO: Alterar o preco de um produto existente no sistema.

DESCRICAO: Chamada quando declarado o comando 'p', onde se cria duas variaveis locais
para guardar os valores lidos pelo input.

ERROS: No caso de nao existir nenhum produto criado com esse identificador escreve
uma mensagem de erro.
*/
void p_comando(product prod[]);

/***************************************************************************************/

/*
FUNCAO: 'E_comando'.

OBJETIVO: Listar a descricao e a quantidade de um produto numa encomenda.

DESCRICAO: Chamada quando declarado o comando 'E', onde se cria duas variaveis locais
para guardar os valores lidos pelo input, e declarar a qunatidade desse produto.

ERROS: No caso de nao existir nenhuma encomenda criada com esse identificador e no caso 
de nao existir nenhum produto criado com esse identificador escreve uama mensagem de erro.
*/
void E_comando(product prod[], encomendas new_encm[]);

/***************************************************************************************/

/*
FUNCAO: 'm_comando'.

OBJETIVO: Listar o identificador da encomenda em que o produto dado ocorre mais vezes. 
Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda de menor id.

DESCRICAO: Chamada quando declarado o comando 'm', onde se cria uma variavel local
para guardar o valor lido pelo input e averiguar a condicao pedida num ciclo for. Nao 
lista nada caso o produto nao ocorra em nenhuma encomenda, ou caso nao haja encomendas

ERROS: No caso de nao existir nenhum produto criado com esse identificador escreve uma 
mensagem de erro.
*/
void m_comando(product prod[], encomendas new_encm[], int num_encomendas);

/***************************************************************************************/

/*
FUNCAO: 'l_comando'.

OBJETIVO: Listar todos os produtos existentes no sistema por ordem crescente de preco. 
Se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem 
crescente de id de produto.

DESCRICAO: Chamada quando declarado o comando 'l', onde vai atraves de um algortimo 
de ordenacao estavel, Merge Sort, ordenar os produtos pela ordem pedida.

ERROS: NENHUM.
*/
void l_comando(product prod[], int l, int idp);

/***************************************************************************************/

/*
FUNCAO: 'L_comando'.

OBJETIVO: Listar todos os produtos de uma encomenda por ordem alfabetica da descricao.

DESCRICAO: Chamada quando declarado o comando 'L', onde vai criar uma variavel local
para guardar o valor lido pelo input e listar o pedido.

ERROS: No caso de nao existir nenhuma encomenda criada com esse identificador escreve
uma mensagem de erro.
*/
void L_comando(encomendas new_encm[], product prod[], int idp);

/***************************************************************************************/

/* Definir FUNCOES AUXILIARES utilizadas ao longo do programa

FUNCAO: 'inicializa_enc'.

OBJETIVO: Inicializar a estrutura encomenda criada na main, com valores 0 e -1.

DESCRICAO: Chamada na main, para atribuir os valores 0 e -1 as variadas variaveis criadas
na estrutura, colocando a -1 o ide de cada encomenda e o idp de cada produto, e a 0 os 
restantes.
*/
void inicializa_enc(encomendas enc[]);

/***************************************************************************************/

/*
FUNCAO: 'inicializa_prod'.

OBJETIVO: Inicializar a estrutura produto criada na main, com valores 0 e -1.

DESCRICAO: Chamada na main, para atribuir os valores 0 e -1 as variadas variaveis criadas
na estrutura, colocando a -1 o idp de cada produto, e a 0 as restantes variaveis.
*/
void inicializa_prod(product prodt[]);

/***************************************************************************************/

/*
FUNCAO: 'verifica_prod'.

OBJETIVO: Verificar a condicao de ser um produto existente no sistema.

DESCRICAO: Chamada por varias funcoes auxiliares da main, de modo a verificar a condicao
de o produto indicado existir ou nao no sistema. Retorna 1 no caso verdadeiro.
*/
int verifica_prod(product prodct[], int idp);

/***************************************************************************************/

/*
FUNCAO: 'verifica_enc'.

OBJETIVO: Verificar a condicao sobre a existencia da encomenda referida.

DESCRICAO: Chamada por varias funcoes auxiliares da main, de modo a verificar a condicao
da existencia ou nao existencia da encomenda dada. Retorna 1 no caso verdadeiro.
*/
int verifica_enc(encomendas enc[], int ide);

/***************************************************************************************/

/*
FUNCAO: 'copia_produto'.

OBJETIVO: Criar um backup da estrutura produto.

DESCRICAO: Chamada pelas funcoes auxiliares 'l_comando', 'L_comando', e 'merge', de modo a
copiar para uma nova estrutura, a estrutura produto pedida, para realizar mudancas na copia
sem afetar a original.
*/
product copia_produto(product prod_or);

/***************************************************************************************/

/*
FUNCAO: 'mergeSort'.

OBJETIVO: Baseando-se no algoritmo de ordenacao Merge Sort, vai criar limites para a
ordenacao de cada parte da lista que queremos.

DESCRICAO: Chamada pela funcao auxiliar 'l_comando', e vai criar limites a esquerda e 
a direita, e chamar a funcao merge para ordenar cada pedaco da lista, segundos os limites.
*/
void mergeSort(product ordem[], int l, int r);

/***************************************************************************************/

/*
FUNCAO: 'merge'.

OBJETIVO: Ordenar a lista dada.

DESCRICAO: Vai ordenar as varias listas dadas pela funcao 'mergeSort', criando primeiro
backups para guardar ambos os lados do pivot m.
*/
void merge(product ordem[], int l, int m, int r);
/***************************************************************************************/
