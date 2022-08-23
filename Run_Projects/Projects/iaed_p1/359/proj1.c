#include <stdio.h>
#include <string.h>
#define MAXIDP 10000       /*nr maximo de produtos*/
#define DESCRICAO 63      /*nr maximo de caracteres da descricao do produto*/
#define MAXPESO 200       /*nr maximo de produtos numa encomenda*/
#define MAXENCOMENDAS 500 /*nrmaximoencomendas*/

typedef struct Produto{
  long int idp;
  char desc[DESCRICAO];
  int preco, peso, qtd;
}produto;

typedef struct Encomenda{
  int ide, peso;
  produto lista[MAXPESO];
}encomenda;

produto sistemaprod[MAXIDP];                                                    /*iniciar sistema dos produtos*/
encomenda sistemaenc[MAXENCOMENDAS];                                            /*iniciar sistema das encomendas*/
produto aux[MAXIDP];                                                            /*estrutura para ordenar*/
encomenda auxenc[MAXENCOMENDAS];                                                /*estrutura para ordenar*/

void inicializa(){
  /*inicializa as arrays*/
  int i;
  for (i=0; i<MAXENCOMENDAS; i++){                                              /*inicia o sistema das encomedas*/
    sistemaenc[i].ide=-1;
  }
  for (i=0; i<MAXIDP; i++){                                                     /*inicia o sistema dos produtos*/
    sistemaprod[i].preco=-1;
    sistemaprod[i].idp=-1;
  }

}

produto novoprod(int contador){
  /*novo produto*/
  produto novo;
  novo.idp=contador;
  scanf(" %63[^:]:%d:%d:%d", novo.desc, &novo.preco, &novo.peso, &novo.qtd);
  printf("Novo produto %d.\n", contador);
  return novo;
}



encomenda novaencomenda(int contador){
  /*cria uma encomenda nova*/
  int i;
  encomenda novo;
  novo.ide=contador;
  novo.peso=0;
  for (i=0; i<MAXPESO; i++){                                                    /*inicializa a encomenda com cada produto com valores plausiveis*/
    novo.lista[i].idp=-1;
    novo.lista[i].preco=-1;
    novo.lista[i].qtd=0;
    novo.lista[i].peso=0;
  }
  printf("Nova encomenda %d.\n", contador);
  return novo;
}


void adicionastock(){
  /*adiciona stock ao produto*/
  int i,id, qtd;
  scanf("%d:%d", &id, &qtd);
  for (i=0; i<MAXIDP; i++){
    if (sistemaprod[i].idp==id){
      sistemaprod[i].qtd+=qtd;      /*adicina o porduto ao stock*/
      return;
    }
  }
  printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
}


int verificaaux(int ide, int idp, char operacao[]){
  /*funcao auxiliar retorna 1 se existe encomenda e produto*/
  int i, estado=0;                                                              /*estado a 1 se encontra encomenda*/
  for (i=0; i<MAXENCOMENDAS; i++){
    if (sistemaenc[i].ide>=0){
      if (sistemaenc[i].ide==ide){
        estado=1;
        break;                                                                  /*ja encontrou a encomenda logo nao precisa de completar o for */
      }
    }
    else break;
  }
  if (estado){                                                                  /* ja encontrou encomenda vai procurar o produto*/
    for (i=0; i<MAXIDP; i++){
      if (sistemaprod[i].preco>=0){
        if (sistemaprod[i].idp==idp){
          return 1;                                                             /*encontrou produto e encoemnda retorna 1*/
        }
      }
      else break;
    }
    if (strcmp(operacao, "listar")!=0){
      printf("Impossivel %s produto %d a encomenda %d. Produto inexistente.\n", operacao, idp, ide);
    }
    else{
      printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
  }
  else{
    if (strcmp(operacao, "listar")!=0){
      printf("Impossivel %s produto %d a encomenda %d. Encomenda inexistente.\n", operacao, idp, ide);
    }
    else{
      printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
  }
  return 0;

}

int adicionaprod_aux(int ide, int idp, int qtd){
  /*funcao auxiliar que retorna 1 se nao originou erros*/
  int i, r;
  for (i=0; i<MAXIDP; i++){
    if (sistemaprod[i].idp>=0){
      if (sistemaprod[i].idp==idp){
        if (sistemaprod[i].qtd<qtd){                                            /* se qtd no sistema for menor que a quantidade pretendida nao ha qtd suf*/
          printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          return 0;
        }
        for (r=0; r<MAXENCOMENDAS; r++){
          if (sistemaenc[r].ide>=0){
            if (sistemaenc[r].ide==ide){
              if ((sistemaenc[r].peso+(sistemaprod[i].peso*qtd))>MAXPESO){      /*ao adicionar o prod a encomenda nao pode exceder 200 peso*/
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                return 0;
              }
            }
          }
          else break;
        }
      }
    }
    else{
      break;
    }
  }
  return 1;
}

void adicionaprod(){
  /*adiciona produtos a encomenda*/
  int i, r, idp, ide, indaux, indaux_enc, qtd;
  produto aux;
  scanf("%d:%d:%d", &ide, &idp, &qtd);
  if (verificaaux(ide, idp, "adicionar")){                                      /*verifica que ha produto e encomenda*/
    if (adicionaprod_aux(ide, idp, qtd)){                                       /*verifica que ha quantidade suficiente e nao passa o limite de peso*/
      for (i=0; i<MAXIDP; i++){
        if (sistemaprod[i].idp==idp){
          indaux=i;                                                             /*indice do produto no sistema*/
          break;
        }
      }
      for (i=0; i<MAXENCOMENDAS; i++){
        if (sistemaenc[i].ide==ide){
          for (r=0; r<MAXPESO; r++){
            if (sistemaenc[i].lista[r].idp==idp){
              sistemaenc[i].lista[r].qtd+=qtd;                                  /*aumenta a quantidade do produto na encomenda*/
              sistemaprod[indaux].qtd-=qtd;                                     /*diminui a qtd disponivel do produto no sistema*/
              sistemaenc[i].peso+=sistemaprod[indaux].peso*qtd;                 /*atualiza peso da encomenda com o produto adicionado*/
              return;
            }
          }
          for (r=0; r<MAXPESO; r++){                                          /*nao encontrou o produto na encomenda*/
            if (sistemaenc[i].lista[r].qtd==0){
              indaux_enc=r;                                                   /*indice onde vai adicionar o produto*/
              break;
            }
          }
          aux=sistemaprod[indaux];                                            /*auxiliar fica com caracteristicas do produto*/
          aux.qtd=qtd;                                                        /*atualizo a quantidade ao auxiliar*/
          sistemaenc[i].lista[indaux_enc]=aux;                                /*adiciono produto a encomenda*/
          sistemaprod[indaux].qtd-=qtd;                                       /*diminuo qtd disponivel do produto na encomenda*/
          sistemaenc[i].peso+=aux.peso*aux.qtd;                               /*atualiza peso da encomenda com o produto adicionado*/
          return;
        }
      }
    }
  }
}



void removestock(){
  /*remove stock a um certo produto*/
  int i, idp, qtd;
  scanf("%d:%d", &idp, &qtd);
  for (i=0; i<MAXIDP; i++){
    if (sistemaprod[i].idp>=0){
      if (sistemaprod[i].idp==idp){
        if (sistemaprod[i].qtd>=qtd){
          sistemaprod[i].qtd-=qtd;                                              /*remove qtd disponivel do produto no sistema*/
          return;
        }
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
      }
    }
    else break;
  }
  printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

void removeprodencomenda(){
  /*remove o produto da encomenda*/
  int i, r, ide, idp, indaux;
  scanf("%d:%d", &ide, &idp);
  if (verificaaux(ide, idp, "remover")){                                        /*verifica que ha encomenda e produto*/
    for (i=0; i<MAXIDP; i++){
      if (sistemaprod[i].idp>=0){
        if (sistemaprod[i].idp==idp){
          indaux=i;                                                             /*indice do prod no sistema*/
          break;
        }
      }
      else break;
    }
    for (r=0; r<MAXENCOMENDAS; r++){
      if (sistemaenc[r].ide>=0){
        if (sistemaenc[r].ide==ide){
          for (i=0; i<MAXPESO; i++){
            if (sistemaenc[r].lista[i].idp>=0){
              if (sistemaenc[r].lista[i].idp==idp){
                sistemaenc[r].peso-=(sistemaenc[r].lista[i].qtd*sistemaprod[indaux].peso);  /*atualizo o peso da encomenda*/
                sistemaprod[indaux].qtd+=sistemaenc[r].lista[i].qtd;            /*adiciono a qtd removida ao stock do produto*/
                sistemaenc[r].lista[i].qtd=0;                                   /*qtd do produto na encomenda fica a 0*/
                return;
              }
            }
            else break;
          }
        }
      }
      else break;
    }
  }
}

void custoencomenda(){
  /*calcula o custo da encomenda*/
  int i, r, ide, custo=0;
  scanf("%d", &ide);
  for (i=0; i<MAXENCOMENDAS; i++){
    if (sistemaenc[i].ide>=0){
      if (sistemaenc[i].ide==ide){
        for (r=0; r<MAXPESO; r++){
          if (sistemaenc[i].lista[r].preco>0){                                  /*sempre que houver produto adicionado logo preco maior que 0 adiciona ao custo*/
            custo+=sistemaenc[i].lista[r].qtd*sistemaenc[i].lista[r].preco;
          }
          else break;
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
        return;
      }
    }
    else break;
  }
  printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

void alterapreco(){
  /*altera o preco de um produto existente no sistema*/
  int idp, preco, i, r, estado=1;                                               /*estado a 0 se existe produto*/
  scanf("%d:%d", &idp, &preco);
  for (i=0; i<MAXIDP; i++){
    if (sistemaprod[i].preco>0){
      if (sistemaprod[i].idp==idp){
        estado=0;
        sistemaprod[i].preco=preco;                                             /*altera o preco do produto no sistema*/
      }
    }
    else break;
  }
  if (estado){
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
  }
  else{
    for (i=0; i<MAXENCOMENDAS; i++){
      if (sistemaenc[i].ide>=0){
        for (r=0; r<MAXPESO; r++){
          if (sistemaenc[i].lista[r].idp>=0){
            if (sistemaenc[i].lista[r].idp==idp){                               /*altera o preco do produto em todas as encomendas que ele se encontra*/
              sistemaenc[i].lista[r].preco=preco;
            }
          }
          else break;
        }
      }
      else break;
    }
  }

}

void prodsencomenda(){
  /*printa descricao e qtd do produto numa encomenda*/
  int i, r, idp, ide;
  scanf("%d:%d", &ide, &idp);
  if (verificaaux(ide, idp, "listar")){                                         /*verifica que ha produto e encomenda*/
    for (r=0; r<MAXENCOMENDAS; r++){
      if (sistemaenc[r].ide>=0){
        if (sistemaenc[r].ide==ide){
          for (i=0; i<MAXPESO; i++){
            if (sistemaenc[r].lista[i].idp>=0){
              if (sistemaenc[r].lista[i].idp==idp){
                printf("%s %d.\n", sistemaenc[r].lista[i].desc, sistemaenc[r].lista[i].qtd);
                return;
              }
            }
            else break;
          }
        }
      }
      else break;
    }
    for (i=0; i<MAXIDP; i++){
      if (sistemaprod[i].idp>=0){
        if (sistemaprod[i].idp==idp){
          printf("%s 0.\n", sistemaprod[i].desc);                               /*se o produto nao existe na encomenda ha 0 de qtd nessa encomenda*/
          return;
        }
      }
      else break;
    }
  }
}

void nrprodmax(){
  /*lista a encomenda em que certo produto ocorre mais vezes*/
  int max=0, maxide,i, r, idp, estado=0;                                        /*estado a 1 se existe produto*/
  scanf("%d", &idp);
  for (i=0; i<MAXIDP; i++){
    if (sistemaprod[i].idp>=0){
      if (sistemaprod[i].idp==idp){
        estado=1;                                                               /*encontrou o produto*/
        break;
      }
    }
    else break;
  }
  if (estado){
    for (i=0; i<MAXENCOMENDAS; i++){
      if (sistemaenc[i].ide>=0){
        for (r=0; r<MAXPESO; r++){
          if (sistemaenc[i].lista[r].qtd>=0){
            if (sistemaenc[i].lista[r].idp==idp && sistemaenc[i].lista[r].qtd>max){
                max=sistemaenc[i].lista[r].qtd;                                 /*atualiza o max*/
                maxide=i;                                                       /*indice do max*/
                break;                                                          /*se o produto ja foi encontrado nesta encomenda ja nao existe mais produtos iguais na mesma encomenda*/
              }
            }
          else break;
        }
      }
      else break;
    }
  }
  if (estado==0){
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  else if (max>0){
    printf("Maximo produto %d %d %d.\n", idp, maxide, max);
  }
}

void mergeprods(int l, int m, int r){
  /*funcao auxiliar da funcao ordena_prod*/
  int i, j, k;
  for (i=m+1; i>l; i--){                                                        /*constroi vetor auxiliar*/
    aux[i-1]=sistemaprod[i-1];
  }
  for (j=m; j<r; j++){                                                          /*constroi vetor auxiliar*/
    aux[r+m-j]=sistemaprod[j+1];
  }
  for (k=l; k<=r; k++){                                                         /*vai escolhendo elementos para ordenar o vetor*/
    if (aux[j].preco<aux[i].preco){
      sistemaprod[k]=aux[j--];
    }
    else if ((aux[j].preco==aux[i].preco) && (aux[j].idp<aux[i].idp)){;
      sistemaprod[k]=aux[j--];
    }
    else{
      sistemaprod[k]=aux[i++];
    }
  }
}

void ordena_prod(int l, int r){
  /*ordena produtos do stock por ordem de preco*/
  /*merge sort*/
  int m=(r+l)/2;
  if (r<=l) return;
  ordena_prod(l, m);                                                            /*recursiva*/
  ordena_prod(m+1, r);                                                          /*recursiva*/
  mergeprods(l, m, r);                                                          /*merge*/
}


void todosprod(){
  /*lista todos os produtos*/
  int i, r=MAXIDP-1;                                                            /*se o r nao mudar entao o sistema esta cheio*/
  for (i=0; i<MAXIDP; i++){
    if (sistemaprod[i].idp==-1){
      r=i-1;                                                                    /*indice do ultimo produto*/
      break;
    }
  }
  ordena_prod(0, r);
  printf("Produtos\n");
  for (i=0; i<=r; i++){
    printf("* %s %d %d\n", sistemaprod[i].desc, sistemaprod[i].preco, sistemaprod[i].qtd);
  }
}



void merge_enc(int ide, int l, int m, int r){
  /*funcao auxailiar da ordena encomenda*/
  int i, j, k;
  for (i=m+1; i>l; i--){                                                        /*constroi vetor auxiliar*/
    auxenc[ide].lista[i-1]=sistemaenc[ide].lista[i-1];
  }
  for (j=m; j<r; j++){                                                          /*constroi vetor auxiliar*/
    auxenc[ide].lista[r+m-j]=sistemaenc[ide].lista[j+1];
  }
  for (k=l; k<=r; k++){                                                         /*vai escolhendo elementos para ordenar o vetor*/
    if (strcmp(auxenc[ide].lista[j].desc, auxenc[ide].lista[i].desc)<0){
      sistemaenc[ide].lista[k]=auxenc[ide].lista[j--];
    }
    else{
      sistemaenc[ide].lista[k]=auxenc[ide].lista[i++];
    }
  }
}

void ordena_encomenda(int ide, int l, int r){
  /*ordena os produtos de uma encomenda por ordem alfabetica. funcao auxiliar da tdsprosencomenda*/
  /*merge sort*/
  int m=(r+l)/2;
  if (r<=l) return;
  ordena_encomenda(ide, l, m);                                                  /*recursiva*/
  ordena_encomenda(ide, m+1, r);                                                /*recursiva*/
  merge_enc(ide, l, m, r);                                                      /*merge*/
}


void tdsprosencomenda(){
  /*lista todos os produtos de uma encomenda*/
  int i, r=MAXPESO-1, ide;                                                      /*se nao mudar o r, a encomenda esta cheia*/
  scanf("%d", &ide);
  for (i=0; i<MAXPESO; i++){
    if (sistemaenc[ide].lista[i].idp==-1){
      r=i-1;                                                                    /*indice do ultimo porduto na encomenda*/
      break;
    }
  }
  ordena_encomenda(ide, 0, r);
  for (i=0; i<MAXENCOMENDAS; i++){
    if (sistemaenc[i].ide==ide){
      printf("Encomenda %d\n", ide);
      for (r=0; r<MAXPESO; r++){
        if (sistemaenc[i].lista[r].qtd>0){
          printf("* %s %d %d\n", sistemaenc[i].lista[r].desc, sistemaenc[i].lista[r].preco, sistemaenc[i].lista[r].qtd);
        }
      }
      return;                                                                   /*se ja encontrou a encomenda nao precisa de continuar no for*/
    }
  }
  printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

int main(){
  int in, nrprod=0, nrenc=0;                                                    /*nrprod nrenc sao o numero de produtos e encomendas respetivamente*/
  inicializa();
  while ((in=getchar())!='x'){
    switch(in){
      case ('a'):
        sistemaprod[nrprod]=novoprod(nrprod);
        nrprod++;
        break;
      case ('q'):
        adicionastock();
        break;
      case ('N'):
        sistemaenc[nrenc]=novaencomenda(nrenc);
        nrenc++;
        break;
      case ('A'):
        adicionaprod();
        break;
      case ('r'):
        removestock();
        break;
      case ('R'):
        removeprodencomenda();
        break;
      case ('C'):
        custoencomenda();
        break;
      case ('p'):
        alterapreco();
        break;
      case ('E'):
        prodsencomenda();
        break;
      case ('m'):
        nrprodmax();
        break;
      case ('l'):
        todosprod();
        break;
      case ('L'):
        tdsprosencomenda();
        break;
    }
  }
  return 0;
}
