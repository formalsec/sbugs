#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Files .h*/
#include "hashtabel.h"
#include "list.h"
#include "Games.h"

/******************************************************************************
 * Usage ()
 *
 * Arguments: nomeProg - name of executable
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: exit program when arguments are missing
 *
 *****************************************************************************/
void Usage(){
  /*exit program without output message*/
  exit(0);
}
/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int
 * Side-Effects: none
 *
 * Description: main Program
 *
 *****************************************************************************/
int main(int argc, char *argv[]){
  /*Declaration of variables*/
   FILE *fpIn, *fpOut;
   
   /* check if the program was correctly executed */
  if(( argc <  3)||(argc > 3))
    Usage();

  /*open files*/
  /*open input file in order to read it*/
  fpIn = fopen( argv[1], "r" );
  /*see if file exists*/
  if( fpIn == NULL ) exit(0);

	/*Open output file - read/write*/
  fpOut = fopen( argv[2], "wr" );
  if( fpOut == NULL ) exit(0);
  
  /*Main function*/
   Solve(fpIn, fpOut);
  /*free all alocated memory*/
  
  /* close all files */
  fclose(fpIn);
  fclose(fpOut);
   return 0;
}
