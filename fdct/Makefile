include ../common.mk

SRC += fdct.c

all: x86

x86:
	$(CC) $(FLAGS) $(SRC) -o x86_fdct

clean:
	rm -f *.o x86_fdct
