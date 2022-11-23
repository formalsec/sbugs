#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int c;
	createHash();
	NL = 0;
	while(1){
		c = getchar();
		switch(c){
			case 'A':
				NL++;
				A();
				break;
			case 'P':
				NL++;
				P();
				break;
			case 'L':
				printHash();
				break;
			case 'a':
				NL++;
				a();
				break;
			case 'l':
				NL++;
				l();
				break;
			case 'r':
				NL++;
				r();
				break;
			case 'p':
				NL++;
				p();
				break;
			case 's':
				NL++;
				s();
				break;
			case 'g':
				NL++;
				g();
				break;
			case 'x':
				destroyHash();
				destroyJogos();
				return 0;
		}
	}
	return 0;
}