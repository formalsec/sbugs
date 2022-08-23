#define MAXPRODUCTS 10000
#define MAXORDERS 500
#define MAXDESC 64
#define MAXPRODUCTSINORDER 100
#define MAX_INPUT 100

/* Struct product */
typedef struct product{
    int id;
    char desc[MAXDESC];
    int price;
    int weight;
    int stock;
    int times_in_order;
} PRODUCT;

/* Struct order */
typedef struct order{
    int orderid;
    int orderweight;
    int sizelstproducts;
    PRODUCT orderlstproducts[MAXPRODUCTSINORDER];   /* List of products within an order */
} ORDER;

/* List of product within the system */
PRODUCT* lstproducts[MAXPRODUCTS];

/* List of orders within the system */
ORDER* lstorders[MAXORDERS];

/* Auxiliar list for mergesort */
PRODUCT aux[MAXPRODUCTS];

void a_parsing(char input[MAX_INPUT], int productid);
void add_stock(char input[MAX_INPUT]);
void remove_stock(char input[MAX_INPUT]);
void create_order(int orderid);
void add_product_to_order(char input[MAX_INPUT]);
void remove_product_from_order(char input[MAX_INPUT]);
void calc_order_cost(char input[MAX_INPUT]);
void change_product_price(char input[MAX_INPUT]);
void list_product_in_order(char input[MAX_INPUT]);
void show_order_of_max_times_product(char input[MAX_INPUT], int max);
void merge(PRODUCT a[], int left, int m, int right);
void mergesort(PRODUCT a[], int l, int r);
void merge_alphabet(PRODUCT a[], int left, int m, int right);
void mergesort_alphabet(PRODUCT a[], int l, int r);
void print_lst_products(int max);
void print_lst_products_in_order(char input[MAX_INPUT]);