#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*-------------------------------------//-------------------------------------*/
/*--------------------------------ASA projeto 1-------------------------------*/
/*---------------------------Carolina Brás ist 94227--------------------------*/
/*----------------------------João Diegues ist 90118--------------------------*/
/*-------------------------------------//-------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*----------------------------------constants---------------------------------*/
#define WHITE 0                     /*hasn't been tested for biggest chain yet*/
#define BLACK 1                               /*testing is over (chain is set)*/

/*---------------------------------structures---------------------------------*/
typedef struct dominoe {
	int root, chain, color;
}  Dominoe;

typedef struct connection{
	int x, y;                                               /*if x falls y falls*/
}  Connection;

/*PASSAR VARIÁVEIS PARA VARIÁVEIS GLOBAIS!!*/
/*------------------------------global variables------------------------------*/
Dominoe* dominoes;                         /*saves information on each dominoe*/
Connection* connections;                        /*saves links between dominoes*/
int n_dom, n_conn;                     /*number of dominoes and of connections*/
FILE *fp;                                       /*file (if input is from file)*/

/*---------------------------functions declarations---------------------------*/
void reads_input(int);
void initialize_dominoe(int);
void initialize_connections_file(int);
void initialize_connections_console(int);
void set_connection(int, int, int);
void dfs(int, int);

/*----------------------------------------------------------------------------*/
/*--------------------------------main function-------------------------------*/
/*----------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	int i, max_chain = 0, interventions = 0;
	if (argc == 2) {                                  /*is input given from file*/
		fp = fopen(argv[1], "r");                             /*opens file in read*/
	}
	reads_input(argc);           /*reads input and saves it in gloval structures*/

/*------------------calls a bfs routine for each root dominoe-----------------*/
	for (i = 1; i <= n_dom; i++) {                               /*tests dominoe*/
		if (dominoes[i].root == 1) {                        	/*is dominoe parent?*/
			interventions += 1;          /*adds an intervention for each root parent*/
			dfs(i, n_conn);
			if (max_chain < dominoes[i].chain) {    /*is the root chain the biggest?*/
				max_chain = dominoes[i].chain;
			}
		}
	}
	printf("%d %d\n", interventions, max_chain);                       /*OUTPUT!*/
	return 0;
}

/*----------------------------------------------------------------------------*/
/*---------------------------------reads input--------------------------------*/
/*----------------------------------------------------------------------------*/
void reads_input(int argc){
  if (argc == 2) {                                           /*input from file*/
        if (fscanf(fp, "%d %d", &n_dom, &n_conn)== 2){
        	dominoes = can_fail_realloc(dominoes, (n_dom+1) * sizeof(Dominoe));
          initialize_dominoe(n_dom);
				}
    connections = can_fail_realloc(connections, (n_conn+1) * sizeof(Connection));
		initialize_connections_file(n_conn);
    }
    else {                                                /*input from console*/
        if(scanf("%d %d", &n_dom, &n_conn)==2){
        	dominoes = can_fail_malloc((n_dom+1) * sizeof(Dominoe));
          initialize_dominoe(n_dom);
				}
    connections = can_fail_realloc(connections, (n_conn+1) * sizeof(Connection));
		initialize_connections_console(n_conn);
    }
}

/*-----------------------------initialize dominoes----------------------------*/
void initialize_dominoe(int n_dom){
	int i;
	for (i = 1; i <= n_dom; i++) {
		dominoes[i].root = 1;              /*dominoes initialized as root dominoes*/
		dominoes[i].color = WHITE;          /*dominoe hasn't been tested for chain*/
		dominoes[i].chain = 1;  /*number of dominoes that fall because of this one*/
	}
}

/*----------------------------initialize connections--------------------------*/
void initialize_connections_file(int n_conn) {
	int i, dom_1, dom_2;                                       /*input from file*/
	for (i = 1; i <= n_conn; i++) {
		if (fscanf(fp, "%d %d\n", &dom_1, &dom_2) == 2){
			set_connection(i, dom_1, dom_2);
		}
	}
}

void initialize_connections_console(int n_conn) {
	int i, dom_1, dom_2;                                    /*input from console*/
	for (i = 1; i <= n_conn; i++) {
		if (scanf("%d %d", &dom_1, &dom_2)==2){
			set_connection(i, dom_1, dom_2);
		}
	}
}

void set_connection(int i, int dom_1, int dom_2) {
	connections[i].x = dom_1;
	connections[i].y = dom_2;
	dominoes[dom_2].root = 0;      /*dominoe 2 is not root (doesn't have childs)*/
}


/*----------------------------------------------------------------------------*/
/*-------------------------------------dfs------------------------------------*/
/*----------------------------------------------------------------------------*/
void dfs(int father, int n_conn){
	int i, k;
	for (i = 1; i <= n_conn; i++) {
		if ((father == connections[i].x)              /*if a dominoe is parent and*/
		&& dominoes[connections[i].y].color != BLACK) {   /*hasn't yet been tested*/
			dfs(connections[i].y, n_conn);         /*call dfs recursively to test it*/
		}
		if ((father == connections[i].x)              /*if a dominoe is parent and*/
		&& dominoes[connections[i].y].color == BLACK) {  /*has already been tested*/
			k = dominoes[connections[i].y].chain + 1;      /*is it's child (chain+1)*/
			if (k > dominoes[father].chain) {             /* bigger then it's chain?*/
				dominoes[father].chain = k;                   /*if yes, save new chain*/
			}
		}
	}
	dominoes[father].color = BLACK;
/*setting a dominoe to BLACK is saying that it has already found it's max chain
valoue for all ramifications coming from him, no longer needs to be tested and
just has to pass on the value to any fathers that try to test him*/
}
