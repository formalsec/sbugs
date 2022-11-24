#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

#define CAR_CMD 100
#define CAR_DES 63
#define MAX_PRODS 10000
#define MAX_ENCS 500
#define MAX_PROD_ENC 200
#define PESO_MAX_ENC 200

typedef struct{
	int idp;
	char desc[CAR_DES];
	int preco;
	int peso;
	int stock;
} prod;

typedef struct{
	int idp;
	int qtd;
} prod_enc;

typedef struct{
	int ide;
	prod_enc prods_enc[MAX_PROD_ENC];
	int nprods_enc;
} enc;

int str_para_int(char str[]){				/* funcao que recebe uma string de algarismo e a converte num inteiro */
	int res = 0, i;
	for(i = 0; str[i] != '\0'; i++){
		res = res * 10;
		res = res + str[i] - 48;
	}
	return res;
}

void cmd_a(char cmd[], prod prods[], int nprods){
	int i = 2, j = 0;
	char str_preco[CAR_CMD], str_peso[CAR_CMD], str_stock[CAR_CMD];
	prods[nprods].idp = nprods;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){				/* transformacao de cada um dos argumentos recebidos atraves do comando em strings ou inteiros */
		prods[nprods].desc[j] = cmd[i];
		j++;
	}
	prods[nprods].desc[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_preco[j] = cmd[i];
		j++;
	}
	str_preco[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_peso[j] = cmd[i];
		j++;
	}
	str_peso[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_stock[j] = cmd[i];
		j++;
	}
	str_stock[j] = '\0';
	prods[nprods].preco = str_para_int(str_preco);
	prods[nprods].peso = str_para_int(str_peso);
	prods[nprods].stock = str_para_int(str_stock);
	printf("Novo produto %d.\n", nprods);
}

void cmd_q(char cmd[], prod prods[], int nprods){
	int i = 2, j = 0, idp, qtd;
	char str_idp[CAR_CMD], str_qtd[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_idp[j] = cmd[i];
		j++;
	}
	str_idp[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_qtd[j] = cmd[i];
		j++;
	}
	str_qtd[j] = '\0';
	idp = str_para_int(str_idp);
	qtd = str_para_int(str_qtd);
	if(idp >= nprods) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else{
		for(i = 0; prods[i].idp != idp; i++);				/* obtem o indice em que o produto esta guardado no vetor dos produto com o idp correspondente */
		prods[i].stock += qtd;
	}
}

void cmd_N(enc encs[], int nencs){
	encs[nencs].ide = nencs;
	encs[nencs].nprods_enc = 0;
	printf("Nova encomenda %d.\n", nencs);
}

void cmd_A(char cmd[], prod prods[], int nprods, enc encs[], int nencs){
	int i = 2, j = 0, ide, idp, qtd, esta_na_encomenda = 0, peso = 0, a, b;
	char str_ide[CAR_CMD], str_idp[CAR_CMD], str_qtd[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_ide[j] = cmd[i];
		j++;
	}
	str_ide[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_idp[j] = cmd[i];
		j++;
	}
	str_idp[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_qtd[j] = cmd[i];
		j++;
	}
	str_qtd[j] = '\0';
	ide = str_para_int(str_ide);
	idp = str_para_int(str_idp);
	qtd = str_para_int(str_qtd);
	if(ide >= nencs) printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if(idp >= nprods) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else{
		for(i = 0; prods[i].idp != idp; i++);
		if(prods[i].stock < qtd) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		else{
			for(i = 0; i < encs[ide].nprods_enc; i++){													/* para cada produto com indice i da encomenda ide */
				if(encs[ide].prods_enc[i].idp == idp){														/* se o produto com o idp correspondente ja esta na encomenda guarda o indice em a */
					esta_na_encomenda = 1;
					a = i;
				}
				for(j = 0; j < nprods; j++) if(prods[j].idp == encs[ide].prods_enc[i].idp) b = j;			/* encontra o indice do produto i da encomenda no vetor dos produtos e guarda-o em b */
				peso += prods[b].peso * encs[ide].prods_enc[i].qtd;
			}
			for(j = 0; j < nprods; j++) if(prods[j].idp == idp) b = j;				/* encontra o indice no vetor dos produtos do produto com idp correspondente */
			if(peso + prods[b].peso * qtd > PESO_MAX_ENC) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
			else if(esta_na_encomenda){
				encs[ide].prods_enc[a].qtd += qtd;
				prods[b].stock -= qtd;
			}
			else{
				encs[ide].prods_enc[encs[ide].nprods_enc].idp = idp;
				encs[ide].prods_enc[encs[ide].nprods_enc].qtd = qtd;
				prods[b].stock -=qtd;
				encs[ide].nprods_enc++;				
			}
		}
	}
}

void cmd_r(char cmd[], prod prods[], int nprods){
	int i = 2, j = 0, idp, qtd;
	char str_idp[CAR_CMD], str_qtd[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_idp[j] = cmd[i];
		j++;
	}
	str_idp[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_qtd[j] = cmd[i];
		j++;
	}
	str_qtd[j] = '\0';
	idp = str_para_int(str_idp);
	qtd = str_para_int(str_qtd);
	if(idp >= nprods) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	else{
		for(i = 0; prods[i].idp != idp; i++);				/* i fica com o indice do produto com idp no vetor dos produtos */
		if(prods[i].stock < qtd) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
		else{
			prods[i].stock -= qtd;
		}
	}
}

void cmd_R(char cmd[], prod prods[], int nprods, enc encs[], int nencs){
	int i = 2, j = 0, ide, idp, esta_na_encomenda = 0, a, qtd;
	char str_ide[CAR_CMD], str_idp[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_ide[j] = cmd[i];
		j++;
	}
	str_ide[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_idp[j] = cmd[i];
		j++;
	}
	str_idp[j] = '\0';
	ide = str_para_int(str_ide);
	idp = str_para_int(str_idp);
	if(ide >= nencs) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	else if(idp >= nprods) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	else{
		for(i = 0; i < encs[ide].nprods_enc; i++){				/* para cada produto da encomenda */
			if(encs[ide].prods_enc[i].idp == idp){					/* se o idp for o idp correspondente */
				esta_na_encomenda = 1;								/* guarda o indice em a (indice dos produtos da encomenda) */
				a = i;
			}
		}
		if(esta_na_encomenda){
			qtd = encs[ide].prods_enc[a].qtd;
			encs[ide].prods_enc[a].qtd = 0;
			for(i = 0; prods[i].idp != idp; i++);				/* i fica com o indice do produto que tem o idp correspondente */
			prods[i].stock += qtd;			
		}
	}
}

void cmd_C(char cmd[], prod prods[], enc encs[], int nencs){
	int i = 2, j = 0, ide, preco = 0;
	char str_ide[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_ide[j] = cmd[i];
		j++;
	}
	str_ide[j] = '\0';
	ide = str_para_int(str_ide);
	if(ide >= nencs) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else{
		for(i = 0; i < encs[ide].nprods_enc; i++){							/* para cada produto da encomenda */
			for(j = 0; prods[j].idp != encs[ide].prods_enc[i].idp; j++);		/* j fica com o indice do produto no vetor dos produtos que tem idp igual ao produto da encomenda */
			preco += encs[ide].prods_enc[i].qtd * prods[j].preco;
		}
		printf("Custo da encomenda %d %d.\n", ide, preco);
	}
}

void cmd_p(char cmd[], prod prods[], int nprods){
	int i = 2, j = 0, idp, preco;
	char str_idp[CAR_CMD], str_preco[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_idp[j] = cmd[i];
		j++;
	}
	str_idp[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_preco[j] = cmd[i];
		j++;
	}
	str_preco[j] = '\0';
	idp = str_para_int(str_idp);
	preco = str_para_int(str_preco);
	if(idp >= nprods) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	else{
		for(i = 0; prods[i].idp != idp; i++);				/* i fica com o indice do produto que tem idp correspondente no vetor dos produtos */
		prods[i].preco = preco;
	}
}

void cmd_E(char cmd[], prod prods[], int nprods, enc encs[], int nencs){
	int i = 2, j = 0, ide, idp, esta_na_encomenda = 0, a;
	char str_ide[CAR_CMD], str_idp[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_ide[j] = cmd[i];
		j++;
	}
	str_ide[j] = '\0';
	i++;
	j = 0;
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_idp[j] = cmd[i];
		j++;
	}
	str_idp[j] = '\0';
	ide = str_para_int(str_ide);
	idp = str_para_int(str_idp);
	if(ide >= nencs) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if(idp >= nprods) printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	else{
		for(i = 0; prods[i].idp != idp; i++);				/* i fica com o indicie do produto que tem idp correspondente no vetor dos produtos */
		for(j = 0; j < encs[ide].nprods_enc; j++){			/* para cada produto da encomenda com indice j */
			if(encs[ide].prods_enc[j].idp == idp){				/* se o seu idp e igual ao idp correspondente */
				esta_na_encomenda = 1;							/* guarda o seu indice em a */
				a = j;
			}
		}
		if(esta_na_encomenda) printf("%s %d.\n", prods[i].desc, encs[ide].prods_enc[a].qtd);
		else printf("%s 0.\n", prods[i].desc);
	}
}

void cmd_m(char cmd[], int nprods, enc encs[], int nencs){
	int i = 2, j = 0, idp, max = 0, ide;
	char str_idp[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_idp[j] = cmd[i];
		j++;
	}
	str_idp[j] = '\0';
	idp = str_para_int(str_idp);
	if(idp >= nprods) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	else{
		for(i = 0; i < nencs; i++){																	/* para cada encomenda i */
			for(j = 0; j < encs[i].nprods_enc; j++){													/* para cada produto j da encomenda i */
				if(encs[i].prods_enc[j].idp == idp && encs[i].prods_enc[j].qtd > max){						/* se o seu idp for o correspondente e a sua quantidade superior ao maior encontrado ate agora */
					max = encs[i].prods_enc[j].qtd;
					ide = i;
				}
			}
		}
		if(max > 0) printf("Maximo produto %d %d %d.\n", idp, ide, max);
	}
}

void merge_preco(prod prods[], int l, int m, int r){
	prod prods_aux[MAX_PRODS];
	int i, j, k;
	for(i = l; i <= m; i++){
		prods_aux[i] = prods[i];
	}
	for(i = m + 1; i <= r; i++){
		prods_aux[i] = prods[i];
	}
	i = l;
	j = m + 1;
	k = l;
	while(i <= m && j <= r){
		if(prods_aux[i].preco == prods_aux[j].preco){
			if(prods_aux[i].idp < prods_aux[j].idp){
				prods[k] = prods_aux[i];
				i++;
			}
			else{
				prods[k] = prods_aux[j];
				j++;
			}
		}
		else{
			if(prods_aux[i].preco < prods_aux[j].preco){
				prods[k] = prods_aux[i];
				i++;
			}
			else{
				prods[k] = prods_aux[j];
				j++;
			}
		}
		k++;
	}
	if(i > m){
		for(; j <= r; j++){
			prods[k] = prods_aux[j];
			k++;
		}
	}
	else{
		for(; i <= m; i++){
			prods[k] = prods_aux[i];
			k++;
		}
	}
}

void msort_preco(prod prods[], int l, int r){
	int m = (r + l)/2;
	if(r <= l) return;
	msort_preco(prods, l, m);
	msort_preco(prods, m + 1, r);
	merge_preco(prods, l, m, r);
}

void cmd_l(prod prods[], int nprods){
	int i;
	msort_preco(prods, 0, nprods - 1);
	printf("Produtos\n");
	for(i = 0; i < nprods; i++){
		printf("* %s %d %d\n", prods[i].desc, prods[i].preco, prods[i].stock);
	}
}

void merge_alfa(enc encs[], prod prods[], int l, int m, int r, int ide){
	prod_enc prods_enc_aux[MAX_PROD_ENC];
	int i, j, k, a, b, c, idp1, idp2;
	for(i = l; i <= m; i++){
		prods_enc_aux[i] = encs[ide].prods_enc[i];
	}
	for(i = m + 1; i<= r; i++){
		prods_enc_aux[i] = encs[ide].prods_enc[i];
	}
	i = l;
	j = m + 1;
	k = l;
	while(i <= m && j <= r){
		idp1 = prods_enc_aux[i].idp;
		idp2 = prods_enc_aux[j].idp;
		for(b = 0; idp1 != prods[b].idp; b++);
		for(c = 0; idp2 != prods[c].idp; c++);
		for(a = 0; prods[b].desc[a] == prods[c].desc[a] && a < 63; a++);
		if(prods[b].desc[a] < prods[c].desc[a]){
			encs[ide].prods_enc[k] = prods_enc_aux[i];
			i++;
		}
		else{
			encs[ide].prods_enc[k] = prods_enc_aux[j];
			j++;
		}
		k++;
	}
	if(i > m){
		for(; j <= r; j++){
			encs[ide].prods_enc[k] = prods_enc_aux[j];
			k++;
		}
	}
	else{
		for(; i <= m; i++){
			encs[ide].prods_enc[k] = prods_enc_aux[i];
			k++;
		}
	}
}

void msort_alfa(enc encs[], prod prods[], int l, int r, int ide){
	int m = (r + l)/2;
	if(r <= l) return;
	msort_alfa(encs, prods, l, m, ide);
	msort_alfa(encs, prods, m + 1, r, ide);
	merge_alfa(encs, prods, l, m, r, ide);
}

void cmd_L(char cmd[], prod prods[], enc encs[], int nencs){
	int i = 2, j = 0, ide;
	char str_ide[CAR_CMD];
	for(; cmd[i] != ':' && cmd[i] != '\n'; i++){
		str_ide[j] = cmd[i];
		j++;
	}
	str_ide[j] = '\0';
	ide = str_para_int(str_ide);
	if(ide >= nencs) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else{
		msort_alfa(encs, prods, 0, encs[ide].nprods_enc - 1, ide);
		if(ide >= nencs) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		else{
			printf("Encomenda %d\n", ide);
			for(i = 0; i < encs[ide].nprods_enc; i++){
				if(encs[ide].prods_enc[i].qtd > 0) printf("* %s %d %d\n", prods[encs[ide].prods_enc[i].idp].desc, prods[encs[ide].prods_enc[i].idp].preco, encs[ide].prods_enc[i].qtd);
			}
		}
	}
}

int main(){
	char cmd[CAR_CMD];
	prod prods[MAX_PRODS];
	enc encs[MAX_ENCS];
	int nprods = 0, nencs = 0;
	while(1){
		fgets(cmd, CAR_CMD, stdin);
		switch(cmd[0]){
			case 'a':
				cmd_a(cmd, prods, nprods);
				nprods++;
			break;
			case 'q':
				cmd_q(cmd, prods, nprods);
			break;
			case 'N':
				cmd_N(encs, nencs);
				nencs++;
			break;
			case 'A':
				cmd_A(cmd, prods, nprods, encs, nencs);
			break;
			case 'r':
				cmd_r(cmd, prods, nprods);
			break;
			case 'R':
				cmd_R(cmd, prods, nprods, encs, nencs);
			break;
			case 'C':
				cmd_C(cmd, prods, encs, nencs);
			break;
			case 'p':
				cmd_p(cmd, prods, nprods);
			break;
			case 'E':
				cmd_E(cmd, prods, nprods, encs, nencs);
			break;
			case 'm':
				cmd_m(cmd, nprods, encs, nencs);
			break;
			case 'l':
				cmd_l(prods, nprods);
			break;
			case 'L':
				cmd_L(cmd, prods, encs, nencs);
			break;
			case 'x':
				return 0;
		}
	}
}
