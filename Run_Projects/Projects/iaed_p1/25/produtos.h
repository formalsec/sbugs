#ifndef PRODUTOS_H
#define PRODUTOS_H
/*
Produto e uma estrutura aonde:
  id e um int que representa o identificador
  name e uma string que representa a descripcao
  price e um int que representa o preco
  weight e um int que representa o peso
  stock e um int que representa a quantidade
*/
typedef struct produto{
  int id;
  char *name;
  int price;
  int weight;
  int stock;
}Produto;

Produto createProd(int id,char* name, int price, int weight, int stock);
Produto addStock(Produto p, int num);
Produto removeStock(Produto p,int num);
Produto changePrice(Produto p, int nPrice);
int getProdPrice(Produto p);
int getProdStock(Produto p);
int getProdWeight(Produto p);
void printProd(Produto p);
int getProdID(Produto p);
char *getProdName(Produto p);
void free_prod(Produto p);

#endif
