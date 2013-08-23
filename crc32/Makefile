include ../common.mk

SRC = -static crc_32.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix crc32, $@)

clean:
	rm -f *.o *_crc32

# vim: set ts=4 sw=4 noet:
