#include "auxiliar.h"
#include <stdio.h>

/*VARIAVEIS GLOBAIS*/

/*Vetor que guarda todos os prudutos existentes; nao sofre ordena??o*/
Produto produto[MAX_PROD];

/*Vetor que guarda todas as encomendas*/
Encomenda encomenda[MAX_ENC];

/*Vetor que guarda todos os ids dos produtos e a sua quantidade disponivel*/
int stock[MAX_PROD];

/*Vetores auxiliares que guardam variaveis temporarias usadas nos algoritmos de ordenacao*/
int copia_id[MAX_PROD], copia_stock[MAX_PROD];

/*Variaveis que registam quantas encomendas e produtos existem*/
int size_p = 0;
int size_e = 0;

/*DECLARACAO DE FUNCOES*/

void novo_produto();
void adiciona_qtd();
void nova_encomenda();
void adiciona_encomenda();
void remove_qtd();
void remove_prod_encomenda();
void calcula_custo();
void altera_preco();
void atualiza_preco();
void lista_por_preco();
void lista_desc_qtd();
void lista_encomenda_nome();
void lista_maximo();

/*DEFENICAO DE FUNCOES*/

/*
  novo_produto: () -> ()
  Cria um novo produto e adiciona a sua quantidade ao stock disponivel.
*/
void novo_produto(){
    /*Define o id do produto segundo ordem de insercao*/
    produto[size_p].id = size_p;
    
    getchar();
    get_string(produto[size_p].desc);
    scanf("%d:%d:%d",&produto[size_p].preco,&produto[size_p].peso,&produto[size_p].qtd);

    /*Atualiza o stock disponivel do produto*/
    stock[size_p] = produto[size_p].qtd;

    printf("Novo produto %d.\n",size_p);

    /*Incrementa a variavel que resgista quantos produtos existem*/
    size_p++;
}

/*
  adiciona_qtd: () -> ()
  Adiciona quantidade de produto a um produto ja existente.
*/
void adiciona_qtd(){
    int tmp, id;
    
    scanf("%d:%d",&id,&tmp);

    /*Verifica se e possivel realizar a operacao*/
    if(id >= size_p){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
        return;
    }

    /*Adiciona a quantidade inserida ao stock global e ao stock disponivel*/
    produto[id].qtd += tmp;
    stock[id] += tmp;
}

/*
  nova_encomenda: () -> ()
  Cria uma nova encomenda.
*/
void nova_encomenda(){ 
    printf("Nova encomenda %d.\n",size_e);

    /*Incrementa a variavel que regista quantas encomendas existem*/
    size_e++;
}

/*
  adiciona_encomenda: () -> ()
  Adiciona um produto existente a uma encomenda existente. Se o produto
  ja se encontrar na encomenda adiciona a quantidade passada a esse produto na encomenda.
*/
void adiciona_encomenda(){
    int id_enc, id_prod, qtd;

    scanf("%d:%d:%d",&id_enc,&id_prod,&qtd);

    /*Verifica se a encomenda e o produto existem*/
    if(id_enc >= size_e){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return;
    }

    else if(id_prod >= size_p){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return;
    }

    /*Verifica se existe quantidade disponivel suficiente e se a encomenda nao excede o peso maximo*/
    if(qtd > stock[id_prod]){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_prod,id_enc);
        return;
    }

    else if(encomenda[id_enc].peso + (produto[id_prod].peso * qtd) > MAX_PESO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_prod,id_enc);
        return;
    }

    /*Diminui o stock de produto disponivel*/
    stock[id_prod] -= qtd;
    
    /*Verifica se o produto existe na encomenda*/
    if(encomenda[id_enc].pinfo[id_prod].set){
        /*Adiciona a quantidade e atualiza o preco da encomenda*/
        encomenda[id_enc].pinfo[id_prod].qtd += qtd;
        encomenda[id_enc].peso += (qtd * produto[id_prod].peso);
    }

    else{
        /*Cria um pinfo correspondente ao produto na encomenda*/
        encomenda[id_enc].pinfo[id_prod].set = 1;
        encomenda[id_enc].pinfo[id_prod].qtd = qtd;

        /*Atualiza o peso da encomenda*/
        encomenda[id_enc].peso += (qtd * produto[id_prod].peso);

        /*Incrementa a variavel que regista quantos produtos existem na encomenda*/
        encomenda[id_enc].size++;
    }
}

/*
  remove_qtd: () -> ()
  Adiciona um produto existente a uma encomenda existente, adicionando a quantidade
  passada no comando se o produto se econtrar na encomenda.
*/
void remove_qtd(){
    int id_prod, qtd;
    
    scanf("%d:%d",&id_prod,&qtd);

    /*Verifica se o produto existe e se existe quantidade suficiente de produto disponivel*/
    if(id_prod >= size_p){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    if(qtd > stock[id_prod]){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,id_prod);
        return;
    }

    /*Retira a quantidade qtd a quantidade global e disponivel do produto*/
    produto[id_prod].qtd -= qtd;
    stock[id_prod] -= qtd;
}

/*
  remove_prod_encomenda: () -> ()
  Remove um produto de uma encomenda caso o produto exista.
*/
void remove_prod_encomenda(){
    int id_enc, id_prod;
    
    scanf("%d:%d",&id_enc,&id_prod);

    /*Verifica se a encomenda e o produto existem*/
    if(id_enc >= size_e){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return;
    }

    if(id_prod >= size_p){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return;
    }

    /*Verifica se o produto existe na encomenda*/
    if(encomenda[id_enc].pinfo[id_prod].set){
        /*Atualiza o preco*/
        encomenda[id_enc].peso -= encomenda[id_enc].pinfo[id_prod].qtd * produto[id_prod].peso;

        /*Atualiza a quantidade de produto disponivel*/
        stock[id_prod] += encomenda[id_enc].pinfo[id_prod].qtd;

        /*Limpa os registos do produto na encomenda*/      
        encomenda[id_enc].pinfo[id_prod].qtd = 0;
        encomenda[id_enc].pinfo[id_prod].set = 0;

        /*Diminui a veriavel que regista a quantidade de produtos na encomenda*/
        encomenda[id_enc].size--;
    }
}

/*
  calcula_custo: () -> ()
  Calcula o preco de uma encomenda.
*/
void calcula_custo(){
    int id_enc, preco = 0, i;

    scanf("%d",&id_enc);

    /*Verifica se a encomenda existe*/
    if(id_enc >= size_e){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_enc);
        return;
    }

    /*Percorre todos os produtos existentes e se existirem na encomenda 
      adiciona o seu preco unitario * a sua quantidade ao preco final da encomenda*/
    for(i=0; i<size_p; i++)
        if(encomenda[id_enc].pinfo[i].set)
            preco += produto[i].preco * encomenda[id_enc].pinfo[i].qtd;

    printf("Custo da encomenda %d %d.\n",id_enc,preco);
}

/*
  altera_preco: () -> ()
  Altera o preco de um produto.
*/
void altera_preco(){
    int id_prod, preco;

    scanf("%d:%d",&id_prod,&preco);

    /*Verifica se o produto existe*/
    if(id_prod >= size_p){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    /*Atualiza o preco do produto*/
    produto[id_prod].preco = preco;
}

/*
  lista_por_preco: () -> ()
  Imprime a descricao, preco e quantidade disponivel de todos os produtos existentes por ordem de preco. 
  Caso tenham o mesmo preco o quem tem id menor aparece primeiro.
*/
void lista_por_preco(){
    puts("Produtos");

    /*Ordena os produtos e imprime*/
    ordena_counting(produto, size_p, copia_id, ret_preco);
    imprime_ordenado(copia_id, size_p, produto, stock);
}

/*
  lista_desc_qtd: () -> ()
  Imprime a descricao de um produto e a quantidade desse produto numa encomenda.
*/
void lista_desc_qtd(){
    int id_enc, id_prod;

    scanf("%d:%d",&id_enc,&id_prod);

    /*Verifica se a encomenda e o produto existem*/
    if(id_enc >= size_e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);
        return;
    }

    else if(id_prod >= size_p){
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    printf("%s %d.\n",produto[id_prod].desc,encomenda[id_enc].pinfo[id_prod].qtd);            
}

/*
  lista_encomenda_nome: () -> ()
  Imprime a descricao, preco e quantidade disponivel dos produtos existentes numa encomenda
  por ordem de alfabetica da sua descricao.
*/
void lista_encomenda_nome(){
    int id_enc, i, j;

    scanf("%d",&id_enc);

    /*Verifica se a encomenda existe*/
    if(id_enc >= size_e){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);
        return;
    }

    printf("Encomenda %d\n",id_enc);

    /*Cria os vetores que conteem copias dos id dos produtos e da quantidade existente na encomenda*/
    for(i=0, j=0; i<encomenda[id_enc].size; j++){
        if(encomenda[id_enc].pinfo[j].set){
            copia_id[i++] = j;
            copia_stock[j] = encomenda[id_enc].pinfo[j].qtd;
        }
    }

    /*Ordena a lista de id e imprime*/
    ordena_merge(copia_id, 0, encomenda[id_enc].size-1, produto, cmp_str);
    imprime_ordenado(copia_id, encomenda[id_enc].size, produto, copia_stock);
}

/*
  lista_maximo: () -> ()
  Imprime o id do produto, o id da encomenda em qual se encontra em maior quantade 
  e a quantidade maxima desse produto numa encomenda.
*/
void lista_maximo(){
    int id_prod, i, max = 0, ide = 0;

    scanf("%d",&id_prod);

    /*Verifica se o produto existe*/
    if(id_prod >= size_p){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    /*Procura o produto em todas as encomendas*/
    for(i=0; i<size_e; i++){
        if(encomenda[i].pinfo[id_prod].qtd > max && encomenda[i].pinfo[id_prod].set){
            /*Atualiza quantidade maxima*/
            max = encomenda[i].pinfo[id_prod].qtd;

            /*Guarda a encomenda em que o maximo se regista*/
            ide = i;
        }
    }

    /*Se o produto nao existir em nenhuma encomenda nao imprime nada*/
    if(max != 0)
        printf("Maximo produto %d %d %d.\n",id_prod,ide,max);
}
