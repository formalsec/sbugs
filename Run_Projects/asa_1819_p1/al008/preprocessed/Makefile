########### Compilers ###########
CC = gcc
CLANG = clang

#Llvm linker
LLVM_LINK = llvm-link-11
#################################


############ Flags ###########
CLANG_FLAGS = -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone -Wno-implicit-function-declaration
CCFLAGS = -Wall -g -no-pie -Wno-int-conversion -Wno-implicit-function-declaration
############################## 


############ Sources ###########
SRCS = $(wildcard *.c)
SYMBOLIC = ../../symbolic
NEW_SYM_VAR = $(SYMBOLIC)/new_sym_var.c
NEW_SYM_VAR_KLEE = $(SYMBOLIC)/new_sym_var_klee.bc
################################


############ Object Files ###########
OBJS = $(SRCS:.c=.o)
BC_OBJS = $(SRCS:.c=.bc)
####################################

#Executable name
EXEC = $(shell basename $(dir $(abspath $(dir .))))


#x86_64 Elf
all: $(OBJS)
	+$(MAKE) -C $(SYMBOLIC) -s
	$(CC) $(CCFLAGS) -o $(EXEC).exe $(OBJS) $(NEW_SYM_VAR)

#Llvm bytecode
bc: $(BC_OBJS)
	+$(MAKE) -C $(SYMBOLIC) bc -s
	$(LLVM_LINK) -o $(EXEC).bc $(BC_OBJS) $(NEW_SYM_VAR_KLEE)


#x86_64 Elf
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@	

#Llvm bytecode
%.bc: %.c
	$(CLANG) $(CLANG_FLAGS) $< -o $@


clean:
	$(RM) *.o *.exe *.bc 

