#include <stdio.h>
#include <string.h>
#define MAXPRODUTOS 10000
#define MAXDESCRICAO 63
#define ZERO 0
#define UM 1
#define MAXIDE 500
#define PESOMAX 200


typedef struct {
    char desc[MAXDESCRICAO];
    int preco;
    int peso;
    int qtd;
}produto;

typedef struct {
    produto ve[PESOMAX];
    int prodstot;
    int pesotot;
}encomenda;
     
void a(int idplivre, produto v[]) {
    int preco, peso, qtd;
    char desc[MAXDESCRICAO] = {'0'};
    scanf("%[^:]:%d:%d:%d", desc, &preco, &peso, &qtd);
    getchar();
    strcpy(v[idplivre].desc, desc);
    v[idplivre].preco = preco;
    v[idplivre].peso = peso;
    v[idplivre].qtd = qtd;
    printf("Novo produto %d.\n", idplivre);
}

void q(int idplivre, produto v[]) {
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    getchar();
    if (idp < idplivre) 
        v[idp].qtd += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

void A(encomenda e[], produto v[], int idelivre, int idplivre) {
    int ide, idp, qtd, i, existe = ZERO, indice;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    getchar();
    if(ide >= idelivre) 
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if(idp >= idplivre)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if(v[idp].qtd < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if(e[ide].pesotot + v[idp].peso * qtd > PESOMAX)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else {
        for(i = ZERO; i < e[ide].prodstot; i++) 
            if(strcmp(e[ide].ve[i].desc, v[idp].desc) == 0) {
                existe = UM;
                indice = i;
        }
        if(existe)
            e[ide].ve[indice].qtd += qtd;
        else {
        e[ide].ve[e[ide].prodstot] = v[idp];
        e[ide].ve[e[ide].prodstot].qtd = qtd;
        e[ide].prodstot ++;
        }
        e[ide].pesotot += v[idp].peso * qtd;
        v[idp].qtd -= qtd;
    }
}

void r(produto v[], int idplivre) {
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    getchar();
    if(idp >= idplivre) 
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if(v[idp].qtd < qtd) 
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        v[idp].qtd -= qtd;
}

void R(encomenda e[], produto v[], int idelivre, int idplivre) {
    int ide, idp, i, indice;
    scanf("%d:%d", &ide, &idp);
    getchar();
    if(idelivre <= ide)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if(idplivre <= idp)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else {
        for(i = ZERO; i < e[ide].prodstot; i++) 
            if(strcmp(e[ide].ve[i].desc, v[idp].desc) == ZERO) {
                indice = i;
                e[ide].pesotot -= e[ide].ve[indice].qtd * e[ide].ve[indice].peso;
                v[idp].qtd += e[ide].ve[indice].qtd;
                while(indice < (e[ide].prodstot - UM)){
                    e[ide].ve[indice] = e[ide].ve[indice + UM];
                    indice++;
                }
                e[ide].prodstot--;
            }
    }
}

void C(encomenda e[],int idelivre) {
    int ide, precotot = ZERO, i = ZERO;
    scanf("%d", &ide);
    getchar();
    if(ide >= idelivre)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else {
        while(i < e[ide].prodstot) {
            precotot += e[ide].ve[i].qtd * e[ide].ve[i].preco;
            i++;
        }
        printf("Custo da encomenda %d %d.\n", ide, precotot);
    }
}

void p(encomenda e[], produto v[], int idelivre, int idplivre) {
    int idp, preco, i, j;
    scanf("%d:%d", &idp, &preco);
    getchar();
    if(idplivre <= idp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else {
        v[idp].preco = preco;
        for(i = ZERO; i < idelivre; i++)
            for(j = ZERO; j < e[i].prodstot; j++)
                if(strcmp(v[idp].desc, e[i].ve[j].desc) == ZERO)
                    e[i].ve[j].preco = preco;

    }
}

void E(encomenda e[], produto v[], int idelivre, int idplivre) {
    int ide, idp, i, qtd = ZERO;
    scanf("%d:%d", &ide, &idp);
    getchar();
    if(idelivre <= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if(idplivre <= idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else {
        for(i = ZERO; i < e[ide].prodstot; i++) 
            if(strcmp(e[ide].ve[i].desc, v[idp].desc) == ZERO)
                qtd = e[ide].ve[i].qtd;
        printf("%s %d.\n", v[idp].desc, qtd);
    }
}

void m(encomenda e[], produto v[], int idelivre, int idplivre) {
    int idp, idemin, contador1, contador2, qtdmax = ZERO;
    scanf("%d", &idp);
    getchar();
    if(idplivre <= idp)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else if(idelivre > ZERO) {
        for(contador1 = ZERO; contador1 < idelivre; contador1++) 
            for(contador2 = ZERO; contador2 < e[contador1].prodstot; contador2++)
                if(strcmp(e[contador1].ve[contador2].desc, v[idp].desc) == ZERO)
                    if(e[contador1].ve[contador2].qtd > qtdmax) {
                        qtdmax = e[contador1].ve[contador2].qtd;
                        idemin = contador1;
                    }
        if(qtdmax > ZERO)
            printf("Maximo produto %d %d %d.\n", idp, idemin, qtdmax);
    }
}

void l(produto v[], int idplivre) {
    int j, i, contador;
    produto p;
    for (i = ZERO; i < idplivre; i++) 
        for (j = ZERO; j < idplivre - UM - i; j++) 
            if(v[j].preco > v[j+UM].preco) {
                p = v[j];
                v[j] = v[j+UM];
                v[j+UM] = p;
            }
    printf("Produtos\n");
    for(contador = ZERO; contador < idplivre; contador++)
        printf("* %s %d %d\n", v[contador].desc, v[contador].preco, v[contador].qtd);
}

void L(encomenda e[], int idelivre) {
    int ide, i, j, feito, cont;
    produto t;
    scanf("%d", &ide);
    getchar();
    if(idelivre <= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else {
        for (i = ZERO; i < (e[ide].prodstot-UM); i++) {
            feito = 1;
            for (j = ZERO; j < (e[ide].prodstot-UM) + (ZERO-i); j++)
                if(strcmp(e[ide].ve[j].desc, e[ide].ve[j+UM].desc)>ZERO) {
                    t = e[ide].ve[j];
                    e[ide].ve[j] = e[ide].ve[j+UM];
                    e[ide].ve[j+UM] = t;
                    feito = 0;
                }
            if (feito) break;
        }
        printf("Encomenda %d\n", ide);
        for (cont = ZERO; cont < e[ide].prodstot; cont++)
            printf("* %s %d %d\n", e[ide].ve[cont].desc, e[ide].ve[cont].preco, e[ide].ve[cont].qtd);

    }
}

    
int main() {
    char cmd;
    int idplivre = ZERO, idelivre = ZERO;
    produto v[MAXPRODUTOS];
    encomenda e[MAXIDE];
    while((cmd = getchar())) {
        getchar();
        switch(cmd) {
            case 'a':
                a(idplivre, v);
                idplivre++;
                break;
            case 'q':
                q(idplivre, v);
                break;
            case 'N':
                printf("Nova encomenda %d.\n", idelivre);
                e[idelivre].pesotot = ZERO;
                e[idelivre].prodstot = ZERO;
                idelivre++;
                break;
            case 'A':
                A(e, v, idelivre, idplivre);
                break;
            case 'r':
                r(v, idplivre);
                break;
            case 'R':
                R(e, v, idelivre, idplivre);
                break;
            case 'C':
                C(e, idelivre);
                break;
            case 'p':
                p(e, v, idelivre, idplivre);
                break;
            case 'E':
                E(e, v, idelivre, idplivre);
                break;
            case 'm':
                m(e, v, idelivre, idplivre);
                break;
            case 'l':
                l(v, idplivre);
                break;
            case 'L':
                L(e, idelivre);
                break;
            case 'x':
                return ZERO;
        }
    
    }
    return ZERO;
}

