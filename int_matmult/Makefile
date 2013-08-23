include ../common.mk

SRC = matmult.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix int_matmult, $@)

clean:
	rm -f *.o *_int_matmult

# vim: set ts=4 sw=4 noet:
