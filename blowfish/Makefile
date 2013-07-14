include ../common.mk

SRC += bf.c bf_cfb64.c bf_enc.c bf_skey.c

all: x86

x86:
	$(CC) $(FLAGS) $(SRC) -o x86_blowfish

clean:
	rm -f *.o x86_blowfish
