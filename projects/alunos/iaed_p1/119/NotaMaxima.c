#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Guilherme Costa, ist195586,Alameda*/
/* Trabalho de IAED, constru??o de um sistema de logistica */

/* Define as constantes */
#define Valor_inicial 0
#define Maximo_produtos 10000
#define Maximo_C 64
#define Max_Peso 200
#define Max_Encomendas 500
#define Fora -10
#define Letra -2
#define Preco -3
#define TRUE 1
#define FALSE 0

int idp = Valor_inicial; /* Variavel global que indica o numero de produtos */
int ide = Valor_inicial; /* Variabel global que indica o numero de encomendas */

/* Cria a estrutura para o produto */
typedef struct produto{
    char descricao[Maximo_C];
    int preco;
    int peso;
    int qtd;
    int posicao; 
}produto;

/* Cria a estrutura para a encomenda*/
typedef struct encomenda{
    struct produto lista[Max_Encomendas];
    int peso_total;
    int custo_total;
    int num_produtos;
}encomenda;

/* Inicializa as estruturas */
produto prod;
produto sistema[Maximo_produtos];
encomenda enco;
encomenda g_enco[Max_Encomendas];
produto s_ord[Maximo_produtos]; /*s_ord,aux e aux2 sao utilizados apenas para o mergesort */
produto any[Maximo_produtos]; 
produto any2[Maximo_produtos];

/* Funcao que verifica se um produto esta dentro de uma encomenda
   Retorna a posicao na encomenda se estiver dentro, se nao retorna FORA */
int ve_dentro(int ide2,int idp2){
    int i;
    for (i = 0; i < g_enco[ide2].num_produtos; i++){ /* Percorre a encomenda */
        if (strcmp(g_enco[ide2].lista[i].descricao,sistema[idp2].descricao) == 0){ /* Ve se esta dentro */
            return i;
        }
    }
    return Fora;
}
/* Funcao que adiciona um produto ao sistema */
void a(produto prod, produto sistema[]){
    int preco,peso,qtd;
    scanf(" %[^:]:%d:%d:%d",prod.descricao,&preco,&peso,&qtd);/*Recebe o input */
    /* Guarda as caracteristicas do produto adicionado*/
    prod.preco = preco;
    prod.peso = peso;
    prod.qtd = qtd;
    sistema[idp] = prod; /*Guarda no sistema o produto adicionado */
    sistema[idp].posicao = idp; /* Utilizado apenas no merge_sort para comparar precos iguais */
    printf("Novo produto %d.\n",idp++);
}
/* Funcao que adiciona stock a um produto existente */
void q(produto sistema[]){
    int idp2,qtd;
    scanf("%d:%d",&idp2,&qtd);
    if (idp2 >= idp){ /* Ve se existe o produto */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp2);
    }
    else{
        sistema[idp2].qtd += qtd; /*Adiciona stock */
    }
}
/* Funcao que cria uma nova encomenda */
void N(encomenda enco, encomenda g_enco[]){
    g_enco[ide] = enco;
    printf("Nova encomenda %d.\n",ide++);
}
/*Funcao que adiciona um produto a uma encomenda ou soma a quantidade caso ele ja exista na mesma*/
void A(encomenda g_enco[],produto sistema[]){
    int ide2,idp2,qtd2;
    scanf("%d:%d:%d",&ide2,&idp2,&qtd2);
    /* Verifica as condicoes para ser adicionado e devolve o erro respetivo */
    if (ide2 >= ide){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp2,ide2);
    }
    else if (idp2 >= idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp2,ide2);
    }
    else if (qtd2 > sistema[idp2].qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp2,ide2);
    }
    else if (g_enco[ide2].peso_total + sistema[idp2].peso * qtd2 > Max_Peso){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp2,ide2);
    }
    else{
        if (ve_dentro(ide2,idp2) != Fora){/* Caso esteja dentro adiciona a qtd*/
            g_enco[ide2].lista[ve_dentro(ide2,idp2)].qtd += qtd2;
        }
        else{ /*Caso esteja fora guarda o produto num novo espaco*/
            g_enco[ide2].lista[g_enco[ide2].num_produtos] = sistema[idp2];
            g_enco[ide2].lista[g_enco[ide2].num_produtos].qtd = qtd2;
            g_enco[ide2].num_produtos++;
        }
        g_enco[ide2].peso_total += sistema[idp2].peso * qtd2;
        sistema[idp2].qtd -= qtd2; /* Remove do stock do sistema a quantidade adicionada*/
    }
}
/*Funcao que remove stock a um produto no sistema caso seja permitido */
void r(produto sistema[]){
    int idp2,qtd2;
    scanf("%d:%d",&idp2,&qtd2);
    /* Verifica e devolve os erros */
    if (idp2 >= idp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp2);
    }
    else if (sistema[idp2].qtd < qtd2){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd2,idp2);
    }
    else{
        sistema[idp2].qtd -= qtd2; /* Retira stock*/
    }
}
/* Funcao que remove um produto da encomenda ao colocar a sua qtd a 0 caso seja possivel */
void R(encomenda g_enco[],produto sistema[]){
    int ide2,idp2;
    scanf("%d:%d",&ide2,&idp2);
    /*Verifica e devolve os erros */
    if (ide2 >= ide){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp2,ide2);
    }
    else if (idp2 >= idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp2,ide2);
    }
    else{
        if (ve_dentro(ide2,idp2) != Fora){
            g_enco[ide2].peso_total -= g_enco[ide2].lista[ve_dentro(ide2,idp2)].qtd * sistema[idp2].peso;/*Reduz o peso total */
            sistema[idp2].qtd += g_enco[ide2].lista[ve_dentro(ide2,idp2)].qtd; /* Adiciona a qtd */
            g_enco[ide2].lista[ve_dentro(ide2,idp2)].qtd = Valor_inicial; /* Mete a qtd na encomenda a 0 */
        }
    }
}
/*Funcao que calcula o custo de uma encomenda caso ela exista */
void C(encomenda g_enco[]){
    int ide2,i;
    scanf("%d",&ide2);
    if (ide2 >= ide){ /*Se nao existir devolve erro */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide2);
    }
    else{
        for (i = 0; i < g_enco[ide2].num_produtos; i++){ /* Percorre a encomenda adicionando o custo de de cada produto */
            g_enco[ide2].custo_total += g_enco[ide2].lista[i].preco * g_enco[ide2].lista[i].qtd;
        }
        printf("Custo da encomenda %d %d.\n",ide2,g_enco[ide2].custo_total);
        g_enco[ide2].custo_total = Valor_inicial; /*Coloca custo_total a 0 para nao dar erro ao calcular uma proxima vez */
    }
}
/* Funcao que altera o preco de um produto, caso ele exista */
void p(encomenda g_enco[], produto sistema[]){
  int idp2,preco2,b,e;
  scanf("%d:%d",&idp2,&preco2);
  if (idp2 >= idp){ /* Se nao existir devolve erro*/
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp2);
  }
  else{
      sistema[idp2].preco = preco2; /* Muda o seu preco no sistema */
      for (b = 0; b < ide; b++){ /* Percorre todas as encomendas */
          for (e = 0; e < g_enco[b].num_produtos; e++) { /* Percorre uma encomenda  */
              if (ve_dentro(b,idp2) != Fora){ /*Caso esteja dentro da encomenda altera o seu preco dentro da mesma */
                  g_enco[b].lista[ve_dentro(b,idp2)].preco = preco2;
              }
          } 
      }
  }
}
/* Funcao que indica a descricao e qtd de um produto numa encomenda caso estes existam */
void E(encomenda g_enco[],produto sistema[]){
    int ide2,idp2;
    scanf("%d:%d",&ide2,&idp2);
    /* Verifica e devolve os erros */
    if (ide2 >= ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide2);
    }
    else if (idp2 >= idp){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp2);
    }
    else{
        if (ve_dentro(ide2,idp2) != Fora){ /* Esta dentro devolve o seu nome e qtd na encomenda */
            printf("%s %d.\n",g_enco[ide2].lista[ve_dentro(ide2,idp2)].descricao,g_enco[ide2].lista[ve_dentro(ide2,idp2)].qtd);
        }
        else{
            printf("%s 0.\n",sistema[idp2].descricao); /*Esta fora devolve o seu nome e a qtd na encomenda que e igual a 0 */
        }
    }
}
/*Funcao que devolve a encomenda e a qtd do produto onde esta e maior*/
void m(encomenda g_enco[]){
    int idp2,maior_qtd,b,e,ide_menor;
    scanf("%d",&idp2);
    if (idp2 >= idp){ /* Caso nao exista devolve erro*/
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp2);
    }
    maior_qtd = Valor_inicial;
    ide_menor = Valor_inicial;
    for (b = 0; b < ide; b++){ /* Processo igual ao da funcao p*/
          for (e = 0; e < g_enco[b].num_produtos; e++) {
              if (ve_dentro(b,idp2) != Fora && maior_qtd < g_enco[b].lista[ve_dentro(b,idp2)].qtd){
                 maior_qtd = g_enco[b].lista[ve_dentro(b,idp2)].qtd;
                 ide_menor = b; /*Garante que caso haja encomendas com a mesma qtd do produto, seja devolvido a com ide menor*/
              }
          }
   }
   if (maior_qtd != Valor_inicial){ /*Garante que apenas retorna se exister pelo menos uma encomenda com este produto*/
       printf("Maximo produto %d %d %d.\n",idp2,ide_menor,maior_qtd);
   }
}

/* Funcao que compara os precos de dois produtos*/
int Compara_Preco(produto anterior, produto posterior){ 
    if (anterior.preco < posterior.preco){
        return TRUE; 
    }
    else if(anterior.preco == posterior.preco){ /*Garante que o com menor idp fica em primeiro caso os precos sejam iguais*/
        return anterior.posicao < posterior.posicao;
    }
    return FALSE;
}
/* Funcao que compara as descricoes de dois produtos atraves dos caracteres ASCII*/
int Compara_Letras(produto anterior,produto posterior){
     if (strcmp(anterior.descricao,posterior.descricao) < Valor_inicial){
         return TRUE;
     }
    return FALSE;   
}

/*Funcao necessaria para o mergesorte, realiza as trocas das posicoes */
void merge(int b,produto auxiliar[], int esquerda, int m, int direita){
    int i, j, k;
    if (b == Preco){
        for (i = m+1; i > esquerda; i--)
            any[i-1] = auxiliar[i-1];
        for (j = m; j < direita; j++)
            any[direita+m-j] = auxiliar[j+1];
        for (k = esquerda; k <= direita; k++)
            if (Compara_Preco(any[j], any[i]) == TRUE)
                auxiliar[k] = any[j--];
            else
                auxiliar[k] = any[i++];
    }
    else if (b == Letra){
        for (i = m+1; i > esquerda; i--)
            any2[i-1] = auxiliar[i-1];
        for (j = m; j < direita; j++)
            any2[direita+m-j] = auxiliar[j+1];
        for (k = esquerda; k <= direita; k++)
            if (Compara_Letras(any2[j], any2[i]) == TRUE)
                auxiliar[k] = any2[j--];
            else
                auxiliar[k] = any2[i++];
    }   
}
/*Algoritmo de ordenacao recursivo que funciona atraves da comparacao e divisao de arrays*/
void mergesort(int b,produto auxiliar[], int esquerda, int direita) {
    int m = (direita+esquerda)/2;
    if (direita <= esquerda)
        return;
    mergesort(b,auxiliar, esquerda, m);
    mergesort(b,auxiliar,m+1, direita);
    merge(b,auxiliar, esquerda, m, direita);
}
/*Funcao que devolve os produtos num sistema por ordem crescente de preco e de idp como segundo criterio */
void l(produto sistema[]){
    int i;
    if( idp == Valor_inicial){
        printf("Produtos\n");
    } 
    else{
        for (i = 0; i < idp; i++){ /* Copia o sistema para o s_ord */
        s_ord[i] = sistema[i];
        }
        mergesort(Preco,s_ord,Valor_inicial, (idp - 1)); /*Realiza o mergesort com a condicao b == Preco */
        printf("Produtos\n");
        for ( i = 0; i < idp; i++){ /* Percorre o sistema */
        printf("* %s %d %d\n",s_ord[i].descricao,s_ord[i].preco,s_ord[i].qtd);
        }
    }
}
/*Funcao que lista os produtos numa encomenda caso exista*/
void L(encomenda g_enco[]){
    int ide2,i;
    scanf("%d",&ide2);
    if (ide2 >= ide){   /*Caso nao exista devolve o erro */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide2);
    }
    else if (g_enco[ide2].num_produtos == 0){ /*Se nao existerem encomendas imprime apenas o cabecalho */
        printf("Encomenda %d\n",ide2);
    }
    else{
        mergesort(Letra,g_enco[ide2].lista,Valor_inicial,(g_enco[ide2].num_produtos- 1)); /*Realiza o mergesort com b == Letra */
        printf("Encomenda %d\n",ide2);
        for (i = 0; i < g_enco[ide2].num_produtos; i++){ /*Percorre a encomenda */ 
            if (g_enco[ide2].lista[i].qtd > Valor_inicial){ /* Se tiverem qtd igual a 0 foram removidos logo nao se imprime*/
                printf("* %s %d %d\n",g_enco[ide2].lista[i].descricao,g_enco[ide2].lista[i].preco,g_enco[ide2].lista[i].qtd);
            }
        }
        
    }
    
}
/*Funcao principal serve apenas para determinar que funcao se vai realizar */
int main(){
    char letra_inicial;
    while (Maximo_produtos > Valor_inicial){ /*Ciclo infinito */
        letra_inicial = getchar(); /*Obtem a primeira letra*/
        /*Todas as funcoes a realizar dependendo da letra obtida*/
        if (letra_inicial == 'a')
             a(prod,sistema);
        else if (letra_inicial == 'x') /* Sai do ciclo*/
             break;
        else if (letra_inicial == 'q')
            q(sistema);
        else if (letra_inicial == 'l')
            l(sistema);       
        else if (letra_inicial == 'N')
            N(enco,g_enco);
        else if (letra_inicial == 'A')
            A(g_enco, sistema);
        else if (letra_inicial == 'r')
            r(sistema);
        else if (letra_inicial == 'R')
            R(g_enco, sistema);
        else if (letra_inicial == 'C')
            C(g_enco);
        else if (letra_inicial == 'p')
            p(g_enco,sistema);
        else if (letra_inicial == 'E')
            E(g_enco,sistema);
        else if (letra_inicial == 'm')
            m(g_enco);
        else if (letra_inicial == 'L')
            L(g_enco);    
    }
    return 0;
}