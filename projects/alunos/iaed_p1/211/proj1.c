#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include "info.h"


    /*********Declaration/initialization of global arrays*********/

product products[TOTAL_PROD] = {0};
order orders[TOTAL_ORDERS] = {0};
int z = 0;
product aux[TOTAL_PROD];  /*auxiliary array(mergesortprice)*/
product productscpy[TOTAL_PROD];
order copycost[TOTAL_PROD];



    /*Functions  Definition*/
/*** function that creates and returns a product ***/

product createProduct(char desc[], int price, int weight, int stock)
{

    product aux; /*declaration of an auxiliary variable of type product*/         
    strcpy(aux.desc,desc);
    aux.price = price;
    aux.weight = weight;
    aux.stock = stock;
    aux.standingP = true;
    aux.idp = z;
    return aux;
}

/*** function that creates and returns an order ***/
order createOrder()
{
    int i;
    order aux;   /* declaration of an auxiliary variable of type order*/
    static int product_counter = 0;
    aux.ide = product_counter;
    aux.price = ZERO;
    aux.weightOrder = ZERO;
    for(i =0; i< MAX_WEIGHT;i++)
    {
        aux.products[i] = products[i];
    }
    aux.standingO = true;
    ++product_counter;
    return aux;


}

/**** function that evaluates the stock of a product ****/
int stockEvaluate(int idp,int stock)
{
    /*difference between the existing amount and the given */
    return  products[idp].stock - stock;
    
}

 

void a(char desc[],int price,int weight ,int stock) 
{
   if((z>= ZERO && z< TOTAL_PROD) && (strlen(desc)<= DESCRIPTION) &&(price > ZERO) && (weight > ZERO) && (stock >= ZERO))
   {
        printf("Novo produto %d.\n",z);
        products[z] = createProduct(desc,price,weight,stock);
        products[z].standingP = true;
        z++;
   } 
}



 /****************************function that adds stock to an existing product,r command*************************/
void q(int idp,int stock)   
{
    
    if(products[idp].standingP == true)
    {
         products[idp].stock += stock;
    }
    else
    {
       printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
    }
    
}


void N() /*function responsible for creating a new order, N command */
{
    static int k = 0;
    orders[k] = createOrder();
    printf("Nova encomenda %d.\n",orders[k].ide);
    k++;
}



/********************function that adds a given product to a given order**************************************/

void A(int ide,int idp,int stock)
{
   
    orders[ide].weightOrder =(products[idp].weight *stock + orders[ide].weightOrder); /*the initial value of the order if the product and the stock selected was added*/
    if(orders[ide].standingO == false ) /* verifies whether or not the given order exists*/
    {
        
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        orders[ide].weightOrder = (products[idp].weight*stock - orders[ide].weightOrder); 
         
    }
    else if(products[idp].standingP == false) /*verifies if the given product exists in the system*/
    {
         
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
         orders[ide].weightOrder = (products[idp].weight*stock - orders[ide].weightOrder); 
    }
    else if(stockEvaluate(idp,stock)< ZERO)  /*evaluates whether or not theres enough stock to be added to the order */
    {
         
         printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
          orders[ide].weightOrder = (products[idp].weight*stock - orders[ide].weightOrder); 
    }
    else if(orders[ide].weightOrder > MAX_WEIGHT)
    {  
        orders[ide].weightOrder = (products[idp].weight*stock - orders[ide].weightOrder); 
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
         
         
        /*since the overall weight of the order is above its maximum weight the product and the given stock that were previoulsy added have to 
        be removed */
    }
    else
    {
         if(( orders[ide].verifier[idp] == false) && (orders[ide].weightOrder <=MAX_WEIGHT)) /*verifies whether or not the product exists in a given order*/
        {
            orders[ide].products[idp] = products[idp];
            orders[ide].products[idp].stock = stock;
            products[idp].stock -= stock;
            orders[ide].verifier[idp] = true; /*the product is now present in the given order*/
            
        }
        else if((orders[ide].verifier[idp] == true) && (orders[ide].weightOrder <=MAX_WEIGHT))/*in this scenario the product is already in the order*/
        {                                                                                     /* an the given stock is added to the existing*/
            orders[ide].products[idp].stock += stock;
            products[idp].stock -= stock;
        }
        else
        {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
        }
        
    }     
}   

 
/****function that removes the stock of a product if certain conditions 
are met */

void r(int idp, int stock) 
{
    if(products[idp].standingP == true)
    {
        if((stockEvaluate(idp,stock)< ZERO))
        {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",stock, idp);
        }
        else
        {
            products[idp].stock -= stock;
        }
    }
    else
    {
       printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp); 
    }
}


/************************* function that removes a product from an order *************************/
void R( int idp, int ide)
{
    if(orders[ide].standingO == true)
    {
        if(products[idp].standingP == true)
        {
            orders[ide].weightOrder -=(products[idp].weight*orders[ide].products[idp].stock); /*the weight of
             order has to be reduced since one of its product was removed */
            products[idp].stock += orders[ide].products[idp].stock; /*the removed stock 
            is added to the original stock of the product*/
            orders[ide].products[idp].stock = ZERO;      
        }
        else
        {
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        }
    }
    else
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }
    
}

/************************* function that computes the total price of an order *************************/
void C(int ide)
{   
    int x,y;
    int total = 0;
    for(x = 0;x<TOTAL_PROD;x++)
    {
        copycost[x] = orders[x]; /*copy of the main array of products*/
    }

    if(copycost[ide].standingO == true) /*verifies if the order exists */
    {
        for(y = 0;y<MAX_WEIGHT;y++)
        {
            if(copycost[ide].products[y].stock != 0 || copycost[ide].products[y].price != 0)
            total += (copycost[ide].products[y].price *copycost[ide].products[y].stock);
        }
        printf("Custo da encomenda %d %d.\n",ide,total);       
       
    }
    else
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);  
    }
   
}

/************************* function that changes the price of a product in the system *************************/
void p(int idp,int price)
{
    int k;
    if(products[idp].standingP == true)  /* verifies if the product with the given id exists*/
    {
      products[idp].price = price; /*the price of the product in the system, is now equal to the given price(in the system)*/
      for(k =0;k<MAX_WEIGHT;k++)/*verifies if the given product is available in any order*/
      {
          if(products[idp].idp == orders[k].products[idp].idp) 
          {
              orders[k].products[idp].price = price; /*the price has now changed in the order*/
          }
      }   
    }
    else
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    }
    
}

/************************* function that list the description and stock of a given product in a given order*************************/
void E(int ide,int idp)
{
    if(orders[ide].standingO == true) /*verifies if the given order exists*/
    {
        if(products[idp].standingP == true) /* verifies whether or not the given id is present in the system*/
        {
            printf("%s %d.\n",orders[ide].products[idp].desc,orders[ide].products[idp].stock);
        }
        else
        {
            printf("Impossivel listar produto %d. Produto inexistente.\n",idp);   
        }  
    }
    else
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }
    

}

/************************* function that lists the id of the order in which a given product has more stock *************************/
void m(int idp)
{   
    if(products[idp].standingP == true)
    {
        int k;/* iteration variable*/
        int m = 0; /* the largest value*/
        int i; /*the index of the largest value*/
        for(k =0; k< TOTAL_ORDERS;k++)
        {
            if(orders[k].products[idp].stock > m) /* verifies if the the number is bigger than the largest case,if so
            ,the largest case is now the number*/
            {
                m = orders[k].products[idp].stock;
                i = k; /*index of the order with the largest amount of stock*/
                
            }
            else if(orders[k].products[idp].stock == m) /*in this scenario the number in stock is equal to largest amount*/
            {
                if(k<i) /*evaluates the iteration variable and the index*/
                {
                   i = k; /*the index value is now equal to  the index k of the orders*/ 
                }
                     
            }
        }
        if(m >ZERO)
        {
            printf("Maximo produto %d %d %d.\n",idp,i,m);
        }
    }
    else
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    }
}

void l(product array[])
{
    int k;
    for(k = 0;k<TOTAL_PROD;k++)
    {
        if(array[k].standingP == true &&  (array[k].price > ZERO))
        {
            printf("* %s %d %d\n",array[k].desc,array[k].price,array[k].stock);
        }
    }
   

}


/********************************Implementation of the sorting algorithm  MERGE SORT *********************************/
void mergesortPrice(product a[],int left,int right)
{
    int m = (right+left)/2;

    if(right<=left)
        return;
    
    mergesortPrice(a,left,m);
    mergesortPrice(a,m+1,right);
    mergePrice(a,left,m,right);
}


void mergePrice(product a[],int left,int m,int right)
{
    int i,j,k;
    for(i = m+1;i >left;i--)
        aux[i-1] = a[i-1];
    for(j = m;j<right;j++)
        aux[right+m-j] = a[j+1];
    for(k =left;k <= right;k++)
        if(aux[j].price< aux[i].price)
            a[k] = aux[j--];
        else if(aux[j].price == aux[i].price)
            if(aux[j].idp < aux[i].idp)
                a[k]= aux[j--];

            else
                a[k] = aux[i++];

        else
            a[k] = aux[i++];
        
            
}
/********************************Implementation of the sorting algorithm  MERGE SORT *********************************/





int main()
{
    int price,weight,stock;
    int ide;
    int idp;
    int x; 
    char desc[DESCRIPTION];
    char input = getchar();


    while((input)!= 'x')
    {   
       
        switch(input)
        {
             /* command to add a new product to the system*/
            case 'a':
                    scanf("%[^:]:%d:%d:%d",desc, &price, &weight, &stock);
                    a(desc,price,weight,stock);
                    break;

            case 'q':  /*command to add stock to an existing product*/
                    scanf("%d:%d",&idp, &stock);
                    q(idp,stock);
                    break;
                
            
            case 'N':   /*command to create a new order */
                        N();
                        break;

            case 'A': /*command to add a product to a certain order,if the product is already in the given order
            the new amount has to be added to the existing  */
                    scanf("%d:%d:%d", &ide, &idp, &stock);
                    A(ide,idp,stock);
                    break;

            case 'r': /* command to remove the stock of a product*/
                    scanf("%d:%d",&idp, &stock);
                    r(idp,stock);
                    break; 

            case 'R': /* command to remove a product from an order*/
                    scanf("%d:%id", &ide, &idp);
                    R(idp,ide);
                    break;
            
            case 'C': /* command to compute the total price of a given order */
                    scanf("%d", &ide);
                    C(ide);
                    break;
            
            case 'p': /* command to change the price of an existing product*/
                    scanf("%d:%d", &idp, &price);
                    p(idp, price); 
                    break; 
            
            case 'E': /*command to list the stock and the description of a product in an order*/
                    scanf("%d:%d",&ide,&idp);
                    E(ide,idp);
                    break; 

            case 'm': /*command to list the id of the order with the biggest amount of a given product*/
                    scanf("%d",&idp);
                    m(idp);
                    break;

            case 'l': /* command to list every product in the system by ascending order of price*/
                    printf("Produtos\n");
                    for(x = 0;x<TOTAL_PROD;x++)
                    {
                        productscpy[x] = products[x]; /*copy of the main array of products*/
                    }
                    mergesortPrice(productscpy,ZERO,TOTAL_PROD-ONE);
                    l(productscpy);
                    break;

                    
            case 'x':
                    break;

        }
        input = getchar();
    }
    return 0;
}
