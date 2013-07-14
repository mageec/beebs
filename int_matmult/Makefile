include ../common.mk

SRC += matmult.c

all: x86

x86:
	$(CC) $(FLAGS) $(SRC) -o x86_int_matmult

clean:
	rm -f *.o x86_int_matmult
