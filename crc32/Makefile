include ../common.mk

all: x86

x86:
	$(CC) $(FLAGS) $(SRC) -static crc_32.c -o x86_crc

clean:
	rm -f *.o x86_crc
