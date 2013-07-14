include ../common.mk

SRC += sha.c sha_driver.c

all: x86

x86:
	$(CC) $(FLAGS) $(SRC) -o x86_sha

clean:
	rm -f *.o x86_sha
