#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "defines_and_functions.h"


/* global vars, useful in this context*/

    /* these ints define how many of them have been initialized*/
    uint g_total_packages = 0; /* No of added packages*/
    uint g_total_products = 0; /* No of added products*/

    /* initialize an array of packages and products*/
    /* all productos and packages will be */
    /* held and updated in them*/
    package g_array_packages[MAX_PACKAGES] = {0};
    product g_array_product[MAX_IDS] = {0};

/*
    Its main bro o-o
*/

int main()
{   
    return CommandProcess();
}

/*
    CommandProcess
    Desc: Loop that processes the input in console 
    looking for commands
    to then call the recognized functions
*/
int CommandProcess()
{   /* keep processing console until ordered to close*/
    while(TRUE)

    {   
        char io_buf[IOBUF_SIZE];
        char cmd = '\0';
        char desc[DESC_MAX_CHAR] = "";
        int filled;
        uint weight,price,qty,id_encom,id_prod = 0;
        fgets(io_buf,IOBUF_SIZE,stdin);/* get the inputted line into a buffer for processing*/
        filled = sscanf(io_buf,"%c",&cmd);/* check if cmd got correctly filled*/
        if(filled)
        {
            switch(cmd) /* basic parsing of function inputs and calls*/
            {
                case 'a': sscanf(io_buf,"%c %[^:]:%u:%u:%u",&cmd,desc,&price,&weight,&qty);     CreateProd(desc,price,weight,qty); break;
                case 'q': sscanf(io_buf,"%c %u:%u",&cmd,&id_prod,&qty);     AddStock(id_prod,qty); break;
                case 'N': CreateEncomenda(); break;
                case 'A': sscanf(io_buf,"%c %u:%u:%u",&cmd,&id_encom,&id_prod,&qty);    AddProd(id_encom,id_prod,qty); break;
                case 'r': sscanf(io_buf,"%c %u:%u",&cmd,&id_prod,&qty);     RemoveStock(id_prod,qty); break;
                case 'R': sscanf(io_buf,"%c %u:%u",&cmd,&id_encom,&id_prod);    RemoveProd(id_encom,id_prod); break;
                case 'C': sscanf(io_buf,"%c %u",&cmd,&id_encom);    ListEncomTotalPrice(id_encom); break;
                case 'p': sscanf(io_buf,"%c %u:%u",&cmd,&id_prod,&price);   ProdNewPrice(id_prod,price);  break;
                case 'E': sscanf(io_buf,"%c %u:%u",&cmd,&id_encom,&id_prod);    ListDescPrice(id_encom,id_prod); break;
                case 'm': sscanf(io_buf,"%c %u",&cmd,&id_prod);     EncomMaxProd(id_prod); break;
                case 'l': ListProdByPrice(); break;
                case 'L': sscanf(io_buf,"%c %u",&cmd,&id_encom);    ListEncomProdByDesc(id_encom); break;
                case 'x': return 0;
                default: printf("Invalid command!\n"); break;

            }
        }
    }
}

/*
########################################################################
    BASIC OPERATIONS OF DECLARED STRUCTS
########################################################################
*/


/*
    GetProdDesc
    Desc: writes the description of the product given, into the buffer
    Buffer must be of at least DESC_MAX_CHAR lenght
*/
void GetProdDesc(uint id, char* buffer)
{
    strcpy(buffer,g_array_product[id].desc);
    return;
}
/*
    GetProdDescPtr
    Desc: returns a pointer to the product desc array
*/
char * GetProdDescPtr(uint id)
{
    return((char *)g_array_product[id].desc); 
}

/*
    GetProdPeso
    Desc: returns the weight of the given product
*/
uint GetProdPeso(uint id)
{
    return g_array_product[id].weight;
}

/*
    GetProdPrice
    Desc: returns the price of the given product
*/
uint GetProdPrice(uint id)
{
    return g_array_product[id].price;
}

/*
    GetProdutoQty
    Desc: returns the quantity of the given product in stock
*/
uint GetProdutoQty(uint id)
{
    return g_array_product[id].qty;
}

/*
    GetEncomQtyProd
    Desc: returns the number of a given product in a given package
*/
uint GetEncomQtyProd(uint id_encom, uint id_prod)
{
    return g_array_packages[id_encom].products[id_prod][0];
}


/*
    SetProdDesc
    Desc: sets a new description for a given product
    max size for description is defined in DESC_MAX_CHAR
*/
void SetProdDesc(uint id,char * desc)
{
    strcpy(g_array_product[id].desc,desc);
    return;
}


/*
    SetProdPrice
    Desc: sets a new price for a given product
*/
void SetProdPrice(uint id,uint price)
{
    g_array_product[id].price = price;
    return;
}

/*
    SetProdPeso
    Desc: sets a new weight for a given product
*/
void SetProdPeso(uint id,uint weight)
{
    g_array_product[id].weight = weight;
    return;
}



/*
    SetProdQty
    Desc: sets a new quantity for a given product
*/
void SetProdQty(uint id,uint qty)
{
    g_array_product[id].qty = qty;
    return;
}

/*
    SetEncomQtyProd
    Desc: sets a products quantity in a given package
*/
void SetEncomQtyProd(uint id_encom, uint id_prod, uint qty)
{
    g_array_packages[id_encom].products[id_prod][0] = qty;
    return;
}

/*
#########################################################
*/

/*
    GetEncomPeso
    Desc: returns the weight of the given package
*/
uint GetEncomPeso(uint id_encom)
{
    uint total_weight = 0;
    uint id_prod = 0;
    uint qty_prod = 0;
    for(id_prod = 0; id_prod < g_total_products;id_prod ++)
    {   
        qty_prod = GetEncomQtyProd(id_encom,id_prod);
        if(qty_prod > 0) total_weight += GetProdPeso(id_prod) * qty_prod;
    
        }
    return total_weight;
}

/*
    CreateProd
    Desc: initialized a new product and
    adds adds it to the global array
*/
void CreateProd(char desc [DESC_MAX_CHAR],uint price, uint weight, uint qty)
{
    /* set the values of the product*/
    SetProdDesc(g_total_products,desc);
    SetProdPeso(g_total_products,weight);
    SetProdPrice(g_total_products,price);
    SetProdQty(g_total_products,qty);

    printf("Novo produto %d.\n",g_total_products);
    g_total_products ++;
    return;
}

/* 
    AddStock
    Desc: adds stock to an existing product
*/
void AddStock(uint id,uint qty)
{
    /* check if the product was already initialized*/
    if(id >= g_total_products)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
        return;
    }
    /* update the quantity in the product array*/
    SetProdQty(id,GetProdutoQty(id)+qty);
    return;
}
/* 
    RemoveStock
    Desc: removes stock to an existing product
*/
void RemoveStock(uint id,uint qty_rem)
{
    uint qty_prod;
    /* check if the product was already initialized*/
    if(id >= g_total_products)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id);
        return;
    }/* check if the we have enough stock to remove */
    qty_prod = GetProdutoQty(id);
    if( qty_prod < qty_rem)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qty_rem,id);
        return;
    }
    /* update the quantity in the product array*/
    SetProdQty(id,qty_prod-qty_rem);
    return;
}

/*
    CreateEncomenda
    Desc: initializes a new package
*/
void CreateEncomenda()
{
    printf("Nova encomenda %d.\n",g_total_packages);
    g_total_packages ++;
    return;
}

/*
    AddProd
    Desc: adds a product/updates it in the given package
*/
void AddProd(uint id_encom, uint id_prod,uint qty)
{   
    int encom_pre_weight,prod_weight = 0;
    /* if the package is uninitialized, print error and return*/
    if(id_encom >= g_total_packages)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_encom);
        return;
    }/* if the product is uninitialized, print error and return*/
    else if(id_prod >= g_total_products)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_encom);
        return;
    }/* product stock quantity is insuficient, print error and return*/
    else if(GetProdutoQty(id_prod) < qty)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_prod,id_encom);
        return;
    }
    encom_pre_weight = GetEncomPeso(id_encom); /* package weight before any additional items*/
    prod_weight = GetProdPeso(id_prod) * qty;    /* total weight of products to add*/
    /* package weight would exceed the max, print error and return*/
    if (encom_pre_weight + prod_weight > MAX_WEIGHT)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_prod,id_encom);
        return;
    }
    /* update the values in the global arrays*/
    RemoveStock(id_prod,qty);
    SetEncomQtyProd(id_encom, id_prod, GetEncomQtyProd(id_encom,id_prod)+qty);
    return;
}






/*
    RemoveProd
    Desc: removes a product from a given package
    adding it back to stock
*/

void RemoveProd(uint id_encom, uint id_prod)
{
    int qty = 0;
    /* check if both the product and package were initialized*/
    if(id_encom >= g_total_packages)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_encom);
        return;
    }
    else if(id_prod >= g_total_products)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_encom);
        return;
    }
    qty  = GetEncomQtyProd(id_encom,id_prod);
    SetProdQty(id_prod,GetProdutoQty(id_prod) + qty);
    SetEncomQtyProd(id_encom,id_prod,0);
    return;
}


/*
    ListEncomTotalPrice
    Desc: returns the total price of the given package
    returns -1 if the package doesnt exist
*/
void ListEncomTotalPrice(uint id)
{
    uint total = 0;
    uint id_prod = 0;
    if(id>= g_total_packages)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id);
        return;
    }

    /*  cycle through all the products and add their collective price
        in the package to the total */
    for(id_prod = 0; id_prod < g_total_products;id_prod ++)
    {
        total += GetEncomQtyProd(id,id_prod) * GetProdPrice(id_prod);
    }
    printf("Custo da encomenda %u %u.\n",id, total);
    return;
}

/*
    ProdNewPrice
    Desc: sets a new prico for a given product
*/
void ProdNewPrice(uint id, uint price)
{
    if(id >= g_total_products)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id);
        return;
    }
    SetProdPrice(id, price);
    return;
}

/*
    ListDescPrice
    Desc: lists both the description and amount of a given product
    in the given package
*/
void ListDescPrice(uint id_encom, uint id_prod)
{
    char * desc;
    /* check if both the product and package were initialized*/
    if(id_encom >= g_total_packages)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_encom);
        return;
    }
    else if(id_prod >= g_total_products)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_prod);
        return;
    }
    desc = GetProdDescPtr(id_prod);
    printf("%s %d.\n",desc,GetEncomQtyProd(id_encom,id_prod));
    return;
}


/*
    EncomMaxProd
    Desc: lists the package which has the most of a given product
    package id serves as a tiebreaker in case of multiple packages
    having the max amount.
    
*/
void EncomMaxProd(uint id_prod)
{   
    int id_encom = UNINITIALIZED;
    uint max_amount,i,encom_prod_qty;
    max_amount = 0;
    /* check if product was initialized*/
    if(id_prod >= g_total_products)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    /* iterate through each package, if its amount of the product is
        greater than max_amount, update the respective variables */
    for( i = 0; i < g_total_packages;i ++)
    {
        encom_prod_qty = GetEncomQtyProd(i,id_prod);

        if(encom_prod_qty > max_amount)
        {
            max_amount = encom_prod_qty;
            id_encom = i;
        }
    }
    if(id_encom == UNINITIALIZED) /* return if no packages had the product*/
    {
        return;
    }

    printf("Maximo produto %d %d %d.\n",id_prod,id_encom,max_amount);
    return;
}


/*  MergeSortOrder
    Desc: orders the two "sub array"s elements into the array, whilst preserving stability
    Note: -> (*p_less_key_func) must be a pointer to a key comparison function that takes 2 elements and
            returns 1/TRUE if the first elements key is smaller than the seconds and 0 if not
*/
void MergeSortOrder(int arr[],int arr_aux[],uint l_bound,uint mid_index, uint r_bound,int (*p_less_key_func)(int,int))
{   
    
    uint left_ptr, right_ptr,index;
    /* write left_arr into the arr_aux in left to right order*/
    for(left_ptr = mid_index + 1;left_ptr > l_bound; left_ptr--)
    {
        arr_aux[left_ptr - 1] = arr[left_ptr - 1];
    }
    /*  write right_arr into the arr_aux in right to left order so the l and r position pointers
        dont conflict, preventing aditional code if a pointer reached the end of its respective "array" */
    for(right_ptr = mid_index; right_ptr < r_bound;right_ptr++)
    {
        arr_aux[r_bound +mid_index -right_ptr] = arr[right_ptr + 1];
    }

    for(index = l_bound; index <= r_bound; index++)
    {
        /* if the left elements "key" is smaller or equal than rights,
            places the left element in the array, preserving stability,
            if left_ptr reach mid, the remaining right elements are are bigger */
        if((*p_less_key_func)(arr_aux[right_ptr],arr_aux[left_ptr]) || left_ptr > mid_index) 
        {
            arr[index] = arr_aux[right_ptr--];
        }
        else
        {
            arr[index] = arr_aux[left_ptr++];
        }
        
    }
    
    return;
}

/*
    MergeSortRecursive
    Desc: Recursively breaks an array into elementary 1 unit arrays and merges them in order
*/
void MergeSortRecursive(int arr[],int arr_aux[],uint l_bound,uint r_bound,int (*p_less_key_func)(int,int))
{
    /* middle point in which to break the p_arr*/
    int mid_index = (l_bound + r_bound)/2; 

    /* return if the indexes are not correctly setup
     or if we reached an p_arr of only 1 element to finish the recursion*/
    if(r_bound <= l_bound){return;}
    /* call the function again on both halves of the p_arr*/
    MergeSortRecursive(arr,arr_aux,l_bound,mid_index,(*p_less_key_func));
    MergeSortRecursive(arr,arr_aux,mid_index +1,r_bound,(*p_less_key_func));

    /* when the recursion collapses, merge both halves*/
    MergeSortOrder(arr,arr_aux, l_bound, mid_index,r_bound,(*p_less_key_func));
    return;
}

/* 
    MergeSort
    Desc: prepares an auxiliary array and calls MergeSortReecursive to handle the ordering
*/
void MergeSort(int arr[],uint l_bound,uint r_bound,int (*p_less_key_func)(int,int))
{
    /* prepares an auxiliary array for memory savings *stonks**/
    int arr_aux[MAX_ARR_SORT_SIZE] = {0};
    MergeSortRecursive(arr,arr_aux,l_bound,r_bound,(*p_less_key_func));
    return;

}


/* 
    CompareProdPrice
    Desc: key compare function that compares the prices of two products given by id
*/
int CompareProdPrice(int id_1, int id_2)
{
    int price_1 = GetProdPrice(id_1);
    int price_2 = GetProdPrice(id_2);
    if(price_1 < price_2) 
    {
        return 1;
    }
    else if(price_1 == price_2) /* id breaks ties if the prices are equal */
    {
        if(id_1 < id_2) return 1;
        else return 0;
    }
    else
    {
        return 0;
    }
    
}


/*
    ListProdByPrice
    Desc: Lists initialized products ordered by price, in the way specified in the project guidelines
*/
void ListProdByPrice()
{   
    uint id;
    int array_ids[MAX_PRODUCTS]; /* compilation rules don't let me make variable size array, reeeeeeeee*/
    char * desc;
    printf("Produtos\n");
    if(g_total_products == 0) return; /* return if no products were created yet*/
    for(id = 0; id < g_total_products; id ++) /* initialize an array which contains the ids of initialized products*/
    {
        array_ids[id] = id;
    }
    MergeSort(array_ids,0, g_total_products -1 , &CompareProdPrice); /* order the ids by comparing product price*/
    /* print the products as in specified on the guidelines */
    for(id = 0; id < g_total_products; id ++)
    {
        desc = GetProdDescPtr(array_ids[id]);
        printf("* %s %d %d\n",desc,GetProdPrice(array_ids[id]),GetProdutoQty(array_ids[id]));
    }
    return;
}









/*
    CompareProdDesc
    Desc: key compare function that compares the description of two products given by id
    Note: compares by ascII standard
*/
int CompareProdDesc(int id_1,int id_2)
{
    /* initialize pointers to the char arrays*/
    char * buf_1 = GetProdDescPtr(id_1);
    char * buf_2  = GetProdDescPtr(id_2);
    int comp = strcmp(buf_1,buf_2); 
    if(comp < 0)
    {
        return 1;
    }
    else if(comp == 0) /* id breaks ties if the strings are equal, not that it should even happen */
    {
        if(id_1 < id_2) return 1;
        else return 0;
    }
    else
    {
        return 0;
    }
}

/*
    ListEncomProdByDesc
    Desc: lists products that are currently in the given package, in the way specified in the project guidelines
*/
void ListEncomProdByDesc(uint id_encom)
{   
    
    uint id,total_prod,counter;
    int array_ids[MAX_ENCOM_PRODS] = {0};
    char * desc;
    int qty_prod;
    if(id_encom >= g_total_packages)
    {
        printf("Impossivel listar encomenda %u. Encomenda inexistente.\n", id_encom);
        return;
    }
    
    printf("Encomenda %d\n",id_encom);
    counter = 0, total_prod = 0;
    for(id = 0; id < g_total_products; id ++)/* initialize an array which contains the ids of initialized products*/
    {
        qty_prod = GetEncomQtyProd(id_encom,id);
        if(qty_prod > 0) /* only add the product id if it exists in the package*/
        {
            array_ids[counter] = id;
            total_prod ++;
            counter ++;
        }  
       if(counter >= MAX_ENCOM_PRODS) break;
    }
    if(total_prod == 0) return;
    MergeSort(array_ids,0, total_prod - 1  , &CompareProdDesc);/* order the ids by comparing product description*/
    /* print the products as in specified on the guidelines */
    for(counter = 0; counter < total_prod; counter ++)
    {   
        qty_prod = GetEncomQtyProd(id_encom,array_ids[counter]);
        desc = GetProdDescPtr(array_ids[counter]);
        printf("* %s %d %d\n",desc,GetProdPrice(array_ids[counter]),qty_prod);
    }
    return;
}