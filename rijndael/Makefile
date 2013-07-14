include ../common.mk

SRC += aes.c aesxam.c

all: x86

x86:
	$(CC) $(FLAGS) $(SRC) -o x86_rijndael

clean:
	rm -f *.o x86_rijndael
