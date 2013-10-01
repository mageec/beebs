include ../common.mk

SRC = bf.c bf_cfb64.c bf_enc.c bf_skey.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix blowfish, $@)

clean:
	rm -f *.o *_blowfish

# vim: set ts=4 sw=4 noet:
