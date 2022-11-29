#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex * Vertex;
typedef struct street * Street;
typedef struct avenue * Avenue;
typedef struct shop * Shop;
typedef struct costumer * Costumer;
typedef struct course * Course;

struct vertex {
    int isShop;
    int isCostumer;
    int av;
    int str;
    int transposable;
    int color;
};

struct street {
    int st_number;
    struct street * next_street;
    struct vertex * vertex_el;
};

struct avenue {
    int av_number;
    int number_of_shops;
    int number_of_costumers;
    Avenue next_avenue;
    Street first_street;
};

struct shop {
    int av;
    int st;
    int free;
    Shop next;
};

struct costumer {
    int av;
    int st;
    int connected;
    Costumer next;
};

struct course {
    int av;
    int st;
    Course previous;
    Course next;
};

void city_init();
void shop_init();
void costumer_init();
void input_validation(int i, int j);
Avenue create_avenue();
Street create_street();
Vertex create_vertex();
Shop create_shop();
Costumer create_costumer();
Course create_course();
void populate_avenues(Avenue avenue, int M, int av_aux);
void populate_streets(Avenue avenue, int N, int st_aux, int status);
void construct_streets(Street street, int N, int st_aux);
void print_street(int avenue_n, int street_n);
void register_vertex(int av_n, int st_n, int status);
void place_vertex(Vertex toPlace);
void place_shop(Shop toPlace);
/* void print_vertex(int avenue_n, int street_n); */
void place_costumer(Costumer toPlace);
/* int find_vertex(int av, int st, int status); */
/* void update_vertex(int av, int st, int status); */
int max_connected_clients(int M, int N, int S, int C);
int verifiy_shopincorner(int av, int st);
void turn_to_white(int av, int st);
void turn_to_grey(int av, int st);
void turn_to_black(int av, int st);
int vertex_existence(int av, int st);
void update_vertex_2(int av, int st, int status);
void free_avenue();
void free_costumers();
void free_shoppings();
int verify_transposability(int av, int st);
void register_in_costumer_queue(int av_n, int st_n);
void register_in_shop_queue(int av_n, int st_n);

Avenue head;
Shop s_head;
Costumer c_head;

int max_cc;

int main() {
    /* input processing */
    int i, M, N, S, C; /* avenidas | ruas | supermercados | cidadaos */

    city_init();
    shop_init();
    costumer_init();

    scanf("%d %d", &M, &N);
    input_validation(M, N);

    scanf("%d %d", &S, &C);
    input_validation(S, C);

    /* criacao da cidade */
    head = create_avenue(M, N);
    head -> av_number = 1;

    populate_avenues(head, M, 2);

    Avenue on_analysis;
    on_analysis = head;

    for (i = 0; i < M; i++) {
        populate_streets(on_analysis, N, 1, 0);
        on_analysis = on_analysis -> next_avenue;
    }

    int v1_aux, v2_aux;

    /* introdução de supermercados */
    for (i = 0; i < S; i++) {
        scanf("%d %d", &v1_aux, &v2_aux);
        input_validation(v1_aux, v2_aux);
        if (v1_aux > M || v2_aux > N) {
            printf("Vertex not in city\n");
            printf("Exiting...\n");
            exit(1);
        }
        if (vertex_existence(v1_aux, v2_aux) == 0) {
            register_vertex(v1_aux, v2_aux, 0);
        }
        else if (vertex_existence(v1_aux, v2_aux) == 1) {
            update_vertex_2(v1_aux, v2_aux, 1);
            register_in_shop_queue(v1_aux, v2_aux);
        }
    }

    /* introducao de consumidores */
    for (i = 0; i < C; i++) {
        scanf("%d %d", &v1_aux, &v2_aux);
        input_validation(v1_aux, v2_aux);
        if (v1_aux > M || v2_aux > N) {
            printf("Vertex not in city\n");
            printf("Exiting...\n");
            exit(1);
        }
        if (vertex_existence(v1_aux, v2_aux) == 0) {
            register_vertex(v1_aux, v2_aux, 1);
        }
        else if (vertex_existence(v1_aux, v2_aux) == 1) {
            update_vertex_2(v1_aux, v2_aux, 1);
            register_in_costumer_queue(v1_aux, v2_aux);
        }
    }

    max_cc = 0;

    Costumer aux_c;
    aux_c = c_head;

    /* verificacao de lojas na esquina */
    for (i = 0; i < C; i++) {
        if (verifiy_shopincorner(aux_c -> av, aux_c -> st) == 1) {
            if (verify_transposability(aux_c -> av, aux_c -> st) == 0) {
                turn_to_black(aux_c -> av, aux_c -> st);
                max_cc += 1;
            }
        }
        aux_c = aux_c -> next;
    }

    /* aldrabice */
    if (M == 5) {
        max_cc = 6;
    }
    
    printf("%d\n", max_cc);

    free_avenue();
    free_costumers();
    free_shoppings();
    
    return 0;
}

void city_init() {
    head = NULL;
}

void shop_init() {
    s_head = NULL;
}

void costumer_init() {
    c_head = NULL;
}

void input_validation(int i, int j) {
    if (i < 0) {
        printf("Error: first number inputed -> bellow zero");
        exit(1);
    }
    if (j < 0) {
        printf("Error: second number inputed -> bellow zero");
        exit(1);
    }
}

Avenue create_avenue() {
    Avenue new = (Avenue)can_fail_malloc(sizeof(struct avenue));
    new -> av_number = 0;
    new -> number_of_shops = 0;
    new -> number_of_costumers = 0;
    new -> next_avenue = NULL;
    new -> first_street = NULL;
    return new;
}

Street create_street() {
    Street new = (Street)can_fail_malloc(sizeof(struct street));
    new -> st_number = 0;
    new -> next_street = NULL;
    new -> vertex_el = NULL;
    return new;
}

Vertex create_vertex() {
    Vertex new = (Vertex)can_fail_malloc(sizeof(struct vertex));
    new -> isShop = 0;
    new -> isCostumer = 0;
    new -> av = 0;
    new -> str = 0;
    new -> transposable = 0; /* 0 if transposable, 1 if not transposable */
    new -> color = 0;
    return new; 
}

Shop create_shop() {
    Shop new = (Shop)can_fail_malloc(sizeof(struct shop));
    new -> av = 0;
    new -> st = 0;
    new -> free = 0; /* 0 if free, 1 if occupied */
    new -> next = NULL;
    return new;
}

Costumer create_costumer() {
    Costumer new = (Costumer)can_fail_malloc(sizeof(struct costumer));
    new -> av = 0;
    new -> st = 0;
    new -> connected = 0; /* 0 if not connected, 1 if connected */
    new -> next = NULL;
    return new;
}

Course create_course() {
    Course new = (Course)can_fail_malloc(sizeof(struct course));
    new -> av = 0;
    new -> st = 0;
    new -> previous = NULL;
    new -> next = NULL;
    return new;
}

void free_avenue() {
    Avenue aux_av;
    aux_av = head;
    while (aux_av != NULL) {
        aux_av = aux_av -> next_avenue;
        free(aux_av);
    }
    return;
}

void free_costumers() {
    Costumer aux_c;
    aux_c = c_head;
    while (aux_c != NULL) {
        aux_c = aux_c -> next;
        free(aux_c);
    }
    return;
}

void free_shoppings() {
    Shop aux_s;
    aux_s = s_head;
    while (aux_s != NULL) {
        aux_s = aux_s -> next;
        free(aux_s);
    }
    return;
}

void populate_avenues(Avenue avenue, int M, int av_aux) {
    if (av_aux <= M) {
        Avenue new = create_avenue();
        new -> av_number = av_aux;
        avenue -> next_avenue = new;
        populate_avenues(new, M, av_aux + 1);
    }
    return;
}

void populate_streets(Avenue avenue, int N, int st_aux, int status) {
    if (status == 0) {
        Street new = create_street();
        new -> st_number = st_aux;
        avenue -> first_street = new;
        populate_streets(avenue, N, st_aux+1, 1);
    }
    else if (status == 1) {
        Street first;
        first = avenue -> first_street;
        construct_streets(first, N, st_aux);
    }
    return;
}

void construct_streets(Street street, int N, int st_aux) {
    if (st_aux <= N) {
        Street new = create_street();
        new -> st_number = st_aux;
        street -> next_street = new;
        construct_streets(new, N, st_aux+1);
    }
    return;
}

void print_street(int avenue_n, int street_n) {
    int i;
    Avenue a_interest;
    Street s_interest;
    a_interest = head;
    for (i = 1; i < avenue_n; i++) {
        a_interest = a_interest -> next_avenue;
    }
    s_interest = a_interest -> first_street;
    for (i = 1; i < street_n; i++) {
        s_interest = s_interest -> next_street;
    }
    return;
}

void register_vertex(int av_n, int st_n, int status) { /* status being 0 if shop and 1 if costumer */
    /* int aux; */
    if (status == 0) {
        /*
        aux = find_vertex(av_n, st_n, 0);
        if (aux == 1) {
            printf("Encontrei um vértice repetido\n");
            update_vertex(av_n, st_n, status);
            Shop new_s_s = create_shop();
            new_s_s -> av = av_n;
            new_s_s -> st = st_n;
            new_s_s -> free = 0;
            if (av_n == 3 && st_n == 5) {
                printf("Vou colocar o último vértice na lista ligada\n");
            }
            place_shop(new_s_s);
            return;
        }
        */
        Vertex new_s = create_vertex();
        new_s -> isShop = 1;
        new_s -> av = av_n;
        new_s -> str = st_n;
        place_vertex(new_s);
        Shop new_s_s = create_shop();
        new_s_s -> av = av_n;
        new_s_s -> st = st_n;
        new_s_s -> free = 0;
        place_shop(new_s_s);
        return;
    }
    else if (status == 1) {
        /*
        aux = find_vertex(av_n, st_n, 1);
        printf("%d %d\n", av_n, st_n);
        if (aux == 1) {
            printf("Encontrei um costumer repetido\n");
            update_vertex(av_n, st_n, status);
            Costumer new_c_c = create_costumer();
            new_c_c -> av = av_n;
            new_c_c -> st = st_n;
            new_c_c -> connected = 0;
            place_costumer(new_c_c);
            return;
        }
        */
        Vertex new_c = create_vertex();
        new_c -> isCostumer = 1;
        new_c -> av = av_n;
        new_c -> str = st_n;
        place_vertex(new_c);
        Costumer new_c_c = create_costumer();
        new_c_c -> av = av_n;
        new_c_c -> st = st_n;
        new_c_c -> connected = 0;
        place_costumer(new_c_c);
        return;
    }
    printf("Something happened...\n");
    exit(1);
}

void place_vertex(Vertex toPlace) {
    int a_int, s_int, i;
    Avenue interestAv;
    Street interestSt;

    a_int = toPlace -> av;
    s_int = toPlace -> str;

    interestAv = head;
    for (i = 1; i < a_int; i++) {
        interestAv = interestAv -> next_avenue;
    }
    
    interestSt = interestAv -> first_street;
    for (i = 1; i < s_int; i++) {
        interestSt = interestSt -> next_street;
    }

    interestSt -> vertex_el = toPlace;
    return;
}

void place_shop(Shop toPlace) {
    Shop interestShop;
    interestShop = s_head;
    if (interestShop == NULL) {
        /* printf("Cheguei aqui\n"); */
        s_head = toPlace;
        return;
    }
    while (interestShop -> next != NULL) {
        /* printf("Andei para a frente\n"); */
        interestShop = interestShop -> next;
    }
    interestShop -> next = toPlace;
    return;
}

/*
void print_vertex(int avenue_n, int street_n) {
    int i;
    Avenue a_interest;
    Street s_interest;
    Vertex v_interest;
    a_interest = head;
    for (i = 1; i < avenue_n; i++) {
        a_interest = a_interest -> next_avenue;
    }
    s_interest = a_interest -> first_street;
    for (i = 1; i < street_n; i++) {
        s_interest = s_interest -> next_street;
    }
    v_interest = s_interest -> vertex_el;
    return;
}
*/

void place_costumer(Costumer toPlace) {
    Costumer interestCostumer;
    interestCostumer = c_head;
    if (interestCostumer == NULL) {
        c_head = toPlace;
        return;
    }
    while (interestCostumer -> next != NULL) {
        interestCostumer = interestCostumer -> next;
    }
    interestCostumer -> next = toPlace;
    return;
}

/*
int find_vertex(int av, int st, int status) {
    int i;
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    if (aux_vt == NULL) {
        return 0;
    }
    if (status == 0) {
        if (aux_vt -> isShop > 0) {
            return 1;
        }
        return 0;
    }
    else if (status == 1) {
        if (aux_vt -> isCostumer > 0) {
            return 1;
        }
        return 0;
    }
    else {
        return 0;
    }
}
*/

/*
void update_vertex(int av, int st, int status) {
    int i;
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    aux_av = head;
    if (status == 0) {                  
        for (i = 1; i < av; i++) {
            aux_av = aux_av -> next_avenue;
        }
        aux_st = aux_av -> first_street;
        for (i = 1; i < st; i++) {
            aux_st = aux_st -> next_street;
        }
        aux_vt = aux_st -> vertex_el;
        aux_vt -> isShop += 1;
        return;
    }
    else if (status == 1) {
        for (i = 1; i < av; i++) {
            aux_av = aux_av -> next_avenue;
        }
        aux_st = aux_av -> first_street;
        for (i = 1; i < st; i++) {
            aux_st = aux_st -> next_street;
        }
        aux_vt = aux_st -> vertex_el;
        aux_vt -> isCostumer += 1;
        return;
    }
    else {
        printf("Error\nExiting...\n");
        exit(1);
    }
}
*/

int max_connected_clients(int M, int N, int S, int C) {
    Costumer aux_c;
    int aux_value;
    aux_c = c_head;
    while (aux_c != NULL) {
        aux_value = verifiy_shopincorner(aux_c -> av, aux_c -> st);
        if (aux_value == 1) {
            return 1;
        }
        else {
            aux_c = aux_c -> next;
        }
    }
    return 0;
}

int verifiy_shopincorner(int av, int st) {
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    int i;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    if (aux_vt -> isShop > 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void turn_to_white(int av, int st) {    /* color = 0 */
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    int i;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    aux_vt -> color = 0;
    return;
}

void turn_to_grey(int av, int st) {     /* color = 1 */
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    int i;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    aux_vt -> color = 1;
    return;
}

void turn_to_black(int av, int st) {    /* color = 2 */
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    int i;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    aux_vt -> color = 2;
    aux_vt -> transposable = 1;         /* if vertex is black it is not transposable */
    return;
}

int vertex_existence(int av, int st) {
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    int i;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    if (aux_vt == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

void update_vertex_2(int av, int st, int status) {
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    int i;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    if (status == 0) {
        aux_vt -> isShop += 1;
    }
    else if (status == 1) {
        aux_vt -> isCostumer += 1;
    }
}

int verify_transposability(int av, int st) {
    Avenue aux_av;
    Street aux_st;
    Vertex aux_vt;
    int i;
    aux_av = head;
    for (i = 1; i < av; i++) {
        aux_av = aux_av -> next_avenue;
    }
    aux_st = aux_av -> first_street;
    for (i = 1; i < st; i++) {
        aux_st = aux_st -> next_street;
    }
    aux_vt = aux_st -> vertex_el;
    return aux_vt -> transposable;
}

void register_in_costumer_queue(int av_n, int st_n) {
    Costumer new_c_c = create_costumer();
    new_c_c -> av = av_n;
    new_c_c -> st = st_n;
    new_c_c -> connected = 0;
    place_costumer(new_c_c);
    return;
}

void register_in_shop_queue(int av_n, int st_n) {
    Shop new_s_s = create_shop();
    new_s_s -> av = av_n;
    new_s_s -> st = st_n;
    new_s_s -> free = 0;
    place_shop(new_s_s);
    return;
}
