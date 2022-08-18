#include "estruturas.h"

void comando_a() {
    /*adiciona um novo produto no sistema*/
    produto prod;
    int size_input, i, j = 0;
    char descricao[STRSIZE]=" ";
    int estado = 0;
    int preco = 0, peso = 0, qtd = 0;
    size_input = strlen(input);
   
    for (i = 0; i < size_input; i++) {
        if (estado == 0) {
            if (i > 1 && input[i] != ' ' && input[i] != ':') {
                descricao[j] = input[i];
                j++;
            }
        } else if (estado == 1 && (input[i] >= '0' && input[i] <= '9'))
            preco = preco * 10 + put_n(input[i]);
        else if (estado == 2 && (input[i] >= '0' && input[i] <= '9'))
            peso = peso * 10 + put_n(input[i]);
        else if (estado == 3 && (input[i] >= '0' && input[i] <= '9'))
            qtd = qtd * 10 + put_n(input[i]);

        if (input[i] == ':')
            estado++;
    }
    prod.idp = cont_prod;
    strcpy(prod.nome, descricao);
    prod.peso = peso;
    prod.preco = preco;
    prod.qtd = qtd;
    printf("Novo produto %d.\n", prod.idp);  
    produtos[cont_prod] = prod;
   
  
    cont_prod++;

}



void comando_q() {
    /*adiciona stock a um produto existente no sistema*/
    int idp, qtd;
    auxStr();
    idp = first;
    qtd = second;
    if (idp>=cont_prod)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        produtos[idp].qtd += qtd;
}



void comando_N() {
    /*cria uma nova encomenda*/
    encomenda enco;
    int i=0;
    enco.index_prod = 0;
    
    for(i=0;i<ENCO_MAX_PROD;i++){
        enco.vetProd[i].idp=-2;
    }
    enco.ide = cont_enco;
    encomendas[cont_enco] = enco;
    printf("Nova encomenda %d.\n", cont_enco);
    cont_enco++;

}



void comando_A() {
    /*adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, 
      adiciona a nova quantidade a quantidade existente 
    */
    int ide=0, idp=0, qtd=0;
       

    auxStr();
    ide = first;
    idp = second;
    qtd = third;
   

    if (ide>=cont_enco) 
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp>=cont_prod) 
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if ((produtos[idp].qtd - qtd)<0 ) 
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if ((pesoEnco(ide) + ((produtos[idp].peso) * qtd)) > 200) 
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
     else {
        int i , found=0;
        encomenda enco = encomendas[ide];
        produto prod = produtos[idp];
        for (i = 0; i < enco.index_prod; i++) {
            if (prod.idp== enco.vetProd[i].idp){
                enco.vetProd[i].qtd+=qtd;
                encomendas[ide] = enco;
                prod.qtd = prod.qtd - qtd;
                produtos[idp]=prod;
                found++;
                break;
            }
        }
        if(found == 0){
            for(i = 0; i < enco.index_prod; i++){/*escreve por cima duma encomenda removida*/
               if (enco.vetProd[i].idp==-1) {
                prod.qtd=qtd;
                enco.vetProd[i] = prod ;
                produtos[idp].qtd = produtos[idp].qtd - qtd;
                encomendas[ide] = enco;
                found++;
                break;
               }
            }
        } if (found == 0) {
            prod.qtd = qtd;
            enco.vetProd[enco.index_prod] = prod;
            produtos[idp].qtd = produtos[idp].qtd - qtd;
            enco.index_prod++;
            encomendas[ide] = enco;
             

        }

    }

}
    

void comando_r() {
    /*remove stock a um produto existente*/
    int idp, qtd;
    auxStr();
    idp = first;
    qtd = second;

    if (idp>=cont_prod) 
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
     else {

        if ((produtos[idp].qtd - qtd) < 0) 
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        else
            produtos[idp].qtd = produtos[idp].qtd - qtd;

    }

}

void comando_R() {
    /*remove produto de uma encomenda*/
    int ide, idp;
    auxStr();
    ide = first;
    idp = second;
    if (ide>=cont_enco) 
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
     else if (idp>=cont_prod) 
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
     else {
        int i;
        encomenda enco = encomendas[ide];
        for (i = 0; i < enco.index_prod; i++) {
            if (produtos[idp].idp==enco.vetProd[i].idp){
                
                produtos[idp].qtd+=enco.vetProd[i].qtd;
                enco.vetProd[i].qtd= 0;
                enco.vetProd[i].idp=-1;
                encomendas[ide] = enco;
                break;
            }
        }

    }
}

void comando_C() {
    /*calcula o custo de uma encomenda*/
    int ide;
    auxStr();
    ide = first;
    if (ide>=cont_enco) 
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else {
        int i, soma = 0;
        encomenda enco = encomendas[ide];
        for (i = 0; i <enco.index_prod; i++)
             soma += (enco.vetProd[i].preco * enco.vetProd[i].qtd);
        printf("Custo da encomenda %d %d.\n", ide, soma);

    }
}

void comando_p() {
    /*altera preco de um produto existente no sistema*/
    int novoP, idp;
    auxStr();
    idp = first;
    novoP = second;
    
    if (idp>=cont_prod) 
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
   else {
        
        int j, i;
        encomenda enco;
        produtos[idp].preco = novoP;
        for (i = 0; i < cont_enco; i++) {
            enco=encomendas[i];
            for (j = 0; j < enco.index_prod; j++) {
              if (produtos[idp].idp==enco.vetProd[j].idp) {
                    enco.vetProd[j].preco=novoP;
                    encomendas[i]=enco;
                }
            }
        }
    }
}

void comando_E() {
    /*lista a descricao e a quantidade de um produto numa encomenda */
    int ide, idp;
    auxStr();
    ide = first;
    idp = second;
    if (ide>=cont_enco) 
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
     else if (idp>=cont_prod) 
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
     else {
        encomenda enco = encomendas[ide];
        produto prod;
        int i,found=0;
        for (i = 0; i < enco.index_prod; i++) {
            if (produtos[idp].idp==enco.vetProd[i].idp){
                  prod = enco.vetProd[i];                    
                  found++;
                  printf("%s %d.\n", prod.nome, prod.qtd);
                  break;
            }
        }
        if(found==0)
            printf("%s 0.\n",produtos[idp].nome);
        
    }
}

void comando_m() {
    /*
    lista o identificador da encomenda em que o produto dado ocorre mais vezes.
     Se houver 2 ou mais encomendas nessa situacao,
     dever? imprimir a encomenda de menor id. 
      */
    int idp;
    auxStr();
    idp = first;
    if (idp>=cont_prod) 
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else {
        encomenda enco;
        int ide;
        int found = 0;
        int maior = 0;
        int i, j;

        for (i = 0; i < cont_enco; i++) {
            enco = encomendas[i];
            for (j = 0; j < enco.index_prod; j++) {
                if (idp == enco.vetProd[j].idp) {
                    found++;
                    if (enco.vetProd[j].qtd == maior) {
                        if (enco.ide < ide) {
                            ide = enco.ide;
                        }
                    }
                    if (enco.vetProd[j].qtd > maior) {
                        ide = enco.ide;
                        maior = enco.vetProd[j].qtd;
                    }
                }
            }
        }

        if (found > 0)
            printf("Maximo produto %d %d %d.\n", idp, ide, maior);
        
        
            

    }

}

void comando_l() {
    /*lista todos os produtos existentes no sistema por ordem crescente de preco. 
    Se houver 2 ou mais produtos com o mesmo preco, 
    devera imprimir esses por ordem crescente de id de produto */
    produto prod_aux;
    produto vet[MAX_PROD];
    int i;
    int j;
    for (i = 0; i < cont_prod; i++) 
        vet[i] = produtos[i];
    
    for (i = 0; i < cont_prod; i++) {
        for (j = i + 1; j < cont_prod; j++) {
            if (vet[i].preco > vet[j].preco) {
                prod_aux = vet[i];
                vet[i] = vet[j];
                vet[j] = prod_aux;
            } else if (vet[i].preco == vet[j].preco) {
                if (vet[i].idp > vet[j].idp) {
                    prod_aux = vet[i];
                    vet[i] = vet[j];
                    vet[j] = prod_aux;
                }
            }

        }
    }
    printf("Produtos\n");
    for (i = 0; i < cont_prod; i++)
        printf("* %s %d %d\n", vet[i].nome, vet[i].preco, vet[i].qtd);

}

void comando_L() {
    /*lista todos os produtos de uma encomenda 
    por ordem alfabetica*/
    int ide;
    auxStr();
    ide = first;

    if (ide>=cont_enco) 
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
     else {
        int j, i, cont = 0;
        produto prod_aux;
        encomenda enco = encomendas[ide];
        produto vet[ENCO_MAX_PROD];

        for (i = 0; i < enco.index_prod; i++) {
            if (enco.vetProd[i].idp >= 0) {
                vet[cont] = enco.vetProd[i];
                cont++;
            }
        }

        for (i = 0; i < cont; i++) {
            for (j = i + 1; j < cont; j++) {
                if ((strcmp(vet[i].nome, vet[j].nome)) > 0) {
                    prod_aux = vet[i];
                    vet[i] = vet[j];
                    vet[j] = prod_aux;
                }
            }
        }
        printf("Encomenda %d\n", ide);
        for (i = 0; i < cont; i++)
            printf("* %s %d %d\n", vet[i].nome, vet[i].preco, vet[i].qtd);

    }

}




