/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct produto
{
  char descricao[64];
  int preco;
  int peso;
  int stock;
  int flag;
} Produto;
typedef struct encomenda
{
  int peso;
  int contaProdEnc;
  int quantidade[10000];
  int flag;
  Produto produtosEncomendas[10000];
} Encomenda;
Produto produtos[10000];
Encomenda encomendas[500];
int contaProdutos = 0;
int contaEncomendas = 0;
void comando_a(char arg[]);
int comando_q(char arg[]);
void comando_N();
int comando_A(char arg[]);
int comando_r(char arg[]);
int comando_R(char arg[]);
int comando_C(char arg[]);
int comando_p(char arg[]);
int comando_E(char arg[]);
int comando_m(char arg[]);
void comando_l();
int comando_L(char arg[]);
void merge(Produto a[], int i1, int j1, int i2, int j2, int f);
void mergeSort(Produto a[], int i, int j, int f);
void separaInput(char arg[100], char res[][100]);
void removeEspaco(char *str);
