#include <stdio.h>
#include <string.h>
#define MAX_PROD 10000 /*quantidade maxima de produtos no sistema*/
#define MAX_ORDERS 500 /* quantidade maxima de encomendas*/
#define MAX_UNIT_PER_ORDER 200/* maximo de unidades por encomenda*/
#define MAX_DESC 63/*numero maximo de caracteres na descricao de um produto*/

/*-----------------------------TIPOS_ESTRUTURADOS_AUXILIARES----------------------*/

/* TIPO QUE REPRESENTA UM PRODUTO */
typedef struct
{
    char desc [MAX_DESC];/* descricao do produto*/
    int pr;/*pre?o do produto*/
    int ps;/*peso do produto*/
    int st;/*stock do profuto*/
}prod;

/* TIPO QUE REPRESENTA UMA ENCOMENDA*/
typedef struct
{
   int id_prod[MAX_UNIT_PER_ORDER];/*ids dos produtos na encomenda*/
   int st_prod[MAX_UNIT_PER_ORDER];/*quantidades dos produtos na encomenda, pela mesma ordem dos ids dos produtos*/
   int n_prod;/*numero de produtos na encomenda*/
   int ps_e;/*peso total da encomenda*/

}order;

/*---------------------------VARIAVEIS_GLOBAIS--------------------------------*/

prod system_prod [MAX_PROD];
order orders [MAX_ORDERS] = {{{0}, {0}, 0, 0}};
/* last_id -> variavel que contem o id do ultimo produto adicionado ao sistema*/
/* last_order -> variavel que contem o id da ultima encomenda do conjunto*/
/* list_aux -> vetor utilizado nas funcoes de ordenacao , merge_order e merge_sist, como vertor auxiliar*/
/* id_list -> vetor utilizado para conter os ids dos produtos aquando da listagem ordenada das encomendas e do sistema*/
int last_id = -1,last_order = -1, list_aux[MAX_PROD], id_list[MAX_PROD];

/*----------------------------FUNCOES_AUXILIARES--------------------------------*/

/*FUNCAO QUE ADICIONA UM NOVO PRODUTO AO SISTEMA, SEM INPUT -- > SEM OUTPUT */
void add_new_prod(){
    last_id++;
    scanf(" %[^:]:%d:%d:%d" ,system_prod[last_id].desc ,&system_prod[last_id].pr, &system_prod[last_id].ps, &system_prod[last_id].st);
    printf("Novo produto %d.\n", last_id);
}

/*FUNCAO QUE ADICIONA OU REMOVE STOCK A UM PRODUTO DO
SISTEMA OU DE UMA ENCOMENDA, CONJ. DE PRODUTOS x N x N x N -- > SEM OUTPUT */
void add_or_rm_st_prod(prod p1[], int id_p, int st_p, int sig){
    /* se sig == -1 remove, se sig == 1 adiciona*/
    p1[id_p].st += st_p * sig;
}

/*FUNCAO QUE CRIA UMA NOVA ENCOMENDA VAZIA, SEM INPUT -- > SEM OUTPUT*/
void new_order(){
    last_order++;

    printf("Nova encomenda %d.\n", last_order);
}

/*FUNCAO QUE ALTERA O PRE?O DE UM DETERMINADO PRODUTO, N x N --> SEM OUTPUT*/
void ch_price_prod (int id_p, int pr_p){
    system_prod[id_p].pr = pr_p;
}

/*FUNCAO QUE ADICIONA UM PRODUTO A UMA ENCOMENDA, N x N x N --> SEM RETORNO*/
void add_to_order(int id_e, int id_p, int st_p){
    int id, status = 1;/*status -> 1 se o produto nao se encontra na encomenda,
    0 caso contrario*/

    if (system_prod[id_p].st < st_p)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_p, id_e);
    else if ((orders[id_e].ps_e + (system_prod[id_p].ps * st_p)) > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_p, id_e);
    else{
        orders[id_e].ps_e += system_prod[id_p].ps * st_p;
        system_prod[id_p].st -= st_p;
        /*verifica se o produto ja existe na encomenda e, em caso afirmativo,
        adiciona a nova quantidade a quantidade existente */
        for(id = 0; id < orders[id_e].n_prod; id++){
            if(orders[id_e].id_prod[id] == id_p){
                orders[id_e].st_prod[id] += st_p;
                status = 0;
                break;
            }

        }
        /*caso nao exista ainda na encomenda adiciona um novo produto*/
        if (status){
            orders[id_e].id_prod[orders[id_e].n_prod] = id_p;
            orders[id_e].st_prod[orders[id_e].n_prod] = st_p;
            orders[id_e].n_prod++;

        }
    }
}

/*FUNCAO QUE REMOVE UM PRODUTO DE UMA ENCOMENDA, N x N --> SEM RETORNO*/
void rm_prod_order(int id_e, int id_p){
    int id;
    /*procura o produto na encomenda e caso ocorra na mesma troca de posicao com o
    ultimo produto da encomenda e remove-o*/
    for(id = 0; id < orders[id_e].n_prod; id++){
        if(orders[id_e].id_prod[id] == id_p){
            system_prod[id_p].st += orders[id_e].st_prod[id];
            orders[id_e].ps_e -= system_prod[id_p].ps * orders[id_e].st_prod[id];
            if(id != orders[id_e].n_prod - 1){
                orders[id_e].st_prod[id] = orders[id_e].st_prod[orders[id_e].n_prod - 1];
                orders[id_e].id_prod[id] = orders[id_e].id_prod[orders[id_e].n_prod - 1];
            }
            orders[id_e].id_prod[orders[id_e].n_prod - 1] = 0;
            orders[id_e].st_prod[orders[id_e].n_prod - 1] = 0;
            orders[id_e].n_prod--;
            break;

        }
    }
}

/*FUNCAO QUE CALCULA O PRECO DE UMA ENCOMENDA, N --> SEM RETORNO*/
void order_cost(int id_e){
    int id, cost = 0;
    for(id = 0; id < orders[id_e].n_prod; id++){

        cost += system_prod[orders[id_e].id_prod[id]].pr * orders[id_e].st_prod[id];
    }
    printf("Custo da encomenda %d %d.\n", id_e, cost);
}

/*FUNCAO QUE LISTA A DESCRICAO E A QUANTIDADE
 DE UM PRODUTO NUMA ENCOMENDA, N x N --> SEM RETORNO*/
void list_prod_order(int id_e, int id_p){
    int id, status = 1;/*status -> 1 se o produto nao se encontra na encomenda,
    0 caso contrario*/
    for(id = 0; id < orders[id_e].n_prod; id++){
        if(orders[id_e].id_prod[id] == id_p){
            printf("%s %d.\n", system_prod[id_p].desc, orders[id_e].st_prod[id]);
            status = 0;
            break;
        }
    }
    /*caso o produto nao ocorra na encomenda*/
    if(status)
        printf("%s 0.\n", system_prod[id_p].desc);
}

/*FUNCAO QUE INDICA A ENCOMENDA QUE CONTEM A MAIOR QUANTIDADE
DE UM DETERMINADO PRODUTO, N --> SEM RETORNO*/
void order_max_prod(int id_p){
    /*max[0] -> id da encomenda com o valor maximo do produto, se iqual a -1 o produto
    nao se encontra em nenhuma encomenda*/
    /*max[1] -> posicao do vetor na encomenda especifica em max[0] onde se
    encontra o id do produto e a respetiva quantidade*/
    int id_e, id, max[2] = {-1, 0};
    /*procura o produto em todas as encomendas*/
    for(id_e = 0; id_e <= last_order; id_e++){
        for(id = 0; id < orders[id_e].n_prod; id++){
            if(orders[id_e].id_prod[id] == id_p){
                if((max[0] == -1) || (orders[id_e].st_prod[id] > orders[max[0]].st_prod[max[1]])){
                    max[0] = id_e;
                    max[1] = id;
                }
                break;
            }
        }
    }
    /*caso o produto exista em alguma encomenda retorna a encomenda com a
    maior quantidade*/
    if(max[0] != -1)
        printf("Maximo produto %d %d %d.\n", id_p, max[0], orders[max[0]].st_prod[max[1]]);
}

/*FUNCAO QUE CRIA UMA LISTA COM TODOS O 'N', 0 < N < SIZE*/
void make_list_id(int size){
    int id;
    for (id = 0; id <= size; id++)
        id_list[id] = id;
}

/*FUNCAO UTILIZADA NA FUNCAO MERGESORT PARA ORDENAR OS PRODUTOS
DO SISTEMA POR ORDEM CRESCENTE DE PRECO*/
void merge_sist(int a[], int left, int m, int right){
    int i, j, k;
    for(i = m + 1; i > left; i--)
        list_aux[i-1] = a[i-1];
    for(j = m; j < right; j++)
        list_aux[right+m-j] = a[j+1];
    for(k = left; k <= right; k++)
        if((system_prod[list_aux[j]].pr < system_prod[list_aux[i]].pr) && (j > m))
            a[k] = list_aux[j--];
        else if ((system_prod[list_aux[j]].pr >= system_prod[list_aux[i]].pr) && (i < m + 1))
            a[k] = list_aux[i++];
}

/*FUNCAO UTILIZADA NA FUNCAO MERGESORT PARA ORDENAR OS PRODUTOS
DE UMA ENCOMENDA POR ORDEM ALFABETICA DA DECRICAO DOS PRODUTOS*/
void merge_order(int a[], int left, int m, int right, int id_e){
    int i, j, k;
    for(i = m + 1; i > left; i--)
        list_aux[i-1] = a[i-1];
    for(j = m; j < right; j++)
        list_aux[right+m-j] = a[j+1];
    for(k = left; k <= right; k++)
        if((strcmp(system_prod[orders[id_e].id_prod[list_aux[j]]].desc, system_prod[orders[id_e].id_prod[list_aux[i]]].desc) < 0) && (j > m))
            a[k] = list_aux[j--];
        else if ((strcmp(system_prod[orders[id_e].id_prod[list_aux[j]]].desc, system_prod[orders[id_e].id_prod[list_aux[i]]].desc) >= 0) && (i < m + 1))
            a[k] = list_aux[i++];
}

/*FUNCAO DE ORDENACAO POR MERGE SORT*/
void mergesort(int a[], int left, int right, int status, int id_e){
    int m = (right + left) / 2;
    if (right <= left)
        return;
    mergesort(a, left, m, status, id_e);
    mergesort(a, m + 1, right, status, id_e);
    if(status)
        merge_sist(a, left, m, right);
    else
        merge_order(a, left, m, right, id_e);
}

/*FUNCAO QUE LISTA OS PRODUTOS DO SISTEMA PELA ORDEM QUE SAO FORNECIDOS*/
void list_sist(int list_id[]){
    int id;
    printf("Produtos\n");
    for (id = 0; id <= last_id; id++){
        printf("* %s %d %d\n", system_prod[list_id[id]].desc, system_prod[list_id[id]].pr, system_prod[list_id[id]].st);
    }
}

/*FUNCAO QUE LISTA OS PRODUTOS DE UMA ENCOMENDA PELA ORDEM QUE SAO FORNECIDOS*/
void list_order(int id_e, int list_id[]){
    int id;
    printf("Encomenda %d\n", id_e);
    for(id = 0; id < orders[id_e].n_prod; id++){
        printf("* %s %d %d\n", system_prod[orders[id_e].id_prod[list_id[id]]].desc, system_prod[orders[id_e].id_prod[list_id[id]]].pr, orders[id_e].st_prod[list_id[id]]);
    }
}

/*COMANDO q id_p:qtd */
void comand_q(){
    int id_aux, var1_aux;/*variaveis auxiliares*/
    scanf("%d:%d", &id_aux, &var1_aux);

    if (id_aux > last_id)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_aux);
    else
        add_or_rm_st_prod(system_prod, id_aux, var1_aux, 1);

    getchar();
}

/*COMANDO A id_e:id_p:qtd*/
void comand_A(){
    int id_aux, var1_aux, var2_aux;/*variaveis auxiliares*/
    scanf("%d:%d:%d", &var1_aux, &id_aux, &var2_aux);

    if (var1_aux > last_order)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_aux, var1_aux);
    else if (id_aux > last_id)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_aux, var1_aux);
    else
        add_to_order(var1_aux, id_aux, var2_aux);

    getchar();
}

/*COMANDO r id_p:qtd*/
void comand_r(){
    int id_aux, var1_aux;/*variaveis auxiliares*/
    scanf("%d:%d", &id_aux, &var1_aux);

    if (id_aux > last_id)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_aux);
    else if (var1_aux > system_prod[id_aux].st)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", var1_aux, id_aux);
    else
        add_or_rm_st_prod(system_prod, id_aux, var1_aux, -1);

    getchar();
}

/*COMANDO R id_e:id_p*/
void comand_R(){
    int id_aux, var1_aux;/*variaveis auxiliares*/
    scanf("%d:%d", &var1_aux, &id_aux);

    if (var1_aux > last_order)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_aux, var1_aux);
    else if (id_aux > last_id)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_aux, var1_aux);
    else
        rm_prod_order(var1_aux, id_aux);

    getchar();
}

/*COMANDO C id_e*/
void comand_C(){
    int var1_aux;/*variavel auxiliares*/
    scanf("%d", &var1_aux);

    if(var1_aux > last_order)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", var1_aux);
    else
        order_cost(var1_aux);

    getchar();
}

/*COMANDO P id_p:new_pr*/
void comand_p(){
    int id_aux, var1_aux;/*variaveis auxiliares*/
    scanf("%d:%d", &id_aux, &var1_aux);

    if (id_aux > last_id)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_aux);
    else
        ch_price_prod(id_aux, var1_aux);

    getchar();
}

/*COMANDO E id_e:id:p*/
void comand_E(){
    int id_aux, var1_aux;/*variaveis auxiliares*/
    scanf("%d:%d", &var1_aux, &id_aux);

    if (var1_aux > last_order)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", var1_aux);
    else if (id_aux > last_id)
        printf("Impossivel listar produto %d. Produto inexistente.\n", id_aux);
    else
        list_prod_order(var1_aux, id_aux);

    getchar();
}

/*COMANDO m id_p*/
void comand_m(){
    int id_aux;/*variavel auxiliar*/
    scanf("%d", &id_aux);

    if (id_aux > last_id)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_aux);
    else
        order_max_prod(id_aux);

    getchar();
}

/*COMANDO l*/
void comand_l(){
    make_list_id(last_id);
    mergesort(id_list, 0, last_id, 1, 0);
    list_sist(id_list);
    getchar();

}

/*COMANDO L id_e*/
void comand_L(){
    int var1_aux;/*variavel auxiliar*/
    scanf("%d", &var1_aux);

    if(var1_aux > last_order)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", var1_aux);
    else{
        make_list_id(orders[var1_aux].n_prod - 1);
        mergesort(id_list, 0, orders[var1_aux].n_prod - 1, 0, var1_aux);
        list_order(var1_aux, id_list);
    }

    getchar();
}

/*-------------------------------FUNCAO_MAIN-------------------------------------*/
/*FUNCAO QUE LE O COMANDO FURNECIDO E RETORNA O RESPETIVO OUTPUT*/
int main (){

    char c;/*variavel que contem o caracter do comando a executar*/

    while((c = getchar()) != 'x'){

        switch(c){
            /**------------------COMANDOS_PRINCIPAIS---------------*/

            case 'a':
                add_new_prod();
                getchar();/*passar para a linha seguinte (ler o '\n')*/
                break;
            case 'q':
                comand_q();
                break;
            case 'N':
                new_order();
                getchar();
                break;
            case 'A':
                comand_A();
                break;
            case 'r':
                comand_r();
                break;
            case 'R':
                comand_R();
                break;
            case 'C':
                comand_C();
                break;
            case 'p':
                comand_p();
                break;
            case 'E':
                comand_E();
                break;
            case 'm':
                comand_m();
                break;
            case 'l':
                comand_l();
                break;
            case 'L':
                comand_L();
                break;

            /*-----------------------COMANDOS AUXILIARES---------------*/

            /*case 'k':
                make_list_id(last_id);
                list_sist(id_list);
                getchar();
                break;
            case 'K':
                scanf("%d", &var1_aux);
                make_list_id(orders[var1_aux].n_prod - 1);
                list_order(var1_aux, id_list);
                getchar();
                break;*/
        }

    }

    return 0;
}
