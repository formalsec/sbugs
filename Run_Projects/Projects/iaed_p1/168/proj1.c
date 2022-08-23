#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P_MAX 10000     /* Numero maximo de produtos no sistema         */
#define E_MAX 500       /* Numero maximo de encomendas no sistema       */
#define PESO_MAX 200    /* Peso maximo de cada encomenda                */
#define DESC_MAX 64     /* Tamanho maximo da descricao de cada produto  */

/* Contador global de produtos no sistema   */
int cont_idp = 0;
/* Contador global de encomendas no sistema */
int cont_ide = 0;

typedef struct produto          /* Estrutura produto    */
{
    int idp, preco, peso, qtd;  /* Respetivo identificador, preco, peso, quantidade */
    char desc[DESC_MAX];        /* e descricao de cada produto  */
}produto;

typedef struct encomenda        /* Estrutura encomenda  */
{
    int ide, cont_prod;         /* Respetivo identificador e contador de produtos da encomenda  */
    produto produtos[PESO_MAX]; /* Vetor dos produtos pertencentes 'a encomenda */

}encomenda;

/* Vetor global dos produtos do sistema */
produto stock[P_MAX] = {0};
/* Vetor global das encomendas do sistema */
encomenda encomendas[E_MAX] = {0};

/* Devolve 1 caso o produto em questao exista no sistema, 0 caso nao */
int produtoExiste(int idp)
{
    if(idp >= cont_idp){
        return 0;
    }else{
        return 1;
    }
}

/* Devolve 1 caso a encomenda em questao exista no sistema, 0 caso nao */
int encomendaExiste(int ide)
{
    if(ide >= cont_ide){
        return 0;
    }else{
        return 1;
    }
}

/* Devolve o peso da encomenda em questao */
int pesoEncomenda(encomenda e)
{
    int i, peso = 0;

    for(i = 0; i < e.cont_prod; i++)
        peso += (e.produtos[i].peso * e.produtos[i].qtd);
    
    return peso;
}

/* Vetor auxiliar utilizado pela funcao merge */
produto aux[P_MAX];

/* Ordena o vetor a[left...right], a partir dos vetores ordenados a[left...m] e a[m+1...right] */
void merge(produto a[], int left, int m, int right, char c)
{
    int i, j, k;
    
    for(i = m+1; i > left; i--)     /*************************/
        aux[i-1] = a[i-1];          /* Construir o vetor aux */
    for(j = m; j < right; j++)      /*************************/
        aux[right+m-j] = a[j+1];

    if(c == 'l'){                     /* <<--      Ordenar por preco ou por descricao   */
        for(k = left; k <= right; k++)          /* dependendo da funcao q chama o sort  */
            if(aux[j].preco < aux[i].preco)
                a[k] = aux[j--];
            else if(aux[j].preco > aux[i].preco)
                a[k] = aux[i++];
            else if(aux[j].idp < aux[i].idp)
                a[k] = aux[j--];
            else
                a[k] = aux[i++];
    }else{
        for(k = left; k <= right; k++)
            if(aux[j].desc[0] < aux[i].desc[0])
                a[k] = aux[j--];
            else if(aux[j].desc[0] > aux[i].desc[0])
                a[k] = aux[i++];
            else if(aux[j].desc[1] < aux[i].desc[1])
                a[k] = aux[j--];
            else
                a[k] = aux[i++];
    }    
}

/* Merge Sort, identico ao dado na aula */
void mergesort(produto a[], int left, int right, char c)
{                                           /*   ^~~~~~                 */
    int m = (right + left) / 2;             /* Carater que representa   */
                                            /* a funcao 'l' ou 'L'      */
    if(right <= left) return;               /* Utilizado pelo merge     */
    
    mergesort(a, left, m, c);
    mergesort(a, (m + 1), right, c);
    
    merge(a, left, m, right, c);    
}

/* Cria um novo produto com as caracteristicas introduzidas */
void a()
{
    char desc[DESC_MAX];
    int preco, peso, qtd;

    produto novo_produto;

    scanf(" %[^:]:%d:%d:%d", desc, &preco, &peso, &qtd); 

    /* Inicializa o produto com os dados recebidos */
    strcpy(novo_produto.desc, desc);
    novo_produto.preco = preco;
    novo_produto.peso = peso;
    novo_produto.qtd = qtd;
    novo_produto.idp = cont_idp;

    /* Adiciona o novo produto ao vetor global de produtos do sistema */
    stock[novo_produto.idp] = novo_produto;
    
    printf("Novo produto %d.\n", novo_produto.idp);

    cont_idp++; 
}

/* Adiciona stock a um produto existente */
void q()
{
    int idp, qtd;

    scanf(" %d:%d", &idp, &qtd);

    if(produtoExiste(idp)){
        /* Caso o produto exista, adiciona a respetiva quantidade ao stock */
        stock[idp].qtd += qtd;
    }else{
        /* Caso contrario levanta o respetivo erro */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

/* Cria uma nova encomenda*/
void N()
{
    encomenda nova_encomenda;

    /* Inicializa a encomenda */
    nova_encomenda.ide = cont_ide;
    nova_encomenda.cont_prod = 0;

    /* Adiciona a nova encomenda ao vetor global de encomendas do sistema */
    encomendas[nova_encomenda.ide] = nova_encomenda;

    printf("Nova encomenda %d.\n", nova_encomenda.ide);
    
    cont_ide++;
}

/* Adiciona um produto a uma encomenda */
void A()
{
    int ide, idp, qtd, i;

    scanf(" %d:%d:%d", &ide, &idp, &qtd);

    /* Verifica se a encomenda ja foi criada */
    if(!encomendaExiste(ide)){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    /* Verifica se o produto ja foi criado */    
    }else if(!produtoExiste(idp)){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    /* Verifica se existe stock suficiente */
    }else if(stock[idp].qtd < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);

    /* Verifica se a adicao excede o peso maximo permitido */
    }else if((pesoEncomenda(encomendas[ide]) + stock[idp].peso * qtd) > PESO_MAX){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
   
    }else{
        /* Variavel de estado que regista se o produto foi encontrado */
        int FOUND = 0;        
        
        /* Verificar se este idp pertence a um dos produtos da encomenda */
        for(i = 0; i < encomendas[ide].cont_prod; i++){
            if(encomendas[ide].produtos[i].idp == idp){
                /* Adicionar qtd */
                encomendas[ide].produtos[i].qtd += qtd;
                stock[idp].qtd -= qtd;
                
                /* Regista que o produto foi encontrado */
                FOUND = 1;
            }
        }    

        /* Caso o produto ainda nao existir na encomenda */
        if(!FOUND){
            encomendas[ide].produtos[encomendas[ide].cont_prod] = stock[idp];

            encomendas[ide].produtos[encomendas[ide].cont_prod].qtd = qtd;

            stock[idp].qtd -= qtd;

            encomendas[ide].cont_prod++;
        }  
    }  
}

/* Remove stock a um produto */
void r()
{
    int idp, qtd;

    scanf(" %d:%d", &idp, &qtd);

    if(produtoExiste(idp)){
        /* Caso o produto exista remove o stock pretendido, caso haja suficiente para tal */
        if((stock[idp].qtd - qtd) >= 0){
            stock[idp].qtd -= qtd;
        }else{
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
    }else{
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
}

/* Remove um produto de uma encomenda */
void R()
{
    int idp, ide, i, FOUND = 0;

    scanf(" %d:%d", &ide, &idp);

    if(!encomendaExiste(ide)){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }else if(!produtoExiste(idp)){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }else{
        /* Encontra o indice i do produto a remover */
        for(i = 0; i < encomendas[ide].cont_prod; i++){
            if(encomendas[ide].produtos[i].idp == idp){
                /* Regista que o produto foi encontrado */
                FOUND = 1;
                break;
            }
        }

        if(FOUND){
            /* Repoe a quantidade do produto em stock */
            stock[idp].qtd += encomendas[ide].produtos[i].qtd;

            /* "Empurra" todos os restantes produtos para cima */
            while(i+1 <= encomendas[ide].cont_prod){
                encomendas[ide].produtos[i] = encomendas[ide].produtos[i+1];

                i++;
            }

            encomendas[ide].cont_prod--;
        }
    }
}

/* Calcula o custo de uma encomenda */
void C()
{
    int ide, i, total = 0;

    scanf(" %d", &ide);

    if(encomendaExiste(ide)){
        /* Calcula o custo da encomenda caso ela exista */
        for(i = 0; i < encomendas[ide].cont_prod; i++)
            total += (encomendas[ide].produtos[i].qtd * encomendas[ide].produtos[i].preco);

        printf("Custo da encomenda %d %d.\n", ide, total);
    }else{
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
}

/* Altera o pre?o de um produto existente no sistema */
void p()
{
    int idp, preco, i, j;

    scanf(" %d:%d", &idp, &preco);

    if(produtoExiste(idp)){
        /* Altera o preco no stock global */
        stock[idp].preco = preco;

        /* Altera o preco caso o produto esteja nalguma encomenda */
        for(i = 0; i < cont_ide; i++){
            for(j = 0; j < encomendas[i].cont_prod; j++){
                if(encomendas[i].produtos[j].idp == idp){
                    encomendas[i].produtos[j].preco = preco;
                }
            }
        }


    }else{
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
}

/* Lista a descricao e a quantidade de um produto numa encomenda */
void E()
{
    int ide, idp, i, FOUND = 0;

    scanf(" %d:%d", &ide, &idp);

    if(!encomendaExiste(ide)){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }else if(!produtoExiste(idp)){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }else{
        /* Encontra o indice i do produto a listar */
        for(i = 0; i < encomendas[ide].cont_prod; i++){
            if(encomendas[ide].produtos[i].idp == idp){
                /* Regista que o produto foi encontrado */
                FOUND = 1;
                break;
            }
        }
        if(FOUND){
            printf("%s %d.\n", encomendas[ide].produtos[i].desc, encomendas[ide].produtos[i].qtd);
        }else{
            printf("%s 0.\n", stock[idp].desc);
        }
    }
}

/* Lista o ide da encomenda em que dado produto ocorre mais vezes */
void m()
{
    int idp, i, j, FOUND = 0;
    int max_qtd[2] = {0}; /* Guarda o ide da encomenda com a maior qtd, e a respetiva qtd */

    scanf(" %d", &idp);

    if(!produtoExiste(idp)){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }else{
        for(i = 0; i < cont_ide; i++){                      /* Percorre todos os produtos   */
            for(j = 0; j < encomendas[i].cont_prod; j++){   /* de todas as encomendas       */
                if(encomendas[i].produtos[j].idp == idp){
                    /* Caso o produto em questao pertenca a dada encomenda*/
                    if(encomendas[i].produtos[j].qtd > max_qtd[1]){
                        /* Caso a sua quantidade na encomenda seja maior do que a maior */
                        /* ate entao registada, atualiza os valores maximos */
                        max_qtd[0] = i;
                        max_qtd[1] = encomendas[i].produtos[j].qtd;
                    }
                    /* Regista que o produto foi encontrado pelo menos uma vez */
                    FOUND = 1;
                }
            }
        }

        if(FOUND){
            printf("Maximo produto %d %d %d.\n", idp, max_qtd[0], max_qtd[1]);
        }
    }
}

/* Lista todos os produtos existentes */
void k()
{
    int i;
    
    printf("Produtos\n");

    for(i = 0; i < cont_idp; i++)
        /* Percorre todos os produtos do sistema pela ordem de identificadores */
        printf("* %s %d %d\n", stock[i].desc, stock[i].preco, stock[i].qtd);
}

/* Lista todos os produtos de uma encomenda */
void K()
{
    int ide, i;

    scanf(" %d", &ide);

    printf("Encomenda %d\n", ide);

    for(i = 0; i < encomendas[ide].cont_prod; i++)
        /* Percorre todos os produtos da encomenda em questao pela ordem de introducao */
        printf("* %s %d %d\n", encomendas[ide].produtos[i].desc, encomendas[ide].produtos[i].preco, encomendas[ide].produtos[i].qtd);
}

/* Lista os produtos existentes por ordem crescente de preco */
void l()
{
    /* Vetor de produtos que vai ser ordenado */
    produto produtos[P_MAX];

    int i;

    /* Copia todos os produtos do sistema para o vetor 'produtos' */
    for(i = 0; i < cont_idp; i++)
        produtos[i] = stock[i];

    /* Ordena o vetor */
    mergesort(produtos, 0, cont_idp-1, 'l');

    printf("Produtos\n");
    /* Percorre o vetor agora ordenado */
    for(i = 0; i < cont_idp; i++)
        printf("* %s %d %d\n", produtos[i].desc, produtos[i].preco, produtos[i].qtd);
}

/* Lista os produtos de uma encomenda por ordem alfab?tica */
void L()
{
    int i, ide;
    /* Vetor de produtos que vai ser ordenado */
    produto produtos[PESO_MAX];

    scanf(" %d", &ide);

    if(encomendaExiste(ide)){
        /* Copia todos produtos da encomenda para o vetor 'produtos' */
        for(i = 0; i < encomendas[ide].cont_prod; i++)
            produtos[i] = encomendas[ide].produtos[i];

        /* Ordena o vetor */
        mergesort(produtos, 0, encomendas[ide].cont_prod-1, 'L');

        printf("Encomenda %d\n", ide);
        /* Percorre o vetor agora ordenado */
        for(i = 0; i < encomendas[ide].cont_prod; i++)
            printf("* %s %d %d\n", produtos[i].desc, produtos[i].preco, produtos[i].qtd);
    }else{
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}

int main()
{
    char com;

    /* Le os comandos introduzidos e chama as respetivas funcoes */
    while ((com = getchar()) != 'x')
    {
        switch (com) {
            case 'a':
                a();
                break;
            
            case 'q':
                q();
                break;
            
            case 'N':
                N();
                break;
            
            case 'A':
                A();
                break;
            
            case 'R':
                R();
                break;
            
            case 'r':
                r();
                break;
            
            case 'C':
                C();
                break;
            
            case 'p':
                p();
                break;
            
            case 'E':
                E();
                break;
            
            case 'm':
                m();
                break;
            
            case 'k':
                k();
                break;
            
            case 'K':
                K();
                break;
            
            case 'l':
                l();
                break;
            
            case 'L':
                L();
                break;
            
            default:
                break;
        }
    }

    return 0;
}
