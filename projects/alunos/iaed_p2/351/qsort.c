#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "qsort.h"

/* sorts chr_arr between left and right index according to their ascii values */
void quicksort(char **chr_arr,int left, int right,void *info_struct, swap_elem f_swap)
{
    int part_idx;
    /* return if the left index coincides or is beyond the right one*/
    if(left >= right)
    {
        return;
    }
    part_idx = part(chr_arr,left,right,info_struct,f_swap);
    /* sort both partitions around part_idx because the element
       arr[part_idx] is in its final position */
    quicksort(chr_arr,left,part_idx-1,info_struct,f_swap);
    quicksort(chr_arr,part_idx+1,right,info_struct,f_swap);
    return;

}

/* selects a random pivot, then places smaller chars to its
   left and bigger chars to its right
   returns the position of the pivot
   based on Lomutos partition scheme */
int part(char **chr_arr,int left, int right, void * info_struct, swap_elem f_swap)
{
    int swap_place = left + rand() % (right-left);
    int curr_idx,lower_idx = (left-1);
    /* move the selected pivot to right position */
    f_swap(swap_place,right,chr_arr,info_struct);
    for(curr_idx = left;curr_idx < right;curr_idx++)
    {
        /* swap if current indexs string compares smaller than
           pivots according to strcmp */
        if(strcmp(*(chr_arr+curr_idx),*(chr_arr+right)) <= 0)
        {
            f_swap(++lower_idx,curr_idx,chr_arr,info_struct);
        }
    }
    /* put the pivot in its final position */
    f_swap(++lower_idx,right,chr_arr,info_struct);
    return lower_idx;


}
