include ../common.mk

SRC = aes.c aesxam.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix rijndael, $@)

clean:
	rm -f *.o *_rijndael

# vim: set ts=4 sw=4 noet:
