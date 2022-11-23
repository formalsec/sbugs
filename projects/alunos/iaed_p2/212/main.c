#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "commands.h"

/* The main function of the program, invoking  functions for the individual commands. */
int main(void){
	int cmd, nl = 0;
	link head = NULL, last = NULL;
	Tree *g = initTree(); 
	Tree2 *t = initTree2();
	do {
		switch(cmd = rd_cmd()){
		case 'a': rd_ws(); cmd_a(&head, &last, &g, &t, ++nl); 	break;
		case 'A': rd_ws(); cmd_A(&t, ++nl); 					break;
		case 'l': 		   cmd_l(head, ++nl); 					break;
		case 'p': rd_ws(); cmd_p(&g, ++nl); 					break;
		case 'P': rd_ws(); cmd_P(&t, ++nl); 					break;
		case 'r': rd_ws(); cmd_r(&head, &last, &g, &t, ++nl);	break;
		case 's': rd_ws(); cmd_s(&g, &t, ++nl); 				break;
		case 'g': 		   cmd_g(t, ++nl); 						break;
		case 'x': 		   cmd_x(g, t);							break;
		}
	} while(cmd != 'x');
	return 0;
}

/*  Reads a given command. */
int rd_cmd(void) {
    const int r = getchar();
    return r;
}

/* Auxiliary function that expects whitespace and consumes it. */
char rd_ws(void) {
    const int w = getchar();
    return w;
}