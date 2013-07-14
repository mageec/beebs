include ../common.mk

FLAGS += -lm

SRC += basicmath_small.c cubic.c

all: x86

x86:
	$(CC) $(FLAGS) $(SRC) -o x86_cubic

clean:
	rm -f *.o x86_cubic
