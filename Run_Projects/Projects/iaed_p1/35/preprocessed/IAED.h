/*File generated by PreProcessor.py*/




typedef struct product
{
  int id;
  char desc[64];
  int price;
  int weight;
  int stock;
  int times_in_order;
} PRODUCT;
typedef struct order
{
  int orderid;
  int orderweight;
  int sizelstproducts;
  PRODUCT orderlstproducts[100];
} ORDER;
PRODUCT *lstproducts[10000];
ORDER *lstorders[500];
PRODUCT aux[10000];
void a_parsing(char input[100], int productid);
void add_stock(char input[100]);
void remove_stock(char input[100]);
void create_order(int orderid);
void add_product_to_order(char input[100]);
void remove_product_from_order(char input[100]);
void calc_order_cost(char input[100]);
void change_product_price(char input[100]);
void list_product_in_order(char input[100]);
void show_order_of_max_times_product(char input[100], int max);
void merge(PRODUCT a[], int left, int m, int right);
void mergesort(PRODUCT a[], int l, int r);
void merge_alphabet(PRODUCT a[], int left, int m, int right);
void mergesort_alphabet(PRODUCT a[], int l, int r);
void print_lst_products(int max);
void print_lst_products_in_order(char input[100]);