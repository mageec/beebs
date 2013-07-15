include ../common.mk

SRC += fir2dim.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix 2dfir, $@)

clean:
	rm -f *.o *_2dfir

# vim: set ts=4 sw=4 noet:
