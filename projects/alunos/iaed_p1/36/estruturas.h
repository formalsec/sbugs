#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_INPUT_SIZE 1000
#define MAX_PROD 10000
#define MAX_SIZE 64
#define MAX_PESO 200
#define MAX_ENC 500



typedef struct produto{
  int id;
  char descricao[MAX_SIZE];
  int preco;
  int peso;
  int qtd;
  int encomendado;
  struct node* head;

}produto;

typedef struct encomenda{
  struct node * head;
  int id;
  int peso;
}encomenda;


#endif /* FS_H */
