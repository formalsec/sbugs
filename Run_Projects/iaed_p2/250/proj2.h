#ifndef PROJ_H
#define PROJ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNAME 1023
#define SIZE 2997 /*numero primo*/

/*ESTRUTURAS*/

/*#################################################################################################################################################

Estrutura Jogos - Criei uma estrutura com as diversas variavies que um jogo tem de ter nos inputs que o utilisador for colocar ao longo do programa:
nome jogo-equip1-equipa2-score1-score2.

Estrutura Equipas - Criei uma estrutura com as diversas variavies que um jogo tem de ter nos inputs que o utilisador for colocar ao longo do programa:
nome equipa-finalscore.

Estrutura Jogoslist - Vai representar uma lista duplamnte ligada. Desta forma tera um head e root que sao do tipo Jogos.

Estrutura Equipaslist - Vai representar uma lista duplamnte ligada. Desta forma tera um head e root que sao do tipo Equipas.

Estrutura Nodo_jogo - Esta estrutura vai definir cada um dos jogos da Hash Table. Desta forma, tera um componente equipa que aponta para a estrutura
dos Jogos, bem como um ponteiro para next qeu apontara para a proxima posicao.

Estrutura Nodo_equipa - Esta estrutura vai definir cada uma das equipas da Hash Table. Desta forma, tera um componente equipa que aponta para a 
estrutura das Equipas, bem como um ponteiro para next qeu apontara para a proxima posicao na Hash Table. 

#################################################################################################################################################*/

typedef struct Jogos{
	char *nome;
	char *equipa1; 
	char *equipa2; 
	int score1;
	int score2;
	struct Jogos *next; 
	struct Jogos *prev;
}Jogos; 


typedef struct Equipas{
	char *nome; 
	int finalscore;
	struct Equipas *next_e; 
	struct Equipas *prev_e;
}Equipas; 


typedef struct Jogoslist{
	struct Jogos *head; 
	struct Jogos *root;
}Jogoslist; 



typedef struct Nodo_jogo{
	Jogos *jogo;
	struct Nodo_jogo *next;
}Nodo_jogo; 


typedef struct Nodo_equipa{
	Equipas *equipa;
	struct Nodo_equipa *next_e; 
}Nodo_equipa; 



/*#################################################################################################################################################
inicializa_l_jogos: Ambas funcoes sao funcoes auxiliares que incializao as listas ligadas, alocando espaco na memoria. (visto que so iremos usar as listas para ser 
mais facil de implementar a funcao l - onde temos de imprimir pela ordem que foram introduzidos)
#################################################################################################################################################*/
Jogoslist* inicializa_l_jogos();



/*#################################################################################################################################################
inicializa_jogo s & inicializa_equipa

Ambas funcoes sao funcoes auxiliares que incializao as Hash Tables, incializando-as a NULL
#################################################################################################################################################*/
void inicializa_jogo(Nodo_jogo **table); 
void inicializa_equipa(Nodo_equipa** table);



/*#################################################################################################################################################
hash: Esta funcao auxiliar recebe um nome e encontra a sua posicao(index) na Hash Table, para que seja mais facil de procurar
#################################################################################################################################################*/
unsigned long hash(char* nome);



/*#################################################################################################################################################
alocar_jogos: Esta funcao auxiliar ira receber as variavies para a funcao "a", e ira alocar a respetiva memoria para cada componente. 
Inicializando tambem os ponteiros next e prev a NULL.

alocar_equipas_nome: Esta funcao auxiliar ira receber a variavel nome, e ira alocar a respetiva memoria para cada componente. 
Inicializando tambem os ponteiros next e prev a NULL.
#################################################################################################################################################*/
Jogos* alocar_jogos();
Equipas* alocar_equipas_nome();



/*#################################################################################################################################################
free_item: Esta funcao tem como objetivo libertar a memoria que esta associado a um certo jogo, bem como a todos os seus componentes.  

free_item_e: Esta funcao tem como objetivo libertar a memoria que esta associado a uma certa equipa, bem como a todos os seus componentes.  

clean_array: Esta funcao tem como objetivo limpar o array com o nome das equipas
#################################################################################################################################################*/
void malloc_array(char **array, int k);
void free_item(Jogos* item);
void free_item_e(Equipas* item);
void libertajogohash(Nodo_jogo *c);
void libertaequipahash(Nodo_equipa *c);



/*#################################################################################################################################################
insert: Esta funcao tem como objetivo adicionar a Hash Table dos jogos um certo jogo recebido.  

insert_e: Esta funcao tem como objetivo adicionar a Hash Table das equipas uma certa equipa recebido.  

inserir_score: Esta funcao tem como objetivo inserir a pontuacao de um jogo na Hash Table. Caso a pontuacao de uma das equipas seja maior que a outra, 
entao incrementa o finalscore da equipa, caso as pontuacoes sejam iguais, nao e adicionado nem retirado pontuacao dessa equipa.
#################################################################################################################################################*/
int insert(Nodo_jogo **table, Jogos* novojogo);
int insert_e(Nodo_equipa **table, Equipas* novaequipa);
void inserir_score(Nodo_equipa **table_e, int score1, int score2, char *equipa1, char* equipa2);



/*#################################################################################################################################################
search: Esta funcao tem como objetivo procurar um nome na Hash Table dos jogos, retornadno o index se existir, senao retorna -1.

search_e: Esta funcao tem como objetivo procurar um nome na Hash Table das equipas, retornadno o index se existir, senao retorna -1.
#################################################################################################################################################*/
int search(Nodo_jogo** table, char *nome);
int search_e(Nodo_equipa** table, char *name);



/*#################################################################################################################################################
pop_node: Funcao auxiliar que tem como objetivo apagar da lista de jogos, desta forma, temos de analisar tres opcoes: 
	1 - caso a lista apenas tenha um elemento
	2 - caso a lista tenha mais do que um elemento e estamos a retirar o primeiro
	3 - caso a lista tenha mais elementos e estejamos a tirar do meio

apaga: Esta funcao tem como objetivo apagar um jogo da Hash Table dos jogos se o jogo e apagado entao teremos de 
retirar o valor desse jogo nas equipas (usando a funcao pop_node).
#################################################################################################################################################*/
void pop_node (Jogoslist *l, Jogos *n);
void apaga(Jogoslist* lista, char name[MAXNAME], Nodo_jogo** table, Nodo_equipa** table_e);



/*#################################################################################################################################################
Adiciona um novo jogo

Na funcao main, ao ativar o comando a, esta sera a funcao utilizada.
Tem como objetivo adicionar um jogo.
Caracteristicas da funcao:
Formato de entrada: 'a nome:equipa1:equipa2:score1:score2'
Formato de saida: NADA (excepto erro)
Erros:
  - `Equipa inexistente.` caso uma das equipas (ou ambas) nao existir. Logo nao foi adicionado a lista das Equipas. 
  -'Jogo existente' no caso de o nome do jogo ja existir no sistema.
#################################################################################################################################################*/
void adiciona_jogo (int i, Jogoslist* lista,Nodo_jogo **hashtable_j, Nodo_equipa** hashtable_e);



/*#################################################################################################################################################
Adiciona uma nova equipa

Na funcao main, ao ativar o comando A, esta sera a funcao utilizada.
Tem como objetivo adicionar uma nova equipa na Hash Table das equipas.
Caracteristicas da funcao:
Formato de entrada: 'A nome'
Formato de saida: NADA (excepto erro)
Erros:
  - `Equipa existente.` no caso de o nome da Equipa ja existir no sistema.
#################################################################################################################################################*/
void adiciona_equipa (int i, Nodo_equipa **hashtable_e, int *teams);



/*#################################################################################################################################################
Lista todos os jogos introduzidos

Na funcao main, ao ativar o comando l, esta sera a funcao utilizada.
Tem como objetivo imprimir todos os jogos introduzidos.
Caracteristicas da funcao:
Formato de entrada: 'l'
Formato de saida: nome-jogo nome-equipa1 nome-equipa2 score1 score2
#################################################################################################################################################*/
void lista(int i, Jogos*l);


/*#################################################################################################################################################
Procura um jogo com o nome dado

Na funcao main, ao ativar o comando p, esta sera a funcao utilizada.
Tem como objetivo procurar um determinado jogo
Caracteristicas da funcao:
Formato de entrada: 'p nome'
Formato de saida: nome-jogo 
Erros: 
- 'Jogo inexistente' no caso de nao existir nenhum jogo com esse nome no sistema.
#################################################################################################################################################*/
void procurajogo(int i,Nodo_jogo**table);



/*#################################################################################################################################################
Procura uma equipa com o nome dado

Na funcao main, ao ativar o comando P, esta sera a funcao utilizada.
Tem como objetivo procurar uma determinada equipa
Caracteristicas da funcao:
Formato de entrada: 'P nome'
Formato de saida: nome numero-de-jogos-ganhos
Erros: 
- 'Equipa inexistente' no caso de nao existir nenhuma equipa com esse nome no sistema.
#################################################################################################################################################*/
void procuraequipa(int i,Nodo_equipa**table);



/*#################################################################################################################################################
Altera um valor na pontuacao de um jogo

Na funcao main, ao ativar o comando s, esta sera a funcao utilizada.
Caracteristicas da funcao:
Formato de entrada: 's nome:score1:score2'
Formato de saida: NADA
Erros: 
- 'Jogo inexistente' no caso de nao existir nenhum jogo com esse nome no sistema.
#################################################################################################################################################*/
void altera_pontos(int i,Nodo_jogo**table, Nodo_equipa**table_e);



/*#################################################################################################################################################
Retira um jogo da Hash Table

Na funcao main, ao ativar o comando r, esta sera a funcao utilizada.
Caracteristicas da funcao:
Formato de entrada: 'r nome'
Formato de saida: NADA
Erros: 
- 'Jogo inexistente.' no caso de nao existir nenhum jogo com esse nome no sistema.
###################################m##############################################################################################################*/
void remover(int i,Jogoslist* nova, Nodo_jogo** table, Nodo_equipa** table_e);



/*#################################################################################################################################################
Ordenar pela ordem de entrada

Na funcao main, ao ativar o comando r, esta sera a funcao utilizada.

Caracteristicas da funcao:

Formato de entrada: 'r nome'
Formato de saida: NADA
Erros: 
- 'Jogo inexistente.' no caso de nao existir nenhum jogo com esse nome no sistema.
###################################m##############################################################################################################*/
void ordena(int i, int *teams, Nodo_equipa** table);



#endif