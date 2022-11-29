#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_INPUT_SIZE 1000000 

struct produto{ 
    int id; 
    char descr[64]; 
    int preco; 
    int peso; 
    int qtd; 
};

/* PRODUTOS */
struct produto products[10000]; 

/* ENCOMENDAS */
struct produto encomendas[500][10000];

int get_descr(char *body, char *descr){ /* body of command */
    int position;

    /* Get position of first ':' */
    char *position_ptr = strchr(body, ':');
    position = position_ptr - body; 

    /* Obtain substring corresponding to description */
    strncpy ( descr, body, position );
    descr[position] = '\0';

    /* Return position of second ':' */
    return position;
}

void get_price(char *body, int* preco, int* position){ 
    int f=1; 
    char c; 
    char price[100] = { '0' }; 

    *position += 1;

    while (f == 1){
        c=body[*position];
        strncat(price, &c, 1);

        *position += 1;

        if ( body[*position] == ':' ){
            f=0;
            break;
        }
    }

    *preco=atoi(price);
}

void get_weight(char *body, int* peso, int* position){
    int f=1;
    char c, weight[100]={ '0' };

    *position += 1;

    while (f == 1){
        c=body[*position];
        strncat(weight, &c, 1);

        *position+=1;

        if ( body[*position] == ':' ){
            f=0;
            break;
        }
    }

    *peso=atoi(weight);
}

void get_qtt(char *body, int* qtd, int* position){
    int f=1;
    char c, qtt[100] = { '0' }; 

    *position += 1;

    while (f == 1){
        c=body[*position];
        strncat(qtt, &c, 1);

        *position+=1;

        if ( body[*position] == '\0' ){
            f=0;
            break;
        }
    }

    *qtd=atoi(qtt);
}

void processInput(){ 
    char line[MAX_INPUT_SIZE], body_of_command[MAX_INPUT_SIZE]; 
    int position, idp = 0, ide = 0, i = 0;
    
    printf("\nProcessing commands...\n");
    while (fgets(line, sizeof(line)/sizeof(char), stdin)) {  
        char token; 
        
        sscanf(line, "%c %s", &token, body_of_command); 

        if (token == 'a'){ /* usar switch */
            /* Store product's id*/
            products[idp].id = idp;

            /* Store product's description*/
            position = get_descr(body_of_command, products[idp].descr); 
            
            /* Store product's price*/
            get_price(body_of_command, &products[idp].preco, &position);

            /* Store product's weight*/
            get_weight(body_of_command, &products[idp].peso, &position);

            /* Store product's quantity*/
            get_qtt(body_of_command, &products[idp].qtd, &position);

            idp++;
            fprintf(stdout, "Novo produto %d.\n", idp); 
        }
        if ( token == 'A' ){ 
            int this_ide, this_idp, this_qtt, this_weight;
            int size, f = 1, position = 0, i=0, found=0, found_in_order=0; 
            char c; 
            char this_idp_s[4] = { '0' }; 
            char this_qtt_s[100] = { '0' }; 
            char this_ide_s[500] = { '0' }; 

            /* Get command's input */
            while (f == 1){
                c=body_of_command[position];
                strncat(this_ide_s, &c, 1);

                position += 1;

                if ( body_of_command[position] == ':' ){
                    f=0;
                    break;
                }
            }

            this_ide=atoi(this_ide_s);

            f = 1;
            position += 1;

            while (f == 1){
                c=body_of_command[position];
                strncat(this_idp_s, &c, 1);

                position += 1;

                if ( body_of_command[position] == ':' ){
                    f=0;
                    break;
                }
            }

            this_idp=atoi(this_idp_s);

            f = 1;
            position += 1;

            while (f == 1){
                c=body_of_command[position];
                strncat(this_qtt_s, &c, 1);

                position += 1;

                if ( body_of_command[position] == '\0' ){
                    f=0;
                    break;
                }
            }

            this_qtt=atoi(this_qtt_s);

            /* Check whether the order exists */
            for (; i< ide; i++ ){
                if ( this_ide == i ){
                    found = 1;
                }
            }
            if ( !found ){
                fprintf(stdout,"Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", this_idp, this_ide);
            }

            i = 0;
            found = 0;

            /* Check whether the product exists */ 
            for (; i< idp; i++ ){
                if ( this_idp == i ){
                    found = 1;

                    size = sizeof(encomendas[this_ide])/sizeof(encomendas[this_ide][0]);
                    /* Check whether the product exists in order*/ 
                    i = 0;
                    for (; i < size; i++){
                        if ( encomendas[this_ide][i].id == this_idp && encomendas[this_ide][i].qtd != 0){
                            found_in_order = 1;

                            /* Check if there is enough stock availiable */
                            if ( this_qtt > products[this_idp].qtd ){
                                fprintf(stdout,"Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", this_idp, this_ide);
                            }

                            /* If there is, check whether the quantity added will exceed the maximum weight allowed */
                            else{
                                this_weight = encomendas[this_ide][i].peso * ( this_qtt + encomendas[this_ide][i].qtd );
                                
                                if ( this_weight > 200 ){
                                    fprintf(stdout,"Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", this_idp, this_ide);
                                }
                                /* If it doesn't exceed, add quantity ordered to product's availiable stock */
                                else { 
                                    encomendas[this_ide][this_idp].qtd += this_qtt;
                                }
                            }
                        }
                    }
                    if ( found_in_order == 0){
                        /* Check if there is enough stock availiable */
                        if ( this_qtt > products[this_idp].qtd ){
                            fprintf(stdout,"Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", this_idp, this_ide);
                        }
                        /* If there is, check whether the quantity added will exceed the maximum weight allowed */
                        else{
                            this_weight = products[this_idp].peso * this_qtt ;
                            
                            if ( this_weight > 200 ){
                                fprintf(stdout,"Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", this_idp, this_ide);
                            }
                            /* If it doesn't exceed, add quantity ordered to product's availiable stock */
                            else { 
                                encomendas[this_ide][this_idp].id = this_idp;
                                strcpy(encomendas[this_ide][this_idp].descr, products[this_idp].descr);
                                encomendas[this_ide][this_idp].peso = products[this_idp].peso;
                                encomendas[this_ide][this_idp].preco = products[this_idp].preco;
                                encomendas[this_ide][this_idp].qtd = this_qtt;

                                products[this_idp].qtd -= this_qtt;
                            }  
                        }
                    }         
                }
            }
            if ( !found ){
                fprintf(stdout,"Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", this_idp, this_ide);
            }
        }
        if ( token == 'C'){ 
            int this_ide, this_cost = 0, i = 0;

            sscanf(body_of_command, "%d", &this_ide);

            if ( this_ide < ide ){
                for(; i<idp; i++){ 
                    if ( encomendas[this_ide][i].qtd != 0){
                        this_cost += encomendas[this_ide][i].preco * encomendas[this_ide][i].qtd;
                    }
                }
                
                fprintf(stdout, "Custo da encomenda %d %d.\n", this_ide, this_cost);
            }
            else{
                fprintf(stdout,"Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", this_ide);
            }
        }
        if ( token == 'E' ){
            int this_ide, this_idp;
            int f = 1, position = 0, i=0, found=0; 
            char c; 
            char this_idp_s[4] = { '0' }; 
            char this_ide_s[500] = { '0' }; 

            /* Get command's input */
            while (f == 1){
                c=body_of_command[position];
                strncat(this_ide_s, &c, 1);

                position += 1;

                if ( body_of_command[position] == ':' ){
                    f=0;
                    break;
                }
            }

            this_ide=atoi(this_ide_s);

            f = 1;
            position += 1;

            while (f == 1){
                c=body_of_command[position];
                strncat(this_idp_s, &c, 1);

                position += 1;

                if ( body_of_command[position] == '\0' ){
                    f=0;
                    break;
                }
            }

            this_idp=atoi(this_idp_s);

            /* Check whether the order exists */
            for (; i< ide; i++ ){
                if ( this_ide == i ){
                    found = 1;
                }
            }
            if ( !found ){
                fprintf(stdout,"Impossivel listar encomenda %d. Encomenda inexistente.\n", this_ide);
            }

            i = 0;
            found = 0;

            /* Check whether the product exists */ 
            for (; i< idp; i++ ){
                if ( this_idp == i ){
                    found = 1;
                    fprintf(stdout, "%s %d.\n", encomendas[this_ide][this_idp].descr, encomendas[this_ide][this_idp].qtd);
                }
            }
            if ( !found ){
                fprintf(stdout,"Impossivel listar produto %d. Produto inexistente.\n", this_idp);
            }
        }
        if ( token == 'l'){  
            int temp_preco, temp_qtd, k, j = 0;
            char *temp[64];
            struct produto ordered_products[10000];
            i = 0;
            *temp = (char *)can_fail_malloc(sizeof(char) * 64);
            

            for (; j < idp; j++){
                strcpy(ordered_products[j].descr, products[j].descr);
                ordered_products[j].preco = products[j].preco;
                ordered_products[j].qtd = products[j].qtd;
            }
            

            j = 0;
            for (; j < idp; ++j)
            {
                for (k = j + 1; k < idp; ++k)
                {
                    if (ordered_products[j].preco > ordered_products[k].preco)
                    {
                        temp_preco = ordered_products[j].preco;
                        strcpy(*temp, ordered_products[j].descr);
                        temp_qtd = ordered_products[j].qtd;

                        ordered_products[j].preco = ordered_products[k].preco;
                        strcpy(ordered_products[j].descr, ordered_products[k].descr);
                        ordered_products[j].qtd = ordered_products[k].qtd;

                        ordered_products[k].preco = temp_preco;
                        strcpy(ordered_products[k].descr, *temp);
                        ordered_products[k].qtd = temp_qtd;
                    }
                }
            }

            fprintf(stdout, "Produtos\n");
            for(; i < idp; i++){ 
                fprintf(stdout, "* %s %d %d\n", ordered_products[i].descr, ordered_products[i].preco, ordered_products[i].qtd); 
            }

            free(*temp);
        }
        if ( token == 'L'){ 
            char *temp[64];
            struct produto encomenda_ordenada[10000];
            int this_ide, count, temp_peso, temp_qtd, temp_preco, temp_id, i = 0, j = 0;

            *temp = (char *)can_fail_malloc(sizeof(char) * 64);

            sscanf(body_of_command, "%d", &this_ide);
            
            if ( this_ide < ide ){
                fprintf(stdout, "Encomenda %d\n", this_ide);
                for (; i < idp; i++){
                    if ( encomendas[this_ide][i].qtd != 0){
                        strcpy(encomenda_ordenada[i].descr, encomendas[this_ide][i].descr);
                        encomenda_ordenada[i].preco = encomendas[this_ide][i].preco;
                        encomenda_ordenada[i].peso = encomendas[this_ide][i].peso;
                        encomenda_ordenada[i].qtd = encomendas[this_ide][i].qtd;
                    }
                }
                
                count = i-1;

                i = 0;
                for(; i<=count;i++){
                    for(j=i+1;j<=count;j++){
                        if(strcmp(encomenda_ordenada[i].descr, encomenda_ordenada[j].descr)>0){
                            strcpy(*temp,encomenda_ordenada[i].descr);
                            temp_preco = encomenda_ordenada[i].preco;
                            temp_peso = encomenda_ordenada[i].peso;
                            temp_qtd = encomenda_ordenada[i].qtd;
                            temp_id = encomenda_ordenada[i].id;

                            strcpy(encomenda_ordenada[i].descr, encomenda_ordenada[j].descr);
                            encomenda_ordenada[i].preco = encomenda_ordenada[j].preco;
                            encomenda_ordenada[i].peso = encomenda_ordenada[j].peso;
                            encomenda_ordenada[i].qtd = encomenda_ordenada[j].qtd;
                            encomenda_ordenada[i].id = encomenda_ordenada[j].id;

                            strcpy(encomenda_ordenada[j].descr,*temp);
                            encomenda_ordenada[j].preco = temp_preco;
                            encomenda_ordenada[j].peso = temp_peso;
                            encomenda_ordenada[j].qtd = temp_qtd;
                            encomenda_ordenada[j].id = temp_id;
                        }
                    }
                }

                i = 0;
                for(; i<idp; i++){ 
                    if ( encomenda_ordenada[i].qtd != 0){
                        fprintf(stdout, "* %s %d %d\n", encomenda_ordenada[i].descr, encomenda_ordenada[i].preco, encomenda_ordenada[i].qtd); 
                    }
                }
            }
            else{
                fprintf(stdout,"Impossivel listar encomenda %d. Encomenda inexistente.\n", this_ide);
            }

            free(*temp);
        }
        if (token == 'm'){
            int this_idp, i = 0, j = 0, found = 0, found_in_order = 0, this_qtd = 0, this_ide;
            sscanf(body_of_command, "%d", &this_idp);

            for(; i < idp; i++){
                if ( i == this_idp ){
                    found = 1;
                    
                    for(; j < ide; j++){
                        if ( encomendas[i][this_idp].qtd > this_qtd ){
                            found_in_order = 1;
                            this_qtd = encomendas[j][this_idp].qtd;
                            this_ide = j;
                        }
                    }
                    
                    if (found_in_order == 1){
                        fprintf(stdout,"Maximo produto %d %d %d.\n", this_idp, this_ide, encomendas[this_ide][this_idp].qtd);
                    }
                }
            }
            if ( found == 0){
                fprintf(stdout,"Impossivel listar maximo do produto %d. Produto inexistente.\n", this_idp);
            }
        }
        if (token == 'N'){
            fprintf(stdout, "Nova encomenda %d.\n", ide);
            ide++;
        }
        if (token == 'p'){
            int this_idp, this_preco, i = 0, found = 0;
            sscanf(body_of_command, "%d:%d", &this_idp, &this_preco);

            for(; i < idp; i++){
                if ( i == this_idp ){
                    found = 1;
                    products[this_idp].preco = this_preco;
                    
                    i = 0;
                    for(; i < ide; i++){
                        if ( encomendas[i][this_idp].preco != 0){
                            encomendas[i][this_idp].preco = this_preco;
                        }
                    }
                }
            }
            if ( found == 0){
                fprintf(stdout,"Impossivel alterar preco do produto %d. Produto inexistente.\n", this_idp);
            }
        }
        if (token == 'q'){
            int this_idp, this_qtt, f = 1, position = 0, i=0, found=0; 
            char c; 
            char this_idp_s[4] = { '0' }; 
            char this_qtt_s[100] = { '0' }; 

            /* Get command's input */
            while (f == 1){
                c=body_of_command[position];
                strncat(this_idp_s, &c, 1);

                position+=1;

                if ( body_of_command[position] == ':' ){
                    f=0;
                    break;
                }
            }

            this_idp=atoi(this_idp_s);

            f = 1;
            position += 1;

            while (f == 1){
                c=body_of_command[position];
                strncat(this_qtt_s, &c, 1);

                position+=1;

                if ( body_of_command[position] == '\0' ){
                    f=0;
                    break;
                }
            }

            this_qtt=atoi(this_qtt_s);

            /* Check whether the product exists */
            for (; i< idp; i++ ){
                if ( this_idp == i ){
                    found = 1;
                    products[this_idp].qtd += this_qtt;
                }
            }
            if ( !found ){
                fprintf(stdout,"Impossivel adicionar produto %d ao stock. Produto inexistente.\n", this_idp);
            }
        }
        if (token == 'r'){
            int this_idp, this_qtt, i = 0, found = 0;
            sscanf(body_of_command, "%d:%d", &this_idp, &this_qtt);

            for(; i < idp; i++){
                if ( i == this_idp ){
                    if ( this_qtt > products[this_idp].qtd ){
                        fprintf(stdout, "Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", this_qtt, this_idp);
                    }
                    else{
                        products[this_idp].qtd -= this_qtt;
                    }
                    found = 1;
                }
            }
            if ( found == 0){
                fprintf(stdout,"Impossivel remover stock do produto %d. Produto inexistente.\n", this_idp);
            }
        }
        if (token == 'R'){
            int this_idp, this_ide, i = 0, found_order = 0, found_prdct = 0;
            sscanf(body_of_command, "%d:%d", &this_ide, &this_idp);

            for(; i < ide; i++){
                if ( i == this_ide ){
                    found_order = 1;

                    i = 0;
                    for (; i < idp; i++){
                        if ( this_idp == i ){
                            found_prdct = 1;

                            encomendas[this_ide][this_idp].id = -1;
                            encomendas[this_ide][this_idp].peso = 0;
                            strcpy(encomendas[this_ide][this_idp].descr,"");
                            encomendas[this_ide][this_idp].preco = 0;
                            encomendas[this_ide][this_idp].qtd = 0;
                        }
                    }
                    if ( found_prdct == 0){
                        fprintf(stdout,"Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", this_idp, this_ide);
                    }
                }
            }
            if ( found_order == 0){
                fprintf(stdout,"Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", this_idp, this_ide);
            }
        }


        if (token == 'x'){
            printf("\nShutting down... Good bye! Adeus!\n"); 

            exit(EXIT_SUCCESS);
        }  
    }
}

int main() {
    processInput();

    return 0;

}


