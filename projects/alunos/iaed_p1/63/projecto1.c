#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "funcoes.h"
int main(){
  do{
    fgets(input,STRSIZE,stdin);
    switch (input[0]){

    case 'a':

        comando_a();
        break;

    case 'q':
        comando_q();
        break;

    case 'N':
        comando_N();
        break;

    case 'A':
        comando_A();
        break;

        case 'r':
        comando_r();
        break;

    case 'R':
        comando_R();
        break;

    case 'C':
        comando_C();
        break;

    case 'p':
        comando_p();
        break;

    case 'E':
        comando_E();
        break;


    case 'm':
        comando_m();
        break;


    case 'l':
        comando_l();
        break;


   case 'L':
        comando_L();
        break;

    	  default:
        break;
    }


  }while(input[0]!='x');


    return 0;
}