#include <stdio.h>
#include <string.h>

/* Definicao de constantes */
#define MAXPROD  10000
#define MAXENCOM   500
#define MAXPESO    200
#define MAXDESC     65

/* Definicao de Estruturas de Dados */
typedef struct {
    int  real;
    int  pID;
    char desc[MAXDESC];
    int  preco;
    int  peso;
    int  stock;
} Produto;

typedef struct {
    int  real;
    int  eID;
    Produto produtos[MAXPESO];
    int  peso_e;
    int  prodcount;
} Encomenda;

typedef struct {
    char desc[MAXDESC];
    int  pID;
    int  qtd;
} L_AUX;

/* Contadores de produtos e encomendas totais no sistema, respetivamente */
int pcount=0;
int ecount=0;

/* Vetores onde s?o guardados os produtos e as encomendas no sistema, respetivamente */
Produto sistema[MAXPROD];  
Encomenda sistema_e[MAXENCOM]; 
L_AUX ordenada [MAXPESO];

/* Prototipos */
void adicionaProduto();
void adicionaStock();
void removeStock();
void alteraPreco();
void criaEncomenda();
void adiciona_ah_Encomenda();
void adicionaEnc_aux(int ide, int idp, int qtd);
void removeDaEncome();
void removeDaEncome_aux(int ide,int idp);
void custoEncome();
void prodNaEncom();
void ocorrenciaProd();
void ocorrenciaProd_aux(int idp);
void listaProdSistema();
void listaProdEncomenda();
void listaProdEncomenda_aux(int ide);

/*======================================================Codigo======================================================*/

/* A main le o carater(comando) do std input  e realiza a acao pretendida */
int main() { 
    char comando; 
    scanf("%c", &comando);
    while (comando !='x') {
       switch (comando)
        {
        case 'a': adicionaProduto();
        break;
        
        case 'q': adicionaStock();
        break;
        
        case 'r': removeStock();
        break;
        
        case 'p': alteraPreco();
        break;
        
        case 'N': criaEncomenda();
        break;
        
        case 'A': adiciona_ah_Encomenda();
        break;
        
        case 'R': removeDaEncome();
        break;
        
        case 'C': custoEncome();
        break;
        
        case 'E': prodNaEncom();
        break;
        
        case 'm': ocorrenciaProd();
        break;
        
        case 'l': listaProdSistema();
        break;
        
        case 'L': listaProdEncomenda();
        break;
       }
    scanf("%c", &comando);
    } 
    return 0;
}

/* Le os dados da linha de comando e cria um novo produto, atualizando o vetor sistema. Atualiza <pcount> */
void adicionaProduto() {
    scanf("%[^:]:%d:%d:%d", sistema[pcount].desc, &sistema[pcount].preco, &sistema[pcount].peso, &sistema[pcount].stock);
    sistema[pcount].pID=pcount;
    sistema[pcount].real=1;
    printf("Novo produto %d.\n", sistema[pcount].pID);
    pcount++;
}

/* Atribui um valor de stock ao produto <pid>; caso o produto ja tenha stock > 0 adiciona o valor ao stock existente */
void adicionaStock() {
    int pid;
    int stockadicional;
    scanf("%d:%d", &pid, &stockadicional);
    if (sistema[pid].real == 1) {                                  
       sistema[pid].stock=sistema[pid].stock+stockadicional;
    }
    else {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", pid);
    }
}

/* Remove stock, <stockaremover>, ao produto <pid> no sistema */
void removeStock() {
    int pid;
    int stockaremover;
    scanf("%d:%d", &pid, &stockaremover);
    if (sistema[pid].real == 1) {
       if (stockaremover <= sistema[pid].stock) {
          sistema[pid].stock=sistema[pid].stock-stockaremover;
       }
       else {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stockaremover, pid);
       }
    }
    else {
       printf("Impossivel remover stock do produto %d. Produto inexistente.\n", pid);
    }     
}

/* Atualiza o valor do preco de um produto no sistema */
void alteraPreco() {
    int pid;
    int preconovo;
    scanf("%d:%d", &pid, &preconovo);
    if (sistema[pid].real == 1) {
       sistema[pid].preco=preconovo;
    }
    else {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", pid);
    }
}

/* Cria encomenda no vetor <sistema_e>, atualiza <ecount> */
void criaEncomenda() {
    sistema_e[ecount].eID=ecount;
    sistema_e[ecount].real=1;
    printf("Nova encomenda %d.\n", sistema_e[ecount].eID);
    ecount++;
}

/* 
 * Auxiliar para adicionar produto a uma encomenda 
 * Percorre o vetor dos produtos da encomenda <ide> e procura o produto <idp> na encomenda
 * Caso encontre o produto adiciona a <qtd> ah quantidade ja existente na encomenda
 * Caso nao encontre o produto, adiciona o produto ah encomenda e atualiza o membro prodcount
 * No fim, atualiza o stock do produto no sistema, removendo <qtd>
*/ 
void adicionaEnc_aux(int ide, int idp, int qtd) {
    int pesoprod=sistema[idp].peso*qtd;
    int pesoatual=sistema_e[ide].peso_e;
    int prodcount=sistema_e[ide].prodcount;
    int i;
    int match=-1;
    sistema_e[ide].peso_e=pesoprod+pesoatual;       /* Atualiza peso total da encomenda */
    for (i = 0; i <= prodcount; i++) {
       if (sistema_e[ide].produtos[i].pID == idp && sistema_e[ide].produtos[i].real == 1) {
          match=i;
          break;
       }
    }
    if (match >= 0) {     /* Caso o produto ja exista na encomenda, match >= 0, atualiza qtd do produto na encomenda */
       sistema_e[ide].produtos[match].stock=sistema_e[ide].produtos[match].stock+qtd;
    }
    else {                /* Caso produto nao exista na encomenda */
       sistema_e[ide].produtos[prodcount].pID=idp;
       sistema_e[ide].produtos[prodcount].real=1;
       sistema_e[ide].produtos[prodcount].stock=qtd;
       strcpy(sistema_e[ide].produtos[prodcount].desc, sistema[idp].desc);
       sistema_e[ide].prodcount++;
    }
    sistema[idp].stock=sistema[idp].stock-qtd;      /* Remove stock do sistema */
}

/* 
 * Verifica se existe encomenda <ide>, produto <idp> na qtd suficiente em stock e se o peso nao excede 200
 * Caso tudo se verifique chama a funcao adicionaEnc_aux
*/ 
void adiciona_ah_Encomenda() {
    int ide;
    int idp;
    int qtd;
    int pesototal;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    pesototal=sistema[idp].peso*qtd;
    pesototal=sistema_e[ide].peso_e+pesototal;
    if (sistema_e[ide].real == 1) {
       if (sistema[idp].real == 1) {
          if (sistema[idp].stock >= qtd) {
             if (pesototal <= MAXPESO) {
                adicionaEnc_aux(ide, idp, qtd);
             }
             else {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
             }
          }
          else {
             printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          }
       }
       else {
          printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
       }    
    }
    else {
       printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }   
}

/* 
 * Encontra o produto a remover da encomenda,
 * Atualiza a qtd de produto na encomenda para 0 e atualiza o stock do produto no sistema
 * Atualiza o peso total da encomenda
*/ 
void removeDaEncome_aux(int ide,int idp){
    int prodcount=sistema_e[ide].prodcount;
    int i;
    int qtd;
    int pesoaremover;
    for (i = 0; i <= prodcount; i++) {
       if (sistema_e[ide].produtos[i].pID == idp) {
          qtd=sistema_e[ide].produtos[i].stock;
          sistema[idp].stock=sistema[idp].stock+qtd;
          sistema_e[ide].produtos[i].stock=0;
          pesoaremover=sistema[idp].peso*qtd;
          sistema_e[ide].peso_e=sistema_e[ide].peso_e-pesoaremover;
          break;
       }
    }
}

/* Verifica se produto <idp> e encomenda <ide> existem, se isto se verifica, chama removeDaEncome_aux */
void removeDaEncome() {
    int ide;
    int idp;
    scanf("%d:%d", &ide, &idp);
    if (sistema_e[ide].real == 1) {
       if (sistema[idp].real == 1) {
          removeDaEncome_aux(ide, idp);     
       }
       else {
          printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
       }
    }
    else {
       printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
}

/* Calcula custo total da encomenda */
void custoEncome() {
    int ide;
    int i;
    int prodcount;
    int soma=0;
    int precoprod=0;
    int indice;
    int qtd;
    scanf("%d", &ide);
    prodcount=sistema_e[ide].prodcount;
    if (sistema_e[ide].real == 1) {
       for (i = 0; i <= prodcount; i++) {             /* Percorre os produtos da encomenda */
          if (sistema_e[ide].produtos[i].real == 1) { /* Verifica se produto existe na encomenda */
             indice=sistema_e[ide].produtos[i].pID;
             qtd=sistema_e[ide].produtos[i].stock;
             precoprod=sistema[indice].preco*qtd;     /* Calcula preco do produto, multiplica pela qtd na encomenda */
             soma=soma+precoprod;                     /* Adiciona preco do produto a <soma> que sera o custo total */
          }
       }
       printf("Custo da encomenda %d %d.\n", ide, soma);
    }
    else {
       printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
}

/* Retorna a qtd de um certo produto <idp> na encomenda <ide> */
void prodNaEncom() {
    int ide;
    int idp;
    int i;
    int match=-1;
    int qtd;
    int prodcount;
    char desc[MAXDESC];
    scanf("%d:%d", &ide, &idp);
    prodcount=sistema_e[ide].prodcount;
    if (sistema_e[ide].real == 1) {                       /* Verifica se encomenda <ide> existe */
       if (sistema[idp].real == 1) {                      /* Verifica se produto <idp> existe */
          for (i = 0; i <= prodcount; i++) {
             if (sistema_e[ide].produtos[i].pID==idp) {   /* Procura produto na encomenda */
                match=i;
                qtd=sistema_e[ide].produtos[match].stock;
                strcpy(desc, sistema[idp].desc+1);
                printf("%s %d.\n", desc, qtd);
                break;
             }
          }
          if (match == -1) {         /* Se nao encontra o produto, imprime a descricao do produto e quantidade 0 */
             strcpy(desc, sistema[idp].desc+1);
             printf("%s 0.\n", desc);
          }
       }
       else {
         printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
       }
    }
    else {
       printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}

/* Retorna a encomenda em que um produto ocorre mais vezes e a sua quantidade na encomenda */
void ocorrenciaProd_aux(int idp) {
    int maior=0;
    int i;
    int prodcount;
    int n;
    int encomenda;
    for (i = 0; i < ecount; i++) {                 /* percorre as encomendas */
       prodcount=sistema_e[i].prodcount;
       for (n = 0; n < prodcount; n++) {           /* percorre o vetor de produtos de todas encomendas */ 
          if (sistema_e[i].produtos[n].pID == idp && sistema_e[i].produtos[n].stock > maior) { 
             maior=sistema_e[i].produtos[n].stock; /* atualiza <maior> se encontrar encomenda com <idp> em maior qtd */
             encomenda=i;
          }
       }
    }
    if (maior > 0) {
       printf("Maximo produto %d %d %d.\n", idp, encomenda, maior);
    }
}

/* Verifica se produto existe, caso se verifique, chama ocorrenciaProd_aux */
void ocorrenciaProd() {
    int idp;
    scanf("%d", &idp);
    if (sistema[idp].real == 1) {
       ocorrenciaProd_aux(idp);
    }
    else {
       printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
}

/* 
 * Lista produtos do sistema por preco usando insertion sort
 * Cria um vetor bidimensional auxiliar que guarda os precos e pID correspondente, de seguida ordena por precos
*/ 
void listaProdSistema() {
    int auxiliar[MAXPROD][2];
    int i;
    int left=0;
    int right=pcount;
    int j;
    int idp;
    for (i = 0; i < pcount; i++) {
       auxiliar[i][0]=sistema[i].preco;
       auxiliar[i][1]=i;
    }
    for (i = left+1; i < right; i++) {
       int v=auxiliar[i][0];
       int w=auxiliar[i][1];
       j=i-1;
       while ( j >= left && auxiliar[j][0] > v) {
          auxiliar[j+1][0]=auxiliar[j][0];
          auxiliar[j+1][1]=auxiliar[j][1];
          j--;
       }
       auxiliar[j+1][0]=v;
       auxiliar[j+1][1]=w;
    }
    printf("Produtos\n");
    for (i = 0; i < pcount; i++) {
       idp=auxiliar[i][1];
       printf("*%s %d %d\n", sistema[idp].desc, sistema[idp].preco, sistema[idp].stock);
    }
}

/* Lista os produtos duma encomenda <ide> ordenados alfabeticamente */
void listaProdEncomenda_aux(int ide) {
    int i;
    int j;
    char temp[MAXDESC];
    int tempid;
    int tempqtd;
    int preco;
    for (i = 0; i < sistema_e[ide].prodcount; i++) {  /* Cria uma lista com as descricoes, stock e pID dos produtos da encomenda */
          ordenada[i].pID=sistema_e[ide].produtos[i].pID;
          ordenada[i].qtd=sistema_e[ide].produtos[i].stock;
          strcpy(ordenada[i].desc, sistema_e[ide].produtos[i].desc);   
    }
    for (i = 0; i <= sistema_e[ide].prodcount; i++) {
       for (j = i+1; j < sistema_e[ide].prodcount; j++) {
          if (strcmp(ordenada[i].desc, ordenada[j].desc) > 0) {   /*Ordena lista por ordem alfabetica da descricao */
            strcpy(temp, ordenada[i].desc);
            strcpy(ordenada[i].desc, ordenada[j].desc);
            strcpy(ordenada[j].desc, temp);
            tempid=ordenada[i].pID;
            ordenada[i].pID=ordenada[j].pID;
            ordenada[j].pID=tempid;
            tempqtd=ordenada[i].qtd;
            ordenada[i].qtd=ordenada[j].qtd;
            ordenada[j].qtd=tempqtd;
          } 
       }
    }
    printf("Encomenda %d\n", ide);
    for (i = 0; i < sistema_e[ide].prodcount; i++) {
       if (ordenada[i].qtd > 0) {
          tempid=ordenada[i].pID;
          preco=sistema[tempid].preco;
          printf("*%s %d %d\n", ordenada[i].desc, preco, ordenada[i].qtd);
       }
    }
}

/* 
 * Verifica se <ide> existe e se peso > 0, ou seja, se ha produtos na encomenda
 * Chama listaProdEncomenda_aux se ambas as condicoes se verificarem
*/
void listaProdEncomenda(){
    int ide;
    scanf("%d", &ide);
    if (sistema_e[ide].real == 1) {
       if (sistema_e[ide].peso_e != 0) {
          listaProdEncomenda_aux(ide);
       }
       else {
          printf("Encomenda %d\n", ide);
       }
    }
    else {
       printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}
