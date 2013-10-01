include ../common.mk

SRC = fdct.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix fdct, $@)

clean:
	rm -f *.o *_fdct

# vim: set ts=4 sw=4 noet:
