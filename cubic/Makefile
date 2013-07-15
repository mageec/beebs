include ../common.mk

SRC = basicmath_small.c cubic.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix cubic, $@) -lm

clean:
	rm -f *.o *_cubic

# vim: set ts=4 sw=4 noet:
