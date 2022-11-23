#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
	Projecto 2 - 16 MAIO 2020
		A.S.A. - IST LEIC-TP 2019/2020

	Miguel Pereira Mestre
		IST173942
*/

#include <stdio.h>
#include <unistd.h>

int main() {
 
	/* INICIAR VARIAVEIS NECESSARIAS */

	int m = 0;
	int v = 0;
	int v2 = 0;

	int n = 0;
	int h = 0;
	int h2 = 0;

	int s = 0;
	int s2 = 0;

	int c = 0;
	int c2 = 0;

	int resposta = 0;


	scanf("%d %d", &m, &n);


	int cidadeSuper[m][n]; /* Criamos a cidade para guardar Supers */
	int cidadeCidadao[m][n]; /* Criamos a cidade para guardar Cidadaos */
	int cidadeProibida[m][n]; /* Criamos a cidade para guardar Estradas Cortadas*/

	/* E colocamos tudo a 0 */

	while(v < m){		
		while(h < n){
			cidadeSuper[v][h] = 0;
			cidadeCidadao[v][h] = 0;
			cidadeProibida[v][h] = 0;
			h += 1;
		};
		v += 1;
		h = 0;
	}

	h = 0; 	/* Reset */
	v = 0;	/* Reset */


	scanf("%d %d", &s, &c);	

	/* M - NORTE -> SUL || N - OESTE <- ESTE */

	while(s2 < s){
		scanf("%d %d", &v, &h);
		cidadeSuper[v-1][n-h] = 1;
		s2 += 1;
	}	

	while(c2 < c){
		scanf("%d %d", &v, &h);
		cidadeCidadao[v-1][n-h] = 1;
		c2 += 1;
	}

	h = 0; 	/* Reset */
	v = 0;	/* Reset */
	s2 = 0; /* Reset */
	c2 = 0;	/* Reset */	

	/* 	Encontrar os que tem super no mesmo sitio */

	while(v < m){
		while(h < n){
			if(cidadeSuper[v][h] == 1 && cidadeCidadao[v][h] == 1){
				cidadeProibida[v][h] = -1;
				resposta += 1;
			}
			h += 1;
		}		
		v += 1;
		h = 0;
	}

	h = 0; 	/* Reset */
	v = 0;	/* Reset */

	/* Preparar as posições com cidadãos */

	while(v < m){
		while(h < n){
			if(cidadeCidadao[v][h] == 1){
				cidadeProibida[v][h] = -1;
			}
			h += 1;
		}		
		v += 1;
		h = 0;
	}

	h = 0; 	/* Reset */
	v = 0;	/* Reset */

	/* ALGORITMO FINAL */

	while(v < m){
		while(h < n){

			while(cidadeCidadao[v][h] == 1){

				/* PASSO I - HA LIGACAO ? */
				/* OESTE */

				if(v >= 0 && v < m && h-1 >= 0 && h < m && cidadeProibida[v][h-1] == 0 && cidadeSuper[v][h-1] == 1){
					cidadeProibida[v][h-1] = -1;
					cidadeProibida[v][h] = -1;
					resposta += 1;
				} else {

					/* NORTE */
					if(v-1 >= 0 && v < m && h >= 0 && h < m && cidadeProibida[v-1][h] == 0 && cidadeSuper[v-1][h] == 1){
						cidadeProibida[v-1][h] = -1;
						cidadeProibida[v][h] = -1;
						resposta += 1;
					}	else {

						/* ESTE */ 
						if(v >= 0 && v < m && h >= 0 && h+1 < m && cidadeProibida[v][h+1] == 0 && cidadeSuper[v][h+1] == 1){ 
							cidadeProibida[v][h+1] = -1;
							cidadeProibida[v][h] = -1;
							resposta += 1;
						}	else {

							/* SUL */
							if(v >= 0 && v+1 < m && h >= 0 && h < m && cidadeProibida[v+1][h] == 0 && cidadeSuper[v+1][h] == 1){
								cidadeProibida[v+1][h] = -1;
								cidadeProibida[v][h] = -1;
								resposta += 1;
							} else {

								/* CONFIRMADO QUE NAO HA LIGACAO IMEDIATA */

								/* PASSO II - PROCURAR CAMINHO ATÉ SUPER */

								v2 = v;
								h2 = h;

								while(v2 < m && cidadeCidadao[v][h] == 1){
									while(h2 < n && cidadeCidadao[v][h] == 1){

										cidadeProibida[v][h] = 0;

										while(v2 >= 0 && v2 < m && h2 >= 0 && h2 < n && cidadeProibida[v2][h2] == 0){

											/* VER SE ME POSSO DESLOCAR */
											/* OESTE */
											if(v2 >= 0 && v2 < m && h2-1 >= 0 && h2 < n && cidadeProibida[v2][h2-1] == 0){
												
												if(cidadeSuper[v2][h2-1] == 1){ /* Ver se há Super na direção em que vou */
													resposta += 1;
													cidadeProibida[v2][h2] = -1;
													cidadeProibida[v2][h2-1] = -1;
													cidadeCidadao[v][h] = 0;
												}
												cidadeProibida[v2][h2] = -1;
												h2 = h2-1;

											} else {

												/* NORTE */
												if(v2-1 >= 0 && v2 < m && h2 >= 0 && h2 < n && cidadeProibida[v2-1][h2] == 0){
													if(cidadeSuper[v2-1][h2] == 1){
														resposta += 1;
														cidadeProibida[v2][h2] = -1;
														cidadeProibida[v2-1][h2] = -1;
														cidadeCidadao[v][h] = 0;
													}
													cidadeProibida[v2][h2] = -1;
													v2 = v2-1;

												} else {

													/* ESTE */ 
													if(v2 >= 0 && v2 < m && h2 >= 0 && h2+1 < n && cidadeProibida[v2][h2+1] == 0){
														if(cidadeSuper[v2][h2+1] == 1){
															resposta += 1;
															cidadeProibida[v2][h2] = -1;
															cidadeProibida[v2][h2+1] = -1;
															cidadeCidadao[v][h] = 0;
														}
														cidadeProibida[v2][h2] = -1;
														h2 = h2+1;
														
													
													} else {

														/* SUL */
														if(v2 >= 0 && v2+1 < m && h2 >= 0 && h2 < n && cidadeProibida[v2+1][h2] == 0){
															if(cidadeSuper[v2+1][h2] == 1){
																resposta += 1;
																cidadeProibida[v2][h2] = -1;
																cidadeProibida[v2+1][h2] = -1;
																cidadeCidadao[v][h] = 0;
															}
															cidadeProibida[v2][h2] = -1;
															v2 = v2+1;
															
															
														}
														}
													}
												};
												cidadeCidadao[v][h] = 0;
											}
											cidadeCidadao[v][h] = 0;
										}	
									}
								}
							}
						}
					}
		
			}
			h +=1;
		}
		v += 1;
		h = 0;
	}

printf("%d", resposta);

return 0;

}