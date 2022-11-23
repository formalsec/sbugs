########### Compilers ###########
CC = gcc
CLANG = clang
##################################


############ Flags ###########
CLANG_FLAGS = -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone
CCFLAGS = -Wall -g -no-pie -Wno-int-conversion -Wno-implicit-function-declaration
##############################


############ Sources and Object files ############
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
##################################################


#Executable name
EXEC = $(shell basename $(CURDIR))

#Prepocessed Directory
PRE = preprocessed



#Compile to x86_64 Elf
all: $(OBJS)
	$(CC) $(CCFLAGS) -o $(EXEC).exe $(OBJS)

#Compile to Llvm bytecode
bc:
	$(CLANG) $(CLANG_FLAGS) -o $(EXEC).bc $(SRCS)



#Compile preprocessed to x86_64 Elf
pre: 
	+$(MAKE) -C $(PRE) -s

#Compile preprocessed to Llvm bytecode
pre_bc: 
	+$(MAKE) -C $(PRE) bc -s


#X86_64 object files
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@	


clean:
	$(RM) *.o *.exe *.bc $(PRE)/*.o $(PRE)/*.exe $(PRE)/*.bc

