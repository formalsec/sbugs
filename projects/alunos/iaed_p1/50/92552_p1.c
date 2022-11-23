#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Macro constants */
#define MAXPRODLIM 10000
#define MAXPACKLIM 500
#define MAXSLOTLIM 200
#define MAXPACKWEIGHT 200
#define MAXPRODINFO 64

/* These two will be used as flags for the sorting algorithm */
#define SORTWPRICE 1
#define SORTWDESC 0

/* Product structure holds:
 * - info : The description string.
 * - id : The product identifier.
 * - price, weight and amount.
 */
typedef struct Product {
    char info[MAXPRODINFO];
    int id;
    int price;
    int weight;
    int amount;
} Product;

/* Section structure holds:
 * - id : The holder of a product id.
 * - amount : The holder of another product stock amount.
 * This struct is only used to complement the Package struct!
 */
typedef struct Section {
    int id;
    int amount;
} Section;

/* Package structure holds:
 * - slot : The holder of an array of product ids and respective stock
 * amount available in the package.
 * - weight : The package's weight.
 */
typedef struct Package {
    Section slot[MAXSLOTLIM];
    int weight;
} Package;

/* Global variables:
 *
 * - c : The char target for the command.
 * - sorted_prod_id : The auxiliary array for sorting product ids.
 *
 * - last_prod_id, last_pack_id, last_slot_id : These are associated
 * with a specific array to represent the index right after when the
 * last element was added, just like how a stack works. Their values
 * can increase, but never decrease. Initialized at 0.
 *
 * - productsys : The product system, containing a bunch of products.
 * - packagesys : The package system, containing a bunch of packages.
 */
int c;
int last_prod_id;
int last_pack_id;
int last_slot_id[MAXPACKLIM];
int sorted_prod_id[MAXPRODLIM];

Product productsys[MAXPRODLIM];
Package packagesys[MAXPACKLIM];

/* Function prototypes */
void do_a();
void do_q();
void do_N();
void do_A();
void do_r();
void do_R();
void do_C();
void do_p();
void do_E();
void do_m();
void do_l();
void do_L();
void doMergeSort(int[], int, int, int);
void doMerge(int[], int, int, int, int);
int prodExists(int);
int packExists(int);

void do_a() {

    scanf("%*c%[^:]:%d:%d:%d",
    productsys[last_prod_id].info,
    &productsys[last_prod_id].price,
    &productsys[last_prod_id].weight,
    &productsys[last_prod_id].amount);

    /* To make sure nothing goes nuts, the string will always have
    a NULL char at the end of the array, regardless of the stdin input. */
    productsys[last_prod_id].info[MAXPRODINFO - 1] = '\0';

    productsys[last_prod_id].id = last_prod_id;
    printf("Novo produto %d.\n", last_prod_id);

    ++last_prod_id;
}

void do_q() {

    int prod_id, add_amount;

    scanf("%*c%d:%d", &prod_id, &add_amount);

    if (!prodExists(prod_id)) {

        printf("Impossivel adicionar produto %d ao stock. "
        "Produto inexistente.\n", prod_id);
    }
    else productsys[prod_id].amount += add_amount;
}

void do_N() {

    /* The package weight is always initialized at 0. */

    printf("Nova encomenda %d.\n", last_pack_id);

    ++last_pack_id;
}

void do_A() {

    int i, j;
    int prod_id, pack_id, prod_amount;
    int prod_weight;

    scanf("%*c%d:%d:%d", &pack_id, &prod_id, &prod_amount);

    if (!packExists(pack_id)) {

        printf("Impossivel adicionar produto %d "
        "a encomenda %d. Encomenda inexistente.\n", prod_id, pack_id);
    }
    else if (!prodExists(prod_id)) {

        printf("Impossivel adicionar produto %d "
        "a encomenda %d. Produto inexistente.\n", prod_id, pack_id);
    }
    else if (productsys[prod_id].amount - prod_amount < 0) {

        printf("Impossivel adicionar produto %d a "
        "encomenda %d. Quantidade em stock insuficiente.\n", prod_id, pack_id);
    }
    else if (productsys[prod_id].weight * prod_amount +
        packagesys[pack_id].weight > MAXPACKWEIGHT) {

        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Peso da encomenda excede o maximo de 200.\n", prod_id, pack_id);
    }
    else {

        i = last_slot_id[pack_id];
        prod_weight = productsys[prod_id].weight;

        for (j = 0; j < i; j++) {

            /* Seeks for the slot index were prod_id is stored*/
            if (packagesys[pack_id].slot[j].id == prod_id) {

                /* In case the product id was found in the package. */
                packagesys[pack_id].slot[j].amount += prod_amount;
                productsys[prod_id].amount -= prod_amount;
                packagesys[pack_id].weight += prod_weight * prod_amount;
                return;
            }
        }

        /* In case the product id was not found in the package. */
        packagesys[pack_id].slot[i].id = prod_id;
        packagesys[pack_id].slot[i].amount = prod_amount;

        productsys[prod_id].amount -= prod_amount;
        packagesys[pack_id].weight += prod_weight * prod_amount;

        ++last_slot_id[pack_id];
    }
}

void do_r() {

    int prod_id, sweep_amount;

    scanf("%*c%d:%d", &prod_id, &sweep_amount);

    if (!prodExists(prod_id)) {

        printf("Impossivel remover stock do "
        "produto %d. Produto inexistente.\n", prod_id);
    }
    else if (productsys[prod_id].amount - sweep_amount < 0) {

        printf("Impossivel remover %d unidades do produto %d "
        "do stock. Quantidade insuficiente.\n", sweep_amount, prod_id);
    }
    else productsys[prod_id].amount -= sweep_amount;
}

void do_R() {

    int i, j;
    int prod_id, pack_id;
    int prod_amount, prod_weight;

    scanf("%*c%d:%d", &pack_id, &prod_id);

    if (!packExists(pack_id)) {

        printf("Impossivel remover produto %d "
        "a encomenda %d. Encomenda inexistente.\n", prod_id, pack_id);
    }
    else if (!prodExists(prod_id)) {

        printf("Impossivel remover produto %d "
        "a encomenda %d. Produto inexistente.\n", prod_id, pack_id);
    }
    else {

        i = last_slot_id[pack_id];

        for (j = 0; j < i; j++) {
            if (packagesys[pack_id].slot[j].id == prod_id) {

                prod_amount = packagesys[pack_id].slot[j].amount;
                prod_weight = productsys[prod_id].weight;

                packagesys[pack_id].slot[j].amount = 0;
                productsys[prod_id].amount += prod_amount;
                packagesys[pack_id].weight -= prod_amount * prod_weight;
                return;
            }
        }
        /* Does nothing if there is no such
        product id available in the package. */
    }
}

void do_C() {

    int i, j;
    int prod_id, pack_id;
    int prod_price, prod_amount, total = 0;

    scanf("%*c%d", &pack_id);

    if (!packExists(pack_id)) {

        printf("Impossivel calcular custo da encomenda %d. " \
        "Encomenda inexistente.\n", pack_id);
    }
    else {

        i = last_slot_id[pack_id];

        for (j = 0; j < i; j++) {

            /* Seeks for the product id stored in
            the specified package slot. */
            prod_id = packagesys[pack_id].slot[j].id;

            prod_price = productsys[prod_id].price;
            prod_amount = packagesys[pack_id].slot[j].amount;

            total += prod_price * prod_amount;
        }
        printf("Custo da encomenda %d %d.\n", pack_id, total);
    }
}

void do_p() {

    int prod_id, prod_new_price;

    scanf("%*c%d:%d", &prod_id, &prod_new_price);

    if (!prodExists(prod_id)) {

        printf("Impossivel alterar preco do produto %d. "
        "Produto inexistente.\n", prod_id);
    }
    else productsys[prod_id].price = prod_new_price;
}

void do_E() {

    int i, j;
    int prod_id, pack_id;

    scanf("%*c%d:%d", &pack_id, &prod_id);

    if (!packExists(pack_id)) {

        printf("Impossivel listar encomenda %d. "
        "Encomenda inexistente.\n", pack_id);
    }
    else if (!prodExists(prod_id)) {

        printf("Impossivel listar produto %d. "
        "Produto inexistente.\n", prod_id);
    }
    else {

        i = last_slot_id[pack_id];

        for (j = 0; j < i; j++)
            if (packagesys[pack_id].slot[j].id == prod_id) {

                printf("%s %d.\n",
                productsys[prod_id].info,
                packagesys[pack_id].slot[j].amount);
                return;
            }

        /* Only executes in case the product id
        was never found in the package in question. */
        printf("%s 0.\n", productsys[prod_id].info);
    }
}

void do_m() {

    int i, j;
    int prod_id, pack_id;
    int check_amount, max_amount = 0;

    scanf("%*c%d", &prod_id);

    if (!prodExists(prod_id)) {

        printf("Impossivel listar maximo do produto %d. " \
        "Produto inexistente.\n", prod_id);
    }
    else {

        for (i = 0; i < last_pack_id; i++) {
            for (j = 0; j < last_slot_id[i]; j++) {
                if (packagesys[i].slot[j].id == prod_id) {
                    check_amount = packagesys[i].slot[j].amount;
                    if (max_amount < check_amount) {
                        max_amount = check_amount;
                        pack_id = i;
                    break;
                    }
                }
            }
        }
        /* This condition checks wether there were any products at all or if
        they were found but all their stock amounts were set to 0, throughout
        the packages. If that is not the case, then max_amount != 0. */
        if (max_amount) {
            printf("Maximo produto %d %d %d.\n",
            prod_id, pack_id, max_amount);
        }
    }
}

void do_l() {

    int i;
    int prod_id;
    int manner = SORTWPRICE;

    for (i = 0; i < last_prod_id; i++)
        sorted_prod_id[i] = productsys[i].id;

    if (last_prod_id)
        doMergeSort(sorted_prod_id, 0, last_prod_id - 1, manner);

    printf("Produtos\n");
    for (i = 0; i < last_prod_id; i++) {

        prod_id = sorted_prod_id[i];
        printf("* %s %d %d\n", productsys[prod_id].info,
        productsys[prod_id].price, productsys[prod_id].amount);
    }
}

void do_L() {

    int i, j, k;
    int prod_id, pack_id, prod_amount;
    int manner = SORTWDESC;

    scanf("%*c%d", &pack_id);

    if (!packExists(pack_id)) {

        printf("Impossivel listar encomenda %d. "
        "Encomenda inexistente.\n", pack_id);
    }
    else {

        i = last_slot_id[pack_id];

        for (j = 0; j < i; j++)
            sorted_prod_id[j] = packagesys[pack_id].slot[j].id;

        if (i)
            doMergeSort(sorted_prod_id, 0, i - 1, manner);

        printf("Encomenda %d\n", pack_id);
        for (j = 0; j < i; j++) {

            prod_id = sorted_prod_id[j];

            for (k = 0; k < i; k++)

                if (packagesys[pack_id].slot[k].id == prod_id) {
                    prod_amount = packagesys[pack_id].slot[k].amount;
                    break;
                }

            /* Only executes if the product amount
            in the package slot != 0 */
            if (prod_amount)
                printf("* %s %d %d\n", productsys[prod_id].info,
                productsys[prod_id].price, prod_amount);
        }
    }
}

/* A flag is sent along with the arguments to determine
 * wether the sorting must be done according to the
 * price (SORTWPRICE) or to the description (SORTWDESC)
 */
void doMergeSort(int prod_arr[], int l, int r, int flag) {

    int m = (l + r) / 2;

    if (r > l) {
        doMergeSort(prod_arr, l, m, flag);
        doMergeSort(prod_arr, m + 1, r, flag);
        doMerge(prod_arr, l, m, r, flag);
    }
}

void doMerge(int prod_arr[], int l, int m, int r, int flag) {

    int i, j, k;
    int lp, rp, result;
    int aux[MAXPRODLIM];

    for (i = m + 1; i > l; i--) {
        aux[i - 1] = prod_arr[i - 1];
    }
    for (j = m; j < r; j++) {
        aux[r + m - j] = prod_arr[j + 1];
    }
    for (k = l; k <= r; k++) {

        if (flag == SORTWPRICE) {

            lp = productsys[aux[i]].price;
            rp = productsys[aux[j]].price;

            if (lp < rp) {
                prod_arr[k] = aux[i++];
            }
            else if (lp > rp) {
                prod_arr[k] = aux[j--];
            }
            else if (aux[i] < aux[j]) {
                prod_arr[k] = aux[i++];
            }
            else prod_arr[k] = aux[j--];
        }
        else if (flag == SORTWDESC) {

            result = strcmp(productsys[aux[i]].info,
            productsys[aux[j]].info);

            if (result < 0) {
                prod_arr[k] = aux[i++];
            }
            else if (result > 0) {
                prod_arr[k] = aux[j--];
            }
            else if (aux[i] < aux[j]) {
                prod_arr[k] = aux[i++];
            }
            else prod_arr[k] = aux[j--];
        }
    }
}

int prodExists(int prod_id) {

   return (prod_id >= 0 && prod_id < last_prod_id);
}

int packExists(int pack_id) {

   return (pack_id >= 0 && pack_id < last_pack_id);
}

int main() {

    /* Exit condition */
    while ((c = getchar()) != 'x') {

        switch (c) {
            case 'a':
                do_a();
                break;
            case 'q':
                do_q();
                break;
            case 'N':
                do_N();
                break;
            case 'A':
                do_A();
                break;
            case 'r':
                do_r();
                break;
            case 'R':
                do_R();
                break;
            case 'C':
                do_C();
                break;
            case 'p':
                do_p();
                break;
            case 'E':
                do_E();
                break;
            case 'm':
                do_m();
                break;
            case 'l':
                do_l();
                break;
            case 'L':
                do_L();
                break;
        }
    }
    return 0;
}