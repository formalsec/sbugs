#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* CONSTANTS */
    /* Maximum number of Products */
    #define MPRD 10000

    /* Maximum number of orders */
    #define MORD 500

    /* Maximum weight per order */
    #define MWEI 200

    /* Maximum  number of characters per description*/
    #define MCHA 63

    /* Maximum size of the command */
    #define CMDSZ 80

    /* Non existance instance */
    #define NONEXIST -1


/* STATES */
    /* Commands states */
    #define DESC 0
    #define PRICE 1
    #define WEIGHT 2
    #define QTD 3
    #define ID 4
    #define IDO 5

    #define BREAK_PROD_NONEX 6
    #define BREAK_ORD_NONEX 7

/* STRUCTS */
    /* Product */
        typedef struct product{
            /* Id of the product */
            int idp;
            /* Description of the product */
            char desc[MCHA];
            /* Quantity of the product */
            int qtd;
            /* Price of the product */
            int prc;
            /* Weight of the product */
            int wght;
        }prct;


    /* Order */
        typedef struct order{
            /* Id of the order */
            int ido;
            /* Weight of the Order, with a maximum of 200 */
            int wght;
            /* Number of products in the order */
            int nbprdct;
            /* Array of the ID of the products and the respective quantity in the
            order */
            int products[MWEI][2];
        }ordr;


/* Global Variables */
    /* Products in the System */
    prct products[MPRD];

    /* Orders in the System */
    ordr orders[MORD];


/* COMMANDS */
    /* Get the command string */
    void getcmd(char cmd[]);

    /* LOWER CASE COMMANDS */
        /* Command "a" */
        int cmd_a(char cmd[], int next_idp);

        /* Command "q" */
        void cmd_q(char cmd[]);

        /* Command "r" */
        void cmd_r(char cmd[]);

        /* Command "p" */
        void cmd_p(char cmd[]);

        /* Command "m" */
        void cmd_m(char cmd[]);

        /* Command "l" */
        void cmd_l();


    /* UPPER CASE COMMANDS */
        /* Command "N" */
        int cmd_N(int next_ido);

        /* Command "A" */
        void cmd_A(char cmd[]);

        /* Command "R" */
        void cmd_R(char cmd[]);

        /* Command "C" */
        void cmd_C(char cmd[]);

        /* Command "E" */
        void cmd_E(char cmd[]);

        /* Command "L" */
        void cmd_L(char cmd[]);


/* AUXILIARY */
    /* INITIALIZATIONS */
        /* Initializes the products */
        void init_products();

        /* Initializes the orders */
        void init_orders();


    /* STRINGS */
        /* String to Intenger */
        int str_int(char string[]);
   
    /* UPDATORS */
        /* Updates a string */
        int up_string(char string[], char next_char, int free_space);
    
    /* QUICKSORT */
        /* Quicksort */
        void quicksort(prct items[],int (*less)(prct, prct), int left, int right);

        /* Veryfied which is less in the command "l" */
        int less_l(prct prct1, prct prct2);

        /* Veryfied which is less in the command "L" */
        int less_L(prct prct1, prct prct2);

        /* partition */
        int partition(prct items[], int left, int right,int (*less)(prct, prct));

        /* Switch the place of two products */
        int exch(prct items[], int pos1, int pos2);



/* MAIN */
    int main(){
        /* Command */
        char cmd[CMDSZ];

        /* The next product id that hasn't been used */
        int next_idp = 0;
        /* The next order id that hasn't been used */
        int next_ido = 0;
        

        /* INITIALIZATIONS */
            init_products();
            init_orders();

        getcmd(cmd);
        
        /* Maind loop */
        while(cmd[0] != 'x'){
            /* Filter the commands */
            switch(cmd[0]){
                case 'a':
                    next_idp = cmd_a(cmd, next_idp);
                    break;
                
                case 'q':
                    cmd_q(cmd);
                    break;

                case 'r':
                    cmd_r(cmd);
                    break;
                
                case 'p':
                    cmd_p(cmd);
                    break;

                case 'm':
                    cmd_m(cmd);
                    break;

                case 'l':
                    cmd_l();
                    break;
                
                case 'N':
                    next_ido = cmd_N(next_ido);
                    break;

                case 'A':
                    cmd_A(cmd);
                    break;

                case 'R':
                    cmd_R(cmd);
                    break;
                
                case 'C':
                    cmd_C(cmd);
                    break;

                case 'E':
                    cmd_E(cmd);
                    break;

                case 'L':
                    cmd_L(cmd);
                    break;
            }
            getcmd(cmd);
        }
        return 0;
    }


/* COMMANDS FUNCTION */

    /* Get the command string */
    void getcmd(char cmd[]){
        /*
        Arguments:
            char cmd[] -- string -- string to be destructively modified
        */
        char c;
        int i=0;
        while((c = getchar()) != '\n' && c != EOF){
            cmd[i] = c;
            i++;
        }
        cmd[i] = '\0';
    }

    /* LOWER CASE COMMANDS */
        /* Command "a" */
        int cmd_a(char cmd[], int next_idp){
            /* 
            Adds a new products to the system

            Command input: "a desc:price:weight:qtd"

            Arguments:
                cmd -- string -- string containing the command
                next_idp -- int -- the next free space in products

            Returns a string in the terminal("Novo produto <idp>")
                Returns the next product id to be used 
            */
            
            /* Auxiliary variables */
            int i;
            int state = DESC;
            /* String to store each individual step */
            char middle_man[MCHA];
            /* Keep track of the middle_man string */
            int man_trc = 0;

            products[next_idp].idp = next_idp;

            for(i = 2; cmd[i] != '\0';i++){
                switch(state){
                    case DESC:
                        if(cmd[i] == ':'){
                            /*update state*/
                                state = PRICE;
                            /* update middle_man */
                                man_trc = up_string(middle_man,'\0',man_trc);
                            /* define product description */
                            for(man_trc = 0;middle_man[man_trc] != '\0';man_trc++){
                                products[next_idp].desc[man_trc] = middle_man[man_trc];
                            }
                            man_trc = 0;
                        }
                        else{
                            /* update middle_man */
                                man_trc = up_string(middle_man,cmd[i],man_trc);
                        }
                        break;

                    case PRICE:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = WEIGHT;
                            /* Update middle man */
                                man_trc = up_string(middle_man,'\0',man_trc);
                            /* Define product price */
                                products[next_idp].prc = str_int(middle_man);
                        }
                        else{
                            /* Update middle_man */
                                man_trc = up_string(middle_man,cmd[i],man_trc);
                        }
                        break;
                    
                    case WEIGHT:
                        if(cmd[i] == ':'){
                            /* Change state */
                                state = QTD;
                            /* Update middle_man */
                                man_trc = up_string(middle_man,'\0',man_trc);
                            /* Define product weight */
                                products[next_idp].wght = str_int(middle_man);
                        }
                        else{
                            /* Update middle_man */
                                man_trc = up_string(middle_man,cmd[i],man_trc);
                        }
                        break;

                    case QTD:
                        /* Update middle_man */
                            man_trc = up_string(middle_man,cmd[i],man_trc);
                        break;
                }
            }
            /* Update middle_man */
                up_string(middle_man,'\0',man_trc);

            /* Define product quantity */
                products[next_idp].qtd = str_int(middle_man);

            printf("Novo produto %d.\n", next_idp);

            return next_idp+1;
        }


        /* Command "q" */
        void cmd_q(char cmd[]){
            /* 
            Adds more quantity to a product

            Command input: "q idp:qtd"

            Arguments:
                cmd -- string -- string containing the command
            */
            char middle_man[MCHA];
            int middle_trc = 0;
            int state = ID;

            int id, i;

            for(i = 2;cmd[i] != '\0';i++){
                switch(state){
                    case ID:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = QTD;
                            /* Update middle man */
                                middle_trc = up_string(middle_man,'\0',middle_trc);
                            /* Check for errors */
                            id = str_int(middle_man);
                            if(products[id].idp == NONEXIST)
                                state = BREAK_PROD_NONEX;
                        }
                        else{
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        }
                        break;

                    case QTD:
                        /* Update middle_man */
                            middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        break;
                }
            }
            if(state == BREAK_PROD_NONEX)
                printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
            else{
                /* Update middle_man */
                    up_string(middle_man,'\0',middle_trc);
                /* Update product quantity */
                    products[id].qtd += str_int(middle_man);
            }
        }


        /* Command "r" */
        void cmd_r(char cmd[]){
            /* 
            Removes quantity from a product in stock

            Command input: "r idp:qtd"

            Arguments:
                cmd -- string -- string containing the command
            */
            int state = ID;

            int i;

            char middle_man[MCHA];
            int middle_trc = 0;

            int idp, qtd;

            for(i = 2;cmd[i] != '\0';i++){
                switch(state){
                    case ID:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = QTD;
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,'\0',middle_trc);
                            /* Define idp */
                                idp = str_int(middle_man);
                            /* Check for errors */
                                if(products[idp].idp == NONEXIST)
                                    state = BREAK_PROD_NONEX;
                        }
                        else{
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        }
                        break;

                    case QTD:
                        /* Update middle_man */
                            middle_trc = up_string(middle_man,cmd[i], middle_trc);
                        break;
                }
            }

            if(state == BREAK_PROD_NONEX)
                printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
            else{
                /* Update middle_man */
                    up_string(middle_man,'\0',middle_trc);
                /* Define quantity */
                    qtd = str_int(middle_man);

                /* Check for errors */
                    if(products[idp].qtd < qtd)
                        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
                    else{
                        /* Subtract the quantity from the product in stock */
                            products[idp].qtd -= qtd;
                    }
            }
        }


        /* Command "p" */
        void cmd_p(char cmd[]){
            /* 
            Change the price of a product 

            Command input: "p idp:price"

            Arguments:
                cmd -- string -- string containing the command
            */
            int i;
            int state = ID;

            int middle_trc = 0;
            char middle_man[MCHA];

            int idp, price;

            for(i = 2;cmd[i] != '\0';i++){
                switch(state){
                    case ID:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = PRICE;
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,'\0',middle_trc);
                            /* Define Id */
                                idp = str_int(middle_man);
                            /* Check for errors */
                                if(products[idp].idp == NONEXIST)
                                    state = BREAK_PROD_NONEX;
                        }
                        else{
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        }
                        break;

                    case PRICE:
                        /* Update middle_man */
                            middle_trc = up_string(middle_man,cmd[i], middle_trc);
                        break;
                }
            }

            if(state == BREAK_PROD_NONEX)
                printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
            else{
                /* Update middle_man */
                    up_string(middle_man,'\0',middle_trc);
                /* Define price */
                    price = str_int(middle_man);
                /* Update product's price */
                    products[idp].prc = price;
            }
            
        }


        /* Command "m" */
        void cmd_m(char cmd[]){
            /* 
            Lists the order in which a product ocurres more often

            Command input: "m idp"

            Arguments:
                cmd -- string -- string containing the command
            */
            int i, j;
            int middle_trc = 0;
            char middle_man[MCHA];

            int idp;

            int max=0;
            int ido = NONEXIST;
            int o_idp = NONEXIST;
            int nbprdct;

            for(i = 2;cmd[i] != '\0';i++){
                /* Update middle_man */
                    middle_trc = up_string(middle_man,cmd[i],middle_trc);
            }
            /* Update middle_man */
                up_string(middle_man,'\0',middle_trc);
            /* Define id */
                idp = str_int(middle_man);
            /* Check for errors */
            if(products[idp].idp == NONEXIST)
                printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
            else{
                /* Check all orders */
                for(i = 0;orders[i].ido != NONEXIST && i < MORD; i++){
                    nbprdct = orders[i].nbprdct;
                    /* Check all products in each order */
                    for(j = 0;nbprdct != 0 && j < MWEI; j++){
                        if(orders[i].products[j][0] == idp){
                            /* Has the product */
                                if(ido == NONEXIST){
                                    /* Initialize the max, ido ajd o_idp variables */
                                    max = orders[i].products[j][1];
                                    ido = i;
                                    o_idp = j;
                                }
                                if(orders[i].products[j][1] > max){
                                    /* New Max */
                                        max = orders[i].products[j][1];
                                        ido = i;
                                        o_idp = j;
                                }
                        }
                        if(orders[i].products[j][0] != NONEXIST)
                            nbprdct--;
                    }
                }

                if(ido != NONEXIST)
                    printf("Maximo produto %d %d %d.\n", idp, ido, orders[ido].products[o_idp][1]);
            }
        }

        /* Command "l" */
        void cmd_l(){
            /* 
            Lists all products in order of price

            Command input: "l"
            */
            prct new_products[MPRD];

            int sz;

            /* Duplicate products list */
            for(sz = 0;products[sz].idp != NONEXIST && sz < MPRD;sz++){
                new_products[sz] = products[sz];
            }

            /* Make sure the final loop has a quicker exit condition */
            new_products[sz].idp = NONEXIST;

            /* Sort the array */
            quicksort(new_products,less_l,0,sz - 1);

            printf("Produtos\n");

            /* Print the array */
            for(sz = 0;new_products[sz].idp != NONEXIST && sz < MPRD;sz++){
                printf("* %s %d %d\n", new_products[sz].desc, new_products[sz].prc, new_products[sz].qtd);
            }
        }


    /* UPPER CASE COMMANDS */
        /* Command "N" */
        int cmd_N(int next_ido){
            /* 
            Creates new Order

            Command input: "N"

            Arguments:
                next_ido -- int -- next free space in orders

            Returns:
                int -- the next free space in orders
            */
            /* Define id */
                orders[next_ido].ido = next_ido;
            /* Define weight */
                orders[next_ido].wght = 0;
            printf("Nova encomenda %d.\n", next_ido);
            return next_ido + 1;
        }

        /* Command "A" */
        void cmd_A(char cmd[]){
            /* 
            Adds an existant product to an order

            Command input: "A ido:idp:qtd"

            Arguments:
                cmd -- string -- string containing the command
            */
            char middle_man[MCHA];
            int middle_trc = 0;
            int state = IDO;

            int nbprdcts;

            /* store ids */
            int idp, ido, qtd;
            int error=NONEXIST;
            int i;

            for(i = 2;cmd[i] != '\0';i++){
                switch(state){
                    case IDO:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = ID;
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,'\0',middle_trc);
                            /* Check for errors */
                                ido = str_int(middle_man);
                                if(orders[ido].ido == NONEXIST)
                                    error = BREAK_ORD_NONEX;

                        }
                        else{
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        }
                        break;
                    
                    case ID:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = QTD;
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,'\0',middle_trc);
                            /* Check for errors */
                                idp = str_int(middle_man);
                                if(products[idp].idp == NONEXIST){
                                    if(error == NONEXIST)
                                        error = BREAK_PROD_NONEX;
                                }
                        }
                        else{
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,cmd[i],middle_trc);    
                        }
                        break;
                    
                    case QTD:
                        /* Update middle_man */
                            middle_trc = up_string(middle_man,cmd[i],middle_trc);                        
                        break;
                }
            }
            /* In case of errors */
            if(error == BREAK_ORD_NONEX)
                printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
            else if(error == BREAK_PROD_NONEX)
                printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
            else{
                /* Update middle_man */
                    up_string(middle_man,'\0',middle_trc);
                /* Define quantity */
                    qtd = str_int(middle_man);

                /* Check for errors */
                if(products[idp].qtd < qtd)
                    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ido);
                else if(qtd*products[idp].wght + orders[ido].wght > MWEI)
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ido);
                else{
                /* Subtract quantity from the product */
                    products[idp].qtd -= qtd;

                    nbprdcts = orders[ido].nbprdct;

                /* Add product and its quantity to the order */
                    /* Check if it already exists */
                    for(i = 0;nbprdcts != 0 && orders[ido].products[i][0] != idp && i < MORD;i++){
                        if(orders[ido].products[i][0] != NONEXIST){
                            nbprdcts--;
                        }
                    }
                    if(nbprdcts == 0)
                        /* In case it doens't exists check for the next free space */
                        for(i = 0;orders[ido].products[i][0] != NONEXIST && i < MWEI;i++);
                    
                    /* In case its a new product  */
                        if(orders[ido].products[i][0] == NONEXIST)
                            orders[ido].nbprdct++;
                    /* Define id */
                        orders[ido].products[i][0] = idp;
                    /* Define quantity */
                        orders[ido].products[i][1] += qtd;
                    /* Update weight */
                        orders[ido].wght += qtd*products[idp].wght;
                }
            }
        }

        /* Command "R" */
        void cmd_R(char cmd[]){
            /* 
            Removes a product from an order

            Command input: "R ido:idp"

            Arguments:
                cmd -- string -- string containing the command
            */
            int i;
            int state = IDO;
            int error=NONEXIST;

            int idp, ido;

            int nbprdcts;

            char middle_man[MCHA];
            int middle_trc = 0;

            for(i = 2;cmd[i] != '\0';i++){
                switch(state){
                    case IDO:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = ID;
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,'\0',middle_trc);
                            /* Define order's id */
                                ido = str_int(middle_man);
                            /* Check error */
                                if(orders[ido].ido == NONEXIST)
                                    error = BREAK_ORD_NONEX;
                        }
                        else{
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        }
                        break;
                    
                    case ID:
                        /* Update middle_man */
                            middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        break;
                }
            }
            /* Update middle_man */
                up_string(middle_man,'\0',middle_trc);
            /* Define product's id */
                idp = str_int(middle_man);
            if(error == BREAK_ORD_NONEX)
                printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ido);
            else if(products[idp].idp == NONEXIST)
                printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ido);
            else{
                nbprdcts = orders[ido].nbprdct;
                for(i = 0; i < MWEI && nbprdcts != 0;i++){
                    /* Find product */
                    if(orders[ido].products[i][0] == idp){
                        /* Remove product */
                            /* Remove id */
                                orders[ido].products[i][0] = NONEXIST;
                            /* Update weight */
                                orders[ido].wght -= orders[ido].products[i][1] * products[idp].wght;
                            /* Update product quantity */
                                products[idp].qtd += orders[ido].products[i][1];
                            /* Remove quantity */
                                orders[ido].products[i][1] = 0;
                            /* Update number of products in the order */
                                orders[ido].nbprdct--;
                        break;
                    }
                    if(orders[ido].products[i][0] != NONEXIST)
                        nbprdcts--;
                }
            }
        }

        /* Command "C" */
        void cmd_C(char cmd[]){
            /* 
            Calculates the cost of an order

            Command input: "C ido"

            Arguments:
                cmd -- string -- string containing the command
            */
            int i;
            int ido, idp;
            int cost=0;
            int nbrprdcts;
            
            int middle_trc = 0;
            char middle_man[MCHA];

            for(i = 2;cmd[i] != '\0';i++){
                /* Update middle_man */
                    middle_trc = up_string(middle_man,cmd[i],middle_trc);
            }
            /* Update middle_man */
                up_string(middle_man,'\0',middle_trc);
            /* Define ido */
                ido = str_int(middle_man);
            
            if(orders[ido].ido == NONEXIST)
                printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ido);
            else{
                nbrprdcts = orders[ido].nbprdct;

                for(i = 0;i < MWEI && nbrprdcts != 0;i++){               
                    if(orders[ido].products[i][0] != NONEXIST){
                        /* Define product id */
                            idp = orders[ido].products[i][0];
                        /* Update cost */
                            cost += orders[ido].products[i][1] * products[idp].prc;
                            nbrprdcts--;
                    }
                }

                printf("Custo da encomenda %d %d.\n", ido, cost);
            }

        }

        /* Command "E" */
        void cmd_E(char cmd[]){
            /* 
            Lists the description and the quantity of a certain product in an order

            Command input: "E ido:idp"

            Arguments:
                cmd -- string -- string containing the command
            */
            int i;
            int state = IDO;

            int middle_trc = 0;
            char middle_man[MCHA];

            int ido, idp;

            for(i = 2;cmd[i] != '\0';i++){
                switch(state){
                    case IDO:
                        if(cmd[i] == ':'){
                            /* Update state */
                                state = ID;
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,'\0',middle_trc);
                            /* Define ido */
                                ido = str_int(middle_man);
                            /* Check for errrors */
                                if(orders[ido].ido == NONEXIST)
                                    state = BREAK_ORD_NONEX;
                        }
                        else{
                            /* Update middle_man */
                                middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        }
                        break;

                    case ID:
                        /* Update middle_man */
                            middle_trc = up_string(middle_man,cmd[i],middle_trc);
                        break;
                }
            }
            if(state == BREAK_ORD_NONEX)
                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
            else{
                /* Update middle_man */
                    up_string(middle_man,'\0',middle_trc);
                /* Define idp */
                    idp = str_int(middle_man);
                /* Check for errors */
                if(products[idp].idp == NONEXIST)
                    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
                else{
                    /* Find product */
                        for(i = 0;orders[ido].products[i][0] != idp && i < MWEI;i++);
                    /* Print description */
                        printf("%s", products[idp].desc);
                    /* Print quantity */
                    if(i == MWEI && orders[ido].products[i][0] != idp)
                        printf(" 0.\n");
                    else
                        printf(" %d.\n", orders[ido].products[i][1]);
                }
            }
        }


        /* Command "L" */
        void cmd_L(char cmd[]){
            /* 
            Lists the products in a order in alfabetic order

            Command input: "L ido"

            Arguments:
                cmd -- string -- string containing the command
            */
            int ido;
            int i, j;
            int middle_trc = 0;
            char middle_man[MCHA];

            prct new_products[MWEI];
            int nbprdct;

            for(i = 2;cmd[i] != '\0';i++){
                /* Update middle_man */
                    middle_trc = up_string(middle_man,cmd[i],middle_trc);
            }
            /* Update middle_man */
                up_string(middle_man,'\0',middle_trc);
            /* Define order's id */
                ido = str_int(middle_man);

            /* Check for errors */
            if(orders[ido].ido == NONEXIST)
                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ido);
            else{
                /* Duplicate */
                nbprdct = orders[ido].nbprdct;
                i = 0;
                j = 0;
                while(nbprdct != 0){
                    if(orders[ido].products[i][0] != NONEXIST){
                        new_products[j] = products[orders[ido].products[i][0]];
                        nbprdct--;
                        j++;
                    }
                    i++;
                }

                /* Make sure the next 'for' loop has an exit condition */
                new_products[j].idp = NONEXIST;

                /* Sort */
                quicksort(new_products,less_L,0,orders[ido].nbprdct - 1);

                printf("Encomenda %d\n", ido);

                for(i = 0;new_products[i].idp != NONEXIST;i++){
                    for(j = 0;orders[ido].products[j][0] != new_products[i].idp;j++);
                    printf("* %s %d %d\n", new_products[i].desc, new_products[i].prc, orders[ido].products[j][1]);
                }
            }
        }


/* AUXILIARY FUNCTIONS */
    /* INITIALIZERS */
        /* Initializes products */
        void init_products(){
            int i;
            for(i = 0; i < MPRD;i++){
                /* Initialize all the products as Nonexistant */
                products[i].idp = NONEXIST;
            }
        }
        
        /* Initializes orders */
        void init_orders(){
            int i, j;
            for(i = 0;i < MORD;i++){
                orders[i].ido = NONEXIST;
                for(j = 0;j < MWEI;j++){
                    /* Initialize all the products int the order as Nonexistant */
                    orders[i].products[j][0] = NONEXIST;
                }
                /* Their weight and number of products in it as 0 */
                orders[i].wght = 0;
                orders[i].nbprdct = 0;
            }
        }

    /* STRINGS */
        /* String to Intenger */
        int str_int(char string[]){
            /* 
            Arguments:
                string -- array char -- a string that represents a number
            Return:
                int -- The number
            */
            int i;
            int nbr=0;
            for(i = 0;string[i] != '\0';i++){
                nbr *= 10;
                nbr += string[i] - 48;
            }
            return nbr;
        }


    /* UPDATORS */
        /* Updates a string */
        int up_string(char string[], char next_char, int free_space){
            /* 
            Updates a string and returns the value of its next free space
                free_space + 1 -> in a normal case
                0 -> the next_char = '\0'

            Arguments:
                string -- char[] -- string to be updated
                next_char -- char -- char to update the string with
                free_space -- int -- position in the string to be updated
            
            Return:
                if next_char = '\0'
                    0 -- int
                else
                    free-space + 1 -- int
             */
            string[free_space] = next_char;
            if(next_char == '\0')
                return 0;
            else
                return free_space + 1;
        }
    


    /* QUICKSORT */
        void quicksort(prct items[],int (*less)(prct, prct), int left, int right){
            /* 
            Quisorts the items

            Arguments:
                items -- prct[] -- list to be sorted
                less -- int function -- defines the means of comparison
                left -- int -- left position
                right -- int -- right position
             */

            int i;

            if(right > left){
                i = partition(items, left, right,(*less));

                quicksort(items, (*less), left, i - 1);
                quicksort(items, (*less), i + 1, right);
            }
        }

        /* partition */
        int partition(prct items[], int left, int right,int (*less)(prct, prct)){
            /* 
            Parts the list

            Arguments:
                items -- prct[] -- list to be sorted
                less -- int function -- defines the means of comparison
                left -- int -- left position
                right -- int -- right position, position of pivot
             */

            int i = left - 1;
            int j = right;
            /* Pivot */
            prct pivot = items[right];

            while(i < j){
                while((i != right && (*less)(items[++i], pivot)));
                while((j != 0 && (*less)(pivot, items[--j])));

                if(j == left)
                    break;
                
                if(i < j){
                    exch(items,i,j);
                }
            }

            exch(items,i, right);
            return i;
        }


        /* Switch the place of two products */
        int exch(prct items[], int pos1, int pos2){
            /* 
            Switches the position of two products in the list
            
            Arguments:
                items -- prct[] -- the list of products
                pos1, pos2 -- int -- the position of the products to be switched
            */

            prct aux_prct = items[pos1];
            /* The switching */
                items[pos1] = items[pos2];
                items[pos2] = aux_prct;
            return 0;
        }


        int less_l(prct prct1, prct prct2){
            /* 
            The Definition of less for the command "l" 
                price then id
            
            Arguments:
                prct1, prct2 -- prct -- the products to evaluate
            
            Return:
                0 -- prct1 > prct2
                1 -- prct1 < prct2
            */
            if(prct1.prc < prct2.prc)
                return 1;
            else if(prct1.prc == prct2.prc){
                if(prct1.idp  < prct2.idp){
                    return 1;
                }
                return 0;
            }
            return 0;
        }


        int less_L(prct prct1, prct prct2){
            /* 
            The Definition of less for the command "L" 
                alfabetic
            
            Arguments:
                prct1, prct2 -- prct -- the products to evaluate
            
            Return:
                0 -- prct1 > prct2
                1 -- prct1 < prct2
            */

            int i;
            /* The smaller description is considered less than the bigger one */
            for(i = 0;prct1.desc[i] != '\0';i++){
                if(prct2.desc[i] == '\0')
                    return 0;
                else if(prct1.desc[i] < prct2.desc[i])
                    return 1;
                else if(prct1.desc[i] > prct2.desc[i])
                    return 0;
            }
            if(prct2.desc[i] != '\0')
                return 1;
            else
                return 0;
        }