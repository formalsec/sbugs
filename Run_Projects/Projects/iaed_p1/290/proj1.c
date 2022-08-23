#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Descricao_max 64               /*constantes usadas*/
#define Encomendas_max 500
#define Produtos_max 10000
#define Peso_max 200

typedef struct{                             /*Estrutura Produto*/
    int id;                                 /*Identificador do produto*/
    int check;                              /*O Check atribui o valor de 1 se o produto existir (na criacao do produto)*/
    int preco;                              /*Pre?o do produto*/
    int peso;                               /*Peso*/
    int stock;                              /*Stock do produto*/
    char descricao[Descricao_max];          /*Descricao/Nome do produto*/
}struc;

typedef struct{                             /*Estrutura Encomenda*/
    int id;                                 /*Identificador da Encomenda*/
    int peso;                               /*Peso da Encomenda*/
    int check;                              /*O Check atribui o valor de 1 se a encomenda existir (na criacao da encomenda)*/
    struc produto[Produtos_max];
}encom;

struc produtos[Produtos_max];               /*Criacao das estruturas produtos e encomendas*/
encom encomendas[Encomendas_max];

    int main(){
        char d;
        int a,b,c,i=0,e=0,count=0;
            do{
                switch(d=getchar())
                {
                    case 'a':{                                                                                                      /*A funcao "a" adiciona um produto ao sistema*/
                        getchar();                                                                                                  /*"Tira" o primeiro espa?o depois do "a"*/
                        scanf("%[^:]:%d:%d:%d",produtos[i].descricao,&produtos[i].preco,&produtos[i].peso,&produtos[i].stock);
                        printf("Novo produto %d.\n",i);
                        produtos[i].check=1;                     /*O Check do produto criado fica a 1*/
                        produtos[i].id=i;
                        count+=1;                               /*Contador do numero de produtos criados*/
                        i++;
                        break;}

                    case 'q':{                                  /*Adiciona stock b ao produto a.*/
                        scanf("%d:%d",&a,&b);
                        if(produtos[a].check)
                            {
                                produtos[a].stock+=b;
                            }else
                                printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",a);
                        break;}

                    case 'N':{                                      /*Cria uma Nova Encomenda*/
                            printf("Nova encomenda %d.\n",e);
                            encomendas[e].check=1;                  /*O Check da encomenda criada fica a 1*/
                            encomendas[e].id=e;
                            e++;

                        break;}

                    case 'A':{                                                                                              /*Adiciona um produto a encomenda*/
                            scanf("%d:%d:%d",&a,&b,&c);
                            if(encomendas[a].check)
                                {                                                                        /*Se a encomenda existir (isto ?, se o check for 1)*/
                                    if(produtos[b].check)
                                    {                                                                  /*Se o produto inserido na encomenda existir no sistema*/
                                        if(c<=produtos[b].stock)
                                        {
                                            encomendas[a].peso+=(produtos[b].peso)*c;
                                            if(encomendas[a].peso<=Peso_max)
                                            {
                                                strcpy(encomendas[a].produto[b].descricao,produtos[b].descricao);               /*Condicoes para verificar que o produto inserido na encomenda*/
                                                encomendas[a].produto[b].preco=produtos[b].preco;                               /*apresenta todas as condicoes*/
                                                encomendas[a].produto[b].peso=produtos[b].peso;
                                                encomendas[a].produto[b].id=b;
                                                encomendas[a].produto[b].stock+=c;
                                                produtos[b].stock-=c;
                                                encomendas[a].produto[b].check=1;
                                            }else
                                                {
                                                    encomendas[a].peso-=(produtos[b].peso)*c;
                                                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",b,a);
                                                }
                                        }else
                                            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",b,a);
                                    }else
                                        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",b,a);
                            }else
                                printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",b,a);
                        break;}

                    case 'r':{                                                                                                      /*Remove stock de um produto do sistema*/
                        scanf("%d:%d",&a,&b);
                        if(produtos[a].check)
                            {
                                if(produtos[a].stock-b<0)
                                {
                                    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",b,a);
                                }else
                                    produtos[a].stock=produtos[a].stock-b;
                            }else
                                printf("Impossivel remover stock do produto %d. Produto inexistente.\n",a);
                        break;}

                    case 'R':{                                                                                              /*Remove um produto da encomenda*/
                            scanf("%d:%d",&a,&b);
                            if(encomendas[a].check)
                                {
                                    if(produtos[b].check)
                                    {
                                        encomendas[a].produto[b].check=0;                                                   /*Ao remover o produto da encomenda, o check do produto na encomenda pasa a 0*/
                                        produtos[b].stock+=encomendas[a].produto[b].stock;
                                        encomendas[a].peso-=(produtos[b].peso)*(encomendas[a].produto[b].stock);
                                        encomendas[a].produto[b].stock=0;

                                    }else
                                        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",b,a);
                                }else
                                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",b,a);
                        break;}

                    case 'C':{                                                                                  /*Calcula o custo de uma encomenda*/
                            scanf("%d",&a);
                            if(encomendas[a].check)
                                {
                                    int j,custo=0;
                                    for(j=0;j<Produtos_max;j++)
                                    {
                                        custo+=(produtos[j].preco)*(encomendas[a].produto[j].stock);          /*Multiplica o pre?o do produto por cada unidade no stock da encomenda*/
                                    }
                                    printf("Custo da encomenda %d %d.\n",a,custo);
                                }else
                                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",a);
                        break;}

                    case 'p':{                                                                          /*Altera o preco de um produto no sistema*/
                            scanf("%d:%d",&a,&b);
                            if(produtos[a].check)
                                {
                                    produtos[a].preco=b;
                                }else
                                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",a);
                        break;}

                    case 'E':{                                                                      /*Exibe a descricao e a quantidade de um produto b na encomenda a*/
                            scanf("%d:%d",&a,&b);
                            if(encomendas[a].check)
                                {
                                    if(produtos[b].check)
                                    {
                                        printf("%s %d.\n",produtos[b].descricao,encomendas[a].produto[b].stock);
                                    }else
                                        printf("Impossivel listar produto %d. Produto inexistente.\n",b);
                                }else
                                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",a);

                        break;}

                    case 'm':{                                                          /*Mostra a encomenda em que o produto a se encontra em maior quantidade. Se existirem 2 encomendas,*/
                            int l,o,maior=0;                                            /*com a mesma quantidade, mostra a de menor id*/
                            scanf("%d",&a);
                            if(produtos[a].check)
                                {
                                    for(l=0;l<Encomendas_max;l++)
                                        {
                                            if(encomendas[l].produto[a].check)                 /*Se o produto existir na encomenda*/
                                                if(encomendas[l].produto[a].stock>maior)
                                                    {
                                                        maior=encomendas[l].produto[a].stock;
                                                        o=encomendas[l].id;
                                                    }
                                        }
                                if(maior==0)                                                    /*ou seja, se nao existir o produto designado na encomenda*/
                                    {
                                        break;
                                    }else
                                        printf("Maximo produto %d %d %d.\n",a,o,maior);
                                }else
                                    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",a);

                        break;}

                    case 'l':{                                                            /*Lista os produtos por ordem crescente de pre?o*/
                        struc temp,arr[Produtos_max];
                        int i,j;
                        for(i=0;produtos[i].check!=0;i++)                                 /*Para os produtos que existem no sistema*/
                            {
                            arr[i].check=1;
                            strcpy(arr[i].descricao,produtos[i].descricao);              /*Cria-se uma estrutura temporaria com os produtos existentes no sistema*/
                            arr[i].id=produtos[i].id;
                            arr[i].stock=produtos[i].stock;
                            arr[i].preco=produtos[i].preco;
                            arr[i].peso=produtos[i].peso;
                            }
                        for(i=1;i<count;i++)
                            for(j=0;j<count-i;j++)
                                {
                                    if(arr[j].preco>arr[j+1].preco)                                     /*Bubble sort para ordenar os produtos por ordem crescente de preco*/
                                    {
                                        temp=arr[j];
                                        arr[j]=arr[j+1];
                                        arr[j+1]=temp;
                                    }
                            }
                        printf("Produtos\n");
                        for (i = 0; i < count; i++)                                                     /*Loop que da printf dos produtos da estrutura temporaria, ja ordenados*/
                            {
                                printf("* %s %d %d\n",arr[i].descricao,arr[i].preco,arr[i].stock);
                            }
                        break;}

                    case 'L':{                                                              /*Lista os produtos numa encomenda por ordem crescente da descricao/nome dos produtos*/
                        struc temp,arr[Produtos_max];
                        int i,j;
                        scanf("%d",&a);
                        if(encomendas[a].check)
                            {
                                for(j=0;j!=Produtos_max;j++)
                                    {
                                        arr[j].check=encomendas[a].produto[j].check;                                                /*Cria-se novamente uma estrutura temporaria*/
                                        strcpy(arr[j].descricao,encomendas[a].produto[j].descricao);
                                        arr[j].id=encomendas[a].produto[j].id;
                                        arr[j].peso=encomendas[a].produto[j].peso;
                                        arr[j].preco=encomendas[a].produto[j].preco;
                                        arr[j].stock=encomendas[a].produto[j].stock;
                                    }
                                for(i=1;i<count;i++)
                                    for(j=0;j<count-i;j++)
                                        {
                                            if(strcmp(arr[j].descricao,arr[j+1].descricao)>0 || strlen(arr[j].descricao)==0)        /*Usa-se o strcmp para comparar as descricoes.*/
                                                {
                                                temp=arr[j];
                                                arr[j]=arr[j+1];                                                                    /*Bubble sort para ordenar*/
                                                arr[j+1]=temp;
                                                }
                                        }

                            printf("Encomenda %d\n",a);
                            for (i = 0;arr[i].check!=0;i++)
                                {
                                printf("* %s %d %d\n",arr[i].descricao,arr[i].preco,encomendas[a].produto[arr[i].id].stock);        /*Printf dos produtos da encomenda a por ordem crescente*/
                                }
                            }else
                                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",a);
                        break;}
            }
        }while (d!='x');                                                                                                            /*termina o loop se o caracter inserido for "x"*/
        return 0;
    }
