#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>

void klee_make_symbolic(void *addr, size_t nbytes, const char *name);

/*
void *new_sym_var(unsigned int length){
    length = length/8;
    void* sym = can_fail_malloc(length);
    klee_make_symbolic(sym, length, "sym");
    return *sym;

}
*/


void *new_sym_var(unsigned int length){
    
    length = length/8; 
    if(length == sizeof(char)){
        char sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_char");
        return sym;
    }

    else if (length == sizeof(int)){
        int sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_int");
        return sym;
    }

    else if (length == sizeof(long)){
        long sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_long");
        return sym;
    }  

    else if (length == sizeof(long int)){
        long int sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_long_int");
        return sym;
    }  

    else if (length == sizeof(long long)){
        long long sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_long_long");
        return sym;
    }  

    else if (length == sizeof(short int)){
        short int sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_short_int");
        return sym;
    }

    else if (length == sizeof(short)){
        short sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_short");
        return sym;
    }

    else{
        void* sym;
        klee_make_symbolic(&sym, sizeof(sym), "sym_unknown_type");
        return sym;
    }

}
