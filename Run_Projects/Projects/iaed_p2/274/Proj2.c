#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estruturas.h"


#define MAXHASH 2497
#define MAXSTR 1024


/* Funcao auxiliar utilizada ao longo de todo o programa para achar o local numa hashtable
 onde uma determinada cadeia de caracteres se insere. */
int hash (char *n) {
	int h = 0, a = 127;
	for (; *n != '\0'; n++) {
		h = (a * h + *n) % MAXHASH;
	}
	return h;
}


/* Funcao auxiliar que ao iniciar a execucao do programa aloca a memoria necessaria
 a uma tabela com listas de jogos utilizada ao longo de todo o programa (hashtable). */
tabela *cria_tabela() {
    int i;
    tabela *tab = malloc(sizeof(tabela));
    for (i = 0; i < MAXHASH; i++)
        tab->vet[i] = NULL;
    return tab;
}


/* Funcao auxiliar que ao iniciar a execucao do programa aloca a memoria necessaria
 a lista de jogos utilizada ao longo de todo o programa */
lista *cria_lista() {
    lista *list = malloc(sizeof(lista));
    list->inicio = NULL;
    list->fim = NULL;
    return list;
}

/* Funcao auxiliar que ao iniciar a execucao do programa aloca a memoria necessaria
 a uma tabela com listas de equipas utilizada ao longo de todo o programa (hashtable). */
tabela_e *cria_tabela_e() {
	int i;
    tabela_e *tab_e = malloc(sizeof(tabela_e));
    for (i = 0; i < MAXHASH; i++)
        tab_e->vet[i] = NULL;
    return tab_e;
}


/* Funcao auxiliar que ao iniciar a execucao do programa aloca a memoria necessaria
 a lista de equipas utilizada ao longo de todo o programa */
lista_das_equipas *cria_lista_e() {
	lista_das_equipas *list_e = malloc(sizeof(lista_das_equipas));
    list_e->inicio = NULL;
    list_e->fim = NULL;
    return list_e;
}


/* Funcao auxiliar para que no fim da execucao do programa, quando o utilizador
 pretenda sair do mesmo ao passar o comando "x", para a linha de comandos, possamos
 libertar toda a memoria alocada durante o decorrer do mesmo. */
/* Mais concretamente, esta funcao liberta a memoria alocada relativa aos jogos. */
void elimina(tabela *tab, lista *list) {
    int i;
    hashtable *entrada, *temp;
    for (i = 0; i < MAXHASH; i++) {
        entrada = tab->vet[i];
        while (entrada != NULL) {
            free(entrada->item->nome);
            free(entrada->item->equipa_1);
            free(entrada->item->equipa_2);
            free(entrada->item);
            temp = entrada->seguinte; /* Para podermos dar free a entrada e 
            continuar a dar free aos seguintes jogos */
            free(entrada);
            entrada = temp;
        }
    }
    free(tab);
    free(list);
}


/* Funcao auxiliar para que no fim da execucao do programa, quando o utilizador
 pretenda sair do mesmo ao passar o comando "x", para a linha de comandos, possamos
 libertar toda a memoria alocada durante o decorrer do mesmo. */
/* Mais concretamente, esta funcao liberta a memoria alocada relativa as equipas. */
void elimina_e(tabela_e *tab_e, lista_das_equipas *list_e) {
    int i;
    hash_equipas *entrada, *temp;
    for (i = 0; i < MAXHASH; i++) {
        entrada = tab_e->vet[i];
        while (entrada != NULL) {
            free(entrada->item->nome);
            temp = entrada->seguinte;
            free(entrada);
            entrada = temp;
        }
    }
    free(tab_e);
    free(list_e);
}


/* Funcao auxiliar usada ao longo do programa para encontrar um jogo que se encontra
 "guardado", dentro de uma hashtable. */
/* Caso esteja na hashtable entao esta funcao retorna o mesmo, caso contrario NULL. */
hashtable *procura(tabela *tab, char *nome) {
    int i = hash(nome);
    hashtable *t;
    for (t = tab->vet[i]; t != NULL; t = t->seguinte) {
        if (strcmp(t->item->nome, nome) == 0) {
            return t;
        }
    }
    return NULL;
}


/* Funcao auxiliar a funcao 'adiciona_jogo' que aloca memoria correspondente a um jogo
 no sistema e adiciona esse mesmo jogo a uma lista duplamente ligada de jogos. */
lista *adiciona_j(tabela *tab, lista *list, char *nome, char *equipa_1, char *equipa_2,
 int resultado_1, int resultado_2, tabela_e *tab_e) {
    hashtable *entrada;
    jogo *j;
    int valor, valor1, valor2;
    j = malloc(sizeof(jogo));
    j->nome = malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(j->nome, nome);
    j->equipa_1 = malloc(sizeof(char) * (strlen(equipa_1) + 1));
    strcpy(j->equipa_1, equipa_1);
    j->equipa_2 = malloc(sizeof(char) * (strlen(equipa_2) + 1));
    strcpy(j->equipa_2, equipa_2);
    j->resultado_1 = resultado_1;
    j->resultado_2 = resultado_2;
    j->seguinte = NULL;
    j->anterior = list->fim;
    if (list->fim != NULL) {
    	list->fim->seguinte = j;
    }
    else {
    	list->inicio = j;
    }
    list->fim = j; /* o jogo e sempre adicionado no fim da lista */
    entrada = malloc(sizeof(hashtable)); /* aloca memoria para a entrada na hashtable */
    entrada->item = j;
    entrada->seguinte = NULL; 
    valor = hash(nome);
    valor1 = hash(equipa_1);
    valor2 = hash(equipa_2);
    entrada->seguinte = tab->vet[valor];
    tab->vet[valor] = entrada; /* introduz para dentro da hashtable
     a entrada que contem o jogo e o ponteiro para o jogo seguinte */
    if (resultado_1 > resultado_2) {
        tab_e->vet[valor1]->item->vitorias++; /* aumenta o valor das vitorias na estrutura da equipa */
        return list;
    }
    if (resultado_2 > resultado_1) {
        tab_e->vet[valor2]->item->vitorias++;
        return list;
    }
    return list;
}


/* Funcao auxiliar usada ao longo do programa para encontrar uma equipa que se encontra
 "guardada", dentro de uma hashtable. */
/* Caso esteja na hashtable entao esta funcao retorna a mesma, caso contrario NULL. */
hash_equipas *procura_e(tabela_e *tab_e, char *nome) {
    int i = hash(nome);
    hash_equipas *t;
    for (t = tab_e->vet[i]; t != NULL; t = t->seguinte) {
        if (strcmp(t->item->nome, nome) == 0) {
            return t;
        }
    }
	return NULL;
}


/* Formato de entrada: `a nome:equipa1:equipa2:score1:score2` */
/* Formato de saida: NADA (excepto erro).*/
/* Erros: */
/*        * `NL Jogo existente.` no caso de ja existir um jogo com esse nome no sistema. */
/*        * `NL Equipa inexistente.` no caso de uma das equipas ou ambas nao existirem no sistema. */
/* Funcao: Adicionar um jogo novo ao sistema. */
lista *adiciona_jogo(int contador, lista *list, tabela *tab, tabela_e *tab_e) {
	hashtable *g;
	hash_equipas *a, *b;
	char nome[MAXSTR], equipa_1[MAXHASH], equipa_2[MAXSTR];
	int resultado_1, resultado_2;
	scanf("%[^:]:%[^:]:%[^:]:%d:%d", nome, equipa_1, equipa_2, &resultado_1, &resultado_2);
	g = procura(tab, nome);
	a = procura_e(tab_e, equipa_1);
    b = procura_e(tab_e, equipa_2);
	if (g != NULL) {
		printf("%d Jogo existente.\n", contador);
		return list;	
	}
	if (a == NULL || b == NULL) {
		printf("%d Equipa inexistente.\n", contador);
		return list;
	}
	else {
		list = adiciona_j(tab, list, nome, equipa_1, equipa_2, resultado_1, resultado_2, tab_e);
	}
    return list;
}


/* Formato de entrada: `l` */
/* Formato de saida: `NL nome-jogo nome-equipa1 nome-equipa2 score1 score2`,
 sendo NL o numero da linha de comandos. */
/* Erros: Nao aplicavel. */
/* Funcao: Listar todos os jogos inseridos no sistema pela sua ordem se insercao. */
/* No caso de nao haver nenhum jogo no sistema, nao imprime nada */
void lista_j(int contador, lista *list) {
	jogo *temp = list->inicio; /* cria um jogo temporario (auxiliar) para
     nao alterar o proprio jogo */
	if (temp == NULL) {
		return;
	}
	while(temp != NULL) {
		printf("%d %s %s %s %d %d\n", contador, temp->nome, temp->equipa_1,
		 temp->equipa_2, temp->resultado_1, temp->resultado_2);
		temp = temp->seguinte;	
	}
}


/* Formato de entrada: `p nome` */
/* Formato de saida: `NL nome-jogo nome-equipa1 nome-equipa2 score1 score2` */
/* Erros: */
/*        * `NL Jogo inexistente.` no caso de nao existir nenhum jogo com esse nome no sistema. */
/* Funcao: Procurar um jogo com um nome dado. */
void procura_jogo(int contador, tabela *tab) {
	char nome[MAXSTR];
	hashtable *entrada;
	scanf("%[^:\n]", nome);
	entrada = procura(tab, nome);
	if (entrada == NULL) {
		printf("%d Jogo inexistente.\n", contador);
	}
	else {
	   printf("%d %s %s %s %d %d\n",contador, entrada->item->nome, entrada->item->equipa_1,
	 entrada->item->equipa_2, entrada->item->resultado_1, entrada->item->resultado_2);
	}
}


/* Funcao auxiliar a funcao 'adiciona_equipa' que aloca memoria correspondente a uma equipa no
 sistema e adiciona essa equipa a uma lista duplamente ligada de equipas. */
lista_das_equipas *adiciona_e(tabela_e *tab_e, lista_das_equipas *list_e, char *nome) {
	hash_equipas *entrada;
	equipa *e;
	int valor;
	e = malloc(sizeof(equipa));
    e->nome = malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(e->nome, nome);
    e->vitorias = 0;
    e->seguinte = NULL;
    e->anterior = list_e->fim;
    if (list_e->fim != NULL) {
    	list_e->fim->seguinte = e;
    }
    else {
    	list_e->inicio = e;
    }
    list_e->fim = e;
    entrada = malloc(sizeof(hash_equipas)); /* aloca memoria para a entrada na hashtable */
    entrada->item = e;
    entrada->item->vitorias = 0; /* inicia o valor das vitorias na estrutura da equipa */
    entrada->seguinte = NULL;
    valor = hash(nome);
    entrada->seguinte = tab_e->vet[valor];
    tab_e->vet[valor] = entrada;
    return list_e;
}


/* Formato de entrada: `A nome` */
/* Formato de saida: NADA (excepto erro). */
/* Erros: */
/*        * `NL Equipa existente.` no caso de ja existir uma equipa com esse nome no sistema. */
/* Funcao: Adicionar uma nova equipa ao sistema. */
lista_das_equipas *adiciona_equipa(int contador, lista_das_equipas *list_e, tabela_e *tab_e) {
	hash_equipas *entrada;
	char nome[MAXSTR];
	scanf("%[^:\n]", nome);
	entrada = procura_e(tab_e, nome);
	if (entrada != NULL) {
		printf("%d Equipa existente.\n", contador);
		return list_e;
	}
	else {
		list_e = adiciona_e(tab_e, list_e, nome); /* guarda a lista depois de adicionar a equipa */
		return list_e;
	}
}


/* Formato de entrada: `P nome` */
/* Formato de saida: `NL nome numero-de-jogos-ganhos` */
/* Erros: */
/*        * `NL Equipa inexistente.` no caso de nao existir nenhuma equipa com esse nome no sistema. */
/* Funcao: Procurar uma equipa dado um nome. */
void procura_equipa(int contador, tabela_e *tab_e) {
    char nome[MAXSTR];
    hash_equipas *entrada;
    scanf("%[^:\n]", nome);
    entrada = procura_e(tab_e, nome);
    if (entrada == NULL) {
        printf("%d Equipa inexistente.\n", contador);
    }
    else {
        printf("%d %s %d\n",contador, entrada->item->nome, entrada->item->vitorias);
    }
}


/* Funcao auxiliar a funcao principal 'apaga_jogo' e a auxiliar 'apaga_j' que remove o
 jogo da lista duplamente ligada de jogos. */
lista *remove_jogo(lista *list, jogo *j) {
    if (j == list->inicio) {
        j->anterior = NULL;
    }
    if (j == list->fim) {
        j->seguinte =  NULL;
    }
    if (j->anterior == NULL) {
        list->inicio = j->seguinte;
    } 
    else {
        j->anterior->seguinte = j->seguinte;
    }
    if (j->seguinte == NULL) {
        list->fim = j->anterior;
    } 
    else {
        j->seguinte->anterior = j->anterior;
    }
    return list;
}


/* Funcao auxiliar a funcao principal 'apaga_jogo' que liberta a memoria do jogo que foi
 alocada anteriormente ao ser inserido no sistema. Caso um equipa tenha ganho esse jogo
 entao a sua vitoria sera retirada. */
lista *apaga_j(tabela *tab, lista *list, char *nome, tabela_e *tab_e) {
    jogo *j, *temp;
    int valor, valor1, valor2;
    valor = hash(nome);
    temp = list->inicio; /* para nao alterar o jogo */
    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            j = temp;
        }
        temp = temp->seguinte;
    }
    valor1 = hash(j->equipa_1);
    valor2 = hash(j->equipa_2);
    list = remove_jogo(list, j);
    tab->vet[valor] = NULL;
    if (j->resultado_1 > j->resultado_2) {
        tab_e->vet[valor1]->item->vitorias--;
        return list;
    }
    if (j->resultado_2 > j->resultado_1) {
        tab_e->vet[valor2]->item->vitorias--;
        return list;
    }
    free(j->nome); /* liberta a memoria que alocou ao inserir o jogo */
    free(j->equipa_1);
    free(j->equipa_2);
    free(j);
    return list;
}


/* Formato de entrada: `r nome` */
/* Formato de saida: NADA (excepto erro). */
/* Erros: */
/*        * `NL Jogo inexistente.` no caso de nao existir nenhum jogo com esse nome no sistema. */
/* Funcao: Apagar um jogo dado um nome. */
lista *apaga_jogo(int contador, lista *list, tabela *tab, tabela_e *tab_e) {
    char nome[MAXSTR];
    hashtable *entrada;
    scanf("%[^:\n]", nome);
    entrada = procura(tab, nome);
    if (entrada == NULL) {
        printf("%d Jogo inexistente.\n", contador);
        return list;
    }
    else {
        list = apaga_j(tab, list, nome, tab_e); /* guarda a lista depois de apagar o jogo */
        return list;
    }
}


/* Formato de entrada: `s nome:score1:score2` */
/* Formato de saida: NADA (excepto erro). */
/* Erros: */
/*        * `NL Jogo inexistente.` no caso de nao existir nenhum jogo com esse nome no sistema. */
/* Funcao: Alterar o score de um jogo dado o nome. */
lista *altera_score(int contador, lista *list, tabela *tab, tabela_e *tab_e) {
    int valor1, valor2, resultado_1, resultado_2, valor;
    char nome[MAXSTR];
    hashtable *entrada;
    jogo *temp;
    scanf("%[^:]:%d:%d", nome, &resultado_1, &resultado_2);
    entrada = procura(tab, nome);
    temp = list->inicio;
    if (entrada == NULL) {
        printf("%d Jogo inexistente.\n", contador);
        return list;
    }
    valor = hash(nome);
    valor1 = hash(entrada->item->equipa_1);
    valor2 = hash(entrada->item->equipa_2);
    if (tab->vet[valor]->item->resultado_1 == tab->vet[valor]->item->resultado_2) {
        if (resultado_1 > resultado_2) {
            tab_e->vet[valor1]->item->vitorias++;
        }
        if (resultado_2 > resultado_1) {
            tab_e->vet[valor2]->item->vitorias++;
        }
        tab->vet[valor]->item->resultado_1 = resultado_1;
        tab->vet[valor]->item->resultado_2 = resultado_2; 
    }
    if (tab->vet[valor]->item->resultado_1 > tab->vet[valor]->item->resultado_2) {
        if (resultado_1 < resultado_2) {
            tab_e->vet[valor1]->item->vitorias--;
            tab_e->vet[valor2]->item->vitorias++;
        }
        if (resultado_1 == resultado_2) {
            tab_e->vet[valor1]->item->vitorias--;
        }
        tab->vet[valor]->item->resultado_1 = resultado_1;
        tab->vet[valor]->item->resultado_2 = resultado_2;
    }
    if (tab->vet[valor]->item->resultado_2 > tab->vet[valor]->item->resultado_1) {
        if (resultado_2 < resultado_1) {
            tab_e->vet[valor2]->item->vitorias--;
            tab_e->vet[valor1]->item->vitorias++;
        }
        if (resultado_1 == resultado_2) {
            tab_e->vet[valor2]->item->vitorias--;
        }
        tab->vet[valor]->item->resultado_1 = resultado_1;
        tab->vet[valor]->item->resultado_2 = resultado_2;
    }
    while (temp != NULL) { /* percorre a lista ate encontrar o jogo e modifica os resultados */
        if (strcmp(temp->nome, nome) == 0) {
            temp->resultado_1 = resultado_1;
            temp->resultado_2 = resultado_2;
        }
        temp = temp->seguinte;
    }
    return list;
}


/* Funcao auxiliar que calcula o tamanho de uma lista de equipas */
int tamanho_lista(lista_das_equipas *list_e) {
    int valor = 0;
    equipa *e, *aux;
    e = list_e->inicio;
    aux = e;
    while (aux != NULL) {
        valor++;
        aux = aux->seguinte;
    }
    return valor;
}


/* Funcao auxiliar ao uso da funcao built-in qsort() que ordena de forma lexicografica */
int compara_nome(const void *a, const void *b) {
    char *e1 = *(char **)a;
    char *e2 = *(char **)b;
    return strcmp(e1, e2);
}


/* Formato de entrada: `g` */
/* Formato de saida:    NL Melhores numero-de-jogos-ganhos */
/*                      NL * nome-equipa1 */
/*                      NL * nome-equipa2 */
/*                      NL * nome-equipa3 */
/* Erros:  Nao aplicavel. */
/* Funcao: Encontrar as equipas que ganharam mais jogos e lista por ordem lexicografica
 (do nome da equipa). */
/* No caso de nao haver nenhuma equipa no sistema, nao imprime nada */
void encontra_equipas(int contador, lista_das_equipas *list_e) {
    int i, e = 0, j = 0;
    equipa *temp;
    char **aux = malloc(sizeof(char*) * tamanho_lista(list_e));
    temp = list_e->inicio;
    if (list_e->inicio == NULL) {
        return;
    }
    while (temp != NULL) {
        if (temp->vitorias > j) {
            j = temp->vitorias;
        }
        temp = temp->seguinte;
    }
    temp = list_e->inicio;

    while (temp != NULL) {
        if (temp->vitorias == j) {
            aux[e] = temp->nome;
            e++;
        }
        temp = temp->seguinte;
    }
    qsort(aux, e, sizeof(char*), compara_nome);
    printf("%d Melhores %d\n", contador, j);
    for (i = 0; i < e; i++) {
        printf("%d * %s\n", contador, aux[i]);
    }
    free(aux);
}


/* Funcao geral que recebe um comando e direciona o utilizador consoante o mesmo */
int menu() {
	lista *list = cria_lista();
    tabela *tab = cria_tabela();
    lista_das_equipas *list_e = cria_lista_e();
    tabela_e *tab_e = cria_tabela_e();
	int contador = 0;
    int run = 1; /* Variavel de controlo para garatir que quando introduzimos o
    comando "x" o ciclo termina e sai do programa */
    char operation;
    while (run == 1) {
    	fflush(stdin); /* Limpa o standard input visto que o scanf() nao o faz */
        operation = getchar(); /* Guarda o comando numa variavel */
        switch (operation) {
            case 'a':
                getchar(); /* Fica com o espaco depois do comando */
            	contador++;
                list = adiciona_jogo(contador, list, tab, tab_e);
                break;
            case 'l':
                contador++;
                lista_j(contador, list);
                break;
            case 'p':
                getchar();
            	contador++;
                procura_jogo(contador, tab);
                break;
            case 'r':
                getchar();
                contador++;
                list = apaga_jogo(contador, list, tab, tab_e);
                break;
            case 's':
                getchar();
                contador++;
                list = altera_score(contador, list, tab, tab_e);
                break;
            case 'A':
                getchar();
            	contador++;
                list_e = adiciona_equipa(contador, list_e, tab_e);
                break;
            case 'P':
                getchar();
                contador++;
                procura_equipa(contador, tab_e);
                break;
            case 'g':
                contador++;
                encontra_equipas(contador, list_e);
                break;            
            case 'x':
                run = 0; /* Faz o "update" da variavel de controlo */
            	elimina(tab, list);
                elimina_e(tab_e, list_e);
                break;
        }
    }
    return 0;
}


/* Funcao principal que chama a funcao geral (menu) deste programa */
int main() {
    menu();
	return 0;
}

