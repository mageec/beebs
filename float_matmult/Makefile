include ../common.mk

SRC = matmult.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix float_matmult, $@)

clean:
	rm -f *.o *_float_matmult

# vim: set ts=4 sw=4 noet:
