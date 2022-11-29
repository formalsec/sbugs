########### Compilers ###########
CC = gcc
CLANG = clang

#Llvm linker
LLVM_LINK = llvm-link-11
#################################


############ Flags ###########
CLANG_FLAGS = -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone -Wno-implicit-function-declaration -Wno-int-conversion
CCFLAGS = -Wall -g -no-pie -Wno-int-conversion -Wno-implicit-function-declaration 
############################## 


############ Sources ###########
SRCS = $(wildcard *.c)
################################


############ Object Files ###########
OBJS = $(SRCS:.c=.o)
BC_OBJS = $(SRCS:.c=.bc)
####################################


#x86_64 Elf
all: $(OBJS)

#Llvm bytecode
bc: $(BC_OBJS)


#x86_64 Elf
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@	

#Llvm bytecode
%.bc: %.c
	$(CLANG) $(CLANG_FLAGS) $< -o $@


clean:
	$(RM) *.o *.exe *.bc 

