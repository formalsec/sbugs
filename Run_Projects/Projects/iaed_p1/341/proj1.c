#include <stdio.h>
#include <string.h>

#define SIM 1                 /*variavel de estado afirmativo*/
#define NAO 0                 /*variavel de estado negativo*/
#define SIZE_DESCR 64         /*tamanho maximo da descricao de cada produto*/
#define SIZE_SYST_PROD 10000  /*numero maximo de produtos*/
#define SIZE_SYST_ENC 500     /*numero maximo de encomendas*/
#define SIZE_ENC 200          /*tamanho maximo de cada encomenda*/

/*estrutura de um produto*/
typedef struct produto{
   char descricao[SIZE_DESCR]; /*descricao*/
   int preco; /*preco*/
   int peso; /*peso*/
   int qtd; /*quantidade*/
   int id; /*identificador*/
}  Produto;

/*estrutura de uma encomenda*/
typedef struct encomenda{
   int peso; /*peso combinado de todos os produtos na encomenda*/
   int preco; /*preco combinado de todos os produtos na encomenda*/
   int cont; /*numero de produtos na encomenda*/
   Produto item[SIZE_ENC]; /*vetor que contem os produtos da encomenda*/
}  Encomenda;

int cont_produto = 0; /*contador de produtos inseridos no sistema*/
int cont_encomenda = 0; /*contador de encomendas inseridas no sistema*/
Produto sistema_produtos[SIZE_SYST_PROD]; /*vetor que contem o stock global (do sistema) de produtos*/
Produto auxiliar[SIZE_SYST_PROD]; /*vetor auxiliar de produtos a ser usado no mergesort invocado pelo comando merge*/
Encomenda sistema_encomendas[SIZE_SYST_ENC]; /*vetor que contem as encomendas todas*/

/*funcao que recebe 2 produtos e avalia se sao o mesmo*/
int mesmosProdutos(Produto p1, Produto p2){
   /*verifica se os identificadores dos produtos sao iguais*/
   if(p1.id == p2.id) return 1;
   return 0;
}

/*funcao que recebe um id e o respetivo contador para verificar se o primeiro e invalido ou nao*/
int eh_id_invalido(int id, int cont){
   /*verifica se o identificador inserido nao e inferior a 0 ou maior que o numero de itens inseridos*/
   if(id >= cont || id < 0) return 1;
   return 0;
}

/*funcao que faz print aos produtos de um certo vetor*/
void print_produtos(int cont, Produto vetor[]){
   int i;
   for(i = 0; i < cont; i++){
      printf("* %s %d %d\n", vetor[i].descricao, vetor[i].preco, vetor[i].qtd);
   }
}

/*funcao que recebe um vetor de produtos e copia para outro*/
void copia(Produto v1[], Produto v2[]){
   int i;
   for(i = 0; i < cont_produto; i++){
      v1[i] = v2[i];
   }
}

/*funcao que troca dois produtos num vetor*/
void troca(Produto vetor[], int i){
   Produto temp; /*variavel temporaria para guardar os produtos*/
   temp = vetor[i+1];
   vetor[i+1] = vetor[i];
   vetor[i] = temp;
   temp = vetor[i];
}

/*funcao merge do mergesort*/
void merge(Produto produtos[], int lim_esq, int meio, int lim_dir){
   int i, j, k;

   /*2 for's iniciais para preencher o vetor auxiliar*/
   for(i = meio + 1; i > lim_esq; i--){
      auxiliar[i-1] = produtos[i-1];
   }
   for(j = meio; j < lim_dir; j++){
      auxiliar[lim_dir+meio-j] = produtos[j+1];
   }

   /*for para gerar um vetor ordenado*/
   for(k = lim_esq; k <= lim_dir; k++){
      /*
      * verifica se o preco do produto na posicao j do vetor auxiliar auxiliar (fim
      * do vetor auxiliar), e superior ao preco do produto da posicao i do vetor
      * (inicio do vetor auxiliar)
      */
      if(auxiliar[j].preco < auxiliar[i].preco){
         produtos[k] = auxiliar[j]; /*se for, insere este na posicao k do vetor produtos*/
         j--; /*decrementa o j pois foi removido um produto da parte direita do vetor auxiliar*/
      }
      /*caso contrario, se o preco de produtos[j] for superior*/
      else if(auxiliar[i].preco < auxiliar[j].preco){
         produtos[k] = auxiliar[i]; /*acrescenta o produto de indice i no vetor final primeiro*/
         i++; /*incrementa o contador da esquerda*/
      }

      /*caso contrario, os precos sao iguais, logo ordena por id*/

      /*verifica se o id de auxiliar[j] eh menor que o de auxiliar[i]*/
      else if(auxiliar[j].id < auxiliar[i].id){
         produtos[k] = auxiliar[j]; /*se for, insere este na posicao k do vetor produtos*/
         j--; /*decrementa o j pois foi removido um produto da parte direita do vetor auxiliar*/
      }
      else{
         produtos[k] = auxiliar[i]; /*acrescenta o produto de indice i no vetor final primeiro*/
         i++; /*incrementa o contador da esquerda*/
      }
   }
}

/*algoritmo de ordenacao mergesort para ordenar produtos num vetor por ordem crescente de preco*/
void mergesort(Produto produtos[], int lim_esq, int lim_dir){
   int meio = (lim_dir + lim_esq) / 2; /*calcula o indice do meio do vetor*/

   /*
   * verifica se o indice da direita eh menor que o da esquerda, se for,
   * termina o processo de divisao do vetor e comeca o merge
   */
   /*caso contrario, divide o vetor de elementos a ordenar*/
   if (!(lim_dir <= lim_esq)){
      mergesort(produtos, lim_esq, meio); /*divide a esquerda*/
      mergesort(produtos, meio + 1, lim_dir); /*divide a direita*/
      merge(produtos, lim_esq, meio, lim_dir); /*merge de volta*/
   }
}


/*
* funcao que recebe um vetor de produtos de uma encomenda
* e o seu tamanho e ordena alfabeticamente estes pelas suas descricoes
*/
void ordena(Produto vetor[], int len){
   int i, ha_troca;
   do{ /*enquanto nao for feita uma troca*/
      ha_troca = NAO; /*faz reset a variavel de estado*/
      /*para cada i no vetor ate ao penultimo item*/
      for(i = 0; i < len - 1; i++){
         /*
         * compara a string de i com a de i+1
         * se o resultado for positivo, quer dizer que a string i deve aparecer
         * mais tarde que a i+1, caso contrario nao ha troca
         */
         if(strcmp(vetor[i].descricao, vetor[i+1].descricao) > 0){
            troca(vetor, i);
            ha_troca = SIM;  /*ativa a flag pois houve uma troca*/
         }
      }
   } while(ha_troca);
}

/*
* funcao corresponedente ao comando 'a'
* - recebe um produto e adiciona-o ao sistema global de stock de produtos
*/
void func_a(Produto produto){
   printf("Novo produto %d.\n", cont_produto);
   produto.id = cont_produto; /*insere o identificador*/
   sistema_produtos[cont_produto] = produto; /*adiciona o produto*/
   cont_produto++; /*incrementa o contador global de produtos*/
}

/*
* funcao correspondente ao comando 'q'
* - recebe o identificador (idp) de um produto e uma quantidade e aumenta
* a quantidade deste no sistema global
*/
void func_q(int idp, int qtd){
   /*verifica se o id e valido, se nao for faz print ao erro*/
   if(eh_id_invalido(idp, cont_produto)) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
   /*se for valido incrementa a quantidade do respetivo produto*/
   else sistema_produtos[idp].qtd += qtd;
}

/*
* funcao correspondente ao comando 'N'
* - cria uma nova encomenda
*/
void func_N(){
   printf("Nova encomenda %d.\n", cont_encomenda);
   sistema_encomendas[cont_encomenda].peso = 0;    /*inicializacao do objeto peso com 0*/
   sistema_encomendas[cont_encomenda].cont = 0;    /*inicializacao do objeto cont com 0*/
   sistema_encomendas[cont_encomenda].preco = 0;   /*inicializacao do objeto preco com 0*/
   cont_encomenda++;
}

/*
* funcao correspondente ao comando 'A'
* - recebe um identificador de encomenda e de produto e uma Quantidade
* - aumenta o respetivo produto pela respetiva quantidade na respetiva encomenda
*/
void func_A(int ide, int idp, int qtd){
   int i, contem = NAO;
   /*verifica se o id e valido, se nao for faz print ao erro*/
   if(eh_id_invalido(ide, cont_encomenda)) printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
   /*verifica se o id e valido, se nao for faz print ao erro*/
   else if(eh_id_invalido(idp, cont_produto)) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
   /*verifica se a quantidade exigida e superior a existente, se sim faz print ao erro*/
   else if(sistema_produtos[idp].qtd < qtd) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
   /*verifica se apos serem acrescentados os produtos nao e excedido o peso maximo, se for faz print ao erro*/
   else if((sistema_produtos[idp].peso * qtd) + sistema_encomendas[ide].peso > 200) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
   else{
      /*loop que percorre os produtos existentes na encomenda (se nao houver produtos nao entra no loop)*/
      for(i = 0; i < sistema_encomendas[ide].cont; i++){
         /*verifica se o produto i da encomenda tiver o mesmo id que o inserido*/
         if(mesmosProdutos(sistema_encomendas[ide].item[i], sistema_produtos[idp])){
            contem = SIM;  /*se for o caso, ativa a flag*/
            break;
         }
      }
      /*se o produto ja se encontra na encomenda*/
      if(contem){
         sistema_encomendas[ide].item[i].qtd += qtd;  /*aumenta a quantidade do produto na encomenda*/
      }
      /*se nao se encontrar na encomenda*/
      else{
         sistema_encomendas[ide].item[sistema_encomendas[ide].cont] = sistema_produtos[idp];  /*insere o produto*/
         sistema_encomendas[ide].item[sistema_encomendas[ide].cont].qtd = qtd;  /*muda a quantidade deste para a quantidade inserida*/
         sistema_encomendas[ide].cont++;  /*incrementa o contador de produtos dentro da encomenda*/
      }
      sistema_encomendas[ide].peso += sistema_produtos[idp].peso * qtd;  /*incrementa o peso da encomenda*/
      sistema_encomendas[ide].preco += sistema_produtos[idp].preco * qtd;  /*incrementa o preco da encomenda*/
      sistema_produtos[idp].qtd -= qtd;   /*decrementa a quantidade do produto no sistema*/
   }
}

/*
* funcao correspondente ao comando 'r'
* - recebe um identificador de produto e uma Quantidade
* - remove a respetiva quantidade do stock existente do respetivo produto no
* sistema global
*/
void func_r(int idp, int qtd){
   /*verifica se o id eh invalido*/
   if(eh_id_invalido(idp, cont_produto)) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
   /*verifica se a quantidade do produto nao fica negativa apos a retirada*/
   else if(sistema_produtos[idp].qtd - qtd < 0) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
   /*caso contrario decrementa a quantidade*/
   else sistema_produtos[idp].qtd -= qtd;
}

/*
* funcao correspondente ao comando 'R'
* - recebe um identificador de encomenda e de produto
* - remove o respetivo produto da respetiva encomenda, sendo que o stock deste
* na encomenda regressa ao stock global
*/
void func_R(int ide, int idp){
   int i, j;
   /*verifica se o id da encomenda eh invalido*/
   if(eh_id_invalido(ide, cont_encomenda)) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
   /*verifica se o id do produto eh invalido*/
   else if(eh_id_invalido(idp, cont_produto)) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
   else{
      /*loop ate encontrar o produto na encomenda*/
      for(i = 0; i < sistema_encomendas[ide].cont; i++){
         /*se encontrar*/
         if(mesmosProdutos(sistema_encomendas[ide].item[i], sistema_produtos[idp])){
            sistema_produtos[idp].qtd += sistema_encomendas[ide].item[i].qtd; /*repoe o stock de sistema*/

            sistema_encomendas[ide].peso -= sistema_encomendas[ide].item[i].qtd * sistema_encomendas[ide].item[i].peso;
            sistema_encomendas[ide].preco -= sistema_encomendas[ide].item[i].qtd * sistema_encomendas[ide].item[i].preco;

            j = i;  /*faz copia da variavel de iteracao*/

            /*enquanto esta nova variavel nao chegar ao fim da encomenda*/
            while(j != sistema_encomendas[ide].cont){
               /*faz 'shift left' dos produtos no vetor encomenda para este ser substituido pelos seguintes*/
               sistema_encomendas[ide].item[j] = sistema_encomendas[ide].item[j+1];
               j++;  /*incrementa j*/
            }
            sistema_encomendas[ide].cont--; /*decrementa o contador de produtos na encomenda*/
            break;
         }
      }
   }
}

/*
* funcao correspondente ao comando 'C'
* - recebe um identificador de uma encomenda
* - retorna o preco da respetiva encomenda
*/
void func_C(int ide){
   /*verifica se o id eh invalido*/
   if(eh_id_invalido(ide, cont_encomenda)) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
   /*se nao for faz print ao preco da encomenda*/
   else printf("Custo da encomenda %d %d.\n", ide, sistema_encomendas[ide].preco);
}

/*
* funcao correspondente ao comando 'p'
* - recebe um identificador de produto e um preco
* - altera o preco do respetivo produto pelo novo tanto no sistema global como
* dentro das encomendas
*/
void func_p(int idp, int preco){
   int i, j;
   if(eh_id_invalido(idp, cont_produto)) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
   else{
      sistema_produtos[idp].preco = preco;   /*altera o preco no sistema*/
      /*loop para cada encomenda*/
      for(i = 0; i < cont_encomenda; i++){
         /*loop para cada produto da encomenda*/
         for(j = 0; j < sistema_encomendas[i].cont; j++){
            /*verifica se o produto for igual ao que esta na encomenda (mesmo id)*/
            if(mesmosProdutos(sistema_encomendas[i].item[j], sistema_produtos[idp])){
               sistema_encomendas[i].preco -= sistema_encomendas[i].item[j].qtd * sistema_encomendas[i].item[j].preco; /*decrementa o preco antigo do preco da encomenda*/
               sistema_encomendas[i].item[j].preco = preco; /*altera o preco do produto na encomenda*/
               sistema_encomendas[i].preco += sistema_encomendas[i].item[j].qtd * sistema_encomendas[i].item[j].preco; /*calcula o novo preco da encomenda*/
               break;
            }
         }
      }
   }
}

/*
* funcao correspondente ao comando 'E'
* - recebe um identificador de encomenda e de produto
* - faz print a descricao e a quantidade do respetivo produto na respetiva
* encomenda
*/
void func_E(int ide, int idp){
   int i;
   /*verifica se o id da encomenda eh invalido*/
   if(eh_id_invalido(ide, cont_encomenda)) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
   /*verifica se o id do produto eh invalido*/
   else if(eh_id_invalido(idp, cont_produto)) printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
   /*caso contrario*/
   else{
      /*percorre os produtos da encomenda de identificador ide*/
      for(i = 0; i < sistema_encomendas[ide].cont; i++){
         /*se encontrar o produto*/
         if(mesmosProdutos(sistema_encomendas[ide].item[i], sistema_produtos[idp])){
            /*faz print da descricao e da quantidade deste na encomenda*/
            printf("%s %d.\n", sistema_produtos[idp].descricao, sistema_encomendas[ide].item[i].qtd);
            return;
         }
      }
      /*se nao der return, quer dizer que o produto tem quantidade 0 na encomenda porque nao existe nela*/
      printf("%s %d.\n", sistema_produtos[idp].descricao, 0);
   }
}

/*
* funcao correspondente ao comando 'm'
* - recebe um identificador de produto
* - retorna o identificador da encomenda onde a quantidade deste e maior, bem
* como o seu proprio identificador de produto
*/
void func_m(int idp){
   int i, j, qtd = 0, ide = 0, contem = NAO;
   /*verifica se o id do produto eh invalido*/
   if(eh_id_invalido(idp, cont_produto)) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
   /*caso contrario*/
   else{
      /*percorre todas as encomendas*/
      for(i = 0; i < cont_encomenda; i++){
         /*percorre todos os produtos em cada encomenda*/
         for(j = 0; j < sistema_encomendas[i].cont; j++){
            /*se encontrar o produto correspondente e a quantidade deste for a maior*/
            if(mesmosProdutos(sistema_encomendas[i].item[j], sistema_produtos[idp]) && (qtd < sistema_encomendas[i].item[j].qtd)){
               qtd = sistema_encomendas[i].item[j].qtd; /*guarda o valor da quantidade*/
               ide = i; /*guarda o identificador da encomenda*/
               contem = SIM; /*ativa a flag de estado*/
               break; /*passa a proxima encomenda*/
            }
         }
      }
      /*se a flag de estado for ativado faz print do identificador do produto,
      * da encomenda em que se encontra e da quantidade deste
      */
      if(contem) printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
   }
}

/*
* funcao correspondente ao comando 'l'
* - ordena todos os produtos no sistema de forma crescente por preco e faz print
* destes na forma ordenada
*/
void func_l(){
   Produto syst_copia[SIZE_SYST_PROD];
   /*
   * como no sistema global de produtos os indices do vetor correspondem
   * diretamente aos identificadores, eh necessario copiar o sistema_produtos
   * para syst_copia para nao alterar a ordem dos id's (e com isso, os indices)
   * no sistema
   */
   copia(syst_copia, sistema_produtos);
   mergesort(syst_copia, 0, cont_produto - 1); /*ordena o vetor*/
   printf("Produtos\n");
   print_produtos(cont_produto, syst_copia);
}

/*
* funcao correspondente ao comando 'L'
* - recebe um identificador de encomenda
* - ordena os produtos na respetiva encomenda por ordem alfabetica da Descricao
* e faz print destes ordenados
*/
void func_L(int ide){
   /*verifica se o id da encomenda eh invalido*/
   if(eh_id_invalido(ide, cont_encomenda)) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
   /*caso contrario*/
   else{
      /*ordena alfabeticamente*/
      ordena(sistema_encomendas[ide].item, sistema_encomendas[ide].cont);
      printf("Encomenda %d\n", ide);
      print_produtos(sistema_encomendas[ide].cont, sistema_encomendas[ide].item);
   }
}

int main(){
   int idp, ide, qtd, preco;
   char comando; /*variavel onde se insere o comando introduzido*/
   int run = SIM; /*variavel de estado para o main loop do programa*/
   Produto produto;

   /*main loop*/
   while(run){
      comando = getchar(); /*le o caracter inicial*/
      switch (comando) {
         case 'a':
            scanf(" %[^:]:%d:%d:%d", produto.descricao, &produto.preco, &produto.peso, &produto.qtd);
            func_a(produto);
            break;

         case 'q':
            scanf("%d:%d", &idp, &qtd);
            func_q(idp, qtd);
            break;

         case 'N':
            func_N();
            break;

         case 'A':
            scanf("%d:%d:%d", &ide, &idp, &qtd);
            func_A(ide, idp, qtd);
            break;

         case 'r':
            scanf("%d:%d", &idp, &qtd);
            func_r(idp, qtd);
            break;

         case 'R':
            scanf("%d:%d", &ide, &idp);
            func_R(ide, idp);
            break;

         case 'C':
            scanf("%d", &ide);
            func_C(ide);
            break;

         case 'p':
            scanf("%d:%d", &idp, &preco);
            func_p(idp, preco);
            break;

         case 'E':
            scanf("%d:%d", &ide, &idp);
            func_E(ide, idp);
            break;

         case 'm':
            scanf("%d", &idp);
            func_m(idp);
            break;

         case 'l':
            func_l();
            break;

         case 'L':
            scanf("%d", &ide);
            func_L(ide);
            break;

         case 'x':
            run = NAO; /*desativa a variavel de estado do main loop*/
            break;

         default:
            continue;
      }
   }
   return 0;
}
