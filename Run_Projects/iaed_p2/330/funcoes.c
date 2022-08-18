#include "funcoes.h"

/******************************************************************************
 *
 * Funcoes auxiliares.
 *
 *****************************************************************************/
/******************************************************************************
 *
 * Funcao vitoria_eq1 - procura as duas equipas, adiciona uma vitoria
 * 	                    a equipa1 e retira uma da equipa2.
 *
 *****************************************************************************/
void vitoria_eq1(Hequipas *TabEquipas, NodeJ *tmpJ){
	int index_eq1, index_eq2;
	NodeE *tmpE;
	index_eq1 = hash(tmpJ->aponta_jogo->equipa1, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq1];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa1) == 0){
			tmpE->aponta_equipa->vitorias += 1;/*Adiciona-lhe uma vitoria*/
			break;
		}
		tmpE = tmpE->proximo;
	}
	index_eq2 = hash(tmpJ->aponta_jogo->equipa2, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq2];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa2) == 0){
			if(tmpE->aponta_equipa->vitorias > 0){
				tmpE->aponta_equipa->vitorias -= 1;/*Retira lhe uma vitoria*/
				break;
			}
		}
		tmpE = tmpE->proximo;
	}
}
/******************************************************************************
 *
 * Funcao vitoria_eq2 - procura as duas equipas, adiciona uma vitoria
 * 	                    a equipa2 e retira uma da equipa1.
 *
 *****************************************************************************/
void vitoria_eq2(Hequipas *TabEquipas, NodeJ *tmpJ){
	int index_eq1, index_eq2;
	NodeE *tmpE;
	index_eq1 = hash(tmpJ->aponta_jogo->equipa1, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq1];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa1) == 0){
			if(tmpE->aponta_equipa->vitorias > 0){
				tmpE->aponta_equipa->vitorias -= 1;/*Retira lhe uma vitoria*/
				break;
			}
		}
		tmpE = tmpE->proximo;
	}
	index_eq2 = hash(tmpJ->aponta_jogo->equipa2, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq2];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa2) == 0){
			tmpE->aponta_equipa->vitorias += 1;/*Adiciona-lhe uma vitoria*/
			break;
		}
		tmpE = tmpE->proximo;
	}
}
/******************************************************************************
 *
 * Funcao empate1 - procura a equipa1 e adiciona-lhe uma vitoria.
 *
 *****************************************************************************/
void empate1(Hequipas *TabEquipas, NodeJ *tmpJ){
	int index_eq1;
	NodeE *tmpE;
	index_eq1 = hash(tmpJ->aponta_jogo->equipa1, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq1];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa1) == 0){
			tmpE->aponta_equipa->vitorias += 1;/*Adiciona-lhe uma vitoria*/
			break;
		}
		tmpE = tmpE->proximo;
	}
}
/******************************************************************************
 *
 * Funcao empate2 - procura a equipa2 e adiciona-lhe uma vitoria.
 *
 *****************************************************************************/
void empate2(Hequipas *TabEquipas, NodeJ *tmpJ){
	int index_eq2;
	NodeE *tmpE;
	index_eq2 = hash(tmpJ->aponta_jogo->equipa2, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq2];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa2) == 0){
			tmpE->aponta_equipa->vitorias += 1;/*Adiciona-lhe uma vitoria*/
			break;
		}
		tmpE = tmpE->proximo;
	}
}
/******************************************************************************
 *
 * Funcao retira_eq1 - procura a equipa1 e retira-lhe uma vitoria.
 *
 *****************************************************************************/
void retira_eq1(Hequipas *TabEquipas, NodeJ *tmpJ){
	int index_eq1;
	NodeE *tmpE;
	index_eq1 = hash(tmpJ->aponta_jogo->equipa1, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq1];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa1) == 0){
			if(tmpE->aponta_equipa->vitorias > 0){
				tmpE->aponta_equipa->vitorias -= 1;/*Retira lhe uma vitoria*/
				break;
			}
			
		}
		tmpE = tmpE->proximo;
	}
}

/******************************************************************************
 *
 * Funcao retira_eq2 - procura a equipa2 e retira-lhe uma vitoria.
 *
 *****************************************************************************/
void retira_eq2(Hequipas *TabEquipas, NodeJ *tmpJ){
	int index_eq2;
	NodeE *tmpE;
	index_eq2 = hash(tmpJ->aponta_jogo->equipa2, TabEquipas->capacidade);
	tmpE = TabEquipas->cabecas[index_eq2];
	while(tmpE != NULL){/*procura equipa*/
		if(strcmp(tmpE->aponta_equipa->nome, tmpJ->aponta_jogo->equipa2) == 0){
			if(tmpE->aponta_equipa->vitorias > 0){
				tmpE->aponta_equipa->vitorias -= 1;/*Retira lhe uma vitoria*/
				break;
			}
		}
		tmpE = tmpE->proximo;
	}
}
/******************************************************************************
 *
 * Funcao atualizador - atualiza os resultados dos jogos.
 *
 *****************************************************************************/
void atualizador(NodeJ *tmpJ, int pontos1_novos, int pontos2_novos){
	tmpJ->aponta_jogo->pontos1 = pontos1_novos;
	tmpJ->aponta_jogo->pontos2 = pontos2_novos; /*Muda os pontos antigos para os novos*/
}

/******************************************************************************
 *
 * Funcao remove_jLista - apaga a lista que contem os jogos.
 * (Adaptada do codigo disponivel nas aulas).
 *
 *****************************************************************************/
void remove_jLista(Cabeca_cauda *extremos_lista_jogos, NodeJ *tmpJ){
	if(tmpJ->aponta_jogo->anterior == NULL){
		/*Caso o jogo seja o primeiro a aparecer na lista passa-se o ponteiro
		que corresponde a esse jogo para o proximo tornando-se o proximo o primeiro*/
		extremos_lista_jogos->cabeca = tmpJ->aponta_jogo->proximo;
	}
	else{
		/*Caso nao seja o ponteiro que indica o jogo anterior ao atual passa a apontar
		para o proximo jogo ao atual*/
		tmpJ->aponta_jogo->anterior->proximo = tmpJ->aponta_jogo->proximo;
	}
	if(tmpJ->aponta_jogo->proximo == NULL){
		/*Caso o jogo seja o ultimo so precisamos de fazer com que o ponteiro
		para o atual passe a apontar para o anterior*/
		extremos_lista_jogos->cauda = tmpJ->aponta_jogo->anterior;
	}
	else{
		/*Caso nao seja o ponteiro anterior do proximo jogo passa a apontar
		para o jogo anterior ao atual*/
		tmpJ->aponta_jogo->proximo->anterior = tmpJ->aponta_jogo->anterior;
	}
	/*Liberta todos os ponteiros*/
	free(tmpJ->aponta_jogo->nome);
	free(tmpJ->aponta_jogo->equipa1);
	free(tmpJ->aponta_jogo->equipa2);
	free(tmpJ->aponta_jogo);
}
/******************************************************************************
 *
 * Funcao remove_jHash - remove o jogo da hashtable correspondente.
 *
 *****************************************************************************/
void remove_jHash(Hjogos *TabJogos, NodeJ *tmpJ, int index){ 
	NodeJ *atual = TabJogos->cabecas[index], *aux = TabJogos->cabecas[index];
    if (atual == tmpJ){ /*Se for o jogo pretendido*/
        TabJogos->cabecas[index] = atual->proximo;  
        free(atual);
        /*o jogo que antes era o proximo passa agora
         a ser o atual apos a libertacao do atual*/                
    }
    else{
    	while (atual != tmpJ){ /*Descobre o jogo pretendido*/
	    	aux = atual; /*aux leva o endereco do atual*/
	        atual = atual->proximo; 
	    }
	    aux->proximo = atual->proximo;
	    /*aux permanece sempre atras do atual e sao feitas as
	     ligacoes necessarias para se puder eliminar o atual*/
	    free(atual);
    }  
} 

/******************************************************************************
 *
 * Funcoes auxiliares para a funcao g
 * (Adaptadas do codigo disponivel do comando 'man qsort').
 *
 *****************************************************************************/
/******************************************************************************
 *
 * Funcao myCompare - forma um metodo de comparacao de strings 
 *					  que sera utilizado para ordenar as equipas
 *					  no qsort.
 *
 *****************************************************************************/
static int myCompare(const void* a, const void* b){ 
	return strcmp(*(const char**)a, *(const char**)b); 
} 

/******************************************************************************
 *
 * Funcao sort - recorre ao qsort para ordenar as equipas
 *
 *****************************************************************************/  
void sort(char* arr[], int n) { 
	qsort(arr, n, sizeof(const char*), myCompare); 
} 

/******************************************************************************
 *
 * Funcoes principais.
 *
 *****************************************************************************/
/******************************************************************************
 *
 * Funcao a - insere um jogo no sistema.
 *
 *****************************************************************************/
void a(Hequipas *TabEquipas, Hjogos *TabJogos, Cabeca_cauda *extremos_lista_jogos, int *NL){
	char nome_aux[MAX_NAME], equipa1_aux[MAX_NAME], equipa2_aux[MAX_NAME];
	int pontos1, pontos2, index;
	NodeE *tmp;
	getchar();
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_aux, equipa1_aux, equipa2_aux, &pontos1, &pontos2);
	if (procuraJ(TabJogos, nome_aux)){
		printf("%d Jogo existente.\n", *NL); /*Caso o jogo ja esteja no sistema*/
		*NL += 1;
	}
	else{
		if(!(procuraE(TabEquipas, equipa1_aux) && procuraE(TabEquipas, equipa2_aux))){
			printf("%d Equipa inexistente.\n", *NL);
			/*Caso nao esteja ainda temos que verificar se as equipas estao*/ 
			*NL += 1;
		}
		else{/*Se este jogo for possivel e nao estiver no sistema passamos a introduzi-lo*/
			hash_insertJ(TabJogos, extremos_lista_jogos, nome_aux, equipa1_aux, equipa2_aux, pontos1, pontos2);
			/*Abaixo faz se a verificacao da equipa vencedora para que as suas vitorias sejam
			atualizadas*/
			if (pontos1 > pontos2){
				index = hash(equipa1_aux, TabEquipas->capacidade);
				tmp = TabEquipas->cabecas[index];
				while(tmp != NULL){
					if(strcmp(tmp->aponta_equipa->nome, equipa1_aux) == 0){
						tmp->aponta_equipa->vitorias +=1;
						break;
					}
					tmp = tmp->proximo;
				}
			}
			else if (pontos2 > pontos1){
				index = hash(equipa2_aux, TabEquipas->capacidade);
				tmp = TabEquipas->cabecas[index];
				while(tmp != NULL){
					if(strcmp(tmp->aponta_equipa->nome, equipa2_aux) == 0){
						tmp->aponta_equipa->vitorias +=1;
						break;
					}
					tmp = tmp->proximo;
				}
			}
			*NL += 1;
		}
	}
}

/******************************************************************************
 *
 * Funcao A - insere uma equipa no sistema.
 *
 *****************************************************************************/
Equipa *A(Hequipas *TabEquipas, Equipa *cabeca_equipas, int *NL){
	char buffer[MAX_NAME];
	getchar();
	scanf("%[^:\n]", buffer);
	if (procuraE(TabEquipas, buffer)){
		printf("%d Equipa existente.\n", *NL);
		*NL += 1;
		return cabeca_equipas; /*No caso da Equipa ja estar no sistema*/
	}
	else{
		*NL += 1;
		return hash_insertE(TabEquipas, cabeca_equipas, buffer);
		/*No caso da Equipa nao estar no sistema iremos introduzi-la*/

	}
}

/******************************************************************************
 *
 * Funcao l - lista todos os jogos do sistema.
 *
 *****************************************************************************/
void l(int *NL, Cabeca_cauda *extremos_lista_jogos){
	Jogo *tmp = extremos_lista_jogos->cabeca;
	while(tmp != NULL){ /*Percorrer toda a lista de jogos ate encontrar o elem NULL
	que significa que nao ha mais elem nas lista e imprimi-los um a um*/
		printf("%d %s %s %s %d %d\n", *NL, tmp->nome, tmp->equipa1,
		 tmp->equipa2, tmp->pontos1, tmp->pontos2);
		tmp = tmp->proximo; 
	}
	*NL += 1;
}

/******************************************************************************
 *
 * Funcao p - procura o jogo pedido no sistema.
 *
 *****************************************************************************/
void p(Hjogos *TabJogos, int *NL){
	char nome_aux[MAX_NAME];
	int index;
	NodeJ *tmp;
	getchar();
	scanf("%[^:\n]", nome_aux);
	if (procuraJ(TabJogos, nome_aux)){ /*Procura o jogo na hashtable*/
		index = hash(nome_aux, TabJogos->capacidade);
		tmp = TabJogos->cabecas[index];
		while(tmp != NULL){
			if(strcmp(tmp->aponta_jogo->nome, nome_aux) == 0){
				printf("%d %s %s %s %d %d\n", *NL, tmp->aponta_jogo->nome, tmp->aponta_jogo->equipa1,
					tmp->aponta_jogo->equipa2, tmp->aponta_jogo->pontos1, tmp->aponta_jogo->pontos2);
					break; /*Caso o jogo exista sera obtido da hashtable e impresso como pedido*/
			}
			tmp = tmp->proximo;
		}
		*NL += 1;
	}
	else{ /*Caso o jogo nao exista na hashtable apresenta se este erro*/
		printf("%d Jogo inexistente.\n", *NL);
		*NL += 1;
	}

}

/******************************************************************************
 *
 * Funcao P - procura a equipa pedida no sistema.
 *
 *****************************************************************************/
/*(Funcao com codigo semelhante a funcao p mas a procura faz-se
na hashtable das equipas em vez de ser na hashtable dos jogos)*/
void P(Hequipas *TabEquipas, int *NL){
	char buffer[MAX_NAME];
	int index;
	NodeE *tmp;
	getchar();
	scanf("%[^:\n]", buffer);
	if (procuraE(TabEquipas, buffer)){
		index = hash(buffer, TabEquipas->capacidade);
		tmp = TabEquipas->cabecas[index];
		while(tmp != NULL){
			if(strcmp(tmp->aponta_equipa->nome, buffer) == 0){
				printf("%d %s %d\n", *NL, tmp->aponta_equipa->nome, tmp->aponta_equipa->vitorias);
				break;
			}
			tmp = tmp->proximo;
		}
		*NL += 1;
	}
	else{
		printf("%d Equipa inexistente.\n", *NL);
		*NL += 1;
	}

}

/******************************************************************************
 *
 * Funcao r - remove um jogo do sistema.
 *
 *****************************************************************************/
void r(int *NL, Hjogos *TabJogos, Hequipas *TabEquipas, Cabeca_cauda *extremos_lista_jogos){
	char nome_aux[MAX_NAME];
	int index;
	NodeJ *tmpJ;
	getchar();
	scanf("%[^:\n]", nome_aux);
	index = hash(nome_aux, TabJogos->capacidade);
	tmpJ = TabJogos->cabecas[index];
	if(!(procuraJ(TabJogos, nome_aux))){ /*Caso o jogo nao exista da erro*/
		printf("%d Jogo inexistente.\n", *NL);
		*NL += 1;
	}
	else{
		while(tmpJ != NULL){ /*Procura o jogo*/
			if(strcmp(tmpJ->aponta_jogo->nome, nome_aux) == 0){
				if(tmpJ->aponta_jogo->pontos1 > tmpJ->aponta_jogo->pontos2){ /*Caso tenha havido vitoria da equipa1*/
					retira_eq1(TabEquipas, tmpJ); /*Funcao que remove vitoria da 1 equipa*/
					remove_jLista(extremos_lista_jogos, tmpJ); /*Apaga da lista de jogos o jogo pretendido*/
					remove_jHash(TabJogos, tmpJ, index);/*Apaga da hashtable de jogos o jogo pretendido*/
					*NL += 1;
					return;
				}
				else if(tmpJ->aponta_jogo->pontos2 > tmpJ->aponta_jogo->pontos1){/*Caso tenha havido vitoria da equipa2*/
					retira_eq2(TabEquipas, tmpJ);/*Funcao que remove vitoria da 2 equipa*/
					remove_jLista(extremos_lista_jogos, tmpJ);
					remove_jHash(TabJogos, tmpJ, index);
					*NL += 1;
					return;
				}
				else{/*Caso o jogo seja um empate*/
					remove_jLista(extremos_lista_jogos, tmpJ);
					remove_jHash(TabJogos, tmpJ, index);
					*NL += 1;
					return;
				}
			}
			tmpJ = tmpJ->proximo;
		}
	}
}

/******************************************************************************
 *
 * Funcao s - altera o resultado do jogo pretendido.
 *
 *****************************************************************************/
void s(Hequipas *TabEquipas, Hjogos *TabJogos, int *NL){
	char nome_aux[MAX_NAME];
	int index, pontos1_novos, pontos2_novos;
	NodeJ *tmpJ;
	getchar();
	scanf("%[^:\n]:%d:%d", nome_aux, &pontos1_novos, &pontos2_novos);
	if (procuraJ(TabJogos, nome_aux)){
		index = hash(nome_aux, TabJogos->capacidade);
		tmpJ = TabJogos->cabecas[index];
		while(tmpJ != NULL){
			if(strcmp(tmpJ->aponta_jogo->nome, nome_aux) == 0){
				/*Apos obter o jogo pretendido temos que comparar 
				o novo resultado com o antigo para saber que alteracoes
				fazer nas vitorias das equipas*/
				if(pontos1_novos > pontos2_novos){/*Caso das novas pontuacoes resultarem
				numa vitoria para a equipa1*/
					if(tmpJ->aponta_jogo->pontos2 > tmpJ->aponta_jogo->pontos1){
						vitoria_eq1(TabEquipas, tmpJ);
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					else if(tmpJ->aponta_jogo->pontos1 == tmpJ->aponta_jogo->pontos2){
						empate1(TabEquipas, tmpJ);
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					else{
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					break;
				}
				else if (pontos2_novos > pontos1_novos){/*Caso das novas pontuacoes resultarem
				numa vitoria para a equipa2*/
					if(tmpJ->aponta_jogo->pontos1 > tmpJ->aponta_jogo->pontos2){
						vitoria_eq2(TabEquipas, tmpJ);
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					else if(tmpJ->aponta_jogo->pontos1 == tmpJ->aponta_jogo->pontos2){
						empate2(TabEquipas, tmpJ);
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					else{
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					break;
				}
				else{/*Caso das novas pontuacoes resultarem
				num empate*/
					if(tmpJ->aponta_jogo->pontos1 > tmpJ->aponta_jogo->pontos2){
						retira_eq1(TabEquipas, tmpJ);
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					else if(tmpJ->aponta_jogo->pontos2 > tmpJ->aponta_jogo->pontos1){
						retira_eq2(TabEquipas, tmpJ);
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					else{
						atualizador(tmpJ, pontos1_novos, pontos2_novos);
					}
					break;
				}
			}
			tmpJ = tmpJ->proximo;
		}
	}
	else{/*Caso o Jogo pedido nao exista no sistema*/
		printf("%d Jogo inexistente.\n", *NL);
	}
	*NL += 1;
}

/******************************************************************************
 *
 * Funcao g - encontras as equipas com mais vitorias e ordena-as por ordem
 *			  lexicografica.
 *
 *****************************************************************************/
void g(int *NL, Equipa *cabeca_equipas){
	Equipa *tmp = cabeca_equipas, *tmp2 = cabeca_equipas, *tmp3 = cabeca_equipas;
	int max = 0, contador_equipas = 0, i = 0;
	char **equipas_maior; 
	if(tmp != NULL){
		while(tmp != NULL){
			if(tmp->vitorias > max){
				max = tmp->vitorias;
			}
			tmp = tmp->proximo;
		} /*Encotra o valor max de vitoria numa equipa*/
		while(tmp2 != NULL){
			if(tmp2->vitorias == max){
				contador_equipas += 1;
			}
			tmp2 = tmp2->proximo;
		}/*Conta quantas equipas tem esse valor max como vitoria*/
		equipas_maior = malloc(sizeof(char*) * contador_equipas);
		while(tmp3 != NULL){
			if(tmp3->vitorias == max){
				equipas_maior[i] = malloc(sizeof(char)*(strlen(tmp3->nome)+1));
				strcpy(equipas_maior[i], tmp3->nome);
				i++;
			}
			tmp3 = tmp3->proximo; /*Mete as equipas que correspondem
			ao criterio num array com memoria previamente alocada*/
		}
		printf("%d Melhores %d\n", *NL, max);
		sort(equipas_maior, contador_equipas); /*Ordena o array por ordem lexicografica*/
	    for (i = 0; i < contador_equipas; i++){
	        printf("%d * %s\n",*NL, equipas_maior[i]); /*Imprime o resultado*/
	    }
	    for(i = 0; i < contador_equipas; i++){
	    	free(equipas_maior[i]);
	    }
		free(equipas_maior); /*Liberta a memoria que foi alocada previamente para o array*/
	}
	*NL += 1;

}
