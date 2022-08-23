#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Charl 65                  /*63+\0 caracteres*/
#define P_max 200                 /*Peso maximo por encomenda*/
#define Pr_max 10000              /*N? maximo de produtos*/
#define E_max 500                 /*N? maximo de encomendas*/
#define In_max 90                 /*Nao creio que o input ultrapasse 90 caracteres*/

struct Produto {                  /*Produtos no sistema*/
  int idp;
  char desc [Charl];
  int preco;
  int peso;
  int stock;
};
struct Pr{                        /*struct para fazer ordenacao por preco*/
  char desc [Charl];
  int preco;
  int stock;
};
struct EProd{                     /*Produtos na encomenda*/
  int idp;
  char desc [Charl];
  int preco;
  int stock;
};
struct Encomenda{
  int ide;
  int Npe;                        /*N? de produtos por encomenda*/
  int Tpeso;
  int Tpreco;
  struct EProd EProd [Pr_max+1];
};

int main(void) {

  void quicksortp(struct Pr Pr[Pr_max+1], int l, int r);
  void alphasort(struct EProd EProd[Pr_max+1], int l, int r);

  int Np, idin, Ne, idein, qtd, Maxpe, Maxe;  /*n? de produtos no sistema, id input, n? de encomendas, id encomenda input,
                                              stock maximo da encomenda, encomenda com stock maximo*/
  int i, j;
  char c, c1;
  const char q[2] = ":";
  char *token;
  char input[In_max];

  struct Produto Produto [Pr_max+1];
  struct Pr Pr [Pr_max+1];                /*+1 para as ordena??o*/
  struct Encomenda Encomenda [E_max+1];

  while ((c=getchar())!='x'){
    c1= getchar();
    scanf("%s", input);

    if (c=='a'){                          /*Adicionar produto ao sistema*/
      if(Np < Pr_max){
        Produto[Np].idp = Np;
        token = strtok(input,q);
        strcpy(Produto[Np].desc, token);
        Produto[Np].desc[Charl-1] = '\0';
        token = strtok(NULL, q);
        Produto[Np].preco = atoi(token);
        token = strtok(NULL, q);
        Produto[Np].peso = atoi(token);
        token = strtok(NULL, q);
        Produto[Np].stock = atoi(token);

        printf("Novo produto %d.\n", Produto[Np].idp);

        Np=Np+1;
      }
    }

    else if (c=='q'){                      /*Adicionar stock ao produto*/
      token = strtok(input,q);
      idin = atoi(token);
      token = strtok(NULL, q);
      qtd = atoi(token);

      if(idin < Np){
        Produto[idin].stock = Produto[idin].stock + qtd;
      }
      else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idin);
      }
    }

    else if (c=='N'){                      /*Adicionar nova encomenda*/
      if(Ne < E_max){
        printf("Nova encomenda %d.\n", Ne);
        Ne++;
      }
    }

    else if (c=='A'){                      /*Adicionar produto ou stock a um produto numa encomenda*/
      token = strtok(input,q);
      idein = atoi(token);
      token = strtok(NULL, q);
      idin = atoi(token);
      token = strtok(NULL, q);
      qtd = atoi(token);

      if (idein < Ne){
        if(idin < Np){
          if(Produto[idin].stock - qtd >= 0){
            if(Encomenda[idein].Tpeso + qtd * Produto[idin].peso <= P_max){
              Encomenda[idein].Tpeso = Encomenda[idein].Tpeso + qtd * Produto[idin].peso;
              for (i=0; i < Encomenda[idein].Npe; i++){
                if(Encomenda[idein].EProd[i].idp == Produto[idin].idp){   /*caso haja um produto igual*/
                  Encomenda[idein].EProd[i].stock = Encomenda[idein].EProd[i].stock + qtd;
                  Produto[idin].stock = Produto[idin].stock - qtd;  /*Remover stock ao produto no sistema*/
                  break;
                }
              }
              if(i==Encomenda[idein].Npe && Encomenda[idein].Npe < Pr_max){        /*caso nao hajam produtos(i=0) ou nao haja nenhum igual(i=Npe)*/
                strcpy(Encomenda[idein].EProd[i].desc,Produto[idin].desc);
                Encomenda[idein].EProd[i].stock = qtd;
                Produto[idin].stock = Produto[idin].stock - qtd;  /*Remover stock ao produto no sistema*/
                Encomenda[idein].EProd[i].preco = Produto[idin].preco;
                Encomenda[idein].EProd[i].idp = Produto[idin].idp;
                Encomenda[idein].Npe++;
              }
            }
            else{
              printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idin, idein);
            }
          }
          else{
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idin, idein);
          }
        }
        else{
          printf("Impossivel adicionar produto %d a encomenda %do.  Produto inexistente.\n", idin, idein);
        }
      }
      else{
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idin, idein);
      }
    }

    else if (c=='r'){                      /*Remover stock ao produto no sistema*/
      token = strtok(input,q);
      idin = atoi(token);
      token = strtok(NULL, q);
      qtd = atoi(token);

      if(idin < Np){
        if(Produto[idin].stock - qtd >= 0){
          Produto[idin].stock = Produto[idin].stock - qtd;
        }
        else{
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idin);
        }
      }
      else{
        printf("Impossivel remover stock do produto %d. Produto inexistente. \n", idin);
      }
    }

    else if (c=='R'){                      /*Remover produto da encomenda (stock 0)*/
      token = strtok(input,q);
      idein = atoi(token);
      token = strtok(NULL,q);
      idin = atoi(token);

      if (idein < Ne){
        for (i=0; i < Encomenda[idein].Npe; i++){
          if(Encomenda[idein].EProd[i].idp == idin){
            Encomenda[idein].Tpeso = Encomenda[idein].Tpeso - Encomenda[idein].EProd[i].stock * Produto[idin].peso;
            Encomenda[idein].EProd[i].stock = 0;    /*produtos com stock 0 sao como se nao existissem na encomenda*/
            break;
          }
        }
        if(i==Encomenda[idein].Npe){              /*caso nao hajam produtos(i=0) ou nao haja nenhum igual(i=Npe)*/
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idin, idein);
        }
      }
      else{
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idin, idein);
      }
    }

    else if (c=='C'){                      /*Calcular custo totad da encomenda*/
      token = strtok(input,q);
      idein = atoi(token);

      if (idein < Ne){
        Encomenda[idein].Tpreco = 0;
        for (i=0; i < Encomenda[idein].Npe; i++){
          Encomenda[idein].Tpreco = Encomenda[idein].Tpreco + Encomenda[idein].EProd[i].stock * Encomenda[idein].EProd[i].preco;
        }
        printf("Custo da encomenda %d %d.\n", idein, Encomenda[idein].Tpreco);
      }
      else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idein);
      }
    }

    else if (c=='p'){                      /*Modificar preco do produto*/
      token = strtok(input,q);
      idin = atoi(token);

      if(idin < Np){
        token = strtok(NULL, q);
        Produto[idin].preco = atoi(token);
      }
      else{
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idin);
      }
    }

    else if (c=='E'){                      /*listar descricao e stock dum produto numa encomenda*/
      token = strtok(input,q);
      idein = atoi(token);

      if (idein < Ne){
        token = strtok(NULL,q);
        idin = atoi(token);
        for (i=0; i < Encomenda[idein].Npe; i++){
          if(Encomenda[idein].EProd[i].idp == idin){
            printf("%s %d\n", Encomenda[idein].EProd[i].desc, Encomenda[idein].EProd[i].stock);
            break;
          }
        }
        if(i==Encomenda[idein].Npe){
          printf("Impossivel listar produto %d. Produto inexistente.\n", idin);
        }
      }
      else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idein);
      }
    }

    else if (c=='m'){                      /*Identificar encomenda com maior stock dum produto*/
      token = strtok(input,q);
      idin = atoi(token);

      if(idin < Np){
        Maxpe = 0;
        for (i=0; i < Ne; i++){
          for (j=0; j < Encomenda[i].Npe; j++){
            if(Encomenda[i].EProd[j].idp == idin){
              if(Encomenda[i].EProd[j].stock > Maxpe){
                Maxpe = Encomenda[i].EProd[j].stock;
                Maxe = i;
              }
            }
          }
        }
        if (Maxpe == 0){
          printf("Impossivel listar produto %d. Produto inexistente.\n", idin);
        }
        else{
          printf("%d %d %d\n", idin, Maxe, Maxpe);
        }
      }
      else{
        printf("Impossivel listar produto %d. Produto inexistente.\n", idin);
      }
    }

    else if (c=='l'){                      /*Listar produtos do sistema por ordem crescente de preco*/
      for(i=0; i < Np; i++){
        Pr[i].preco= Produto[i].preco;
        strcpy(Pr[i].desc, Produto[i].desc);
        Pr[i].stock= Produto[i].stock;
      }

      quicksortp(Pr, 0, Np);

      printf("Produtos\n");
      for(i=0; i < Np; i++){
        printf("* %s %d %d\n",Pr[i].desc, Pr[i].preco, Pr[i].stock);
      }
    }

    else if (c=='L'){                      /*Listar produtos duma encomenda alfabeticamente*/
      token = strtok(input,q);
      idein = atoi(token);

      if (idein < Ne){
        alphasort(Encomenda[idein].EProd, 0, Encomenda[idein].Npe);

        printf("Encomenda %d\n", idein);
        for(i=0; i < Encomenda[idein].Npe; i++){
          if(Encomenda[idein].EProd[i].stock != 0){    /*para nao listar os eliminados em 'R'*/
            printf("* %s %d %d\n",Encomenda[idein].EProd[i].desc, Encomenda[idein].EProd[i].preco, Encomenda[idein].EProd[i].stock);
          }
        }
      }
      else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idein);
      }
    }
  }
  c1 = c1 + 1;
  return 0;
}
