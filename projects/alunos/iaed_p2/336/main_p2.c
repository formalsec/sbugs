#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "games_struct.h"
#include "teams_struct.h"
#include "comands.h"

int main(){
    d_b *data_base = init_data_base();
    char comand; /* comando de input */
    scanf("%c", &comand);
    while (comand != 'x' && comand != EOF){
        if(comand != '\n')
        	comand_list(comand, data_base);
        scanf("%c", &comand);
    }
    destroy_data(data_base);
    return 0;
}