#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 64
#define MAX_PRODUTO 10000
#define MAX_ENCOMENDA 500
#define MAX_P_ENCOMENDA 200

typedef struct {
  char descricao[MAX_CHAR];
  int idp;
  int preco;
  int peso;
  int stock;
} produto;

typedef struct {
  int ide;
  int peso_total;
  produto produto_e[200];
} encomenda;

/* VARIAVEIS GLOBAIS (para facilitar)*/
produto p[MAX_PRODUTO];
encomenda e[MAX_ENCOMENDA];

/*---------- FUNCOES AUXILIARES ----------------*/

int get_string (char c[]) { /* recebe cadeia de caracteres como argumento, devolve um inteiro*/
  char ch;
  int i = 0;

  while ((ch = getchar ()) != ':' && ch != '\0' && ch != '\n') {
    c[i++] = ch;            /* copia caracter a caracter ate chegar ao fim da string pretendida */
  }
  c[i] = '\0';
  return 0;
}

int get_int () { /* devolve um inteiro correspondente aos numeros da string ate :*/
  char ch;
  int i = 0;

  while ((ch = getchar()) != ':' && ch != '\0' && ch != '\n') {
    i = i * 10 + (ch - '0');
  }
  return i;
}

int existe_produto(int idp) { /* verifica que o produto se encontra na lista de produtos, se sim, retorna o seu indice*/
  int i;

  for(i = 0; i < MAX_PRODUTO; i++) {
    if (p[i].idp == idp) return i;
  }
  return -1;
}

int existe_encomenda(int ide) { /* verifica que a encomenda se encontra na lista de encomenda, se sim, retorna o seu indice*/
  int i;

  for(i = 0; i < MAX_ENCOMENDA; i++) {
    if (e[i].ide == ide) return i;
  }
  return -1;
}

int existe_stock(int qntd, produto p){
  if (p.stock >= qntd) return 1;
  return -1;

}

int encomenda_tem_produto(encomenda e, int idp) {
  int i;

  for (i=0; i < 200; i++) {
    if (e.produto_e[i].idp == idp) return i;
  }
  return -1;
}

int ultrapassa_peso(encomenda e, produto p, int qtd) {
  int peso_inicial;

  peso_inicial = e.peso_total;
  if ((peso_inicial + p.peso * qtd) > MAX_P_ENCOMENDA) return -1;
  return 1;
}

int compara_precos(produto p1, produto p2) { /* retorna 1 se o preco do primeiro produto for superior ao do segundo*/
  if (p1.preco > p2.preco) return 1;
  else if (p1.preco == p2.preco) {
    if (p1.idp > p2.idp) return 1; /* caso o preco seja igual, retorna 1 se o id do primeiro produto for superior ao do segundo*/
    else return 0;
  }
  else return 0;
}

void ordena_preco(){
  produto aux;
  int troca = 2, k;
  while (troca != 0) {
    troca = 0;
    for (k = 1; k < 1000; k++) {
      if (p[k].stock == -1) break;  /* bubble sort para ordenar por preco*/
      if (compara_precos (p[k-1], p[k]) == 1) {
        aux = p[k-1];
        p[k-1] = p[k];
        p[k] = aux;
        troca = 1;
      }
    }
  }
}

int compara_alfa( char c1[], char c2[]) {
  int i;
  for (i=0; i< MAX_CHAR; i++) {
    int x = c1[i];
    int y = c2[i];
    if (c1[i] == ' ') return 0;
    else if (c2[i] == ' ') return 1;
    else if (x > y) return 1;
    else if (x < y) return 0;
  }
  return 0;
}

void ordena_alfa(int ide) {
  int troca = 2, k;
  produto aux;
  while (troca != 0) {
    troca = 0;
    for (k = 1; k < 200; k++) {
      if (e[ide].produto_e[k].idp == -1) {troca = 0;}
      if (compara_alfa (e[ide].produto_e[k-1].descricao, e[ide].produto_e[k].descricao) == 1) {
        aux = e[ide].produto_e[k-1];
        e[ide].produto_e[k-1] = e[ide].produto_e[k];
        e[ide].produto_e[k] = aux;
        troca = 1;
      }
    }
  }
}

/*-------- COMANDOS -------*/

void adiciona_produto (int idp) { /* comando a*/
  produto p1;
  int i;

  get_string(p1.descricao);
  p1.preco = get_int();
  p1.peso = get_int();
  p1.stock = get_int();
  p1.idp = idp;

  for (i=0; i<MAX_PRODUTO; i++) {
    if (p[i].stock == -1) {
      p[i] = p1;
      printf("%s %d%s\n", "Novo produto", p1.idp, ".");
      break;
    }
  }
}

void adiciona_stock() { /* comando q */
  int id, qtd, numero_produto;
  id = get_int();
  qtd = get_int();

  numero_produto = existe_produto(id);
  if (numero_produto == -1) {
    printf("%s %d %s\n", "Impossivel adicionar produto", id,"ao stock. Produto inexistente.");
    return;
  }
  else {
    p[numero_produto].stock = p[numero_produto].stock + qtd;
  }
}

void remove_stock() { /* comando r meio atabalhoado mas acho que funciona bem*/
  int idp, qtd, numero_produto;
  numero_produto = 0;
  idp = get_int();
  qtd = get_int();
  numero_produto = existe_produto(idp);
  if (numero_produto == -1) {
    printf("%s %d%s\n", "Impossivel remover stock do produto", idp,". Produto inexistente.");
    return;
  }
  if (existe_stock(qtd, p[idp]) == -1) {
      printf("%s %d %s %d %s\n", "Impossivel remover", qtd ,"unidades do produto", idp,"do stock. Quantidade insuficiente.");
      return;
    }
  p[idp].stock = p[idp].stock - qtd;
}

void altera_preco() { /* comando p */
   int idp, preco, j, i;
   idp = get_int();
   preco = get_int();

   if (existe_produto(idp) == -1) {
     printf("%s %d%s\n", "Impossivel alterar preco do produto", idp,". Produto inexistente.");
     return;
   }
   p[idp].preco = preco;
   for(i = 0; i < MAX_ENCOMENDA; i++){
     if(e[i].ide == -1){
       break;
     }
     for(j = 0; j < MAX_P_ENCOMENDA; j++){


       if(e[i].produto_e[j].idp == idp) e[i].produto_e[j].preco = preco;
     }
   }
}

void lista_produtos_preco() { /* comando l, usa auxiliar l? de cima para ordenar */
  int i;
  ordena_preco(p);
  printf("Produtos\n");
  for(i=0; i<MAX_PRODUTO; i++) {
    if (p[i].stock == -1) break;
    else {
      printf("%s %s %d %d\n", "*", p[i].descricao, p[i].preco, p[i].stock);
    }
  }
}

void nova_encomenda(int ide) { /* comando N */
  int j;
  e[ide].ide = ide;
  for (j = 0; j < MAX_P_ENCOMENDA; j++){
        e[ide].produto_e[j].idp = -1;
  }
  printf("%s %d%s\n", "Nova encomenda", ide, ".");
}

void adiciona_produto_encomenda() { /* comando A, uma das minha suspeitas de segmentation fault, n?o consegui corrigir */
  int ide, idp, qntd, aux, i;
  ide = get_int();
  idp = get_int();
  qntd = get_int();

  if ((existe_encomenda(ide) == -1)) {
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idp, "a encomenda", ide, ". Encomenda inexistente.");  /*erro nao existe encomenda */
    return;
  }
  if (existe_produto(idp) == -1){
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idp, "a encomenda", ide, ". Produto inexistente."); /*erro nao existe produto */
    return;
  }
  if (existe_stock(qntd, p[idp]) == -1){
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idp, "a encomenda", ide, ". Quantidade em stock insuficiente."); /*erro nao existe stock */
    return;
  }
  if (ultrapassa_peso(e[ide], p[idp], qntd) == -1){
    printf("%s %d %s %d%s\n", "Impossivel adicionar produto", idp, "a encomenda", ide, ". Peso da encomenda excede o maximo de 200."); /*erro ultrapassa peso*/
    return;
  }
  /* adicionar produto: dois casos: um em que se j? h? produto e adiciona-se mais, ou em que nao h? ainda */
  aux = encomenda_tem_produto(e[ide],idp);
  if (aux != -1) {
    e[ide].produto_e[aux].stock = e[ide].produto_e[aux].stock + qntd;
    p[idp].stock = p[idp].stock - qntd;
    e[ide].peso_total = e[ide].peso_total + p[idp].peso * qntd;
    return;
  }

  /* segundo caso: adiciona o produto from scratch*/
  for (i = 0; i < MAX_P_ENCOMENDA; i++)
  {
    if(e[ide].produto_e[i].idp == -1)
    {
      e[ide].produto_e[i] = p[idp];
      e[ide].produto_e[i].idp = idp;
      e[ide].produto_e[i].stock = qntd;
      p[idp].stock = p[idp].stock - qntd;
      e[ide].peso_total = e[ide].peso_total + p[idp].peso * qntd;
      return;
    }
  }
}

void remove_produto_encomenda() { /* comando R, outra suspeita de segmentation fault mas tentei muita coisa e n?o consegui corrigir */
  int ide, idp, i;
  ide = get_int();
  idp = get_int();
  i = encomenda_tem_produto(e[ide],idp);
  if (existe_encomenda(ide) == -1) {
    printf("%s %d %s %d%s\n", "Impossivel remover produto", idp, "a encomenda", ide, ". Encomenda inexistente.");
    return;
  }
  if (existe_produto(idp) == -1){
    printf("%s %d %s %d%s\n", "Impossivel remover produto", idp, "a encomenda", ide, ". Produto inexistente.");
    return;
  }
if (i != -1) {
      p[idp].stock = p[idp].stock + e[ide].produto_e[i].stock;
      e[ide].produto_e[i].idp = -1;
      e[ide].peso_total = e[ide].peso_total - (e[ide].produto_e[i].stock * p[idp].peso);
      e[ide].produto_e[i].stock = 0;
    }
}

void onde_ha_mais() { /* comando m, outro possivel suspeito de segmentation fault.. */
  int idp, i, j, max, id_enco_final;
  idp = get_int();
  max = 0;
  id_enco_final = 0;
  if (existe_produto(idp) == -1 ) {
    printf("%s %d%s\n", "Impossivel listar maximo do produto", idp, ". Produto inexistente.");
    return;
  }
  for (i = 0; i < 500; i++) {
    for (j = 0; j < 200; j++) {
      if (e[i].produto_e[j].idp == idp && e[i].produto_e[j].stock > max){
        max = e[i].produto_e[j].stock;
        id_enco_final = e[i].ide;
        break;
      }
    }
  }

  if (max != 0) printf("%s %d %d %d.\n", "Maximo produto", idp, id_enco_final, max);
}

void lista_desc_qtd_produto_encomenda() { /* comando E */
  int ide, idp, i, aux;
  ide = get_int();
  idp = get_int();
  if (existe_encomenda(ide) == -1) {
    printf("%s %d%s\n", "Impossivel listar encomenda", ide, ". Encomenda inexistente.");
    return;
  }
  if (existe_produto(idp) == -1) {
    printf("%s %d%s\n", "Impossivel listar produto", idp, ". Produto inexistente.");
    return;
  }
    for (i = 0; i < 200; i++) {
      if (e[ide].produto_e[i].idp == idp) aux = i;
    }
    if(e[ide].produto_e[aux].stock == -1) printf("%s 0.\n", p[idp].descricao);
    else printf("%s %d.\n", p[idp].descricao, e[ide].produto_e[aux].stock);
}

void calcula_custo_encomenda() { /* comando C */
  int ide, i, aux, total;
  ide = get_int();
  total = 0;
  aux = 0;
  if ((existe_encomenda(ide) == -1)) {
    printf("%s %d%s\n", "Impossivel calcular custo da encomenda", ide, ". Encomenda inexistente.");
    return;
  }
  for (i = 0; i < 1500; i++) {
    aux = encomenda_tem_produto(e[ide],i);
    if (aux != -1) {
      total = total + (e[ide].produto_e[aux].stock * e[ide].produto_e[aux].preco);
    }
  }
  printf("%s %d% d%s\n", "Custo da encomenda", ide, total, ".");
}

void lista_produtos_alfa() { /* comando L, usa auxiliares l? de cima tamb?m para ordenar alfabeticamente */
  int i = 0, ide;
  ide = get_int();
  if (existe_encomenda(ide) == -1) {
    printf("%s %d%s\n", "Impossivel listar encomenda", ide,". Encomenda inexistente.");
    return;
  }
  ordena_alfa(ide);
  printf("%s %d\n", "Encomenda", ide);
  for(i=0; i< 200; i++) {
    if (e[ide].produto_e[i].preco != 0 && e[ide].produto_e[i].stock != 0 && e[ide].produto_e[i].idp != -1){
    printf("* %s %d %d\n", e[ide].produto_e[i].descricao, e[ide].produto_e[i].preco, e[ide].produto_e[i].stock);
    }
  }
}

int main () {
  int i, idp = 0;
  int ide = 0;
  char comando = 'y';

  /* inicializar as structs */
  produto p0;
  encomenda e0;

  strcpy(p0.descricao, " ");
  p0.idp = -1;
  p0.preco = 0;
  p0.peso = 0;
  p0.stock = -1;

  for (i = 0; i < MAX_PRODUTO; i++) {
    p[i] = p0;
  }

  e0.ide = -1;
  e0.peso_total = 0;
  for (i = 0; i < MAX_P_ENCOMENDA; i++){
    e0.produto_e[i] = p0;
  }

  for (i = 0; i < MAX_ENCOMENDA; i++) {
    e[i] = e0;
  }

  while (comando != 'x') {
    switch ( comando = getchar() ) {

      case 'a':
        getchar();
        adiciona_produto(idp);
        idp++;
        break;
      case 'q':
        getchar();
        adiciona_stock();
        break;
      case 'r':
        getchar();
        remove_stock();
        break;
      case 'p':
        getchar();
        altera_preco();
        break;
      case 'l':
        lista_produtos_preco();
        break;
      case 'L':
        getchar();
        lista_produtos_alfa();
        break;
      case 'N':
        nova_encomenda(ide);
        ide++;
        break;
      case 'A':
        getchar();
        adiciona_produto_encomenda();
        break;
      case 'R':
        getchar();
        remove_produto_encomenda();
        break;
      case 'E':
        getchar();
        lista_desc_qtd_produto_encomenda();
        break;
      case 'C':
        getchar();
        calcula_custo_encomenda();
        break;
      case 'm':
        getchar();
        onde_ha_mais();
        break;
      case 'x':
        break;
    }
  }
  return 0;
}
