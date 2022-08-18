#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPRODUTO 10000 /* No maximo existem 10 000 produtos*/
#define MAXENCOMENDAS 500
#define MAXPESO 200

typedef struct Produto{
  int id;
  char desc[64];
  int preco;
  int peso;
  int stock;

} produto;

typedef struct Encomenda{
  int id;
  int idprodutos[200];
  int quantidadestock[200];
  int peso;
  int custo;
  int numeroDeProdutos;
} encomenda;



int main(){
  char comando; /* Comando a executar, primeiro caracter de cada linha de entrada*/
  
  char tmp[100]; /* Variavel temporaria para ler as caracteristicas dos produtos*/
  char tmp2[100];
  char adiciona[100];

  int comandoA = 0; /* Contador do numero de vezes que o comando a foi executado*/
  int comandoE = 0;


  int altera = 1;
  int i;
  int f;

  int ocorrenciaProduto = 0;
  int idOcorrencia = 0; 
 
  produto listaProdutos[MAXPRODUTO]; /* Vetor que contem produtos */
  encomenda listaEncomendas[MAXENCOMENDAS];



  scanf("%c",&comando);
  


  for(;;) { /* Loop infinito */

    switch(comando) {
      
      /* adiciona um novo produto ao sistema TESTADO*/
    case 'a':{

          listaProdutos[comandoA].id = comandoA;  /* Guarda o id do produto na lista de produtos na posicao comandoA*/

          scanf("%*[ ]%[^:]s", listaProdutos[comandoA].desc); /* Le e guarda a descricao do produto na lista de produtos na posicao comandoA*/

          scanf("%*[:]%[^:]s", tmp); listaProdutos[comandoA].preco=atoi(tmp); /* Le o preco como uma string e guanda em tmp, depois converte o valor de tmp para um inteiro com o comando atoi e guarda esse inteiro na lista de produtos*/

          scanf("%*[:]%[^:]s", tmp); listaProdutos[comandoA].peso=atoi(tmp);

          scanf("%*[:]%[^:\n]s", tmp); listaProdutos[comandoA].stock=atoi(tmp);

          printf("Novo produto %i.\n", listaProdutos[comandoA].id);

          comandoA++; /* Soma +1 a variavel que conta as vezes que o comando a foi executado */

      break;
    }

      /* adiciona stock a um produto existente no sistema  (q ido:stock) */
    case 'q': {

          scanf("%*[ ]%[^:]s", tmp);

          if(strlen(listaProdutos[atoi(tmp)].desc) == 0){
            printf("Impossivel adicionar produto %s ao stock. Produto inexistente.\n", tmp);
            break;              
          }

          scanf("%*[:]%[^:\n]s", adiciona);
          listaProdutos[atoi(tmp)].stock+=atoi(adiciona);

      break;
    }

      /* cria uma nova encomenda */
    case 'N': {
        
        listaEncomendas[comandoE].id = comandoE;    /* Guarda o id da encomenda na lista de produtos na posicao encomendaE*/
        printf("Nova encomenda %i.\n", listaEncomendas[comandoE].id);
        

        listaEncomendas[comandoE].peso = 0;
        listaEncomendas[comandoE].custo = 0;
        listaEncomendas[comandoE].numeroDeProdutos = 0;
        
        comandoE++;

      break;
    }

     /* adiciona um produto a uma encomenda */
    case 'A':{
      scanf("%*[ ]%[^:]s", tmp);
      scanf("%*[:]%[^:\n]s", tmp2);      


      if (comandoE <= atoi(tmp)){
        printf("Impossivel adicionar produto %s a encomenda %s. Encomenda inexistente.\n", tmp2, tmp);
            break;
      }

      if (strlen(listaProdutos[atoi(tmp2)].desc) == 0){
            printf("Impossivel adicionar produto %s a encomenda %s. Produto inexistente.\n", tmp2 , tmp);
            break;
      }
     
      scanf("%*[:]%[^:\n]s", adiciona);
      if (listaProdutos[atoi(tmp2)].stock < atoi(adiciona)){
            printf("Impossivel adicionar produto %s a encomenda %s. Quantidade em stock insuficiente.\n", tmp2, tmp);
            break;
      }

      if (((atoi(adiciona) * listaProdutos[atoi(tmp2)].peso) + listaEncomendas[atoi(tmp)].peso) > MAXPESO ){
        printf("Impossivel adicionar produto %s a encomenda %s. Peso da encomenda excede o maximo de 200.\n", tmp2, tmp);
        break;
      }
    
      for (i=0; i < listaEncomendas[atoi(tmp)].numeroDeProdutos; i++ ){
        if (listaEncomendas[atoi(tmp)].idprodutos[i] == atoi(tmp2)){

          listaEncomendas[atoi(tmp)].quantidadestock[i] += atoi(adiciona);

          listaEncomendas[atoi(tmp)].peso = listaEncomendas[atoi(tmp)].peso + (atoi(adiciona) * listaProdutos[atoi(tmp2)].peso);
          /*listaEncomendas[atoi(tmp)].custo = listaEncomendas[atoi(tmp)].custo + (atoi(adiciona) * listaProdutos[atoi(tmp2)].preco);*/

          listaProdutos[atoi(tmp2)].stock -= atoi(adiciona);

          goto fim;  
        } 
      }


      listaEncomendas[atoi(tmp)].idprodutos[listaEncomendas[atoi(tmp)].numeroDeProdutos] = atoi(tmp2);
      listaEncomendas[atoi(tmp)].quantidadestock[listaEncomendas[atoi(tmp)].numeroDeProdutos] = atoi(adiciona);

      listaEncomendas[atoi(tmp)].peso = listaEncomendas[atoi(tmp)].peso + (atoi(adiciona) * listaProdutos[atoi(tmp2)].peso);

      listaProdutos[atoi(tmp2)].stock -= atoi(adiciona);

      if(altera){
        listaEncomendas[atoi(tmp)].numeroDeProdutos++;
      }

      fim:
      break;
    }

      /* remove stock a um produto existente  TESTADO*/
    case 'r': {

          scanf("%*[ ]%[^:]s", tmp);

          if(strlen(listaProdutos[atoi(tmp)].desc) == 0){
            printf("Impossivel remover stock do produto %s. Produto inexistente.\n", tmp);
            break;              
          }

          scanf("%*[:]%[^:\n]s", adiciona);

          if (listaProdutos[atoi(tmp)].stock < atoi(adiciona))
          {
            printf("Impossivel remover %s unidades do produto %i do stock. Quantidade insuficiente.\n", adiciona, listaProdutos[atoi(tmp)].id);
            break;
          }

          listaProdutos[atoi(tmp)].stock-=atoi(adiciona);

      break;
    }

      /* remove um produto de uma encomenda */
    case 'R': {
      scanf("%*[ ]%[^:]s", tmp);
      scanf("%*[:]%[^:\n]s", tmp2);      


      if (comandoE <= atoi(tmp)){
        printf("Impossivel remover produto %s a encomenda %s. Encomenda inexistente.\n", tmp2, tmp);
            break;
      }

      if (strlen(listaProdutos[atoi(tmp2)].desc) == 0){
            printf("Impossivel remover produto %s a encomenda %s. Produto inexistente.\n", tmp2 , tmp);
            break;
      }
      

      for (i = 0; i < listaEncomendas[atoi(tmp)].numeroDeProdutos; i++ ){
        /*printf("Dentro do for1\n");*/
        if (listaEncomendas[atoi(tmp)].idprodutos[i] == atoi(tmp2)){

          listaEncomendas[atoi(tmp)].peso -= (listaEncomendas[atoi(tmp)].quantidadestock[i] * listaProdutos[atoi(tmp2)].peso);

          listaEncomendas[atoi(tmp)].idprodutos[i] = listaEncomendas[atoi(tmp)].idprodutos[i+1];

          listaProdutos[atoi(tmp2)].stock += listaEncomendas[atoi(tmp)].quantidadestock[i];

          listaEncomendas[atoi(tmp)].quantidadestock[i] = listaEncomendas[atoi(tmp)].quantidadestock[i+1];

          for (; i < listaEncomendas[atoi(tmp)].numeroDeProdutos - 1; i++){
            /*printf("For2\n");*/
            listaEncomendas[atoi(tmp)].idprodutos[i] = listaEncomendas[atoi(tmp)].idprodutos[i+1];

            listaEncomendas[atoi(tmp)].quantidadestock[i] = listaEncomendas[atoi(tmp)].quantidadestock[i+1];
          }

          
          listaEncomendas[atoi(tmp)].quantidadestock[i+1] = 0;
          listaEncomendas[atoi(tmp)].numeroDeProdutos--;

          goto final;
        }  
      }

      final:
     
      break;
    }

     /* calcula o custo de uma encomenda */
    case 'C':{

      scanf("%*[ ]%[^:\n]s", tmp);
      if (comandoE <= atoi(tmp)){
        printf("Impossivel calcular custo da encomenda %s. Encomenda inexistente.\n", tmp);
            break;
      }

      for (i=0; i < listaEncomendas[atoi(tmp)].numeroDeProdutos; i++ ){
        listaEncomendas[atoi(tmp)].custo += (listaProdutos[listaEncomendas[atoi(tmp)].idprodutos[i]].preco * listaEncomendas[atoi(tmp)].quantidadestock[i]);        
      }

      printf("Custo da encomenda %s %i.\n", tmp, listaEncomendas[atoi(tmp)].custo);
      listaEncomendas[atoi(tmp)].custo = 0;
      break;
    }

      /* altera o pre?o de um produto existente no sistema TESTADO*/
    case 'p': {

          scanf("%*[ ]%[^:]s", tmp);

          if(strlen(listaProdutos[atoi(tmp)].desc) == 0){
            printf("Impossivel alterar preco do produto %s. Produto inexistente.\n", tmp);
            break;              
          }

          scanf("%*[:]%[^:\n]s", adiciona);
          listaProdutos[atoi(tmp)].preco=atoi(adiciona);

      break;
    }

      /* retorna a descri??o e a quantidade de um produto numa dada encomenda */
    case 'E': {
      scanf("%*[ ]%[^:]s", tmp);
      scanf("%*[:]%[^:\n]s", tmp2);      


      if (comandoE <= atoi(tmp)){
        printf("Impossivel listar encomenda %s. Encomenda inexistente.\n", tmp);
            break;
      }

      if (strlen(listaProdutos[atoi(tmp2)].desc) == 0){
            printf("Impossivel listar produto %s. Produto inexistente.\n", tmp2);
            break;
      }

      for(i=0; i<listaEncomendas[atoi(tmp)].numeroDeProdutos; i++ ){
        if(listaEncomendas[atoi(tmp)].idprodutos[i] == atoi(tmp2)){
          printf("%s %i.\n",listaProdutos[atoi(tmp2)].desc, listaEncomendas[atoi(tmp)].quantidadestock[i]);

          goto terminou;
        }
      }

      printf("%s 0.\n",listaProdutos[atoi(tmp2)].desc);

      terminou:
      break;
    }

     /* retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
    case 'm':{
      scanf("%*[ ]%[^:\n]s", tmp);

      if (strlen(listaProdutos[atoi(tmp)].desc) == 0){
            printf("Impossivel listar maximo do produto %s. Produto inexistente.\n", tmp);
            break;
      }

      for(i=0; i < comandoE; i++){
        for(f=0; f < listaEncomendas[i].numeroDeProdutos ; f++){
          if(listaEncomendas[i].idprodutos[f] == atoi(tmp)){
            if(ocorrenciaProduto < listaEncomendas[i].quantidadestock[f]){
              ocorrenciaProduto = listaEncomendas[i].quantidadestock[f];
              idOcorrencia = i;

              /*printf("Encontrou uma na encomenda %i\n", i);*/

            }
            if (ocorrenciaProduto == listaEncomendas[i].quantidadestock[f]){
              if(idOcorrencia >i){
                idOcorrencia = i;
              }
            }
          }           
        }
      }

      if (ocorrenciaProduto != 0)
      {
        printf("Maximo produto %s %i %i.\n", tmp, idOcorrencia, ocorrenciaProduto);
      }
      ocorrenciaProduto = 0;
      idOcorrencia = 0;

      break;
    }


      /* lista todos os produtos existentes no sistema por ordem crescente de pre?o */
    case 'l': {
        /*
        for(i=0; i<MAXPRODUTO-1; i++){
          for(f=i+1; f<MAXPRODUTO-1; f++){    // Erro = Do modo anterior o ?ltimo elemento n?o era comparado, assim n?o mudava.
            if(listaProdutos[i].preco < listaProdutos[f].preco){       // A l?gica estava invertida, gerando sequ?ncia 'int' em ordem reversa.
              temporaria = listaProdutos[i].id;
              vetor[i] = listaProdutos[f].id;
              vetor[f] = temporaria;
            }
          }
        }  */
      break;
    }

      /* lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
    case 'L': {

      break;
    }

     /* termina o programa */
    case 'x': {

      return 0;
    }
    }
    scanf("%c", &comando); /* Vai a linha seguinte ler o valor do caracter que diz qual comando a executar e guarda no lugar do comando executado anteriormente */
  }
  return 0;
}
