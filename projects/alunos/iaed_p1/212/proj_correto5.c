#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#define MAX_CHARS 64 /* max characters of a word */
#define MAX_PROD 10000 /* max products in the sistem */
#define MAX_ORDERS 500 /* max orders possible in the sistem */
#define MAX_PRODS_OD 200 /* max products in an order */

/*------------------------------------------------------------------  GLOBAL VARIABLES  --------------------------------------------------------------------------*/
int i = 0; /* counts the number of products */
int y = 0; /* counts the number of orders */

/*-------------------------------------------------------------------------  STRUCTURES  -------------------------------------------------------------------------*/
typedef struct product 
{
   int ident;/*idp of a product*/
   char desc[MAX_CHARS]; /* string that describes a product eg. "bread" */
   int price;  /* price of the product*/
   int weight; /* weight of the product eg. 2kg */
   int quant; /* quantity of the product in stock */
   int state_prod;/*state of a product, if its 1 its in the system else is 0 and is not in the system*/
}product;

typedef struct order 
{
   int ident_o;/*ide of an order*/
   product set_prod[MAX_PRODS_OD]; /* Set of products */
   int state;/*state of an order, if its 1 its in the system else is 0 and is not in the system*/
   int peso_order;/*Total weight of an order*/
}order;

/*-------------------------------------------------------------------------  GLOBAL ARRAYS  -----------------------------------------------------------------------*/
product aux[MAX_PROD]; /*Auxliar array used in mergesort*/
product sistem[MAX_PROD]; /* array of products */
order sistem_orders[MAX_ORDERS]; /* array of orders */
product sistem2[MAX_PROD];/*copy of the sistem used for the mergesort*/
product sistem3[MAX_PRODS_OD];/*copy of the sistem used for the quicksort*/

/*------------------------------------------------------------------  PROTOTYPE AUXILIAR FUNCTIONS  --------------------------------------------------------------*/
int indentify_prod(product s[],int idp);
product make_product(char *desc,int price,int weight,int quant);
order make_order(product s[]);
int product_in_order(int ide,order s[],int idp);
int product_in_system(int idp);
int order_in_system(int ide);
void copy_el(product source[],product dest[], int size);
int product_already_system(char *desc);
void mergesort_price(product a[], int low, int high);
void merge_price(product a[], int low, int mid, int high);
void swap(product *xp,product *yp);
void quicksort_str(product a[], int left, int right);
int partition_str(product a[], int left, int right);

/*------------------------------------------------------------------  PROTOTYPE PRODUCT FUNCTIONS  --------------------------------------------------------------*/
void a(char *desc,int price,int weight,int quant);
void q(int idp, int quant);
void r(int idp, int quant);
void p(int idp, int price);
void l(product a[]);

/*------------------------------------------------------------------  PROTOTYPE ORDER FUNCTIONS  -----------------------------------------------------------------*/
void N(product s[]);
void A(int ide, int idp,int quant);
void R(int ide, int idp);
void C(int ide);
void E(int ide, int idp);
void m(int idp);
void L(int ide, product a[]);


/*-------------------------------------------------------------------------------  MAIN PROGRAM  -----------------------------------------------------------------*/
int main() {
   char c; int weight; char desc[MAX_CHARS]; int quant; int price; int idp; int ide;
   product new_order[MAX_PROD];
   while ((c = getchar())!= 'x') {
   switch (c) 
   {
      case 'a':
      {
         scanf("%62[^:]:%d:%d:%d",desc,&price,&weight,&quant);
         a(desc,price,weight,quant);
         break;
      }
      case 'q':
      {
         scanf("%d:%d",&idp,&quant);
         q(idp,quant);
         break;
      }
      case 'r':
      {
         scanf("%d:%d",&idp,&quant);
         r(idp,quant);
         break;
      }
      case 'p':
      {
         scanf("%d:%d",&idp,&price);
         p(idp,price);
         break;
      }
      case 'l':
      {
         copy_el(sistem,sistem2,MAX_PROD);
         mergesort_price(sistem2,0,MAX_PRODS_OD-1);
         printf("Produtos\n");
         l(sistem2);
         break;
      }
      case 'N':
      {
         N(new_order);
         break;
      }
      case 'A':
      {
         scanf("%d:%d:%d",&ide,&idp,&quant);
         A(ide,idp,quant);
         break;
      }
      case 'R':
      {
         scanf("%d:%d",&ide,&idp);
         R(ide,idp);
         break;
      }
      case 'C':
      {
         scanf("%d",&ide);
         C(ide);
         break;
      }
      case 'E':
      {
         int r = 0; int c = 0;
         scanf("%d:%d",&ide,&idp);
         while(r<MAX_ORDERS)
         {
            while(c<MAX_PRODS_OD)
            {
               strcpy(sistem_orders[r].set_prod[c].desc,sistem[c].desc);
               c++;
            }
            c=0;
            r++;
         }
         E(ide,idp);
         break;
      }
      case 'm':
      {
         scanf("%d",&idp);
         m(idp);
         break;
      }
      case 'L':
      {
         scanf("%d",&ide);
         if (order_in_system(ide) == 1)
         {
         copy_el(sistem_orders[ide].set_prod,sistem3,MAX_PRODS_OD);
         quicksort_str(sistem3,0,MAX_PRODS_OD-1);
         printf("Encomenda %d\n",ide);
         L(ide,sistem3);
        }
         else
         {
             printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
         }
         break;
      }
   }
   }
   return 0;
}

/*--------------------------------------------------------------------------------   PRODUCT'S FUNCTIONS  ------------------------------------------------------------------------------------ */

/*This function adds a product into the system, but if the product is already in it it doesn't add anything*/
void a(char *desc,int price,int weight,int quant)
{
    product test_product = make_product(desc,price,weight,quant);
    if (product_already_system(test_product.desc) == 1)
    {
    }
    else
    {
   if ((i >= 0 && i < MAX_PROD) && (strlen(desc) <= MAX_CHARS) && (price > 0) && (weight > 0) && (quant >=0))
   {
   printf("Novo produto %d.\n",i);     /* adds a new product into an array of products (sistem) */
   sistem[i] = make_product(desc,price,weight,quant);
   i++;
   }
    }
}

/* This function adds more stock to a product if the product is in the system, else it wont add anything and instead will print an error*/
void q(int idp, int quant)
{
   if (indentify_prod(sistem,idp) == 1) /* product exists in the sistem*/
   {
      sistem[idp].quant += quant;
   }
   else 
   {
      printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
   }
}

/* This function removes stock from a product if the product is in the sistem and if the resulting quantity is bigger or equal to 0, else it wont and instead will print an error*/
void r(int idp, int quant)
{
   int new_quant = sistem[idp].quant;
   if ((product_already_system(sistem[idp].desc) == 1) && ((new_quant -= quant) >= 0))/* product exists in the sistem*/
   {
      sistem[idp].quant -= quant;
   }
   else if ((indentify_prod(sistem,idp) == 1) && ((new_quant -= quant) < 0))
   {
      printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quant,idp);
   }
   else
   {
      printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
   }
}

/*This function list the products in the system*/
void l(product a[])
{
   int i;
    for (i = 0; i < MAX_PROD; i++)
        if ((indentify_prod(a,i) == 1) && (a[i].price > 0))
      {
         printf("* %s %d %d\n",a[i].desc,a[i].price,a[i].quant);
      } 
}

/* This function adds more stock to a product if the product is in the sistem, else it wont and instead will print an error*/
void p(int idp, int price)
{
   if ((indentify_prod(sistem,idp) == 1) && (price > 0)) /* product exists in the sistem*/
   {
      int i = 0;
      sistem[idp].price = price;
      while (i <MAX_PRODS_OD)
      {
          if (sistem[idp].ident == sistem_orders[i].set_prod[idp].ident)
          {
              if ((product_in_order(i,sistem_orders,idp) == 1) && (product_in_system(idp) == 1)){
              sistem_orders[i].set_prod[idp].price = price;
              }
          }
          i++;
      }
   }
   else 
   {
      printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
   }
}

/*--------------------------------------------------------------------------------   ORDER'S FUNCTIONS  ------------------------------------------------------------------------------------ */

/*This function creates a new order*/
void N(product ar[])
{
   printf("Nova encomenda %d.\n",y);       /* adds a new order into an array of orders (sistem_orders) */
   sistem_orders[y] = make_order(ar);
   sistem_orders[y].state = 1;
   y++;
}

/*This function adds a specific quantity of a product into an order (if it's not in order) else it adds more quantity to a product while the quantity is lower than the quantity of the product in the system and it's weight doesn't surpass 200*/
void A(int ide, int idp,int quant)
{
   sistem_orders[ide].peso_order = (sistem[idp].weight * quant + sistem_orders[ide].peso_order);
   if (order_in_system(ide) == 0)
   {
     printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
     sistem_orders[ide].peso_order -= (sistem[idp].weight * quant);
   }
   else if ((product_in_system(idp) == 0))
   {
     printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
     sistem_orders[ide].peso_order -= (sistem[idp].weight * quant);
   }
   else if (quant > sistem[idp].quant)
   {
      printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
      sistem_orders[ide].peso_order -= (sistem[idp].weight * quant);
   }
   else {
      if ((product_in_order(ide,sistem_orders,idp) == 0) && (sistem_orders[ide].peso_order <= 200))
      {
         sistem_orders[ide].set_prod[idp] = sistem[idp];
         sistem_orders[ide].set_prod[idp].quant = quant;
         sistem[idp].quant -= quant;
      }
      else if ((product_in_order(ide,sistem_orders,idp) == 1) && (sistem_orders[ide].peso_order <= 200))
      {
          sistem_orders[ide].set_prod[idp].quant += quant;
          sistem[idp].quant -= quant;
      }
      else if (sistem_orders[ide].peso_order > 200)
      {
      printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
      sistem_orders[ide].peso_order -= (sistem[idp].weight * quant);
      }
   }
}

/*This function removes a product from an order*/
void R(int ide, int idp)
{
   if (order_in_system(ide) == 0)
   {
     printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
   }
   else if ((product_in_system(idp) == 0))
   {
     printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
   }
   else
   {
       sistem_orders[ide].peso_order -= (sistem[idp].weight * sistem_orders[ide].set_prod[idp].quant);
       sistem[idp].quant += sistem_orders[ide].set_prod[idp].quant;
        sistem_orders[ide].set_prod[idp].quant = 0;
   }
}

/*This function prints the overall cost of an order*/
void C(int ide)
{
   if (order_in_system(ide) == 0)
   {
     printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
   }
   else
   {
   int i = 0;
   int total = 0;
   while (i<MAX_PRODS_OD)
   {
      total += (sistem_orders[ide].set_prod[i].price * sistem_orders[ide].set_prod[i].quant);
      i++;
   }
   printf("Custo da encomenda %d %d.\n",ide,total);
   }
}

/*This function prints the quantity of a specific product in a specific order*/
void E(int ide, int idp)
{
   if (order_in_system(ide) == 0)
   {
     printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
   }
   else if ((product_in_system(idp) == 0))
   {
     printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
   }
   else
   {
      printf("%s %d.\n",sistem[idp].desc,sistem_orders[ide].set_prod[idp].quant);
   }
}

/*This function prints the maximum quantity of product in system of orders, if there two orders which have the same quantity then it returns the quantity and the order with a lower ide*/
void m(int idp)
{
   if (product_in_system(idp) == 0)
   {
     printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
   }
   else
   {
      int i = 0; int max = 0; int index;
      while (i<MAX_ORDERS)
      {
         if (sistem_orders[i].set_prod[idp].quant > max)
         {
            max = sistem_orders[i].set_prod[idp].quant;
            index = i;
         }
         else if (sistem_orders[i].set_prod[idp].quant == max)
         {
            if (i < index)
            {
               index = i;
            }
         }
         i++;
      }
      if (max > 0)
      {
         printf("Maximo produto %d %d %d.\n",idp,index,max);
      }
   }
}

/*This function sorts a the products of a specific order based on it's description*/
void L(int ide, product a[])
{
   int i=0;
   while (i<MAX_PRODS_OD)
   {
      if ((order_in_system(ide) == 1) && (a[i].quant > 0))
      {
         printf("* %s %d %d\n",a[i].desc,a[i].price,a[i].quant);
      }
      i++;
   }
}  


/*--------------------------------------------------------------------------------   AUXILIAR FUNCTIONS  -------------------------------------------------------------------------------------- */

/*This function removes the 1st whitespaces in a product's description, which is the first character in the description's string*/
void remove_white(char * str)
{
   char ch = ' ';
   int len = strlen(str);
   int i;
   int j;
	   	
  	for(i = 0; i < len; i++)
	{
		if(str[i] == ch)
		{
			for(j = i; j < len; j++)
			{
				str[j] = str[j + 1];
			}
			len--;
			i--;	
		} 
	}	
}

/*This function goes through the system and checks if a product is already in it or not */
int product_already_system(char *desc)
{
    int i = 0; int res = 0; /*if res is 0 it me*/ 
    while (i<MAX_PROD)
    {
        if ((strcmp(desc,sistem[i].desc) == 0) && (sistem[i].state_prod == 1))
        {
            res = 1;
        }
        i++;
    }
    return res;
}

/*This function creates a valid product*/
product make_product(char *desc,int price,int weight,int quant)
{
    product p1 = {0,"",0,0,0,1};   /* creates a product and returns the created product*/
    p1.ident = i;
    p1.price = price;
    p1.weight = weight;
    p1.quant = quant;
    strcpy(p1.desc, desc);
    remove_white(p1.desc);
    return p1;
}

/* This function verifies wether a product is valid or not*/
int indentify_prod(product s[],int idp) 
{
   if (s[idp].price != 0 && s[idp].weight != 0)
   {
      return 1; /* this function verifies wether a product is or isnt in the sistem*/
   }
   else {
      return 0;
   }
}

/*This function copies the elements in an array of product into another array of products*/
void copy_el(product source[],product dest[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        dest[i] = source[i];
    }
}

/*This function creates a valid order and returns it*/
order make_order(product s[])
{
    order p1 = {0};
    p1.ident_o = y;
    copy_el(s,p1.set_prod,MAX_PRODS_OD);
    return p1;
}

/*This function verifies wether a product is in an order or not*/
int product_in_order(int ide,order s[],int idp)
{
   if (s[ide].set_prod[idp].state_prod == 1)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

/*This function also verifies wether a product is in the system or not*/
int product_in_system(int idp)
{
   if (sistem[idp].state_prod == 1)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

/*This function verifies wether an order is in the system or not*/
int order_in_system(int ide)
{
   if (sistem_orders[ide].state == 1)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

/*This function sorts an array of products based on a product's price*/
void mergesort_price(product a[], int low, int high)
{
    int mid = (high + low) / 2;

    if (high <= low)
        return;
    mergesort_price(a, low, mid);
    mergesort_price(a, mid + 1, high);
    merge_price(a, low, mid, high);
}

/*This is auxiliar function to the mergesort based on a product's price*/
void merge_price(product a[], int low, int mid, int high)
{
    int right;
    int left;
    int k;
    int i;

    k = 0;
    left = low;
    right = mid + 1;

    for (;  (left <= mid) && (right <= high);  ++k) {
        if (a[left].price <= a[right].price)
            aux[k] = a[left++];
        else
            aux[k] = a[right++];
    }

    for (;  left <= mid;  ++left, ++k)
        aux[k] = a[left];

    for (;  right <= high;  ++right, ++k)
        aux[k] = a[right];

    k = low;
    i = 0;
    for (;  k <= high;  ++k, ++i)
        a[k] = aux[i];
}

/*This function swaps two products*/
void swap(product *xp,product *yp)
{ 
    product temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

/*This function sorts an array of products based on a product's description using quicksort*/
void quicksort_str(product a[], int left, int right)
{
int i;
if (right <= left)
return;
i = partition_str(a, left, right);
quicksort_str(a, left, i-1);
quicksort_str(a, i+1, right);
}

/*This is auxiliar function to the quicksort based on a product's price*/
int partition_str(product a[], int left, int right)
{
int i = left-1;
int j = right;
product v = a[right];
    while (i < j) {
        while (strcmp(a[++i].desc,v.desc) < 0);
        while (strcmp(v.desc,a[--j].desc) < 0)
        if (j == left)
            break;
        if (i < j)
        swap(&a[i], &a[j]);
    }
swap(&a[i], &a[right]);
return i;
}